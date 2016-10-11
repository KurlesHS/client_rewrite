/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocolfactory.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 0:05
 */

#ifndef HARDWAREPROTOCOLFACTORY_H
#define HARDWAREPROTOCOLFACTORY_H

#include "network/tcpserver.h"

#include <list>

using namespace std;

/* подразумеваем, что сетевая взаимодействие с сервером происходит в главном потоке */

class HardwareProtocolFactory : public ITcpServerEvents {
public:
    HardwareProtocolFactory();
    virtual ~HardwareProtocolFactory();
    
    void newConnection(TcpServer* self) override;
    
private:
    TcpServer *mServer;
    list<TcpSocketSharedPrt> mCurrentConnections;

};

#endif /* HARDWAREPROTOCOLFACTORY_H */

