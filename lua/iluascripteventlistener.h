/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iluascripteventlistener.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 18:09
 */

#ifndef ILUASCRIPTEVENTLISTENER_H
#define ILUASCRIPTEVENTLISTENER_H

#include "iluaevent.h"

#include <string>

using namespace std;

class ILuaScriptEventsListener {
public:    
    virtual ~ILuaScriptEventsListener() {
    }
    virtual void luaEvent(ILuaEventSharedPtr event) = 0;
};

#endif /* ILUASCRIPTEVENTLISTENER_H */

