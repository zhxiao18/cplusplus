#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> //close
#include <stdio.h> //perror

Socket::Socket(int fd)
:_sockfd(fd)
{

}

Socket::Socket()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd < 0)
    {
        perror("socket init");
        return;
    }
}

Socket::~Socket()
{
    close(_sockfd);
}

int Socket::getSocketFd()
{
    return _sockfd;
}
