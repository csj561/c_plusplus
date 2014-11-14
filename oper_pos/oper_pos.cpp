#include <iostream>
#include <cstring>

using namespace std;
class A
{
	int a;
public:
	A(const int &_a):a(_a){}
	const int &operator[](const int &p) const
	{cout<<"const"<<endl;return a;}
	int &operator[](const int &p) 
	{cout<<"no const"<<endl;return a;}
};
void f1(const int &a)
{
}
void f2(int &a)
{
}
int main()
{
	A a(10);
	int i=a[0];
	int j=0;
	a[0]=j;
	return 0;
}
