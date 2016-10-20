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

using namespace std;

class ISettings {
public:
    virtual ~ISettings() { }
    
    virtual uint16_t port() = 0;
    
    virtual string scriptNameByNotifyCode(const string &notifyCode) = 0;
    virtual string fileServerUrl() = 0;
    virtual string autostartScript() = 0;
    

};

#endif /* ISETTINGS_H */

