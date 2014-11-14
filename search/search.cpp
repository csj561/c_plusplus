#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
//#include <utility>
using namespace std;

vector<int> t;
vector<int> t2;
void init()
{
	int i=10;
	do
	{
	t.push_back(i);
	if(i==8)
	t.push_back(i);
	}
	while(--i);
}
void init2()
{
	int i=6;
	do
	t2.push_back(i);
	while(i--);
}

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
void testNegate()
{
	negate<int> intNegate;
	for(vector<int>::iterator iter=t.begin();iter!=t.end();iter++)
		cout<<intNegate(*iter)<<" ";
	cout<<endl;
}
void testSort()
{
	sort(t.begin(),t.end(),not2(less<int>()));
	p(t);
}
void testCount_if()
{
	int ret=count_if(t.begin(),t.end(),
			(bind1st(greater<int>(),2)));
	cout<<"ret is "<<ret <<endl;
}
void testMismatch()
{
	string s1="meet",s2="meat";
	pair<string::iterator,string::iterator> ret=mismatch(s1.begin(),s1.end(),s2.begin());
	p(ret.first,s1.end());
}
void testEqual()
{
	string s1="meet",s2="meat";
	cout<<"ret is same :: "<<equal(s1.begin(),s1.end(),s1.begin())<<endl;
}
template<typename T>
void testBound(const T& t)
{
	cout<<"lower 8 index "<<lower_bound(t.begin(),t.end(),8)-t.begin()<<endl;
	cout<<"lower 8 index "<<upper_bound(t.begin(),t.end(),8)-t.begin()<<endl;
}
template<typename T>
void testRange(const T& t)
{
	pair<typename T::const_iterator,typename T::const_iterator> ret=equal_range(t.begin(),t.end(),8);
	cout<<"Range 8 index "<<ret.first-t.begin()<<" "
	<<ret.second-t.begin()<<endl;
}
class A{
public:
int v;
	A(int a):v(a){}
	
	//operator int(){return v;}
	void p(){cout<<"v="<<v<<endl;}
};
//bool operator==(const A &a,const A &b){return a.v==b.v;}
bool operator<(const A &a,const A &b){return a.v<b.v;}
bool operator>(const A &a,const A &b){return a.v>b.v;}
vector<A> a;
void initA()
{
	int i=6;
	do
	a.push_back(A(i));
	while(i--);
}
template<typename T>
void testBinary_search(T& tt)
{
	cout<<"ret is "<<binary_search(tt.begin(),tt.end(),A(22))<<endl;
}
int main()
{
	init();
	init2();
	initA();
	testBinary_search(a);
	return 0;
}
