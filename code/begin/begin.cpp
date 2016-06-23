#include <fool.h>

using namespace std;
int idx=0;
int f()
{return idx++;}
int main()
{
	const int sz=10;
	int *a=new int[sz];
	/*
	int* pb=begin(a);
	int* pe=end(a);
	*/
	generate_n(a,sz,f);
	for(int i : a )
		cout<<i<<endl;
	return 0;
}
