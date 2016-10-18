/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luatoaudiomediator.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 23:59
 */

#ifndef LUATOAUDIOMEDIATOR_H
#define LUATOAUDIOMEDIATOR_H

#include "lua/iluascripteventlistener.h"
#include "isoundmanagereventslistener.h"
#include "soundmanagerifhappenshandler.h"

class SoundManager;
class LuaScriptManager;


class LuaToAudioMediator : public ILuaScriptEventsListener, public ISoundManagerEventsListener {
public:
    LuaToAudioMediator(LuaScriptManager *luaManager, SoundManager *soundManager);
    virtual ~LuaToAudioMediator();
    
    // ISoundManagerEventsListener
    void fileNotFound(const string& playbackId) override;
    void playbackFinished(const string& playbackId, const bool isCanceled) override;
    void playbackStarted(const string& playbackId) override;

    // ILuaScriptEventsListener
    void luaEvent(ILuaEventSharedPtr event) override;
    
private:
    void handleStopLocalAudioEvent(ILuaEventSharedPtr event);
    void handlePlayFileEvent(ILuaEventSharedPtr event);    
    
private:
    LuaScriptManager *mLuaManager;
    SoundManager *mSoundManager;
    SoundManagerIfHappensHandler mIfHappensHandler;

};

#endif /* LUATOAUDIOMEDIATOR_H */

