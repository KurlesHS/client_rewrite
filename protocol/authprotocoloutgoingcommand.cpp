/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   authprotocoloutgoingcommand.cpp
 * Author: Alexey
 * 
 * Created on 13 октября 2016 г., 0:56
 */

#include "authprotocoloutgoingcommand.h"
#include "hardwareprotocol.h"

#include "logger.h"

AuthProtocolOutgoingCommand::AuthProtocolOutgoingCommand(
        HardwareProtocol *protocol, const string &sessionId) :
    mProtocol(protocol),
    mSessionId(sessionId)
{
}

AuthProtocolOutgoingCommand::~AuthProtocolOutgoingCommand()
{
}

uint16_t AuthProtocolOutgoingCommand::command() const
{
    return 0x0001;
}

void AuthProtocolOutgoingCommand::doWork(const vector<char>& payload)
{
    string userName(payload.begin(), payload.end());
    mProtocol->setUserName(userName);
}

bool AuthProtocolOutgoingCommand::doWorkAfterAuth() const
{
    return false;
}

vector<char> AuthProtocolOutgoingCommand::payload() const
{
    return vector<char>(mSessionId.begin(), mSessionId.end());
}
