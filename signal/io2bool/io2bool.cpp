#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;


int main()
{
	
	int s;
	while(cin>>s);
	cout<<boolalpha;
	cout<<"eof:"<<cin.eof()<<endl;
	cout<<"fail:"<<cin.fail()<<endl;
	cout<<"bad:"<<cin.bad()<<endl;
	cout<<"good:"<<cin.good()<<endl;
	return 0;
}