/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   itimer.h
 * Author: Alexey
 *
 * Created on 28 июля 2016 г., 21:13
 */

#ifndef ITIMER_H
#define ITIMER_H

#include <functional>
#include <memory>

#include "safe_list.h"

class ITimer;

using namespace std;
using ITimerSharedPtr = std::shared_ptr<ITimer>;

using TimerCallback = function<void(ITimer*)>;

class ITimerFactory {
public:
    virtual ~ITimerFactory();
    virtual ITimerSharedPtr getTimer(const uint32_t interval=0) = 0;
};

class ITimerEvents {
public:
    virtual ~ITimerEvents();
    
    virtual void timeout(ITimer *self) = 0;
};

class ITimer {
public:
    ITimer(const uint32_t &interval);    
    virtual ~ITimer();
    
    void addTimerEventListener(ITimerEvents *listener);
    void removeTimerEventListener(ITimerEvents *listener);
    
    void addCallbackFunction(TimerCallback func);
    void removeCallbackFunctions();
    
    uint32_t interval() const;
    void setInterval(uint32_t mInterval);
    bool isSingleShot() const;
    void setSingleShot(bool singleshot);
    
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isStarted() const = 0;
    
    void start(const uint32_t interval);
    
protected:
    void emit_timeout();
    
    
private:
    uint32_t mInterval;
    bool mIsSingleShot;
    safe_list<ITimerEvents*> mEventListeners;
    safe_list<TimerCallback> mTimerCallbackFunc;    
};

#endif /* ITIMER_H */

