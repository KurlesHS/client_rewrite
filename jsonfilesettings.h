/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JsonFileSettings.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 20:05
 */

#ifndef JSONFILESETTINGS_H
#define JSONFILESETTINGS_H

#include "isettings.h"

#include <unordered_map>


using namespace std;


class JsonFileSettings : public ISettings {
public:
    JsonFileSettings(const string &filePath) ;
    
    virtual ~JsonFileSettings();
    uint16_t port() override;
    string scriptNameByNotifyCode(const string& notifyCode) override;
    string fileServerUrl() override;
    string autostartScript() override;

    
private:
    void readSettings(const string &filePath);

private:
    uint16_t mPort;
    string mFileServerUrl;
    string mAutostartScript;
    
    unordered_map<string, string> mCodeToScriptBinding;
};

#endif /* JSONFILESETTINGS_H */

