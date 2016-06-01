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
#include <stdio.h>
#ifdef __linux__
#include <sys/time.h>
#include <unistd.h>
#endif
#include <time.h>
extern FILE *__fool_flog;
#ifdef __cplusplus
extern "C"
{
	char * __gettm(char *_curtm);
}
#else
char * __gettm(char *_curtm);
#endif
#define DEG(x,...) {\
	char buf[3*K];\
	char timebuf[K/10];\
	int len =snprintf(buf,sizeof(buf)-1,"[%s:%d]",__FILE__,__LINE__);\
	len +=snprintf(buf+len,sizeof(buf)-len-2,x,##__VA_ARGS__);\
	buf[len++]='\n';\
	write(fileno(__fool_flog),buf,len);\
	}
#define XDEG(x,...) {\
	char buf[3*K];\
	char timebuf[K/10];\
	int len =snprintf(buf,sizeof(buf)-1,"%s[%s:%d]",__gettm(timebuf),__FILE__,__LINE__);\
	len +=snprintf(buf+len,sizeof(buf)-len-2,x,##__VA_ARGS__);\
	buf[len++]='\n';\
	write(fileno(__fool_flog),buf,len);\
	}
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
#include "fool_internal.hpp"
namespace fool
{
	COM_INTERFACES;
	int scan_image(const char *fn,std::list<std::string> &ret);
	const char *strstr(const char *src,const char *str);
	void replace_str(std::string &str,const char *ostr,const char *nstr);
	// 0 %d%02d%02d%02d%02d%02d
	// 1 %d-%02d-%02d %02d:%02d:%02d
	// 2 %d-%02d-%02d 00:00:00
	// 5 %d%02d%02d%02d0000
	// 6 %d%02d%02d%02d%02d%02d
	// 7 %d%02d%02d
	// 10 %d-%02d-%02d
    std::string time_to_str(time_t i_time,int i_format  = 0);
	//format 1:yyyy-mm-dd hh:mi:ss
    //format 2:yyyy/mm/dd hh:mi:ss
    //format 3:yyyymmddhhmiss
    //format 4:yymmddhhmiss default 20yy
    time_t str_to_time(const char * p_time, int n_format);
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
