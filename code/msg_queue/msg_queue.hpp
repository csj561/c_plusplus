#ifndef _MES_QUEUE_H_
#define _MES_QUEUE_H_
#include <list>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

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
				if(!sz)
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
		unsigned int size() 
		{
			boost::lock_guard<boost::mutex> guard(mt);
			return sz;
		}
	};
}
#endif
