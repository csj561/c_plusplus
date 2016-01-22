#include <iostream>
#include <fool.h>
#include <map>
using namespace std;
//using namespace fool;

int main(int argc,char **argv)
{
	char buf[1024];
	const char *p;
	list<string> l;
	int ret = fool::scan_image(argv[1],l);
	if(ret>0)
		fool::Pri(l);
	else
		cout<<fool::scan_err(ret)<<endl;
	return 0;
}
