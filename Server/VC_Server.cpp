#include "VC_Server.h"

namespace vc
{
    Vc_Server::~Vc_Server() {

    }
    Vc_Server::Vc_Server(const std::string &ip, const int &port, const int &epollevent, const int &maxconn, bool et) : m_ip(ip), m_port(port),
                                                                                                    _epollevent(epollevent), _maxconnect(maxconn), _et(et)
    {

    }

    void Vc_Server::CreateSocket()
    {
        int Domain = AF_INET;
        int type = SOCK_STREAM;

        if(_Sock.Create_socket(Domain, type))
        {
            std::cout << "CreateSocket" << std::endl;
            m_sock = _Sock.getfd();
        }
        else
        {
            std::cout << "CreateSocket error" << std::endl;
            exit(0);
        }
    }

    void Vc_Server::bind()
    {
        if(_Sock.bind(m_ip, m_port))
        {
            std::cout << "bind ip, port success " << std::endl;
        }
        else
        {
            std::cout << "socket bind error" << std::endl;
            exit(0);
        }
        _Sock.listen(1024);
        std::cout << "server alreay listen fd is " << _Sock.getfd() << std::endl;

        _Sock.setKeepAlive();
        _Sock.setTcpNoDelay();
        //不要设置close wait否则http服务回包主动关闭连接会有问题
        _Sock.setNoCloseWait(_et);
        _Sock.setblock(false);

    }

    void Vc_Server::CreateEpoll()
    {
        _epoller.create_epoll(_epollevent, _maxconnect, _et); //event, conn, et

        _epoller.add(_Sock.getfd(), EPOLLIN);

        std::cout << "create_epoll success" << std::endl;
    }

    void Vc_Server::run()
    {
        std::cout << "server run" << std::endl;

        int i = 0;
        while(true)
        {
            int _ep_wait = _epoller.wait();
            std::cout << "m_sock = " << m_sock << std::endl;
            std::cout << "_ep_wait = " << _ep_wait << std::endl;

            for(i = 0; i < _ep_wait; ++i)
            {
                const epoll_event &ev = _epoller.get(i);
                std::cout << "ev.data.fd = " << ev.data.fd << std::endl;
                if(m_sock == ev.data.fd)
                {
                    NewConnection();
                    sleep(500);
                }
                else if(ev.events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
                {
                    std::cout << "close connect" << std::endl;
                    sleep(500);
                }
                //处理客户连接上接收到的数据
                else if (ev.events & EPOLLIN)
                {
                    std::cout << "EPOLLIN" << std::endl;
                    sleep(500);

                }
                else if(ev.events & EPOLLOUT)
                {
                    std::cout << "EPOLLOUT" << std::endl;
                    sleep(500);
                }
            }
        }

    }

    void Vc_Server::NewConnection()
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        if(_et)
        {
            while(true)
            {
                int connfd = accept(m_sock, (struct sockaddr *) &client_addr, &client_addr_len);
                if(connfd < 0)
                {
                    break;
                }
                else
                {
                    std::cout << "new client connect" << std::endl;
                }
            }
        }
        else
        {
            ; //lt
        }
    }

} //vc
