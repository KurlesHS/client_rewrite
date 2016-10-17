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

JsonFileSettings::JsonFileSettings(const string& filePath) :
    mPort(55555)
{
    readSettings(filePath);
}

uint16_t JsonFileSettings::port()
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
                } else if (element.key() == "bindings" && element.value().is_object()) {
                    json obj = element.value();
                    for (json::iterator it = obj.begin(); it != obj.end(); ++it) {
                        if (it.value().is_string()) {
                            mCodeToScriptBinding[it.key()] = it.value();
                        }
                    }
                }
            }
        }
    } catch (exception &) {
    }    
}

string JsonFileSettings::scriptNameByNotifyCode(const string& notifyCode)
{
    auto it = mCodeToScriptBinding.find(notifyCode);
    if (it != mCodeToScriptBinding.end()) {
        return it->second;
    }
    return string();
}