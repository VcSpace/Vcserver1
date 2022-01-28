#ifndef VCSERVER_VC_SERVER_H
#define VCSERVER_VC_SERVER_H

#include "VC_Socket.h"
#include "../Epoll/VC_Epoller.h"
#include "../Timer/VC_Timer.h"
#include "../Thread/VC_Thread.hpp"

namespace vc
{
    class VC_Server
    {
    public:
        VC_Server(const std::string &ip, const int &port, const int &epollevent, const int &maxcon, bool et, int threadnum, int queue_size);
        ~VC_Server();

        void CreateSocket();
        void CreateEpoll();
        void CreateThread();
        void bind();
        void run();

        bool NewConnection();

    private:
        Vc_Socket _Sock;
        VC_Epoller _epoller;
        VC_Timer *_timer;
        VC_Thread<VC_Server *> *_thread;

    private:
        int fd;
        int m_sock;
        int m_epollfd;
        int m_threadnum;
        int m_port;
        int _epollevent;
        int _maxconnect;
        int que_size;

        std::string m_ip;
        bool _et;
    };

} //vc

#endif //VCSERVER_VC_SERVER_H
