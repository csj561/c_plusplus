#include <iostream>
#include <fool.h>
#include <map>
#include <cstring>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
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

#if 0
	map<int,int> m;
	int &i=m[10];
	i=199;
	fool::PriM(m);
#endif
#if 0
	XDEG("%d",100);
#endif
#if 0
	string s="123";
	string s1="1234";
	vector<char> v1(s.begin(),s.end());
	vector<char> v2(s1.begin(),s1.end()),r;
	fool::PreTree<char,int> t;
	cout<<t.add( v1,1)<<endl;
	cout<<t.add(v2,2)<<endl;
	string _key="12378655";
	vector<char> key(_key.begin(),_key.end());
	int ret=0;
	cout<<t.match(key,ret,&r)<<endl;
	fool::Pri(r);
#endif
#if 0
	string s="123";
	string s1="1234",r;
	
	fool::PreTree<string,int> t;
	t.add( s,1);
	t.add(s1,2);
	string _key="12378655";
	int ret=0;
	t.match(_key,ret,&r);
	cout<<r<<endl;
	t.match("123456",ret,&r);
	cout<<r<<endl;
	t.del("1234");
	t.del("123");
	t.match(_key,ret,&r);
	cout<<r<<endl;
	t.match("123456",ret,&r);
	cout<<r<<endl;
#endif
#if 0
	cout<<bitset<16>(fool::g711_alaw_decode_sample(0b10011100))<<endl;
#endif
#if 0
	fool::timer tmm("Test timer");
	std::cout<<"fadfafafa"<<std::endl;
	string s=fool::time_to_str((int)time(NULL));
	XDEG("Now time [%s]",s.c_str());
	time_t t=fool::str_to_time(s.c_str(),3);
	XDEG("sys time %d transfer time %d",(int)time(NULL),(int)t);
	{
		fool::timer();
	}
#endif
	int sz=1000*10000;
	vector<int> v(sz);
	{
		fool::timer t("Push to vector");
		for(int i=0;i<sz;i++)
			v[i]=i;
	}
	
	{
			fool::timer t("random_shuffle");
			random_shuffle(v.begin(),v.end());
		}

	
	
	{
		fool::timer t("sort std");
		sort(v.begin(),v.end());
	}
	cout<<"v size "<< v.size()<<endl;
	cin>>sz;
return 0;

}
