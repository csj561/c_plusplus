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
	int efd=epoll_create(maxno);
	int fd1,fd2;
	int ret;
	struct epoll_event  ev,evs[maxno];
	
	fd1=open("1",O_RDONLY|O_NONBLOCK);
	fd2=open("2",O_RDONLY|O_NONBLOCK);
	ev.events=EPOLLET|EPOLLRDHUP;
	ev.data.fd=fd1;
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,fd1,&ev);
	if(ret)
		perror("epoll_ctl");
	ev.events=EPOLLIN|EPOLLET;
	ev.data.fd=fd2;
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,fd2,&ev);
	if(ret)
		perror("epoll_ctl");
	while((ret=epoll_wait(efd,evs,maxno,-1))>0)
	{
		char buf[k];
		for(int i=0;i<ret;i++)
		{
			memset(buf,0,k);
			read(evs[i].data.fd,buf,k);
			cout<<"read dat:"<<buf<<endl;
		}
		//break;
	}
	//d();
	return 0;
}