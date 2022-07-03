#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ev.h>

int main(int argc, char **argv)
{
    short port;
    scanf("%i",&port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    char buf[256];
    if(sock < 0)
    {
        perror("can't create connection"); exit(1);
    }
    struct sockaddr_in sai;
    sai.sin_family = AF_INET;
    sai.sin_addr.s_addr = htonl(INADDR_ANY);
    sai.sin_port = htons(port);
    bind(sock, (struct sockaddr*)&sai,sizeof(sai));
    listen(sock, 10);
    int conn = accept(sock, (struct sockaddr*)NULL, NULL);
    while(1)
    {
        read(conn, buf, 256);
        if(strlen(buf))
        {
            printf(buf);
            write(conn, buf,strlen(buf));
        }
        sprintf(buf, "");
    }
    return 0;
}
