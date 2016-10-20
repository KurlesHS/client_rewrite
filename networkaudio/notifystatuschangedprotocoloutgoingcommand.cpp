/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotifyStatusChangedProtocolOutgoingCommand.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 20:18
 */

#include "notifystatuschangedprotocoloutgoingcommand.h"

#include "json/json.hpp"

using json = nlohmann::json;

NotifyStatusChangedProtocolOutgoingCommand::NotifyStatusChangedProtocolOutgoingCommand(const string &hardwareId, const IHardwareStatusesEvents::NotifyStatus &status) :
    mHardwareId(hardwareId),
    mStatus(status)
{
}

NotifyStatusChangedProtocolOutgoingCommand::~NotifyStatusChangedProtocolOutgoingCommand()
{
}

uint16_t NotifyStatusChangedProtocolOutgoingCommand::command() const
{
    return 0x1001;
}

void NotifyStatusChangedProtocolOutgoingCommand::doWork(const vector<char>& payload)
{

}

vector<char> NotifyStatusChangedProtocolOutgoingCommand::payload() const
{
    string status = "unknown";
    switch (mStatus) {
        case IHardwareStatusesEvents::NotifyStatus::Wait:
            status = "wait";
            break;
        case IHardwareStatusesEvents::NotifyStatus::Process:
            status = "process";
            break;
        case IHardwareStatusesEvents::NotifyStatus::Error:
            status = "error";
            break;
        case IHardwareStatusesEvents::NotifyStatus::Unknown:
            status = "unknown";
            break;
    }
    json j;
    j["status"] = status;
    j["id"] = mHardwareId;
    auto res = j.dump(2);
    return vector<char>(res.begin(), res.end());
}

