#ifndef _EVENTLOOP_H__
#define _EVENTLOOP_H__

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
private:
    int _epfd;
    bool _isLooping;
    Acceptor & _acceptor; //为了调用_acceptor中的fd()获得socket的fd
    vector<struct epoll_event> _evtList;
    map<int, shared_ptr<TcpConnection>> _conns; //存放文件描述符与Tcp键值对
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif


