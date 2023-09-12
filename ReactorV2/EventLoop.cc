#include "EventLoop.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <iostream>

EventLoop::EventLoop(Acceptor & accept)
:_epfd(createEpollFd()),
_isLooping(false),
_accept(accept),
_evtList(1024) //同时监听的文件描述符上限
{
    addEpollReadFd(_accept.getFd());
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

//事件循环
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping)
    {
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    _isLooping = false;
}

int EventLoop::createEpollFd()
{
    int fd = epoll_create(1);
    if(fd < 0)
    {
        perror("epoll_create");
        return fd;
    }
    return fd;
}

//将文件描述符添加到红黑树上
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(-1 == ret)
    {
        perror("epoll_ctl_add error : -1");
        return;
    }
}

void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(-1 == ret)
    {
        perror("epoll_ctl_del error : -1");
        return;
    }
}

void EventLoop::waitEpollFd()
{
    int ret;
    do{
        ret = ::epoll_wait(_epfd, _evtList.data(), _evtList.size(), 3000);
    }while(-1 == ret && errno == EINTR);

    if(-1 == ret)
    {
        perror("epoll_wait: errno = -1");
    }
    else if(0 == ret)
    {
        /* perror(">>epoll_wait timeout."); */
        std::cout << "epoll_wait timeout!" << std::endl;
    }
    else
    {
        //监听的文件描述符超过上限
        if(ret == (int)_evtList.size())
        {
            _evtList.resize(2 * ret);
        }

        //遍历所有的就绪文件描述符
        for(int idx = 0; idx != ret; ++idx)
        {
            int fd = _evtList[idx].data.fd;
            if(_accept.getFd() == fd)
            {
                //fd与监听套接字的文件描述符相等，代表有新的连接过来
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleNewConnection();
                }
            }
            else
            {
                //旧链接发送消息过来了
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleMessage(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int connfd = _accept.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }

    addEpollReadFd(connfd);

    TcpConnectPtr tcpconn(new TcpConnection(connfd));

    //在此注册三个事件
    tcpconn->setNewConnectionCallback(_onConnection);
    tcpconn->setMessageCallback(_onMessage);
    tcpconn->setCloseCallback(_onClose);

    _conns.insert(std::make_pair(connfd, tcpconn));

    //执行连接建立事件
    tcpconn->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);

    //连接存在
    if(it != _conns.end())
    {
        
        bool flag = it->second->isClosed();
        //连接断开
        if(flag)
        {
            it->second->handleCloseCallback();
            delEpollReadFd(fd);
            _conns.erase(it);
        }
        //连接未断开
        else
        {
            it->second->handleMessageCallback();
        }
    }
    else
    {
        std::cout << "连接不存在。" << std::endl;
        return;
    }
}

void EventLoop::setConnectionCallback(TcpConnectionCallback && cb)
{
    _onConnection = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback && cb)
{
    _onMessage = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback && cb)
{
    _onClose = std::move(cb);
}
