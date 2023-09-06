#ifndef _SOCKET_H__
#define _SOCKET_H__

#include "NonCopyable.h"

class Socket
:public NonCopyable
{
public:
    Socket();
    ~Socket();
    explicit Socket(int fd);
    int fd() const;

private:
    int _fd;
};

#endif


