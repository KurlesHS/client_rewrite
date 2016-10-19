/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   networkaudioifhappenshandler.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 14:41
 */

#ifndef NETWORKAUDIOIFHAPPENSHANDLER_H
#define NETWORKAUDIOIFHAPPENSHANDLER_H

#include <string>
#include <list>

#include "lua/iluaeventforifhappenshandler.h"

using namespace std;

class NetworkAudioIfHappensHandler : public ILuaEventForIfHappensHandler
{
public:
    NetworkAudioIfHappensHandler();
    
    virtual ~NetworkAudioIfHappensHandler();
    
    void ifHappensExpiried(const string& ifHappensId) override;    
    void registerCommand(sol::state& state) override;
    
    void onNetworkAudioFailedToStart();
    void onNetworkAudioPlaybackStarted();
    void onNetworkAudioPlaybackFinished();

private:
    string networkAudioFailedToStart();
    string networkAudioPlaybackStarted();
    string networkAudioPlaybackFinished();
    
private:
    list<string> mFailedPendingEvents;
    list<string> mStartedPendingEvents;
    list<string> mFinishedPendingEvents;
};

#endif /* NETWORKAUDIOIFHAPPENSHANDLER_H */

