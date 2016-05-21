#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
using namespace std;
template<typename T>
void p(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>
void initC(T &c,int n)
{c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T,typename P,typename Q>
void testMerge(T &c,P &p,Q &q){
merge(c.begin(),c.end(),p.begin(),p.end(),back_inserter(q));
}

int main()
{
	vector<int> v;
	list<int> l;
	deque<int> deq;
	initC(v,10);
	initC(l,7);
	testMerge(v,l,deq);
	p(deq);
	return 0;
}