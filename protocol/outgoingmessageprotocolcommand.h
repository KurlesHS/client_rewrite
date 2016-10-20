/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutgoingMessageProtocolCommand.h
 * Author: Alexey
 *
 * Created on 20 октября 2016 г., 1:14
 */

#ifndef OUTGOINGMESSAGEPROTOCOLCOMMAND_H
#define OUTGOINGMESSAGEPROTOCOLCOMMAND_H

#include "iprotocoloutgoingcommand.h"


class OutgoingMessageProtocolCommand : public IProtocolOutgoingCommand {
public:
    OutgoingMessageProtocolCommand(const string &hardwareId, const string &message);
    virtual ~OutgoingMessageProtocolCommand();
    
    uint16_t command() const override;
    void doWork(const vector<char>& payload) override;
    vector<char> payload() const override;
    
private:
    const string mHardwareId;
    const string mMessage;
};

#endif /* OUTGOINGMESSAGEPROTOCOLCOMMAND_H */

