#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_
#include <stdint.h>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#define K 1024

#define DEG(x,...) {\
	char buf[3*K];\
	char timebuf[K/10];\
	int len =snprintf(buf,sizeof(buf)-1,"[%s:%d]",__FILE__,__LINE__);\
	len +=snprintf(buf+len,sizeof(buf)-len-2,x,##__VA_ARGS__);\
	buf[len++]='\n';\
	fwrite(buf,len,1,stdout);\
	}

//#define DEG(x,...) 
const uint64_t  un64_max=~uint64_t(0);
const uint32_t  un32_max=~uint32_t(0);
const uint16_t  un16_max=~uint16_t(0);
const uint8_t  un8_max=~uint8_t(0);
const char idx0[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,
				   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,
				   5,5,6,6,7};
const char idx1[]={128,64,32,16,8,4,2,1};

template<class T,size_t  N=8>
class mem_pool
{
	unsigned char *bit_map;
	std::vector<T*> datas;
	//boost::mutex _lock;
	int64_t used,allocated;
	

public:
	mem_pool():bit_map(NULL),used(0),allocated(0){}
	~mem_pool()
	{
		for(int64_t i=0;i<allocated;i++)
		{
			if(is_used(i))
			{
				(datas[i/N]+(i%N))->~T();
				setnouse(i);
			}
		}
		typename std::vector<T*>::const_iterator iter;
		for(iter=datas.begin();iter!=datas.end();iter++)
		{
			free(*iter);
		}
	}
	T *construct()
	{
		int64_t offset=search_nouse_elem();
		if(offset<0)
		{
			T *new_data=(T*)::malloc(sizeof(T)*N);
			if(!new_data)
				return NULL;
			{
				//_lock;
				datas.push_back(new_data);
				int64_t _allocated=allocated;
				allocated+=N;
				bit_map=(unsigned char *)realloc(bit_map,allocated/8);
				memset(bit_map+_allocated/8,0,N/8);
				setuse(used++);
				T *ret=new (new_data) T();
				return ret;
			}
		}
		else
		{
			setuse(offset);
			T* ret=new (datas[offset/N]+(offset%N)) T();
			used++;
			return ret;
		}
	}
	void destroy(T* p)
	{
		int64_t offset=find_elem(p);
		if(offset>-1)
		{
			p->~T();
			setnouse(offset);
			used--;
		}
	}
	
private:
	int64_t find_elem(T* p) 
	{
		int64_t offset=0;
		bool find=false;
		typename std::vector<T*>::const_iterator iter;
		for(iter=datas.begin();iter!=datas.end();iter++)
		{
			if(p>=*iter&&p<*iter+N)
			{
				offset+=p-*iter;
				if(is_used(offset))
					find=true;
				break;
			}
			offset+=N;
		}
		return find? offset : -1;
	}
	bool is_used(int64_t offset)
	{
		if(offset>used)
			return false;
		unsigned char *cur=bit_map+offset/8;
		int idx=offset%8;
		return *cur&idx1[idx];
	}
	int64_t search_nouse_elem() const
	{
		if(!bit_map)
			return -1;
		int64_t offset=0;
		const uint64_t *pos=(const uint64_t *)bit_map;
		const uint64_t *end=(const uint64_t *)(bit_map+allocated/8);
		while(pos<end)
		{
			if(un64_max == *pos)
			{
				offset+=64;
				pos++;
			}
			else
			{
				const uint32_t *pos32=(const uint32_t*)pos;
				if(un32_max==*pos32)
				{
					pos32++;
					offset+=32;
				}
				const uint16_t *pos16=(const uint16_t*)pos32;
				if(un16_max==*pos16)
				{
					pos16++;
					offset+=16;
				}
				const uint8_t *pos8=(const uint8_t *)pos16;
				if(un8_max == *pos8)
				{
					pos8++;
					offset+=8;
				}
				offset+=idx0[*pos8];
				break;
			}
		}
		return allocated > offset ? offset:-1;
	}
	bool setuse(int64_t offset)
	{
		if(offset>allocated)
			return false;
		unsigned char *cur=bit_map+offset/8;
		int idx=offset%8;
		*cur|=idx1[idx];
		DEG("idx [%ld] used",offset);
		return true;
	}
	bool setnouse(int64_t offset)
	{
		if(offset>used)
			return false;
		unsigned char *cur=bit_map+offset/8;
		int idx=offset%8;
		*cur&=~idx1[idx];
		DEG("idx [%ld] free cur [%d]",offset,*cur);
		return true;
	}
};
#endif