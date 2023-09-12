#ifndef __TIMERFD_H__
#define __TIMERFD_H__


#include <functional>

using std::function;

class TimerFd
{
    using TimerFdCallback = function<void()>;
public:
    TimerFd(int initSec, int periodicSec, TimerFdCallback &&cb);
    ~TimerFd();

    //开始与结束函数
    void start();
    void stop();
    
private:
    //为了给数据成员_evtfd进行初始化
    int createTimerFd();

    //封装read函数，该read函数可以读_evtfd文件描述符
    void handleRead();

    //设置定时器的函数
    void setTimerFd(int initSec, int periodicSec);


private:
    int _timerfd;
    int _initSec;//初始时间
    int _periodicSec;//周期时间
    bool _isStarted;//标识EventFd是否在运行
    TimerFdCallback _cb;

};

#endif
