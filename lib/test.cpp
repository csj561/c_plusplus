#include <iostream>
#include <fool.h>
#include <map>
using namespace std;
//using namespace fool;
int main(int argc,char **argv)
{
#if 0
	char buf[1024];
	const char *p;
	list<string> l;
	int ret = fool::scan_image(argv[1],l);
	if(ret>0)
		fool::Pri(l);
	else
		cout<<fool::scan_err(ret)<<endl;
#endif
#if 0
	int ret = fool::qr_image_create(argv[1],argv[2]);
	
	cout<<fool::qr_image_err(ret)<<endl;
#endif
#if 0
	cout<<fool::check_date(argv[1])<<endl;
#endif
	cout<<(bool)fool::BM_find(argv[1],argv[2])<<endl;
	return 0;
}
