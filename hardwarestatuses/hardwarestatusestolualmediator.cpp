/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusesToLualMediator.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 18:59
 */

#include "hardwarestatusestolualmediator.h"
#include "lua/luascriptmanager.h"
#include "hardwarestatusesmanager.h"
#include "lua/sethardwarestatusesluaevent.h"

HardwareStatusesToLualMediator::HardwareStatusesToLualMediator(HardwareStatusesManager *statusesManager, LuaScriptManager *luaManager) :
    mStatusesManager(statusesManager),
    mLuaManager(luaManager)
{
    mLuaManager->addLuaScriptEventListener(this);
    mHardwareStatusesHandlers[ILuaEvent::EventType::SetHardwareStatusFail] =
            IHardwareStatusesEvents::HardwareStatus::Fail;
    mHardwareStatusesHandlers[ILuaEvent::EventType::SetHardwareStatusUnknown] =
            IHardwareStatusesEvents::HardwareStatus::Unknown;
    mHardwareStatusesHandlers[ILuaEvent::EventType::SetHardwareStatusWork] =
            IHardwareStatusesEvents::HardwareStatus::Work;

    mNotifyStatusesHandlers[ILuaEvent::EventType::SetNotifyStatusError] =
            IHardwareStatusesEvents::NotifyStatus::Error;
    mNotifyStatusesHandlers[ILuaEvent::EventType::SetNotifyStatusProcess] =
            IHardwareStatusesEvents::NotifyStatus::Process;
    mNotifyStatusesHandlers[ILuaEvent::EventType::SetNotifyStatusUnknown] =
            IHardwareStatusesEvents::NotifyStatus::Unknown;
    mNotifyStatusesHandlers[ILuaEvent::EventType::SetNotifyStatusWait] =
            IHardwareStatusesEvents::NotifyStatus::Wait;
}

HardwareStatusesToLualMediator::~HardwareStatusesToLualMediator()
{
    mLuaManager->removeLuaScriptEventListener(this);
}

void HardwareStatusesToLualMediator::luaEvent(ILuaEventSharedPtr event)
{

    auto evtType = event->eventType();
    auto it = mHardwareStatusesHandlers.find(evtType);
    auto evt = static_cast<SetHardwareStatusesLuaEvent*> (event.get());
    if (it != mHardwareStatusesHandlers.end()) {
        mStatusesManager->setHardwareStatus(evt->hardwareId(), it->second);
    } else {
        auto it2 = mNotifyStatusesHandlers.find(evtType);
        if (it2 != mNotifyStatusesHandlers.end()) {
            mStatusesManager->setNotifyStatus(evt->hardwareId(), it2->second);
        }
    }
}