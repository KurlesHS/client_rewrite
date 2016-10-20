/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StartNotifyProtocolOutgoingCommand.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 21:41
 */

#include "startscriptprotocoloutgoingcommand.h"

#include "json/json.hpp"

using json = nlohmann::json;

StartScriptProtocolOutgoingCommand::StartScriptProtocolOutgoingCommand(const string& notifyId, const string& notifyCode, const string& scriptName) :
    mNotifyId(notifyId),
    mNotifyCode(notifyCode),
    mScriptName(scriptName)
{

}

StartScriptProtocolOutgoingCommand::~StartScriptProtocolOutgoingCommand()
{
}

uint16_t StartScriptProtocolOutgoingCommand::command() const
{
    return 0x0100;
}

void StartScriptProtocolOutgoingCommand::doWork(const vector<char>& payload)
{
    (void) payload;
}

vector<char> StartScriptProtocolOutgoingCommand::payload() const
{
    json j;
    j["id"] = mNotifyId;
    j["code"] = mNotifyCode;
    j["script"] = mScriptName;
    auto res = j.dump(2);
    return vector<char>(res.begin(), res.end());
}


