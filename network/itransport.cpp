/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "itransport.h"
#include "safe_list.h"

void ITransport::addTransportEventsListener(ITransportEvents* listener)
{
    mEventListeners.emplace_back(listener);
}

void ITransport::removeTransportEventsListener(ITransportEvents* listener)
{
    mEventListeners.safe_remove(listener);
}

ITransport::~ITransport()
{
}

ITransportEvents::~ITransportEvents()
{
}

void ITransport::emit_disonnected()
{
    mEventListeners.call_member_func(&ITransportEvents::disconnected, this);    
}

void ITransport::emit_readyRead()
{
    mEventListeners.call_member_func(&ITransportEvents::readyRead, this);  
}



