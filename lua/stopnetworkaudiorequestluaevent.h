/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stopnetworkaudiorequestluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 10:07
 */

#ifndef STOPNETWORKAUDIOREQUESTLUAEVENT_H
#define STOPNETWORKAUDIOREQUESTLUAEVENT_H

#include "iluaevent.h"


class StopNetworkAudioRequestLuaEvent : public ILuaEvent{
public:
    StopNetworkAudioRequestLuaEvent();
    virtual ~StopNetworkAudioRequestLuaEvent();
    
    ILuaEvent::EventType eventType() const override;

private:

};

#endif /* STOPNETWORKAUDIOREQUESTLUAEVENT_H */

