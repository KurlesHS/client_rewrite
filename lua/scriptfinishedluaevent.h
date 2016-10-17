/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scriptfinishedluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 9:11
 */

#ifndef SCRIPTFINISHEDLUAEVENT_H
#define SCRIPTFINISHEDLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class ScriptFinishedLuaEvent : public ILuaEvent{
public:
    ScriptFinishedLuaEvent(const string &scriptId);

    virtual ~ScriptFinishedLuaEvent();
    
    ILuaEvent::EventType eventType() const override;
    
    string scriptId() const;

private:
    string mScriptId;

};

#endif /* SCRIPTFINISHEDLUAEVENT_H */

