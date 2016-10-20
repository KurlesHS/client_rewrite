/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scriptfinishedluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 9:11
 */

#include "scriptfinishedluaevent.h"

ScriptFinishedLuaEvent::ScriptFinishedLuaEvent(
        const string &scriptId,
        const string &notifyId,
        const string &notifyCode,
        const string &scriptName,
        const bool isCanceled,
        const bool hasError) :
    mScriptId(scriptId),
    mNotifyId(notifyId),
    mNotifyCode(notifyCode),
    mScriptName(scriptName),
    mIsCanceled(isCanceled),
    mHasError(hasError)

{

}

bool ScriptFinishedLuaEvent::hasError() const
{
    return mHasError;
}

bool ScriptFinishedLuaEvent::isCanceled() const
{
    return mIsCanceled;
}

string ScriptFinishedLuaEvent::notifyCode() const
{
    return mNotifyCode;
}

string ScriptFinishedLuaEvent::scriptName() const
{
    return mScriptName;
}

string ScriptFinishedLuaEvent::scriptId() const
{
    return mScriptId;
}

ScriptFinishedLuaEvent::~ScriptFinishedLuaEvent()
{
}

ILuaEvent::EventType ScriptFinishedLuaEvent::eventType() const
{
    return ILuaEvent::EventType::FinishScript;
}

string ScriptFinishedLuaEvent::notifyId() const
{
    return mNotifyId;
}



