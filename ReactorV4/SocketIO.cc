#include "SocketIO.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

SocketIO::SocketIO(int fd)
:_fd(fd)
{

}

SocketIO::~SocketIO()
{
    close(_fd);
}

int SocketIO::writen(const char * buf, int len)
{
   int left = len;
   const char * pstr = buf;
   int ret = 0;

   while(left > 0)
   {
       ret = write(_fd, pstr, left);
       if(-1 == ret && errno == EINTR)
       {
           continue;
       }
       else if(-1 == ret)
       {
           perror("writen errno = -1");
           return len - ret;
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
   return len = left;
}

int SocketIO::readn(char * buf, int len)
{
    int left = len;
    char * pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = read(_fd, pstr, left);

        if(-1 == ret && errno == EINTR) //中断
        {
            continue;
        }
        else if(-1 == ret) //异常
        {
            perror("read errno = -1");
            return len - ret;
        }
        else if(0 == ret) //断开链接
        {
            break;
        }
        else{
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SocketIO::readLine(char * buf, int len)
{
    int left = len - 1;
    char * pstr = buf;
    int ret = 0, total = 0;

    while(left > 0)
    {
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("readline errno = -1");
            return len - ret; 
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            for(int idx = 0; idx < ret; ++idx)
            {
                if(pstr[idx] == '\n')
                {
                    int sz = idx + 1;
                    readn(pstr, sz);
                    pstr += sz;
                    *pstr = '\0';
                    return total + sz;
                }
            }
            readn(pstr, ret);
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
}
