#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
using namespace std;
template<typename T>
void p(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>
void initC(T &c,int n)
{c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T,typename P>
void testCopy(T &c,P &p){
copy(c.begin(),c.end(),back_inserter(p));
}

int main()
{
	vector<int> v;
	list<int> l;
	initC(v,10);
	testCopy(v,l);
	p(l);
	return 0;
}