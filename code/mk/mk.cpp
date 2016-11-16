#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
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
	vstr cmp_parm;// compile params
	string line;
	if(ifs)
	{
		while(getline(ifs,line))
		{
			boost::trim(line);
			if(0==line.size()||'#'==line[0])
				continue;
			cmp_parm.push_back(line);
		}
		ifs.close();
	}
	cflg=cmp_parm[0];
	string sysLib,usrLib;
	istringstream iss;
	string lib;
	iss.str(cmp_parm[1]);
	do
	{// 系统中自带的库
		lib="";
		iss>>lib;
		if(lib.size())
			sysLib+=" -l ",sysLib+=lib;
	}while(lib.size());
	iss.clear();
	iss.str(cmp_parm[2]);
	do
	{ // 用户自己的库，默认到HOME下的lib中
		lib="";
		iss>>lib;
		if(lib.size())
		{
			string libPath=string(getenv("HOME"))+"/lib/lib"+lib;
			if(!access(string(libPath+".so").c_str(),F_OK)
				||!access(string(libPath+".a").c_str(),F_OK))
			{
				usrLib+=" -l ",usrLib+=lib;
			}
		}
			
	}while(lib.size());
	cflg+=usrLib+sysLib;
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
		const char *CC="g++ ";
		if('c'== argv[i][strlen(argv[i])-1])
			CC="gcc ";
		ofs<<CC<<fn[0]<<" -o "<<fn[1]<<" "<<cflg;
		cout<<ofs.str()<<endl;
		system(ofs.str().c_str());
	}
	return 0;
}
