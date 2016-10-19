/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inetworkaudioevents.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 9:40
 */

#ifndef INETWORKAUDIOEVENTS_H
#define INETWORKAUDIOEVENTS_H

class INetworkAudoEvents {
public:
    virtual ~INetworkAudoEvents() { }

    virtual void onFailToStartNetworkStream() = 0;
    virtual void onStartNetworkStream() = 0;
    virtual void onFinishNetworkStream() = 0;
    
};


#endif /* INETWORKAUDIOEVENTS_H */

