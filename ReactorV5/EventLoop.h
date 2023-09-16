#ifndef _EVENTLOOP_H__
#define _EVENTLOOP_H__

#include "MutexLock.h"
#include <sys/epoll.h>
#include <map>
#include <memory>
#include <functional>
#include <vector>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

class Acceptor;
class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr & con)>;
using Functor = function<void()>;

class EventLoop
{
public:
    EventLoop(Acceptor & acceptor);
    ~EventLoop();
    void loop();
    void unloop();
    void setNewConnectionCallback(TcpConnectionCallback && cb);
    void setMessageCallback(TcpConnectionCallback && cb);
    void setCloseCallback(TcpConnectionCallback && cb);
private:
    //封装epoll_wait
    void waitEpollFd();
    int createEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);

    int createEventFd();
public:
    //执行系统调用ead函数
    void handleRead();
    //执行write函数
    void weakup();
    //执行线程池传递过来的任务
    void doPendingFunctors();
    void runInLoop(Functor &&cb);
private:
    int _epfd;
    bool _isLooping;
    Acceptor & _acceptor; //为了调用_acceptor中的fd()获得socket的fd
    vector<struct epoll_event> _evtList;
    map<int, shared_ptr<TcpConnection>> _conns; //存放文件描述符与Tcp键值对
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;

    int _evtfd; //eventfd返回的文件描述符
    vector<Functor> _pendings;
    MutexLock _mutex;
};

#endif


