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
	if(argc!=2)
	{
		cerr<<"Two arguments !!!"<<endl;
		return -1;
	}
	ifstream ifs(argv[1],ifstream::ate|ifstream::in);
	if(!ifs)
	{
		cerr<<argv[1]<<" Open error!!!"<<endl;
		return -1;
	}
	cout<<argv[1]<<" size is "<<ifs.tellg()<<" bites"<<endl;
	ifs.close();
	return 0;
}
