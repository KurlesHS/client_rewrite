/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudothreadworker.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 8:46
 */

#ifndef NETWORKAUDOTHREADWORKER_H
#define NETWORKAUDOTHREADWORKER_H

#include <ev++.h>

extern "C" {
#include <portaudio.h>
}

#include <condition_variable>
#include <functional>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <list>

using namespace std;

class INetworkAudoEvents;

class NetworkAudoThreadWorker
{
public:
    NetworkAudoThreadWorker(INetworkAudoEvents *eventListener);
    virtual ~NetworkAudoThreadWorker();

    void start();
    void quit();
    void threadProc();

    void startStream(const string &streamAddress);
    void stopStream();


private:
    void playbackCallback(void *outputBuffer, unsigned long framesPerBuffer);

    static int paCallback(const void *inputBuffer, void *outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void *userData);

    void addPendingFunc(const function<void()> &func);
    void onAsync();

    void onFfmegStdOut(ev::io &io, int events);
    void onFfmegStdErr(ev::io &io, int events);

    void startStreamImpl(const string &streamAddress);
    void stopStreamImpl();
    
    
    bool startPortAudio();
    void stopPortAudio();
    
    void startStartStreamWatchdog();
    void stopStartStreamWatchdog();
    
    void onStartStreamTimeout();
    
    void onFfmpegExit();

private:
    INetworkAudoEvents *mEventListener;
    thread mThread;
    mutex mMutex;
    mutex mMutexForAudioData;
    mutex mWaitStartThreadMutex;
    condition_variable mWaitStartThreadCondVar;
    ev::loop_ref mThreadLoop;
    ev::async mAsync;
    atomic_bool mIsThreadStarted;
    atomic_bool mIsNetworkStarted;    
    atomic_bool mIsInformedAboutFinish;
    list<function<void() >> mPendingFunc;
    vector<char> mAudioData;
    ev::io mStdOutIo;
    ev::io mStdErrIo;
    ev::timer mStartStreamWatchog;
    pid_t mFfmpegPid;
    
    PaStream *mStream;
};

#endif /* NETWORKAUDOTHREADWORKER_H */

