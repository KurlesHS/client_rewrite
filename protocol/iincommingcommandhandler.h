/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iincommingcommandhandler.h
 * Author: kurles
 *
 * Created on 13 октября 2016 г., 9:38
 */

#ifndef IINCOMMINGCOMMANDHANDLER_H
#define IINCOMMINGCOMMANDHANDLER_H

#include <vector>

#include "stdint.h"

using namespace std;

class IIncommingCommandHandler {
public:
    IIncommingCommandHandler() = default;    
    virtual ~IIncommingCommandHandler() { } 
    
    virtual uint16_t command() const = 0;
    virtual bool handleCommand(const vector<char> &payload) = 0;
};

#endif /* IINCOMMINGCOMMANDHANDLER_H */

