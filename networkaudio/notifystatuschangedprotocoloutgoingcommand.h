/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NotifyStatusChangedProtocolOutgoingCommand.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 20:18
 */

#ifndef NOTIFYSTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H
#define NOTIFYSTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H

#include "protocol/iprotocoloutgoingcommand.h"
#include "ihardwarestatusesevents.h"

#include <string>

using namespace std;


class NotifyStatusChangedProtocolOutgoingCommand : public IProtocolOutgoingCommand {
public:
    NotifyStatusChangedProtocolOutgoingCommand(const string &hardwareId, const IHardwareStatusesEvents::NotifyStatus &status);
    virtual ~NotifyStatusChangedProtocolOutgoingCommand();
    
    uint16_t command() const override;
    void doWork(const vector<char>& payload) override;
    vector<char> payload() const override;

private:
    const string mHardwareId;
    const IHardwareStatusesEvents::NotifyStatus mStatus;

};

#endif /* NOTIFYSTATUSCHANGEDPROTOCOLOUTGOINGCOMMAND_H */

