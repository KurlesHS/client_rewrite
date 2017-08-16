/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JsonFileSettings.cpp
 * Author: Alexey
 * 
 * Created on 17 октября 2016 г., 20:05
 */

#include "jsonfilesettings.h"

#include "3rdparty/json/json.hpp"

#include <fstream>

using namespace std;

JsonFileSettings::~JsonFileSettings()
{
}

string JsonFileSettings::eventFilesDir() const
{
    return mEventFilesDir;
}


JsonFileSettings::JsonFileSettings(const string& filePath) :
    mPort(55555),
    mManualGpioRead(false)
{
    readSettings(filePath);
}

uint16_t JsonFileSettings::port() const
{
    return mPort;
}

void JsonFileSettings::readSettings(const string& filePath)
{
    using json = nlohmann::json;
    vector<char> buff;
    try {
        ifstream stream(filePath);
        if (stream.is_open()) {
            stream.seekg(0, stream.end);
            int size = stream.tellg();
            stream.seekg(0, stream.beg);

            buff.resize(size);
            stream.read(buff.data(), size);
            json j = json::parse(string(buff.begin(), buff.end()));
            for (json::iterator element = j.begin(); element != j.end(); ++element) {
                if (element.key() == "port" && element.value().is_number()) {
                    mPort = element.value();
                } else if (element.key() == "manual_gpio_read" && element.value().is_boolean()) {
                    mManualGpioRead = element.value();
                } else if (element.key() == "file_server" && element.value().is_string()) {
                    mFileServerUrl = element.value();
                } else if (element.key() == "event_files_dir" && element.value().is_string()) {
                    mEventFilesDir = element.value();
                } else if (element.key() == "username" && element.value().is_string()) {
                    mUsername = element.value();
                } else if (element.key() == "password" && element.value().is_string()) {
                    mPassword = element.value();
                } else if (element.key() == "autostart_script" && element.value().is_string()) {
                    mAutostartScript = element.value();
                } else if (element.key() == "bindings" && element.value().is_object()) {
                    json obj = element.value();
                    for (json::iterator it = obj.begin(); it != obj.end(); ++it) {
                        if (it.value().is_string()) {
                            mCodeToScriptBinding[it.key()] = it.value();
                        }
                    }
                } else if (element.key() == "gpio" && element.value().is_object()) {
                    json obj = element.value();
                    for (json::iterator it = obj.begin(); it != obj.end(); ++it) {
                        if (it.value().is_array()) {
                            json array = it.value();
                            if (array.size() > 1) {
                                if (array[0].is_string() && array[1].is_string()) {
                                    string gpioId = it.key();
                                    string gpioName = array[0];
                                    string gpioDirection = array[1];
                                    GpioSettings gs;
                                    gs.id = gpioId;
                                    gs.name = gpioName;
                                    if (gpioDirection == "in") {
                                        gs.direction = GpioSettings::Direction::In;
                                    } else if (gpioDirection == "out") {
                                        gs.direction = GpioSettings::Direction::Out;
                                    } else {
                                        continue;
                                    }
                                    mGpioSettings.emplace_back(gs);
                                }
                            }
                        }
                    }
                }
            }
        }
    } catch (exception &) {

    }
    if (mFileServerUrl.size() && mFileServerUrl.at(mFileServerUrl.size() - 1) != '/') {
        mFileServerUrl += "/";
    }
}

string JsonFileSettings::scriptNameByNotifyCode(const string& notifyCode) const
{
    auto it = mCodeToScriptBinding.find(notifyCode);
    if (it != mCodeToScriptBinding.end()) {
        return it->second;
    }
    return string();
}

string JsonFileSettings::fileServerUrl() const
{
    return mFileServerUrl;
}

string JsonFileSettings::autostartScript() const
{
    return mAutostartScript;
}

list<GpioSettings> JsonFileSettings::gpioSettings() const
{
    return mGpioSettings;
}

string JsonFileSettings::password() const
{
    return mPassword;
}

string JsonFileSettings::username() const
{
    return mUsername;
}

bool JsonFileSettings::manualGpioRead() const
{
    return mManualGpioRead;
}

