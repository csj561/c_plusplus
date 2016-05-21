#include <string>
#include <iostream>
#include <cstring>
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
}
void svr(unsigned short port)
{
	int svrfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr addr;
	struct sockaddr_in *addrp;
	const int k=1024;
	char buf[k]={0};
	socklen_t len;
	addrp=reinterpret_cast<struct sockaddr_in *>(&addr);
	if(svrfd<0)
	{
		perror("socket");
		exit(-1);
	}
	addrp->sin_family=AF_INET;
	addrp->sin_addr.s_addr=INADDR_ANY;
	addrp->sin_port=htons(port);
	if(bind(svrfd,&addr,sizeof(struct sockaddr)))
	{
		perror("bind");
		exit(-1);
	}
	len=sizeof(struct sockaddr);
	while(recvfrom(svrfd,buf,k,0,&addr,&len)>0)
	{
		char ip[INET_ADDRSTRLEN];
		time_t t=time(NULL);
		string s("server response at ");
		//inet_ntop(AF_INET,&addrp->sin_addr,ip,sizeof( struct in_addr));
		cout<<"get dat from :"<<inet_ntoa(addrp->sin_addr)<<":"<<ntohs(addrp->sin_port)<<endl;
		cout<<buf<<endl;
		s+=ctime(&t);
		if(sendto(svrfd,s.c_str(),s.size(),0,&addr,sizeof(struct sockaddr))<0)
		{
			perror("send");
			exit(-1);
		}
		memset(buf,0,k);
	}
	perror("recvfrom");
}
void client(const string &ip,unsigned short port)
{
	int svrfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr addr;
	struct sockaddr_in *addrp;
	const int k=1024;
	char buf[k]={0};
	socklen_t len;
	pid_t pid;
	addrp=reinterpret_cast<struct sockaddr_in *>(&addr);
	if(svrfd<0)
	{
		perror("socket");
		exit(-1);
	}
	addrp->sin_family=AF_INET;
	addrp->sin_addr.s_addr=inet_addr(ip.c_str());
	addrp->sin_port=htons(port);
	if(connect(svrfd,&addr,sizeof(struct sockaddr))<0)
	{
		perror("connect");
		exit(-1);
	}
	if((pid=fork())>0)
	{
		while(1){
		string s;
		cout<<"input to send:";
		cin>>s;
		send(svrfd,s.c_str(),s.size(),0);
		usleep(1000*100);
		}
	}
	else if(pid==0)
	{
		while(recv(svrfd,buf,k,0)>0)
		{
			char ip[INET_ADDRSTRLEN];
			time_t t=time(NULL);
			string s("get dat at ");
			cout<<buf<<endl;
			
			memset(buf,0,k);
		}
		perror("recvfrom");exit(0);
	}
	else{perror("fork");exit(0);}
}
int main(int argc,char **argv)
{
	if(argc<=1)
	{
		cout<<"error param"<<endl;
		exit(-1);
	}
	if(string(argv[1])=="c")
	{
		if(argc!=4)
		{
			cout<<"error param"<<endl;
			exit(-1);
		}
		client(string(argv[2]),atoi(argv[3]));
	}
	else if(string(argv[1])=="s")
		svr(atoi(argv[2]));
	
	return 0;
}