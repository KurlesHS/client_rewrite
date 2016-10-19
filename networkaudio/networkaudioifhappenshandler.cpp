/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudioifhappenshandler.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 14:41
 */

#include "networkaudioifhappenshandler.h"
#include "uuid.h"
#include "lua/iluaeventforifhappenshandler.h"

NetworkAudioIfHappensHandler::NetworkAudioIfHappensHandler()
{
}

NetworkAudioIfHappensHandler::~NetworkAudioIfHappensHandler()
{
}

void NetworkAudioIfHappensHandler::ifHappensExpiried(const string& ifHappensId)
{
    mFailedPendingEvents.remove(ifHappensId);
    mStartedPendingEvents.remove(ifHappensId);
    mFinishedPendingEvents.remove(ifHappensId);
}

void NetworkAudioIfHappensHandler::registerCommand(sol::state& state)
{
    auto x = this;
    state.set_function("network_audio_failed_to_start",
            &NetworkAudioIfHappensHandler::networkAudioFailedToStart, x);
    state.set_function("network_audio_playback_finished",
            &NetworkAudioIfHappensHandler::networkAudioPlaybackFinished, x);
    state.set_function("network_audio_playback_started",
            &NetworkAudioIfHappensHandler::networkAudioPlaybackStarted, x);
}

string NetworkAudioIfHappensHandler::networkAudioFailedToStart()
{
    auto ifHappensId = Uuid::createUuid().toString();
    mFailedPendingEvents.push_back(ifHappensId);
    return ifHappensId;
}

string NetworkAudioIfHappensHandler::networkAudioPlaybackFinished()
{
    auto ifHappensId = Uuid::createUuid().toString();
    mFinishedPendingEvents.push_back(ifHappensId);
    return ifHappensId;
}

string NetworkAudioIfHappensHandler::networkAudioPlaybackStarted()
{
    auto ifHappensId = Uuid::createUuid().toString();
    mStartedPendingEvents.push_back(ifHappensId);
    return ifHappensId;
}

void NetworkAudioIfHappensHandler::onNetworkAudioFailedToStart()
{
    decltype(mFailedPendingEvents) copy;
    copy.swap(mFailedPendingEvents);
    for (auto ifHappensId : copy) {
        ifHappensHappened(ifHappensId);
    }
}

void NetworkAudioIfHappensHandler::onNetworkAudioPlaybackFinished()
{
    decltype(mFinishedPendingEvents) copy;
    copy.swap(mFinishedPendingEvents);
    for (auto ifHappensId : copy) {
        ifHappensHappened(ifHappensId);
    }
}

void NetworkAudioIfHappensHandler::onNetworkAudioPlaybackStarted()
{
    decltype(mStartedPendingEvents) copy;    
    copy.swap(mStartedPendingEvents);
    for (auto ifHappensId : copy) {
        ifHappensHappened(ifHappensId);
    }
}

