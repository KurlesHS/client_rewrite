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
#include "lua/scriptfinishedluaevent.h"
#include "lua/scriptstartedluaevent.h"
#include "protocol/startscriptprotocoloutgoingcommand.h"
#include "protocol/finishscriptprotocoloutgoingcommand.h"
#include "lua/logmessageluaevent.h"
#include "lua/outgoingmessageluaevent.h"
#include "protocol/outgoingmessageprotocolcommand.h"

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
    mLuaManager->addLuaScriptEventListener(this);
}

LuaToProtocolMediator::~LuaToProtocolMediator()
{

}

void LuaToProtocolMediator::handleFinishScriptLuaEvent(ILuaEventSharedPtr event)
{
    auto evt = static_cast<ScriptFinishedLuaEvent*> (event.get());

    FinishScriptProtocolOutgoingCommand::FinishReason reason = FinishScriptProtocolOutgoingCommand::FinishReason::Normal;
    string strReason("normal");

    if (evt->isCanceled()) {
        reason = FinishScriptProtocolOutgoingCommand::FinishReason::Canceled;
        strReason = "cancel";
    } else if (evt->hasError()) {
        reason = FinishScriptProtocolOutgoingCommand::FinishReason::Error;
        strReason = "error";
    }
    Logger::msg("script (%s) with notify id '%s' is finished with status %s",
            evt->scriptName().data(), evt->notifyId().data(), strReason.data());
    mProtocolFactory->sendCommand(
            make_shared<FinishScriptProtocolOutgoingCommand>(evt->notifyId(), evt->scriptName(), reason));
}

void LuaToProtocolMediator::handleStartScriptLuaEvent(ILuaEventSharedPtr event)
{
    auto evt = static_cast<ScriptStartedLuaEvent*> (event.get());
    Logger::msg("script (%s) with notify id '%s' and code '%s' is started",
            evt->scriptName().data(), evt->notifyId().data(), evt->notifyCode().data());
    mProtocolFactory->sendCommand(
            make_shared<StartScriptProtocolOutgoingCommand>(evt->notifyId(), evt->notifyCode(), evt->scriptName()));
}

void LuaToProtocolMediator::handleOutgoingMessageLuaEvent(ILuaEventSharedPtr event)
{
    auto evt = static_cast<OutgoingMessageLuaEvent*> (event.get());
    Logger::msg("message from hardware with id (%s): %s",
            evt->hardwareId().data(), evt->message().data());
    mProtocolFactory->sendCommand(
            make_shared<OutgoingMessageProtocolCommand>(evt->hardwareId(), evt->message()));
}

void LuaToProtocolMediator::luaEvent(ILuaEventSharedPtr event)
{
    switch (event->eventType()) {
        case ILuaEvent::EventType::FinishScript:
            handleFinishScriptLuaEvent(event);
            break;
        case ILuaEvent::EventType::StartScript:
            handleStartScriptLuaEvent(event);
            break;
        case ILuaEvent::EventType::OutgoingMessage:
            handleOutgoingMessageLuaEvent(event);
        default:
            break;
    }
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
        auto event = make_shared<ScriptFinishedLuaEvent>("", startNotifyInfo.id, startNotifyInfo.code, "-", false, true);
        mLuaManager->luaEvent(event);
    } else {
        mLuaManager->startScript(scriptName, startNotifyInfo);
    }
}

void LuaToProtocolMediator::cancelNotifyRequest(const string& notifyId)
{
    mLuaManager->cancelScript(notifyId);
}

