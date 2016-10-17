#ifndef LOGGER_H
#define LOGGER_H

#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <condition_variable>

#include <ev++.h>


using namespace std;
class Logger
{
    struct compressLogInfo {
        string fileToCompress;
        string fileTemplate;
        string path;
    };

public:
    static void openlog(const string &path, const string &logfilename);
    static void closelog();
    static void msg(const char *format, ...);
    static void msg(const string &str);
    static void createInstanse();
    static void setCopyToStdoutEnabled(const bool enabled);
    static size_t maxNum(const char *pattern, const char *filter, size_t prevMaxNum);

private:
    Logger();
    void openlogHelper(const string &path = string(), const string &logfilename = string());
    void closelogHelper();
    void msgHelper(const char *message);
    static size_t maxNumInDir(const char *dir, const char *filter);
    static void* compressLogThreadFunc(void *arg);
    static void compressLog(compressLogInfo * const logInfo);
    
    void run();
    
    void onAsync();
    void processMessage(const string &message);

private:
    static Logger *m_instanse;
    FILE *m_file;
    bool m_copyToStdout;
    size_t m_logFileSize;
    string m_logFilePath;
    string m_logFileName;
    queue<string> mMessages;
    mutex mMutex;
    mutex mWaitStartThreadMutex;
    condition_variable mWaitStartThreadCondVar;
    ev::async *mAsync;
    thread mThread;
    
};

#endif // LOGGER_H