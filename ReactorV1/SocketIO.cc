#include "SocketIO.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

SocketIO::SocketIO(int fd)
: _fd(fd)
{
}

SocketIO::~SocketIO()
{
    close(_fd);
}

int SocketIO::writen(const char  *buff, int len)
{
    const char * pstr = buff;
    int left = len;
    int ret = 0;

    while(left > 0)
    {
        ret = write(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            //发生中断
            continue;
        }
        else if(-1 == ret)
        {
            //错误
            perror("write error:-1");
            return len - left;
        }
        else if(0 == ret)
        {
            //数据写完了
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SocketIO::readn(char *buff, int len)
{
    char * pstr = buff;
    int left = len;
    int ret = 0;

    while (left > 0)
    {
        ret = read(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("readn error : -1");
            return len - left;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SocketIO::readLine(char *buff, int len)
{
    char * pstr = buff;
    int left = len;
    int ret = 0, total = 0;

    while (left > 0)
    {
        //使用MSG_PEEK是因为不确定是否读到行尾
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("readLine error: -1");
            return len - left;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            //读到行尾
            for(int idx = 0; idx != ret; ++idx)
            {
                if(pstr[idx] == '\n')
                {
                    int size = idx + 1;
                    readn(pstr, size);
                    pstr += size;
                    *pstr = '\0';

                    return total + size;
                }
            }
            //未读到行尾
            readn(pstr, ret);
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
    *pstr = '\0';
    return len - left;
}
