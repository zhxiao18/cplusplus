#ifndef __EVENTFD_H__
#define __EVENTFD_H__

#include <functional>

using std::function;

class EventFd
{
    using EventFdCallback = function<void()>;
public:
    EventFd(EventFdCallback &&cb);
    ~EventFd();

    //开始与结束函数
    void start();
    void stop();
    
private:
    //为了给数据成员_evtfd进行初始化
    int createEventFd();

    //封装read函数，该read函数可以读_evtfd文件描述符
    void handleRead();
public:
    //封装write函数，该write函数可以写_evtfd文件描述符
    void wakeup();


private:
    int _evtfd;//由eventfd返回的文件描述符
    bool _isStarted;//标识EventFd是否在运行
    EventFdCallback _cb;

};

#endif
