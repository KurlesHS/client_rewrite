/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocolfactory.cpp
 * Author: Alexey
 * 
 * Created on 12 октября 2016 г., 20:25
 */

#include "hardwareprotocolfactory.h"
#include "hardwareprotocol.h"

HardwareProtocolFactory::~HardwareProtocolFactory()
{
}

void HardwareProtocolFactory::newConnection(TcpServer* self)
{
    /* получено новое соединение*/
    while (self->hasPendingConnections()) {
        auto socket = self->nextPendingConnection();
        if (socket) {
            /* есть создаём протокол, и помещаем его к активным */
            auto protocol = std::make_shared<HardwareProtocol>(socket);
            mActiveProtocols.push_back(protocol);
            for (auto h : mIncommingCommandHandlers) {
                protocol->registerIncommingCommandHandler(h);
            }
            
        }
    }
}

HardwareProtocolFactory::HardwareProtocolFactory()
{
    mServer.addServerEventListener(this);
}

bool HardwareProtocolFactory::startListen(const uint16_t port)
{
    return mServer.startListen(port);
}

void HardwareProtocolFactory::sendCommand(IProtocolOutgoingCommandSharedPtr command) {
    for (HardwareProtocolSharedPtr protocol : mActiveProtocols) {
        protocol->sendOutgoingCommand(command);
    }
}

void HardwareProtocolFactory::registerIncommingCommandHandler(IIncommingCommandHandler* handler) {
    mIncommingCommandHandlers.push_back(handler);
    for (HardwareProtocolSharedPtr protocol : mActiveProtocols) {
        protocol->registerIncommingCommandHandler(handler);
    }
}


