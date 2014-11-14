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

template<typename T,typename P,typename Q>
void testMerge(T &c,P &p,Q &q){
merge(c.begin(),c.end(),p.begin(),p.end(),back_inserter(q));
}
template<typename T>
void testInplace_merge(T &t){inplace_merge(t.begin(),find(t.begin(),t.end(),9)+1,t.end());}

int main()
{
	vector<int> v,vv;
	list<int> l;
	deque<int> deq;
	initC(v,10);
	addC(v,6);
	p(v);
	testInplace_merge(v);
	p(v);
	return 0;
}