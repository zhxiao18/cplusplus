#include "TimerFd.h"
#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

TimerFd::TimerFd(int initSec, int periodicSec, TimerFdCallback &&cb)
: _timerfd(createTimerFd())
, _initSec(initSec)
, _periodicSec(periodicSec)
, _isStarted(false)
, _cb(std::move(cb))//注册
{

}

TimerFd::~TimerFd()
{
    //停定时器
    close(_timerfd);
}

//开始与结束函数
void TimerFd::start()
{
    //使用IO多路复用进行监听
    struct pollfd pfd;
    pfd.fd = _timerfd;
    pfd.events = POLLIN;

    //设置定时器
    setTimerFd(_initSec, _periodicSec);

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

void TimerFd::stop()
{
    if(_isStarted)
    {
        _isStarted = false;
        setTimerFd(0, 0);
    }
}

//为了给数据成员_evtfd进行初始化
int TimerFd::createTimerFd()
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if(fd < 0)
    {
        perror("timerfd_create");
        return fd;
    }

    return fd;
}

//封装read函数，该read函数可以读_evtfd文件描述符
void TimerFd::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_timerfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("handleRead");
        return;
    }
}
void TimerFd::setTimerFd(int initSec, int periodicSec)
{
    struct itimerspec newValue;

    newValue.it_value.tv_sec = initSec;
    newValue.it_value.tv_nsec = 0;

    newValue.it_interval.tv_sec = periodicSec;
    newValue.it_interval.tv_nsec = 0;

    int ret = timerfd_settime(_timerfd, 0, &newValue, nullptr);
    if(ret < 0)
    {
        perror("setTimerfd");
        return;
    }
}
