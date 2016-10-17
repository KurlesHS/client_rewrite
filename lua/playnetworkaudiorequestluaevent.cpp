/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   playnetworkaudiorequestluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 10:00
 */

#include "playnetworkaudiorequestluaevent.h"

PlayNetworkAudioRequestLuaEvent::~PlayNetworkAudioRequestLuaEvent()
{
}

PlayNetworkAudioRequestLuaEvent::PlayNetworkAudioRequestLuaEvent(const string& url) :
    mUrl(url)
{

}

ILuaEvent::EventType PlayNetworkAudioRequestLuaEvent::eventType() const
{
    return ILuaEvent::EventType::PlayNetworkAudioRequest;
}

string PlayNetworkAudioRequestLuaEvent::url() const
{
    return mUrl;
}


