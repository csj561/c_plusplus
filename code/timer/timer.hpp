#ifndef _FOOL_TIMER_H_
#define _FOOL_TIMER_H_
#include <cstdio>
#include <string>
#include <sys/time.h>
#include <time.h>
namespace fool
{
    using std::string;
    class timer
    {
    public:
        timer(string const & _fn="Anonymity"):fn(_fn),cpu_time(clock())
        {gettimeofday(&natual_time,NULL);}
        virtual ~timer()
        {
            struct timeval natual_end_time;
            gettimeofday(&natual_end_time,NULL);
            double cpu_cost_time=(double)(clock()-cpu_time)/CLOCKS_PER_SEC;
            double natual_cost_time=(natual_end_time.tv_sec-natual_time.tv_sec) * 1000
                +(double)(natual_end_time.tv_usec-natual_time.tv_usec)/1000;
            printf("Timer[%s] Cpu time [%.3lfms] natual time [%.3lfms]\n",fn.c_str(),cpu_cost_time,natual_cost_time);
        }
    
    private:
        string fn;
        clock_t cpu_time;
        struct timeval natual_time;
        timer(const timer &);
    };
}
#endif // !_FOOL_TIMER_H_
