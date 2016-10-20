/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusChangedProtocolOutgoingCommand.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 19:37
 */

#include "hardwarestatuschangedprotocoloutgoingcommand.h"

#include "json/json.hpp"

using json = nlohmann::json;

HardwareStatusChangedProtocolOutgoingCommand::HardwareStatusChangedProtocolOutgoingCommand(const string &hardwareId, const IHardwareStatusesEvents::HardwareStatus &status) :
    mHardwareId(hardwareId),
    mStatus(status)
{
}

HardwareStatusChangedProtocolOutgoingCommand::~HardwareStatusChangedProtocolOutgoingCommand()
{
}

void HardwareStatusChangedProtocolOutgoingCommand::doWork(const vector<char>& payload)
{
    (void) payload;
}

vector<char> HardwareStatusChangedProtocolOutgoingCommand::payload() const
{
    string status = "unknown";
    switch (mStatus) {
        case IHardwareStatusesEvents::HardwareStatus::Fail:
            status = "fail";
            break;
        case IHardwareStatusesEvents::HardwareStatus::Unknown:
            status = "unknown";
            break;
        case IHardwareStatusesEvents::HardwareStatus::Work:
            status = "work";
            break;
    }
    json j;
    j["status"] = status;
    j["id"] = mHardwareId;
    auto res = j.dump(2);
    return vector<char>(res.begin(), res.end());
}

uint16_t HardwareStatusChangedProtocolOutgoingCommand::command() const
{
    return 0x1000;
}

void HardwareStatusChangedProtocolOutgoingCommand::doWorkOnError()
{

}
