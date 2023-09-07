#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

ThreadPool *gPool = nullptr;

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
        /* _msg; */
        //数据_msg就可以拿到本函数中进行执行
        //...
        //....
        //...
        /* string msg1 = _msg; */
        //在此处需要将处理好之后的数据发送给EventLoop
        //然后让EventLoop/Reactor将处理好之后的msg1
        //发送给客户端
        //线程池处理好业务逻辑之后，也就是从msg变为了
        //msg1，然后将数据发送给EventLoop，因为线程池
        //只具备处理业务逻辑的能力，不具备收发数据的
        //能力，所以需要将数据msg1发送给EventLoop
        //
        //现在线程池处理好数据之后，需要告知Reactor/EventLoop
        //此时可以停下来去接收我线程池处理好之后的数据
        //
        //现在的问题是线程池如何与Reactor/EventLoop之间进行通信？
        //进程或者线程之间进行通信有一种方法：eventfd
        _con->sendInLoop(_msg);
    }
private:
    TcpConnectionPtr _con;
    string _msg;
};

void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!" << endl;
}

void onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();
    cout << ">>recv client msg = " << msg << endl;
    //msg做处理之后再发给客户端也可以
    //可以写业务逻辑
    //msg经过处理之后的数据称为msg1
    //假如将msg处理之后变为的msg1的业务逻辑处理比较复杂
    //decode、compute、encode如果花费是时间比较久，那么
    //处理业务逻辑就变为成V3版本的瓶颈，所以就可考虑将
    //业务逻辑的处理交给线程池
    //msg = "hello"
    //msg1 = HeLlO
    MyTask task(con, msg);
    gPool->addTask(std::bind(&MyTask::process, task));
}

void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!" << endl;
}

void test()
{
    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallback(std::move(onNewConnection)
                          , std::move(onMessage)
                          , std::move(onClose));
    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}

