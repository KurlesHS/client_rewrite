/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StartNotifyProtocolOutgoingCommand.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 21:41
 */

#ifndef STARTNOTIFYPROTOCOLOUTGOINGCOMMAND_H
#define STARTNOTIFYPROTOCOLOUTGOINGCOMMAND_H

#include "iprotocoloutgoingcommand.h"

class StartScriptProtocolOutgoingCommand : public IProtocolOutgoingCommand {
public:
    StartScriptProtocolOutgoingCommand(const string &notifyId,
            const string &notifyCode,
            const string &scriptName);
    virtual ~StartScriptProtocolOutgoingCommand();

    uint16_t command() const override;
    void doWork(const vector<char>& payload) override;
    vector<char> payload() const override;

private:
    const string mNotifyId;
    const string mNotifyCode;
    const string mScriptName;
};

#endif /* STARTNOTIFYPROTOCOLOUTGOINGCOMMAND_H */

