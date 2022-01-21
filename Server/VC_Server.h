#ifndef VCSERVER_VC_SERVER_H
#define VCSERVER_VC_SERVER_H

#include "VC_Socket.h"
#include "../Epoll/VC_Epoller.h"

namespace vc
{
    class Vc_Server
    {
    public:
        Vc_Server(const std::string &ip, const int &port, const int &epollevent, const int &maxcon, bool et);
        ~Vc_Server();

        void CreateSocket();
        void CreateEpoll();
        void bind();
        void run();

        bool NewConnection();

    private:
        Vc_Socket _Sock;
        VC_Epoller _epoller;

    private:
        int m_sock;
        int m_epollfd;
        int fd;
        int m_port;
        int _epollevent;
        int _maxconnect;

        std::string m_ip;
        bool _et;
    };

} //vc

#endif //VCSERVER_VC_SERVER_H
