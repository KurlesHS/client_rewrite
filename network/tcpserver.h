/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tcpserver.h
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 21:21
 */

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <string>
#include <deque>

#include <ev++.h>

#include "safe_list.h"
#include "tcpsocket.h"

using namespace std;

class TcpSocket;
class TcpServer;

class ITcpServerEvents {
public:
    virtual ~ITcpServerEvents();

    virtual void newConnection(TcpServer *self) = 0;
};

class TcpServer {
public:
    TcpServer(ev::loop_ref loop = 0);
    virtual ~TcpServer();

    bool startListen(int port);
    void close();

    void addServerEventListener(ITcpServerEvents *listener);
    void removeServerEventListener(ITcpServerEvents *listener);

    bool hasPendingConnections() const;
    int pendingConnectionCount() const;

    TcpSocketSharedPrt nextPendingConnection();
    TcpSocketSharedPrt nextPendingConnection(const ev::loop_ref &loop);

protected:
    void emit_newConnection();

private:
    void onNewConnection(ev::io &watcher, int flag);

private:
    int mServerId;
    std::string mError;
    int mMaxClients;
    ev::io mConnectionWatcher;
    deque<int> mPendingClientDescriptors;
    safe_list<ITcpServerEvents *> mEventListeners;
};

#endif /* TCPSERVER_H */

