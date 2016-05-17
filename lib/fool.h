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
#if 0

#define DEG_LOG 0
#if DEG_LOG
static FILE *flog=stdout;
#define K 1024
#define DEG(x,...) {\
    char buf[K];\
    snprintf(buf,sizeof(buf),"[%s:%d] %s\n",__FILE__,__LINE__,x);\
    fprintf(stdout,buf,##__VA_ARGS__);\
}
#define XDEG(x,...) {\
    time_t t;\
    char _curtm[256];\
    int len=0; \
struct timeval tv;\
    gettimeofday(&tv,NULL);\
    t=tv.tv_sec;\
struct tm*_tm=localtime(&t);\
    len=strftime(_curtm,sizeof(_curtm),"[%Y/%m/%d %H:%M:%S]",_tm);\
    sprintf(_curtm+len-1," %06ld]",tv.tv_usec);\
    char buf[K];\
    snprintf(buf,sizeof(buf),"%s[%s:%d] %s\n",_curtm,__FILE__,__LINE__,x);\
    fprintf(flog,buf,##__VA_ARGS__);\
}
#endif

#endif
char _curtm[K/8];
#include <cstdio>
#ifdef __linux__
#include <sys/time.h>
#endif
#include <time.h>
FILE *flog=stdout;
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
#define CURTM (__gettm(),_curtm)
#define DEG(x,...) {\
	char buf[K];\
	snprintf(buf,sizeof(buf),"[%s:%d] %s\n",__FILE__,__LINE__,x);\
	fprintf(stdout,buf,##__VA_ARGS__);\
	}
#define XDEG(x,...) {\
	char buf[K];\
	snprintf(buf,sizeof(buf),"%s[%s:%d] %s\n",CURTM,__FILE__,__LINE__,x);\
	fprintf(flog,buf,##__VA_ARGS__);\
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
	void pre_destory_pretree(pre_tree *); \
	int8_t g711_alaw_encode_sample(int16_t); \
	int16_t g711_alaw_decode_sample(int8_t); \
	int g711_alaw_encode(const int16_t *,int,int8_t *,int*); \
	int g711_alaw_decode(const int8_t *,int,int16_t *,int*);

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
#include <vector>
#include <set>
#include <climits>
#include <pthread.h>

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
	template<typename KEY,typename VALUE,typename CONTAINER=std::vector<KEY> >
	class PreTree
	{
		struct leaf
		{
			VALUE val;
			KEY key;
			leaf *parent;
			std::set<leaf> leafs;
			bool is_have_val;
			leaf():parent(NULL),is_have_val(false){}
			bool operator==(const KEY& _key) const
			{
				return key==_key;
			}
			bool operator<(const leaf &lr) const
			{
				return key<lr.key;
			}
		};
		leaf root;// root不能有其它字段，只能有叶子结点
	public:
		bool add(CONTAINER const &key,const VALUE &val,bool _force=false)
		{
			typename CONTAINER::const_iterator iter;
			leaf* cur=&root;
			for(iter=key.begin();
				iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
				{
					leaf tmp;
					tmp.key=*iter;
					if(key.end()==iter+1)
					{
						tmp.val=val;
						tmp.is_have_val = true;
						tmp.parent=cur;
					}
					cur = (leaf*)&(*cur->leafs.insert(tmp).first);
				}
				else
				{
					if(key.end()==iter+1)
					{
						if(!liter->is_have_val || (liter->is_have_val&& _force))
						{
							leaf *pleaf=(leaf *)&(*liter);// 风险，set的迭代器默认为const类型，怕破坏掉元素内部排序
							pleaf->val=val;
							pleaf->is_have_val=true;
							return true;
						}
						return false;
					}
					cur=(leaf*)&(*liter);
				}
			}
			return true;
		}
		
		bool match(const CONTAINER &key,VALUE &val,CONTAINER *pre=NULL) const 
		{
			typename CONTAINER::const_iterator iter;
			const VALUE *ret=NULL;
			const leaf* cur=&root;
			iter=key.begin();
			if(pre)
				pre->clear();
			for(;iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
					break;
				else
				{
					if(liter->is_have_val)
						ret=&liter->val;
					cur=(const leaf*)&(*liter);
				}
			}
			if(ret)
			{
				val=*ret;
				if(pre)
					pre->assign(key.begin(),iter);
			}
			
			return ret;
		}
		bool del(const CONTAINER &key)
		{
			typename CONTAINER::const_iterator iter;
			leaf *ret=NULL;
			const leaf* cur=&root;
			iter=key.begin();
			for(;iter!=key.end();iter++)
			{
				typename std::set<leaf>::iterator liter= find(cur->leafs.begin(),cur->leafs.end(),*iter);
				if(cur->leafs.end()==liter)
					break;
				else
				{
					if(liter->is_have_val&&key.end()==iter+1)
						ret=(leaf *)&(*liter);
					cur=(const leaf*)&(*liter);
				}
			}
			if(ret)
			{
				ret->is_have_val=false;
				while(ret->parent
					&&ret->leafs.empty()
					&&!ret->is_have_val)
				{
					typeof(ret) parent = ret->parent;
					parent->leafs.erase(*ret);
					ret=parent;
				}
				return true;
			}
			return false;
		}
	};
	
	template<typename VALUE>
	class PreTree<std::string,VALUE>
	{
		typedef std::basic_string<char> CONTAINER;
		typedef std::string key_type;
		PreTree< char,VALUE,CONTAINER > data;
		public:
		bool add(const key_type &key,const VALUE &val)
		{return data.add(key,val);}
		bool match(const CONTAINER &key,VALUE &val,CONTAINER *pre=NULL)
		{return data.match(key,val,pre);}
		bool del(const key_type & key)
		{return data.del(key);}
	};
	class thread_guard
	{
		pthread_mutex_t &mutex;
		public:
			thread_guard(pthread_mutex_t &_m):mutex(_m){pthread_mutex_lock(&mutex);}
			~thread_guard(){pthread_mutex_unlock(&mutex);}
	};
	template<typename T,size_t N=UINT_MAX>
	class security_list
	{
		pthread_mutex_t mutex;
		std::list<T> data;
		
		public:
			security_list(){pthread_mutex_init(&mutex,NULL);}
			~security_list(){pthread_mutex_destroy(&mutex);}
			bool push(const T& e)
			{
				try
				{
					thread_guard mt_guard(mutex);
					if(data.size()>=N)
						throw N;
					data.push_back(e);
					return true;
				}
				catch(...)
				{
					return false;
				}
			}
			bool pop(T&e)
			{
				thread_guard mt_guard(mutex);
				if(data.empty())
					return false;
				e=data.front();
				data.pop_front();
				return true;
			}
			int size() const
			{return data.size();}
	};
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
