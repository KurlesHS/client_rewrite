/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   luascript.cpp
 * Author: Alexey
 * 
 * Created on 9 июля 2016 г., 18:01
 */

#include <uuid/uuid.h>
#include <sol2.hpp>

#include "luascript.h"
#include "timer/itimer.h"
#include "ioc/resolver.h"

#include <list>
#include <string>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <ev++.h>

#include "uuid.h"
#include "scriptfinishedluaevent.h"
#include "logmessageluaevent.h"
#include "playlocalfilerequestluaevent.h"
#include "stoplocalaudiorequestluaevent.h"
#include "playnetworkaudiorequestluaevent.h"
#include "stopnetworkaudiorequestluaevent.h"
#include "logger.h"
#include "sethardwarestatusesluaevent.h"
#include "outgoingmessageluaevent.h"



// static const char priorityVarName[] = "priority";
static const char groupVarName[] = "group";

static const char startFuncName[] = "start";
static const char cleanupOnCancelFuncName[] = "cleanup_on_cancel";
static const char finishFuncName[] = "finish";
static const char logMessageFuncName[] = "log_message";
static const char playLocalFileByFilepathFuncName[] = "play_local_file_by_filepath";
static const char playLocalFileByFilehashFuncName[] = "play_local_file_by_filehash";
static const char stopPlayLocalFileFuncName[] = "stop_play_local_file";
static const char playNetworkAudioFuncName[] = "play_network_audio";
static const char stopPlayNetworkAudioFuncName[] = "stop_play_network_audio";
static const char ifHappensFuncName[] = "if_happens";
static const char delayFuncName[] = "delay";
static const char cancelPendingFuncFuncName[] = "cancel_pending_func";

static const char setHardwareStatusWorkFuncName[] = "set_hardware_status_work";
static const char setHardwareStatusFailFuncName[] = "set_hardware_status_fail";
static const char setHardwareStatusUnknownFuncName[] = "set_hardware_status_unknown";

static const char setNotifyStatusProcessFuncName[] = "set_notify_status_process";
static const char setNotifyStatusWaitFuncName[] = "set_notify_status_wait";
static const char setNotifyStatusErrorFuncName[] = "set_notify_status_error";
static const char setNotifyStatusUnknownFuncName[] = "set_notify_status_unknown";

static const char outgoingMessageFuncName[] = "outgoing_message";

static const char onRelayChagedFuncName[] = "on_relay_changed";

static const char notifyIdVarName[] = "notify_id";
static const char notifyCodeVarName[] = "notify_code";
static const char hardwaresVarName[] = "hardwares";
static const char priorityVarName[] = "priority";
static const char audioContentTypeVarName[] = "audio_content_type";
static const char audioContentValueVarName[] = "audio_content_value";
static const char audioContentFilenameVarName[] = "audio_content_filename";

/*
static const char FuncName[] = "";
 */

using namespace std;

class IfHappensPendingFunc;

typedef std::shared_ptr<IfHappensPendingFunc> IfHappensPendingFuncSharedPtr;

class IfHappensPendingFunc
{
public:
    using onExecuteFunc = std::function<void(const std::string &)>;

    IfHappensPendingFunc(const std::string &pendingId,
            const std::string &ifHappensId,
            const int delay, const sol::function &okFunc,
            const sol::function &errorFunc) :
        mPendingId(pendingId),
        mIfHappensId(ifHappensId),
        mDelay(delay),
        mOkFunc(okFunc),
        mErrorFunc(errorFunc),
        mTimer(Resolver::resolveDi<ITimerFactory>()->getTimer())
    {

    }

    ~IfHappensPendingFunc()
    {
        stop();
    }

    virtual void start()
    {
        mTimer->setSingleShot(true);
        mTimer->addCallbackFunction([this](ITimer *) {
            onTimeout(); });
        mTimer->start(mDelay);
    }

    void onTimeout()
    {
        if (mOnTimeoutFunc) {
            mOnTimeoutFunc(mPendingId);
        }
    }

    virtual void stop()
    {
        mTimer->stop();
    }

    template<typename ...Args>
    void executeOkFunc(Args ...args)
    {
        stop();
        if (mOkFunc) {
            mOkFunc(std::forward<Args>(args)...);
        }
    }

    void executeErrorFunc()
    {
        if (mErrorFunc) {
            mErrorFunc();
        }
    }

    std::string ifHappensId() const
    {
        return mIfHappensId;
    }

    void setOnTimeoutFunc(onExecuteFunc func)
    {
        mOnTimeoutFunc = func;
    }

    sol::function okFunc() const
    {
        return mOkFunc;
    }

private:
    const std::string mPendingId;
    const std::string mIfHappensId;
    const int mDelay;
    const sol::function mOkFunc;
    const sol::function mErrorFunc;
    ITimerSharedPtr mTimer;

    onExecuteFunc mOnTimeoutFunc;
};

struct OnRelayChangedParams
{
    sol::object relayNum;
    sol::object relayState;
};

class LuaScriptPrivate
{
    friend class LuaScript;
    LuaScript *q;
    std::string scriptName;
    std::string scriptPath;
    std::string group = "default_group";
    sol::state state;
    bool isValid = true;
    bool isFinished = false;
    bool isFinishedEmited = false;
    bool isCanceled = false;
    std::string lastError;
    int priority = 0;
    std::string id;
    std::string notifyId;
    ev::async async;
    StartNotifyInfo startNotifyInfo;

    ITimerFactory *timerFactory;
    std::unordered_map<std::string, IfHappensPendingFuncSharedPtr> mIfHappensFunc;
    std::unordered_map<std::string, OnRelayChangedParams> mRelayChangeParams;
    list<ILuaScriptEventsListener*> mEventListeners;
    list<function<void() >> mAsyncFunc;

    LuaScriptPrivate()
    {
        async.set<LuaScriptPrivate, &LuaScriptPrivate::onAsync>(this);
        async.start();
    }

    void onAsync()
    {
        for (auto f : mAsyncFunc) {
            f();
        }
        mAsyncFunc.clear();
    }

    void informAboutLuaEvent(ILuaEventSharedPtr event)
    {
        addAsyncFunc([event, this]() {
            for (const auto listener : mEventListeners) {
                listener->luaEvent(event);
            }
        });
    }

    void removeIfHappensParams(const std::string &idHappensId)
    {
        mRelayChangeParams.erase(idHappensId);
    }

    void addLuaScriptEventListener(ILuaScriptEventsListener *listener)
    {
        mEventListeners.push_back(listener);
    }

    void removeLuaScriptEventListener(ILuaScriptEventsListener *listener)
    {
        mEventListeners.remove(listener);
    }

    void onRelayChanged(const int relayNum, const int newState)
    {
        for (auto it = mRelayChangeParams.begin(); it != mRelayChangeParams.end();) {
            bool relayIsSame = true;
            bool stateIsSame = true;
            if (it->second.relayNum.is<int>()) {
                relayIsSame = relayNum == it->second.relayNum.as<int>();
            }
            if (it->second.relayState.is<int>()) {
                stateIsSame = newState == it->second.relayState.as<int>();
            }
            if (relayIsSame && stateIsSame) {
                // совпали как номер реле так и его состояние
                // ищем функции с этим if happens id и запускаем их
                findAndExecute(it->first, relayNum, newState);
                // удаляем эти параметры
                it = mRelayChangeParams.erase(it);
            } else {
                ++it;
            }
        }
    }

    template<typename ...Args>
    void findAndExecute(const std::string &ifHappensId, Args ...args)
    {
        for (auto it = mIfHappensFunc.begin();
                it != mIfHappensFunc.end();) {
            if (it->second->ifHappensId() == ifHappensId) {
                // идентификаторы совпали
                try {
                    // пытаемся запустить
                    it->second->executeOkFunc(args...);
                } catch (sol::error error) {
                    // если ошибка - помечаем скрипт как ошибочный
                    setLastError(error.what());
                    break;
                }
                it = mIfHappensFunc.erase(it);
            } else {
                ++it;
            }
        }
        // проверка скрипта на завершённость
        checkIfFinished();
    }

    void setHardwareStatusWorkFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetHardwareStatusWork, hardwareId));
    }

    void setHardwareStatusFailFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetHardwareStatusFail, hardwareId));
    }

    void setHardwareStatusUnknownFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetHardwareStatusUnknown, hardwareId));
    }

    void setNotifyStatusProcessFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetNotifyStatusProcess, hardwareId));
    }

    void setNotifyStatusWaitFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetNotifyStatusWait, hardwareId));
    }

    void setNotifyStatusErrorFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetNotifyStatusError, hardwareId));
    }

    void setNotifyStatusUnknownFuncImpl(const string &hardwareId)
    {
        informAboutLuaEvent(make_shared<SetHardwareStatusesLuaEvent>(
                ILuaEvent::EventType::SetNotifyStatusUnknown, hardwareId));
    }

    void outgoingMessageFuncImpl(const string &hardwareId, const string &message)
    {
        informAboutLuaEvent(make_shared<OutgoingMessageLuaEvent>(
                hardwareId, message));
    }

    std::string onRelayChangedFuncImpl(sol::object relayNum, sol::object newState)
    {
        auto id = Uuid::createUuid().toString();
        mRelayChangeParams[id] = {relayNum, newState};
        return id;
    }

    void checkIfFinished()
    {
        if (isFinished && !isFinishedEmited) {
            isFinishedEmited = true;
            informAboutLuaEvent(make_shared<ScriptFinishedLuaEvent>(
                    id,
                    startNotifyInfo.id,
                    startNotifyInfo.code,
                    scriptName,
                    isCanceled,
                    !lastError.empty()));
        }
    }

    void setLastError(const std::string &lastError)
    {
        this->lastError = lastError;
        isValid = false;
        isFinished = true;
        Logger::msg("lua error: %s", lastError.data());
    }

    void cancelPendingFuncImpl(const std::string &pendingId)
    {
        try {
            auto func = mIfHappensFunc.at(pendingId);
            // при удалении penfing'a нужно удалить так же и привязанные к
            // нему условиия if happens
            removeIfHappensParams(func->ifHappensId());
            mIfHappensFunc.erase(pendingId);
        } catch (std::out_of_range) {

        }
    }

    void createId()
    {
        id = Uuid::createUuid().toString();
    }

    /* functions */

    void finishFuncImpl()
    {
        isFinished = true;
    }

    std::string delayFuncImpl(const double &seconds, const sol::function &func)
    {
        // delay - тот же ифхаппенс, с пустой ok функцией 
        return ifHappensFuncImpl(seconds, std::string(), sol::function(), func);
    }

    std::string ifHappensFuncImpl(
            const double &second, const std::string &ifHappensId,
            const sol::function &okFunc, const sol::function &errorFunc)
    {
        std::string id;
        if (second <= 0) {
            if (errorFunc) {
                // если кол-во секунд меньше или равно нулю и присутствует 
                // функция ошибки - сразу вызываем ее
                errorFunc();
                checkIfFinished();
            }
        } else {
            if (okFunc || errorFunc) {
                // одна из функций должна обязательно присутствовать
                id = Uuid::createUuid().toString();
                // создаем экземпляр
                auto func = std::make_shared<IfHappensPendingFunc>(
                        id, ifHappensId, second * 1000, okFunc, errorFunc);
                // сохраняем его
                mIfHappensFunc[id] = func;
                func->setOnTimeoutFunc([this](const std::string & pendingId) {
                    // функция, вызываемая по таймауту 
                    try {
                        auto func = mIfHappensFunc.at(pendingId);
                        try {
                            // пытаемся вызвать функцию ошибки
                            func->executeErrorFunc();
                        } catch (sol::error error) {
                            setLastError(error.what());
                        }
                    } catch (std::out_of_range) {

                    }
                    // удаляем инфу об функции
                    auto f = [this, pendingId]() {
                        cancelPendingFuncImpl(pendingId);
                        checkIfFinished();
                    };
                    addAsyncFunc(f);

                });
                // запускаем таймер ожидания события
                func->start();
            }
        }
        return id;
    }

    void addAsyncFunc(const function<void()> &f)
    {
        mAsyncFunc.push_back(f);
        async.send();
    }

    void logMessageFuncImpl(const std::string &message)
    {
        stringstream ss;
        ss << "message from lua script: " << message;

        Logger::msg(ss.str());
        //informAboutLuaEvent(make_shared<LogMessageLuaEvent>(message));
    }

    std::string playLocalFileByFilepathFuncImpl(const std::string &filepath)
    {
        std::string id = Uuid::createUuid().toString();
        informAboutLuaEvent(make_shared<PlayLocalFileRequestLuaEvent>(
                PlayLocalFileRequestLuaEvent::Type::ByPath, id, filepath));
        return id;
    }

    std::string playLocalFileByFilehashFuncImpl(const std::string &filehash)
    {
        std::string id = Uuid::createUuid().toString();
        informAboutLuaEvent(make_shared<PlayLocalFileRequestLuaEvent>(
                PlayLocalFileRequestLuaEvent::Type::ByHash, id, filehash));
        return id;
    }

    void stopPlayLocalFileFuncImpl(const std::string &id)
    {
        informAboutLuaEvent(make_shared<StopLocalAudioRequestLuaEvent>(id));
    }

    void playNetworkAudioFuncImpl(const std::string &url)
    {
        informAboutLuaEvent(make_shared<PlayNetworkAudioRequestLuaEvent>(url));
    }

    void stopPlayNetworkAudioFuncImpl()
    {
        informAboutLuaEvent(make_shared<StopNetworkAudioRequestLuaEvent>());
    }
};

std::string LuaScript::id() const
{
    return d->id;
}

float LuaScript::getFloatVar(const std::string& varName)
{
    return d->state.get<float>(varName);
}

int LuaScript::getIntegerVar(const std::string& varName)
{
    return d->state.get<int>(varName);
}

std::string LuaScript::getStringVar(const std::string& varName)
{
    return d->state.get<std::string>(varName);
}

std::string LuaScript::notifyId() const
{
    return d->notifyId;
}

void LuaScript::setNotifyId(const std::string& notifyId)
{
    d->notifyId = notifyId;
}

ILuaPendingFunc::~ILuaPendingFunc()
{
}

void LuaScript::init()
{
    try {        
        d->state.script_file(d->scriptPath);
        sol::function startFunc = d->state[startFuncName];
        // если в скрипте нет функции старт - беда, счиатем что в скрипте 
        // ошибка
        if (!startFunc) {
            d->setLastError(std::string(R"(function "start" is missing)"));
            return;
        }
        // попытка прочитать приоритет (по умолчанию - 0).
        sol::object priorityObject = d->state[priorityVarName];
        if (priorityObject.is<int>()) {
            // если переменная приоритета присутствует - назначаем
            // указанный приоритет
            d->priority = priorityObject.as<int>();
        } 
        // попытка прочитать группу (по умолчанию - 0).
        sol::object groupObject = d->state[groupVarName];
        if (groupObject.is<std::string>()) {
            // если переменная приоритета присутствует - назначаем
            // указанный приоритет
            d->group = groupObject.as<std::string>();
        }


        d->state.set_function(finishFuncName,
                &LuaScriptPrivate::finishFuncImpl, d);
        d->state.set_function(delayFuncName,
                &LuaScriptPrivate::delayFuncImpl, d);
        d->state.set_function(ifHappensFuncName,
                &LuaScriptPrivate::ifHappensFuncImpl, d);
        d->state.set_function(cancelPendingFuncFuncName,
                &LuaScriptPrivate::cancelPendingFuncImpl, d);
        d->state.set_function(logMessageFuncName,
                &LuaScriptPrivate::logMessageFuncImpl, d);
        d->state.set_function(playLocalFileByFilehashFuncName,
                &LuaScriptPrivate::playLocalFileByFilehashFuncImpl, d);
        d->state.set_function(playLocalFileByFilepathFuncName,
                &LuaScriptPrivate::playLocalFileByFilepathFuncImpl, d);
        d->state.set_function(stopPlayLocalFileFuncName,
                &LuaScriptPrivate::stopPlayLocalFileFuncImpl, d);
        d->state.set_function(playNetworkAudioFuncName,
                &LuaScriptPrivate::playNetworkAudioFuncImpl, d);
        d->state.set_function(stopPlayNetworkAudioFuncName,
                &LuaScriptPrivate::stopPlayNetworkAudioFuncImpl, d);

        d->state.set_function(setHardwareStatusFailFuncName,
                &LuaScriptPrivate::setHardwareStatusFailFuncImpl, d);
        d->state.set_function(setHardwareStatusUnknownFuncName,
                &LuaScriptPrivate::setHardwareStatusUnknownFuncImpl, d);
        d->state.set_function(setHardwareStatusWorkFuncName,
                &LuaScriptPrivate::setHardwareStatusWorkFuncImpl, d);

        d->state.set_function(setNotifyStatusErrorFuncName,
                &LuaScriptPrivate::setNotifyStatusErrorFuncImpl, d);
        d->state.set_function(setNotifyStatusProcessFuncName,
                &LuaScriptPrivate::setNotifyStatusProcessFuncImpl, d);
        d->state.set_function(setNotifyStatusUnknownFuncName,
                &LuaScriptPrivate::setNotifyStatusUnknownFuncImpl, d);
        d->state.set_function(setNotifyStatusWaitFuncName,
                &LuaScriptPrivate::setNotifyStatusWaitFuncImpl, d);

        d->state.set_function(outgoingMessageFuncName,
                &LuaScriptPrivate::outgoingMessageFuncImpl, d);

        d->state.set_function(onRelayChagedFuncName,
                &LuaScriptPrivate::onRelayChangedFuncImpl, d);


    } catch (const sol::error &error) {
        d->setLastError(error.what());
    }
}

LuaScript::LuaScript(const std::string &scriptPath) :
    d(new LuaScriptPrivate)
{
    d->timerFactory = Resolver::resolveDi<ITimerFactory>();
    d->createId();
    d->q = this;
    d->scriptPath = scriptPath;
    d->state.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math);
    init();
}

LuaScript::~LuaScript()
{
    delete d;
}

int LuaScript::priority() const
{
    return d->priority;
}

void LuaScript::setPriority(const int priority)
{
    d->priority = priority;
}

std::string LuaScript::group() const
{
    return d->group;
}

bool LuaScript::isValid() const
{
    return d->isValid;
}

std::string LuaScript::lastError() const
{
    return d->lastError;
}

bool LuaScript::isFinished() const
{
    return d->isFinished;
}

bool LuaScript::run()
{
    bool result = false;
    if (isValid()) {
        try {
            d->state.script(std::string(startFuncName) + "()");
            d->checkIfFinished();
            result = true;
        } catch (sol::error error) {
            d->setLastError(error.what());
            d->checkIfFinished();
        }
    } else {
        d->setLastError("attempt to run invalid script");
    }
    return result;
}

void LuaScript::cancel()
{
    if (!isFinished() && isValid()) {
        d->isCanceled = true;
        // имеет смысл только когда скрипт в работе
        sol::function cleanOnCancel = d->state[cleanupOnCancelFuncName];
        if (cleanOnCancel) {
            // в скрипте присутствует функция cleanup_on_cancel
            try {
                cleanOnCancel();
            } catch (sol::error error) {
                d->setLastError(error.what());
            }
        }
        d->isFinished = true;
        d->checkIfFinished();
    }
}

void LuaScript::onRelayChanged(const int relayNum, const int newState)
{
    d->onRelayChanged(relayNum, newState);
}

int LuaScript::pendingIfHanpensFunctionCount() const
{
    return d->mIfHappensFunc.size();
}

int LuaScript::relayChangedActiveConditionsCount() const
{
    return d->mRelayChangeParams.size();
}

void LuaScript::addLuaScriptEventListener(ILuaScriptEventsListener* listener)
{
    d->addLuaScriptEventListener(listener);
}

void LuaScript::removeLuaScriptEventListener(ILuaScriptEventsListener* listener)
{
    d->removeLuaScriptEventListener(listener);
}

sol::state& LuaScript::luaState()
{
    return d->state;
}

list<sol::function> LuaScript::ifHappensOkFunc(const string& ifHappensId)
{
    list<sol::function> result;
    for (auto x : d->mIfHappensFunc) {
        if (x.second->ifHappensId() == ifHappensId) {
            x.second->stop();
            if (x.second->okFunc()) {
                result.push_back(x.second->okFunc());
            }
        }
    }
    return result;
}

string LuaScript::scriptName() const
{
    return d->scriptName;
}

void LuaScript::setScriptName(const string& name)
{
    d->scriptName = name;
}

void LuaScript::removeIfHappens(const string& ifHappensId, const bool checkIsfinished, const bool forceAsync)
{
    if (forceAsync) {
        d->addAsyncFunc([this, ifHappensId, checkIsfinished]() {
            removeIfHappens(ifHappensId, checkIsfinished, false);
        });
    } else {
        for (auto x = d->mIfHappensFunc.begin(); x != d->mIfHappensFunc.end();) {
            if (x->second->ifHappensId() == ifHappensId) {
                x->second->stop();
                x = d->mIfHappensFunc.erase(x);
            } else {
                ++x;
            }
        }
        if (checkIsfinished) {
            d->checkIfFinished();
        }
    }
}

const StartNotifyInfo& LuaScript::notifyInfo() const
{
    return d->startNotifyInfo;
}

void LuaScript::setNotifyInfo(const StartNotifyInfo& info)
{
    d->startNotifyInfo = info;
    auto createTable = [this](const unordered_map<string, string> &tableValue) {
        sol::table tbl = d->state.create_table(0, 0);
        for (auto it = tableValue.begin(); it != tableValue.end(); ++it) {
            tbl[it->first] = it->second;
        }
        return tbl;
    };

    auto createArray = [this](const list<string> &arrayValue) {
        sol::table arr = d->state.create_table(0, 0);
        int idx = 1;
        for (const auto &value : arrayValue) {
            arr[idx++] = value;
        }
        return arr;
    };

    d->state[hardwaresVarName] = createArray(info.hardwares);
    d->state[notifyIdVarName] = info.id;
    d->state[notifyCodeVarName] = info.code;
    d->state[audioContentFilenameVarName] = info.audioContentFileName;
    d->state[audioContentTypeVarName] = info.audioContentType;
    d->state[audioContentValueVarName] = info.audioContentValue;


    for (auto it = info.additionalData.begin(); it != info.additionalData.end(); ++it) {
        switch (it->second.type) {
            case StartNotifyAdditionalData::Type::List:
                d->state[it->first] = createArray(it->second.listValue);
                break;
            case StartNotifyAdditionalData::Type::String:
                d->state[it->first] = it->second.stringValue;
                break;
            case StartNotifyAdditionalData::Type::Table:
                d->state[it->first] = createTable(it->second.tableValue);
                break;
            default:
                break;
        }
    }
}
