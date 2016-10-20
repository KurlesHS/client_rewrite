/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScriptStartedLuaEvent.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 21:19
 */

#include "scriptstartedluaevent.h"

ScriptStartedLuaEvent::~ScriptStartedLuaEvent()
{
}

ILuaEvent::EventType ScriptStartedLuaEvent::eventType() const
{
    return ILuaEvent::EventType::StartScript;
}

ScriptStartedLuaEvent::ScriptStartedLuaEvent(
        const string& notifyId,
        const string& notifyCode,
        const string& scriptName) :
    mNotifyId(notifyId),
    mNotifyCode(notifyCode),
    mScriptName(scriptName)
{

}

string ScriptStartedLuaEvent::notifyCode() const
{
    return mNotifyCode;
}

string ScriptStartedLuaEvent::notifyId() const
{
    return mNotifyId;
}

string ScriptStartedLuaEvent::scriptName() const
{
    return mScriptName;
}
