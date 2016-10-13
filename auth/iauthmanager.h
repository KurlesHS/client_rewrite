/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   iauthmanager.h
 * Author: Alexey
 *
 * Created on 12 октября 2016 г., 23:20
 */

#ifndef IAUTHMANAGER_H
#define IAUTHMANAGER_H

#include <string>

using namespace std;

class IAuthManager {
public:
    virtual ~IAuthManager() {}  
    virtual string getUserPassword(const string &userName) const = 0;

};

#endif /* IAUTHMANAGER_H */

