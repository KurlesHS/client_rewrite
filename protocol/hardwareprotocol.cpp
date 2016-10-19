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
#include "iincommingcommandhandler.h"
#include "authprotocoloutgoingcommand.h"
#include "pingincommingcommandhandler.h"
#include "logger.h"

#include <math.h>
#include <arpa/inet.h>
#include <netinet/in.h>

HardwareProtocol::HardwareProtocol(ITransportSharedPrt transport) :
    mTransport(transport),
    mAuthManager(di_inject(IAuthManager)),
    mPingCommandHandler(new PingIncommingCommandHandler()),
    mTimerFactory(di_inject(ITimerFactory)),
    mError(Error::NoError),
    mSequenceNumber(0),
    mSessionId(Uuid::createUuid().toString()),
    mIsAuthorized(false),
    mIsAuthError(false)
{
    mTransport->addTransportEventsListener(this);
    sendOutgoingCommand(make_shared<AuthProtocolOutgoingCommand>(this, mSessionId));
    registerIncommingCommandHandler(mPingCommandHandler);
    Logger::msg("client from %s is connected...", transport->peerAddress().data());
}

void HardwareProtocol::registerIncommingCommandHandler(IIncommingCommandHandler* handler)
{
    mIncommingCommandHandlers[handler->command()] = handler;
}

HardwareProtocol::~HardwareProtocol()
{
    mTransport->removeTransportEventsListener(this);
    delete mPingCommandHandler;
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
        doWorkWithIncommingData();
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
            doWorkWithIncommingData();
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
    cmd.sequenceNum = currentSeqNum;
    sendCommand(&cmd);
}

void HardwareProtocol::sendCommand(Command* cmd)
{
    if (mTransport->isOpen()) {
        cmd->updateSign(mUserName, mPassword, mSessionId);
        mTransport->write(CommandParser::bulidPacket(*cmd));
    }
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
            /* удаляем команду из списка ожидающих ответа */
            mOutgoingCommands.erase(it);
            /* пароноидальная проверка */
            if (outCmd) {
                if (cmd.command == 0x0000) {
                    /* работа должна быть сделана до проверки авторизации */
                    if (!outCmd->doWorkAfterAuth()) {
                        outCmd->doWork(cmd.data);
                    }
                    if (!cmd.checkSign(mUserName, mPassword, mSessionId)) {
                        /* беда с аутентификацией */
                        if (!mIsAuthError) {
                            mIsAuthError = true;
                            Logger::msg("client from %s: auth error...", mTransport->peerAddress().data());
                        }
                        if (mTransport->isOpen()) {
                            mError = Error::AuthError;
                            mTransport->close();
                            disconnected(mTransport.get());
                        }
                        return;
                    } else if (!mIsAuthorized) {
                        mIsAuthorized = true;
                        Logger::msg("client from %s is authorized...", mTransport->peerAddress().data());

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
    } else {
        /* входящая команда */
        /* сразу проверяем на валидность */
        if (!cmd.checkSign(mUserName, mPassword, mSessionId)) {
            /* беда с аутентификацией */
            if (!mIsAuthError) {
                mIsAuthError = true;
                Logger::msg("client from %s: auth error...", mTransport->peerAddress().data());
            }
            if (mTransport->isOpen()) {
                mError = Error::AuthError;
                mTransport->close();
                disconnected(mTransport.get());
            }
            return;
        } else if (!mIsAuthorized) {
            mIsAuthorized = true;
            Logger::msg("client from %s is authorized...", mTransport->peerAddress().data(), mUserName.data());
        }
        auto it = mIncommingCommandHandlers.find(cmd.command);
        /* по умолчанию отклик ошибочный */
        uint16_t respCommand = 0xffff;
        if (it != mIncommingCommandHandlers.end()) {
            IIncommingCommandHandler *handler = it->second;
            if (handler->handleCommand(cmd.data)) {
                /* команда обработана - шлём нормальный отклик*/
                respCommand = 0x0000;
            }
        }
        /* формируем ответ */
        Command resp;
        resp.command = respCommand;
        resp.sequenceNum = cmd.sequenceNum;
        /* и отправляем его */
        sendCommand(&resp);
    }
}