/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stoplocalaudiorequestluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 9:45
 */

#include "stoplocalaudiorequestluaevent.h"

StopLocalAudioRequestLuaEvent::StopLocalAudioRequestLuaEvent(const string& id) :
    mId(id)
{

}

StopLocalAudioRequestLuaEvent::~StopLocalAudioRequestLuaEvent()
{
}

string StopLocalAudioRequestLuaEvent::id() const
{
    return mId;
}

ILuaEvent::EventType StopLocalAudioRequestLuaEvent::eventType() const
{
    return ILuaEvent::EventType::StopLocalAudioRequest;
}

