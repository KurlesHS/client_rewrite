/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IHardwareStatusesEvents.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 16:02
 */

#ifndef IHARDWARESTATUSESEVENTS_H
#define IHARDWARESTATUSESEVENTS_H

#include <string>

using namespace std;

class IHardwareStatusesEvents 
{
public :
    enum class HardwareStatus {
        Working, 
        Error,
        Unknown
    };
    
    enum class NotifyStatus {
        Wait, 
        Process,
        Error,
        Unknown
    };
public:    
    virtual ~IHardwareStatusesEvents() {}
    
    virtual void onHardwareStatusChanged(const string &hardwareId, const HardwareStatus &newSatus) = 0;
    virtual void onNotifyStatusChanged(const string &hardwareId, const NotifyStatus &newSatus) = 0;
    
    
private:

};

#endif /* IHARDWARESTATUSESEVENTS_H */

