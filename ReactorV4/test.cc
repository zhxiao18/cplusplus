#include "TcpConnection.h"
#include "ThreadPool.h"
#include "TcpServer.h"
#include <iostream>
#include <cctype>
#include <functional>

using std::cout;
using std::endl;
using std::bind;

ThreadPool * gPool;

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
    gPool->addTask(std::bind(&MyTask::process, task));
}

void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed." << endl;
}

int main(void)
{
    TcpServer server("127.0.0.1", 10425);
    server.setAll(std::move(onNewConnection), std::move(onMessage), std::move(onClose));

    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;

    server.start();

    return 0;
}
