/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwarestatusesmanager.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 15:50
 */

#include "hardwarestatusesmanager.h"

#include "thread/threadregister.h"

HardwareStatusesManager::HardwareStatusesManager()
{
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<HardwareStatusesManager, &HardwareStatusesManager::onAsync>(this);
    mAsync.start();
}

HardwareStatusesManager::~HardwareStatusesManager()
{
}

void HardwareStatusesManager::onAsync()
{
    mMutex.lock();
    decltype(mPendingFunc) copy;
    copy.swap(mPendingFunc);
    mMutex.unlock();
    for (auto f : copy) {
        f();
    }
}

void HardwareStatusesManager::addEventsListener(IHardwareStatusesEvents* listener)
{
    mEventsListeners.push_back(listener);
}

void HardwareStatusesManager::removeEventsListener(IHardwareStatusesEvents* listener)
{
    mEventsListeners.remove(listener);
}

IHardwareStatusesEvents::NotifyStatus HardwareStatusesManager::NotifyStatus(const string& hardwareId)
{
    auto it = mNotifyStatuses.find(hardwareId);
    if (it != mNotifyStatuses.end()) {
        return it->second;
    }
    return IHardwareStatusesEvents::NotifyStatus::Unknown;
}

IHardwareStatusesEvents::HardwareStatus HardwareStatusesManager::hardwareStatus(const string& hardwareId)
{
    auto it = mHardwareStatuses.find(hardwareId);
    if (it != mHardwareStatuses.end()) {
        return it->second;
    }
    return IHardwareStatusesEvents::HardwareStatus::Unknown;
}

void HardwareStatusesManager::setHardwareStatus(const string& hardwareId, const IHardwareStatusesEvents::HardwareStatus& hardwareStatus)
{
    mHardwareStatuses[hardwareId] = hardwareStatus;
    for (auto listener : mEventsListeners) {
        listener->onHardwareStatusChanged(hardwareId, hardwareStatus);
    }
}

void HardwareStatusesManager::setNotifyStatus(const string& hardwareId, const IHardwareStatusesEvents::NotifyStatus& notifyStatus)
{
    mNotifyStatuses[hardwareId] = notifyStatus;
    for (auto listener : mEventsListeners) {
        listener->onNotifyStatusChanged(hardwareId, notifyStatus);
    }
}

set<string> HardwareStatusesManager::hardwares() const
{
    set<string> result;
    
    for (auto it = mHardwareStatuses.begin(); it != mHardwareStatuses.end(); ++it) {
        result.insert(it->first);
    }
    
    for (auto it = mNotifyStatuses.begin(); it != mNotifyStatuses.end(); ++it) {
        result.insert(it->first);
    }
    
    return result;
}
