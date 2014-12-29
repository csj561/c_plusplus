#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
using namespace std;
class A{
public:
A(){cout<<"in "<<__func__<<endl;}
class B{
public:
B(){cout<<"in "<<__func__<<endl;}
void f(A a){a.f();}
};
B b;
void f();
};
void A::f(){}
int main()
{
	A a;
	return 0;
}