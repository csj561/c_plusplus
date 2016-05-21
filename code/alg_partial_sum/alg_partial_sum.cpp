#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
using namespace std;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>void initC(T &c,int n){c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void addC(T &c,int n){for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void rsort(T &c){sort(c.begin(),c.end(),greater<typename T::value_type>());}
template<class T,class P>
void testPartial_sum(T &t,P &p){p.clear();partial_sum(t.begin(),t.end(),back_inserter(p));}
template<class T,class P>
void testAdjacent_diff(T &t,P &p){p.clear();adjacent_difference(t.begin(),t.end(),back_inserter(p));}

int main()
{
	vector<int> v;
	list<int> l;
	initC(v,5);
	random_shuffle(v.begin(),v.end());
	p(v);
	testAdjacent_diff(v,l);
	p(l);
	return 0;
}
