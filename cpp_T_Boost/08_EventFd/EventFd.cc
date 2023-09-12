#include "EventFd.h"
#include <unistd.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

EventFd::EventFd(EventFdCallback &&cb)
: _evtfd(createEventFd())
, _isStarted(false)
, _cb(std::move(cb))//注册
{

}

EventFd::~EventFd()
{
    close(_evtfd);
}

//开始与结束函数
void EventFd::start()
{
    //使用IO多路复用进行监听
    struct pollfd pfd;
    pfd.fd = _evtfd;
    pfd.events = POLLIN;

    _isStarted = true;
    while(_isStarted)
    {
        int nready = poll(&pfd, 1, 5000);
        if(-1 == nready && errno == EINTR)
        {
            continue;
        }
        else if(-1 == nready)
        {
            perror("-1 == nready");
            break;
        }
        else if(0 == nready)
        {
            cout << ">>poll timeout!" << endl;
        }
        else
        {
            if(pfd.revents & POLLIN)
            {
                handleRead();//执行read，让其阻塞
                if(_cb)
                {
                    _cb();//将回调函数进行执行
                }
            }
        }
    }
}

void EventFd::stop()
{
    _isStarted = false;
}

//为了给数据成员_evtfd进行初始化
int EventFd::createEventFd()
{
    int fd = eventfd(10, 0);
    if(fd < 0)
    {
        perror("eventfd");
        return fd;
    }

    return fd;
}

//封装read函数，该read函数可以读_evtfd文件描述符
void EventFd::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_evtfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("handleRead");
        return;
    }
}

//封装write函数，该write函数可以写_evtfd文件描述符
void EventFd::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("wakeup");
        return;
    }

}
