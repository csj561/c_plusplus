/*
*
*xyd 2016-1-9
*
*/

#define FOOL_CPP
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <cstring>
#include <dirent.h>
#include "fool.h"
#include <fstream>
#include <algorithm>
extern "C" {
#include <png.h>

}
#include <zbar.h>

#define BUFLEN 256
#define K 1024
#define log_err(x,...) fprintf(stderr,x,##__VA_ARGS__)
#define log_warn(x,...) fprintf(stdout,x,##__VA_ARGS__)
#define log_errno(x,...) do{ \
							char buf[K],errbuf[BUFLEN]; \
							strerror_r(errno,errbuf,BUFLEN); \
							sprintf(buf,"[%s:%d]ERROR: %s [%s]",__FILE__,__LINE__,x,errbuf); \
							fprintf(stderr,buf,##__VA_ARGS__); \
						   }while(0)

namespace fool
{
	using std::ifstream;
	using std::ofstream;
	static mode_t get_file_type(const char *fn)
	{
		struct stat st;
		memset(&st,0,sizeof(struct stat));
		if(-1 == stat(fn,&st))
			return 0;
		return st.st_mode;
	}
	// TODO È¨ÏÞ¸´ÖÆ
	static bool _cpfile2file(const char *src,const char *dest)
	{
		ifstream ifs(src);
		ofstream ofs(dest);
		if(ifs&&ofs)
		{
			ofs<<ifs.rdbuf();
			return true;
		}
		return false;
	}
	
	static bool _cp(const char *src,const char *dest,bool mv = false)
	{
		if(!is_exist(src))
			goto err;
		if(is_regfile(src))
		{
			if(!is_exist(dest) ||is_regfile(dest))
			{
				if(!mv || (-1 == rename(src,dest) && EXDEV == errno))
				{
					if(!_cpfile2file(src,dest))
						goto err;
					if(mv&&-1 == remove(src))
					{
						log_errno("Remove %s.\n",src);
						goto err;
					}
				}
				else 
				{
					log_errno("rename [%s to %s]",src,buf);
					goto err;
				}
			}
			else if(is_dir(dest))
			{
				log_err("%s is exist, and it's a file",dest);
				goto err;
			}
			
		}
		else if(is_dir(src))
		{
			bool _is_exist = is_exist(dest);
			if(mv&& _is_exist)
			{
				log_err("%s is exist",dest);
				goto err;
			}
			else
			{
				int ret = 0; 
				if(!mv ||(-1 == (ret= rename(src,dest)) && EXDEV == errno))
				{
					if(_is_exist ||( !_is_exist&&!mkdir(dest,0755)))
					{
						
						DIR *dp=NULL;
						dirent *pdir,dir;
						dp=opendir(src);
						if(!dp)
						{
							log_err("Open dir [%s] failed.\n",src);
							goto err;
						}
						do
						{
							readdir_r(dp,&dir,&pdir);
							if(!pdir)
								break;
							if(!strcmp(".",pdir->d_name) || !strcmp("..",pdir->d_name))
								continue;
							if(DT_REG==pdir->d_type||DT_DIR==pdir->d_type)
							{
								char bufs[K],bufd[K];
								strcpy(bufs,src);
								strcat(bufs,"/");
								strcat(bufs,pdir->d_name);

								strcpy(bufd,dest);
								strcat(bufd,"/");
								strcat(bufd,pdir->d_name);
								if(!_cp(bufs,bufd,mv))
								{
									closedir(dp);
									log_err("Copy [%s] to [%s] err.\n",bufs,bufd);
									goto err;
								}
							}
							else
							{
								log_warn("Only suport copy reguler file and dir. [%s/%s] isn't a reguler or dir\n",
									src,pdir->d_name);
							}
						}while(1);
						closedir(dp);
						if(mv&&-1== rmdir(src))
						{
							log_errno("rmdir %s.\n",src);
							goto err;
						}
					}
					else
					{
						log_errno("mkdir dir %s failed.\n",dest);
						goto err;
					}
				}	
				else if(-1 == ret)
				{
					log_errno("rename [%s to %s]",src,dest);
					goto err;
				}
				
			}
		}
		return true;
		err:
			return false;
	}

	static bool cp_mv(const char *src,const char *dest, bool flags)
	{
		if(is_exist(dest)&&is_dir(dest))
		{
			char buf[K];
			strcpy(buf,dest);
			strcat(buf,"/");
			strcat(buf,get_filename(src));
			return _cp(src,buf,flags);
		}
		return _cp(src,dest,flags);
	}
	
	bool check_suffix(const char *fn,const char *suffix)
	{
		const char *result = std::find_end(fn,fn+strlen(fn),
			suffix,suffix+strlen(suffix));
		if(result != fn+strlen(fn)&&result != fn&&'.' == *(result-1))
		{
			return true;
		}
		return false;
	}
	
	bool is_exist(const char *filepath)
	{
		return !access(filepath,F_OK);
	}
	bool is_regfile(const char *filename)
	{
		return S_ISREG(fool::get_file_type(filename));
	}
	
	bool is_dir(const char *filename)
	{
		return S_ISDIR(fool::get_file_type(filename));
	}
	
	bool cp(const char *src,const char *dest)
	{
		return fool::cp_mv(src,dest,false);
	}
	bool mv(const char *src,const char *dest)
	{
		return fool::cp_mv(src,dest,true);
	}
	const char *get_filename(const char *filepath)
	{
		const char *pe=filepath+strlen(filepath) - 1;
		while(filepath!=pe && '/' == *pe)
			pe--;
		while(filepath!=pe && '/' !=*--pe);
		return '/' == *pe && filepath!=pe ? pe+1 : pe;
	}
	int scan_image(const char *fn,char *buf,int bufsz)
	{
		return ::scan_image(fn,buf,bufsz);
	}
	const char *scan_err(int err_code)
	{
		return ::scan_err(err_code);
	}
}

bool check_suffix(const char *fn,const char *suffix)
{
	return fool::check_suffix(fn,suffix);
}

bool is_exist(const char *filepath)
{
	return fool::is_exist(filepath);
}
bool is_regfile(const char *filename)
{
	return fool::is_regfile(filename);
}

bool is_dir(const char *filename)
{
	return fool::is_dir(filename);
}

bool cp(const char *src,const char *dest)
{
	return fool::cp(src,dest);
}
bool mv(const char *src,const char *dest)
{
	return fool::mv(src,dest);
}
const char *get_filename(const char *filepath)
{
	return get_filename(filepath);
}

