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
	alarm(2);
	signal(SIGALRM,&f);
	pause();
	return 0;
}