/*
*
*xyd 2016-1-9
*
*/
#ifndef FOOL_H
#define FOOL_H
#ifdef __cplusplus
#include <iostream>
namespace fool
{
	template<typename T>
	void p(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<*iter<<"\n";
	}

	template<typename T>
	void pm(const T &c)
	{
		for(typename T::const_iterator iter=c.begin();iter!=c.end();iter++) 
			std::cout<<iter->first<<" <> "<<iter->second<<"\n";
	}

}
namespace fool
{
	bool is_exist(const char *filepath);
	bool is_regfile(const char *filename);
	bool is_dir(const char *filename);
	const char *get_filename(const char *filepath);
	bool cp(const char *src,const char *dest);
	bool mv(const char *src,const char *dest);
	bool check_suffix(const char *fn,const char *suffix);

}

#else
#include <stdbool.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

bool is_exist(const char *filepath);
bool is_regfile(const char *filename);
bool is_dir(const char *filename);
const char *get_filename(const char *filepath);
bool cp(const char *src,const char *dest);
bool mv(const char *src,const char *dest);
bool check_suffix(const char *fn,const char *suffix);
#ifdef __cplusplus
}
#endif
#endif
