#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;
typedef vector<int> vIint;
template<typename T>
void p(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>
void initC(T &c,int n)
{c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>
void addC(T &c,int n)
{for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
#if 1
template<typename T>
void rsort(T &c){sort(c.begin(),c.end(),greater<typename T::value_type>());}
template<typename T>
void testPartition(T &t){partition(t.begin(),t.end(),not1( bind2nd(modulus<typename T::value_type>(),2)));}
template<typename T>
void testNth_elemetn(T &t){
nth_element(t.begin(),t.begin()+9,t.end());
}
#endif
int main()
{
	vIint s;
	initC(s,4);
	do p(s);
	while(next_permutation(s.begin(),s.end()));
		
	cout<<"end::";
	p(s);
	return 0;
}