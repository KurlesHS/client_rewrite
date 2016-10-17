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

#include <algorithm>

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
            mCurrentScript->cancel();
        }
    }
}

void LuaScriptManager::startScript(const string& scriptName, const StartNotifyInfo &info)
{
    string scriptPath = mLuaScriptPath + "/" + scriptName + ".lua";
    auto script = make_shared<LuaScript>(scriptPath);
    script->setNotifyId(info.id);
    if (script->isValid()) {
        script->addLuaScriptEventListener(this);
        if (mCurrentScript) {
            if (mCurrentScript->priority() < script->priority()) {
                // если у пришедшего скрипта приоритет больше текущего, то выполнение
                // текущей задачи надо прервать
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
            mCurrentScript->run();
        }
    }
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
        mPendingCommands.push_back([this, event]() {
            mCurrentScript.reset();
            informAboutEvent(event);
            if (!mScripts.empty()) {
                mCurrentScript = mScripts.front();
                        mScripts.pop_front();
                        mCurrentScript->run();
            }
        });
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

