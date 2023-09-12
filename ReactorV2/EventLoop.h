#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include "Acceptor.h"
#include "TcpConnection.h"
#include <sys/epoll.h>
#include <memory>
#include <vector>
#include <map>
#include <functional>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;

using TcpConnectPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectPtr &con)>;

class EventLoop
{
public:
    EventLoop(Acceptor & accept);
    ~EventLoop();
    void loop();
    void unloop();

    //设置事件函数,只是作为中转，如果TcpConnection在EventLoop类外创建，则不需要
    void setConnectionCallback(TcpConnectionCallback && cb);
    void setMessageCallback(TcpConnectionCallback && cb);
    void setCloseCallback(TcpConnectionCallback && cb);
private:
    int createEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int fd);

private:
    int _epfd;
    bool _isLooping;
    Acceptor & _accept;
    vector<struct epoll_event> _evtList;
    map<int, TcpConnectPtr> _conns;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif
