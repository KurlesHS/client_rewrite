/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainhandler.h
 * Author: Alexey
 *
 * Created on 13 октября 2016 г., 1:07
 */

#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include "protocol/hardwareprotocolfactory.h"
#include "soundmanager.h"
#include "lua/luascriptmanager.h"
#include "luatoprotocolmediator.h"
#include "luatoaudiomediator.h"

class MainHandler {
public:
    MainHandler();
    virtual ~MainHandler();
    
    bool run();
    
private:
    HardwareProtocolFactory mFactory;
    SoundManager mSoundManager;
    LuaScriptManager mLuaScriptManager;
    LuaToProtocolMediator mLuaToProtocolMediator;
    LuaToAudioMediator mLuaToAudioMediator;
};

#endif /* MAINHANDLER_H */

