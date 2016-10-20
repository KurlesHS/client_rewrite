/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutgoingMessageLuaEvent.h
 * Author: Alexey
 *
 * Created on 20 октября 2016 г., 1:06
 */

#ifndef OUTGOINGMESSAGELUAEVENT_H
#define OUTGOINGMESSAGELUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;
class OutgoingMessageLuaEvent : public ILuaEvent
{
public:
    OutgoingMessageLuaEvent(const string &hardwareId, const string &message);
    virtual ~OutgoingMessageLuaEvent();
    ILuaEvent::EventType eventType() const override;

    const string hardwareId() const;

    const string message() const;
 
private:
    const string mHardwareId;
    const string mMessage;

};

#endif /* OUTGOINGMESSAGELUAEVENT_H */

