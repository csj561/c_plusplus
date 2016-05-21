#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
using namespace std;

vector<int> t;
void init()
{
	int i=10;
	do
	t.push_back(i);
	while(--i);
}
void p()
{
	for(vector<int>::iterator iter=t.begin();iter!=t.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;
}
void testNegate()
{
	negate<int> intNegate;
	for(vector<int>::iterator iter=t.begin();iter!=t.end();iter++)
		cout<<intNegate(*iter)<<" ";
	cout<<endl;
}
void testSort()
{
	sort(t.begin(),t.end(),not2(less<int>()));
	p();
}
void testCount_if()
{
	int ret=count_if(t.begin(),t.end(),
			(bind1st(greater<int>(),2)));
	cout<<"ret is "<<ret <<endl;
}
int main()
{
	init();
	testCount_if();
	return 0;
}
