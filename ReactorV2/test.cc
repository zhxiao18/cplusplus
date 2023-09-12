#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include <iostream>

using  std::cout;
using  std::endl;

void onConnectionCallback(const TcpConnectPtr & con)
{
    cout << con->toString() << " has connected." << endl;
}

void onMessageCallback(const TcpConnectPtr & con)
{
    cout << ">> " << con->receive() << endl;
    con->send("--msg has received.\n");
}
void onCloseCallback(const TcpConnectPtr & con)
{
    cout << con->toString() << " closed." << endl;
}
int main(void)
{
    Acceptor acceptor("127.0.0.1", 10425);
    //处于监听状态
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setConnectionCallback(std::move(onConnectionCallback));
    loop.setMessageCallback(std::move(onMessageCallback));
    loop.setCloseCallback(std::move(onCloseCallback));

    loop.loop();
    loop.unloop();
    return 0;
}
