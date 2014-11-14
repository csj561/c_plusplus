#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <functional>
#include <algorithm>
#include <utility>
using namespace std;
template<typename T>
void p(const T &t)
{
	for(typename T::const_iterator iter=t.begin();iter!=t.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;
}
template<typename T>
void p(T beg,T end)
{
	while(beg!=end)
		cout<<*beg++<<" ";
	cout<<endl;
}
template<typename T>
void init2N(T &c,int n)
{
	
}
int generate_f()
{
	static int i=0;
	return i--;
}
void testGenerate_n()
{
	list<int> l(9);
	generate_n(l.begin(),5,generate_f);
	p(l);
	//cout<<endl;
}
void testFill_n()
{
	list<int> l(9);
	fill_n(++l.begin(),5,6);
	p(l);
	//cout<<endl;
}
int main()
{
testFill_n();
	return 0;
}
