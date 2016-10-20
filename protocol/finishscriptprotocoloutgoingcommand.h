/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FinishScriptProtocolOutgoingCommand.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 21:53
 */

#ifndef FINISHSCRIPTPROTOCOLOUTGOINGCOMMAND_H
#define FINISHSCRIPTPROTOCOLOUTGOINGCOMMAND_H

#include "iprotocoloutgoingcommand.h"

class FinishScriptProtocolOutgoingCommand : public IProtocolOutgoingCommand {
public:

    enum class FinishReason {
        Normal,
        Error,
        Canceled
    };
    FinishScriptProtocolOutgoingCommand(const string &notifyId, const string &scriptName, const FinishReason reason);
    virtual ~FinishScriptProtocolOutgoingCommand();
    
    uint16_t command() const override;
    
    void doWork(const vector<char>& payload) override;
    
    vector<char> payload() const override;



private:
    const string mNotifyId;
    const string mScriptName;
    const FinishReason mReason;
};

#endif /* FINISHSCRIPTPROTOCOLOUTGOINGCOMMAND_H */

