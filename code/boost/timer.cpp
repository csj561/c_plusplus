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
		progress_timer t;/// ����ʱ�Զ��������������ʱ����ִ��ʱ��
		long long i=99999999;
		while(i--);
	}
	split_line();
	cout<<t.elapsed_max()/3600<<endl;/// ��ӡ���Լ�������ʱ����
	cout<<t.elapsed_min()<<endl; /// ��Сʱ��������λs
	cout<<t.elapsed()<<endl; /// ��ӡ���󹹽����˴�����ִ��������ʱ�䣬����������ʱ��
	split_line();
	progress_display pd(10);
	int i=10;
	while(i--)
	{
		++pd;
		sleep(1);
	}
}

