#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"

class TcpConnection
{
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string & msg);
    string receive();
    string toString();
private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    Socket _socket;
    SocketIO _socketIo;
    InetAddress _localAddr;
    InetAddress _peerAddr;
};

#endif


