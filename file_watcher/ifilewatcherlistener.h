/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ifilewatcherlistener.h
 * Author: Alexey
 *
 * Created on 20 марта 2017 г., 19:08
 */

#ifndef IFILEWATCHERLISTENER_H

#include <string>

class IFileWatcherListener {
public:
    virtual ~IFileWatcherListener() {}
    
    virtual void onNewFile(const std::string &result) = 0;
};
#define IFILEWATCHERLISTENER_H



#endif /* IFILEWATCHERLISTENER_H */

