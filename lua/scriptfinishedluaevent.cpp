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

ScriptFinishedLuaEvent::ScriptFinishedLuaEvent(const string& scriptId) :
mScriptId(scriptId)
{

}

ScriptFinishedLuaEvent::~ScriptFinishedLuaEvent() {
}

ILuaEvent::EventType ScriptFinishedLuaEvent::eventType() const {
    return ILuaEvent::EventType::FinishScript;
}

string ScriptFinishedLuaEvent::scriptId() const
{
    return mScriptId;
}



