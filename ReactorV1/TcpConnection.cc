#include "TcpConnection.h"
#include <sstream>

using std::ostringstream;

TcpConnection::TcpConnection(int fd)
:_sockIO(fd),
_sock(fd),
_localAddr(getLocalAddr()),
_peerAddr(getPeerAddr())
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
    return string(buf);
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":" << _localAddr.port() << "->" << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);

    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }
    return InetAddress(addr);
}

//获取对端网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);

    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }
    return InetAddress(addr);
}