#ifndef _TCPCONNECTION_H__
#define _TCPCONNECTION_H__

#include "NonCopyable.h"
#include "SocketIO.h"
#include "Socket.h"
#include "InetAddress.h"
#include <string>
#include <memory>
#include <functional>

using std::string;
using std::shared_ptr;
using std::function;

class TcpConnection;

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = function<void(const TcpConnectionPtr & con)>;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string &msg);
    string receive();

    // 调试函数
    string toString();
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

    //设置连接建立、连接删除、信息到达三个回调函数
    void setNewConnectioCallback(const TcpConnectionCallback & cb);
    void setMessageCallback(const TcpConnectionCallback & cb);
    void setCloseCallback(const TcpConnectionCallback & cb);

    //执行三个回调函数
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

    bool isClosed();
private:
    SocketIO _sockIO;

    // 调试变量
    Socket _sock;
    InetAddress _localAddr; // 获取本端地址信息
    InetAddress _peerAddr;  // 获取对端地址信息

    //网络连接的三个事件的变量定义
    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

#endif
