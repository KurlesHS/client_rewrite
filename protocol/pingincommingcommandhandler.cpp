/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pingincommingcommandhandler.cpp
 * Author: Alexey
 * 
 * Created on 15 октября 2016 г., 14:06
 */

#include "pingincommingcommandhandler.h"

PingIncommingCommandHandler::PingIncommingCommandHandler()
{
}

PingIncommingCommandHandler::~PingIncommingCommandHandler()
{
}

uint16_t PingIncommingCommandHandler::command() const
{
    return 0x0002;
}

bool PingIncommingCommandHandler::handleCommand(const vector<char>& payload)
{
    (void) payload;
    return true;
}

