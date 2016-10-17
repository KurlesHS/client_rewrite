/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   soundmanager.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 11:14
 */

#include "soundmanager.h"

#include "thread/threadregister.h"

#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <openssl/sha.h>

#include <ev++.h>

#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>

string getHashByFilename(const string &name)
{
    regex re(R"(\b([A-Fa-f\d]{32,64})_(.+)\b)");
    smatch match;
    if (regex_search(name, match, re)) {
        return match[1];
    }
    return string();
}

SoundManager::~SoundManager()
{
}

SoundManager::SoundManager(const string& path) :
    mPath(path)
{
    updateFiles();
    mAvPlayWatcher.set(ThreadRegister::loopForCurrentThread());
    mAvPlayWatcher.set<SoundManager, &SoundManager::onAvPlayEvent>(this);
}

void SoundManager::updateFiles()
{
    char buff[0x1000];
    DIR *dfd = opendir(mPath.data());
    struct dirent *dp;

    if (dfd == NULL) {
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        struct stat stbuf;
        string fileName(dp->d_name);
        string filePath = mPath + "/" + fileName;
        if (stat(filePath.data(), &stbuf) == -1) {
            continue;
        }

        if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
            // Skip directories
            continue;
        } else {
            auto hash = getHashByFilename(fileName);
            if (hash.empty()) {
                // надо переименовать по шаблону
                FILE *f = fopen(filePath.data(), "rb");
                if (f) {
                    rewind(f);
                    SHA256_CTX ctx;
                    SHA224_Init(&ctx);
                    while (true) {
                        int sizeOfBuff = sizeof (buff);
                        int len = fread(buff, 1, sizeOfBuff, f);
                        if (len <= 0) {
                            break;
                        }
                        SHA224_Update(&ctx, buff, len);
                    }
                    fclose(f);
                    SHA224_Final(reinterpret_cast<unsigned char*> (buff), &ctx);
                    string strHash;
                    strHash.resize(SHA224_DIGEST_LENGTH * 2);
                    for (int i = 0; i < SHA224_DIGEST_LENGTH; i++) {
                        static const char hexDigits[] = "0123456789abcdef";
                        int hight = (buff[i] >> 4) & 0x0f;
                        int low = buff[i] & 0x0f;
                        strHash[i * 2] = hexDigits[hight];
                        strHash[i * 2 + 1] = hexDigits[low];
                    }
                    auto newFilePath = mPath + "/" + strHash + "_" + fileName;
                    rename(filePath.data(), newFilePath.data());
                } else {
                    continue;
                }

            }
            cout << filePath << ": " << getHashByFilename(fileName) << endl;
        }
    }
    closedir(dfd);
}

void SoundManager::playbackByHash(string hash, const string &playbackId)
{
    std::transform(hash.begin(), hash.end(), hash.begin(), ::tolower);
    DIR *dfd = opendir(mPath.data());
    struct dirent *dp;
    bool found = false;

    if (dfd == NULL) {
        return;
    }

    while ((dp = readdir(dfd)) != NULL) {
        struct stat stbuf;
        string fileName(dp->d_name);
        string filePath = mPath + "/" + fileName;
        if (stat(filePath.data(), &stbuf) == -1) {
            continue;
        }

        if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
            // Skip directories
            continue;
        } else {
            auto fileHash = getHashByFilename(fileName);
            if (fileHash == hash) {
                found = true;
                // нашли файл - пытаемся его проиграть
                playbackByFilePath(filePath, playbackId);
                break;
            }
        }
    }
    closedir(dfd);
    if (!found) {
        // информируем о том, что файл не найден
        informAboutEvent(&ISoundManagerEventsListener::fileNotFound, playbackId);
    }
}

void SoundManager::playbackByFilePath(const string &filepath, const string& playbackId)
{
    SoundManagerFileInfo fileInfo;
    fileInfo.filePath = filepath;
    fileInfo.playbackId = playbackId;
    if (mAvPlayWatcher.active) {
        mFilesToPlayback.push_back(fileInfo);
    } else {
        mCurrentPlaybackFile = fileInfo;
        startPlaybackCurrentFile();
    }
}

void SoundManager::startPlaybackCurrentFile()
{
    mIsPlaybackStarted = false;
    stringstream ss;
    ss << "avplay -nodisp -autoexit '";
    ss << mCurrentPlaybackFile.filePath;
    ss << "' 2>&1";

    FILE *f = popen(ss.str().data(), "r");
    if (f) {
        int fd = fileno(f);        
        mAvPlayWatcher.start(fd, ev::READ);
    } else {
        informAboutEvent(&ISoundManagerEventsListener::fileNotFound, mCurrentPlaybackFile.playbackId);
        mCurrentPlaybackFile.filePath.clear();
        mCurrentPlaybackFile.playbackId.clear();
        // пробуем начать играть следующий файл.
        tryToPlaybackNextFile();
    }
}

void SoundManager::tryToPlaybackNextFile()
{
    if (!mFilesToPlayback.empty()) {
        mCurrentPlaybackFile = mFilesToPlayback.front();
        mFilesToPlayback.pop_front();
        startPlaybackCurrentFile();
    }
}

void SoundManager::addEventListener(ISoundManagerEventsListener* listener)
{
    mEventListeners.push_back(listener);
}

void SoundManager::removeEventListener(ISoundManagerEventsListener* listener)
{
    mEventListeners.remove(listener);
}

void SoundManager::onAvPlayEvent(ev::io& io, int event)
{    
    if (event & ev::READ) {
        static string duration("  Duration:");
        int count;
        ioctl(io.fd, FIONREAD, &count);
        vector<char> buff;
        buff.resize(count);
        int len = read(io.fd, buff.data(), buff.size());

        if (len <= 0) {
            // все, выход из программы avplay
            io.stop();
            close(io.fd);
            mCurrentPlaybackFile.filePath.clear();
            mCurrentPlaybackFile.playbackId.clear();
            if (!mIsPlaybackStarted) {
                // если не начинали проигрывние - значит беда
                informAboutEvent(&ISoundManagerEventsListener::fileNotFound, mCurrentPlaybackFile.playbackId);
            } else {
                // если начинали = то проигрывние закончено
                informAboutEvent(&ISoundManagerEventsListener::playbackFinished, mCurrentPlaybackFile.playbackId, false);
            }
            tryToPlaybackNextFile();
        } else if (!mIsPlaybackStarted) {
            if (std::search(buff.begin(), buff.end(), duration.begin(), duration.end()) != buff.end()) {
                mIsPlaybackStarted = true;
                informAboutEvent(&ISoundManagerEventsListener::playbackStarted, mCurrentPlaybackFile.playbackId);
            }
        }
    }
}

void SoundManager::cancelPlaybackFile(const string& playbackId)
{
    if (mCurrentPlaybackFile.playbackId == playbackId) {
        if (mAvPlayWatcher.is_active()) {
            mAvPlayWatcher.stop();
            close(mAvPlayWatcher.fd);
            informAboutEvent(&ISoundManagerEventsListener::playbackFinished, mCurrentPlaybackFile.playbackId, true);            
        }
        clearInfoAboutCurrentFile();
        tryToPlaybackNextFile();
    } else {        
        mFilesToPlayback.remove_if([playbackId](const SoundManagerFileInfo &info) {
            return playbackId == info.playbackId;
        });
    }
}

void SoundManager::clearInfoAboutCurrentFile()
{
    mCurrentPlaybackFile.filePath.clear();
    mCurrentPlaybackFile.playbackId.clear();
}