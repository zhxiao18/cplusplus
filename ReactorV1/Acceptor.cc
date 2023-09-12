#include "Acceptor.h"

Acceptor::Acceptor(const string & ip, unsigned short port)
:_socket(),
_addr(ip, port)
{

}

Acceptor::~Acceptor()
{

}

void Acceptor::ready()
{
    setIpReuse();
    setPortReuse();
    bind();
    listen();
}

int Acceptor::accept()
{
    int accfd = ::accept(_socket.getSocketFd(), nullptr, nullptr);
    if(-1 == accfd)
    {
        perror("accept");
        return accfd;
    }
    return accfd;
}

void Acceptor::bind()
{
    int ret = ::bind(_socket.getSocketFd(), (struct sockaddr *)_addr.getInetaddressPtr(), sizeof(struct sockaddr));
    if(-1 == ret)
    {
        perror("bind");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_socket.getSocketFd(), 128);
    if(-1 == ret)
    {
        perror("listen");
        return;
    }
}

void Acceptor::setIpReuse()
{
    int opt = 1;
    int ret = setsockopt(_socket.getSocketFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(-1 == ret)
    {
        perror("setsockopt ip");
        return;
    }
}

void Acceptor::setPortReuse()
{
    int opt = 1;
    int ret = setsockopt(_socket.getSocketFd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(-1 == ret)
    {
        perror("setsockopt port");
        return;
    }
}
