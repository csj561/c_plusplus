#include <iostream>
#include <cstring>

using namespace std;
class A
{
public:
	int a;
	A(int _a):a(_a){}
	void operator*(){cout<<"it's *"<<endl;}
	A& operator->(){cout<<"it's ->"<<endl;return *this;}
	A operator--(){cout<<"it's --"<<endl;return *this;}
	A operator--(int){cout<<"it's -- int"<<endl;return *this;}
};
bool operator||(A a1,A a2)
{
	return true;
}
int main()
{
	A a(10);
	int i=0,j=0;
	i=100;
	--j=100;
	cout<<"i = "<<i<<endl;
	cout<<"j = "<<j<<endl;
	return 0;
}
