#include <iostream>
#include <boost/timer.hpp>
#include <boost/progress.hpp>

#include <unistd.h>

using namespace std;
using namespace boost;
void split_line()
{
	cout<<"---------------------------------------------------------------\n"<<endl;
}
int main()
{
	timer t;
	{
		progress_timer t;/// 析构时自动输出构建到析构时代码执行时间
		long long i=99999999;
		while(i--);
	}
	split_line();
	cout<<t.elapsed_max()/3600<<endl;/// 打印可以计算的最大时间量
	cout<<t.elapsed_min()<<endl; /// 最小时间量，单位s
	cout<<t.elapsed()<<endl; /// 打印对象构建到此处代码执行所花的时间，不包含休眠时间
	split_line();
	progress_display pd(10);
	int i=10;
	while(i--)
	{
		++pd;
		sleep(1);
	}
}

