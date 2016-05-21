#include <iostream>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex[2];
void *test(void *arg)
{
	pthread_mutex_t *p_m=NULL;
	if(string("0")==static_cast<const char *>(arg))
		p_m=&(mutex[0]);
	else
		p_m=&(mutex[0]);
	pthread_mutex_lock(p_m);
	cout<<static_cast<const char *>(arg)<<endl;
	sleep(3);
	pthread_mutex_unlock(p_m);
	return NULL;
}

int main()
{
	pthread_t t[2];
	if(0>pthread_mutex_init(&mutex[0],NULL))
		perror("xxxx");
	if(0>pthread_mutex_init(&mutex[1],NULL))
		perror("xxx2");
	pthread_create(t,NULL,&test,static_cast<char *>("0"));
	pthread_create(t+1,NULL,&test,static_cast<char *>("1"));
	sleep(5);
	return 0;
}
