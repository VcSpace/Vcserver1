#ifndef VCSERVER_VC_THREAD_H
#define VCSERVER_VC_THREAD_H

#include <unistd.h>
#include <pthread.h>
#include <queue>

namespace vc
{
    template <typename T>
    class VC_Thread
    {
    public:
        VC_Thread(int threadnum = 8);
        ~VC_Thread();

        void append(T res);
        T pop();

    private:
        std::queue<T*> _pool;
        pthread_t *_threads;

        int m_thread;
    };

   template <typename T>
   VC_Thread<T>::VC_Thread(int threadnum)
   {
       if(threadnum <= 0)
       {
           m_thread = 8;
       }
       else
       {
           m_thread = threadnum;
       }

       for(int t = 0; t < m_thread; ++t)
       {
           pthread_create()
       }

   }

} //vc


#endif //VCSERVER_VC_THREAD_H
