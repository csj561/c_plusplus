#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <cstdio>
#include <time.h>
#include <dirent.h>
using namespace std;
struct info_elem
{
        string path;
        string fn; 
        bool isfile;
};
const uint32_t file_mask = /*IN_CLOSE_WRITE|*/IN_DELETE_SELF/*|IN_MODIFY*/;
const uint32_t dir_mask = IN_DELETE_SELF|IN_CREATE|IN_MOVED_FROM|IN_MOVED_TO|IN_DELETE;
map<uint32_t,info_elem> info_map;
int find_wd(const string &path)
{
	map<uint32_t,info_elem>::iterator iter = info_map.begin();
	for(;iter != info_map.end();iter++)
		if(path == iter->second.path)
			return iter->first;
	return -1;
}
bool is_dir(const string &path)
{
	struct stat st; 
        if(stat(path.c_str(),&st))
        {   
                string err = "[stat] :" + path + " > ";
                perror(err.c_str());
                return false;
        } 
	return S_ISDIR(st.st_mode);
}
void add_detect(const string &path,int fd) 
{
        
        info_elem elem;
        elem.path = path;
        elem.isfile = !is_dir(path);
	int ret = inotify_add_watch(fd,path.c_str(),elem.isfile ? file_mask : dir_mask);
	info_map[ret] = elem;
	if(!elem.isfile)
	{
		DIR *pdir;
		struct dirent *p_dir;
		pdir = opendir(path.c_str());
		while((p_dir=readdir(pdir)))
		{
			if(string(".") == p_dir->d_name || string("..") == p_dir->d_name)
				continue;
			string _path = path + (path[path.size() - 1] == '/' ? "" : "/") + p_dir->d_name;
			add_detect(_path,fd);
		}
	}
}
const char * getEventStr(uint32_t event)
{
	if(IN_CLOSE_WRITE&event)
		return "write_close";
	else if(IN_DELETE&event)
		return "delete";
	else if(IN_DELETE_SELF&event)
		return "delete_self";
	else if(IN_CREATE&event)
		return "create_file";
	else if(IN_MODIFY&event)
		return "modify_file";
	else if(IN_MOVED_FROM&event)
		return "move_from";
	else if(IN_MOVED_TO&event)
		return "move_to";
	
	return "No this event";
}

void process(struct inotify_event *ev,int fd)
{
	string log;
	time_t rawtime;
    struct tm * timeinfo;
    char buffer [128];
 
    time (&rawtime);
    timeinfo = localtime (&rawtime);
 
    strftime (buffer,sizeof(buffer),"[%Y/%m/%d %H:%M:%S] ",timeinfo);
	info_elem &elem = info_map[ev->wd];
	log = string(buffer) + "Detect [" + elem.path + "] event: " + getEventStr(ev->mask);
	if(ev->mask & (IN_CREATE|IN_MOVED_TO))
	{
		string new_file = elem.path + (elem.path[elem.path.size()-1] =='/'? "" : "/") + ev->name;
		log = log + "[" + new_file +"] type : [" + (is_dir(new_file) ? "Dir" : "File")+ "]";
		add_detect(new_file,fd);
	}
	if(ev->mask & IN_DELETE_SELF)
	{
		inotify_rm_watch(fd,ev->wd);
		info_map.erase(ev->wd);
	}
	if(ev->mask & IN_DELETE)
	{
		string new_file = elem.path + (elem.path[elem.path.size()-1] =='/'? "" : "/") + ev->name;
		log = log + "[" + new_file +"]";
		int wd = find_wd(new_file);
		if(wd>=0)
		{
			if(info_map[wd].isfile)
				return ;
			inotify_rm_watch(fd,wd);
			info_map.erase(wd);
		}
	}
	if(ev->mask & IN_MOVED_FROM)
	{
		string new_file = elem.path + (elem.path[elem.path.size()-1] =='/'? "" : "/") + ev->name;
		log = log + "[" + new_file +"]";
		int wd = find_wd(new_file);
		if(wd>=0)
		{
			inotify_rm_watch(fd,wd);
			info_map.erase(wd);
		}
	}
	cout<<log<<endl;
}

int main(int argc,char **argv)
{
    int fd  = inotify_init();
	if(fd<0)
	{
		perror("[inotify_init]");
		return 0;
	}
	add_detect(argv[1],fd);
	while(1)
	{
		uint8_t buf[BUFSIZ] = {0};
		uint8_t *cur = buf;
		int ret = read(fd,buf,BUFSIZ);
		if(ret <0)
		{
			perror("[read]");
			return -1;
		}
		do{
			struct inotify_event * ev = (struct inotify_event *)cur;
			if((ev->mask & (file_mask|dir_mask))==0)
				break;
			process(ev,fd);
			cur += sizeof(struct inotify_event) + ev->len;
		}
		while(cur-buf < ret);
		
		if(!info_map.size())
		{
			cout<<"No detect file .Exit"<<endl;
			break;
		}
	}
	close(fd);
	return 0;
}
