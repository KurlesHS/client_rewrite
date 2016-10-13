/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   startnotifyincommingcommandhandler.h
 * Author: kurles
 *
 * Created on 13 октября 2016 г., 9:48
 */

#ifndef STARTNOTIFYINCOMMINGCOMMANDHANDLER_H
#define STARTNOTIFYINCOMMINGCOMMANDHANDLER_H

#include "iincommingcommandhandler.h"

#include <list>
#include <unordered_map>

#include "stdint.h"

#include "json/json.hpp"

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
    unordered_map<string, StartNotifyAdditionalData> additionalData;
};

class StartNotifyIncommingCommandHandler : public IIncommingCommandHandler {
public:
    StartNotifyIncommingCommandHandler();
    virtual ~StartNotifyIncommingCommandHandler();

    uint16_t command() const override;
    bool handleCommand(const vector<char>& payload) override;

private:

};

#endif /* STARTNOTIFYINCOMMINGCOMMANDHANDLER_H */

