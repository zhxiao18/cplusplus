#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtfd(createEventFd())
, _isLooping(false)
, _acceptor(acceptor)
, _evtList(1024)
, _mutex()
{
    //将文件描述符listenfd放在红黑树上进行监听
    //该listenfd就是Socket类创建的数据成员
    addEpollReadFd(_acceptor.fd());
    //监听_evtfd
    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
    close(_evtfd);
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

//事件不循环
void EventLoop::unloop()
{
    _isLooping = false;
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

//在其中封装::epoll_wait
void EventLoop::waitEpollFd()
{
    int nready = 0;
    do{
        nready = ::epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    }while(-1 == nready && errno == EINTR);

    if(-1 == nready)
    {
        cerr << "-1 == nready" << endl;
    }
    else if(0 == nready)
    {
        cout << ">>epoll_wait timeout"<< endl;
    }
    else
    {
        //监听的文件描述符如果操作了1024
        if(nready == (int)_evtList.size())
        {
            //就可以进行扩容
            _evtList.resize(2 * nready);
        }

        for(int idx = 0; idx < nready; ++idx)
        {
            /* int listenfd = _acceptor.fd(); */
            int fd = _evtList[idx].data.fd;
            //有新的连接请求
            if(_acceptor.fd() == fd)//判断文件描述符是否是listenfd
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleNewConnection();//处理新的连接
                }
            }
            else if(fd == _evtfd)
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleRead();
                    //将所有的任务都进行执行
                    doPengdingFunctors();
                }
            }
            //老的连接上有新的数据发送过来了
            else
            {
                if(_evtList[idx].events & EPOLLIN)
                {
                    handleMessage(fd);//处理消息发送
                }
                
            }
        }
    }
}

//处理新的连接
void EventLoop::handleNewConnection()
{
    //1、调用accept，返回文件描述符
    int connfd = _acceptor.accept();
    if(connfd < 0)
    {
        perror("handleNewConnection");
        return;
    }
    //2、将connfd放在红黑树上进行监听
    //（表明在红黑树进行监听的文件描述符有两类，一类是
    //listenfd，另外一类是：connfd）
    addEpollReadFd(connfd);
    
    //3、如果connfd是正常的，那么就表明三次握手建立成功
    //就可以建立客户端到服务器的TCP连接
    TcpConnectionPtr con(new TcpConnection(connfd, this));
    //处理Tcp网络通信过程中的三个半事件（连接建立、连接断开、消息到达）
    //需要注册这三个事件
    con->setNewConnectionCallback(_onConnection);//注册连接建立的事件
    con->setCloseCallback(_onClose);//注册连接断开的事件
    con->setMessageCallback(_onMessage);//注册消息到达的事件

    //4、就可以将connfd与TcpConnectionPtr的键值对放在map中存起来
    _conns.insert(std::make_pair(connfd, con));

    con->handleNewConnectionCallback();//执行连接建立的事件
}

//进行消息的收发（处理）
void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    //连接是存在的
    if(it != _conns.end())
    {
        //判断进行读操作是否结束
        bool flag = it->second->isClosed();
        if(flag)
        {
            //连接断开
            it->second->handlCloseCallback();//执行连接断开的事件
            delEpollReadFd(fd);//将文件描述符从红黑树上删除
            _conns.erase(it);//将连接从map中删除
        }
        else
        {
            it->second->handleMessageCallback();//执行消息的到达的事件
        }
    }
    else
    {
        cout << "该连接是不存在" << endl;
        return;
    }
}

//创建文件描述符_epfd
int EventLoop::createEpollFd()
{
    int fd = ::epoll_create1(0);
    if(fd < 0)
    {
        perror("epoll_create1");
        return fd;
    }

    return fd;
}

//将文件描述符放在红黑树上进行监听
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;
    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl add");
        return;
    }
}

//将文件描述符从红黑树上摘除
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;
    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0)
    {
        perror("epoll_ctl add");
        return;
    }
}
int EventLoop::createEventFd()
{
    int fd = eventfd(10, 0);
    if(fd < 0)
    {
        perror("eventfd");
        return fd;
    }
    return fd;
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_evtfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("read");
        return;
    }
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(one));
    if(ret != sizeof(one))
    {
        perror("write");
        return;
    }

}
//将vector中的所有任务进行批量执行
void EventLoop::doPengdingFunctors()
{
    //vector<Functor> _pendings;
    vector<Functor> tmp;
    {
        MutexLockGuard autoLock(_mutex);
        tmp.swap(_pendings);
    }

    for(auto &th : tmp)
    {
        th();//其实处理好之后的数据是在此处发送给客户端的
    }
}
void EventLoop::runInLoop(Functor &&cb)
{
    //将发送数据能力的send函数（TcpConnection中）以及
    //处理好之后的msg发送给了EventLoop，并且使用vector
    //将其存起来
    {
        MutexLockGuard autoLock(_mutex);
        _pendings.push_back(std::move(cb));
    }

    //线程池唤醒EventLoop
    wakeup();
}
