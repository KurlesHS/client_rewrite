/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocolfactory.cpp
 * Author: Alexey
 * 
 * Created on 12 октября 2016 г., 0:05
 */

#include "hardwareprotocolfactory.h"

HardwareProtocolFactory::HardwareProtocolFactory()
{
    mServer->addServerEventListener(this);
}

HardwareProtocolFactory::~HardwareProtocolFactory()
{
}

void HardwareProtocolFactory::newConnection(TcpServer* self)
{
    while (self->hasPendingConnections()) {
        auto socket = self->nextPendingConnection();
        
    }

}


