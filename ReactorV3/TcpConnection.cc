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
    socklen_t len = sizeof(struct sockaddr_in);

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
    socklen_t len = sizeof(struct sockaddr_in);

    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
    }
    return InetAddress(addr);
}

bool TcpConnection::isClosed()
{
    char buff[10] = {0};
    //只会将数据拷贝出来，不行将其移除掉
    int ret = ::recv(_sock.fd(), buff, sizeof(buff), MSG_PEEK);
    return (0 == ret);
}

void TcpConnection::setNewConnectioCallback(const TcpConnectionCallback & cb)
{
    _onConnection = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
    _onMessage = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
    _onClose = cb;
}

//执行三个回调函数
void TcpConnection::handleNewConnectionCallback()
{
    if(_onConnection)
    {
        _onConnection(shared_from_this()); 
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage)
    {
        _onMessage(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose)
    {
        _onClose(shared_from_this());
    }
}
