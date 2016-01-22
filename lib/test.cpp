#include <iostream>
#include <fool.h>
#include <map>
using namespace std;
//using namespace fool;

int main(int argc,char **argv)
{
	char buf[1024];
	const char *p;
	int ret = fool::scan_image(argv[1],buf,1024);
	if(ret>0)
		p=buf;
	else
		p=fool::scan_err(ret);
	cout<<p<<endl;
	return 0;
}
