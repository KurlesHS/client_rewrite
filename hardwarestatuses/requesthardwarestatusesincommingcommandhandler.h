/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RequestHardwareStatusesIncommingCommandHandler.h
 * Author: Alexey
 *
 * Created on 20 октября 2016 г., 0:39
 */



#ifndef REQUESTHARDWARESTATUSESINCOMMINGCOMMANDHANDLER_H
#define REQUESTHARDWARESTATUSESINCOMMINGCOMMANDHANDLER_H

#include "protocol/iincommingcommandhandler.h"

class HardwareProtocolFactory;
class HardwareStatusesManager;


class RequestHardwareStatusesIncommingCommandHandler : public IIncommingCommandHandler {
public:
    RequestHardwareStatusesIncommingCommandHandler(HardwareProtocolFactory *protocolFactory, HardwareStatusesManager *statusesManager);    
    virtual ~RequestHardwareStatusesIncommingCommandHandler();
    
    uint16_t command() const override;
    bool handleCommand(const vector<char>& payload) override;

private:
    HardwareProtocolFactory *mProtocolFactory;
    HardwareStatusesManager *mStatusesManager;
};

#endif /* REQUESTHARDWARESTATUSESINCOMMINGCOMMANDHANDLER_H */

