#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;
template<typename T>
void p(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>
void initC(T &c,int n)
{c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>
void addC(T &c,int n)
{for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>
void rsort(T &c){sort(c.begin(),c.end(),greater<typename T::value_type>());}
template<typename T>
void testRemove(T &t){t.erase(remove_if(t.begin(),t.end(),bind2nd( modulus<typename T::value_type>(),2)),t.end());}
template<typename T>
void testUnique(T &t){
t.erase(
unique(t.begin(),t.end()),
t.end());
}


int main()
{
	vector<int> v,vv(10);
	list<int> l;
	initC(l,10);
	addC(l,10);
	
	p(l);
	reverse(l.begin(),l.end());
	p(l);
	return 0;
}