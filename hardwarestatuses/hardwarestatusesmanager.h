/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwarestatusesmanager.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 15:50
 */

#ifndef HARDWARESTATUSESMANAGER_H
#define HARDWARESTATUSESMANAGER_H

#include "ihardwarestatusesevents.h"

#include "ev++.h"

#include <unordered_map>
#include <functional>
#include <mutex>
#include <list>
#include <set>

using namespace std;




class HardwareStatusesManager 
{
public:
    HardwareStatusesManager();    
    virtual ~HardwareStatusesManager();
    
    void addEventsListener(IHardwareStatusesEvents *listener);
    void removeEventsListener(IHardwareStatusesEvents *listener);
    
    IHardwareStatusesEvents::HardwareStatus hardwareStatus(const string &hardwareId);
    IHardwareStatusesEvents::NotifyStatus NotifyStatus(const string &hardwareId);
    
    void setHardwareStatus(const string &hardwareId, const IHardwareStatusesEvents::HardwareStatus &hardwareStatus);
    void setNotifyStatus(const string &hardwareId, const IHardwareStatusesEvents::NotifyStatus &notifyStatus);
    
    set<string> hardwares() const;
    
private:
    void onAsync();
    
private:
    list<function<void()>> mPendingFunc;    
    list<IHardwareStatusesEvents*> mEventsListeners;
    ev::async mAsync;
    mutex mMutex;
    unordered_map<string, IHardwareStatusesEvents::HardwareStatus> mHardwareStatuses;
    unordered_map<string, IHardwareStatusesEvents::NotifyStatus> mNotifyStatuses;
    
};

#endif /* HARDWARESTATUSESMANAGER_H */

