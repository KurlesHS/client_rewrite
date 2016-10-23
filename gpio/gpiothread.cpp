/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GpioThread.cpp
 * Author: Alexey
 * 
 * Created on 21 октября 2016 г., 3:05
 */

#include "gpiothread.h"
#include "isettings.h"
#include "ioc/resolver.h"
#include "logger.h"
#include "gpiomanager.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>

struct GpioThread::GpioInfo
{

    enum class Direction
    {
        In,
        Out
    };
    int pinNum;
    string pinName;
    string pinId;
    Direction direction;
    GpioThread::GpioInfo *next;
    int fd;
};

GpioThread::GpioThread(GpioManager *manager) :
    mManager(manager),
    mGpioInfoList(nullptr)
{

}

GpioThread::~GpioThread()
{
    auto gpioInfo = mGpioInfoList;
    while (gpioInfo) {
        auto copy = gpioInfo;
        delete copy;
        gpioInfo = gpioInfo->next;
    }
}

void GpioThread::start()
{
    mThread = thread(&GpioThread::threadProc, this);
    mThread.detach();
}

static bool writeTo(const char *path, const char *data, const size_t size)
{
    bool result = false;
    FILE *f = fopen(path, "w");
    if (f) {
        int bytesWritten = fwrite(data, size, 1, f);
        (void) bytesWritten;
        auto err = errno;
        fflush(f);
        fclose(f);
        result = err == 0;
#if 0
        cout << data << " > " << path << " " << strerror(err) << " " << err << " "
                << result << " == " << size << endl;
#endif

    }
    return result;
}

bool GpioThread::writeTo(const string& path, const string& data)
{
    return ::writeTo(path.data(), data.data(), (size_t) data.size());
}

string GpioThread::readFrom(const string& path, bool *ok)
{
    char buff[0x10];
    string result;
    if (ok) {
        *ok = false;
    }
    struct stat st;
    if (stat(path.data(), &st) != 0) {
        return result;
    }

    if (!S_ISREG(st.st_mode)) {
        return result;
    }

    FILE *f = fopen(path.data(), "r");
    if (!f) {
        return result;
    }

    int len = fread(buff, 1, 0x10, f);
    if (len > 0) {
        result = string(buff, buff + len);
        if (ok) {
            *ok = true;
        }
    }
    return result;

}

static bool exportGpio(int gpioNum)
{
    string strPinNum = to_string(gpioNum);
    return ::writeTo("/sys/class/gpio/export", strPinNum.data(), strPinNum.size());
}

static bool unexportGpio(int gpioNum)
{
    string strPinNum = to_string(gpioNum);
    return ::writeTo("/sys/class/gpio/unexport", strPinNum.data(), strPinNum.size());
}

static bool checkDir(const string &dir)
{
    bool result = false;
    DIR* d = opendir(dir.data());
    if (d) {
        /* Directory exists. */
        closedir(d);
        result = true;
    }
    return result;
}

static string getDataForDirection(GpioSettings::Direction direction)
{
    string result;
    switch (direction) {
        case GpioSettings::Direction::In:
            result = "in";
            break;
        case GpioSettings::Direction::Out:
            result = "out";
            break;
    }
    return result;
}

static string getDataForEdge(GpioSettings::Direction direction, const int currentState)
{
    string result;
    switch (direction) {
        
        case GpioSettings::Direction::In:
            result = "both";        
            break;
        case GpioSettings::Direction::Out:
            result = "none";
            break;
    }
    return result;
}

string GpioThread::pathForGpioNum(const int pinNum)
{
    return string("/sys/class/gpio/gpio") + to_string(pinNum);
}

void GpioThread::threadProc()
{
    auto settings = di_inject(ISettings);

    struct gpio
    {
        int pinNum;
        GpioSettings setting;
        bool correct;
        bool needUnexport;
    };
    list<gpio> correctInfo;
    for (GpioSettings gpioInfo : settings->gpioSettings()) {
        string name = gpioInfo.name;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.size() > 2 && name[0] == 'p' && name[1] >= 'a' && name[1] <= 'z') {
            int base = name[1] - 'a';
            base *= 32;
            string pinNumStr(name.begin() + 2, name.end());
            int add;
            bool ok = false;
            try {
                size_t idx;
                add = std::stoi(pinNumStr, &idx, 10);
                ok = idx == pinNumStr.size();
            } catch (...) {

            }

            if (ok) {
                gpio g;
                g.setting = gpioInfo;
                g.pinNum = base + add;
                g.correct = true;
                g.needUnexport = false;
                correctInfo.push_back(g);
            } else {
                Logger::msg("gpio: can't register gpio '%s': '%s'",
                        gpioInfo.id.data(), gpioInfo.name.data());
                continue;
            }
        }
    }
    static const int delay = 250000;
    for (gpio &g : correctInfo) {
        // сделать проверку?
        if (checkDir(pathForGpioNum(g.pinNum))) {
            unexportGpio(g.pinNum);
        }
    }
    errno = 0;
    usleep(delay);
    for (gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        if (!exportGpio(g.pinNum)) {
            Logger::msg("gpio: can't export gpio %s", g.setting.id.data());
            g.correct = false;
            continue;
        }
    }

    usleep(delay);
    for (gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        string tmp = pathForGpioNum(g.pinNum) + "/value";
        bool ok;
        string data = readFrom(tmp, &ok);
        if (ok && data.size()) {
            g.setting.currentValue = data[1] - '0';
        } else {
            Logger::msg("gpio: can't get gpio %s current state)", g.setting.id.data());
            g.needUnexport = true;
            g.correct = false;
            g.needUnexport = true;
            continue;
        }
    }

    usleep(delay);
    for (gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        string tmp = pathForGpioNum(g.pinNum) + "/direction";
        string data = getDataForDirection(g.setting.direction);
        if (!::writeTo(tmp.data(), data.data(), data.size())) {
            Logger::msg("gpio: can't set gpio %s direction (%s)", g.setting.id.data(), data.data());
            g.needUnexport = true;
            g.correct = false;
            g.needUnexport = true;
            continue;
        }
    }



    usleep(delay);
    for (gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        string tmp = pathForGpioNum(g.pinNum) + "/edge";
        string data = getDataForEdge(g.setting.direction, g.setting.currentValue);
        if (!::writeTo(tmp.data(), data.data(), data.size())) {
            Logger::msg("gpio: can't set gpio %s edge %s mode ", g.setting.id.data(), data.data());
            g.needUnexport = true;
            g.correct = false;
            continue;
        }
    }

    mMutex.lock();
    for (const gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        GpioThread::GpioInfo *newGpio = new GpioThread::GpioInfo;
        newGpio->next = nullptr;
        newGpio->pinId = g.setting.id;
        newGpio->pinName = g.setting.name;
        newGpio->pinNum = g.pinNum;
        newGpio->fd = -1;
        newGpio->direction = g.setting.direction == GpioSettings::Direction::In ?
                GpioThread::GpioInfo::Direction::In :
                GpioThread::GpioInfo::Direction::Out;
        if (mGpioInfoList) {
            GpioThread::GpioInfo *last = mGpioInfoList;
            while (last->next) {
                last = last->next;
            }
            last->next = newGpio;
        } else {
            mGpioInfoList = newGpio;
        }

        Logger::msg("gpio: registered %s gpio '%s': '%s'",
                getDataForDirection(g.setting.direction).data(),
                g.setting.id.data(), g.setting.name.data());
    }
    mMutex.unlock();

    usleep(delay);
    for (const gpio &g : correctInfo) {
        if (g.needUnexport) {
            unexportGpio(g.pinNum);
        }
    }

    threadFunc();
}

void GpioThread::threadFunc()
{
    struct pollfd * poolFd;
    int err;
    char c;
    int idx = 0;
    mMutex.lock();
    auto info = mGpioInfoList;
    while (info) {
        if (info->direction == GpioThread::GpioInfo::Direction::In) {
            ++idx;
        }
        info = info->next;
    }
    mMutex.unlock();

    if (idx == 0) {
        /* нет у нас gpio на вход, нечего и тред занимать*/
        return;
    }

    poolFd = new struct pollfd[idx];
    mMutex.lock();
    info = mGpioInfoList;
    idx = 0;
    while (info) {
        if (info->direction == GpioThread::GpioInfo::Direction::In) {
            string path = pathForGpioNum(info->pinNum) + "/value";
            auto fd = open(path.data(), O_RDONLY);
            if (fd < 0) {
                Logger::msg("gpio: can't start monitor gpio '%s': %s",
                        info->pinId.data(), strerror(errno));
                continue;
            }
            /* заполняем структуру для pool*/
            poolFd[idx].events = POLLPRI | POLLERR;
            poolFd[idx].fd = fd;
            poolFd[idx].revents = 0;
            ++idx;
            info->fd = fd;
        }
        info = info->next;
    }
    mMutex.unlock();

    while (true) {
        for (int i = 0; i < idx; ++i) {
            lseek(poolFd[i].fd, 0, SEEK_SET);
        }
        err = poll(poolFd, idx, 1000);
        // cout << "poll: " << idx << " " << err << endl;
        if (err > 0) {
            for (int i = 0; i < idx; ++i) {
                if (poolFd[i].revents & POLLPRI) {
                    mMutex.lock();
                    info = mGpioInfoList;
                    while (info) {
                        if (info->fd == poolFd[i].fd) {
                            break;
                        }
                        info = info->next;
                    }
                    mMutex.unlock();
                    if (info) {
                        auto bytesRead = read(poolFd[i].fd, &c, 1);
                        if (bytesRead > 0) {
                            int newStatus = c - '0';                            
                            mManager->onGpioStatusChanged(info->pinId, newStatus);
                            // Logger::msg("!!!!gpio: state of gpio pin '%s' change to '%d'", info->pinId.data(), newStatus);                            
                        } else {
                            Logger::msg("gpio: error happens while receiving gpio '%s' (%s) state",
                                    info->pinId.data(), info->pinName.data());
                        }
                    }
                }
            }
        }
    }

    delete[] poolFd;
}

GpioThread::GpioInfo* GpioThread::gpioInfo(const string& gpioId)
{
    lock_guard<mutex> lock(mMutex);
    auto info = mGpioInfoList;
    while (info) {
        if (info->pinId == gpioId) {
            // cout << gpioId << ": " << info->pinId << " " << info->pinName << endl;
            break;
        }
        info = info->next;
    }
    return info;

}

int GpioThread::gpioState(const string& gpioId)
{
    int result = -1;
    auto info = gpioInfo(gpioId);
    if (info) {
        bool ok;
        auto data = readFrom(pathForGpioNum(info->pinNum) + "/value", &ok);
        if (ok && data.size()) {
            result = data[0] == '1' ? 1 : 0;
            Logger::msg("gpio: request state for gpio '%s': state %d",
                    gpioId.data(), result);
        } else {
            Logger::msg("gpio: request state for gpio '%s': unable to get state",
                    gpioId.data());
        }
    } else {
        Logger::msg("gpio: request state for gpio '%s': gpio not found",
                gpioId.data());
    }
    return result;
}

bool GpioThread::setGpioState(const string& gpioId, int state)
{
    static constexpr const char *high_val = "1";
    static constexpr const char *low_val = "0";
    bool result = false;
    const char *var = state ? high_val : low_val;
    auto info = gpioInfo(gpioId);
    if (info) {
        if (info->direction == GpioThread::GpioInfo::Direction::In) {
            Logger::msg("gpio: can't set state for gpio '%s': gpio configured for input",
                    gpioId.data());
        } else {
            if (writeTo(pathForGpioNum(info->pinNum) + "/value", var)) {
                result = true;
                Logger::msg("gpio: set state for gpio '%s' to %s: success",
                        gpioId.data(), var);
            } else {
                Logger::msg("gpio: set state for gpio '%s' to %s: unable to set state",
                        gpioId.data(), var);
            }
        }
    } else {
        Logger::msg("gpio: can't set state for gpio '%s': gpio not found",
                gpioId.data());
    }
    return result;
}

