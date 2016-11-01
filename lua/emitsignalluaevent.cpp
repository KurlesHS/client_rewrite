/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EmitSignalLuaEvent.cpp
 * Author: Alexey
 * 
 * Created on 1 ноября 2016 г., 18:17
 */

#include "emitsignalluaevent.h"

EmitSignalLuaEvent::~EmitSignalLuaEvent()
{
}

EmitSignalLuaEvent::EmitSignalLuaEvent(const string& signalName) :
    mSignalName(signalName)
{

}

ILuaEvent::EventType EmitSignalLuaEvent::eventType() const
{
    return EventType::EmitSignal;
}

const string EmitSignalLuaEvent::signalName() const
{
    return mSignalName;
}


