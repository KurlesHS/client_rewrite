/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SetHardwareStatusesLuaEvent.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 16:27
 */

#ifndef SETHARDWARESTATUSESLUAEVENT_H
#define SETHARDWARESTATUSESLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class SetHardwareStatusesLuaEvent : public ILuaEvent
{
public:
    SetHardwareStatusesLuaEvent(const ILuaEvent::EventType &type, const string &hardwareId);
    virtual ~SetHardwareStatusesLuaEvent();
    
    ILuaEvent::EventType eventType() const override;
    
    string hardwareId() const;
    
private:
    const ILuaEvent::EventType mType;
    const string mHardwareId;

};

#endif /* SETHARDWARESTATUSESLUAEVENT_H */

