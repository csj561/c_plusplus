#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	int cnt=10000000;
	vector<int> v(cnt);
	for(int i=0;i<cnt;i++)
		v[i]=i;
	random_shuffle(v.begin(),v.end());
	random_shuffle(v.begin(),v.end());
	ofstream ofs("out.dat");
	copy(v.begin(),v.begin()+8000000,ostream_iterator<int>(ofs,"\n"));
	ofs.close();
}
