/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 21:06
 */

#include <cstdlib>
#include <iostream>

#include <ev++.h>

#include "thread/threadregister.h"

using namespace std;

#include "fortest.h"

int main(int argc, char** argv)
{
    ev::default_loop mainLoop;
    ThreadRegister::registerThread(mainLoop);
    ForTest test;
    test.run();
    
    mainLoop.run();
    
    
    return 0;
}

