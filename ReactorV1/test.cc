//只能监听单个客户端，所以需要封装epoll(V2版本)
#include "Acceptor.h"
#include "TcpConnection.h"
#include <iostream>

using  std::cout;
using  std::endl;

int main(void)
{
    Acceptor acceptor("127.0.0.1", 10425);
    //处于监听状态
    acceptor.ready();

    //三次握手建立成功
    TcpConnection connect(acceptor.accept());

    cout << connect.toString() << endl;

    while (1)
    {
       cout << ">>client: " << connect.receive() << endl;
       connect.send("hello\n"); 
    }
    return 0;
}