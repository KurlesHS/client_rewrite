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

#include "auth/lua/iluafunctionregistrator.h"

#include <string>

using namespace std;

class LuaToGpioMediator : public ILuaFunctionRegistrator
{
public:
    LuaToGpioMediator();
    virtual ~LuaToGpioMediator();
    
    void registerFunction(sol::state* state) override;
    
    bool setGpioFuncImpl(const string &gpioId, const int state);
    int getGpioFuncImpl(const string &gpioId);
    
private:

};

#endif /* LUATOGPIOMEDIATOR_H */

