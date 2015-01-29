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
#include <netdb.h>
}
void p(const struct hostent *host)
{
	cout<<"name :" <<host->h_name<<endl;
	char **cur=host->h_aliases;
	while(*cur)
		cout<<"alias :" <<*cur++<<endl;
	cout<<"type :" <<(host->h_addrtype==AF_INET ? "AF_INET" : "AF_INET6")<<endl;
	cur=host->h_addr_list;
	while(*cur)
		cout<<"addr_list :" <<*cur++<<endl;
	cout<<endl;
}
int main()
{
	struct hostent *host=NULL;
	while(host=gethostent())
		p(host);
	
	//d();
	return 0;
}