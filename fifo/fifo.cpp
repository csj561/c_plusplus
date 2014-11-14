#include <iostream>
#include <cstring>
extern "C"
{
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
}
using namespace std;
#define FIFO_N "fifo.test"
#define K 1024
#if 1
int main()
{
	int fd=0;
	char buf[K]={0};
	if(!access(FIFO_N,F_OK))
		remove(FIFO_N);
	if(mkfifo(FIFO_N,0644)<0)
	{perror("[perror]");return -1;}
	
	if((fd=open(FIFO_N,O_RDONLY))<0)
	{perror("[open]");return -1;}
	cout<<"Open "<<FIFO_N<<" ok"<<endl;
	while( read(fd,buf,K)>0){
	cout<<"get data::  " << buf<<endl;
	memset(buf,K,0);
	sleep(3);
	}
	close(fd);
	cout<<FIFO_N<<" closed"<<endl;
	return 0;
}
#else
int main()
{
	int fd=0;
	string s;

	if((fd=open(FIFO_N,O_WRONLY))<0)
	{perror("[open]");return -1;}
	cout<<"Open "<<FIFO_N<<" ok"<<endl;
	//do{
	cout<<"input data" <<endl;
	cin>>s;
	//if(s=="break")
	//break;
	//}while( write(fd,s.c_str(),s.size())>0);
	write(fd,s.c_str(),s.size());
	sleep(1);
	write(fd,s.c_str(),s.size());
	close(fd);
	cout<<FIFO_N<<" closed"<<endl;
	return 0;
}
#endif