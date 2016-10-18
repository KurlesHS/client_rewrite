/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudiothread.cpp
 * Author: Alexey
 * 
 * Created on 18 октября 2016 г., 23:16
 */

extern "C"
{
#define __STDC_CONSTANT_MACROS
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "networkaudiothread.h"
#include "networkaudiomanager.h"

#include <vector>

#define TARGET_SAMPLE_RATE 41000
#define MAX_SAMPLE_BUFF_SIZE 3840

NetworkAudioThread::NetworkAudioThread(NetworkAudioManager *manager, const string &streamUrl) :
    mManager(manager),
    mStreamUrl(streamUrl),
    mExitRequest(false),
    mIsRunning(false),
    mResampler(nullptr),
    mCurrentOffset(0),
    mThread(&NetworkAudioThread::run, this)
{

}

NetworkAudioThread::~NetworkAudioThread()
{
    if (mResampler) {
        src_delete(mResampler);
        mResampler = nullptr;
        delete[] mResamplerData.data_in;
        delete[] mResamplerData.data_out;
    }
}

static int convertToS16LE(vector<int16_t> &out, AVCodecContext *codecContext, AVFrame *frame, const int planeSize)
{

    int datasize = -1;
    int sampleNum = 0;
    switch (codecContext->sample_fmt) {
        case AV_SAMPLE_FMT_S16P:
            for (unsigned int nb = 0; nb < planeSize / sizeof (uint16_t); nb++) {
                for (int ch = 0; ch < codecContext->channels; ch++) {
                    out[sampleNum] = ((uint16_t *) frame->extended_data[ch])[nb];
                    sampleNum++;
                }
            }
            datasize = (planeSize) * codecContext->channels;
            // ao_play(adevice, (char*)samples, (plane_size) * ctx->channels  );
            break;
        case AV_SAMPLE_FMT_FLTP:
            for (unsigned int nb = 0; nb < planeSize / sizeof (float); nb++) {
                for (int ch = 0; ch < codecContext->channels; ch++) {
                    out[sampleNum] = ((float *) frame->extended_data[ch])[nb] * std::numeric_limits<short>::max();
                    sampleNum++;
                }
            }
            datasize = (planeSize / sizeof (float)) * sizeof (uint16_t) * codecContext->channels;
            //ao_play(adevice, (char*)samples, ( plane_size/sizeof(float) )  * sizeof(uint16_t) * ctx->channels );
            break;
        case AV_SAMPLE_FMT_S16:
            //ao_play(adevice, (char*)frame->extended_data[0],frame->linesize[0] );
            datasize = frame->linesize[0];
            memcpy(out.data(), frame->extended_data[0], datasize);
            break;
        case AV_SAMPLE_FMT_FLT:
            for (unsigned int nb = 0; nb < planeSize / sizeof (float); nb++) {
                out[nb] = static_cast<short> (((float *) frame->extended_data[0])[nb] * std::numeric_limits<short>::max());
            }
            //ao_play(adevice, (char*)samples, ( plane_size/sizeof(float) )  * sizeof(uint16_t) );
            datasize = (planeSize / sizeof (float)) * sizeof (uint16_t);
            break;
        case AV_SAMPLE_FMT_U8P:
            for (unsigned int nb = 0; nb < planeSize / sizeof (uint8_t); nb++) {
                for (int ch = 0; ch < codecContext->channels; ch++) {
                    out[sampleNum] = (((uint8_t *) frame->extended_data[0])[nb] - 127) * std::numeric_limits<short>::max() / 127;
                    sampleNum++;
                }
            }
            //ao_play(adevice, (char*)samples, ( plane_size/sizeof(uint8_t) )  * sizeof(uint16_t) * ctx->channels );
            datasize = (planeSize / sizeof (uint8_t)) * sizeof (uint16_t) * codecContext->channels;
            break;
        case AV_SAMPLE_FMT_U8:
            for (unsigned int nb = 0; nb < planeSize / sizeof (uint8_t); nb++) {
                out[nb] = static_cast<short> ((((uint8_t *) frame->extended_data[0])[nb] - 127) * std::numeric_limits<short>::max() / 127);
            }
            datasize = (planeSize / sizeof (uint8_t)) * sizeof (uint16_t) * codecContext->channels;
            //ao_play(adevice, (char*)samples, ( plane_size/sizeof(uint8_t) )  * sizeof(uint16_t) );
            break;
        default:
            break;
    }
    return datasize;
}

void NetworkAudioThread::exit()
{
    mExitRequest = true;
}

void NetworkAudioThread::run()
{
    AVFormatContext* formatContext;
    AVCodecContext* codecContext;
    AVCodec* codec;
    unsigned int audioStreamNum;


    int err = avformat_open_input(&formatContext, mStreamUrl.data(), NULL, NULL);
    if (err < 0) {
        mIsRunning = false;
        //qWarning() << tr("ffmpeg: Unable to open input stream '%0'").arg(mAddress);
        formatContext = nullptr;
        return;
    }

    err = avformat_find_stream_info(formatContext, NULL);
    if (err < 0) {
        // qWarning() << tr("ffmpeg: Unable to find stream info ('%0')").arg(mAddress);
        avformat_close_input(&formatContext);
        formatContext = 0;
        mIsRunning = false;
        return;
    }

    for (audioStreamNum = 0; audioStreamNum < formatContext->nb_streams; ++audioStreamNum) {
        if (formatContext->streams[audioStreamNum]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            break;
        }
    }

    if (audioStreamNum == formatContext->nb_streams) {
        // qWarning() << tr("ffmpeg: Unable to find video stream ('%0')").arg(mAddress);
        avformat_close_input(&formatContext);
        formatContext = 0;
        mIsRunning = false;
        return;
    }

    codecContext = formatContext->streams[audioStreamNum]->codec;
    codec = avcodec_find_decoder(codecContext->codec_id);

    err = avcodec_open2(codecContext, codec, NULL);
    if (err < 0) {
        // qWarning() << tr("ffmpeg: Unable to open codec ('%0')").arg(mAddress);
        avformat_close_input(&formatContext);
        formatContext = 0;
        mIsRunning = false;
        return;
    }

    AVPacket readingPacket;
    int buffer_size = 192000 + FF_INPUT_BUFFER_PADDING_SIZE;

    vector<uint8_t> buffer;
    buffer.resize(buffer_size);
    vector<int16_t> out;
    out.resize(buffer.size() / 2);

    readingPacket.data = buffer.data();
    readingPacket.size = buffer.size();

    av_init_packet(&readingPacket);

    AVFrame *frame = av_frame_alloc();

    if (codecContext->sample_rate != TARGET_SAMPLE_RATE) {
        int error;
        float ratio = TARGET_SAMPLE_RATE / (float) codecContext->sample_rate;
        mResampler = src_new(SRC_ZERO_ORDER_HOLD, codecContext->channels, &error);
        src_set_ratio(mResampler, ratio);
        mResamplerData.src_ratio = ratio;
        mResamplerData.end_of_input = 1;
        mResamplerData.data_in = new float[MAX_SAMPLE_BUFF_SIZE];
        mResamplerData.data_out = new float[MAX_SAMPLE_BUFF_SIZE];
    }

    while (av_read_frame(formatContext, &readingPacket) == 0) {
        if (readingPacket.stream_index == static_cast<int> (audioStreamNum)) {
            int dataPrecent = 0;
            int planeSize;
            avcodec_decode_audio4(codecContext, frame, &dataPrecent, &readingPacket);
            int data_size = av_samples_get_buffer_size(&planeSize, codecContext->channels,
                    frame->nb_samples,
                    codecContext->sample_fmt, 1);
            (void) data_size;
            if (dataPrecent) {
                // всё хорошо здесь
                int sizeInBytes = convertToS16LE(out, codecContext, frame, planeSize);
                if (sizeInBytes) {
                    // а вот здесь бы не плохо бы еще и ресемпл сделать....
                    if (mResampler) {
                        /* таки ресемпл требуется ... */
                        int sizeInSamples = sizeInBytes / sizeof (int16_t);
                        for (int i = 0; i < sizeInSamples; ++i) {
                            mResamplerData.data_in[mCurrentOffset++] = out[i] / 32768.;
                        }
                        src_process(mResampler, &mResamplerData);
                        for (int i = 0; i < mResamplerData.output_frames_gen; ++i) {
                            out[i] = mResamplerData.data_out[i] * 32768;
                        }
                        sizeInBytes = mResamplerData.output_frames_gen * sizeof (int16_t);
                    }
                    
                    vector<char> audioData((char*)out.data(), (char*)out.data() + out.size() * sizeof(int16_t));
                    mManager->informAboutFailToStartPlayingNetworkStream();

                    // и отдать на проигрывание
                }
            }
        }
        av_packet_unref(&readingPacket);
        /* av_free_packet is deprecated */
        // av_free_packet(&readingPacket);
        if (mExitRequest) {
            break;
        }
    }
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    av_frame_free(&frame);
}

