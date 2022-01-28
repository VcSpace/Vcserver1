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
        VC_Thread(int threadnum = 8, int que_size = 1024);
        ~VC_Thread();

        void push();
        void pop();
        void run();

    private:
        static void *worker(void *arg);
        VC_Lock _lock;

    private:
        std::queue<T*> _pool;
        pthread_t *_threads;

        int m_thread;
        int m_qsize;
    };

   template <typename T>
   VC_Thread<T>::VC_Thread(int threadnum, int que_size)
   {
       m_thread = threadnum;
       m_qsize = que_size;
       _threads = new pthread_t[m_thread];

       for(int t = 0; t < m_thread; ++t)
       {
           if(pthread_create(_threads + t, nullptr, worker, this) != 0)
           {
               delete[] _threads;
               throw std::exception();
           }
           else
           {
               std::cout << "create thread: " << t + 1 << std::endl;
           }

           if(pthread_detach(_threads[t]))
           {
               delete[] _threads;
               throw std::exception();
           } else
           {
               std::cout << "detech thread: " << t + 1 << std::endl;
           }
       }

   }

    template<typename T>
    VC_Thread<T>::~VC_Thread()
    {
        delete[] _threads;
    }

    template<typename T>
    void* VC_Thread<T>::worker(void *arg)
    {
        VC_Thread *p = static_cast<VC_Thread *>(arg);
        p->run();
        return p;
    }

    template<typename T>
    void VC_Thread<T>::run()
    {
        std::cout << "thread start " << std::endl;
        while(true)
        {
            _lock.lock();
            _lock.unlock();
        }
    }

    template<typename T>
    void VC_Thread<T>::push()
    {

    }

    template<typename T>
    void VC_Thread<T>::pop()
    {

    }

} //vc


#endif //VCSERVER_VC_THREAD_H
