/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileContentEventHandler.cpp
 * Author: Alexey
 * 
 * Created on 20 марта 2017 г., 20:53
 */

#include "filecontenteventhandler.h"
#include <uuid.h>

#include <unordered_map>
#include <logger.h>

namespace {
    const char eventName[] = "incoming_file_content";
}

class FileContentEventHandlerPrivate {
public:
    FileContentEventHandlerPrivate(FileWatcher *fileWatcher) :
    fileWatcher(fileWatcher) {}
    
public:
    FileWatcher *fileWatcher;
    unordered_map<string, string> currentIfHappensIds;    
};

FileContentEventHandler::FileContentEventHandler(FileWatcher *fileWatcher) :
    d(new FileContentEventHandlerPrivate(fileWatcher))
{
    d->fileWatcher->addListener(this);
}

FileContentEventHandler::~FileContentEventHandler()
{
    delete d;
}

void FileContentEventHandler::ifHappensExpiried(const string& ifHappensId)
{
    d->currentIfHappensIds.erase(ifHappensId);
}

void FileContentEventHandler::onNewFile(const std::string& result)
{
    Logger::msg(R"(new file content: "%s")", result.data());
    list<string> happened;
    for (auto it = d->currentIfHappensIds.begin(); it != d->currentIfHappensIds.end();) {
        if (it->second.size()) {
            if (result == it->second) {
                happened.push_back(it->first);
                it = d->currentIfHappensIds.erase(it);
                continue;
            }
        } else {
            happened.push_back(it->first);
            it = d->currentIfHappensIds.erase(it);
            continue;
        }
        ++it;
    }
    
    for (const auto &id : happened) {
        ifHappensHappened(id, result);
    }    
}


void FileContentEventHandler::registerCommand(sol::state& state)
{
    auto x = this;
    state.set_function(eventName, &FileContentEventHandler::incomingFileContentImpl, x);
}

string FileContentEventHandler::incomingFileContentImpl(const sol::object& data)
{
    string ifHappensId = Uuid::createUuid().toString();
    string content;
    if (data.is<string>()) {
        content = data.as<string>();
    }
    d->currentIfHappensIds[ifHappensId] = content;
    
    return ifHappensId;    
}