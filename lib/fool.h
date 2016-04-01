/*
*
*xyd 2016-1-9
*
*/
#ifndef FOOL_H
#define FOOL_H
#define K 1024
#define QRCODE_MAX_LEN K
#define MACRO_COMB(x,y) x#y
char _curtm[K/8];
#include <cstdio>
#ifdef __linux__
#include <sys/time.h>
#endif
void __gettm()
{
	time_t t;
	int len=0;
	#ifdef __linux__
	struct timeval tv;
	gettimeofday(&tv,NULL);
	t=tv.tv_sec;
	#else
	t=time(NULL);
	#endif
	struct tm*_tm=localtime(&t);
	len=strftime(_curtm,sizeof(_curtm),"[%Y/%m/%d %H:%M:%S]",_tm);
	#ifdef __linux__
	sprintf(_curtm+len-1," %06ld]",tv.tv_usec);
	#endif
}
#define CUTTM (__gettm(),_curtm)
#define DEG(x,...) {\
	char buf[K];\
	snprintf(buf,sizeof(buf),"[%s:%d] %s\n",__FILE__,__LINE__,x);\
	fprintf(stdout,buf,##__VA_ARGS__);\
	}
#define XDEG(x,...) {\
	char buf[K];\
	snprintf(buf,sizeof(buf),"%s[%s:%d] %s\n",CUTTM,__FILE__,__LINE__,x);\
	fprintf(stdout,buf,##__VA_ARGS__);\
	}
struct pre_tree;
/*C和C++兼容接口*/
#define COM_INTERFACES \
	bool is_exist(const char *filepath); \
	bool is_regfile(const char *filename); \
	bool is_dir(const char *filename); \
	const char *get_filename(const char *filepath); \
	bool cp(const char *src,const char *dest); \
	bool mv(const char *src,const char *dest); \
	bool check_suffix(const char *fn,const char *suffix);/*("/home/xyd/a.txt","txt")*/ \
	int scan_image(const char *fn,char *buf,int bufsz); \
	const char *scan_err(int err_code); \
	int qr_image_create(const char * text,const char *fn); \
	const char *qr_image_err(int err_code); \
	bool isspace_str(const char *line); \
	int rm_space_line(const char *fn); \
	bool check_date(const char *datetime); /*eg:20160201*/ \
	const char * BM_find(const char *src,const char *str); /*字符串匹配的Boyer-Moore算法*/ \
	char * replace_str(const char *src,const char *ostr,const char *nstr); \
	pre_tree * pre_create_pretree(); /*prefix tree*/ \
	bool pre_add_item(pre_tree *p_tree,const char *,void *); \
	void *pre_find(const char *,int ); \
	void pre_destory_pretree(pre_tree *);

enum EN_SCAN
{
	EN_SCAN_NO_INFO=0,
	EN_SCAN_ERR_FMT,
	EN_SCAN_ERR_SHORT_BUF,
	EN_SCAN_ERR_LONG_INFO,
	EN_SCAN_ERR_OPEN_IMG,
	EN_SCAN_XXX
};
enum EN_ENCODE_QR
{
	EN_ENCODE_QR_OK =0,
	EN_ENCODE_QR_ERR_FMT,
	EN_ENCODE_QR_ERR_LONG_INFO,
	EN_ENCODE_QR_ERR_NULL_INFO,
	EN_ENCODE_QR_ERR_ENCODE,
	EN_ENCODE_QR_ERR_OPENFILE,
	EN_ENCODE_QR_ERR_MALLOC,
	EN_ENCODE_QR_XXX
};
#ifdef __cplusplus
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

namespace fool
{
	template<typename T>
	void Pri(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<*iter<<"\n";
	}

	template<typename T>
	void PriM(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<iter->first<<" <> "<<iter->second<<"\n";
	}
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
	template<typename InputIter1,typename InputIter2>
	int count_blk(InputIter1 iter1_beg,InputIter1 iter1_end,
				InputIter2 iter2_beg,InputIter2 iter2_end)
	{
		int count=0;
		int iter2_len=0;
		InputIter1 cur=iter1_beg;
		InputIter2 t = iter2_beg;
		
		while(t++!=iter2_end)
			iter2_len++;
		while(iter1_end!=(cur=std::search(cur,iter1_end,iter2_beg,iter2_end)))
		{
			count++;
			for(int i=0; i<iter2_len;i++)
				cur++;
		}
		return count;
	}
	#if 0
	template<typename KEY,typename VALUE>
	class Stree
	{
		struct leaf
		{
			VALUE val;
			KEY key;
			std::set<leaf> leafs;
			bool is_root;
			bool is_have_val;
		}
		leaf root;
	public:
		bool add(std::vector<KEY> const &key,const VALUE &val)
		{
			typename std::vector<KEY>::iterator;
			leaf* cur=&root;
			for(std::vector<KEY>::iterator iter=key.begin();
				iter!=key.end();iter++)
			{
				std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
				{
					leaf tmp;
					tmp.key=*iter;
					if(key.end()==iter)
					{
						tmp.val=val;
						tmp.is_have_val = true;
					}
					cur->leafs.insert(tmp);
				}
				else
				{
					if(key.end()==iter&&liter->is_have_val)
						return false;
					cur=&liter->leafs;
				}
			}
			return true;
		}
		bool match(const std::vector<KEY> &key,VALUE &val,std::vector<KEY> *ret=NULL)
		{
			return true;
		}
	};
	#endif

}
namespace fool
{
	COM_INTERFACES;
	int scan_image(const char *fn,std::list<std::string> &ret);
	const char *strstr(const char *src,const char *str);
	void replace_str(std::string &str,const char *ostr,const char *nstr);
}
#define FOOL_IS_CPLUSPLUS 1
#else
#include <stdbool.h>
#define FOOL_IS_CPLUSPLUS 0
#endif
#ifdef __cplusplus
extern "C" {
#endif
#if defined(FOOL_CPP) || FOOL_IS_CPLUSPLUS == 0
/*只被C文件和库的源文件包含*/
COM_INTERFACES;

#endif
#undef FOOL_IS_CPLUSPLUS
#ifdef __cplusplus
}
#endif
#endif
