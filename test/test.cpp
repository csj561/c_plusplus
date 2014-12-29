#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;
class A{
int a;
public:
A():a(0){}
operator int()const {return a;}
int set(int _a){return a=_a;}
};
int main(int argc,char **argv)
{
	vector<int> v;
	cout<<"max siz :" <<hex<<v.max_size()<<endl;
	return 0;
}
