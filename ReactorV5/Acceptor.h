#ifndef _ACCEPTOR_H__
#define _ACCEPTOR_H__

#include "NonCopyable.h"
#include "Socket.h"
#include "InetAddress.h"

class Acceptor
{
public:
    Acceptor(const string &ip, unsigned short port);
    ~Acceptor();
    void ready();
    int accept();
    int fd() const;

private:
    void bind();
    void listen();
    void setReuseAddr();
    void setReusePort();

private:
    Socket _sock;
    InetAddress _addr;
};

#endif
