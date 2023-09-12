#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

class SocketIO
{
public:
    SocketIO(int fd);
    ~SocketIO();
    int writen(const char *buff, int len);
    int readn(char *buff, int len);
    int readLine(char *buff, int len);

private:
    int _fd;
};

#endif
