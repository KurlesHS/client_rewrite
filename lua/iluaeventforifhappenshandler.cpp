/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "iluaeventforifhappenshandler.h"

void ILuaEventForIfHappensHandler::addLuaScript(LuaScript* listener)
{
    mLuaScripts.push_back(listener);
}

void ILuaEventForIfHappensHandler::removeLuaScript(LuaScript* listener)
{
    mLuaScripts.remove(listener);
}

ILuaEventForIfHappensHandler::~ILuaEventForIfHappensHandler()
{
    
}