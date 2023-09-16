#ifndef _TCPSERVER_H__
#define _TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"

class TcpServer
{
public:
    TcpServer(const string & ip, unsigned short port);
    ~TcpServer();
    void start();
    void stop();
    void setAll(TcpConnectionCallback && onNewConnCallback, TcpConnectionCallback && onMessageCallback, TcpConnectionCallback && onCloseCallback);
private:
    Acceptor _acceptor;
    EventLoop _eventLoop;
};

#endif
