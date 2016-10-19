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

#include "thread/threadregister.h"
#include "logger.h"

#include <algorithm>
#include <iostream>
#include <bits/c++config.h>

NetworkAudioManager::NetworkAudioManager() :
    mWorker(nullptr)
{
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<NetworkAudioManager, &NetworkAudioManager::onAsync>(this);
    mAsync.start();
}

void NetworkAudioManager::start()
{
    mWorker = new NetworkAudoThreadWorker(this);
    mWorker->start();
}

void NetworkAudioManager::addEventListener(INetworkAudoEvents* listener)
{
    mEventsListeners.push_back(listener);
}

void NetworkAudioManager::removeEventListener(INetworkAudoEvents* listener)
{
    mEventsListeners.remove(listener);
}

NetworkAudioManager::~NetworkAudioManager()
{
    if (mWorker) {
        mWorker->quit();
        delete mWorker;
    }
}

void NetworkAudioManager::startStream(const string& streamAddress)
{
    if (mWorker) {
        mWorker->startStream(streamAddress);
    }
}

void NetworkAudioManager::stopStream()
{
    if (mWorker) {
        mWorker->stopStream();
    }
}

bool NetworkAudioManager::isPlaying() const
{
    return false;
}

void NetworkAudioManager::onAsync()
{
    mMutex.lock();
    decltype(mPendingFunc) copy;
    copy.swap(mPendingFunc);
    mMutex.unlock();
    for (auto f : copy) {
        f();
    }

}

template<typename M, typename ... Args>
static void informAboutEvent(
        list<INetworkAudoEvents*> &mEventsListeners,
        list<function<void()>> &pendingFunc,
        mutex &mutex,
        ev::async &async,
        M m, Args ... args)
{
    mutex.lock();
    #define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
    auto f = [&]() {
        for (auto listener : mEventsListeners) {
            CALL_MEMBER_FN(listener, m)(std::forward<Args>(args)...);
            listener->onFailToStartNetworkStream();
        }
    };
    pendingFunc.push_back(f);
    mutex.unlock();
    async.send();    
}

void NetworkAudioManager::onFailToStartNetworkStream()
{
    cout << __func__ << endl;
    informAboutEvent(&INetworkAudoEvents::onFailToStartNetworkStream);
#if 0
    mMutex.lock();
    auto f = [this]() {
        for (auto listener : mEventsListeners) {
            listener->onFailToStartNetworkStream();
        }
    };
    mPendingFunc.push_back(f);
    mMutex.unlock();
    mAsync.send();
#endif
}

void NetworkAudioManager::onFinishNetworkStream()
{
    cout << __func__ << endl;
    informAboutEvent(&INetworkAudoEvents::onFinishNetworkStream);
}

void NetworkAudioManager::onStartNetworkStream()
{
    cout << __func__ << endl;
    informAboutEvent(&INetworkAudoEvents::onStartNetworkStream);
}

