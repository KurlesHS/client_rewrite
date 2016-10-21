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

#include <algorithm>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>

GpioThread::GpioThread()
{

}

GpioThread::~GpioThread()
{

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
        cout << data << " > " << path << " " << strerror(err) << " " << err << " "
                << result << " == " << size << endl;

    }
    return result;
}

static bool exportGpio(int gpioNum)
{
    string strPinNum = to_string(gpioNum);
    return writeTo("/sys/class/gpio/export", strPinNum.data(), strPinNum.size());
}

static bool unexportGpio(int gpioNum)
{
    string strPinNum = to_string(gpioNum);
    return writeTo("/sys/class/gpio/unexport", strPinNum.data(), strPinNum.size());
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

static string getDataForEdge(GpioSettings::Direction direction)
{
    string result;
    switch (direction) {
        case GpioSettings::Direction::In:
            result = "rising";
            break;
        case GpioSettings::Direction::Out:
            result = "none";
            break;
    }
    return result;
}

string pathForGpioNum(const int pinNum)
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
                Logger::msg("can't register gpio '%s': '%s'",
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
            Logger::msg("can't export gpio %s", g.setting.id.data());
            g.correct = false;
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
        if (!writeTo(tmp.data(), data.data(), data.size())) {
            Logger::msg("can't set gpio %s direction (%s)", g.setting.id.data(), data.data());
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
        string data = getDataForEdge(g.setting.direction);
        if (!writeTo(tmp.data(), data.data(), data.size())) {
            Logger::msg("can't set gpio %s edge %s mode ", g.setting.id.data(), data.data());
            g.needUnexport = true;
            g.correct = false;
            continue;
        }
    }

    for (const gpio &g : correctInfo) {
        if (!g.correct) {
            continue;
        }
        Logger::msg("registered %s gpio '%s': '%s'",
                getDataForDirection(g.setting.direction).data(),
                g.setting.id.data(), g.setting.name.data());
    }

    usleep(delay);
    for (const gpio &g : correctInfo) {
        if (g.needUnexport) {
            unexportGpio(g.pinNum);
        }
    }
}



