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


class GpioManager {
public:
    GpioManager();
    virtual ~GpioManager();
    
    void start();
private:
    GpioThread mWorker;

};

#endif /* GPIOMANAGER_H */

