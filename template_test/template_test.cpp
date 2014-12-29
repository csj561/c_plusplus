#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>void add(const T &a,const T &b){cout<<"add ret is "<<a+b<<endl;}


template<typename T>void test(T t){cout<<"Template"<<endl;}
template<>void test(short t){cout<<"Short"<<endl;}
void test(short t){cout<<"common short"<<endl;}
template<class T> class A{
public:
void p(){cout<<"common A"<<endl;}
};
template<>
void A<const char *>::p(){cout<<"special A"<<endl;}
void f(const int &){cout<<"const f"<<endl;}
void f( int ){cout<<"common f"<<endl;}
int main()
{
	int a;
	const int b=0;
	f(a);
	f(b);
	return 0;
}
