/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HardwareStatusesToProtocolMediator.cpp
 * Author: Alexey
 * 
 * Created on 19 октября 2016 г., 18:54
 */

#include "hardwarestatusestoprotocolmediator.h"

#include "hardwarestatuschangedprotocoloutgoingcommand.h"
#include "hardwarestatusesmanager.h"
#include "protocol/hardwareprotocolfactory.h"
#include "networkaudio/notifystatuschangedprotocoloutgoingcommand.h"

#include <memory>

using namespace std;

HardwareStatusesToProtocolMediator::HardwareStatusesToProtocolMediator(HardwareProtocolFactory *protocolFactory, HardwareStatusesManager *statusesManager) :
    mProtocolFactory(protocolFactory),
    mStatusesManager(statusesManager),
    mRequsetHardwareStatusesHandler(protocolFactory, statusesManager)
{
    mStatusesManager->addEventsListener(this);
    mProtocolFactory->registerIncommingCommandHandler(&mRequsetHardwareStatusesHandler);

}

HardwareStatusesToProtocolMediator::~HardwareStatusesToProtocolMediator()
{
    mStatusesManager->removeEventsListener(this);
}

void HardwareStatusesToProtocolMediator::onHardwareStatusChanged(const string& hardwareId, const HardwareStatus& newSatus)
{
    mProtocolFactory->sendCommand(make_shared<HardwareStatusChangedProtocolOutgoingCommand>(hardwareId, newSatus));
}

void HardwareStatusesToProtocolMediator::onNotifyStatusChanged(const string& hardwareId, const NotifyStatus& newSatus)
{
    mProtocolFactory->sendCommand(make_shared<NotifyStatusChangedProtocolOutgoingCommand>(hardwareId, newSatus));
}
