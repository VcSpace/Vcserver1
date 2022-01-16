#ifndef VCSERVER_VC_EPOLLER_H
#define VCSERVER_VC_EPOLLER_H

#include <sys/epoll.h>
#include <cassert>
#include <sys/types.h>
#include <unistd.h>

namespace vc
{
    class VC_Epoller
    {
    public:
        VC_Epoller();
        ~VC_Epoller();

        void create_epoll(int ev_size, int max_conn, bool et);
        void add(int fd, __uint32_t event);
        void mod(int fd, __uint32_t event);
        void del(int fd, __uint32_t event);
        void epollctl(int fd, __uint32_t event, int op);

        int wait();
        struct epoll_event &get(int i)
        {
            assert(_pevs != 0);
            return _pevs[i];
        }

    private:
        struct epoll_event *_pevs;

        int _ev_size;
        int _epollfd;
        int _maxconnect;

        bool _et;
    };

} //vc


#endif //VCSERVER_VC_EPOLLER_H
