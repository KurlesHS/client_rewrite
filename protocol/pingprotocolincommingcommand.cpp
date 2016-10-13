/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pingprotocolincommingcommand.cpp
 * Author: Alexey
 * 
 * Created on 12 октября 2016 г., 23:50
 */

#include "pingprotocolincommingcommand.h"

PingProtocolIncommingCommand::PingProtocolIncommingCommand()
{
}

PingProtocolIncommingCommand::~PingProtocolIncommingCommand()
{
}

void PingProtocolIncommingCommand::doWork(const vector<char>& payload)
{
    /* ничего не надо делать */
    (void)payload;    
}

vector<char> PingProtocolIncommingCommand::payload() const
{
    /* отклик посылаем пустой */
    return vector<char>();
}