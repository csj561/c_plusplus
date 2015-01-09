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

int main()
{
	
	pid_t pid;
	if((pid=fork())==0)
	{
		return 0;
	}
	else if(pid>0)
	{
	signal(SIGCLD,SIG_IGN);
	}
	getchar();
	return 0;
}