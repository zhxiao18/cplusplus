#include "TcpConnection.h"

TcpConnection::TcpConnection(int fd)
:_sockIO(fd)
{
    
}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string & msg)
{
    _sockIO.writen(msg.c_str(),msg.size());
}

string TcpConnection::receive()
{
    char buf[4096] = {0};
    _sockIO.readLine(buf, sizeof(buf));
}
