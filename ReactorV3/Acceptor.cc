#include "Acceptor.h"

Acceptor::Acceptor(const string & ip, unsigned short port)
:_sock(),
_addr(ip, port)
{

}

Acceptor::~Acceptor()
{

}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

int Acceptor::accept()
{
    int connfd = ::accept(_sock.fd(), nullptr, nullptr);
    if(-1 == connfd)
    {
        perror("accept");
        return -1;
    }
    return connfd;
}

void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(), (struct sockaddr *)_addr.getInetAddressPtr(), sizeof(struct sockaddr));
    if(-1 == ret)
    {
        perror("bind");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(), 128);
    if(-1 == ret)
    {
        perror("listen");
        return;
    }
}

void Acceptor::setReuseAddr()
{
    int opt = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(-1 == ret)
    {
        perror("setsockopt-addr");
        return;
    }
}

void Acceptor::setReusePort()
{
    int opt = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(-1 == ret)
    {
        perror("setsockopt-port");
        return;
    }
}

int Acceptor::fd() const
{
    return _sock.fd();
}
