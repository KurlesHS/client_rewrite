/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusesToLualMediator.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 18:59
 */

#ifndef HARDWARESTATUSESTOLUALMEDIATOR_H
#define HARDWARESTATUSESTOLUALMEDIATOR_H

#include "lua/iluascripteventlistener.h"
#include "lua/iluaevent.h"

#include "enumclasshash.h"
#include "ihardwarestatusesevents.h"

#include <unordered_map>
#include <string>

using namespace std;

class HardwareStatusesManager;
class LuaScriptManager;

class HardwareStatusesToLualMediator : public ILuaScriptEventsListener {
public:
    HardwareStatusesToLualMediator(HardwareStatusesManager *statusesManager, LuaScriptManager *luaManager);
    virtual ~HardwareStatusesToLualMediator();
    
    void luaEvent(ILuaEventSharedPtr event) override;
    
private:
    HardwareStatusesManager *mStatusesManager;
    LuaScriptManager *mLuaManager;
    unordered_map<ILuaEvent::EventType, IHardwareStatusesEvents::HardwareStatus, EnumClassHash> mHardwareStatusesHandlers;
    unordered_map<ILuaEvent::EventType, IHardwareStatusesEvents::NotifyStatus, EnumClassHash> mNotifyStatusesHandlers;
    

};

#endif /* HARDWARESTATUSESTOLUALMEDIATOR_H */

