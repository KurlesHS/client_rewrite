/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luatonetworkstreammediator.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 14:29
 */

#include "luatonetworkstreammediator.h"
#include "lua/playnetworkaudiorequestluaevent.h"
#include "networkaudio/networkaudiomanager.h"
#include "lua/stopnetworkaudiorequestluaevent.h"
#include "logger.h"
#include "lua/luascriptmanager.h"

LuaToNetworkStreamMediator::LuaToNetworkStreamMediator(LuaScriptManager *luaManager, NetworkAudioManager *networkAudioManager) :
    mLuaManager(luaManager),
    mNetworkAudioManager(networkAudioManager)
{
    mLuaManager->addLuaScriptEventListener(this);
    mNetworkAudioManager->addEventListener(this);
    mLuaManager->addIfHappensHandler(&mIfHappensHandler);
}

LuaToNetworkStreamMediator::~LuaToNetworkStreamMediator()
{
}

void LuaToNetworkStreamMediator::luaEvent(ILuaEventSharedPtr event)
{
    switch (event->eventType()) {
        case ILuaEvent::EventType::PlayNetworkAudioRequest:
            handlePlayNetworkAudioRequest(event);
            break;
        case ILuaEvent::EventType::StopNetworkAudioRequest:
            handleStopNetworkAudioRequest(event);
            break;
        default:
            break;
    }
}

void LuaToNetworkStreamMediator::handlePlayNetworkAudioRequest(ILuaEventSharedPtr event)
{
    auto req = static_cast<PlayNetworkAudioRequestLuaEvent*> (event.get());
    if (req) {
        mNetworkAudioManager->startStream(req->url());
    }
}

void LuaToNetworkStreamMediator::handleStopNetworkAudioRequest(ILuaEventSharedPtr event)
{
    auto req = static_cast<StopNetworkAudioRequestLuaEvent*> (event.get());
    if (req) {
        mNetworkAudioManager->stopStream();
    }
}

void LuaToNetworkStreamMediator::onFailToStartNetworkStream()
{
    Logger::msg("fail to start network audio lua event");
    mIfHappensHandler.onNetworkAudioFailedToStart();
}

void LuaToNetworkStreamMediator::onFinishNetworkStream()
{
    Logger::msg("finish network audio lua event");
    mIfHappensHandler.onNetworkAudioPlaybackFinished();
}

void LuaToNetworkStreamMediator::onStartNetworkStream()
{
    Logger::msg("start network audio lua event");
    mIfHappensHandler.onNetworkAudioPlaybackStarted();
}

