/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GpioThread.h
 * Author: Alexey
 *
 * Created on 21 октября 2016 г., 3:05
 */

#ifndef GPIOTHREAD_H
#define GPIOTHREAD_H

#include <thread>

using namespace std;

class GpioThread {
public:
    GpioThread();
    virtual ~GpioThread();
    
    void start();
    
    void threadProc();
    
private:
    thread mThread;

};

#endif /* GPIOTHREAD_H */

