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
	void * operator new(size_t n){
	cout<<"in A new"<<endl;
	return ::operator new (n);
	}
	~A(){cout<<"Destroy A:"<<a<<endl;}
};

int main()
{
	A *p=reinterpret_cast<A*>(operator new (sizeof(A)));
	::new (p) A(50);
	operator new(10);
	p->~A();
	operator delete(reinterpret_cast<void *>(p));
	return 0;
}