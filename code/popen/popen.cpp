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
void d(){long long i=1000000000;
	while(i--);}
int main()
{
	
	FILE *fp=NULL;
	const int k=1024;
	char buf[k];
	fp=popen("sleep 3","r");
	while(0&&fgets(buf,k,fp))
	{
		puts(buf);
		//getchar();
	}
	cout<<"end-----------"<<endl;
	pclose(fp);
	cout<<"end-----------"<<endl;
	//d();
	return 0;
}