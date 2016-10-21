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

#include "gpiomanager.h"

GpioManager::GpioManager()
{
}

GpioManager::~GpioManager()
{
}

void GpioManager::start()
{
    mWorker.start();
}

