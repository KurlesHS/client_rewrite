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

#include <string>

class LuaScriptPrivate;

class ILuaPendingFunc {
public:

    virtual ~ILuaPendingFunc() {
    }
};

class ILuaScriptEventsListener 
{
public:
    virtual ~ILuaScriptEventsListener() {}
    virtual void luaEvent(ILuaEventSharedPtr event) = 0;
    
};

class LuaScript {
public:
    LuaScript(const std::string &scriptPath);
    virtual ~LuaScript();

    bool run();
    void cancel();

    std::string id() const;

    bool isValid() const;
    bool isFinished() const;
    std::string lastError() const;

    int priority() const;
    std::string group() const;
    
    void addLuaScriptEventListener(ILuaScriptEventsListener *listener);
    void removeLuaScriptEventListener(ILuaScriptEventsListener *listener);

    void onRelayChanged(const int relayNum, const int newState);

    std::string getStringVar(const std::string &varName);
    int getIntegerVar(const std::string &varName);
    float getFloatVar(const std::string &varName);

    int pendingIfHanpensFunctionCount() const;
    int relayChangedActiveConditionsCount() const;

private:
    friend class LuaScriptPrivate;
    LuaScriptPrivate *d;
};

#endif /* LUASCRIPT_H */


