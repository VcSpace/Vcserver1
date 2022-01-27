#ifndef VCSERVER_VC_THREAD_H
#define VCSERVER_VC_THREAD_H

#include <queue>

#include "VC_Lock.h"

namespace vc
{
    template <typename T>
    class VC_Thread
    {
    public:
        VC_Thread(int threadnum, int que_size);
        ~VC_Thread();

        void push(T *res);
        void pop();
        void run();

    private:
        static void worker(void *arg);
        VC_Lock *_lock;

    private:
        std::queue<T*> _pool;
        pthread_t *_threads;

        int m_thread;
        int m_qsize;
    };

   template <typename T>
   VC_Thread<T>::VC_Thread(int threadnum, int que_size)
   {
       if(threadnum <= 0)
       {
           m_thread = 8;
       }
       else
       {
           m_thread = threadnum;
       }
       _threads = new pthread_t[m_thread];

       for(int t = 0; t < m_thread; ++t)
       {
           if(pthread_create(*(_threads + t), nullptr, worker, this) != 0)
           {
               delete[] _threads;
               throw std::exception();
           }
           else
           {
               ;
           }

           if(pthread_detach(_threads[t]))
           {
               delete[] _threads;
               throw std::exception();
           } else
           {
               ;
           }
       }

   }

    template<typename T>
    VC_Thread<T>::~VC_Thread()
    {
        delete[] _threads;
    }

    template<typename T>
    void VC_Thread<T>::worker(void *arg)
    {
        VC_Thread *p = static_cast<VC_Thread *>(arg);
        p->run();
        return p;
    }

    template<typename T>
    void VC_Thread<T>::run()
    {
        _lock.lock();

    }

    template<typename T>
    void VC_Thread<T>::push(T *res)
    {

    }

    template<typename T>
    void VC_Thread<T>::pop()
    {

    }

} //vc


#endif //VCSERVER_VC_THREAD_H
