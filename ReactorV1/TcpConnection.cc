#include "TcpConnection.h"
#include <sstream>

using std::ostringstream;

TcpConnection::TcpConnection(int fd)
:_socket(fd),
_socketIo(fd),
_localAddr(getLocalAddr()),
_peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string & msg)
{
    _socketIo.writen(msg.c_str(), msg.size());
}

string TcpConnection::receive()
{
    char buf[65536] = {0};
    _socketIo.readLine(buf, sizeof(buf));

    return string(buf);
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.getIp() << ":" << _localAddr.getPort() << " ---> " << _peerAddr.getIp() << ":" << _peerAddr.getPort();
    return oss.str();
}

InetAddress TcpConnection::getLocalAddr()
{
    //获取本端地址信息
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = getsockname(_socket.getSocketFd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
    }
    return addr;
}

InetAddress TcpConnection::getPeerAddr()
{
    //获取对端地址信息
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    int ret = getpeername(_socket.getSocketFd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }
    return addr;
}
