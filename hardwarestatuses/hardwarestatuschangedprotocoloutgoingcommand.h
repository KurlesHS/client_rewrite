/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusChangedProtocolOutgoingCommand.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 19:37
 */

#ifndef HARDWARESTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H
#define HARDWARESTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H

#include "protocol/iprotocoloutgoingcommand.h"
#include "ihardwarestatusesevents.h"

#include <string>

using namespace std;

class HardwareStatusChangedProtocolOutgoingCommand : public IProtocolOutgoingCommand {
public:
    HardwareStatusChangedProtocolOutgoingCommand(const string &hardwareId, const IHardwareStatusesEvents::HardwareStatus &status);
    virtual ~HardwareStatusChangedProtocolOutgoingCommand();    
    vector<char> payload() const override;    
    
    void doWork(const vector<char>& payload) override;

    uint16_t command() const override;
    
    void doWorkOnError() override;

private:
    const string mHardwareId;
    const IHardwareStatusesEvents::HardwareStatus mStatus;
};

#endif /* HARDWARESTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H */

