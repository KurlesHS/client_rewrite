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
#include <mutex>

using namespace std;

class GpioManager;

class GpioThread
{
    struct GpioInfo;

public:
    GpioThread(GpioManager *manager);
    virtual ~GpioThread();

    void start();

    void threadProc();
    static string pathForGpioNum(const int pinNum);
    static bool writeTo(const string &path, const string &data);
    static string readFrom(const string &path, bool *ok = 0);

    int gpioState(const string &gpioId);
    bool setGpioState(const string &gpioId, int state);

private:
    GpioThread::GpioInfo * gpioInfo(const string &gpioId);
    void threadFunc();
        
private:
    GpioManager *mManager;
    thread mThread;
    GpioThread::GpioInfo *mGpioInfoList;
    mutex mMutex;
};

#endif /* GPIOTHREAD_H */

