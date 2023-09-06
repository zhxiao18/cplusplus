#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include <iostream>

using std::cout;
using std::endl;

void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected." << endl;
    cout << "connected" << endl;
}

void onMessage(const TcpConnectionPtr &con)
{
    // 接受客户端数据
    string msg = con->receive();
    cout << ">>receive client: " << msg << endl;
    //.....
    // 业务逻辑
    // 。。。。
    con->send(msg);
}

void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed" << endl;
    cout << "closed" << endl;
}

int main(void)
{
    Acceptor acceptor("127.0.0.1", 12345);
    acceptor.ready(); // 处于监听状态

    EventLoop loop(acceptor);

    loop.setNewConnectionCallback(std::move(onNewConnection));
    loop.setMessageCallback(std::move(onMessage));
    loop.setCloseCallback(std::move(onClose));

    loop.loop();
    return 0;
}
