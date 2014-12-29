#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;
class A{
int a;
public:
	A(int _a):a(_a){}
	void p()const {cout<<"a:"<<a<<endl;}
	~A(){cout<<"Destroy A:"<<a<<endl;}
};

int main()
{
	A a(20);
	allocator<A> alc;
	A *ap=alc.allocate(1);
	*ap=a;
	a.p();
	alc.construct(ap,a);
	ap->p();
	alc.destroy(ap);
	alc.deallocate(ap,1);
	return 0;
}