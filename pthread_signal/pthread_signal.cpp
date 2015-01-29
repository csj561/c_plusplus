#include <string>
#include <iostream>
using namespace std;
extern "C"{
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
}
void sig_hdl(int )
{
	cout<<"get signal thread : "<<pthread_self()<<endl;
	sleep(3);
}
void *pth_hdl(void *)
{
	cout<<"create thread "<<pthread_self()<<endl;
	while(1)
		sleep(1);
	return NULL;
}
int main()
{
	pthread_t pth_id;
	signal(SIGINT,&sig_hdl);
	cout<<"man pid"<<getpid()<<endl<<
	"man thread "<<pthread_self()<<endl;
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	pthread_join(pth_id,NULL);
	return 0;
}