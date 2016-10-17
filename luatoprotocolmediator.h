/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LuaToProtocolMediator.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 19:38
 */

#ifndef LUATOPROTOCOLMEDIATOR_H
#define LUATOPROTOCOLMEDIATOR_H

#include "protocol/startnotifyinfo.h"
#include "isettings.h"
#include "protocol/startnotifyincommingcommandhandler.h"
#include "cancelnotifyincommingcommandhandler.h"

class LuaScriptManager;
class HardwareProtocolFactory;

class LuaToProtocolMediator {
public:
    LuaToProtocolMediator(LuaScriptManager *luaManager, HardwareProtocolFactory *protocolFactory);
    virtual ~LuaToProtocolMediator();
    
    void startNotifyRequest(const StartNotifyInfo &startNotifyInfo);
    void cancelNotifyRequest(const string &notifyId);
    
private:
    StartNotifyIncommingCommandHandler mStartNotifyIncommingCommandHandler;
    CancelNotifyIncommingCommandHandler mCancelNotifyIncommingCommandHandler;
    LuaScriptManager *mLuaManager;
    HardwareProtocolFactory *mProtocolFactory;
    ISettings *mSettings;
};

#endif /* LUATOPROTOCOLMEDIATOR_H */

