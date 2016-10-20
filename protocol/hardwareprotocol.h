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



#include "network/tcpsocket.h"
#include "network/itransport.h"

#include "iprotocoloutgoingcommand.h"
#include "hardwareprotocolpacketparser.h"
#include "iincommingcommandhandler.h"

#include <unordered_map>
#include "timer/itimer.h"

class HardwareProtocol;
class IAuthManager;
class ITimerFactory;

class IIncommingCommandHandler;

using HardwareProtocolSharedPtr = std::shared_ptr<HardwareProtocol>;

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
    void registerIncommingCommandHandler(IIncommingCommandHandler *handler);
    
    Error error() const;
    
    void disconnectFromClient();

private:
    void doWorkWithIncommingData();

    void processOkCommand(const Command &cmd);
    void processErrorCommand();
    void processEmptyCommand();
    void processIncompleteCommand();
    
    void sendCommand(Command *cmd);
    
    void onPingCmdTimeout();

private:
    ITransportSharedPrt mTransport;
    IAuthManager *mAuthManager;
    HardwareProtocolPacketParser mHardwareProtocolParser;
    IIncommingCommandHandler *mPingCommandHandler;
    ITimerFactory *mTimerFactory;
    ITimerSharedPtr mTimerForPingCommand; 
    Error mError;
    
    unordered_map<uint64_t, IProtocolOutgoingCommandSharedPtr> mOutgoingCommands;
    unordered_map<uint16_t, IIncommingCommandHandler *> mIncommingCommandHandlers;

    uint64_t mSequenceNumber;
    string mUserName;
    string mPassword;
    const string mSessionId;
    bool mIsAuthorized;
    bool mIsAuthError;
};

#endif /* HARDWAREPROTOCOL_H */

