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

#include <ev++.h>

#include <list>
#include <mutex>
#include <functional>

#include "networkaudothreadworker.h"



using namespace std;

#include "inetworkaudioevents.h"

class NetworkAudioManager : public INetworkAudoEvents
{
public:
    NetworkAudioManager();
    virtual ~NetworkAudioManager();
    
    void startStream(const string &streamAddress);
    void stopStream();
    
    void addEventListener(INetworkAudoEvents *listener);
    void removeEventListener(INetworkAudoEvents *listener);

    void start();

    bool isPlaying() const;

    void onFailToStartNetworkStream() override;
    void onStartNetworkStream() override;
    void onFinishNetworkStream() override;
    
private:
    void onAsync();
    
    template<typename M, typename ... Args>
    void informAboutEvent(M m, Args ... args)
{
    mMutex.lock();
    #define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
    auto f = [this, m, args...]() {
        for (auto listener : mEventsListeners) {
            CALL_MEMBER_FN(listener, m)(std::forward<Args>(args)...);            
        }
    };
    mPendingFunc.push_back(f);
    mMutex.unlock();
    mAsync.send();    
}

private:
    NetworkAudoThreadWorker *mWorker;
    list<INetworkAudoEvents*> mEventsListeners;
    list<function<void()>> mPendingFunc;    
    ev::async mAsync;
    mutex mMutex;

};

#endif /* NETWORKAUDIOMANAGER_H */
