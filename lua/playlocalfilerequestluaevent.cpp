
/* 
 * File:   playlocalfilerequestluaevent.cpp
 * Author: kurles
 * 
 * Created on 17 октября 2016 г., 9:33
 */

#include "playlocalfilerequestluaevent.h"

PlayLocalFileRequestLuaEvent::PlayLocalFileRequestLuaEvent(const Type& type, const string &id, const string& value) :
    mType(type),
    mId(id),
    mValue(value)
{

}

PlayLocalFileRequestLuaEvent::~PlayLocalFileRequestLuaEvent()
{
}

ILuaEvent::EventType PlayLocalFileRequestLuaEvent::eventType() const
{
    using ET = ILuaEvent::EventType;
    return mType == Type::ByHash ?
            ET::PlayLocalFileByHashRequest :
            ET::PlayLocalFileByPathRequest;
}

PlayLocalFileRequestLuaEvent::Type PlayLocalFileRequestLuaEvent::type() const
{
    return mType;
}

string PlayLocalFileRequestLuaEvent::value() const
{
    return mValue;
}
