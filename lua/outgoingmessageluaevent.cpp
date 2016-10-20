/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutgoingMessageLuaEvent.cpp
 * Author: Alexey
 * 
 * Created on 20 октября 2016 г., 1:06
 */

#include "outgoingmessageluaevent.h"

OutgoingMessageLuaEvent::~OutgoingMessageLuaEvent()
{
}

OutgoingMessageLuaEvent::OutgoingMessageLuaEvent(const string& hardwareId, const string& message) :
    mHardwareId(hardwareId),
    mMessage(message)
{

}

ILuaEvent::EventType OutgoingMessageLuaEvent::eventType() const
{
    return ILuaEvent::EventType::OutgoingMessage;
}

const string OutgoingMessageLuaEvent::hardwareId() const
{
    return mHardwareId;
}

const string OutgoingMessageLuaEvent::message() const
{
    return mMessage;
}
