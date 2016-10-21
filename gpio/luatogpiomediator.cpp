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

LuaToGpioMediator::LuaToGpioMediator()
{
}

LuaToGpioMediator::~LuaToGpioMediator()
{
}


int LuaToGpioMediator::getGpioFuncImpl(const string& gpioId)
{

}

void LuaToGpioMediator::registerFunction(sol::state* state)
{
    
}

bool LuaToGpioMediator::setGpioFuncImpl(const string& gpioId, const int state)
{

}
