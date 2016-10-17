/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   isoundmanagereventslistener.h
 * Author: Alexey
 *
 * Created on 18 октября 2016 г., 0:01
 */

#ifndef ISOUNDMANAGEREVENTSLISTENER_H
#define ISOUNDMANAGEREVENTSLISTENER_H

#include <string>

using namespace std;

class ISoundManagerEventsListener 
{
public:
    virtual ~ISoundManagerEventsListener() { }
    
    virtual void fileNotFound(const string &playbackId) = 0;
    virtual void playbackStarted(const string &playbackId) = 0;
    virtual void playbackFinished(const string &playbackId, const bool isCanceled) = 0;
};

#endif /* ISOUNDMANAGEREVENTSLISTENER_H */

