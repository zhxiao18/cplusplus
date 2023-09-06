#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"
#include <unistd.h>
#include <iostream>

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd()),
_isLooping(false),
_acceptor(acceptor),
_evtList(1024)
{
    addEpollReadFd(_acceptor.fd());
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

void EventLoop::loop()
{
    _isLooping = true;
    while (_isLooping)
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
    if (fd < 0)
    {
        perror("epoll_create");
    }
    return fd;
}
void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onConnection = std::move(cb);
}
void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessage = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onClose = std::move(cb);
}

void EventLoop::waitEpollFd()
{
    int nready = 0;
    do{
        nready = ::epoll_wait(_epfd, _evtList.data(), _evtList.size(), 3000);
    } while (-1 == nready && errno == EINTR);
    if(-1 == nready)
    {
        perror("epoll_wait nready = -1");
    }
    else if(0 == nready)
    {
        std::cout << ">>epoll_wait timeout" << std::endl;
    }
    else
    {
        //监听的文件描述符超过上限，扩容
        if(nready == _evtList.size())
        {
            _evtList.resize(2 * nready);
        }

        for(int idx = 0; idx < nready; ++idx)
        {
            int fd = _evtList[idx].data.fd;
            if(_acceptor.fd() == fd) //代表有新链接过来
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleNewConnection();
                }
            }
            else
            {
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
    //1、返回文件描述符.
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }

    //2、把文件描述符放入监听队列
    addEpollReadFd(connfd);

    //3、如果connfd正确，连接就已经建立，
    TcpConnectionPtr tcpCon(new TcpConnection(connfd));
    //注册网络通信的三个事件
    tcpCon->setNewConnectioCallback(_onConnection);
    tcpCon->setMessageCallback(_onMessage);
    tcpCon->setCloseCallback(_onClose);

    //4、将connfd与TcpConnection键值对放入map
    _conns.insert(std::make_pair(connfd, tcpCon));
    tcpCon->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    //连接存在
    if(it != _conns.end())
    {
        bool flag = it->second->isClosed();//判断读操作是否结束
        if(flag)
        {
            it->second->handleCloseCallback();  //执行连接断开事件
            delEpollReadFd(fd); //将监听结点从红黑树上删除
            _conns.erase(it);
        }
        else
        {
            it->second->handleMessageCallback();//执行消息到达事件
        }
    }
    else
    {
        std::cout << "连接不存在" << std::endl;
        return;
    }
}

void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;
    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if (ret < 0)
    {
        perror("EPOLL_CTL_ADD");
        return;
    }
}

void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;
    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if (ret < 0)
    {
        perror("EPOLL_CTL_DEL");
        return;
    }
}
