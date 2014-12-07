#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <deque>
#include <functional>
using namespace std;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<" "; cout<<endl;}
template<typename T>void initC(T &c,int n){c.clear();for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void addC(T &c,int n){for(int i=0;i<n;i++)c.push_back(typename T::value_type(i));}
template<typename T>void rsort(T &c){sort(c.begin(),c.end(),greater<typename T::value_type>());}
template<typename T>void quick_sort(T *p, int size)
{
	if(size<=1)
		return;
	{
		typedef T* iter;
		iter ibeg=p,iend=p+size-1;
		T key=*p;
		while(ibeg<iend)
		{
			while(ibeg<iend && key<*iend)
				iend--;
			*ibeg=*iend;
			while(ibeg<iend && *ibeg<key)
				ibeg++;
			*iend=*ibeg;
		}
		*ibeg=key;
		quick_sort(p,ibeg-p);
		quick_sort(ibeg+1,p+size-(ibeg+1));
	}
}
typedef vector<int> vInt;
int main()
{
	vInt v;
	initC(v,10);
	reverse (v.begin(),v.end());
	p(v);
	quick_sort(&v[0],v.size());
	p(v);
	return 0;
}