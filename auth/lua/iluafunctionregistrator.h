/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ILuaFunctionRegistrator.h
 * Author: kurles
 *
 * Created on 21 октября 2016 г., 15:54
 */

#ifndef ILUAFUNCTIONREGISTRATOR_H
#define ILUAFUNCTIONREGISTRATOR_H

namespace sol {
    struct state;
}

class ILuaFunctionRegistrator
{
public:
    ILuaFunctionRegistrator();
    virtual ~ILuaFunctionRegistrator();
    virtual void registerFunction(sol::state *state) = 0;
    
private:

};

#endif /* ILUAFUNCTIONREGISTRATOR_H */

