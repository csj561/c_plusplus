#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <map>
using namespace std;
typedef vector<string> vstr;
typedef map<string,int> msi;
typedef map<string,string> mss;
mss m_;

/*遍历打印map中的内容*/
template<typename T>
void pm(const T &c)
{for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<iter->first<<" == "<<iter->second<<endl; cout<<endl;}


/*
	获取目录下面的文件(或者目录)， .或者..会被过滤掉
	   DT_BLK      This is a block device.

       DT_CHR      This is a character device.

       DT_DIR      This is a directory.

       DT_FIFO     This is a named pipe (FIFO).

       DT_LNK      This is a symbolic link.

       DT_REG      This is a regular file.

       DT_SOCK     This is a UNIX domain socket.

       DT_UNKNOWN  The file type is unknown.

       -1 		   All files.

*/
void get_file_list(const string &path,msi &m,int type = -1)
{
	struct stat st;
	string base_dir = path + ('/' == path[path.size()-1] ? "" : "/");
	m.clear();
	if(-1 == stat(path.c_str(),&st) || !S_ISDIR(st.st_mode))
	{
		return;
	}
	DIR *dp=NULL;
	struct dirent *pdir=NULL,dir;
	dp = opendir(path.c_str());
	if(dp)
	{
		while(0==readdir_r(dp,&dir,&pdir)&&pdir)
		{
			if(0==strcmp(pdir->d_name,".")||0==strcmp(pdir->d_name,".."))
				continue;
			if(-1 == type)
				m[base_dir+pdir->d_name] = pdir->d_type;
			else if(type == pdir->d_type)
				m[base_dir+pdir->d_name] = pdir->d_type;
		}
		closedir(dp);
	}
	//pm(m);
}
/*替换string中的内容，map中first为旧值，second为新值*/
void procss_line(string &line,const mss &m)
{
	for(mss::const_iterator iter = m.begin();iter!=m.end();iter++)
	{
		while(1)
		{
			string::size_type pos = line.find(iter->first);
			if(string::npos == pos)
				break;
			line.replace(pos,iter->first.size(),iter->second);
		}
	}
}
/*去除string中的回车换行符*/
void rm_nl(string &line)
{
	static mss m;
	if(!m.size())
	{
		m["\n"] = "";
		m["\r"] = "";
	}
	
	procss_line(line,m);
}
/*将string以key分割成两段,以最后一个key为分割点*/
vstr line_split(const string & line,const string &key)
{
	vstr ret;
	//rm_nl(line);
	string::size_type pos = line.find_last_of(key);
	if(string::npos == pos)
	{
		//cerr<<"Err file name "<<line<<endl;
		return ret;
	}
	ret.push_back(string(line.c_str(),pos));
	ret.push_back(string((line.c_str()+pos+key.size())));
	//cout<<ret[0]<<endl;
	//cout<<ret[1]<<endl;
	return ret;
}
void init_file(const string &file,mss &m)
{
	ifstream ifs(file.c_str());
	string line;
	if(!ifs)
		return;
	while(getline(ifs,line))
	{
		rm_nl(line);
		vstr ret = line_split(line,":");
		if(!ret.size())
			continue;
		if(ret[0] == ret[1])
			continue;
		m[ret[0]] = ret[1];
	}
	ifs.close();
}
void init()
{
	msi fm;
	m_["\n"] = "";
	m_["\r"] = "";
	get_file_list(string(getenv("HOME"))+"/.fmt",fm);
	for(msi::const_iterator iter = fm.begin();iter!=fm.end();iter++)
		init_file(iter->first,m_);
}



void procss_file(const string &fn,const mss &m)
{
	ifstream ifs(fn.c_str());
	string tmp_fn = fn+".tmp";
	ofstream ofs(tmp_fn.c_str());
	if(ifs&&ofs)
	{
		string line;
		while(getline(ifs,line))
		{
			procss_line(line,m);
			ofs<<line<<"\r\n";
		}
		ifs.close();
		ofs.close();
		rename(tmp_fn.c_str(),fn.c_str());
	}
}
string get_suffix(const string &fn)
{
	return strrchr(fn.c_str(),'.');
}
void indent_file(const string &fn)
{
	string tmp = tmpnam(NULL);
	tmp+=get_suffix(fn);
	ostringstream oss;
	oss<<"indent -kr -cli4 -nut -bl4 -bli0 -npsl "<<fn<<" -o "<<tmp<<" && mv "<<tmp<<" "<<fn;
	cout<<oss.str()<<endl;
	system(oss.str().c_str());
}
void process(const char *fn,mss &m)
{
	if(access(fn,F_OK))
		return;
	procss_file(fn,m);
	indent_file(fn);
	procss_file(fn,m);
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
		process(argv[i],m_);
	}
	return 0;
}
