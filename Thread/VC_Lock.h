#ifndef VCSERVER_VC_LOCK_H
#define VCSERVER_VC_LOCK_H

#include <mutex>
#include <pthread.h>
#include <unistd.h>

namespace vc
{
    class VC_Lock
    {
    public:
        VC_Lock();
        ~VC_Lock();

        bool lock();
        bool unlock();

    private:
        pthread_mutex_t m_mutex;

    };
} //vc


#endif //VCSERVER_VC_LOCK_H
