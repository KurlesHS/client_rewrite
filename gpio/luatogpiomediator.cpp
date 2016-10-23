/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LuaToGpioMediator.cpp
 * Author: kurles
 * 
 * Created on 21 октября 2016 г., 16:18
 */

#include "luatogpiomediator.h"

#include "sol2/sol2.hpp"

#include "lua/luascriptmanager.h"
#include "gpiomanager.h"
#include "uuid.h"

#include <iostream>

LuaToGpioMediator::LuaToGpioMediator(LuaScriptManager* luaManager, GpioManager* gpioManager) :
    mLuaManager(luaManager),
    mGpioManager(gpioManager)
{
    mLuaManager->addLuaFunctionRegistrator(this);
    mLuaManager->addIfHappensHandler(this);
    mGpioManager->addEventListener(this);
}

LuaToGpioMediator::~LuaToGpioMediator()
{
    mLuaManager->removeLuaFunctionRegistrator(this);
}

int LuaToGpioMediator::getGpioFuncImpl(const string& gpioId)
{
    return mGpioManager->gpioState(gpioId);
}

bool LuaToGpioMediator::setGpioFuncImpl(const string& gpioId, const int state)
{
    return mGpioManager->setGpioState(gpioId, state);
}

void LuaToGpioMediator::registerFunction(sol::state* state)
{
    auto x = this;
    state->set_function("get_gpio", &LuaToGpioMediator::getGpioFuncImpl, x);
    state->set_function("set_gpio", &LuaToGpioMediator::setGpioFuncImpl, x);
}

void LuaToGpioMediator::registerCommand(sol::state& state)
{
    auto x = this;
    state.set_function("gpio_state_changed", &LuaToGpioMediator::gpioStateChangedFuncImpl, x);
}

void LuaToGpioMediator::ifHappensExpiried(const string& ifHappensId)
{    
    mPendingEvents.remove_if([ifHappensId](const GpioStateChangedParamHolder holder) {
       return  ifHappensId == holder.ifHappensId;
    });    
}

void LuaToGpioMediator::gpioStateChanged(const string& gpioId, const int state)
{
    auto &lst = mPendingEvents;
    list<string> happened;
    for (auto it = lst.begin(); it != lst.end();) {
        bool gpioIdIsSame = true;
        bool stateIsSame = true;
        if (it->hasGpioId) {
            gpioIdIsSame = it->gpioId == gpioId;
        }
        if (it->hasState) {
            stateIsSame = it->state == state;
        }
        if (gpioIdIsSame && stateIsSame) {
            auto ifHappensId = it->ifHappensId;
            it = lst.erase(it);
            happened.push_back(ifHappensId);            
            continue;
        }         
        ++it;
    }
    
    for (const auto &id : happened) {
        ifHappensHappened(id, gpioId, state);
    }
}

string LuaToGpioMediator::gpioStateChangedFuncImpl(const sol::object& gpioId, const sol::object &state)
{
    GpioStateChangedParamHolder holder;
    holder.ifHappensId = Uuid::createUuid().toString();
    if (gpioId.is<string>()) {
        holder.hasGpioId = true;
        holder.gpioId = gpioId.as<string>();
    } else {
        holder.hasGpioId = false;
    }
    
    if (state.is<int>()) {
        holder.hasState = true;
        holder.state = state.as<int>();
    } else {
        holder.hasState = false;
    }
    mPendingEvents.push_back(holder);
    return holder.ifHappensId;
}



