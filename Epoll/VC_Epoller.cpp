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
        epoll_event ev;
        ev.data.fd = fd;
        if(_et)
        {
            ev.events = event;
            std::cout << "set events" << std::endl;
//            ev.events |= EPOLLET;
        }
        else
        {
            ev.events = EPOLLIN | EPOLLRDHUP;
        }

        int ret = epoll_ctl(_epollfd, op, fd, &ev);

        std::cout << "epoll_ctl: " << ret << std::endl;
    }

    int VC_Epoller::wait(int timeout) {
        return epoll_wait(_epollfd, _pevs, _maxconnect, timeout);
    }

} //vc
