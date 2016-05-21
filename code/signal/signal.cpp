#include <iostream>
#include <cstring>
#include <cstdio>
extern "C"
{
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
}
using namespace std;

void f(int s)
{
	time_t t=time(NULL);
	
	//while(1)
	{
		printf("got signal %d in pid %d \n",s,getpid());
		sleep(3);
		cout<<"end signal handler"<<endl;
	}
}
int main(int argc,char **argv)
{
	
	pid_t pid;
	cout<<"in :"<<argv[0]
	<<" pid is "<<getpid()<<endl;
	
	signal(40,&f);
	signal(SIGTERM,SIG_IGN);
	
	getchar();
	//sleep(2);
	cout<<"exit father"<<endl;
	//while(1)
	//	sleep(1);
	
	//getchar();
	return 0;
}
