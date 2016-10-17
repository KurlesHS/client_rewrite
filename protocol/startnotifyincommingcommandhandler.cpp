/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   startnotifyincommingcommandhandler.cpp
 * Author: kurles
 * 
 * Created on 13 октября 2016 г., 9:48
 */

#include "startnotifyincommingcommandhandler.h"
#include "startnotifyinfo.h"
#include "luatoprotocolmediator.h"

#include "logger.h"

using json = nlohmann::json;

static void handleIdKey(json::iterator &it, StartNotifyInfo &info)
{
    if (it.value().is_string()) {
        info.id = it.value();
    }
}

static void handlePriorityKey(json::iterator &it, StartNotifyInfo &info)
{

    if (it.value().is_number()) {
        info.priority = it.value();
    }
}

static void handleAudioContentKey(json::iterator &it, StartNotifyInfo &info)
{

    if (it.value().is_object()) {
        json obj = it.value();
        for (json::iterator element = obj.begin(); element != obj.end(); ++element) {
            if (element.value().is_string()) {
                if (element.key() == "type") {
                    // 'file' or 'url'
                    info.audioContentType = element.value();
                } else if (element.key() == "value") {
                    info.audioContentValue = element.value();
                } else if (element.key() == "filename") {
                    info.audioContentFileName = element.value();
                }
            }
        }
    }
}

static void handleHardwareKey(json::iterator &it, StartNotifyInfo &info)
{
    if (it.value().type() == json::value_t::array) {
        json obj = it.value();
        for (const auto &element : obj) {
            if (element.is_string()) {
                info.hardwares.push_back(element);
            }
        }
    }
}

static void handleCodeKey(json::iterator &it, StartNotifyInfo &info)
{
    if (it.value().is_string()) {
        info.code = it.value();
    }
}

static void handleAdditionalDataKey(json::iterator &it, StartNotifyInfo &info)
{
    if (!it.value().is_object()) {
        /* если значение не объект - то тут и ловить нам нечего */
        return;
    }
    json obj = it.value();
    for (json::iterator element = obj.begin(); element != obj.end(); ++element) {
        string varName = element.key();
        StartNotifyAdditionalData data;
        if (element.value().is_string()) {
            data.type = StartNotifyAdditionalData::Type::String;
            data.stringValue = element.value();
        } else if (element.value().is_array()) {
            data.type = StartNotifyAdditionalData::Type::List;
            for (const auto &listElement : element.value()) {
                if (listElement.is_string()) {
                    data.listValue.push_back(listElement);
                }
            }
        } else if (element.value().is_object()) {
            data.type = StartNotifyAdditionalData::Type::Table;
            auto val = element.value();
            for (json::iterator tableElement = val.begin(); tableElement != val.end(); ++tableElement) {
                if (tableElement.value().is_string()) {
                    data.tableValue[tableElement.key()] = tableElement.value();
                }
            }
        } else {
            continue;
        }
        info.additionalData[varName] = data;
    }
}

StartNotifyIncommingCommandHandler::StartNotifyIncommingCommandHandler(LuaToProtocolMediator *mediator) :
    mMediator(mediator)
{
}

StartNotifyIncommingCommandHandler::~StartNotifyIncommingCommandHandler()
{
}

uint16_t StartNotifyIncommingCommandHandler::command() const
{
    return 0x0100;
}

bool StartNotifyIncommingCommandHandler::handleCommand(const vector<char>& payload)
{
    bool result = true;
    try {
        using handler = void (*)(json::iterator &it, StartNotifyInfo & info);

        json j = json::parse(string(payload.begin(), payload.end()));
        unordered_map<string, handler> handlers;
        handlers["id"] = handleIdKey;
        handlers["code"] = handleCodeKey;
        handlers["hardware"] = handleHardwareKey;
        handlers["priority"] = handlePriorityKey;
        handlers["audio_content"] = handleAudioContentKey;
        handlers["additional_data"] = handleAdditionalDataKey;

        StartNotifyInfo info;
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            auto h = handlers.find(it.key());
            if (h != handlers.end()) {
                h->second(it, info);
            }
        }
        /* TODO: сделать что нибудь с вытащеной информацией */
        Logger::msg("received start notify incomming command with code '%s'", info.code.data());
        mMediator->startNotifyRequest(info);
    } catch (const std::exception &e) {
        Logger::msg("received mailformed (wrong) start notify incomming command");
        result = false;
    }
    return result;
}


