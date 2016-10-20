/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luascriptmanager.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 18:12
 */

#ifndef LUASCRIPTMANAGER_H
#define LUASCRIPTMANAGER_H

#include "luascript.h"
#include "iluascripteventlistener.h"
#include "iluaeventforifhappenshandler.h"

#include "protocol/startnotifyinfo.h"


#include <string>
#include <list>

#include <ev++.h>

class ILuaEventForIfHappensHandler;

using namespace std;

class LuaScriptManager : public ILuaScriptEventsListener {
public:
    LuaScriptManager(const string &luaScriptPath);
    virtual ~LuaScriptManager();
    
    void startAutostartScript(const string &scriptName);

    void startScript(const string &scriptName, const StartNotifyInfo &info);    
    void cancelScript(const string &notifyId);

    void luaEvent(ILuaEventSharedPtr event) override;
    
    void addLuaScriptEventListener(ILuaScriptEventsListener *listener);
    void removeLuaScriptEventListener(ILuaScriptEventsListener *listener);
    
    void addIfHappensHandler(ILuaEventForIfHappensHandler *handler);
    void removeIfHappensHandler(ILuaEventForIfHappensHandler *handler);   

private:
    void onAsyncCommand();
    
    void informAboutEvent(ILuaEventSharedPtr event);
    
    void runCurrentScript();
    void resetCurrentScript();
    void resetAutostartScript();



private:
    const string mLuaScriptPath;
    list<LuaScriptSharedPtr> mScripts;
    LuaScriptSharedPtr mCurrentScript;
    LuaScriptSharedPtr mAutostartScript;
    list<ILuaScriptEventsListener*> mEventListeners;
    list<ILuaEventForIfHappensHandler*> mIfHappensHandlers;
    ev::async mAsync;
    list<function<void()> > mPendingCommands;
    




};

#endif /* LUASCRIPTMANAGER_H */

