/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LuaToGpioMediator.h
 * Author: kurles
 *
 * Created on 21 октября 2016 г., 16:18
 */

#ifndef LUATOGPIOMEDIATOR_H
#define LUATOGPIOMEDIATOR_H

#include "lua/iluafunctionregistrator.h"
#include "lua/iluaeventforifhappenshandler.h"
#include "gpiomanager.h"
#include <string>
#include <functional>
#include "sol2/sol2.hpp"

class LuaScriptManager;


using namespace std;

struct GpioStateChangedParamHolder {
    string ifHappensId;
    bool hasGpioId;
    string gpioId;
    bool hasState;
    int state;
};

class LuaToGpioMediator : public ILuaFunctionRegistrator, public ILuaEventForIfHappensHandler, public IGpioEvents
{
public:
    LuaToGpioMediator(LuaScriptManager *luaManager, GpioManager *gpioManager);
    virtual ~LuaToGpioMediator();
    
    void registerFunction(sol::state* state) override;
    
    bool setGpioFuncImpl(const string &gpioId, const int state);
    int getGpioFuncImpl(const string &gpioId);
    
    void ifHappensExpiried(const string& ifHappensId) override;
    void registerCommand(sol::state& state) override;
    
    void gpioStateChanged(const string& gpioId, const int state) override;
    
private:
    string gpioStateChangedFuncImpl(const sol::object &gpioId, const sol::object &state);
    
private:
    LuaScriptManager *mLuaManager;
    GpioManager *mGpioManager;
    list<GpioStateChangedParamHolder> mPendingEvents;
    list<function<void()> > mPendingFunc;

};

#endif /* LUATOGPIOMEDIATOR_H */

