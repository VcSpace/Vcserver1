#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>


int main(int argc, char **argv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(20111);

    int ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(sockfd, 10);
    assert(ret == 0);

    struct sockaddr_in client_addr;
    socklen_t socklen = sizeof(client_addr);
    char buf[4096] = {0};
//    while(true)
    {
        memset(buf, 0, sizeof(buf));
        int clientfd = accept(sockfd, (struct sockaddr*) &client_addr, &socklen);
        recv(clientfd, buf, sizeof(buf), 0);
        std::cout << "server_recv: " << buf << std::endl;

        memset(buf, 0, sizeof(buf));

        close(clientfd);
    }

    close(sockfd);

    return 0;
}
