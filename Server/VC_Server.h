#ifndef VCSERVER_VC_SERVER_H
#define VCSERVER_VC_SERVER_H


#include "VC_Socket.h"

namespace vc
{
    class Vc_Server
    {
    public:
        Vc_Server(const std::string &ip, const int &port);
        ~Vc_Server();

        void CreateSocket();
        void bind();

    private:
        Vc_Socket _Sock;
        int m_sock;
        int fd;

        std::string m_ip;
        int m_port;

    };

} //vc

#endif //VCSERVER_VC_SERVER_H
