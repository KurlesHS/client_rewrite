/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "itransport.h"

void ITransport::addTransportEventsListener(ITransportEvents* listener)
{
    mEventListeners.emplace_back(listener);
}

void ITransport::removeTransportEventsListener(ITransportEvents* listener)
{
    mEventListeners.remove(listener);
}

ITransport::~ITransport()
{
}

ITransportEvents::~ITransportEvents()
{
}

void ITransport::emit_disonnected()
{
    auto copyOfListeners = mEventListeners;
    for (const auto listener : copyOfListeners) {
        listener->disconnected(this);
    }
}

void ITransport::emit_readyRead()
{
    auto copyOfListeners = mEventListeners;
    for (const auto listener : copyOfListeners) {
        listener->readyRead(this);
    }
}



