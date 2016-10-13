/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   authprotocoloutgoingcommand.h
 * Author: Alexey
 *
 * Created on 13 октября 2016 г., 0:56
 */

#ifndef AUTHPROTOCOLOUTGOINGCOMMAND_H
#define AUTHPROTOCOLOUTGOINGCOMMAND_H

#include "iprotocoloutgoingcommand.h"

#include <string>

class HardwareProtocol;

using namespace std;

class AuthProtocolOutgoingCommand : public IProtocolOutgoingCommand {
public:
    AuthProtocolOutgoingCommand(HardwareProtocol *protocol, const string &sessionId);    
    virtual ~AuthProtocolOutgoingCommand();
    uint16_t command() const override;
    void doWork(const vector<char>& payload) override;
    vector<char> payload() const override;
    bool doWorkAfterAuth() const override;
    
    
private:
    HardwareProtocol *mProtocol;
    const string mSessionId;
};

#endif /* AUTHPROTOCOLOUTGOINGCOMMAND_H */

