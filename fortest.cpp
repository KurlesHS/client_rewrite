/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fortest.cpp
 * Author: Alexey
 * 
 * Created on 11 октября 2016 г., 22:51
 */

#include "fortest.h"
#include "ioc/resolver.h"
#include "timer/itimer.h"

#include <iostream>



ForTest::ForTest()
{
}

ForTest::~ForTest()
{
}

void ForTest::disconnected(ITransport* self)
{
    cout << "disconnect inter " << mCurrentTransports.size() << endl;    
    mCurrentTransports.remove_if([self, this](ITransportSharedPrt transport) {
        if (transport.get() == self) {
            mSpendTransports.push_back(transport);
            transport->removeTransportEventsListener(this);
            return true;
        } 
       return false;
    });
    
    cout << "disconnect exit " << mCurrentTransports.size() << endl;
}

void ForTest::newConnection(TcpServer* self)
{    
    mSpendTransports.clear();
    while (self->hasPendingConnections()) {
        auto socket = self->nextPendingConnection();
        if (socket) {
            socket->addTransportEventsListener(this);
            socket->write("hello", 6);
            mCurrentTransports.push_back(socket);            
        }
    }
}

void ForTest::readyRead(ITransport* self)
{
    char buff[0x1000];
    int len = self->bytesAvailable();
    self->read(buff, len);
    self->write(buff, len);
}

void ForTest::run()
{
    mServer.startListen(55555);
    mServer.addServerEventListener(this);
    di_inject_variable(ITimerFactory, timerfactory);
    auto timer = timerfactory->getTimer(12);
    (void)timer;
}


