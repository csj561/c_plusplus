#include <msg_queue.hpp>
#include <cstdio>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>
msg::queue<int> q;

void f(int t)
{
	while(1)
	{
		int i=q.pop();
		printf("thread [%d] get [%d]\n",t,i);
	}
}


int main()
{
	boost::thread t1(f,1);
	boost::thread t2(boost::bind(f,2));
	boost::thread t3(f,3);
	boost::thread t4(f,4);
	int i=1;
	//sleep(5);
	while(i)
	{
		q.push(i++);
		sleep(1);
	}
}
