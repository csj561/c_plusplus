#include <cstdio>
#include <string>
#include <iostream>
#include "class_handle.h"
using namespace std;

class A: public class_hdl_base
{
int a;
public:
A():a(0){cout<<"init A"<<endl;}
void p(){cout<<"a="<<a<<endl;}
void add(){a++;p();}
A * clone()const {return new A(*this);}
~A(){cout<<"destroy A"<<endl;}
};
int main()
{
	A a();
	class_hdl<A> c;
	
	getchar();
	return 0;
}