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
	//while(1)
	{
		printf("got signal at %s \n",ctime(&t));
		//sleep(1);
	}
}
int main(int argc,char **argv)
{
	cout<<"in: "<<argv[0]<<endl;
	//while(1)
	{
		time_t t=time(NULL);
		cout<<ctime(&t);
		sleep(1);
	}
	string s;
	cin>>s;
	cout<<"s="<<s<<endl;
	cout<<"exit: "<<argv[0]<<endl;
	return 0;
}
