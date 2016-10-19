/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudothreadworker.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 8:46
 */

#include <iostream>

#include <sys/ioctl.h>
#include <unistd.h>

#include "networkaudothreadworker.h"
#include "logger.h"

#include "thread/threadregister.h"
#include "inetworkaudioevents.h"

static pid_t start_avplay(const char *filepath, int &stdOutFd, int &stdErrFd)
{
    pid_t pid = 0;
    int pipeFdStdOut[2];
    int pipeFdStdErr[2];

    pipe(pipeFdStdOut); //create a pipe for stdout
    pipe(pipeFdStdErr); //create a pipe for stdin
    pid = fork(); //span a child process
    if (pid == 0) {
        // Дочерний процесс
        // закрываем пайпы на чтение
        close(pipeFdStdOut[0]);
        close(pipeFdStdErr[0]);
        dup2(pipeFdStdOut[1], STDOUT_FILENO);
        dup2(pipeFdStdErr[1], STDERR_FILENO);
        //  const char *command[] = {"avplay", "-nodisp", "-autoexit", mCurrentPlaybackFile.filePath.data(), "2>&1", NULL};
        // ffmpeg -i rtsp://192.168.56.1:9002/test.sdp -f s16le -acodec pcm_s16le pipe:1
        //-af aresample=resampler=soxr -ar 44100
        //execl("/usr/bin/ffmpeg", "/usr/bin/ffmpeg", "-i", filepath, "-f", "s16le", "-acodec", "pcm_s16le", "pipe:1", (char*) NULL);
        execl("/usr/bin/ffmpeg", "/usr/bin/ffmpeg", "-i", filepath, "-af", "aresample=resampler=soxr", "-ar", "48000", "-f", "s16le", "-acodec", "pcm_s16le", "-ac", "1", "pipe:1", (char*) NULL);
    }

    // Родительский процесс
    // закрываем пайпы на запись
    close(pipeFdStdOut[1]);
    close(pipeFdStdErr[1]);

    // отдаём файловые для обоих потоков вывода
    stdErrFd = pipeFdStdErr[0];
    stdOutFd = pipeFdStdOut[0];
    return pid;
}

NetworkAudoThreadWorker::~NetworkAudoThreadWorker()
{
}

NetworkAudoThreadWorker::NetworkAudoThreadWorker(INetworkAudoEvents *eventListener) :
    mEventListener(eventListener),
    mThreadLoop(nullptr),
    mIsThreadStarted(false),
    mIsNetworkStarted(false),
    mFfmpegPid(0),
    mStream(nullptr)
{

}

void NetworkAudoThreadWorker::start()
{
    mThread = thread(&NetworkAudoThreadWorker::threadProc, this);
    mThread.detach();
    std::unique_lock<std::mutex> lock(mWaitStartThreadMutex);
    mWaitStartThreadCondVar.wait(lock);
}

void NetworkAudoThreadWorker::threadProc()
{
    // mThread.detach();
    PaError error = Pa_Initialize();
    if (error == paNoError) {
        Logger::msg("portaudio library is initialzed");
    }
    ev::dynamic_loop loop;
    ThreadRegister::registerCurrentThread(loop);
    mThreadLoop = loop;
    mStdErrIo.set(loop);
    mStdErrIo.set<NetworkAudoThreadWorker, &NetworkAudoThreadWorker::onFfmegStdErr>(this);

    mStdOutIo.set(loop);
    mStdOutIo.set<NetworkAudoThreadWorker, &NetworkAudoThreadWorker::onFfmegStdOut>(this);

    mStartStreamWatchog.set(loop);
    mStartStreamWatchog.set<NetworkAudoThreadWorker, &NetworkAudoThreadWorker::onStartStreamTimeout>(this);

    mAsync.set(loop);
    mAsync.set<NetworkAudoThreadWorker, &NetworkAudoThreadWorker::onAsync>(this);
    mAsync.start();
    mAsync.send();
    mIsThreadStarted = true;
    mWaitStartThreadCondVar.notify_all();
    loop.run();
    mAsync.stop();
    ThreadRegister::unregisterCurrentThread();
    mThreadLoop = nullptr;
    if (error == paNoError) {
        Pa_Terminate();
    }
    mIsThreadStarted = false;
    mWaitStartThreadCondVar.notify_all();
}

void NetworkAudoThreadWorker::onStartStreamTimeout()
{
    stopStreamImpl();
}

void NetworkAudoThreadWorker::startStartStreamWatchdog()
{
    stopStartStreamWatchdog();
    mStartStreamWatchog.start(10);
}

void NetworkAudoThreadWorker::stopStartStreamWatchdog()
{
    if (mStartStreamWatchog.is_active()) {
        mStartStreamWatchog.stop();
    }
}

void NetworkAudoThreadWorker::startStream(const string& streamAddress)
{
    addPendingFunc([this, streamAddress]() {
        startStreamImpl(streamAddress);
    });
}

void NetworkAudoThreadWorker::stopStream()
{
    addPendingFunc([this]() {
        stopStreamImpl();
    });
}

void NetworkAudoThreadWorker::startStreamImpl(const string& streamAddress)
{
    stopStreamImpl();
    int out, err;
    mFfmpegPid = start_avplay(streamAddress.data(), out, err);
    if (mFfmpegPid > 0) {
        mIsInformedAboutFinish = false;
        mStdErrIo.start(err, ev::READ);
        mStdOutIo.start(out, ev::READ);
        startStartStreamWatchdog();
    }
}

void NetworkAudoThreadWorker::stopStreamImpl()
{
    stopPortAudio();
    if (mFfmpegPid > 0) {
        mStdErrIo.stop();
        mStdOutIo.stop();
        kill(mFfmpegPid, SIGTERM);
        onFfmpegExit();
    }
    mIsNetworkStarted = false;
}

void NetworkAudoThreadWorker::onFfmpegExit()
{    
    if (!mIsInformedAboutFinish) {
        mIsInformedAboutFinish = true;
        if (mIsNetworkStarted) {
            mEventListener->onFinishNetworkStream();
        } else {
            mEventListener->onFailToStartNetworkStream();
        }
    }
}

#define SOUND_FRAME_SIZE 512
#define SOUND_SAMPLE_RATE 48000

bool NetworkAudoThreadWorker::startPortAudio()
{
    cout << __func__ << endl;
    if (mStream) {
        // уже открыт
        return true;
    }
    PaStreamParameters outputStreamParameters;
    outputStreamParameters.device = Pa_GetDefaultOutputDevice();
    bool isStarted = outputStreamParameters.device != paNoDevice;
    if (isStarted) {
        outputStreamParameters.channelCount = 1;
        outputStreamParameters.sampleFormat = paInt16;
        outputStreamParameters.suggestedLatency = Pa_GetDeviceInfo((outputStreamParameters.device))->defaultLowOutputLatency;
        outputStreamParameters.hostApiSpecificStreamInfo = NULL;
        isStarted = Pa_OpenStream(&mStream, NULL, &outputStreamParameters,
                SOUND_SAMPLE_RATE, SOUND_FRAME_SIZE, paClipOff, &paCallback, this) == paNoError;
        if (isStarted) {
            isStarted = Pa_StartStream(mStream) == paNoError;
            if (!isStarted) {
                Pa_CloseStream(mStream);
                mStream = nullptr;
            }
        }
    }
    return mStream;
}

void NetworkAudoThreadWorker::stopPortAudio()
{
    cout << __func__ << endl;
    if (mStream) {
        Pa_StopStream(mStream);
        Pa_CloseStream(mStream);
        mStream = nullptr;
    }

}

int NetworkAudoThreadWorker::paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    (void) inputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    ((NetworkAudoThreadWorker*) userData)->playbackCallback(outputBuffer, framesPerBuffer);
    return paContinue;
}

void NetworkAudoThreadWorker::onFfmegStdErr(ev::io& io, int events)
{
    if (events & ev::READ) {
        int count;
        ioctl(io.fd, FIONREAD, &count);
        vector<char> buff;
        buff.resize(count);
        int len = read(io.fd, buff.data(), buff.size());
        if (len <= 0) {
            // все, выход из программы ffmpeg
            stopStartStreamWatchdog();
            io.stop();
            close(io.fd);
        } else {
            // nothing to do here.
            //printf("on std err read: %d: %s\n", count, buff.data());
        }
    }
}

void NetworkAudoThreadWorker::onFfmegStdOut(ev::io& io, int events)
{
    if (events & ev::READ) {
        int count;
        ioctl(io.fd, FIONREAD, &count);
        vector<char> buff;
        buff.resize(count);
        int len = read(io.fd, buff.data(), buff.size());
        if (len <= 0) {
            // все, выход из программы ffmpeg
            stopStartStreamWatchdog();
            io.stop();
            close(io.fd);
            onFfmpegExit();
        } else {
            // nothing to do here.
            //printf("on std err read: %d: %s\n", count, buff.data());
            mMutexForAudioData.lock();
            mAudioData.reserve(mAudioData.size() + buff.size());
            mAudioData.insert(mAudioData.end(), buff.begin(), buff.end());
            if (mAudioData.size() > 192000) {
                int half = mAudioData.size() / 2;
                if (half % 2 == 1) {
                    ++half;
                }
                mAudioData.erase(mAudioData.begin() + half, mAudioData.end());
            }
            if (!mIsNetworkStarted) {
                stopStartStreamWatchdog();
                startPortAudio();
                mIsNetworkStarted = true;
                mEventListener->onStartNetworkStream();
            }
            mMutexForAudioData.unlock();
        }
    }
}

void NetworkAudoThreadWorker::playbackCallback(void* outputBuffer, unsigned long framesPerBuffer)
{
    fflush(stdout);
    mMutexForAudioData.lock();

    int maxBytesToSend = framesPerBuffer * sizeof (int16_t);
    int bytesToSend = std::min(maxBytesToSend, (int) mAudioData.size());
    memcpy(outputBuffer, mAudioData.data(), bytesToSend);
    int remainBytes = maxBytesToSend - bytesToSend;
    if (remainBytes > 0) {
        memset(reinterpret_cast<char*> (outputBuffer) + bytesToSend, 0, remainBytes);
    }
    if ((int) mAudioData.size() <= bytesToSend) {
        mAudioData.clear();
    } else {
        mAudioData.erase(mAudioData.begin(), mAudioData.begin() + bytesToSend);
    }
    mMutexForAudioData.unlock();
}

void NetworkAudoThreadWorker::quit()
{
    if (mIsThreadStarted) {
        addPendingFunc([this]() {
            mThreadLoop.unloop();
        });
        std::unique_lock<std::mutex> lock(mWaitStartThreadMutex);
        mWaitStartThreadCondVar.wait(lock);
    }
}

void NetworkAudoThreadWorker::addPendingFunc(const function<void()>& func)
{
    mMutex.lock();
    mPendingFunc.emplace_back(func);
    mMutex.unlock();
    if (mAsync.is_active()) {
        mAsync.send();
    }
}

void NetworkAudoThreadWorker::onAsync()
{

    mMutex.lock();
    decltype(mPendingFunc) copy;
    copy.swap(mPendingFunc);
    mMutex.unlock();
    for (auto f : copy) {
        f();
    }
}

