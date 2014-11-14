#include <iostream>
#include <cstring>

using namespace std;

class A{
friend void B::F();
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
int main()
{
	B b;
	b.F();
	fun();
	return 0;
}
