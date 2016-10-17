/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   playlocalfilerequestluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 9:33
 */

#ifndef PLAYLOCALFILEREQUESTLUAEVENT_H
#define PLAYLOCALFILEREQUESTLUAEVENT_H

#include "iluaevent.h"

#include <string>

using namespace std;

class PlayLocalFileRequestLuaEvent : public ILuaEvent{
public:
    enum class Type {
        ByHash,
        ByPath
    };
    PlayLocalFileRequestLuaEvent(const Type &type, const string &id,  const string &value);    
    virtual ~PlayLocalFileRequestLuaEvent();
    
    ILuaEvent::EventType eventType() const override;
    Type type() const;
    string value() const;
    string id() const;

private:
    const Type mType;
    const string mId;
    const string mValue;

};

#endif /* PLAYLOCALFILEREQUESTLUAEVENT_H */

