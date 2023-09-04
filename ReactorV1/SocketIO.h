#ifndef _SOCKETIO_H__
#define _SOCKETIO_H__

class SocketIO
{
public:
    SocketIO(int fd);
    ~SocketIO();
    int writen(const char * buf, int len);
    int readn(char * buf, int len);
    int readLine(char * buf, int len);

private:
    int _fd;
};

#endif


