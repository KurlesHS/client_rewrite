/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   startnotifyinfo.h
 * Author: Alexey
 *
 * Created on 17 октября 2016 г., 19:07
 */

#ifndef STARTNOTIFYINFO_H
#define STARTNOTIFYINFO_H

#include <unordered_map>
#include <list>

using namespace std;

struct StartNotifyAdditionalData {
    enum class Type {
        String,
        List,
        Table
    };

    string stringValue;
    list<string> listValue;
    unordered_map<string, string> tableValue;

    Type type;

};

struct StartNotifyInfo {
    string id;
    string code;
    list<string> hardwares;
    int priority;
    string audioContentType;
    string audioContentValue;
    string audioContentFileName;
    unordered_map<string, StartNotifyAdditionalData> additionalData;
};


#endif /* STARTNOTIFYINFO_H */

