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
#include <sys/types.h>
#include <utime.h>
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
	template<typename InputIter,typename UnaryPre>
	InputIter find_if_not(InputIter iter1,InputIter iter2,UnaryPre pre)
	{
		while(iter1 != iter2)
		{
			if(!pre(*iter1))
				return iter1;
			iter1++;
		}
		return iter1;
	}
	static mode_t get_file_type(const char *fn)
	{
		struct stat st;
		memset(&st,0,sizeof(struct stat));
		if(-1 == stat(fn,&st))
			return 0;
		return st.st_mode;
	}
	// TODO 权限复制
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

	int scan_image(const char *fn,std::list<std::string> &ret_list)
	{
		char buf[10*K];
		const char *p = buf;
		ret_list.clear();
		int ret = fool::scan_image(fn,buf,10*K);
		for(int i = 0; i < ret; i++)
		{
			ret_list.push_back(p);
			p+=strlen(p)+1;
		}
		return ret;
	}
	int qr_image_create(const char * text,const char *fn)
	{
		return ::qr_image_create(text,fn);
	}
	const char * qr_image_err(int err_code)
	{
		return ::qr_image_err(err_code);
	}

	bool isspace_str(const char *str)
	{
		const char *last = str+strlen(str);
		return last == find_if_not(str,last,isspace);
	}

	int rm_space_line(const char *fn)
	{
		char buf[256];
	    if(NULL == fn || 0 == strlen(fn))
	    {
	        return 0;
	    }
	    std::string tmp_file = std::string(fn) + "-" + get_filename((const char*)tmpnam(buf));

	    /// 更新文件之后，保证文件的修改时间与更新之前相同
	    struct stat _src_stat;
	    if(-1 == ::stat(fn,&_src_stat))
	    {
	        return -errno;
	    }
	    ifstream ifs(fn);

	    ofstream ofs(tmp_file.c_str());

	    if(!ifs)
	    {   
	        /* 文件打开失败 */
	        return -errno;
	    }

	    if(!ofs)
	    {   
	        /* 文件打开失败 */
	        return -errno;
	    }
	    std::string line;
	    while(getline(ifs,line))
	    {
	       if(isspace_str(line.c_str()))
		   		continue;
		   ofs<<line<<"\n";
	    }

	    ifs.close();
	    ofs.close();
	    if(::rename(tmp_file.c_str(),fn))
	    {
	        return -errno;
	    }

	    struct utimbuf _src_timbuf;
	    _src_timbuf.actime = _src_stat.st_atime;
	    _src_timbuf.modtime = _src_stat.st_mtime;
	    ::utime(fn,&_src_timbuf);
		return 0;
	}

	bool check_date(const char *datetime)
	{        
        int year = 0;
        int month = 0;
        int day = 0;
        int _month_set1[] = {1,3,5,7,8,10,12}; 
        int _month_set2[] = {4,6,9,11};
        sscanf(datetime,"%4d%2d%2d",&year, &month, &day);
        
        if(_month_set1 + sizeof(_month_set1)/sizeof(_month_set1[0]) != find(_month_set1,
        _month_set1 + sizeof(_month_set1)/sizeof(_month_set1[0]),month)) 
        {
            if (day > 31)
            {
                return false;
            }
        }
        else if(_month_set2 + sizeof(_month_set2)/sizeof(_month_set2[0]) != find(_month_set2,
            _month_set2 + sizeof(_month_set2)/sizeof(_month_set2[0]),month)) 
        {
            if (day > 30)
            {
                return false;
            }
        }
        else
        {
            if(0 == year % 100)
            {
                if(0 == year % 400)
                {
                    if(day > 29)
                    {
                        return false;
                    }
                }
                else
                {
                    if(day > 28)
                    {
                        return false;
                    }
                }
            }
            else if(0 == year % 4)
            {
                if(day > 29)
                {
                    return false;
                }
            }
            else
            {
                if(day > 28)
                {
                    return false;
                }
            }
        }
        return true;
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

bool isspace_str(const char *str)
{
	return fool::isspace_str(str);
}

int rm_space_line(const char *fn)
{
	return fool::rm_space_line(fn);
}

bool check_date(const char *datetime)
{
	return fool::check_date(datetime);
}

