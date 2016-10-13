/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocolpacketparser.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 20:58
 */

#ifndef HARDWAREPROTOCOLPACKETPARSER_H
#define HARDWAREPROTOCOLPACKETPARSER_H

#include <vector>

#include "command.h"

using namespace std;

class HardwareProtocolPacketParser {
public:
    enum class Result : char {
        Ok,
        Incomplete,
        Error,
        Empty
    };
    
    HardwareProtocolPacketParser();    
    virtual ~HardwareProtocolPacketParser();    
    
    void addData(const char *data, const int len);    
    Command getCommand(Result &result);
    
private:
    void handleErrorCommand();
    void handleOkCommand();
    void handleIncompleteCommand();
    
private:    
    CommandParser mParser;
    vector<char> mBuffer;
};

#endif /* HARDWAREPROTOCOLPACKETPARSER_H */

