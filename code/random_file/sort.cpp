#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <foo.h>

using namespace std;

int main()
{
	const int cnt=10000000;
	bool bits[cnt];
	vector<int> v(cnt);
	vector<int> ov(cnt);
	for(int i=0;i<cnt;i++)
		v[i]=i;
	XDEG("start random");
	random_shuffle(v.begin(),v.end());
	random_shuffle(v.begin(),v.end());
	XDEG("end random");
	for(int i=0;i<cnt;i++)
		bit[v[i]]=false;
	for(auto a=v.begin();a!=v.begin();a++)
		if(bits[*a])
			ov[]

}
