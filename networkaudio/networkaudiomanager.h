/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudiomanager.h
 * Author: Alexey
 *
 * Created on 18 октября 2016 г., 22:38
 */

#ifndef NETWORKAUDIOMANAGER_H
#define NETWORKAUDIOMANAGER_H

#include <list>
#include <mutex>
#include <vector>
#include <functional>

#include <ev++.h>

extern "C" {
#include <portaudio.h>
}

using namespace std;

class NetworkAudioManagerEvents {
public:
    virtual ~NetworkAudioManagerEvents();
    virtual void startPlayingNetworkStream() = 0;
    virtual void failToStartPlayingNetworkStream() = 0;
    virtual void finishPlayingNetworkStream() = 0;
};

class NetworkAudioManager {
public:
    NetworkAudioManager();
    virtual ~NetworkAudioManager();
    
    void start();
    
    bool isPlaying() const;
    
    
    // для внутреннего пользования
    void informAboutStartPlayingNetworkStream();
    void informAboutFailToStartPlayingNetworkStream();
    void informAboutFinishPlayingNetworkStream();
    
    void newAudioFrame(const vector<char> &frame);
    
   
    
private:
    void onAsync();
    
    void playbackCallback(void *outputBuffer, unsigned long framesPerBuffer);
    
    static int paCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );
private:
    ev::async mAsync;
    list<function<void()>> mPendingCommands;
    vector<char> mAudioData;
    
    PaStream *mStream;
    bool mIsPortAudioInitialized;
    mutex mMutex;

};

#endif /* NETWORKAUDIOMANAGER_H */

