#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888

int main()
{
    int cfd;
    struct sockaddr_in serv_addr;
    char buf[BUFSIZ];
    int nByte;

    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == cfd)
    {
        perror("socket error");
        exit(-1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* inet_pton(cfd, SERV_IP, &serv_addr.sin_addr.s_addr); */

    connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(1)
    {
        fgets(buf, sizeof(buf), stdin);//hello world  ----> hello world\n\0
        write(cfd, buf, strlen(buf));

        nByte = read(cfd, buf, sizeof(buf));

        write(STDOUT_FILENO, buf, nByte);
    }

    close(cfd);
    return 0;
}
