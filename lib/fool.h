/*
*
*xyd 2016-1-9
*
*/

#ifndef FOOL_H
#define FOOL_H
namespace fool
{
	bool is_exist(const char *filepath);
	bool is_regfile(const char *filename);
	bool is_dir(const char *filename);
	const char *get_filename(const char *filepath);
	bool cp(const char *src,const char *dest);
}
#endif
