/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RequestHardwareStatusesIncommingCommandHandler.cpp
 * Author: Alexey
 * 
 * Created on 20 октября 2016 г., 0:39
 */

#include "requesthardwarestatusesincommingcommandhandler.h"
#include "hardwarestatusesmanager.h"
#include "protocol/hardwareprotocolfactory.h"
#include "hardwarestatuschangedprotocoloutgoingcommand.h"
#include "logger.h"
#include "networkaudio/notifystatuschangedprotocoloutgoingcommand.h"

RequestHardwareStatusesIncommingCommandHandler::RequestHardwareStatusesIncommingCommandHandler(HardwareProtocolFactory* protocolFactory, HardwareStatusesManager* statusesManager) :
    mProtocolFactory(protocolFactory),
    mStatusesManager(statusesManager)
{

}

RequestHardwareStatusesIncommingCommandHandler::~RequestHardwareStatusesIncommingCommandHandler()
{
}

uint16_t RequestHardwareStatusesIncommingCommandHandler::command() const
{
    return 0x0200;
}

bool RequestHardwareStatusesIncommingCommandHandler::handleCommand(const vector<char>& payload)
{
    (void) payload;
    Logger::msg("received request hardware info command, start broadcast info...");
    auto hs = mStatusesManager->hardwares();
    for (auto hardwareId : hs) {        
        auto cmd = make_shared<HardwareStatusChangedProtocolOutgoingCommand>
                (hardwareId, mStatusesManager->hardwareStatus(hardwareId));
        mProtocolFactory->sendCommand(cmd);
    }
    
    for (auto hardwareId : hs) {        
        auto cmd = make_shared<NotifyStatusChangedProtocolOutgoingCommand>
                (hardwareId, mStatusesManager->notifyStatus(hardwareId));
        mProtocolFactory->sendCommand(cmd);
    }
    
    return true;
}
