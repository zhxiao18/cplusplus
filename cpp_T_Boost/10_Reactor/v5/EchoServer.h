#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class MyTask
{
public:
    MyTask(const TcpConnectionPtr &con, const string &msg)
    : _con(con)
    , _msg(msg)
    {

    }
    void process()
    {
        _con->sendInLoop(_msg);
    }
private:
    TcpConnectionPtr _con;
    string _msg;
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize
               , const string &ip
               , unsigned short port)
    : _pool(threadNum, queSize)
    , _server(ip, port)
    {

    }

    ~EchoServer()
    {

    }

    void start()
    {
        _pool.start();
        using namespace std::placeholders;
        _server.setAllCallback(std::bind(&EchoServer::onNewConnection, this, _1)
                               , std::bind(&EchoServer::onMessage, this, _1)
                               , std::bind(&EchoServer::onClose, this, _1));
        _server.start();
    }

    void stop()
    {
        _pool.stop();
        _server.stop();
    }

    void onNewConnection(const TcpConnectionPtr &con)
    {
        cout << con->toString() << " has connected!" << endl;
    }
    
    void onMessage(const TcpConnectionPtr &con)
    {
        string msg = con->receive();
        cout << ">>recv client msg = " << msg << endl;
    
        MyTask task(con, msg);
        _pool.addTask(std::bind(&MyTask::process, task));
    }
    
    void onClose(const TcpConnectionPtr &con)
    {
        cout << con->toString() << " has closed!" << endl;
    }
private:
    ThreadPool _pool;
    TcpServer _server;
};



#endif
