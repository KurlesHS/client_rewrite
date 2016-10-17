/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logmessageluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 9:29
 */

#ifndef LOGMESSAGELUAEVENT_H
#define LOGMESSAGELUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;


class LogMessageLuaEvent : public ILuaEvent {
public:
    LogMessageLuaEvent(const string &message);
    virtual ~LogMessageLuaEvent();
    
    string message() const;
    ILuaEvent::EventType eventType() const override;

    
private:
    const string mMessage;

};

#endif /* LOGMESSAGELUAEVENT_H */

