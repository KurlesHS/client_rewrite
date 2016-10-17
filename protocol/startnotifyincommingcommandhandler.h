/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   startnotifyincommingcommandhandler.h
 * Author: kurles
 *
 * Created on 13 октября 2016 г., 9:48
 */

#ifndef STARTNOTIFYINCOMMINGCOMMANDHANDLER_H
#define STARTNOTIFYINCOMMINGCOMMANDHANDLER_H

#include "iincommingcommandhandler.h"

#include "startnotifyinfo.h"

#include <list>
#include <unordered_map>

#include "stdint.h"

#include "json/json.hpp"

using namespace std;

class LuaToProtocolMediator;

class StartNotifyIncommingCommandHandler : public IIncommingCommandHandler {
public:
    StartNotifyIncommingCommandHandler(LuaToProtocolMediator *mediator);
    virtual ~StartNotifyIncommingCommandHandler();

    uint16_t command() const override;
    bool handleCommand(const vector<char>& payload) override;

private:
    LuaToProtocolMediator *mMediator;
    string mCommandDescription;
};

#endif /* STARTNOTIFYINCOMMINGCOMMANDHANDLER_H */

