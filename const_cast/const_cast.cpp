#include <iostream>
using namespace std;

class B
{
public:
    B() { m_iNum=0;}
public:
    int m_iNum;
};
void foo()
{
    const B b1;

    B *b2 = const_cast<B*>(&b1);

    B &b3 = const_cast<B&>(b1);
    b2->m_iNum = 200;    //fine
    b3.m_iNum = 300;    //fine
	cout<<b1.m_iNum<<endl;
}
int main( int argc, char * argv[] )
{
    	const int a=100;
	int &b=const_cast<int &>(a);
	b=200;
	cout<<a<<endl;
    return 0;
}
