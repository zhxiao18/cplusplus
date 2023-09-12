#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket
{
public:
    explicit Socket(int fd);
    Socket();
    ~Socket();
    int getSocketFd();
private:
    int _sockfd;
};

#endif


