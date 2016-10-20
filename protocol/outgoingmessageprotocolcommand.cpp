/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutgoingMessageProtocolCommand.cpp
 * Author: Alexey
 * 
 * Created on 20 октября 2016 г., 1:14
 */

#include "outgoingmessageprotocolcommand.h"

#include "json/json.hpp"

using json = nlohmann::json;

OutgoingMessageProtocolCommand::OutgoingMessageProtocolCommand(const string& hardwareId, const string& message) :
    mHardwareId(hardwareId),
    mMessage(message)
{

}

uint16_t OutgoingMessageProtocolCommand::command() const
{
    return 0x1002;
}

void OutgoingMessageProtocolCommand::doWork(const vector<char>& payload)
{
    (void) payload;
}

vector<char> OutgoingMessageProtocolCommand::payload() const
{
    json j;
    j["id"] = mHardwareId;
    j["message"] = mMessage;
    
    auto res = j.dump(2);
    return vector<char>(res.begin(), res.end());
}

OutgoingMessageProtocolCommand::~OutgoingMessageProtocolCommand()
{
}

