#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
#include <cstdio>
using namespace std;
extern "C"
{
#include <unistd.h>
#include <signal.h>
}
void f(int signo)
{
	cout<<"got signal"<<endl;
}
string operator+(const string &s,int i)
{
	ostringstream os;
	os<<i;
	return os.str();
}
int main()
{
	for (int i=0;i<64;i++)
		psignal(i,(string("")+i).c_str());
	return 0;
}