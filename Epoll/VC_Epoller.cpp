#include "VC_Epoller.h"

#include <iostream>

namespace vc
{

    VC_Epoller::VC_Epoller() : _pevs(nullptr), _epollfd(0), _ev_size(20000), _maxconnect(1024), _et(true)
    {

    }

    VC_Epoller::~VC_Epoller()
    {
        if(_pevs != nullptr)
        {
            delete[] _pevs;
            _pevs = nullptr;
        }

        if(_epollfd > 0)
        {
            ::close(_epollfd);
        }
    }

    void VC_Epoller::create_epoll(int ev_size, int max_conn, bool et)
    {
        _ev_size = ev_size;
        _maxconnect = max_conn;
        _et = et;

        _epollfd = epoll_create(_maxconnect + 1);
        std::cout << "create epoll error " << std::endl;
        assert(_epollfd != -1);

        _pevs = new epoll_event[_maxconnect + 1];
    }

    void VC_Epoller::add(int fd, __uint32_t event)
    {
        epollctl(fd, event, EPOLL_CTL_ADD);
    }

    void VC_Epoller::mod(int fd, __uint32_t event)
    {
        epollctl(fd, event, EPOLL_CTL_MOD);
    }

    void VC_Epoller::del(int fd, __uint32_t event)
    {
        epollctl(fd, event, EPOLL_CTL_DEL);
    }

    void VC_Epoller::epollctl(int fd, __uint32_t event, int op)
    {
        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = event;
        if(_et)
        {
            ev.events |= EPOLLET;
        }

        epoll_ctl(_epollfd, op, fd, &ev);
    }

    int VC_Epoller::wait() {
        return epoll_wait(_epollfd, _pevs, _maxconnect, 30);
    }

} //vc
