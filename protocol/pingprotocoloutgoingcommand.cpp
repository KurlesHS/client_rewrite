/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PingProtocolOutgoingCommand.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 23:11
 */

#include "pingprotocoloutgoingcommand.h"
#include "ioc/resolver.h"
#include "hardwareprotocol.h"

PingProtocolOutgoingCommand::PingProtocolOutgoingCommand(HardwareProtocol* protocol) :
    mHardwareProtocol(protocol)
{
    mTimer = di_inject(ITimerFactory)->getTimer(10000);
    mTimer->setSingleShot(true);
    mTimer->addCallbackFunction([this](ITimer *) {
        onTimeout();
    });
}

void PingProtocolOutgoingCommand::onTimeout()
{
    mHardwareProtocol->disconnectFromClient();
}

PingProtocolOutgoingCommand::~PingProtocolOutgoingCommand()
{
    
}

uint16_t PingProtocolOutgoingCommand::command() const
{
    return 0x0002;
}

void PingProtocolOutgoingCommand::doWork(const vector<char>& payload)
{
    
    (void) payload;
}

vector<char> PingProtocolOutgoingCommand::payload() const
{
    mTimer->start();
    return vector<char>();
}

