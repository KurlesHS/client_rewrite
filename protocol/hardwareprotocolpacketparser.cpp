/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hardwareprotocolpacketparser.cpp
 * Author: Alexey
 * 
 * Created on 12 октября 2016 г., 20:58
 */

#include <cstring>

#include "hardwareprotocolpacketparser.h"

HardwareProtocolPacketParser::HardwareProtocolPacketParser()
{
}

HardwareProtocolPacketParser::~HardwareProtocolPacketParser()
{
}

void HardwareProtocolPacketParser::addData(const char* data, const int len)
{
    int offset = mBuffer.size();
    mBuffer.resize(offset + len);
    memcpy(mBuffer.data() + offset, data, len);
}

Command HardwareProtocolPacketParser::getCommand(HardwareProtocolPacketParser::Result &result)
{   
    result = Result::Empty;
    Command cmd;
    if (!mBuffer.empty()) {
        auto res = mParser.parse(mBuffer.data(), mBuffer.size());
        switch (res) {
            case CommandParser::Result::Error:
                result = Result::Error;
                
                break;
            case CommandParser::Result::Incomplete:
                result = Result::Incomplete;
                break;
            case CommandParser::Result::Ok:
                result = Result::Ok;                
                cmd = mParser.cmd();
                break;
        }
    }
    return cmd;
}

void HardwareProtocolPacketParser::handleErrorCommand()
{
    /* при ошибке очищаем буфер */
    mBuffer.clear();
}

void HardwareProtocolPacketParser::handleIncompleteCommand()
{
    /* если команда неполная - ничего не делаем*/
}

void HardwareProtocolPacketParser::handleOkCommand()
{
    /* если же команда корректная - откорректировать буфер */
    auto commandLenght = mParser.currentCommandTotalLenght();
    /* если размер буфера меньше (не должно такого быть) 
     * или равен длинне команды - просто очищаем буфер */
    if (mBuffer.size() <= commandLenght) {
        mBuffer.clear();
    } else {
        /* если размер буфера больше, чем размер команды - 
         * удаляем из буфера данные, относящияеся к этой команде */
        mBuffer.erase(mBuffer.begin(), mBuffer.begin() + commandLenght);        
    }
}