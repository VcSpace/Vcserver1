#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int cl_sock = socket(PF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(20222);

    struct sockaddr fromaddr;
    socklen_t addrlen_t;
    int addrlen = sizeof(fromaddr);
    char sendbuffer[4096] = {0};
//    while(true)
    {
        addrlen_t = sizeof(serv_addr);
        printf("Input a string: ");
        scanf("%s", sendbuffer);

        sendto(cl_sock, sendbuffer, sizeof(sendbuffer) + 1, 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

        memset(sendbuffer, 0, sizeof(sendbuffer));
    }

    close(cl_sock);

    return 0;
}

