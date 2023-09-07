#ifndef __EVENTFD_H__
#define __EVENTFD_H__

#include <functional>

using std::function;

class EventFd
{
    using EventFdCallback = function<void()>; 
public:
    EventFd(EventFdCallback && cb);
    ~EventFd();
    void start();
    void stop();
    void wakeup();
private:
    int createEventFd();//创建EventFd
    void handleRead();//读_evfd
private:
    int _evtfd;//Event返回的文件描述符
    bool _isRunning;//标识EventFd是否在运行
    EventFdCallback _cb;//回调函数
};

#endif


