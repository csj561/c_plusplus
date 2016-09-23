#ifndef _MES_QUEUE_H_
#define _MES_QUEUE_H_
#include <list>
#include <sys/time.h>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace msg
{
	template<class T,class C=std::list<T> >
	class queue
	{
		C dat;
		boost::mutex mt;
		boost::condition_variable_any cond;
		int wait_num;
		unsigned int sz;
	public:
		queue():wait_num(0),sz(0){}
		//void push_back(const T& t){dat.push_back(t);}
		//void push_front(const T& t){dat.push_front(t);}
		void push(const T& t)
		{
			boost::lock_guard<boost::mutex> guard(mt);
			dat.push_back(t);
			sz++;
			if(wait_num)
			{
				wait_num--;
				cond.notify_one();
			}
		}
		T pop()
		{
			boost::lock_guard<boost::mutex> guard(mt);
			do
			{
				if(!sz)// 防止刚刚有数据就被别的线程取走的情况
				{
					wait_num++;
					cond.wait(mt);
				}
				else
				{
					break;
				}
			}while(1);
			
			T t=dat.front();
			dat.pop_front();
			sz--;
			return t;
		}
		bool pop(T &ret,int64_t micro_sec)
		{
			struct timeval _start_time;
			gettimeofday(&_start_time,NULL);
			int64_t start_time=_start_time.tv_sec*1000000+_start_time.tv_usec;
			if(micro_sec<=0)
				return false;
			boost::lock_guard<boost::mutex> guard(mt);
			do
			{
				struct timeval _now_time;
				gettimeofday(&_now_time,NULL);
				int64_t now_time=_now_time.tv_sec*1000000+_now_time.tv_usec;
				if(now_time-start_time>=micro_sec)
					return false;
				
				if(!sz)// 防止刚刚有数据就被别的线程取走的情况
				{
					wait_num++;
					int64_t wait_time=micro_sec-(now_time-start_time);
					boost::posix_time::time_duration  td=
						boost::posix_time::seconds(wait_time/1000000)+boost::posix_time::microseconds(wait_time%1000000);
					cond.timed_wait(mt,td);
				}
				else
				{
					break;
				}
			}while(1);
			
			ret=dat.front();
			dat.pop_front();
			sz--;
			return true;
		}
		unsigned int size() 
		{
			boost::lock_guard<boost::mutex> guard(mt);
			return sz;
		}
	};
}
#endif
