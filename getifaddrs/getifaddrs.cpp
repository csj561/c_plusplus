#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <cstdlib>
#include <cstdio>
extern "C"{
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
}
using namespace std;
void pr_ifa(struct ifaddrs *ifa)
{
	while(ifa)
	{
	//if(ifa->ifa_addr->sa_family==AF_INET)
	{
	struct sockaddr_in *skin=(struct sockaddr_in *)ifa->ifa_addr;
	cout<<"ifn: "<<ifa->ifa_name
	<<" ip:"<<inet_ntoa(skin->sin_addr)
	<<" family "<<ifa->ifa_addr->sa_family<<endl;
	}
	ifa=ifa->ifa_next;
	}
}
int main()
{
	struct ifaddrs *ifa;
	if(getifaddrs(&ifa)<0)
	{
		perror("[getifaddrs]");
		return -1;
	}
	pr_ifa(ifa);
	freeifaddrs(ifa);
}