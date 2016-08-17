#include "mem_pool.h"
#include <string>
using namespace std;

struct C
{
	string s;
	int i;
	char c;
	short i16;
	double d;
};

int main()
{
	const int cnt=10;
	mem_pool<C> cp;
	C *cs[cnt];
	for (int i=0;i<cnt;i++)
		cs[i]=cp.construct();
	//for(int i=0;i<cnt;i++)
	//	cp.destroy(cs[i]);
}
