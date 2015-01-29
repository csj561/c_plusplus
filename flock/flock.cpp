#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
extern "C"
{
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
}
using namespace std;
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type=type;
	lock.l_start=offset;
	lock.l_whence=whence;
	lock.l_len=len;
	return fcntl(fd,cmd,&lock);
}
int get_lock(int fd, int type, off_t offset, int whence, off_t len, struct flock &lock)
{
	lock.l_type=type;
	lock.l_start=offset;
	lock.l_whence=whence;
	lock.l_len=len;
	return fcntl(fd,F_GETLK,&lock);
}
void p_lock(const struct flock &lock)
{
	cout<<"type :";
	switch (lock.l_type)
	{
		case F_RDLCK:
		cout<<"F_RDLCK"<<endl;break;
		case F_WRLCK:
		cout<<"F_WRLCK"<<endl;break;
		case F_UNLCK:
		cout<<"F_UNLCK"<<endl;break;
	}
	cout<<"start :"<<lock.l_start<<endl;
	cout<<"whence :";
	switch (lock.l_whence)
	{
		case SEEK_SET:
		cout<<"SEEK_SET"<<endl;break;
		case SEEK_CUR:
		cout<<"SEEK_CUR"<<endl;break;
		case SEEK_END:
		cout<<"SEEK_END"<<endl;break;
	}
	cout<<"len :"<<lock.l_len<<endl;
}
int main(int argc,char **argv)
{
	const string fn("flock.txt");
	int fd;
	pid_t pid;
	{
	ofstream ofs(fn.c_str(),ios::out|ios::trunc);
	ofs<<"123";
	}
	if((pid=fork())>0)
	{
		fd=open(fn.c_str(),O_WRONLY);
		int ret=lock_reg(fd,F_SETLK,F_WRLCK,0,SEEK_SET,1);
		ret|=lock_reg(fd,F_SETLK,F_WRLCK,2,SEEK_SET,1);
		cout<<"parent set lock "<<(ret ? "failed" : "OK")<<endl;
		waitpid(pid,NULL,0);
	}
	else if(pid==0)
	{
		sleep(1);
		struct flock lock;
		fd=open(fn.c_str(),O_WRONLY);
		get_lock(fd,F_WRLCK,0,SEEK_SET,3,lock);
		p_lock(lock);
	}
	return 0;
}
