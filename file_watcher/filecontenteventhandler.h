/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileContentEventHandler.h
 * Author: Alexey
 *
 * Created on 20 марта 2017 г., 20:53
 */

#ifndef FILECONTENTEVENTHANDLER_H
#define FILECONTENTEVENTHANDLER_H



#include <lua/iluaeventforifhappenshandler.h>

#include "filewatcher.h"
#include "ifilewatcherlistener.h"

class FileContentEventHandlerPrivate;

class FileContentEventHandler : public ILuaEventForIfHappensHandler, public IFileWatcherListener {
public:
    FileContentEventHandler(FileWatcher *fileWatcher);
    virtual ~FileContentEventHandler();
    
    void ifHappensExpiried(const string& ifHappensId) override;
    void registerCommand(sol::state& state) override;
    
    void onNewFile(const std::string& result) override;
    
private:
    string incomingFileContentImpl(const sol::object& data);


private:
    FileContentEventHandlerPrivate *d;
};

#endif /* FILECONTENTEVENTHANDLER_H */

