/*
*
*xyd 2016-1-9
*
*/
#ifndef FOOL_H
#define FOOL_H
#define QRCODE_MAX_LEN 1024
#define MACRO_COMB(x,y) x#y
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
	bool check_date(const char *datetime); /*eg:20160201*/

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

}
namespace fool
{
	COM_INTERFACES;
	int scan_image(const char *fn,std::list<std::string> &ret);
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
