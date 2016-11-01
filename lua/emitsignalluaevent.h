/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EmitSignalLuaEvent.h
 * Author: Alexey
 *
 * Created on 1 ноября 2016 г., 18:17
 */

#ifndef EMITSIGNALLUAEVENT_H
#define EMITSIGNALLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class EmitSignalLuaEvent : public ILuaEvent {
public:
    EmitSignalLuaEvent(const string &signalName);    
    virtual ~EmitSignalLuaEvent();
    ILuaEvent::EventType eventType() const override;
    
    const string signalName() const;


private:
    const string mSignalName;

};

#endif /* EMITSIGNALLUAEVENT_H */

