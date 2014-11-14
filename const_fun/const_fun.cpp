#include <iostream>
#include <cstring>
#include <string>
using namespace std;
class A
{
	public:
		int a;
		string s;
};
int main()
{
	A a;
	int b=200;
	cerr<<"s="<<a.s<<endl;
	cerr<<"a="<<a.a<<endl;
	int *c=new int[10]();
	cout<<"c[5]="<<c[5]<<endl;
	delete []c;
	return 0;
}
