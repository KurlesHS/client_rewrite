/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logmessageluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 9:29
 */

#include "logmessageluaevent.h"

LogMessageLuaEvent::LogMessageLuaEvent(const string& message) :
    mMessage(message)
{

}

string LogMessageLuaEvent::message() const
{
    return mMessage;
}

LogMessageLuaEvent::~LogMessageLuaEvent()
{
}

ILuaEvent::EventType LogMessageLuaEvent::eventType() const
{
    return ILuaEvent::EventType::LogMessage;
}


