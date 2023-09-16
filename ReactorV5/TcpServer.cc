#include "TcpServer.h"

TcpServer::TcpServer(const string & ip, unsigned short port)
:_acceptor(ip, port),
_eventLoop(_acceptor)
{

}

TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    _acceptor.ready();
    _eventLoop.loop();
}

void TcpServer::stop()
{
    _eventLoop.unloop();
}

void TcpServer::setAll(TcpConnectionCallback && onNewConnCallback, TcpConnectionCallback && onMessageCallback, TcpConnectionCallback && onCloseCallback)
{
    _eventLoop.setNewConnectionCallback(std::move(onNewConnCallback));
    _eventLoop.setMessageCallback(std::move(onMessageCallback));
    _eventLoop.setCloseCallback(std::move(onCloseCallback));
}
