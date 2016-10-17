/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cancelnotifyincommingcommand.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 23:03
 */

#ifndef CANCELNOTIFYINCOMMINGCOMMANDHANDLER_H
#define CANCELNOTIFYINCOMMINGCOMMANDHANDLER_H

#include "protocol/iincommingcommandhandler.h"

class LuaToProtocolMediator;

class CancelNotifyIncommingCommandHandler : public IIncommingCommandHandler {
public:
    CancelNotifyIncommingCommandHandler(LuaToProtocolMediator *mediator);
    virtual ~CancelNotifyIncommingCommandHandler();

    uint16_t command() const override;
    bool handleCommand(const vector<char>& payload) override;


private:
    LuaToProtocolMediator *mMediator;
};

#endif /* CANCELNOTIFYINCOMMINGCOMMANDHANDLER_H */

