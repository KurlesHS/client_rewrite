/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScriptStartedLuaEvent.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 21:19
 */

#ifndef SCRIPTSTARTEDLUAEVENT_H
#define SCRIPTSTARTEDLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class ScriptStartedLuaEvent : public ILuaEvent {
public:
    ScriptStartedLuaEvent(const string &notifyId,
            const string &notifyCode,
            const string &scriptName);
    virtual ~ScriptStartedLuaEvent();

    ILuaEvent::EventType eventType() const override;
    
    string notifyId() const;
    string notifyCode() const;
    string scriptName() const;


private:
    const string mNotifyId;
    const string mNotifyCode;
    const string mScriptName;
};

#endif /* SCRIPTSTARTEDLUAEVENT_H */

