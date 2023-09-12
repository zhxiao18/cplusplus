#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //sockaddr_in
#include <string>

using std::string;

class InetAddress
{
public:
    InetAddress(const string & ip, unsigned short port);
    InetAddress(struct sockaddr_in & addr);
    ~InetAddress();
    string getIp() const;
    unsigned short getPort() const;
    const struct sockaddr_in * getInetaddressPtr() const;
private:
    struct sockaddr_in _addr;
};

#endif


