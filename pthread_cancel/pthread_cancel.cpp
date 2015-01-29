#include <string>
#include <iostream>
using namespace std;
extern "C"{
#include <unistd.h>
#include <pthread.h>
}
class A{};
bool operator<(A a,A b){cout<<__func__<<endl;return true;}
void pth_exit(void *)
{
	cout<<"exit thread : "<<pthread_self()<<endl;
}
void *pth_hdl(void *)
{
	pthread_cleanup_push(&pth_exit,NULL);
	{
		char i;
		read(STDIN_FILENO,&i,1);
	}
	pthread_cleanup_pop(1);
	return NULL;
}
int main()
{
	pthread_t pth_id;
	pthread_create(&pth_id,NULL,&pth_hdl,NULL);
	sleep(1);
	pthread_cancel(pth_id);
	pthread_join(pth_id,NULL);
	return 0;
}