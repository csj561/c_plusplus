#include <iostream>
#include <cstring>

using namespace std;
class A{
	public:
		//A(double d){cout<<"create A"<<endl;}
		operator int(){return 0;}
		//int operator+(int ){cout<<"in A +"<<endl;return 0;}
};
void f(int  a)
{}
int operator+(A, int){cout<<"in +"<<endl;return 0;}
int main()
{
	A a;
	a+2.0;
	return 0;
}
