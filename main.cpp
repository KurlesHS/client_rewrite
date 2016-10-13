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
#include "timer/timerfactory.h"
#include "ioc/resolver.h"
#include "fortest.h"
#include "auth/iauthmanager.h"
#include "auth/authmanager.h"
#include "mainhandler.h"

using namespace std;

int main(int argc, char** argv)
{
    auto authManager = new AuthManager();
    authManager->addUser("admin", "admin");
    di_register_type(ITimerFactory, TimerFactory,)
    di_register_object(IAuthManager, authManager)
    di_inject_variable(IAuthManager, auth);
    
    auth->getUserPassword("admin");
            
    ev::default_loop mainLoop;
    ThreadRegister::registerThread(mainLoop);
    
#if 0
    ForTest test;
    test.run();
#endif
    
    MainHandler m;
    m.run();
    
    mainLoop.run();
    
    di_unregister_type(ITimerFactory)
    di_unregister_type(IAuthManager)    
    
    return 0;
}

