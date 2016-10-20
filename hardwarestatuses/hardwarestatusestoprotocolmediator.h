/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusesToProtocolMediator.h
 * Author: Alexey
 *
 * Created on 19 октября 2016 г., 18:54
 */

#ifndef HARDWARESTATUSESTOPROTOCOLMEDIATOR_H
#define HARDWARESTATUSESTOPROTOCOLMEDIATOR_H


#include "ihardwarestatusesevents.h"

#include "requesthardwarestatusesincommingcommandhandler.h"

class HardwareProtocolFactory;
class HardwareStatusesManager;

class HardwareStatusesToProtocolMediator : IHardwareStatusesEvents {
public:
    HardwareStatusesToProtocolMediator(HardwareProtocolFactory *protocolFactory, HardwareStatusesManager *statusesManager);
    virtual ~HardwareStatusesToProtocolMediator();
    
    void onHardwareStatusChanged(const string& hardwareId, const HardwareStatus& newSatus) override;
    void onNotifyStatusChanged(const string& hardwareId, const NotifyStatus& newSatus) override;
            
private:
    HardwareProtocolFactory *mProtocolFactory;
    HardwareStatusesManager *mStatusesManager;
    RequestHardwareStatusesIncommingCommandHandler mRequsetHardwareStatusesHandler;

};

#endif /* HARDWARESTATUSESTOPROTOCOLMEDIATOR_H */

