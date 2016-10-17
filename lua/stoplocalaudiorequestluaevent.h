/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stoplocalaudiorequestluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 9:45
 */

#ifndef STOPLOCALAUDIOREQUESTLUAEVENT_H
#define STOPLOCALAUDIOREQUESTLUAEVENT_H

#include <string>

#include "iluaevent.h"

using namespace std;

class StopLocalAudioRequestLuaEvent : public ILuaEvent {
public:
    StopLocalAudioRequestLuaEvent(const string &id);
    virtual ~StopLocalAudioRequestLuaEvent();
    
    string id() const;
    
    ILuaEvent::EventType eventType() const override;

    
private:
    const string mId;

};

#endif /* STOPLOCALAUDIOREQUESTLUAEVENT_H */

