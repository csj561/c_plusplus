#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <zbar.h>
#include "fool.h"

/* to complete a runnable example, this abbreviated implementation of
	 * get_data() will use libpng to read an image file. refer to libpng
	 * documentation for details
	 */
static int get_data (const char *name,
					  int *width, int *height,
					  void **raw)
{
	FILE *file = fopen(name, "rb");
	if(!file) 
		return -EN_SCAN_ERR_OPEN_IMG;
	png_structp png =
		png_create_read_struct(PNG_LIBPNG_VER_STRING,
							   NULL, NULL, NULL);
	if(!png) return -EN_SCAN_ERR_OPEN_IMG;
	if(setjmp(png_jmpbuf(png))) return -EN_SCAN_ERR_OPEN_IMG;
	png_infop info = png_create_info_struct(png);
	if(!info) 
		return -EN_SCAN_ERR_OPEN_IMG;
	png_init_io(png, file);
	png_read_info(png, info);
	/* configure for 8bpp grayscale input */
	int color = png_get_color_type(png, info);
	int bits = png_get_bit_depth(png, info);
	if(color & PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);
	if(color == PNG_COLOR_TYPE_GRAY && bits < 8)
		png_set_gray_1_2_4_to_8(png);
	if(bits == 16)
		png_set_strip_16(png);
	if(color & PNG_COLOR_MASK_ALPHA)
		png_set_strip_alpha(png);
	if(color & PNG_COLOR_MASK_COLOR)
		png_set_rgb_to_gray_fixed(png, 1, -1, -1);
	/* allocate image */
	*width = png_get_image_width(png, info);
	*height = png_get_image_height(png, info);
	*raw = malloc(*width * *height);
	png_bytep rows[*height];
	int i;
	for(i = 0; i < *height; i++)
		rows[i] = *raw + (*width * i);
	png_read_image(png, rows);
	return 0;
}
int scan_image(const char *fn,char *buf,int bufsz)
{
	memset(buf,0,bufsz);
	int len = 0;
	int cnt = 0;
	int result = 0;
	zbar_image_scanner_t *scanner = NULL;
	/* create a reader */
    scanner = zbar_image_scanner_create();

    /* configure the reader */
    zbar_image_scanner_set_config(scanner, 0, ZBAR_CFG_ENABLE, 1);

    /* obtain image data */
    int width = 0, height = 0;
    void *raw = NULL;
	int i;
	zbar_image_t *image=NULL;

	if(!(check_suffix(fn,"png") 
		||check_suffix(fn,"PNG")))
	{
		result = -EN_SCAN_ERR_FMT;
		goto ret;
	}
    if(get_data(fn, &width, &height, &raw)<0)
    {
		result = -EN_SCAN_ERR_OPEN_IMG;
		goto ret;
    }
	bool is_find = false;

    /* wrap image data */
   image = zbar_image_create();
    zbar_image_set_format(image, *(int*)"Y800");
    zbar_image_set_size(image, width, height);
    zbar_image_set_data(image, raw, width * height, zbar_image_free_data);

    /* scan the image for barcodes */
    int n = zbar_scan_image(scanner, image);

    /* extract results */
    const zbar_symbol_t *symbol = zbar_image_first_symbol(image);
    for(; symbol; symbol = zbar_symbol_next(symbol)) 
	{
		char line[1024];
		cnt ++;
		is_find = true;
        /* do something useful with results */
        zbar_symbol_type_t typ = zbar_symbol_get_type(symbol);
        const char *data = zbar_symbol_get_data(symbol);
		int data_len = strlen(data);
        //len +=sprintf(buf+len,"[%s]decoded %s symbol \"%s\"\n",
        //       argv[i],zbar_get_symbol_name(typ), data);
        if(data_len >= 1024)
        {
        	result = -EN_SCAN_ERR_LONG_INFO;
        	goto ret;
        }
		else if(data_len >= bufsz - len)
		{
			result = -EN_SCAN_ERR_SHORT_BUF;
			goto ret;
		}
		sprintf(buf+len,"%s",data);
		len += data_len + 1;
		result = cnt;
    }
	if(!is_find)
	{
			result = -EN_SCAN_NO_INFO;
	}
	ret:
    /* clean up */
	//if(raw)
	//	free(raw);
	if(image)
    	zbar_image_destroy(image);
	if(scanner)
    	zbar_image_scanner_destroy(scanner);
	return result;
}

const char *scan_err(int err_code)
{
	char *err_str[EN_SCAN_XXX];
	if(err_code>0)
	{
		return "No occur error.";
	}
	if(err_code<-EN_SCAN_XXX)
	{
		return "Unkown error.";
	}
	/*
		EN_SCAN_ERR_FMT,
		EN_SCAN_ERR_SHORT_BUF,
		EN_SCAN_ERR_LONG_INFO,
		EN_SCAN_ERR_OPEN_IMG

	*/
	err_str[EN_SCAN_ERR_FMT] = "error formt image file, only support png image.";
	err_str[EN_SCAN_ERR_SHORT_BUF] = "the out buf is too short to store the decode informations.";
	err_str[EN_SCAN_ERR_LONG_INFO] = "the decode information is longer than 1024";
	err_str[EN_SCAN_ERR_OPEN_IMG] = "open image file error.";
	return err_str[-err_code];
}


