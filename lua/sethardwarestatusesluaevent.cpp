/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SetHardwareStatusesLuaEvent.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 16:27
 */

#include "sethardwarestatusesluaevent.h"

SetHardwareStatusesLuaEvent::SetHardwareStatusesLuaEvent(const ILuaEvent::EventType &type, const string &hardwareId) :
    mType(type),
    mHardwareId(hardwareId)
{
}

SetHardwareStatusesLuaEvent::~SetHardwareStatusesLuaEvent()
{
}

ILuaEvent::EventType SetHardwareStatusesLuaEvent::eventType() const
{
    return mType;
}

string SetHardwareStatusesLuaEvent::hardwareId() const
{
    return mHardwareId;
}

