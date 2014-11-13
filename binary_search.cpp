#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
template<typename T>
void p(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>
void initC(T &c,int n)
{c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>
void testBinary_search(T &c){
cout<<"ret is "<<binary_search(c.begin(),c.end(),3)<<endl;
}
class A
{
public:
int a;
A(const int &_a):a(_a){}
operator int()const{return a;}
};
int main()
{
	vector<A> v;
	initC(v,10);
	testBinary_search(v);
	return 0;
}