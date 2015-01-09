#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
#include <cstdio>
using namespace std;
extern "C"
{
#include <unistd.h>
#include <signal.h>
}
void f(int signo)
{
	cout<<"got signal"<<endl;
}
int main()
{
	struct sigaction sact;
	sact.sa_handler=&f;
	sigemptyset(&sact.sa_mask);
	sact.sa_flags=SA_INTERRUPT;
	sigaction(SIGINT,&sact,NULL);
	//signal(SIGINT,&f);
	{
		char i;
		read(STDIN_FILENO,&i,1);
	}
	return 0;
}