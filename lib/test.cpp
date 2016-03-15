#include <iostream>
#include <fool.h>
#include <map>
#include <cstring>
#include <string>
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
#if 0
	string s = argv[1];
	fool::replace_str(s,argv[2],argv[3]);
	cout<<argv[1]<<endl<<s<<endl;
	
#endif
#if 0
	cout<<fool::BM_find(argv[1],argv[2])<<endl;
#endif

#if 1
	map<int,int> m;
	int &i=m[10];
	i=199;
	fool::PriM(m);
#endif
return 0;

}
