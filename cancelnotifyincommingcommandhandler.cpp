/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cancelnotifyincommingcommand.cpp
 * Author: Alexey
 * 
 * Created on 17 октября 2016 г., 23:03
 */

#include "cancelnotifyincommingcommandhandler.h"

#include "logger.h"
#include "luatoprotocolmediator.h"

CancelNotifyIncommingCommandHandler::CancelNotifyIncommingCommandHandler(LuaToProtocolMediator* mediator) :
    mMediator(mediator)
{

}

CancelNotifyIncommingCommandHandler::~CancelNotifyIncommingCommandHandler()
{
}

uint16_t CancelNotifyIncommingCommandHandler::command() const
{
    return 0x0101;
}

bool CancelNotifyIncommingCommandHandler::handleCommand(const vector<char>& payload)
{
    string notifyId(payload.begin(), payload.end());
    Logger::msg("received cancel notify incomming command with notify id '%s'", notifyId.data());    
    mMediator->cancelNotifyRequest(notifyId);
    return true;
}

