#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cstdio>
extern "C"{
#include <dirent.h>
#include <unistd.h>
}
using namespace std;
typedef list<string> list_dir;
template<typename T>void p(const T &c){for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) cout<<*iter<<endl; cout<<endl;}
int get_dirlist(list_dir &l)
{
	char *cpwd=getcwd(NULL,0);
	string pwd(cpwd);
	DIR *dp=NULL;
	dirent dire,*cur=NULL;
	
	free(cpwd);
	pwd+="/";
	if((dp=opendir(pwd.c_str()))==NULL)
	{
		perror("dopen ");
		return -1;
	}
	l.clear();
	while(1)
	{
		readdir_r(dp,&dire,&cur);
		if(!cur)
			break;
		if(cur->d_name[0]=='.'
		||DT_DIR!=cur->d_type)
			continue;
		l.push_back(pwd+cur->d_name);
	}
	closedir(dp);
	return 0;
}
int action(const  string &dir)
{
	string cmd("make -C ");
	cmd += dir + " clean";
//	cout<<cmd<<endl;
	return system(cmd.c_str());
}
int main()
{
	list_dir l;
	get_dirlist(l);
	for_each(l.begin(),l.end(),&action);
	return 0;
}
