#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>void initC(T &c,int n){c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void initC(T &c,int from,int to){c.clear();for(from;to!=to;from++)c.push_back(typename T::value_type(from));}
template<typename T>void addC(T &c,int n){for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T,typename P>void testIncludes(T &t,P &p){cout<<"ret is "<<includes(t.begin(),t.end(),p.begin(),p.end()) <<endl;}
template<typename T,typename P,typename Q>
void testSet_unique(T &t,P &p,Q &q){set_union(t.begin(),t.end(),p.begin(),p.end(),back_inserter(q));}


int main()
{
	vector<int> v,vv(3);
	list<int> l;
	initC(l,10);addC(vv,5);
	testSet_unique(l,vv,v);
	p(v);
	return 0;
}