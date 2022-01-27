#include "VC_Lock.h"

#include <iostream>


namespace vc
{
    VC_Lock::VC_Lock()
    {
        if(pthread_mutex_init(&m_mutex, nullptr) != 0)
        {
            std::cout << "mutex init error" << std::endl;
        }

    }

    VC_Lock::~VC_Lock() {
        unlock();

        if(pthread_mutex_destroy(&m_mutex) != 0)
        {
            std::cout << "mutex destroy error" << std::endl;
        }

    }

    bool VC_Lock::lock() {
        if(pthread_mutex_lock(&m_mutex) != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool VC_Lock::unlock() {
        if(pthread_mutex_unlock(&m_mutex) != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
} //vc