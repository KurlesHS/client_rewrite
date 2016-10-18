/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainhandler.cpp
 * Author: Alexey
 * 
 * Created on 13 октября 2016 г., 1:07
 */

#include <unistd.h>

#include "mainhandler.h"

#include "protocol/startnotifyincommingcommandhandler.h"

#include "ioc/resolver.h"
#include "isettings.h"
#include "jsonfilesettings.h"
#include "logger.h"
#include "thread/threadregister.h"

MainHandler::MainHandler() :
    mSoundManager("/home/kurles/develop/orange_files"),
    mLuaScriptManager("/usr/share/sonet/scripts"),
    mLuaToProtocolMediator(&mLuaScriptManager, &mFactory),
    mLuaToAudioMediator(&mLuaScriptManager, &mSoundManager)
{
    Logger::createInstanse();
    Logger::setCopyToStdoutEnabled(true);
    Logger::openlog("/var/log/sonet/server/", "server.log");
    Logger::msg("--- Sonet hardware server started ---");    
    mNetworkAudioManager.start();
}

MainHandler::~MainHandler()
{

}

bool MainHandler::run()
{
    di_inject_variable(ISettings, settings);
    if (mFactory.startListen(settings->port())) {
        Logger::msg("start listening port %d", settings->port());
        return true;
    } else {
        Logger::msg("can't start listening port %d", settings->port());
        sleep(1);
        ThreadRegister::unloopAllLoops();
        return false;
    }
}


