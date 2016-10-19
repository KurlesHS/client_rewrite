/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iluaevent.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 8:42
 */

#ifndef ILUAEVENT_H
#define ILUAEVENT_H

#include <memory>

class ILuaEvent;

using ILuaEventSharedPtr = std::shared_ptr<ILuaEvent>;

class ILuaEvent
{
public:

    enum class EventType
    {
        FinishScript,
        LogMessage,
        PlayNetworkAudioRequest,
        StopNetworkAudioRequest,
        PlayLocalFileByHashRequest,
        PlayLocalFileByPathRequest,
        StopLocalAudioRequest,
        setHardwareStatusWorking,
        SetHardwareStatusError,
        SetHardwareStatusUnknown,
        SetNotifyStatusProcess,
        SetNotifyStatusWait,
        SetNotifyStatusError,
        SetNotifyStatusUnknown

    };

    virtual ~ILuaEvent()
    {
    }

    virtual EventType eventType() const = 0;

private:

};

#endif /* ILUAEVENT_H */

