/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocol.cpp
 * Author: Alexey
 * 
 * Created on 12 октября 2016 г., 18:45
 */

#include "uuid.h"
#include "hardwareprotocol.h"

#include "ioc/resolver.h"

#include "timer/itimer.h"

#include "auth/iauthmanager.h"
#include "authprotocoloutgoingcommand.h"

#include <math.h>

HardwareProtocol::HardwareProtocol(ITransportSharedPrt transport) :
    mTransport(transport),
    mAuthManager(di_inject(IAuthManager)),
    mTimerFactory(di_inject(ITimerFactory)),
    mError(Error::NoError),
    mSequenceNumber(0),
    mSessionId(Uuid::createUuid().toString(28)), /* 28 байт id сессии */
    mIsAuthorized(false)
{
    mTransport->addTransportEventsListener(this);
    sendOutgoingCommand(make_shared<AuthProtocolOutgoingCommand>(this, mSessionId));
}

HardwareProtocol::~HardwareProtocol()
{
    mTransport->removeTransportEventsListener(this);
}

void HardwareProtocol::disconnected(ITransport* self)
{
    self->removeTransportEventsListener(this);
}

void HardwareProtocol::readyRead(ITransport* self)
{
    char buff[0x1000];
    int bytes = self->bytesAvailable();
    while (bytes > 0) {
        bytes = min<int>(bytes, sizeof (buff));
        self->read(buff, bytes);
        mHardwareProtocolParser.addData(buff, bytes);
        bytes = self->bytesAvailable();
    }
}

void HardwareProtocol::doWorkWithIncommingData()
{
    HardwareProtocolPacketParser::Result res;
    auto cmd = mHardwareProtocolParser.getCommand(res);
    using R = HardwareProtocolPacketParser::Result;
    switch (res) {
        case R::Empty:
            processEmptyCommand();
            break;
        case R::Ok:
            processOkCommand(cmd);
            break;
        case R::Incomplete:
            processIncompleteCommand();
            break;
        case R::Error:
            processErrorCommand();
            break;
    }
}

void HardwareProtocol::processEmptyCommand()
{
    //TODO: запланировать отправку ping команды
}

void HardwareProtocol::processErrorCommand()
{
    mError = Error::CommandError;
    if (mTransport->isOpen()) {
        mTransport->close();
        disconnected(mTransport.get());
    }
}

void HardwareProtocol::processIncompleteCommand()
{
    // TODO: запустить таймер

}

HardwareProtocol::Error HardwareProtocol::error() const
{
    return mError;
}

void HardwareProtocol::sendOutgoingCommand(IProtocolOutgoingCommandSharedPtr outgoingCommand)
{
    if (!mTransport->isOpen()) {
        return;
    }
    auto currentSeqNum = mSequenceNumber++;
    mOutgoingCommands[currentSeqNum] = outgoingCommand;
    Command cmd;
    cmd.command = outgoingCommand->command();
    cmd.data = outgoingCommand->payload();
    cmd.updateSignAndSession(mUserName, mPassword, mSessionId);
    
    mTransport->write(CommandParser::bulidPacket(cmd));
    
}

void HardwareProtocol::setUserName(const string& userName)
{
    mUserName = userName;
    mPassword = mAuthManager->getUserPassword(userName);
}

void HardwareProtocol::processOkCommand(const Command& cmd)
{
    if (cmd.command == 0x0000 || cmd.command == 0xffff) {
        /* отклик. */
        auto it = mOutgoingCommands.find(cmd.sequenceNum);
        if (it != mOutgoingCommands.end()) {
            /* есть команда, ожидающая отклика */
            IProtocolOutgoingCommandSharedPtr outCmd = it->second;
            /* пароноидальная проверка */
            if (outCmd) {
                if (cmd.command == 0x0000) {
                    /* работа должна быть сделана до проверки авторизации */
                    if (!outCmd->doWorkAfterAuth()) {
                        outCmd->doWork(cmd.data);
                    }
                    if (!cmd.checkSign(mUserName, mPassword, mSessionId)) {
                        /* беда с аутентификацией */
                        if (mTransport->isOpen()) {
                            mError = Error::AuthError;
                            mTransport->close();
                            disconnected(mTransport.get());
                        }
                        return;
                    }
                    /* работа должна быть сделана после проверки авторизации */
                    if (outCmd->doWorkAfterAuth()) {
                        outCmd->doWork(cmd.data);
                    }
                } else {
                    outCmd->doWorkOnError();
                }
            }
        }
    }
}