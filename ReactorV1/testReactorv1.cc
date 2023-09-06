#include "Acceptor.h"
#include "TcpConnection.h"
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
    Acceptor acceptor("127.0.0.1", 10425);
    acceptor.ready(); //处于监听状态

    TcpConnection tcpcon(acceptor.accept());

    //调试
    cout << tcpcon.toString() << "has connected" << endl;

    while(1)
    {
       cout << ">>recv: " << tcpcon.receive() << endl;
       tcpcon.send("hello!");
    }

    return 0;
}
