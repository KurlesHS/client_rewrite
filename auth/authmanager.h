/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   authmanager.h
 * Author: Alexey
 *
 * Created on 27 сентября 2016 г., 21:58
 */

#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <unordered_map>
#include <string>

using namespace std;

#include "iauthmanager.h"

class AuthManager : public IAuthManager {
public:
    AuthManager();
    virtual ~AuthManager();    
    string getUserPassword(const string &userName) const override;
    
    void addUser(const string &userName, const string &userPassword);    
    
private:
    unordered_map<string, string> mUsersInfo;

};

#endif /* AUTHMANAGER_H */

