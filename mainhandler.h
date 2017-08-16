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
#include "networkaudio/networkaudiomanager.h"
#include "luatonetworkstreammediator.h"
#include "hardwarestatuses/hardwarestatusestolualmediator.h"
#include "hardwarestatuses/hardwarestatusestoprotocolmediator.h"
#include "hardwarestatuses/hardwarestatusesmanager.h"
#include "gpio/gpiomanager.h"
#include "gpio/luatogpiomediator.h"
#include "file_watcher/filewatcher.h"
#include "file_watcher/filecontenteventhandler.h"

class MainHandler {
public:
    MainHandler();
    virtual ~MainHandler();
    
    bool run();
    
private:
    NetworkAudioManager mNetworkAudioManager;
    HardwareProtocolFactory mFactory;
    SoundManager mSoundManager;
    LuaScriptManager mLuaScriptManager;
    HardwareStatusesManager mStatusesManager;
    GpioManager mGpioManager;
    LuaToGpioMediator mLuaToGpioMediator;
    LuaToProtocolMediator mLuaToProtocolMediator;
    LuaToAudioMediator mLuaToAudioMediator;
    LuaToNetworkStreamMediator mLuaToNetworkStreamMediator;
    HardwareStatusesToLualMediator mHardwareStatusesToLualMediator;
    HardwareStatusesToProtocolMediator mHardwareStatusesToProtocolMediator;
    FileWatcher mFileWatcher;
    FileContentEventHandler mFileContentEventHandler;
};

#endif /* MAINHANDLER_H */

