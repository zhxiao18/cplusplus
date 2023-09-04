#ifndef _TCPCONNECTION_H__
#define _TCPCONNECTION_H__

#include "NonCopyable.h"
#include "SocketIO.h"
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
private:
    SocketIO _sockIO;
};

#endif


