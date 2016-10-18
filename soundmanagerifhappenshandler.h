/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   audiofilenotfoundifhappenshandler.h
 * Author: kurles
 *
 * Created on 18 октября 2016 г., 10:42
 */

#ifndef AUDIOFILENOTFOUNDIFHAPPENSHANDLER_H
#define AUDIOFILENOTFOUNDIFHAPPENSHANDLER_H

#include "lua/iluaeventforifhappenshandler.h"

#include "sol2/sol2.hpp"
#include "isoundmanagereventslistener.h"

#include <list>
#include <string>

using namespace std;

struct SoundManagerIfHappensHandlerData {
    string ifHappensId;
    bool hasPlaybackId;
    string playbackId;
    bool hasIsCanceled;
    bool isCanceled;
};

class SoundManagerIfHappensHandler : public ILuaEventForIfHappensHandler,
        public ISoundManagerEventsListener
{
public:
    SoundManagerIfHappensHandler();
    virtual ~SoundManagerIfHappensHandler();
    
    void ifHappensExpiried(const string& ifHappensId) override;
    void registerCommand(sol::state& state) override;
    
    void fileNotFound(const string& playbackId) override;
    void playbackFinished(const string& playbackId, const bool isCanceled) override;
    void playbackStarted(const string& playbackId) override;

private:
    string notFoundFuncImpl(const sol::object &playbackId);
    string playbackFinishedFuncImpl(const sol::object& playbackId, const sol::object &isCanceled);
    string playbackStartedFuncImpl(const sol::object& playbackId);
    
private:
    list<SoundManagerIfHappensHandlerData> mFileNotFoundPendingEvents;
    list<SoundManagerIfHappensHandlerData> mPlaybackStartedPendingEvents;
    list<SoundManagerIfHappensHandlerData> mPlaybackFinishedPendingEvents;
    
    
    
    

};

#endif /* AUDIOFILENOTFOUNDIFHAPPENSHANDLER_H */

