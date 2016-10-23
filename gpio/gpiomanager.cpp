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
#include <iostream>

#include "gpiomanager.h"
#include "thread/threadregister.h"
#include "logger.h"
#include "ioc/resolver.h"

GpioManager::GpioManager() :
    mWorker(this)
{
    for (auto gpio : di_inject(ISettings)->gpioSettings()) {
        if (gpio.direction == GpioSettings::Direction::In) {
            gpio.currentValue = -2;
            gpio.prevValue = -2;
            mInputGpios.push_back(gpio);
        }
    }
    mAsync.set(ThreadRegister::loopForCurrentThread());
    mAsync.set<GpioManager, &GpioManager::onAsync>(this);
    mAsync.start();
    mTimer.set(ThreadRegister::loopForCurrentThread());
    mTimer.set<GpioManager, &GpioManager::onTimer>(this);
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
    //Logger::msg("!!!gpio: state of gpio pin '%s' change to '%d'", gpioId.data(), state);
    if (mTimer.is_active()) {
        mTimer.stop();
    }            
    for (auto it = mInputGpios.begin(); it != mInputGpios.end(); ++it) {
        if (it->id == gpioId) {
            it->currentValue = state;
        }
    }
    mTimer.start(.05);
}

void GpioManager::onTimer()
{   
    for (auto it = mInputGpios.begin(); it != mInputGpios.end(); ++it) {
        if (it->currentValue != it->prevValue) {
            it->prevValue = it->currentValue;
            Logger::msg("gpio: gpio '%s' (%s) state changed to %d",
                                    it->id.data(), it->name.data(), it->currentValue);
            for (const auto listener : mEventListenres) {                
                listener->gpioStateChanged(it->id, it->currentValue);
            }
        }
    }
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

void GpioManager::addEventListener(IGpioEvents* listener)
{
    mEventListenres.push_back(listener);
}

void GpioManager::removeEventListener(IGpioEvents* listener)
{
    mEventListenres.remove(listener);
}
