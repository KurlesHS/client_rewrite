/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PingProtocolOutgoingCommand.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 23:11
 */

#ifndef PINGPROTOCOLOUTGOINGCOMMAND_H
#define PINGPROTOCOLOUTGOINGCOMMAND_H

#include "iprotocoloutgoingcommand.h"

#include "timer/itimer.h"

class HardwareProtocol;

class PingProtocolOutgoingCommand : public IProtocolOutgoingCommand  {
public:
    PingProtocolOutgoingCommand(HardwareProtocol *protocol);
    virtual ~PingProtocolOutgoingCommand();
    uint16_t command() const override;
    void doWork(const vector<char>& payload) override;
    vector<char> payload() const override;
    
    void onTimeout();

private:
    HardwareProtocol *mHardwareProtocol;
    ITimerSharedPtr mTimer;

};

#endif /* PINGPROTOCOLOUTGOINGCOMMAND_H */

