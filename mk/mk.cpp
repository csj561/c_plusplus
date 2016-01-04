#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;
typedef vector<string> vstr;
string cflg("");
vstr fn_split(const string & fn)
{
	vstr ret;
	string::size_type pos = fn.find_last_of('.');
	if(string::npos == pos)
	{
		cerr<<"Err file name "<<fn<<endl;
		return ret;
	}
	ret.push_back(fn);
	ret.push_back(string(fn.c_str(),pos) + ".elf");
	struct stat st0,st1;
	if(0 == stat(ret[0].c_str(),&st0) && 0 == stat(ret[1].c_str(),&st1))
	{
		if(st1.st_mtime > st0.st_mtime)
		{
			cout<<ret[1]<<" is newer than "<<ret[0]<<endl;
			ret.clear();
		}
	}
	return ret;
}

void init()
{
	string fn(".cfg");
	if(access(fn.c_str(),F_OK))
	{
		fn=string(getenv("HOME"))+"/.gcc_cfg";
	}
	ifstream ifs(fn.c_str());
	if(ifs)
	{
		getline(ifs,cflg);
		ifs.close();
	}
}
int main(int argc,char **argv)
{
	if(argc == 1 )
	{
		cerr<<"No input file!!!"<<endl;
		return 0;
	}
	init();
	for(int i = 1;i < argc; i++)
	{
		vstr fn = fn_split(argv[i]);
		if(!fn.size())
			continue;
		ostringstream ofs;
		ofs<<"g++ "<<fn[0]<<" -o "<<fn[1]<<" "<<cflg;
		cout<<ofs.str()<<endl;
		system(ofs.str().c_str());
	}
	return 0;
}
