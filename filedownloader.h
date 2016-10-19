/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filedownloader.h
 * Author: kurles
 *
 * Created on 19 октября 2016 г., 11:59
 */

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <ev++.h>

#include <string>
#include <vector>

#include "soundmanager.h"

using namespace std;

class FileDownloader
{
public:
    FileDownloader(const string &serverAddress, const string &path, const string& hash, const string& fileName, const fileIsDownloadedCallback& callback);
    virtual ~FileDownloader();
    
    void start();
    
private:
    void onIo(ev::io &io, int events);
    
private:
    const string mServerAddress;
    const string mPath;
    const string mHash;
    const string mFileName;
    const fileIsDownloadedCallback mCallback;
    vector<char> mBuffer;
    string result;
    
    ev::io mIo;
    FILE *mFile;
    bool mIsStartDownload;

};

#endif /* FILEDOWNLOADER_H */

