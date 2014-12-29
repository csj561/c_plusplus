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
	if(signal(SIGINT,&f)==SIG_ERR)
	{
		perror("signal");
		return ;
	}
	//while(1)
	{
		printf("got signal in pid %d \n",getpid());
		sleep(3);
	}
}
int main(int argc,char **argv)
{
	
	pid_t pid;
	cout<<"in :"<<argv[0]<<endl;
	if((pid=fork())==0)
	{

	}
	if(pid>0)
	{
	sigset(SIGINT,&f);
	signal(SIGTERM,SIG_IGN);
	
	getchar();
	//sleep(2);
	cout<<"exit father"<<endl;
	}
	//while(1)
	//	sleep(1);
	
	//getchar();
	return 0;
}
