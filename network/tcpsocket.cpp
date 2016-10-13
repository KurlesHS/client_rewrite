/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tcpsocket.cpp
 * Author: Alexey
 * 
 * Created on 11 октября 2016 г., 21:47
 */

#include "tcpsocket.h"

#include "thread/threadregister.h"

#include <vector>

#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>

std::string getPeerAddress(const int socketDecsriptor)
{
    if (socketDecsriptor < 0) {
        return string();
    }

    socklen_t len;
    struct sockaddr_storage addr;
    char ipstr[INET6_ADDRSTRLEN + 1];
    int port;
    len = sizeof addr;
    getpeername(socketDecsriptor, (struct sockaddr*) &addr, &len);

    // deal with both IPv4 and IPv6:
    if (addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *) &addr;
        port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
    } else { // AF_INET6
        struct sockaddr_in6 *s = (struct sockaddr_in6 *) &addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
    }
    (void) port;
    return string(ipstr);

}

TcpSocket::TcpSocket(ev::loop_ref loop) :
    mSocketDescriptor(-1),
    mReadOffset(0),
    mWriteLen(0)

{
    mReadBuff.resize(0x1000);
    mWriteBuff.resize(0x1000);

    if (!loop.raw_loop) {
        loop = ThreadRegister::loopForCurrentThread();
    }
    mReadWriteWatcher.set(loop);
    mReadWriteWatcher.set<TcpSocket, &TcpSocket::onReadWriteEvent>(this);
}

TcpSocket::TcpSocket(const int socketDescriptor, ev::loop_ref loop) :
    TcpSocket(loop)
{
    mSocketDescriptor = socketDescriptor;
    mPeerAddress = getPeerAddress(socketDescriptor);
    mReadWriteWatcher.start(socketDescriptor, ev::READ);
}

void TcpSocket::onReadWriteEvent(ev::io& watcher, int flag)
{
    (void) watcher;
    if (flag & ev::ERROR) {
        errorCallback();
    } else {
        if (flag & ev::READ) {
            readCallback();
        }
        if (flag & ev::WRITE) {
            writeCallback();
        }
    }
}

void TcpSocket::errorCallback()
{        
    close();
    emit_disonnected();
}

bool TcpSocket::isOpen() const
{
    return mSocketDescriptor >= 0;
}


void TcpSocket::readCallback()
{
    // кол-во байт, нас ожидающих
    int count;
    ioctl(mSocketDescriptor, FIONREAD, &count);

    uint total = mReadOffset + count;
    if (mReadBuff.size() < total) {
        mReadBuff.resize(total);
    }

    ssize_t nread = recv(mSocketDescriptor, &mReadBuff[mReadOffset], count, 0);

    if (nread < 0) {
        // read error                
        close();
        emit_disonnected();
    } else if (nread == 0) {
        // close event        
        close();
        emit_disonnected();
    } else {
        mReadOffset += nread;
        emit_readyRead();
        // std::cout << nread << std::endl;        
    }
}

void TcpSocket::writeCallback()
{
    if (mWriteLen == 0) {
        mReadWriteWatcher.set(ev::READ);
    } else {
        int count = ::write(mSocketDescriptor, &mWriteBuff[0], mWriteLen);
        if (count < 0) {
            // ошибка            
            close();
            emit_disonnected();
        } else {
            int remain = mWriteLen - count;
            if (remain > 0) {
                memmove(&mWriteBuff[0], &mWriteBuff[count], remain);
            }
            mWriteLen = remain;
            if (mWriteLen == 0) {
                mReadWriteWatcher.set(ev::READ);
            }
        }
    }

}

TcpSocket::~TcpSocket()
{
}

int TcpSocket::bytesAvailable() const
{
    return mReadOffset;
}

void TcpSocket::close()
{
    if (mSocketDescriptor >= 0) {
        mReadWriteWatcher.stop();
        ::close(mSocketDescriptor);
        mSocketDescriptor = -1;
        mWriteLen = 0;
        mReadOffset = 0;
    }
}

std::string TcpSocket::peerAddress() const
{
    return mPeerAddress;
}

int TcpSocket::read(char* buff, int len)
{
    len = mReadOffset < len ? mReadOffset : len;
    int bytesRemain = mReadOffset - len;
    memcpy(buff, &mReadBuff[0], len);
    if (bytesRemain) {
        memmove(&mReadBuff[0], &mReadBuff[len], bytesRemain);
    }
    mReadOffset = bytesRemain;
    return len;

}

int TcpSocket::write(const char* buff, int len)
{
    size_t totalBytes = mWriteLen + len;
    if (mWriteBuff.size() < totalBytes) {
        mWriteBuff.resize(totalBytes);
    }
    memcpy(&mWriteBuff[mWriteLen], buff, len);
    mWriteLen += len;
    mReadWriteWatcher.set(ev::WRITE);

    return len;
}



