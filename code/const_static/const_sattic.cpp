#include <iostream>
#include <cstring>

using namespace std;

class A{
friend class B;
friend void fun();
void f(){}
};
class B{
public:
	A a;
	void F(){a.f();}
};

void fun()
{
	A a;
	a.f();
}
class C{
	public :
	const static int i=100;
	static int j;
};
int C::j=1000;
int main()
{
	B b;
	b.F();
	fun();
	cout<<"C::j="<<C::j<<endl;
	return 0;
}
