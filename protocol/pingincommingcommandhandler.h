/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pingincommingcommandhandler.h
 * Author: Alexey
 *
 * Created on 15 октября 2016 г., 14:06
 */

#ifndef PINGINCOMMINGCOMMANDHANDLER_H
#define PINGINCOMMINGCOMMANDHANDLER_H

#include "iincommingcommandhandler.h"

class PingIncommingCommandHandler : public IIncommingCommandHandler {
public:
    PingIncommingCommandHandler();    
    virtual ~PingIncommingCommandHandler();
    
    uint16_t command() const override;
    bool handleCommand(const vector<char>& payload) override;
    


private:
    

};

#endif /* PINGINCOMMINGCOMMANDHANDLER_H */

