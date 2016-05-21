#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <cstdlib>
#include <list>
extern "C"
{
#include <sys/types.h>
#include <dirent.h>
}
using std::string;
using std::cout;
using std::endl;

bool empty_dir(const string &path)
{
	DIR *dirp=NULL;
	struct dirent dir_elem,*dp;
	string _path(path);
	if((dirp=opendir(_path.c_str()))!=NULL)
	{
		while(1)
		{
			readdir_r(dirp,&dir_elem,&dp);
			if(!dp)
				break;
			if(string(dp->d_name)=="."||string(dp->d_name)=="..")
				continue;
			else if(dp->d_type==DT_DIR)
			{
				if(!empty_dir(path+"/"+dp->d_name))
					goto NOT_EMPTY;
			}
			else
			{
			NOT_EMPTY:
				closedir(dirp);
				return false;
			}
		}
		closedir(dirp);
	}
	return true;
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		cout<<"Two arguments!"<<endl;
		return -1;
	}
	cout<<argv[1]<<"is empty "<<(empty_dir(argv[1])?"true" : "false")<<endl;
	
	return 0;
}