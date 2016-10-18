/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   audiofilenotfoundifhappenshandler.cpp
 * Author: kurles
 * 
 * Created on 18 октября 2016 г., 10:42
 */

#include <iostream>

#include "soundmanagerifhappenshandler.h"
#include "uuid.h"

SoundManagerIfHappensHandler::SoundManagerIfHappensHandler()
{
}

SoundManagerIfHappensHandler::~SoundManagerIfHappensHandler()
{
}

void SoundManagerIfHappensHandler::fileNotFound(const string& playbackId)
{
    auto &lst = mFileNotFoundPendingEvents;
    for (auto it = lst.begin(); it != lst.end();) {
        if (it->hasPlaybackId) {
            if (it->playbackId == playbackId) {
                ifHappensHappened(it->ifHappensId, playbackId);
                it = lst.erase(it);
                continue;
            }
        } else {
            ifHappensHappened(it->ifHappensId, playbackId);
            it = lst.erase(it);
            continue;
        }
        ++it;
    }
}

void SoundManagerIfHappensHandler::ifHappensExpiried(const string& ifHappensId)
{
    auto deleter = [](decltype(mFileNotFoundPendingEvents) & lst, const string & id) {
        for (auto it = lst.begin(); it != lst.end();) {
            if (it->ifHappensId == id) {
                it = lst.erase(it);
            } else {
                ++it;
            }
        }
    };

    deleter(mFileNotFoundPendingEvents, ifHappensId);
    deleter(mPlaybackFinishedPendingEvents, ifHappensId);
    deleter(mPlaybackStartedPendingEvents, ifHappensId);
}

string SoundManagerIfHappensHandler::notFoundFuncImpl(const sol::object& playbackId)
{
    SoundManagerIfHappensHandlerData data;
    data.ifHappensId = Uuid::createUuid().toString();
    if (playbackId.is<string>()) {
        data.hasPlaybackId = true;
        data.playbackId = playbackId.as<string>();
    } else {
        data.hasPlaybackId = false;
    }
    mFileNotFoundPendingEvents.push_back(data);
    return data.ifHappensId;
}

void SoundManagerIfHappensHandler::playbackFinished(const string& playbackId, const bool isCanceled)
{
    auto &lst = mPlaybackFinishedPendingEvents;
    for (auto it = lst.begin(); it != lst.end();) {
        bool okPlaybackId = !it->hasPlaybackId;
        bool okCanceled = !it->hasIsCanceled;
        if (it->hasPlaybackId) {
            okPlaybackId = it->playbackId == playbackId;            
        } 
        if (it->hasIsCanceled) {
            okCanceled = it->isCanceled == isCanceled;
        }
        if (okCanceled && okPlaybackId) {
            ifHappensHappened(it->ifHappensId, playbackId, isCanceled);
            it = lst.erase(it);
        } else {
            ++it;
        }
    }
}

string SoundManagerIfHappensHandler::playbackFinishedFuncImpl(const sol::object& playbackId, const sol::object &isCanceled)
{
    SoundManagerIfHappensHandlerData data;
    data.ifHappensId = Uuid::createUuid().toString();
    if (playbackId.is<string>()) {
        data.hasPlaybackId = true;
        data.playbackId = playbackId.as<string>();
    } else {
        data.hasPlaybackId = false;
    }
    if (isCanceled.is<bool>()) {
        data.hasIsCanceled = true;
        data.isCanceled = isCanceled.as<bool>();
    } else {
        data.hasIsCanceled = false;
    }
    mPlaybackFinishedPendingEvents.push_back(data);
    return data.ifHappensId;
}

void SoundManagerIfHappensHandler::playbackStarted(const string& playbackId)
{
    auto &lst = mPlaybackStartedPendingEvents;
    for (auto it = lst.begin(); it != lst.end();) {
        if (it->hasPlaybackId) {
            if (it->playbackId == playbackId) {
                ifHappensHappened(it->ifHappensId, playbackId);
                it = lst.erase(it);
                continue;
            }
        } else {
            ifHappensHappened(it->ifHappensId, playbackId);
            it = lst.erase(it);
            continue;
        }
        ++it;
    }
}

string SoundManagerIfHappensHandler::playbackStartedFuncImpl(const sol::object& playbackId)
{
    SoundManagerIfHappensHandlerData data;
    data.ifHappensId = Uuid::createUuid().toString();
    if (playbackId.is<string>()) {
        data.hasPlaybackId = true;
        data.playbackId = playbackId.as<string>();
    } else {
        data.hasPlaybackId = false;
    }
    mPlaybackStartedPendingEvents.push_back(data);
    return data.ifHappensId;
}

void SoundManagerIfHappensHandler::registerCommand(sol::state& state)
{

    auto x = this;
    state.set_function("file_not_found",
            &SoundManagerIfHappensHandler::notFoundFuncImpl, x);
    state.set_function("playback_started",
            &SoundManagerIfHappensHandler::playbackStartedFuncImpl, x);
    state.set_function("playback_finished",
            &SoundManagerIfHappensHandler::playbackFinishedFuncImpl, x);
}
