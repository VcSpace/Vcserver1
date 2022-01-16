#ifndef VCSERVER_VC_SOCKET_H
#define VCSERVER_VC_SOCKET_H

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/fcntl.h>

namespace vc
{
    class Vc_Socket
    {
    public:
        Vc_Socket();
        ~Vc_Socket();

        bool Create_socket(int Domain, int type);
        bool bind(const std::string ip, const int port);
        bool parseAddr(const std::string ip, struct in_addr &addr);

        void bind(const struct sockaddr_in &addr, socklen_t addrlen);
        void listen(int size);
        void setKeepAlive();
        void setTcpNoDelay();
        void setNoCloseWait(bool et);
        void setblock(bool block);

        int SetSocketOpt(int opt, const void *optval, socklen_t len, int level);
        int getfd() {return _sockfd;}

    private:
        int _sockfd;
        int _Domain;
        int _type;
    };

} //vc

#endif //VCSERVER_VC_SOCKET_H
