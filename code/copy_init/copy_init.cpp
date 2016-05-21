#include <iostream>
#include <cstring>

using namespace std;
class C{
	public :
		C(const string &c){};
};
class A
{
	//A(const A&){cout<<"copy init"<<endl;}
public:
	A(const A&){cout<<"copy init"<<endl;}
	A(int a){}
	A & operator=(const A&a)
	{
		cout<<"this is operator ="<<endl;
		return *this;
	}
	//A(const string &s){cout<<"string init"<<endl;}
	A(const C &s){cout<<"class C init"<<endl;}
};
int main()
{
	A a(2);
	A b=C("xxxx");
	C c("xxx");
	return 0;
}
