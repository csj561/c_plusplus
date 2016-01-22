/*
*
*xyd 2016-1-9
*
*/
#ifndef FOOL_H
#define FOOL_H

/*C和C++兼容接口*/
#define COM_INTERFACES \
	bool is_exist(const char *filepath); \
	bool is_regfile(const char *filename); \
	bool is_dir(const char *filename); \
	const char *get_filename(const char *filepath); \
	bool cp(const char *src,const char *dest); \
	bool mv(const char *src,const char *dest); \
	bool check_suffix(const char *fn,const char *suffix); \
	int scan_image(const char *fn,char *buf,int bufsz); \
	const char *scan_err(int err_code);

enum EN_SCAN
{
	EN_SCAN_NO_INFO=0,
	EN_SCAN_ERR_FMT,
	EN_SCAN_ERR_SHORT_BUF,
	EN_SCAN_ERR_LONG_INFO,
	EN_SCAN_ERR_OPEN_IMG,
	EN_SCAN_XXX
};
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
	COM_INTERFACES;
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
