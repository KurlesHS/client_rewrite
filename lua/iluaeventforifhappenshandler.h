/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iluaeventforifhappenshandler.h
 * Author: kurles
 *
 * Created on 18 октября 2016 г., 8:37
 */

#ifndef ILUAEVENTFORIFHAPPENSHANDLER_H
#define ILUAEVENTFORIFHAPPENSHANDLER_H

#include <string>
#include <list>

#include <sol2/sol2.hpp>

#include "luascript.h"


using namespace std;

class LuaScript;

class ILuaEventForIfHappensHandler
{
public:

    virtual ~ILuaEventForIfHappensHandler();

    virtual void registerCommand(sol::state &state) = 0;
    virtual void ifHappensExpiried(const string &ifHappensId) = 0;

    void addLuaScript(LuaScript *listener);

    void removeLuaScript(LuaScript *listener);

protected:

    template<typename ...Args>
    void ifHappensHappened(const string &ifHappensId, Args ... args)
    {
        for (auto luaScript : mLuaScripts) {
            luaScript->ifHappensHappened(ifHappensId, std::forward<Args>(args)...);
        }
    }

private:
    list<LuaScript*> mLuaScripts;
};

#endif /* ILUAEVENTFORIFHAPPENSHANDLER_H */

