#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/epoll.h>

#define SERV_PORT 8888
#define OPEN_MAX 5000

int main()
{
    int listenfd, connfd, sockfd, epfd;
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    int ret, i, j, nready, nByte;
    char buf[BUFSIZ], str[BUFSIZ];
    struct epoll_event evt, ep[OPEN_MAX];


    //1、创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd)
    {
        perror("socket error");
        exit(-1);
    }

    //2、地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //3、端口复用
    int opt2 = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2));

    //4、绑定ip与端口号
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(-1 == ret)
    {
        perror("bind error");
        close(listenfd);
        exit(-1);
    }

    //5、服务器监听
    ret = listen(listenfd, 128);
    if(-1 == ret)
    {
        perror("listen error");
        close(listenfd);
        exit(-1);
    }
    printf("server is listening...\n");

    //6、epoll类型IO多路复用
    //创建红黑树的根节点（使用数据结构：红黑树 + 就绪链表）
    epfd = epoll_create(OPEN_MAX);
    if(-1 == epfd)
    {
        perror("epoll_create error");
        close(listenfd);
        exit(-1);
    }

    //对应结构体evt赋值，目的是放在红黑树上进行监听
    evt.events = EPOLLIN;
    evt.data.fd = listenfd;
    /* evt.data.ptr = ; */

    //将文件描述符listenfd放在红黑树上进行监听
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);
    if(-1 == ret)
    {
        perror("epoll_ctl error");
        close(listenfd);
        exit(-1);
    }

    while(1)
    {
        //6.1、使用epoll_wait负责监听，如果返回值大于0，表明有满足
        //条件的连接被监听到
        nready = epoll_wait(epfd, ep, OPEN_MAX, -1);
        if(nready < 0)
        {
            perror("select error");
            close(listenfd);
            exit(-1);
        }

        //7、遍历这些nready
        for(i = 0; i < nready; ++i)
        {
            //7.1、异常处理
            if(!(ep[i].events & EPOLLIN))
            {
                continue;
            }

            //7.2、如果有监听到的是listenfd，表示有新的请求进来
            if(ep[i].data.fd == listenfd)//如果是连接事件
            {
                clie_addr_len = sizeof(clie_addr);
                //8、有新的连接，那么accept肯定会有返回值
                connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
                if(-1 == connfd)
                {
                    perror("accept error");
                    close(listenfd);
                    exit(-1);
                }
                printf("receive from %s from port %d\n", 
                       inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                       ntohs(clie_addr.sin_port));

                //将connfd放在红黑树上继续监听（类似于select中，
                //放在client数组中进行继续监听一样）
                evt.events = EPOLLIN;
                evt.data.fd = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &evt);
            }
            //7.3、不是连接建立事件，而是读写事件(信息传递事件)
            //那就表明是老的连接上有数据可读，那肯定是客户端
            //有数据发送过来，所以就可以进行接收,执行read/write
            else 
            {
                sockfd = ep[i].data.fd;
                nByte = read(sockfd, buf, sizeof(buf));
                //表明数据读完了（对应的缓冲区中没有数据了）
                //也就是表明连接马上要断开了
                if(nByte == 0)
                {
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(-1 == ret)
                    {
                        perror("epoll_ctl error");
                    }
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                }
                //连接异常
                else if(nByte < 0)
                {
                    perror("epoll_ctl error");
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(-1 == ret)
                    {
                        perror("epoll_ctl error");
                    }
                    close(sockfd);

                }
                //正常的操作
                else 
                {
                    for(j = 0; j < nByte; ++j)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
                }
            }
        }
    }

    close(listenfd);
    close(connfd);

    return 0;
}
