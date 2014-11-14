#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void f(string &a){}
int main()
{
	f(string("xxx"));
	return 0;
}
