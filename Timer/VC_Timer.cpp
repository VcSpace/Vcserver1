#include "VC_Timer.h"

namespace vc
{
    VC_Timer::VC_Timer(int maxconn, int time) : _times(new vc::TimerNode[maxconn])
    {

    }

    VC_Timer::~VC_Timer()
    {
        if(_times)
        {
            delete _times;
        }

        _times = nullptr;
    }


} //vc