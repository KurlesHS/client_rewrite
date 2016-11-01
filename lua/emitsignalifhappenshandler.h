/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EmitSignalIfHappensHandler.h
 * Author: Alexey
 *
 * Created on 1 ноября 2016 г., 19:43
 */

#ifndef EMITSIGNALIFHAPPENSHANDLER_H
#define EMITSIGNALIFHAPPENSHANDLER_H

#include "iluaeventforifhappenshandler.h"

#include <list>

using namespace std;



class EmitSignalIfHappensHandler : public ILuaEventForIfHappensHandler {
    struct Holder {
        string ifHappensId;
        bool hasSignalName;
        string signalName;
    };
public:
    EmitSignalIfHappensHandler();
    virtual ~EmitSignalIfHappensHandler();
    void ifHappensExpiried(const string& ifHappensId) override;
    void registerCommand(sol::state& state) override;
    
    void incommingSignal(const string &signalName);
    void luaEvent(ILuaEventSharedPtr event);

private:
    string signalFuncImpl(const sol::object& signalName);
    
private:
    list<Holder> mPendingEvents;
};

#endif /* EMITSIGNALIFHAPPENSHANDLER_H */

