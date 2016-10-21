/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GpioManager.cpp
 * Author: Alexey
 * 
 * Created on 20 октября 2016 г., 23:23
 */

#include <bits/c++config.h>

#include "gpiomanager.h"
#include "thread/threadregister.h"

GpioManager::GpioManager() :
    mWorker(this)
{
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<GpioManager, &GpioManager::onAsync>(this);
    mAsync.start();
}

GpioManager::~GpioManager()
{
}

void GpioManager::start()
{
    mWorker.start();
}

int GpioManager::gpioState(const string& gpioId)
{
    return mWorker.gpioState(gpioId);
}

bool GpioManager::setGpioState(const string& gpioId, int state)
{
    return mWorker.setGpioState(gpioId, state);
}

void GpioManager::informAboutGpioStatusChanged(const string& gpioId, const int state)
{

}

void GpioManager::onAsync()
{
    auto copy = decltype(mPendingFunctions)();
    mMutex.lock();
    copy.swap(mPendingFunctions);
    mMutex.unlock();
    for (const auto &f : copy) {
        f();
    }
}

void GpioManager::onGpioStatusChanged(const string& gpioId, const int state)
{
    auto func = [this, gpioId, state] () {
        informAboutGpioStatusChanged(gpioId, state);
    };
    mMutex.lock();
    mPendingFunctions.push_back(func);
    mMutex.unlock();
    mAsync.send();
}