#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
extern "C"{
#include <sys/time.h>
#include <unistd.h>
}
using namespace std;
typedef vector<int> vIint;
typedef list<int> lInt;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>void initC(T &c,int n){c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void addC(T &c,int n){for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
int get_rand(int r){struct timeval tv;gettimeofday(&tv,NULL);return tv.tv_usec%r;}
template<typename T>void randomC(T &t){vIint tmpV(t.begin(),t.end());random_shuffle(tmpV.begin(),tmpV.end(),get_rand);T tmpT(tmpV.begin(),tmpV.end());swap(t,tmpT);}
int main()
{
	vIint v;lInt l;
	initC(v,4);initC(l,10);
	p(l);
	randomC(l);
	p(l);
	return 0;
}