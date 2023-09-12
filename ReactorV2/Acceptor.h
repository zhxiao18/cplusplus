#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"
#include <string>

using std::string;

class Acceptor
{
public:
    Acceptor(const string & ip, unsigned short port);
    ~Acceptor();
    void ready();
    int accept();
    int getFd();
private:
    void bind();
    void listen();
    void setIpReuse();
    void setPortReuse();
private:
    Socket _socket;
    InetAddress _addr;
};

#endif

