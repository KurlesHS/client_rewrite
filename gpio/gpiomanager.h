/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GpioManager.h
 * Author: Alexey
 *
 * Created on 20 октября 2016 г., 23:23
 */

#ifndef GPIOMANAGER_H
#define GPIOMANAGER_H

#include "gpiothread.h"

#include <ev++.h>

#include <functional>
#include <mutex>
#include <list>

using namespace std;

class GpioManager
{
public:
    GpioManager();
    virtual ~GpioManager();

    int gpioState(const string &gpioId);
    bool setGpioState(const string &gpioId, int state);

    void start();
    
    void onGpioStatusChanged(const string &gpioId, const int state);
    
private:
    void informAboutGpioStatusChanged(const string &gpioId, const int state);
    void onAsync();

private:
    GpioThread mWorker;
    mutex mMutex;
    ev::async mAsync;
    list<function<void()>> mPendingFunctions;

};

#endif /* GPIOMANAGER_H */

