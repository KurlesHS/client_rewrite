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

MainHandler::MainHandler()
{
}

MainHandler::~MainHandler()
{
}

void MainHandler::run()
{
    mFactory.startListen(55555);
}


