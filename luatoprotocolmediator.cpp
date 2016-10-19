/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LuaToProtocolMediator.cpp
 * Author: Alexey
 * 
 * Created on 17 октября 2016 г., 19:38
 */

#include "luatoprotocolmediator.h"

#include "lua/luascriptmanager.h"
#include "protocol/hardwareprotocolfactory.h"

#include "logger.h"
#include "ioc/resolver.h"

LuaToProtocolMediator::LuaToProtocolMediator(LuaScriptManager *luaManager, HardwareProtocolFactory *protocolFactory, SoundManager *soundManager) :
    mStartNotifyIncommingCommandHandler(this),
    mCancelNotifyIncommingCommandHandler(this),
    mLuaManager(luaManager),
    mProtocolFactory(protocolFactory),
    mSoundManager(soundManager),
    mSettings(di_inject(ISettings))
{
    mProtocolFactory->registerIncommingCommandHandler(&mStartNotifyIncommingCommandHandler);
    mProtocolFactory->registerIncommingCommandHandler(&mCancelNotifyIncommingCommandHandler);
}

LuaToProtocolMediator::~LuaToProtocolMediator()
{
}

void LuaToProtocolMediator::startNotifyRequest(const StartNotifyInfo& startNotifyInfo)
{
    bool isNeedToStartNotifyIdemideatly = true;
    if (startNotifyInfo.audioContentType == "file" && !startNotifyInfo.audioContentValue.empty()) {
        if (!mSoundManager->isFilePresent(startNotifyInfo.audioContentValue)) {
            // нужно скачать файл!!!
            isNeedToStartNotifyIdemideatly = false;
            mSoundManager->downloadFileFromServer(startNotifyInfo.audioContentValue,
                    startNotifyInfo.audioContentFileName, [this, startNotifyInfo](bool result) {
                        auto startNotifyInfoCopy = startNotifyInfo;
                        if (!result) {
                            startNotifyInfoCopy.audioContentFileName.clear();
                                    startNotifyInfoCopy.audioContentType.clear();
                                    startNotifyInfoCopy.audioContentValue.clear();
                        }
                        startNotifyRequestHelper(startNotifyInfoCopy);
                    });
        }
    }

    if (isNeedToStartNotifyIdemideatly) {
        // файл скачивать не нужно
        startNotifyRequestHelper(startNotifyInfo);
    }
}

void LuaToProtocolMediator::startNotifyRequestHelper(const StartNotifyInfo& startNotifyInfo)
{
    string scriptName = mSettings->scriptNameByNotifyCode(startNotifyInfo.code);
    if (scriptName.empty()) {
        Logger::msg("binding notify code '%s' with script name isn't present", startNotifyInfo.code.data());
    } else {
        mLuaManager->startScript(scriptName, startNotifyInfo);
    }
}

void LuaToProtocolMediator::cancelNotifyRequest(const string& notifyId)
{
    mLuaManager->cancelScript(notifyId);
}

