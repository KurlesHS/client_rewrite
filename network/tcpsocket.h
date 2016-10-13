/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tcpsocket.h
 * Author: Alexey
 *
 * Created on 11 октября 2016 г., 21:47
 */

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <ev++.h>
#include <string>
#include <vector>

#include "itransport.h"

class TcpSocket;

using namespace std;
using TcpSocketSharedPrt = shared_ptr<TcpSocket>;

class TcpSocket : public ITransport {
public:
    TcpSocket(ev::loop_ref loop = nullptr);
    TcpSocket(const int socketDescriptor, ev::loop_ref loop = nullptr);
    virtual ~TcpSocket();

    int bytesAvailable() const override;
    void close() override;
    bool isOpen() const override;
    std::string peerAddress() const override;
    int read(char* buff, int len) override;
    int write(const char* buff, int len) override;

private:
    void onReadWriteEvent(ev::io &watcher, int flag);
    
    void readCallback();
    void writeCallback();
    void errorCallback();
       

private:
    int mSocketDescriptor;
    ev::io mReadWriteWatcher;
    
    int mReadOffset;
    int mWriteLen;
    std::vector<char> mReadBuff;
    std::vector<char> mWriteBuff;
    std::string mPeerAddress;
};

#endif /* TCPSOCKET_H */

