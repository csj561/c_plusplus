#include <iostream>
#include <cstring>
#include <cstdio>
extern "C"
{
#include <unistd.h>
#include <time.h>
#include <signal.h>
}
using namespace std;
void f(int s)
{
	time_t t=time(NULL);
	while(1)
	{
		printf("got signal at %d \n",t);
		sleep(1);
	}
}
int main()
{
	signal(SIGUSR1,&f);
	while(1)
		sleep(1);
	return 0;
}
