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
#include "iprotocoloutgoingcommand.h"
#include <list>
#include <memory>

class HardwareProtocol;
class IIncommingCommandHandler;

using namespace std;

/* подразумеваем, что сетевая взаимодействие с сервером происходит в главном потоке */

class HardwareProtocolFactory : public ITcpServerEvents {
public:
    HardwareProtocolFactory();
    virtual ~HardwareProtocolFactory();

    bool startListen(const uint16_t port);
    void newConnection(TcpServer* self) override;
    void sendCommand(IProtocolOutgoingCommandSharedPtr command);
    void registerIncommingCommandHandler(IIncommingCommandHandler *handler);


private:
    TcpServer mServer;
    list<std::shared_ptr<HardwareProtocol>> mActiveProtocols;
    list<std::shared_ptr<HardwareProtocol>> mSpentProtocols;


};

#endif /* HARDWAREPROTOCOLFACTORY_H */

