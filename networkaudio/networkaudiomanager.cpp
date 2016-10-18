/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudiomanager.cpp
 * Author: Alexey
 * 
 * Created on 18 октября 2016 г., 22:38
 */

#include "networkaudiomanager.h"

extern "C"
{
#include <libavformat/avformat.h>
}

#include "thread/threadregister.h"
#include "logger.h"

#include <algorithm>


NetworkAudioManager::NetworkAudioManager() :
    mStream(0),
    mIsPortAudioInitialized(false)
{
    // инициализируем ffplay


    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<NetworkAudioManager, &NetworkAudioManager::onAsync>(this);
    mAsync.start();
}

void NetworkAudioManager::start()
{
    av_register_all();
    avformat_network_init();
    Logger::msg("libav is initialized");

    PaError error = Pa_Initialize();
    if (error == paNoError) {
        Logger::msg("portaudio library is initialzed");
    }
}

void NetworkAudioManager::onAsync()
{    
    for (auto f : mPendingCommands) {
        f();
    }
    
    mPendingCommands.clear();
}

int NetworkAudioManager::paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    ((NetworkAudioManager*)userData)->playbackCallback(outputBuffer, framesPerBuffer);
    return 0;
}

NetworkAudioManager::~NetworkAudioManager()
{
    if (mIsPortAudioInitialized) {
        Pa_Terminate();
    }
}

void NetworkAudioManager::newAudioFrame(const vector<char>& frame)
{
    mMutex.lock();
    mAudioData.reserve(mAudioData.size() + frame.size());
    mAudioData.insert(mAudioData.end(), frame.begin(), frame.end());
    mMutex.unlock();
}


void NetworkAudioManager::playbackCallback(void* outputBuffer, unsigned long framesPerBuffer)
{
    mMutex.lock();
    if (mAudioData.size() > 192000) {
        int half = mAudioData.size() / 2;
        if (half % 2 == 1) {
            ++half;
        }
        mAudioData.erase(mAudioData.begin() + half, mAudioData.end());
    }
    
    int maxBytesToSend = framesPerBuffer * sizeof(int16_t);
    int bytesToSend = std::min(maxBytesToSend, (int)mAudioData.size());
    memcpy(outputBuffer, mAudioData.data(), bytesToSend);
    if ((int)mAudioData.size() <= bytesToSend) {
        mAudioData.clear();
    } else {
        mAudioData.erase(mAudioData.begin(), mAudioData.begin() + bytesToSend);
    }
    mMutex.unlock();
}


void NetworkAudioManager::informAboutFailToStartPlayingNetworkStream()
{

}

void NetworkAudioManager::informAboutFinishPlayingNetworkStream()
{

}

void NetworkAudioManager::informAboutStartPlayingNetworkStream()
{

}

bool NetworkAudioManager::isPlaying() const
{
    return false;
}

NetworkAudioManagerEvents::~NetworkAudioManagerEvents()
{
}
