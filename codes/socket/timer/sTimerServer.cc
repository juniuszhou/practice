#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>

#include <stdio.h>
#include     <time.h>

using namespace std;

int main(int argc, char **argv)
{
    int     listenfd, connfd;
    struct sockaddr_in servaddr;
    char    buff[100];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13); /* daytime server */

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd,0);

    for ( ; ; ) {
        connfd = accept(listenfd, NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}

