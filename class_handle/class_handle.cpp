#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "class_handle.h"
using namespace std;
class A: public class_hdl_base
{
public:
A(){cout<<"init A"<<endl;}
A(const A& rhl){cout<<"copy init A"<<endl;}
virtual void p()const{cout<<"in class A"<<endl;}
A * clone()const {return new A(*this);}
~A(){cout<<"destroy A"<<endl;}
};
class B: public A
{
public:
B(){cout<<"init B"<<endl;}
B(const B& rhl){cout<<"copy init B"<<endl;}
virtual void p()const{cout<<"in class B"<<endl;}
B * clone()const {return new B(*this);}
~B(){cout<<"destroy B"<<endl;}
};
typedef vector<class_hdl<A> > vectorA;
void p(const class_hdl<A> t)
{
	t->p();
}
int main()
{
	A a;B b;
	vectorA va;
	{
	class_hdl<A> c(a), d(b);
	va.push_back(c);va.push_back(d);}
	for_each(va.begin(),va.end(),p);
	getchar();
	va.erase(va.begin());
	getchar();
	return 0;
}