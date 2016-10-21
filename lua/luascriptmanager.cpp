/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luascriptmanager.cpp
 * Author: Alexey
 * 
 * Created on 17 октября 2016 г., 18:12
 */

#include "luascriptmanager.h"

#include "thread/threadregister.h"
#include "scriptfinishedluaevent.h"
#include "logger.h"
#include "scriptstartedluaevent.h"
#include "auth/lua/iluafunctionregistrator.h"

#include <algorithm>
#include <iostream>

LuaScriptManager::LuaScriptManager(const string& luaScriptPath) :
    mLuaScriptPath(luaScriptPath)
{
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<LuaScriptManager, &LuaScriptManager::onAsyncCommand>(this);
    mAsync.start();
}

void LuaScriptManager::cancelScript(const string& notifyId)
{

    for (auto it = mScripts.begin(); it != mScripts.end(); ++it) {
        if (it->get()->notifyId() == notifyId) {
            it = mScripts.erase(it);
        }
    }

    if (mCurrentScript) {
        if (mCurrentScript->notifyId() == notifyId) {
            Logger::msg("Cancel current script '%s'", mCurrentScript->scriptName().data());
            mCurrentScript->cancel();
        }
    }
}

void LuaScriptManager::startAutostartScript(const string& scriptName)
{
    if (scriptName.empty()) {
        Logger::msg("autostart script is not present in settings");
        return;
    }
    string scriptPath = mLuaScriptPath + "/" + scriptName + ".lua";
    auto script = make_shared<LuaScript>(scriptPath);
    script->setScriptName(scriptName);
    if (script->isValid()) {
        mAutostartScript = script;
        mAutostartScript->addLuaScriptEventListener(this);
        for (auto handler : mIfHappensHandlers) {
            handler->registerCommand(mAutostartScript->luaState());
            handler->addLuaScript(mAutostartScript.get());
        }
        Logger::msg("starting autostart script '%s'...", scriptName.data());
        for (auto registrator : mFunctionRegistrators) {
            registrator->registerFunction(&mAutostartScript->luaState());
        }
        mAutostartScript->run();
    } else {
        Logger::msg("autostart script '%s' is not valid", scriptName.data());
    }

}

void LuaScriptManager::startScript(const string& scriptName, const StartNotifyInfo &info)
{
    string scriptPath = mLuaScriptPath + "/" + scriptName + ".lua";
    auto script = make_shared<LuaScript>(scriptPath);
    script->setNotifyId(info.id);
    script->setScriptName(scriptName);
    if (script->isValid()) {
        script->setPriority(info.priority);
        script->setNotifyInfo(info);
        script->addLuaScriptEventListener(this);
        if (mCurrentScript) {
            if (mCurrentScript->priority() < script->priority()) {
                // если у пришедшего скрипта приоритет больше текущего, то выполнение
                // текущей задачи надо прервать
                Logger::msg("cancel current script '%s'", mCurrentScript->scriptName().data());
                mCurrentScript->cancel();
                // TODO: log this
            }
            // добваляем сприпт в очередь
            mScripts.push_back(script);
            // сортируем ее
            mScripts.sort([](LuaScriptSharedPtr a, LuaScriptSharedPtr b) {
                return a->priority() > b->priority();
            });
            // и ожидаем завершения работы скрипта                

        } else {
            // скрипта в работе на данный момент нет - запускаем текущий скрипт
            mCurrentScript = script;
            runCurrentScript();
        }
    } else {
        luaEvent(make_shared<ScriptFinishedLuaEvent>(script->id(), info.id, info.code, scriptName, false, true));
    }
}

void LuaScriptManager::runCurrentScript()
{
    if (mCurrentScript) {
        for (auto registrator : mFunctionRegistrators) {
            registrator->registerFunction(&mCurrentScript->luaState());
        }
        for (auto handler : mIfHappensHandlers) {
            handler->registerCommand(mCurrentScript->luaState());
            handler->addLuaScript(mCurrentScript.get());
        }
        const auto &info = mCurrentScript->notifyInfo();
        for (auto listener : mEventListeners) {
            listener->luaEvent(make_shared<ScriptStartedLuaEvent>(info.id,
                    info.code, mCurrentScript->scriptName()));
        }
        mCurrentScript->run();
    }
}

void LuaScriptManager::resetAutostartScript()
{
    if (mAutostartScript) {
        for (auto handler : mIfHappensHandlers) {
            handler->removeLuaScript(mAutostartScript.get());
        }
        Logger::msg("clear autostart script '%s'", mAutostartScript->scriptName().data());
        mAutostartScript.reset();
    }
}

void LuaScriptManager::resetCurrentScript()
{
    if (mCurrentScript) {
        for (auto handler : mIfHappensHandlers) {
            handler->removeLuaScript(mCurrentScript.get());
        }
        Logger::msg("remove current script '%s'", mCurrentScript->scriptName().data());
        mCurrentScript.reset();
    }
}

void LuaScriptManager::addIfHappensHandler(ILuaEventForIfHappensHandler* handler)
{
    mIfHappensHandlers.push_back(handler);
}

void LuaScriptManager::removeIfHappensHandler(ILuaEventForIfHappensHandler* handler)
{
    mIfHappensHandlers.remove(handler);
}

void LuaScriptManager::addLuaScriptEventListener(ILuaScriptEventsListener* listener)
{
    mEventListeners.push_back(listener);
}

void LuaScriptManager::removeLuaScriptEventListener(ILuaScriptEventsListener* listener)
{
    mEventListeners.remove(listener);
}

void LuaScriptManager::luaEvent(ILuaEventSharedPtr event)
{
    if (event->eventType() == ILuaEvent::EventType::FinishScript) {
        // для предотвращения удаления экземпляра LuaScript в процесс рассылки
        // оным уведомления о событии
        auto finishEvent = static_cast<ScriptFinishedLuaEvent*> (event.get());

        if (mCurrentScript && finishEvent && finishEvent->scriptId() == mCurrentScript->id()) {
            mPendingCommands.push_back([this, event]() {
                resetCurrentScript();
                informAboutEvent(event);
                if (!mScripts.empty()) {
                    mCurrentScript = mScripts.front();
                            mScripts.pop_front();
                            runCurrentScript();
                }
            });
            mAsync.send();
        } else if (mAutostartScript && finishEvent && finishEvent->scriptId() == mAutostartScript->id()) {
            mPendingCommands.push_back([this, event]() {
                resetAutostartScript();
                informAboutEvent(event);
            });
            mAsync.send();
        } else {
            informAboutEvent(event);
        }
    } else {
        informAboutEvent(event);
    }
}

void LuaScriptManager::informAboutEvent(ILuaEventSharedPtr event)
{
    for (auto listener : mEventListeners) {
        listener->luaEvent(event);
    }
}

void LuaScriptManager::onAsyncCommand()
{
    for (auto cmd : mPendingCommands) {
        cmd();
    }
    mPendingCommands.clear();
}

LuaScriptManager::~LuaScriptManager()
{
}

void LuaScriptManager::addLuaFunctionRegistrator(ILuaFunctionRegistrator* registrator)
{
    mFunctionRegistrators.push_back(registrator);
}

void LuaScriptManager::removeLuaFunctionRegistrator(ILuaFunctionRegistrator* registrator)
{
    mFunctionRegistrators.remove(registrator);
}
