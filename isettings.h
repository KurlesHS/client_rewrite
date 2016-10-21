/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   isettings.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 20:03
 */

#ifndef ISETTINGS_H
#define ISETTINGS_H

#include <string>
#include <list>

using namespace std;

struct GpioSettings {
    enum class Direction {
        In,
        Out
    };
    string id;
    string name;
    Direction direction;
};

class ISettings {
public:
    virtual ~ISettings() { }
    
    virtual uint16_t port() = 0;
    
    virtual string scriptNameByNotifyCode(const string &notifyCode) = 0;
    virtual string fileServerUrl() = 0;
    virtual string autostartScript() = 0;
    virtual list<GpioSettings> gpioSettings() = 0;
    

};

#endif /* ISETTINGS_H */

