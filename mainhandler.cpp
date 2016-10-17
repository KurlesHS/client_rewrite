/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainhandler.cpp
 * Author: Alexey
 * 
 * Created on 13 октября 2016 г., 1:07
 */

#include "mainhandler.h"

#include "protocol/startnotifyincommingcommandhandler.h"

MainHandler::MainHandler() :
    mSoundManager("/home/kurles/develop/orange_files")
{
    mSoundManager.playbackByHash("7626e4d70bf6a25634bfcbd377274de40208f4be313832e9db2dc4fb", "id1");
}

MainHandler::~MainHandler()
{
    
}

void MainHandler::run()
{
    mFactory.startListen(55555);
}


