/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stopnetworkaudiorequestluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 10:07
 */

#include "stopnetworkaudiorequestluaevent.h"

StopNetworkAudioRequestLuaEvent::StopNetworkAudioRequestLuaEvent()
{
}

StopNetworkAudioRequestLuaEvent::~StopNetworkAudioRequestLuaEvent()
{
}

ILuaEvent::EventType StopNetworkAudioRequestLuaEvent::eventType() const
{
    return ILuaEvent::EventType::StopNetworkAudioRequest;
}


