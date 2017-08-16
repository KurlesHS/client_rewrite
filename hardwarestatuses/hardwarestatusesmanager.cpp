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
#include "logger.h"

HardwareStatusesManager::HardwareStatusesManager()
{
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<HardwareStatusesManager, &HardwareStatusesManager::onAsync>(this);
    mAsync.start();
    
    mHardwareStatusToString = {
        {IHardwareStatusesEvents::HardwareStatus::Fail, "fail"},
        {IHardwareStatusesEvents::HardwareStatus::Unknown, "unknown"},
        {IHardwareStatusesEvents::HardwareStatus::Work, "working"}
    };
    
    mNotifyStatusToString = {
        {IHardwareStatusesEvents::NotifyStatus::Error, "error"},
        {IHardwareStatusesEvents::NotifyStatus::Process, "process"},
        {IHardwareStatusesEvents::NotifyStatus::Unknown, "unknown"},
        {IHardwareStatusesEvents::NotifyStatus::Wait, "wait"}
    };        
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

IHardwareStatusesEvents::NotifyStatus HardwareStatusesManager::notifyStatus(const string& hardwareId)
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
    string strStatus("unknown");
    try {
        strStatus = mHardwareStatusToString.at(hardwareStatus);
    } catch (...) {
        
    }
    Logger::msg("hardware status of hardware with id '%s' changed to '%s'", hardwareId.data(), strStatus.data());
    for (auto listener : mEventsListeners) {
        listener->onHardwareStatusChanged(hardwareId, hardwareStatus);
    }
}

void HardwareStatusesManager::setNotifyStatus(const string& hardwareId, const IHardwareStatusesEvents::NotifyStatus& notifyStatus)
{
    mNotifyStatuses[hardwareId] = notifyStatus;
    string strStatus("unknown");
    try {
        strStatus = mNotifyStatusToString.at(notifyStatus);
    } catch (...) {
        
    }
    Logger::msg("notiy status of hardware with id '%s' changed to '%s'", hardwareId.data(), strStatus.data());
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
