/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileWatcher.h
 * Author: Alexey
 *
 * Created on 20 марта 2017 г., 18:08
 */

#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <vector>
#include <string>
#include <list>

#include <ev++.h>


#include "ifilewatcherlistener.h"

using namespace std;

class FileWatcher {
public:
    FileWatcher(const string &eventFilesDir, bool const readContent, const bool tryToErase);
    virtual ~FileWatcher();
    
    void start();
    
    void addListener(IFileWatcherListener *listener);
    void removeListener(IFileWatcherListener *listener);   
    
private:
    void onNewEvent(ev::io &watcher, int flag);
    void errorCallback();
    void readCallback();
    
private:
    ev::io mWatcher;
    const string mEventFilesDir;
    const bool mReadContent;
    const bool mTryToErase;
    std::list<IFileWatcherListener*> mListeners;
    std::vector<char> mReadBuff;
    int mINotifyId;
    int mDirId;
};

#endif /* FILEWATCHER_H */

