/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FinishScriptProtocolOutgoingCommand.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 21:53
 */
#include "finishscriptprotocoloutgoingcommand.h"

#include "json/json.hpp"

using json = nlohmann::json;

FinishScriptProtocolOutgoingCommand::~FinishScriptProtocolOutgoingCommand()
{
}

FinishScriptProtocolOutgoingCommand::FinishScriptProtocolOutgoingCommand(const string& notifyId, const string& scriptName, const FinishReason reason) :
    mNotifyId(notifyId),
    mScriptName(scriptName),
    mReason(reason)
{

}

uint16_t FinishScriptProtocolOutgoingCommand::command() const
{
    return 0x0101;
}

void FinishScriptProtocolOutgoingCommand::doWork(const vector<char>& payload)
{
    (void) payload;
}

vector<char> FinishScriptProtocolOutgoingCommand::payload() const
{
    string reason;

    switch (mReason) {
        case FinishReason::Canceled:
            reason = "cancel";
            break;
        case FinishReason::Error:
            reason = "error";
            break;
        case FinishReason::Normal:
            reason = "normal";
            break;
    }
    json j;
    j["id"] = mNotifyId;
    j["script"] = mScriptName;
    j["reason"] = reason;
    
    auto res = j.dump(2);
    return vector<char>(res.begin(), res.end());
}

