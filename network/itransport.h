/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   itransport.h
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 21:15
 */

#ifndef ITRANSPORT_H
#define ITRANSPORT_H

#include <string>
#include <memory>

#include "safe_list.h"

using namespace std;

class ITransport;

using ITransportSharedPrt = std::shared_ptr<ITransport>;

class ITransportEvents {
public:    
    virtual ~ITransportEvents();    
    virtual void readyRead(ITransport *self) = 0;
    virtual void disconnected(ITransport *self) = 0;
};

class ITransport {
public:

    virtual ~ITransport();

    virtual void close() = 0;

    virtual int read(char *buff, int len) = 0;
    virtual int write(const char *buff, int len) = 0;
    virtual int bytesAvailable() const = 0;

    virtual string peerAddress() const = 0;
    
    void addTransportEventsListener(ITransportEvents *listener);
    void removeTransportEventsListener(ITransportEvents *listener);  
    
protected:
    void emit_readyRead();
    void emit_disonnected();
  
private:
    safe_list<ITransportEvents*> mEventListeners;

};



#endif /* ITRANSPORT_H */

