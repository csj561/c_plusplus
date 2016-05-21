#include <string>
#include <iostream>
using namespace std;
class A{};
bool operator<(A a,A b){cout<<__func__<<endl;return true;}
int main()
{
	A a , b ,c;
	if(a<b||b<c)
	{}
	return 0;
}