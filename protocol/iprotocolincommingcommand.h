/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iprotocolincommingcommand.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 23:33
 */

#ifndef IPROTOCOLINCOMMINGCOMMAND_H
#define IPROTOCOLINCOMMINGCOMMAND_H

#include <vector>

using namespace std;

class IProtocolIncommingCommand {
public:
    virtual ~IProtocolIncommingCommand() { }
    
    virtual void doWork(const vector<char> &payload) = 0;
    virtual vector<char> payload() const = 0;
    virtual bool isNeedAuth() const { return true; }
};

#endif /* IPROTOCOLINCOMMINGCOMMAND_H */

