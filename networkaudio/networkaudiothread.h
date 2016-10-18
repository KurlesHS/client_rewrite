/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudiothread.h
 * Author: Alexey
 *
 * Created on 18 октября 2016 г., 23:16
 */

#ifndef NETWORKAUDIOTHREAD_H
#define NETWORKAUDIOTHREAD_H

#include <thread>
#include <atomic>

#include "3rdparty/rabbit/samplerate.h"

using namespace std;

class NetworkAudioManager;

class NetworkAudioThread {
public:
    NetworkAudioThread(NetworkAudioManager *manager, const string &streamUrl);
    virtual ~NetworkAudioThread();
    
    void exit();
    
private:
    void run();    
    
private:
    NetworkAudioManager *mManager;
    const string &mStreamUrl;
    atomic_bool mExitRequest;
    atomic_bool mIsRunning;
    SRC_STATE *mResampler;
    SRC_DATA mResamplerData;
    int mCurrentOffset;
    thread mThread;
    
};

#endif /* NETWORKAUDIOTHREAD_H */

