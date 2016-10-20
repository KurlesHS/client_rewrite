/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luascript.h
 * Author: Alexey
 *
 * Created on 9 июля 2016 г., 18:01
 */



#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "iluaevent.h"
#include "iluascripteventlistener.h"

#include "protocol/startnotifyinfo.h"

#include <string>
#include <memory>
#include <list>

#include "sol2/sol2.hpp"

class LuaScriptPrivate;
class ILuaEventForIfHappensHandler;

class ILuaPendingFunc
{
public:

    virtual ~ILuaPendingFunc();
};

class LuaScript;

using LuaScriptSharedPtr = std::shared_ptr<LuaScript>;
using namespace std;

class LuaScript
{
public:
    LuaScript(const std::string &scriptPath);
    virtual ~LuaScript();
    
    void setNotifyInfo(const StartNotifyInfo &info);
    const StartNotifyInfo &notifyInfo() const;

    bool run();
    void cancel();

    sol::state &luaState();

    std::string id() const;

    std::string notifyId() const;
    void setNotifyId(const std::string &notifyId);

    void setScriptName(const string &name);
    string scriptName() const;
    

    bool isValid() const;
    bool isFinished() const;
    std::string lastError() const;

    int priority() const;
    void setPriority(const int priority);
    std::string group() const;

    void addLuaScriptEventListener(ILuaScriptEventsListener *listener);
    void removeLuaScriptEventListener(ILuaScriptEventsListener *listener);

    void onRelayChanged(const int relayNum, const int newState);

    std::string getStringVar(const std::string &varName);
    int getIntegerVar(const std::string &varName);
    float getFloatVar(const std::string &varName);

    int pendingIfHanpensFunctionCount() const;
    int relayChangedActiveConditionsCount() const;

    template<typename ... Args>
    void ifHappensHappened(const string& ifHappensId, Args ... args)
    {   
        for (auto f : ifHappensOkFunc(ifHappensId)) {
            f(std::forward<Args>(args)...);
        }            
        removeIfHappens(ifHappensId, true, true);
    }
    
private:
    list<sol::function> ifHappensOkFunc(const string& ifHappensId);
    void removeIfHappens(const string& ifHappensId, const bool checkIsfinished, const bool forceAsync);    

private:
    friend class LuaScriptPrivate;
    LuaScriptPrivate *d;
};

#endif /* LUASCRIPT_H */