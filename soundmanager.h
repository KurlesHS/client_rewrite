/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   soundmanager.h
 * Author: kurles
 *
 * Created on 17 октября 2016 г., 11:14
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <queue>
#include <list>

#include <ev++.h>

#include "isoundmanagereventslistener.h"

using namespace std;

struct SoundManagerFileInfo {
    string playbackId;
    string filePath;    
};


class SoundManager
{
public:
    SoundManager(const string &path);

    virtual ~SoundManager();
    
    void playbackByHash(string hash, const string &playbackId);
    void playbackByFilePath(const string &filepath, const string &playbackId);
    void cancelPlaybackFile(const string &playbackId);
    void addEventListener(ISoundManagerEventsListener *listener);
    void removeEventListener(ISoundManagerEventsListener *listener);
    
private:
    void updateFiles();
    void clearInfoAboutCurrentFile();
    
    void onAvPlayEvent(ev::io &io, int event);
    void startPlaybackCurrentFile();
    void tryToPlaybackNextFile();
    
    template<typename M, typename ... Args>
    void informAboutEvent(M m, Args ... args)
    {
        #define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
        for (auto listener : mEventListeners) {
            CALL_MEMBER_FN(listener, m)(std::forward<Args>(args)...);
        }
    }
    
private:
    const string mPath;
    list<ISoundManagerEventsListener*> mEventListeners;
    SoundManagerFileInfo mCurrentPlaybackFile;
    ev::io mAvPlayWatcher;
    list<SoundManagerFileInfo> mFilesToPlayback;
    bool mIsPlaybackStarted;
};

#endif /* SOUNDMANAGER_H */

