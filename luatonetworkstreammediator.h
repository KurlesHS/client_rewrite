/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luatonetworkstreammediator.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 14:29
 */

#ifndef LUATONETWORKSTREAMMEDIATOR_H
#define LUATONETWORKSTREAMMEDIATOR_H


#include "lua/iluascripteventlistener.h"
#include "networkaudio/inetworkaudioevents.h"
#include "networkaudio/networkaudioifhappenshandler.h"


class LuaScriptManager;
class NetworkAudioManager;

class LuaToNetworkStreamMediator : public ILuaScriptEventsListener, public INetworkAudoEvents
{
public:
    LuaToNetworkStreamMediator(LuaScriptManager *luaManager, NetworkAudioManager *networkAudioManager);

    virtual ~LuaToNetworkStreamMediator();
    
    void luaEvent(ILuaEventSharedPtr event) override;
    
    void onFailToStartNetworkStream() override;
    void onFinishNetworkStream() override;
    void onStartNetworkStream() override;
    
private:
    void handlePlayNetworkAudioRequest(ILuaEventSharedPtr event);
    void handleStopNetworkAudioRequest(ILuaEventSharedPtr event);
    
private:
    LuaScriptManager *mLuaManager;
    NetworkAudioManager *mNetworkAudioManager;
    NetworkAudioIfHappensHandler mIfHappensHandler;

};

#endif /* LUATONETWORKSTREAMMEDIATOR_H */

