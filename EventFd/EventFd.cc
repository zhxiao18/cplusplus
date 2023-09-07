#include "EventFd.h"
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#include <sys/eventfd.h>
#include <iostream>

EventFd::EventFd(EventFdCallback && cb)
:_evtfd(createEventFd())
,_isRunning(false)
,_cb(std::move(cb))
{

}

EventFd::~EventFd()
{
    close(_evtfd);
}

void EventFd::start()
{
    //使用poll监听
    struct pollfd pfd;
    pfd.fd = _evtfd;
    pfd.events = POLLIN;

    _isRunning = true;
    while(_isRunning)
    {
        int nready = poll(&pfd, 1, 3000);
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
            std::cout << ">>poll timeout." << std::endl;
        }
        else
        {
            if(pfd.revents & POLLIN)
            {
                handleRead(); //执行read，让其阻塞
                if(_cb)
                {
                    _cb();
                }
            }
        }
    }
}

void EventFd::stop()
{
    _isRunning = false;
}

void EventFd::wakeup()
{
    uint64_t num = 1;
    int ret = write(_evtfd, &num, sizeof(num));
    if(ret != sizeof(num))
    {
        perror("wakeup");
        return;
    }
}

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

void EventFd::handleRead()
{
    uint64_t num = 1;
    int ret = read(_evtfd, &num, sizeof(num));
    if(ret != sizeof(num))
    {
        perror("handleRead");
        return;
    }
}
