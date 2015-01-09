#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
#include <cstdio>
#include <cstring>
using namespace std;
extern "C"
{
#include <unistd.h>
#include <pthread.h>
}
pthread_key_t key;
pthread_mutex_t mutex;
void f(void *dat)
{
pthread_mutex_lock(&mutex);
	cout<<reinterpret_cast<const char *>(dat)<<endl;
	//pthread_key_delete(key);
	free(dat);
	pthread_mutex_unlock(&mutex);
}
void f2(void *dat)
{

	cout<<reinterpret_cast<const char *>(dat)<<endl;
}
void *thread(void *dat)
{
pthread_key_t key2;
pthread_key_create(&key2,&f);
pthread_setspecific(key2,strdup("key2"));
	sleep(1);
	pthread_setspecific(key,strdup(reinterpret_cast<const char *>(dat)));
	return NULL;
}
void *thread2(void *dat)
{
	pthread_setspecific(key,strdup(reinterpret_cast<const char *>(dat)));
	return NULL;
	//pthread_key_delete(key);
}

int main()
{
	pthread_t ptid1,ptid2;
	pthread_attr_t attr1,attr2;
	pthread_mutex_init(&mutex,NULL);
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	//pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_DETACHED);
	//pthread_attr_setdetachstate(&attr2,PTHREAD_CREATE_DETACHED);
	pthread_key_create(&key,&f);
	pthread_setspecific(key,strdup("main"));
	
	pthread_create(&ptid1,&attr1,&thread,strdup("int thread"));
	pthread_create(&ptid2,&attr2,&thread2,strdup("int thread2"));
	//pthread_join(ptid2,NULL);
	//pthread_join(ptid1,NULL);
	//pthread_key_delete(key);
	//cout<<reinterpret_cast<const char *>( pthread_getspecific(key))<<endl;
	sleep(2);
	return 0;
}