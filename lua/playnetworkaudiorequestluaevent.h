/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   playnetworkaudiorequestluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 10:00
 */

#ifndef PLAYNETWORKAUDIOREQUESTLUAEVENT_H
#define PLAYNETWORKAUDIOREQUESTLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class PlayNetworkAudioRequestLuaEvent : public ILuaEvent {
public:
    PlayNetworkAudioRequestLuaEvent(const string &url);
    virtual ~PlayNetworkAudioRequestLuaEvent();
    
    ILuaEvent::EventType eventType() const override;
    string url() const;

private:
    const string &mUrl;
};

#endif /* PLAYNETWORKAUDIOREQUESTLUAEVENT_H */

