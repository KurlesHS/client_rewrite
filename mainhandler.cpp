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
#include "logger.h"
#include "thread/threadregister.h"

MainHandler::MainHandler() :
    mSoundManager("/var/spool/sonet/files", Resolver::resolveDi<ISettings>()->fileServerUrl()),
    mLuaScriptManager("/usr/share/sonet/scripts"),
    mLuaToProtocolMediator(&mLuaScriptManager, &mFactory, &mSoundManager),
    mLuaToAudioMediator(&mLuaScriptManager, &mSoundManager),
    mLuaToNetworkStreamMediator(&mLuaScriptManager, &mNetworkAudioManager),
    mHardwareStatusesToLualMediator(&mStatusesManager, &mLuaScriptManager),
    mHardwareStatusesToProtocolMediator(&mFactory, &mStatusesManager)
{
    Logger::createInstanse();
    Logger::setCopyToStdoutEnabled(true);
    Logger::openlog("/var/log/sonet/server/", "server.log");
    Logger::msg("--- Sonet hardware server started ---");
    mGpioManager.start();
    mNetworkAudioManager.start();
    mGpioManager.gpioState("fire");
    mGpioManager.setGpioState("power", 1);
    mLuaScriptManager.startAutostartScript(di_inject(ISettings)->autostartScript());
    
#if 0
    mNetworkAudioManager.startStream("rtsp://localhost:9002/test.sdp");
    mSoundManager.downloadFileFromServer("827717d816d95c60f2059c8be841341897216104100d7b495f04c96f", "test.mp4", [](bool result) {
        cout << "downloaded: " << (int) result << endl;
    });
#endif

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


