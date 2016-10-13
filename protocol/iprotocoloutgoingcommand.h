/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iprotocoloutgoingcommand.h
 * Author: Alexey
 *
 * Created on 13 октября 2016 г., 0:00
 */

#ifndef IPROTOCOLOUTGOINGCOMMAND_H
#define IPROTOCOLOUTGOINGCOMMAND_H

#include <vector>
#include <memory>

using namespace std;

class IProtocolOutgoingCommand;

using IProtocolOutgoingCommandSharedPtr = shared_ptr<IProtocolOutgoingCommand>;

class IProtocolOutgoingCommand {
public:        
    virtual ~IProtocolOutgoingCommand() { }
    
    virtual uint16_t command() const = 0;
    virtual void doWork(const vector<char> &payload) = 0;
    virtual void doWorkOnError() { }
    virtual vector<char> payload() const = 0;
    virtual bool doWorkAfterAuth() const { return false; }    
};

#endif /* IPROTOCOLOUTGOINGCOMMAND_H */

