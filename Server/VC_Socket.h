#ifndef VCSERVER_VC_SOCKET_H
#define VCSERVER_VC_SOCKET_H

#include <iostream>
#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace vc
{
    class Vc_Socket
    {
    public:
        Vc_Socket();
        ~Vc_Socket();

        bool create_socket(int Domain, int type);
        bool bind(const std::string ip, const int port);
        bool parseAddr(const std::string ip, struct in_addr &addr);

    private:
        int _sockfd;
        int _Domain;
        int _type;
    };

} //vc

#endif //VCSERVER_VC_SOCKET_H
