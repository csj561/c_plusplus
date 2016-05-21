#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
extern "C"{
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
}
using namespace std;

int main()
{
	map<int , int> m;
	cout<<"m size :" <<m.size()<<endl;
	int i=m[2];
	cout<<"m size :" <<m.size()<<endl;
}