#include <iostream>
#include <cstring>
#include <cstdio>
extern "C"
{
#include <pthread.h>
}
using namespace std;

int main()
{
	pthread_mutexattr_t pattr;
	int type;
	if(pthread_mutexattr_init(&pattr)<0)
	{
		perror("[pthread_mutexattr_init]");
		return -1;
	}
	if(pthread_mutexattr_gettype(&pattr,&type)<0)
	{
		perror("[pthread_mutexattr_gettype]");
		return -1;
	}
	cout<<"type is "<<type<<endl;
	type=PTHREAD_MUTEX_NORMAL;
	if(pthread_mutexattr_settype(&pattr,type)<0)
	{
		perror("[pthread_mutexattr_settype]");
		return -1;
	}
	cout<<"type is "<<type<<endl;
	if(pthread_mutexattr_gettype(&pattr,&type)<0)
	{
		perror("[pthread_mutexattr_gettype]");
		return -1;
	}
	cout<<"type is "<<type<<endl;
	return 0;
}
