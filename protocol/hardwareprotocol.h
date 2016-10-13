/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocol.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 18:45
 */

#ifndef HARDWAREPROTOCOL_H
#define HARDWAREPROTOCOL_H

class HardwareProtocol;
class IAuthManager;

#include "network/tcpsocket.h"
#include "network/itransport.h"

#include "iprotocoloutgoingcommand.h"
#include "hardwareprotocolpacketparser.h"

#include <unordered_map>

class ITimerFactory;

class HardwareProtocol : public ITransportEvents {
public:

    enum class Error : char {
        NoError,
        SocketError,
        AuthError,
        CommandError
    };

    HardwareProtocol(ITransportSharedPrt transport);
    virtual ~HardwareProtocol();
    virtual void disconnected(ITransport* self) override;
    virtual void readyRead(ITransport* self) override;
    void setUserName(const string &userName);
    
    void sendOutgoingCommand(IProtocolOutgoingCommandSharedPtr outgoingCommand);
    
    Error error() const;

private:
    void doWorkWithIncommingData();

    void processOkCommand(const Command &cmd);
    void processErrorCommand();
    void processEmptyCommand();
    void processIncompleteCommand();

private:
    ITransportSharedPrt mTransport;
    IAuthManager *mAuthManager;
    HardwareProtocolPacketParser mHardwareProtocolParser;
    ITimerFactory *mTimerFactory;
    Error mError;
    
    unordered_map<uint64_t, IProtocolOutgoingCommandSharedPtr> mOutgoingCommands;

    uint64_t mSequenceNumber;
    string mUserName;
    string mPassword;
    const string mSessionId;
    bool mIsAuthorized;
};

#endif /* HARDWAREPROTOCOL_H */

