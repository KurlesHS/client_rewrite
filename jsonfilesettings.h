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
    uint16_t port() const override;
    string scriptNameByNotifyCode(const string& notifyCode) const override;
    string fileServerUrl() const override;
    string autostartScript() const override;
    list<GpioSettings> gpioSettings() const override;
    string password() const override;
    string username() const override;
    bool manualGpioRead() const override;
    string eventFilesDir() const override;

    
private:
    void readSettings(const string &filePath);

private:
    uint16_t mPort;
    string mFileServerUrl;
    string mAutostartScript;    
    string mPassword;
    string mUsername;
    string mEventFilesDir;
    bool mManualGpioRead;
    unordered_map<string, string> mCodeToScriptBinding;
    list<GpioSettings> mGpioSettings;
};

#endif /* JSONFILESETTINGS_H */

