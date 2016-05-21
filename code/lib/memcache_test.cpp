#include <iostream>
#include <vector>
#include <string>
#include <libmemcached/memcached.hpp>
using namespace std;
using namespace memcache;
typedef vector<char> vch;
int main()
{
	vch data;
	Memcache mcache(string("127.0.0.1"),11211);
	string e;
	mcache.error(e);
	cout<<"Error:: "<<e<<endl;
	bool b=mcache.get("xyd",data);
	mcache.error(e);
	cout<<"Error:: "<<e<<endl;
	string s(data.begin(),data.end());
	cout<<"ret: "<<data.size()<<" value: "<<s<<endl;
}
