#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;


class TcpConnection
:public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectPtr &con)>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string & msg);
    string receive();
    string toString();

    //注册三个回调函数
    //只能使用const左值引用，不能使用右值引用
    void setNewConnectionCallback(const TcpConnectionCallback & cb);
    void setMessageCallback(const TcpConnectionCallback & cb);
    void setCloseCallback(const TcpConnectionCallback & cb);
    //执行三个回调函数
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

    //在EventLoop中调用
    bool isClosed();
private:
    //调试函数
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
private:
    Socket _socket;
    SocketIO _socketIo;
    InetAddress _localAddr;
    InetAddress _peerAddr;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif


