/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EmitSignalIfHappensHandler.cpp
 * Author: Alexey
 * 
 * Created on 1 ноября 2016 г., 19:43
 */

#include "emitsignalifhappenshandler.h"
#include "emitsignalluaevent.h"
#include "uuid.h"
#include "logger.h"

EmitSignalIfHappensHandler::EmitSignalIfHappensHandler()
{
}

EmitSignalIfHappensHandler::~EmitSignalIfHappensHandler()
{
}

void EmitSignalIfHappensHandler::ifHappensExpiried(const string& ifHappensId)
{
    mPendingEvents.remove_if([ifHappensId](const Holder holder) {
        return ifHappensId == holder.ifHappensId;
    });
}

void EmitSignalIfHappensHandler::registerCommand(sol::state& state)
{
    auto x = this;
    state.set_function("signal", &EmitSignalIfHappensHandler::signalFuncImpl, x);
}

string EmitSignalIfHappensHandler::signalFuncImpl(const sol::object& signalName)
{
    Holder h;
    h.ifHappensId = Uuid::createUuid().toString();
    h.hasSignalName = signalName.is<string>();
    if (h.hasSignalName) {
        h.signalName = signalName.as<string>();
    }
    mPendingEvents.push_back(h);
    return h.ifHappensId;
}

void EmitSignalIfHappensHandler::incommingSignal(const string& signalName)
{
    auto &lst = mPendingEvents;
    list<string> happened;
    for (auto it = lst.begin(); it != lst.end();) {
        
        bool signalIsSame = true;
        if (it->hasSignalName) {
            signalIsSame = it->signalName == signalName;
        }
        
        if (signalIsSame) {
            auto ifHappensId = it->ifHappensId;
            it = lst.erase(it);
            happened.push_back(ifHappensId);
            continue;
        }
        ++it;
    }

    for (const auto &id : happened) {
        ifHappensHappened(id, signalName);
    }
}

void EmitSignalIfHappensHandler::luaEvent(ILuaEventSharedPtr event)
{
    if (event->eventType() == ILuaEvent::EventType::EmitSignal) {
        auto signalEvent = dynamic_cast<EmitSignalLuaEvent*>(event.get());
        if (signalEvent) {
            incommingSignal(signalEvent->signalName());
            Logger::msg("incomming signal: '%s'", signalEvent->signalName().data());
        }
        
    }
}




