#ifndef _TCPCONNECTION_H__
#define _TCPCONNECTION_H__

#include "NonCopyable.h"
#include "SocketIO.h"
#include "Socket.h"
#include "InetAddress.h"
#include <string>

using std::string;

class TcpConnection
:public NonCopyable
{
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string & msg);
    string receive();

    //调试函数
    string toString();
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    SocketIO _sockIO;

    //调试变量
    Socket _sock;
    InetAddress _localAddr; //获取本端地址信息
    InetAddress _peerAddr;  //获取对端地址信息
};

#endif


