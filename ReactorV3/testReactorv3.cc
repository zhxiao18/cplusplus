#include "TcpServer.h"
#include "TcpConnection.h"
#include <iostream>

using std::cout;
using std::endl;

void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected." << endl;
    /* cout << "connected" << endl; */
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
    /* cout << "closed" << endl; */
}

int main(void)
{
    TcpServer tcpServer("127.0.0.1", 10425);
    tcpServer.setAll(std::move(onNewConnection), std::move(onMessage), std::move(onClose));
    tcpServer.start();
    /* tcpServer.stop(); */
    return 0;
}
