#include "TcpConnection.h"
#include "ThreadPool.h"
#include "TcpServer.h"
#include <iostream>
#include <cctype>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

class MyTask
{
public:
    MyTask(const TcpConnectionPtr &con, const string & msg)
        :_con(con),
        _msg(msg)
    {

    }

    void process()
    {
        //...........
        //处理业务逻辑
        //..........
        
        for(auto &elem : _msg)
        {
            elem = toupper(elem);
        }

        //在TcpConnection中调用senToLoop函数，让EventLoop把数据发送给客户端
        _con->sendToLoop(_msg);
    }
private:
    TcpConnectionPtr _con;
    string _msg;
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port)
    :_pool(threadNum, queSize),
    _server(ip, port)
    {

    }

    ~EchoServer()
    {

    }

    void start()
    {
        _pool.start();
        using namespace std::placeholders;
        _server.setAll(std::bind(&EchoServer::onNewConnection,this,_1), std::bind(&EchoServer::onMessage,this,_1), std::bind(&EchoServer::onClose,this,_1));
        _server.start();
    }

    void onNewConnection(const TcpConnectionPtr &con)
    {
        cout << con->toString() << " has connected." << endl;
    }

    void onMessage(const TcpConnectionPtr &con)
    {
        //接收数据
        string msg = con->receive();
        cout << "receive msg = " << msg << endl;

        //把任务添加到线程池
        MyTask task(con, msg);
        _pool.addTask(std::bind(&MyTask::process, task));
    }

    void onClose(const TcpConnectionPtr &con)
    {
        cout << con->toString() << " has closed." << endl;
    }

private:
    ThreadPool _pool;
    TcpServer _server;
};
