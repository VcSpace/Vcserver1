#ifndef VCSERVER_VC_TIMER_H
#define VCSERVER_VC_TIMER_H

#include <chrono>
#include <time.h>
#include <cassert>
#include <functional>
#include <vector>

namespace vc
{
    struct TimerNode {
        int id;
        int expires;
        bool _istimeout = false;

        bool operator<(const TimerNode& t) {
            return expires < t.expires;
        }
    };

    class VC_Timer
    {
    public:
        VC_Timer(int maxconn, int time);
        ~VC_Timer();

    private:
        struct TimerNode *_times;

    };
} //vc

#endif //VCSERVER_VC_TIMER_H
