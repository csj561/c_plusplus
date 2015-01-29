#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstring>
#include <functional>
#include <cstdio>
using namespace std;
extern "C"
{
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
}
const int maxno=20,k=1024;
int main()
{
	int fd1,fd2;
	
	fd1=open("1",O_WRONLY|O_NONBLOCK);
	cout<<"open fd1:"<<fd1<<endl;
	sleep(2);
	cout<<"close fd1:"<<fd1<<endl;
	close(fd1);
	//d();
	return 0;
}
