/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   tcpserver.cpp
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 21:21
 */

#include "tcpserver.h"

#include "thread/threadregister.h"
#include "tcpsocket.h"
#include "ioc/resolver.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <resolv.h>
#include <errno.h>
#include <fcntl.h>
#include <list>
#include <iostream>

static int setnonblock(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;

    return fcntl(fd, F_SETFL, flags);
}

ITcpServerEvents::~ITcpServerEvents()
{

}

TcpServer::TcpServer(ev::loop_ref loop) :
    mServerId(-1),
    mMaxClients(10000)
{
    if (!loop.raw_loop) {
        loop = ThreadRegister::loopForCurrentThread();
    }
    mConnectionWatcher.set(loop);
    mConnectionWatcher.set<TcpServer, &TcpServer::onNewConnection>(this);
}

void TcpServer::onNewConnection(ev::io& watcher, int flag)
{
    (void) watcher;
    (void) flag;
    socklen_t len = sizeof(sockaddr);
    sockaddr_in client_addr;
    int client_sd = accept(watcher.fd, (sockaddr*) & client_addr, &len);

    if (client_sd < 0) {
        cout << "errno: " << errno << ", " << strerror(errno) << endl;
        return;
    }
    setnonblock(client_sd);
    mPendingClientDescriptors.emplace_back(client_sd);
    emit_newConnection();
}

bool TcpServer::hasPendingConnections() const
{
    return !mPendingClientDescriptors.empty();
}

int TcpServer::pendingConnectionCount() const
{
    return mPendingClientDescriptors.size();
}

TcpSocketSharedPrt TcpServer::nextPendingConnection(const ev::loop_ref& loop)
{
    if (hasPendingConnections()) {
        if (loop.raw_loop) {
            auto it = mPendingClientDescriptors.front();
            mPendingClientDescriptors.pop_front();
            return std::make_shared<TcpSocket>(it, loop);
        }
    }
    return nullptr;
}

TcpSocketSharedPrt TcpServer::nextPendingConnection()
{
    if (hasPendingConnections()) {
        auto loop = ThreadRegister::loopForCurrentThread();
        if (loop.raw_loop) {
            auto it = mPendingClientDescriptors.front();
            mPendingClientDescriptors.pop_front();
            return std::make_shared<TcpSocket>(it, loop);
        }
    }
    return nullptr;
}

void TcpServer::close()
{
    // закрываем так же все ожидающие подключения
    for (const int socketDescripror : mPendingClientDescriptors) {
        ::close(socketDescripror);
    }
    if (mServerId >= 0) {
        ::close(mServerId);
        mServerId = -1;
    }
}

TcpServer::~TcpServer()
{
    // перед уничтожением сервера закрываем соединения и прослушку
    close();
}

bool TcpServer::startListen(int port)
{
    if (mServerId >= 0) {
        // уже слушаем порт
        mError = "already binged";
        return false;
    }
    mServerId = socket(PF_INET, SOCK_STREAM, 0);

    if (mServerId < 0) {
        mError = "socket error";
        return false;
    }

    setnonblock(mServerId);
    struct sockaddr_in addr;
    bzero(&addr, sizeof (sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // для быстрого перебиндивания порта....
    int yes = 1;
    if (setsockopt(mServerId, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (yes)) == 1) {
        mError = "setsockopt error";
        goto on_error;
    }

    if (bind(mServerId, (struct sockaddr *) &addr, sizeof (addr)) != 0) {
        mError = "bind error";
        goto on_error;
    }

    if (::listen(mServerId, mMaxClients) == 0) {
        mConnectionWatcher.start(mServerId, EV_READ);
        return true;
    }
    mError = "can't start listening port";
on_error:
    ::close(mServerId);
    mServerId = -1;
    return false;
}

void TcpServer::addServerEventListener(ITcpServerEvents* listener)
{
    mEventListeners.emplace_back(listener);
}

void TcpServer::removeServerEventListener(ITcpServerEvents* listener)
{
    mEventListeners.remove(listener);
}

void TcpServer::emit_newConnection()
{
    for (const auto listener : mEventListeners) {
        listener->newConnection(this);
    }
}
