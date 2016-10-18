/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luatoaudiomediator.cpp
 * Author: Alexey
 * 
 * Created on 17 октября 2016 г., 23:59
 */

#include "luatoaudiomediator.h"
#include "auth/authmanager.h"
#include "lua/luascriptmanager.h"
#include "soundmanager.h"
#include "lua/playlocalfilerequestluaevent.h"
#include "lua/stoplocalaudiorequestluaevent.h"

LuaToAudioMediator::~LuaToAudioMediator()
{
}

LuaToAudioMediator::LuaToAudioMediator(LuaScriptManager* luaManager, SoundManager* soundManager) :
    mLuaManager(luaManager),
    mSoundManager(soundManager)
{
    mLuaManager->addLuaScriptEventListener(this);
    mSoundManager->addEventListener(this);
    mLuaManager->addIfHappensHandler(&mIfHappensHandler);
}

void LuaToAudioMediator::luaEvent(ILuaEventSharedPtr event)
{
    using ET = ILuaEvent::EventType;
    switch (event->eventType()) {
        case ET::PlayLocalFileByHashRequest:
        case ET::PlayLocalFileByPathRequest:
            handlePlayFileEvent(event);
            break;
        case ET::StopLocalAudioRequest:
            handleStopLocalAudioEvent(event);
            break;
        default:
            break;
    }
}

void LuaToAudioMediator::fileNotFound(const string& playbackId)
{
    mIfHappensHandler.fileNotFound(playbackId);
}

void LuaToAudioMediator::playbackFinished(const string& playbackId, const bool isCanceled)
{
    mIfHappensHandler.playbackFinished(playbackId, isCanceled);
}

void LuaToAudioMediator::playbackStarted(const string& playbackId)
{
    mIfHappensHandler.playbackStarted(playbackId);
}

void LuaToAudioMediator::handlePlayFileEvent(ILuaEventSharedPtr event)
{
    auto playEvent = static_cast<PlayLocalFileRequestLuaEvent*> (event.get());
    switch (playEvent->type()) {
        case PlayLocalFileRequestLuaEvent::Type::ByHash:
            mSoundManager->playbackByHash(playEvent->value(), playEvent->id());
            break;
        case PlayLocalFileRequestLuaEvent::Type::ByPath:
            mSoundManager->playbackByFilePath(playEvent->value(), playEvent->id());
            break;
    } 
}

void LuaToAudioMediator::handleStopLocalAudioEvent(ILuaEventSharedPtr event)
{
    auto stopEvent = static_cast<StopLocalAudioRequestLuaEvent*> (event.get());
    mSoundManager->cancelPlaybackFile(stopEvent->id());
}
