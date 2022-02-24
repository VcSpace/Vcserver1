#include "VC_Server.h"

namespace vc
{
    VC_Server::~VC_Server() {

    }
    VC_Server::VC_Server(const std::string &ip, const int &port, const int &epollevent, const int &maxconn, bool et, int threadnum, int queue_size) : m_ip(ip), m_port(port),
                     _epollevent(epollevent), _maxconnect(maxconn), _et(et), m_sock(-1), m_epollfd(0), _timer(nullptr), m_threadnum(threadnum), que_size(queue_size)
    {

    }

    void VC_Server::CreateSocket()
    {
        int Domain = AF_INET;
        int type = SOCK_STREAM;

        if(_Sock.Create_socket(Domain, type))
        {
            ;

        }
        else
        {
            std::cout << "CreateSocket error" << std::endl;
            exit(0);
        }

        bind();
    }

    void VC_Server::bind()
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
        _Sock.listen(10);
        std::cout << "server alreay listen fd is " << _Sock.getfd() << std::endl;

        _Sock.setKeepAlive();
        _Sock.setTcpNoDelay();
        //不要设置close wait否则http服务回包主动关闭连接会有问题
        _Sock.setNoCloseWait(_et);
        _Sock.setblock(false);

    }

    void VC_Server::CreateEpoll()
    {
        _epoller.create_epoll(_epollevent, _maxconnect, _et); //event, conn, et
        m_sock = _Sock.getfd();
        _epoller.add(m_sock, EPOLLIN | EPOLLOUT | EPOLLET);
        m_epollfd = _epoller.getfd();

        std::cout << "create_epoll success" << std::endl;
    }

    //这个函数为测试使用
    static void handle_events(const epoll_event *ev, int epfd) {
        printf("events %d: ", ev->data.fd);

        if (ev->events & EPOLLIN) {
            printf("EPOLLIN ");
        }

        if (ev->events & EPOLLOUT) {
            printf("EPOLLOUT ");
        }

        printf("\n");
    }

    void VC_Server::run()
    {
        std::cout << "server run" << std::endl;

        int i = 0;
        int timeMS = 0;
        while(true)
        {
            if(timeMS > 0) {
                ;
            }

            int _ep_wait = _epoller.wait(timeMS);

            if(_ep_wait < 0 && errno != EINTR)
            {
                std::cout << "epoll failure" << std::endl;
                break;
            }

            for(i = 0; i < _ep_wait; i++)
            {
                const epoll_event &ev = _epoller.get(i);
                if(m_sock == m_epollfd)
                {
                    if(NewConnection())
                    {
                        ;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if(ev.events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
                {
                    std::cout << "close connect" << std::endl;
                }
//                处理客户连接上接收到的数据
                else if(ev.events & EPOLLIN)
                {
                    std::cout << "EPOLLIN" << std::endl;
                    
                }
                else if(ev.events & EPOLLOUT)
                {
                    std::cout << "EPOLLOUT" << std::endl;
                }
//                else
//                {
//                    vc::handle_events(&ev, m_epollfd);
//                    continue;
//                }
            }
        }

    }

    bool VC_Server::NewConnection()
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
                    ;
                }
                else
                {
                    std::cout << "new client connect" << std::endl;
                    return true;
                }
            }
        }
        else
        {
            ; //lt
        }

        return false;
    }

    void VC_Server::CreateThread()
    {
        _thread = new VC_Thread<VC_Server *>(m_threadnum, que_size);
    }

} //vc
