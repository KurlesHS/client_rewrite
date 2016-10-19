#include "logger.h"
#include <stdarg.h>
#include <ctime>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <condition_variable>

#include "thread/threadregister.h"

using MutexLocker = lock_guard<mutex>;

static std::string printfIntoString(const char *format, ...)
{
    static char buff[0x400];
    va_list arg;
    va_start(arg, format);
    vsprintf(buff, format, arg);
    va_end(arg);
    return std::string(buff);
}

static int atoiext(const char *str, bool *ok)
{
    // проверка на валидность строки
    *ok = false;
    for (int i = 0; str[i] != 0; ++i) {
        if ((str[i] < '0' || str[i] > '9') && (str[i] != '\n' && str[i] != ' ')) {
            return 0;
        }
    }
    *ok = true;
    return strtol(str, 0, 10);
}

static bool _strcmp(const char *str1, const char *str2)
{
    while (true) {
        if (*str1 == 0x00 || *str2 == 0x00) {
            return true;
        }

        if (*(str1++) != *(str2++)) {
            return false;
        }
    }
}

Logger *Logger::m_instanse = nullptr;

Logger::Logger() :
    m_file(nullptr),
    m_copyToStdout(false),
    m_logFileSize(0),
    mAsync(nullptr)

{
    if (!m_instanse) {
        m_instanse = this;
    }
    mThread = thread([this]() {
        run();
    });
    std::unique_lock<std::mutex> lock(mWaitStartThreadMutex);
    mWaitStartThreadCondVar.wait(lock);
}

void Logger::run()
{
    ev::dynamic_loop loop;
    ThreadRegister::registerCurrentThread(loop);
    ev::async async;
    async.set(loop);
    async.set<Logger, &Logger::onAsync>(this);
    async.start();
    mAsync = &async;
    onAsync();
    mWaitStartThreadCondVar.notify_all();
    loop.run();
    onAsync();

}

void Logger::processMessage(const string& message)
{
    if (m_copyToStdout) {
        cout << message << flush;
    }
    if (m_file) {
        ssize_t len = fputs(message.data(), m_file);
        fflush(m_file);
        if (len < 0) {
            closelogHelper();
            openlogHelper();
            return;
        }
        m_logFileSize += message.length();
        if (m_logFileSize > 0x80000) {
            closelogHelper();
            compressLogInfo *logInfo = new compressLogInfo;
            string oldFileName = m_logFilePath + m_logFileName;
            logInfo->fileTemplate = m_logFileName;
            logInfo->fileToCompress = m_logFileName + ".0";
            logInfo->path = m_logFilePath;
            ::unlink(logInfo->fileToCompress.data());
            int res = ::rename(oldFileName.data(), (m_logFilePath + logInfo->fileToCompress).data());
            if (res == 0) {
                pthread_t thread;
                int result = pthread_create(&thread, NULL, &Logger::compressLogThreadFunc, logInfo);
                if (result != 0) {
                    compressLog(logInfo);
                    delete logInfo;
                }
            }
            openlogHelper();
        }
    }
}

void Logger::onAsync()
{
    while (true) {
        mMutex.lock();
        if (mMessages.empty()) {
            mMutex.unlock();
            break;
        }
        string message = mMessages.front();
        mMessages.pop();
        mMutex.unlock();
        processMessage(message);
    }

}

void Logger::openlogHelper(const string &path, const string &logfilename)
{
    if (!path.empty()) {
        m_logFilePath = path;
    }
    if (!logfilename.empty()) {
        m_logFileName = logfilename;
    }

    if (m_file == nullptr) {
        string filePath = m_logFilePath + m_logFileName;
        m_file = fopen(filePath.data(), "a");
        if (m_file) {
            m_logFileSize = ftell(m_file);
        }
    }
}

void Logger::closelogHelper()
{
    if (m_file) {
        fclose(m_file);
        m_file = nullptr;
    }
}

void Logger::msgHelper(const char *message)
{
    mMutex.lock();
    mMessages.push(string(message));
    mMutex.unlock();
    if (mAsync) {
        mAsync->send();
    }
}

void Logger::compressLog(Logger::compressLogInfo * const logInfo)
{
    if (logInfo) {
        int num = maxNumInDir(logInfo->path.data(), logInfo->fileTemplate.data()) + 1;
        string fileToCompress = logInfo->path + logInfo->fileToCompress;
        string resultFile = logInfo->path + printfIntoString("%s.%d.gz", logInfo->fileTemplate.data(), num);
        //gzip -c archivefile1.txt > archivefile1.txt.gz
        string cmdToExecute = printfIntoString("/bin/gzip -c %s > %s", fileToCompress.data(), resultFile.data());
        cout << cmdToExecute.data() << endl;
        int res = system(cmdToExecute.data());
        (void) res;
    }
}

size_t Logger::maxNumInDir(const char *dir, const char *filter)
{
    DIR *d;
    struct dirent *pDir;
    if (strlen(dir) > 0) {
        d = opendir(dir);
    } else {
        d = opendir(".");
    }
    size_t maxNum = 0;
    if (d) {
        while ((pDir = readdir(d)) != NULL) {
            maxNum = Logger::maxNum(pDir->d_name, filter, maxNum);
        }
        closedir(d);
    }
    return maxNum;
}

void *Logger::compressLogThreadFunc(void *arg)
{
    compressLogInfo *logInfo = (compressLogInfo*) arg;
    if (logInfo) {
        compressLog(logInfo);
        delete logInfo;
    }
    return NULL;
}

size_t Logger::maxNum(const char *pattern, const char *filter, size_t prevMaxNum)
{
    size_t sizeOfFilter = strlen(filter);
    size_t sizeOfPattern = strlen(pattern);
    if (sizeOfPattern >= sizeOfFilter + 5) {
        if (_strcmp(filter, pattern)) {
            while (true) {
                const char *x = pattern + sizeOfFilter;
                if (*x != '.') {
                    break;
                }
                ++x;
                int l = strlen(x);
                if (l < 4) {
                    break;
                }
                string extension(x + l - 3);
                if (extension != ".gz") {
                    break;
                }
                string numStr(x, l - 3);
                bool ok;
                size_t num = atoiext(numStr.data(), &ok);
                if (ok && num > prevMaxNum) {
                    prevMaxNum = num;
                }
                break;
            }
        }
    }
    return prevMaxNum;
}

void Logger::openlog(const string &path, const string &logfilename)
{
    if (m_instanse) {
        m_instanse->openlogHelper(path, logfilename);
    }

}

void Logger::closelog()
{
    if (m_instanse) {
        m_instanse->closelogHelper();
    }

}

void Logger::msg(const char *format, ...)
{
    if (!m_instanse) {
        return;
    }
    static char buff[0x400];
    static char timebuf[80];
    struct tm tstruct;
    time_t now = time(0);
    tstruct = *localtime(&now);
    strftime(timebuf, sizeof (timebuf), "%Y-%m-%d %X", &tstruct);

    static const char str[] = "%s [sonet-hardware-server] %s\n";

    if (m_instanse) {
        va_list arg;
        va_start(arg, format);
        int len = vsprintf(buff, format, arg);
        va_end(arg);
        if (len > 0) {
            string resStr = printfIntoString(str, timebuf, buff);
            m_instanse->msgHelper(resStr.data());
        }
    }
}

void Logger::msg(const string &str)
{
    msg(str.data());
}

void Logger::createInstanse()
{
    if (!m_instanse) {
        m_instanse = new Logger();
    }
}

void Logger::setCopyToStdoutEnabled(const bool enabled)
{
    if (m_instanse) {
        m_instanse->m_copyToStdout = enabled;
    }
}