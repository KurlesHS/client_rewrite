/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   filedownloader.cpp
 * Author: kurles
 * 
 * Created on 19 октября 2016 г., 11:59
 */

#include "filedownloader.h"
#include "thread/threadregister.h"
#include "logger.h"

#include <sys/ioctl.h>
#include <unistd.h>

static pid_t startWget(const string &serverAddress, const string &hash, int &outFd)
{
    pid_t pid = 0;
    int pipefd[2];

    pipe(pipefd); // Созадём пайп
    pid = fork(); // форкаем 
    if (pid == 0) {
        // Дочернтй процесс

        // закрываем чтение (вход)
        close(pipefd[0]);
        // биндим запись (выход)
        dup2(pipefd[1], STDOUT_FILENO);
        // dup2(pipefd[1], STDERR_FILENO);
        //  wget -O - -o /dev/null http://localhost:8088/get/827717d816d95c60f2059c8be841341897216104100d7b495f04c96f > 1

        string url = serverAddress + "get/" + hash;
        execl("/usr/bin/wget", "/usr/bin/wget", "-O", "-", "-o", "/dev/null", url.data(), (char*) NULL);
    }

    // Родительский процесс
    // закрываем запись (выход)
    close(pipefd[1]);
    outFd = pipefd[0];
    return pid;
}

FileDownloader::FileDownloader(const string &serverAddress, const string &path, const string& hash, const string& fileName, const fileIsDownloadedCallback& callback) :
    mServerAddress(serverAddress),
    mPath(path),
    mHash(hash),
    mFileName(fileName),
    mCallback(callback),
    mFile(NULL),
    mIsStartDownload(false)


{
    mIo.set(ThreadRegister::loopForCurrentThread());
    mIo.set<FileDownloader, &FileDownloader::onIo>(this);
}

FileDownloader::~FileDownloader()
{
}

void FileDownloader::onIo(ev::io& io, int events)
{
    if (events & ev::READ) {
        int count;
        ioctl(io.fd, FIONREAD, &count);
        mBuffer.resize(count);
        int len = read(io.fd, mBuffer.data(), mBuffer.size());
        if (len <= 0) {
            // выход            
            io.stop();
            close(io.fd);
            fclose(mFile);
            if (mIsStartDownload) {
                Logger::msg("file with hash '%s' is downloaded", mHash.data());                
            } else {
                Logger::msg("error hapened while downloading file with hash '%s'", mHash.data());                
            }
            mCallback(mIsStartDownload);
            delete this;
        } else {
            if (!mIsStartDownload) {
                mIsStartDownload = true;
                Logger::msg("started downloading file with hash '%s'", mHash.data());                
            }
            // пишем данные
            fwrite(mBuffer.data(), mBuffer.size(), 1, mFile);
            // nothing to do here.
            //printf("on std err read: %d: %s\n", count, buff.data());
        }
    }
}

void FileDownloader::start()
{
    auto newFilePath = mPath + "/" + mHash + "_" + mFileName;
    mFile = fopen(newFilePath.data(), "wb");
    if (mFile) {
        // тут можно стартовать процесс скачки
        int fd;
        auto pid = startWget(mServerAddress, mHash, fd);
        if (pid > 0) {
            // получилось запустить wget
            mIo.start(fd, ev::READ);
        } else {
            // не получилось запустить wget
            Logger::msg("can't start process for downloading for file hash '%s'", mHash.data());
            // закрываем файл
            fclose(mFile);
            // удаляем его
            unlink(newFilePath.data());
            mCallback(false);
            delete this;
        }
    } else {
        // не получилось открыть файл - дальнейшие манипуляции бессмысленны
        Logger::msg("can't open file for writting for file hash '%s'", mHash.data());
        mCallback(false);
        delete this;
    }

}
