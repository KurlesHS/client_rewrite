/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileWatcher.cpp
 * Author: Alexey
 * 
 * Created on 20 марта 2017 г., 18:08
 */

#include "filewatcher.h"

#include <unistd.h>
#include <stddef.h>

#include <sys/inotify.h>
#include <sys/ioctl.h>

#include <logger.h>
#include <thread/threadregister.h>
#include <fcntl.h>

FileWatcher::FileWatcher(const string &eventFilesDir, bool const readContent, const bool tryToErase) :
    mEventFilesDir(eventFilesDir),
    mReadContent(readContent),
    mTryToErase(tryToErase),
    mINotifyId(-1),
    mDirId(-1)
{
    
}

void FileWatcher::start()
{
    if (mEventFilesDir.size() == 0) {
        return;
    }
    mINotifyId = inotify_init();
    if (mINotifyId < 0) {
        return;
    }
    mDirId = inotify_add_watch(mINotifyId, mEventFilesDir.data(), IN_CLOSE_WRITE);

    if (mDirId < 0) {
        return;
    }
    mWatcher.set(ThreadRegister::loopForCurrentThread());
    mWatcher.set<FileWatcher, &FileWatcher::onNewEvent>(this);
    mWatcher.start(mINotifyId, ev::READ);
}


void FileWatcher::addListener(IFileWatcherListener* listener)
{
    mListeners.push_back(listener);
}

void FileWatcher::removeListener(IFileWatcherListener* listener)
{
    mListeners.remove(listener);
}

FileWatcher::~FileWatcher()
{
    if (mDirId >= 0) {
        inotify_rm_watch(mINotifyId, mDirId);
    }
    if (mINotifyId >= 0) {
        close(mINotifyId);
    }
}

void FileWatcher::onNewEvent(ev::io& watcher, int flag)
{
    (void) watcher;
    if (flag & ev::ERROR) {
        errorCallback();
    } else if (flag & ev::READ) {
        readCallback();
    }
}

void FileWatcher::errorCallback()
{

}

void FileWatcher::readCallback()
{
    int count;
    ioctl(mINotifyId, FIONREAD, &count);
    if (count < 0) {
        return;
    }
    int currentSize = mReadBuff.size();
    mReadBuff.resize(currentSize + count);
    ssize_t nRead = read(mINotifyId, mReadBuff.data() + currentSize, count);
    if (nRead < 0) {
        mReadBuff.clear();
        return;
    }
    int delta = count - nRead;
    if (delta > 0) {
        mReadBuff.resize(mReadBuff.size() - delta);
    }

    while (mReadBuff.size()) {
        /* Разбираем события и помещаем их в очередь. */
        struct inotify_event *pEvent = (struct inotify_event *) mReadBuff.data();
        size_t event_size = offsetof(struct inotify_event, name) + pEvent->len;
        if (event_size > mReadBuff.size()) {
            break;
        }
        string result = mEventFilesDir;
        if (result.size()) {
            if (result[result.size() - 1] != '/') {
                result += '/';
            }
            result += string(pEvent->name);

            char buff[0x100];
            buff[0x00] = 0x00;
            if (mReadContent) {

                FILE *fd = fopen(result.data(), "r");
                if (fd != NULL) {
                    size_t r = fread(buff, 1, 0x100 - 1, fd);                    
                    buff[r] = 0x00;
                }
                fclose(fd);
            }

            if (mTryToErase) {
                unlink(result.data());
            }
            if (mReadContent) {
                result = string(buff);
            }
            
            if (result.size()) {
                for (const auto &lisener : mListeners) {
                    lisener->onNewFile(result);
                }
            }
        }
        mReadBuff.erase(mReadBuff.begin(), mReadBuff.begin() + event_size);
    }
}