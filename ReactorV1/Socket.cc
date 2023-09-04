#include "Socket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(_fd < 0)
    {
        perror("socket");
        return;
    }
}

Socket::~Socket()
{
    close(_fd);
}

Socket::Socket(int fd)
:_fd(fd)
{

}

int Socket::fd() const
{
    return _fd;
}
