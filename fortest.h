/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fortest.h
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 22:51
 */

#ifndef FORTEST_H
#define FORTEST_H

#include "thread/threadregister.h"
#include "network/tcpserver.h"
#include "network/tcpsocket.h"

using namespace std;

class ForTest : public ITransportEvents, public ITcpServerEvents {
public:
    ForTest();
    virtual ~ForTest();
    
    void run();
    
    void disconnected(ITransport* self) override;
    void newConnection(TcpServer* self) override;
    void readyRead(ITransport* self) override;    
    
    
private:
    list<ITransportSharedPrt> mCurrentTransports;
    list<ITransportSharedPrt> mSpendTransports;
    TcpServer mServer;
    

};

#endif /* FORTEST_H */

