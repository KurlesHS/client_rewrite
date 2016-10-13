/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pingprotocolincommingcommand.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 23:50
 */

#ifndef PINGPROTOCOLINCOMMINGCOMMAND_H
#define PINGPROTOCOLINCOMMINGCOMMAND_H

#include "iprotocolincommingcommand.h"

class PingProtocolIncommingCommand : public IProtocolIncommingCommand {
public:
    PingProtocolIncommingCommand();
    virtual ~PingProtocolIncommingCommand();
    vector<char> payload() const override;
    void doWork(const vector<char>& payload) override;
};

#endif /* PINGPROTOCOLINCOMMINGCOMMAND_H */

