#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <getopt.h>

#include "fool.h"
#include "qrencode.h"

#define INCHES_PER_METER (100.0/2.54)

enum imageType {
	PNG_TYPE,
	EPS_TYPE,
	SVG_TYPE,
	ANSI_TYPE,
	ANSI256_TYPE,
	ASCII_TYPE,
	ASCIIi_TYPE,
	UTF8_TYPE,
	ANSIUTF8_TYPE
};

struct ImageParam
{
	int casesensitive;
	int eightbit;
	int version;
	int size;
	int margin;
	int dpi;
	int structured;
	int rle;
	int micro;
	QRecLevel level;
	QRencodeMode hint;
	unsigned int fg_color[4];
	unsigned int bg_color[4];
	enum imageType image_type;
};

void InitImageParam(struct ImageParam *imageParam)
{
	imageParam->casesensitive = 1;
	imageParam->eightbit = 0;
	imageParam->version = 0;
	imageParam->size = 3;
	imageParam->margin = 4;
	imageParam->dpi = 72;
	imageParam->structured = 0;
	imageParam->rle = 0;
	imageParam->micro = 0;
	imageParam->level = QR_ECLEVEL_L;
	imageParam->hint = QR_MODE_8;
	unsigned int* p=  imageParam->fg_color;//{0, 0, 0, 255};
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 255;
	p = imageParam->bg_color; // = {255, 255, 255, 255};
	*p++ = 255;
	*p++ = 255;
	*p++ = 255;
	*p++ = 255;
	imageParam->image_type = PNG_TYPE;
};
#if 0
static int color_set(unsigned int color[4], const char *value)
{
	int len = strlen(value);
	int count;
	if(len == 6) {
		count = sscanf(value, "%02x%02x%02x%n", &color[0], &color[1], &color[2], &len);
		if(count < 3 || len != 6) {
			return -1;
		}
		color[3] = 255;
	} else if(len == 8) {
		count = sscanf(value, "%02x%02x%02x%02x%n", &color[0], &color[1], &color[2], &color[3], &len);
		if(count < 4 || len != 8) {
			return -1;
		}
	} else {
		return -1;
	}
	return 0;
}
#endif
#define MAX_DATA_SIZE (7090 * 16) /* from the specification */
#if 0
static unsigned char *readStdin(int *length)
{
	unsigned char *buffer;
	int ret;

	buffer = (unsigned char *)malloc(MAX_DATA_SIZE + 1);
	if(buffer == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	ret = fread(buffer, 1, MAX_DATA_SIZE, stdin);
	if(ret == 0) {
		fprintf(stderr, "No input data.\n");
		exit(EXIT_FAILURE);
	}
	if(feof(stdin) == 0) {
		fprintf(stderr, "Input data is too large.\n");
		exit(EXIT_FAILURE);
	}

	buffer[ret] = '\0';
	*length = ret;

	return buffer;
}

static FILE *openFile(const char *outfile)
{
	FILE *fp;

	if(outfile == NULL || (outfile[0] == '-' && outfile[1] == '\0')) {
		fp = stdout;
	} else {
		fp = fopen(outfile, "wb");
		if(fp == NULL) {
			fprintf(stderr, "Failed to create file: %s\n", outfile);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}

	return fp;
}
#endif

static int writePNG(QRcode *qrcode, const char *outfile,struct ImageParam *param)
{
	static FILE *fp; // avoid clobbering by setjmp.
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette;
	png_byte alpha_values[2];
	unsigned char *row, *p, *q;
	int x, y, xx, yy, bit;
	int realwidth;
	unsigned int *fg_color = param->fg_color;
	unsigned int *bg_color = param->bg_color;
	int margin = param->margin;
	int size = param->size;
	int dpi = param->dpi;

	realwidth = (qrcode->width + margin * 2) * size;
	row = (unsigned char *)malloc((realwidth + 7) / 8);
	if(row == NULL) {
		return -EN_ENCODE_QR_ERR_MALLOC;
	}

	if(outfile[0] == '-' && outfile[1] == '\0') {
		fp = stdout;
	} else {
		fp = fopen(outfile, "wb");
		if(fp == NULL) {
			fprintf(stderr, "Failed to create file: %s\n", outfile);
			perror(NULL);
			free(row);
			return -EN_ENCODE_QR_ERR_OPENFILE;
		}
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG writer.\n");
		exit(EXIT_FAILURE);
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG write.\n");
		exit(EXIT_FAILURE);
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fprintf(stderr, "Failed to write PNG image.\n");
		exit(EXIT_FAILURE);
	}

	palette = (png_colorp) malloc(sizeof(png_color) * 2);
	if(palette == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	palette[0].red   = fg_color[0];
	palette[0].green = fg_color[1];
	palette[0].blue  = fg_color[2];
	palette[1].red   = bg_color[0];
	palette[1].green = bg_color[1];
	palette[1].blue  = bg_color[2];
	alpha_values[0] = fg_color[3];
	alpha_values[1] = bg_color[3];
	png_set_PLTE(png_ptr, info_ptr, palette, 2);
	png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr,
			realwidth, realwidth,
			1,
			PNG_COLOR_TYPE_PALETTE,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);
	png_set_pHYs(png_ptr, info_ptr,
			dpi * INCHES_PER_METER,
			dpi * INCHES_PER_METER,
			PNG_RESOLUTION_METER);
	png_write_info(png_ptr, info_ptr);

	/* top margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * size; y++) {
		png_write_row(png_ptr, row);
	}

	/* data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		bit = 7;
		memset(row, 0xff, (realwidth + 7) / 8);
		q = row;
		q += margin * size / 8;
		bit = 7 - (margin * size % 8);
		for(x=0; x<qrcode->width; x++) {
			for(xx=0; xx<size; xx++) {
				*q ^= (*p & 1) << bit;
				bit--;
				if(bit < 0) {
					q++;
					bit = 7;
				}
			}
			p++;
		}
		for(yy=0; yy<size; yy++) {
			png_write_row(png_ptr, row);
		}
	}
	/* bottom margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * size; y++) {
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(fp);
	free(row);
	free(palette);

	return 0;
}
#if 0
static int writeEPS(QRcode *qrcode, const char *outfile)
{
	FILE *fp;
	unsigned char *row, *p;
	int x, y, yy;
	int realwidth;

	fp = openFile(outfile);
   
	realwidth = (qrcode->width + margin * 2) * size;
	/* EPS file header */
	fprintf(fp, "%%!PS-Adobe-2.0 EPSF-1.2\n"
				"%%%%BoundingBox: 0 0 %d %d\n"
				"%%%%Pages: 1 1\n"
				"%%%%EndComments\n", realwidth, realwidth);
	/* draw point */
	fprintf(fp, "/p { "
				"moveto "
				"0 1 rlineto "
				"1 0 rlineto "
				"0 -1 rlineto "
				"fill "
				"} bind def "
				"%d %d scale ", size, size);
	
	/* data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		row = (p+(y*qrcode->width));
		yy = (margin + qrcode->width - y - 1);
		
		for(x=0; x<qrcode->width; x++) {
			if(*(row+x)&0x1) {
				fprintf(fp, "%d %d p ", margin + x,  yy);
			}
		}
	}

	fprintf(fp, "\n%%%%EOF\n");
	fclose(fp);

	return 0;
}

static void writeSVG_writeRect(FILE *fp, int x, int y, int width, char* col, float opacity)
{
	if(fg_color[3] != 255) {
		fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
				"fill=\"#%s\" fill-opacity=\"%f\" />\n", 
				x, y, width, col, opacity );
	} else {
		fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
				"fill=\"#%s\" />\n", 
				x, y, width, col );
	}
}

static int writeSVG( QRcode *qrcode, const char *outfile )
{
	FILE *fp;
	unsigned char *row, *p;
	int x, y, x0, pen;
	int symwidth, realwidth;
	float scale;
	char fg[7], bg[7];
	float fg_opacity;
	float bg_opacity;

	fp = openFile(outfile);

	scale = dpi * INCHES_PER_METER / 100.0;

	symwidth = qrcode->width + margin * 2;
	realwidth = symwidth * size;

	snprintf(fg, 7, "%02x%02x%02x", fg_color[0], fg_color[1],  fg_color[2]);
	snprintf(bg, 7, "%02x%02x%02x", bg_color[0], bg_color[1],  bg_color[2]);
	fg_opacity = (float)fg_color[3] / 255;
	bg_opacity = (float)bg_color[3] / 255;

	/* XML declaration */
	fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n", fp );

	/* DTD 
	   No document type specified because "while a DTD is provided in [the SVG] 
	   specification, the use of DTDs for validating XML documents is known to be 
	   problematic. In particular, DTDs do not handle namespaces gracefully. It 
	   is *not* recommended that a DOCTYPE declaration be included in SVG 
	   documents." 
	   http://www.w3.org/TR/2003/REC-SVG11-20030114/intro.html#Namespace
	*/

	/* Vanity remark */
	fprintf( fp, "<!-- Created with qrencode %s (http://fukuchi.org/works/qrencode/index.html.en) -->\n", 
			QRcode_APIVersionString() );

	/* SVG code start */
	fprintf( fp, "<svg width=\"%0.2fcm\" height=\"%0.2fcm\" viewBox=\"0 0 %d %d\""\
			" preserveAspectRatio=\"none\" version=\"1.1\""\
			" xmlns=\"http://www.w3.org/2000/svg\">\n", 
			realwidth / scale, realwidth / scale, symwidth, symwidth
		   );

	/* Make named group */
	fputs( "\t<g id=\"QRcode\">\n", fp );

	/* Make solid background */
	if(bg_color[3] != 255) {
		fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" fill-opacity=\"%f\" />\n", symwidth, symwidth, bg, bg_opacity);
	} else {
		fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" />\n", symwidth, symwidth, bg);
	}

	/* Create new viewbox for QR data */
	fputs( "\t\t<g id=\"Pattern\">\n", fp);

	/* Write data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		row = (p+(y*qrcode->width));

		if( !rle ) {
			/* no RLE */
			for(x=0; x<qrcode->width; x++) {
				if(*(row+x)&0x1) {
					writeSVG_writeRect(fp,	margin + x,
								margin + y, 1,
								fg, fg_opacity);
				}
			}
		} else {
			/* simple RLE */
			pen = 0;
			x0  = 0;
			for(x=0; x<qrcode->width; x++) {
				if( !pen ) {
					pen = *(row+x)&0x1;
					x0 = x;
				} else {
					if(!(*(row+x)&0x1)) {
						writeSVG_writeRect(fp, x0 + margin, y + margin, x-x0, fg, fg_opacity);
						pen = 0;
					}
				}
			}
			if( pen ) {
				writeSVG_writeRect(fp, x0 + margin, y + margin, qrcode->width - x0, fg, fg_opacity);
			}
		}
	}
	/* Close QR data viewbox */
	fputs( "\t\t</g>\n", fp );

	/* Close group */
	fputs( "\t</g>\n", fp );

	/* Close SVG code */
	fputs( "</svg>\n", fp );
	fclose( fp );

	return 0;
}

static void writeANSI_margin(FILE* fp, int realwidth,
                             char* buffer, int buffer_s,
                             char* white, int white_s )
{
	int y;

	strncpy(buffer, white, white_s);
	memset(buffer + white_s, ' ', realwidth * 2);
	strcpy(buffer + white_s + realwidth * 2, "\033[0m\n"); // reset to default colors
	for(y=0; y<margin; y++ ){
		fputs(buffer, fp);
	}
}

static int writeANSI(QRcode *qrcode, const char *outfile)
{
	FILE *fp;
	unsigned char *row, *p;
	int x, y;
	int realwidth;
	int last;

	char *white, *black, *buffer;
	int white_s, black_s, buffer_s;

	if( image_type == ANSI256_TYPE ){
		/* codes for 256 color compatible terminals */
		white = "\033[48;5;231m";
		white_s = 11;
		black = "\033[48;5;16m";
		black_s = 10;
	} else {
		white = "\033[47m";
		white_s = 5;
		black = "\033[40m";
		black_s = 5;
	}

	size = 1;

	fp = openFile(outfile);

	realwidth = (qrcode->width + margin * 2) * size;
	buffer_s = ( realwidth * white_s ) * 2;
	buffer = (char *)malloc( buffer_s );
	if(buffer == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	/* top margin */
	writeANSI_margin(fp, realwidth, buffer, buffer_s, white, white_s);

	/* data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		row = (p+(y*qrcode->width));

		bzero( buffer, buffer_s );
		strncpy( buffer, white, white_s );
		for(x=0; x<margin; x++ ){
			strncat( buffer, "  ", 2 );
		}
		last = 0;

		for(x=0; x<qrcode->width; x++) {
			if(*(row+x)&0x1) {
				if( last != 1 ){
					strncat( buffer, black, black_s );
					last = 1;
				}
			} else {
				if( last != 0 ){
					strncat( buffer, white, white_s );
					last = 0;
				}
			}
			strncat( buffer, "  ", 2 );
		}

		if( last != 0 ){
			strncat( buffer, white, white_s );
		}
		for(x=0; x<margin; x++ ){
			strncat( buffer, "  ", 2 );
		}
		strncat( buffer, "\033[0m\n", 5 );
		fputs( buffer, fp );
	}

	/* bottom margin */
	writeANSI_margin(fp, realwidth, buffer, buffer_s, white, white_s);

	fclose(fp);
	free(buffer);

	return 0;
}

static void writeUTF8_margin(FILE* fp, int realwidth,
			     const char* white, const char *reset,
			     int use_ansi)
{
	int x, y;

	for (y = 0; y < margin/2; y++) {
		fputs(white, fp);
		for (x = 0; x < realwidth; x++)
			fputs("\342\226\210", fp);
		fputs(reset, fp);
		fputc('\n', fp);
	}
}

static int writeUTF8(QRcode *qrcode, const char *outfile, int use_ansi)
{
	FILE *fp;
	int x, y;
	int realwidth;
	const char *white, *reset;

	if (use_ansi){
		white = "\033[40;37;1m";
		reset = "\033[0m";
	} else {
		white = "";
		reset = "";
	}

	fp = openFile(outfile);

	realwidth = (qrcode->width + margin * 2);

	/* top margin */
	writeUTF8_margin(fp, realwidth, white, reset, use_ansi);

	/* data */
	for(y = 0; y < qrcode->width; y += 2) {
		unsigned char *row1, *row2;
		row1 = qrcode->data + y*qrcode->width;
		row2 = row1 + qrcode->width;

		fputs(white, fp);

		for (x = 0; x < margin; x++)
			fputs("\342\226\210", fp);

		for (x = 0; x < qrcode->width; x++) {
			if(row1[x] & 1) {
				if(y < qrcode->width - 1 && row2[x] & 1) {
					fputc(' ', fp);
				} else {
					fputs("\342\226\204", fp);
				}
			} else {
				if(y < qrcode->width - 1 && row2[x] & 1) {
					fputs("\342\226\200", fp);
				} else {
					fputs("\342\226\210", fp);
				}
			}
		}

		for (x = 0; x < margin; x++)
			fputs("\342\226\210", fp);

		fputs(reset, fp);
		fputc('\n', fp);
	}

	/* bottom margin */
	writeUTF8_margin(fp, realwidth, white, reset, use_ansi);

	fclose(fp);

	return 0;
}

static void writeASCII_margin(FILE* fp, int realwidth, char* buffer, int buffer_s, int invert)
{
	int y, h;

	h = margin;

	memset(buffer, (invert?'#':' '), realwidth);
	buffer[realwidth] = '\n';
	buffer[realwidth + 1] = '\0';
	for(y=0; y<h; y++ ){
		fputs(buffer, fp);
	}
}

static int writeASCII(QRcode *qrcode, const char *outfile, int invert)
{
	FILE *fp;
	unsigned char *row;
	int x, y;
	int realwidth;
	char *buffer, *p;
	int buffer_s;
	char black = '#';
	char white = ' ';

	if(invert) {
		black = ' ';
		white = '#';
	}

	size = 1;

	fp = openFile(outfile);

	realwidth = (qrcode->width + margin * 2) * 2;
	buffer_s = realwidth + 2;
	buffer = (char *)malloc( buffer_s );
	if(buffer == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	/* top margin */
	writeASCII_margin(fp, realwidth, buffer, buffer_s, invert);

	/* data */
	for(y=0; y<qrcode->width; y++) {
		row = qrcode->data+(y*qrcode->width);
		p = buffer;

		memset(p, white, margin * 2);
		p += margin * 2;

		for(x=0; x<qrcode->width; x++) {
			if(row[x]&0x1) {
				*p++ = black;
				*p++ = black;
			} else {
				*p++ = white;
				*p++ = white;
			}
		}

		memset(p, white, margin * 2);
		p += margin * 2;
		*p++ = '\n';
		*p++ = '\0';
		fputs( buffer, fp );
	}

	/* bottom margin */
	writeASCII_margin(fp, realwidth, buffer, buffer_s, invert);

	fclose(fp);
	free(buffer);

	return 0;
}

static QRcode *encode(const unsigned char *intext, int length)
{
	QRcode *code;

	if(micro) {
		if(eightbit) {
			code = QRcode_encodeDataMQR(length, intext, version, level);
		} else {
			code = QRcode_encodeStringMQR((char *)intext, version, level, hint, casesensitive);
		}
	} else {
		if(eightbit) {
			code = QRcode_encodeData(length, intext, version, level);
		} else {
			code = QRcode_encodeString((char *)intext, version, level, hint, casesensitive);
		}
	}

	return code;
}

static void qrencode(const unsigned char *intext, int length, const char *outfile)
{
	QRcode *qrcode;
	
	qrcode = encode(intext, length);
	if(qrcode == NULL) {
		perror("Failed to encode the input data");
		exit(EXIT_FAILURE);
	}
	switch(image_type) {
		case PNG_TYPE:
			writePNG(qrcode, outfile);
			break;
		case EPS_TYPE:
			writeEPS(qrcode, outfile);
			break;
		case SVG_TYPE:
			writeSVG(qrcode, outfile);
			break;
		case ANSI_TYPE:
		case ANSI256_TYPE:
			writeANSI(qrcode, outfile);
			break;
		case ASCIIi_TYPE:
			writeASCII(qrcode, outfile,  1);
			break;
		case ASCII_TYPE:
			writeASCII(qrcode, outfile,  0);
			break;
		case UTF8_TYPE:
			writeUTF8(qrcode, outfile, 0);
			break;
		case ANSIUTF8_TYPE:
			writeUTF8(qrcode, outfile, 1);
			break;
		default:
			fprintf(stderr, "Unknown image type.\n");
			exit(EXIT_FAILURE);
	}
	QRcode_free(qrcode);
}

static QRcode_List *encodeStructured(const unsigned char *intext, int length)
{
	QRcode_List *list;

	if(eightbit) {
		list = QRcode_encodeDataStructured(length, intext, version, level);
	} else {
		list = QRcode_encodeStringStructured((char *)intext, version, level, hint, casesensitive);
	}

	return list;
}

static void qrencodeStructured(const unsigned char *intext, int length, const char *outfile)
{
	QRcode_List *qrlist, *p;
	char filename[FILENAME_MAX];
	char *base, *q, *suffix = NULL;
	const char *type_suffix;
	int i = 1;
	size_t suffix_size;

	switch(image_type) {
		case PNG_TYPE:
			type_suffix = ".png";
			break;
		case EPS_TYPE:
			type_suffix = ".eps";
			break;
		case SVG_TYPE:
			type_suffix = ".svg";
			break;
		case ANSI_TYPE:
		case ANSI256_TYPE:
		case ASCII_TYPE:
		case UTF8_TYPE:
		case ANSIUTF8_TYPE:
			type_suffix = ".txt";
			break;
		default:
			fprintf(stderr, "Unknown image type.\n");
			exit(EXIT_FAILURE);
	}

	if(outfile == NULL) {
		fprintf(stderr, "An output filename must be specified to store the structured images.\n");
		exit(EXIT_FAILURE);
	}
	base = strdup(outfile);
	if(base == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	suffix_size = strlen(type_suffix);
	if(strlen(base) > suffix_size) {
		q = base + strlen(base) - suffix_size;
		if(strcasecmp(type_suffix, q) == 0) {
			suffix = strdup(q);
			*q = '\0';
		}
	}
	
	qrlist = encodeStructured(intext, length);
	if(qrlist == NULL) {
		perror("Failed to encode the input data");
		exit(EXIT_FAILURE);
	}

	for(p = qrlist; p != NULL; p = p->next) {
		if(p->code == NULL) {
			fprintf(stderr, "Failed to encode the input data.\n");
			exit(EXIT_FAILURE);
		}
		if(suffix) {
			snprintf(filename, FILENAME_MAX, "%s-%02d%s", base, i, suffix);
		} else {
			snprintf(filename, FILENAME_MAX, "%s-%02d", base, i);
		}
		switch(image_type) {
			case PNG_TYPE: 
				writePNG(p->code, filename);
				break;
			case EPS_TYPE: 
				writeEPS(p->code, filename);
				break;
			case SVG_TYPE: 
				writeSVG(p->code, filename);
				break;
			case ANSI_TYPE:
			case ANSI256_TYPE:
				writeANSI(p->code, filename);
				break;
			case ASCIIi_TYPE:
				writeASCII(p->code, filename, 1);
				break;
			case ASCII_TYPE:
				writeASCII(p->code, filename, 0);
				break;
			case UTF8_TYPE:
				writeUTF8(p->code, filename, 0);
				break;
			case ANSIUTF8_TYPE:
				writeUTF8(p->code, filename, 0);
				break;

			default:
				fprintf(stderr, "Unknown image type.\n");
				exit(EXIT_FAILURE);
		}
		i++;
	}

	free(base);
	if(suffix) {
		free(suffix);
	}

	QRcode_List_free(qrlist);
}

int main(int argc, char **argv)
{
	int opt, lindex = -1;
	char *outfile = NULL;
	unsigned char *intext = NULL;
	int length = 0;

	while((opt = getopt_long(argc, argv, optstring, options, &lindex)) != -1) {
		switch(opt) {
			case 'h':
				if(lindex == 0) {
					usage(1, 1);
				} else {
					usage(1, 0);
				}
				exit(EXIT_SUCCESS);
				break;
			case 'o':
				outfile = optarg;
				break;
			case 's':
				size = atoi(optarg);
				if(size <= 0) {
					fprintf(stderr, "Invalid size: %d\n", size);
					exit(EXIT_FAILURE);
				}
				break;
			case 'v':
				version = atoi(optarg);
				if(version < 0) {
					fprintf(stderr, "Invalid version: %d\n", version);
					exit(EXIT_FAILURE);
				}
				break;
			case 'l':
				switch(*optarg) {
					case 'l':
					case 'L':
						level = QR_ECLEVEL_L;
						break;
					case 'm':
					case 'M':
						level = QR_ECLEVEL_M;
						break;
					case 'q':
					case 'Q':
						level = QR_ECLEVEL_Q;
						break;
					case 'h':
					case 'H':
						level = QR_ECLEVEL_H;
						break;
					default:
						fprintf(stderr, "Invalid level: %s\n", optarg);
						exit(EXIT_FAILURE);
						break;
				}
				break;
			case 'm':
				margin = atoi(optarg);
				if(margin < 0) {
					fprintf(stderr, "Invalid margin: %d\n", margin);
					exit(EXIT_FAILURE);
				}
				break;
			case 'd':
				dpi = atoi(optarg);
				if( dpi < 0 ) {
					fprintf(stderr, "Invalid DPI: %d\n", dpi);
					exit(EXIT_FAILURE);
				}
				break;
			case 't':
				if(strcasecmp(optarg, "png") == 0) {
					image_type = PNG_TYPE;
				} else if(strcasecmp(optarg, "eps") == 0) {
					image_type = EPS_TYPE;
				} else if(strcasecmp(optarg, "svg") == 0) {
					image_type = SVG_TYPE;
				} else if(strcasecmp(optarg, "ansi") == 0) {
					image_type = ANSI_TYPE;
				} else if(strcasecmp(optarg, "ansi256") == 0) {
					image_type = ANSI256_TYPE;
				} else if(strcasecmp(optarg, "asciii") == 0) {
					image_type = ASCIIi_TYPE;
				} else if(strcasecmp(optarg, "ascii") == 0) {
					image_type = ASCII_TYPE;
				} else if(strcasecmp(optarg, "utf8") == 0) {
					image_type = UTF8_TYPE;
				} else if(strcasecmp(optarg, "ansiutf8") == 0) {
					image_type = ANSIUTF8_TYPE;
				} else {
					fprintf(stderr, "Invalid image type: %s\n", optarg);
					exit(EXIT_FAILURE);
				}
				break;
			case 'S':
				structured = 1;
				break;
			case 'k':
				hint = QR_MODE_KANJI;
				break;
			case 'c':
				casesensitive = 1;
				break;
			case 'i':
				casesensitive = 0;
				break;
			case '8':
				eightbit = 1;
				break;
			case 'r':
				rle = 1;
				break;
			case 'M':
				micro = 1;
				break;
			case 'f':
				if(color_set(fg_color, optarg)) {
					fprintf(stderr, "Invalid foreground color value.\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'b':
				if(color_set(bg_color, optarg)) {
					fprintf(stderr, "Invalid background color value.\n");
					exit(EXIT_FAILURE);
				}
				break;
			case 'V':
				usage(0, 0);
				exit(EXIT_SUCCESS);
				break;
			case 0:
				break;
			default:
				fprintf(stderr, "Try `qrencode --help' for more information.\n");
				exit(EXIT_FAILURE);
				break;
		}
	}

	if(argc == 1) {
		usage(1, 0);
		exit(EXIT_SUCCESS);
	}

	if(outfile == NULL && image_type == PNG_TYPE) {
		fprintf(stderr, "No output filename is given.\n");
		exit(EXIT_FAILURE);
	}

	if(optind < argc) {
		intext = (unsigned char *)argv[optind];
		length = strlen((char *)intext);
	}
	if(intext == NULL) {
		intext = readStdin(&length);
	}

	if(micro && version > MQRSPEC_VERSION_MAX) {
		fprintf(stderr, "Version should be less or equal to %d.\n", MQRSPEC_VERSION_MAX);
		exit(EXIT_FAILURE);
	} else if(!micro && version > QRSPEC_VERSION_MAX) {
		fprintf(stderr, "Version should be less or equal to %d.\n", QRSPEC_VERSION_MAX);
		exit(EXIT_FAILURE);
	}

	if(margin < 0) {
		if(micro) {
			margin = 2;
		} else {
			margin = 4;
		}
	}

	if(micro) {
		if(version == 0) {
			fprintf(stderr, "Version must be specified to encode a Micro QR Code symbol.\n");
			exit(EXIT_FAILURE);
		}
		if(structured) {
			fprintf(stderr, "Micro QR Code does not support structured symbols.\n");
			exit(EXIT_FAILURE);
		}
	}

	if(structured) {
		if(version == 0) {
			fprintf(stderr, "Version must be specified to encode structured symbols.\n");
			exit(EXIT_FAILURE);
		}
		qrencodeStructured(intext, length, outfile);
	} else {
		qrencode(intext, length, outfile);
	}

	return 0;
}
#endif
static QRcode *encode(const unsigned char *intext, int length,struct ImageParam *param)
{
	QRcode *code;

	if(param->micro) {
		if(param->eightbit) {
			code = QRcode_encodeDataMQR(length, intext, param->version, param->level);
		} else {
			code = QRcode_encodeStringMQR((char *)intext, param->version, param->level, param->hint, param->casesensitive);
		}
	} else {
		if(param->eightbit) {
			code = QRcode_encodeData(length, intext, param->version, param->level);
		} else {
			code = QRcode_encodeString((char *)intext, param->version, param->level, param->hint, param->casesensitive);
		}
	}

	return code;
}

static int qrencode(const unsigned char *intext, int length, const char *outfile)
{
	int ret =0;
	QRcode *qrcode;
	struct ImageParam param;
	if(!intext||length<=0)
		return -EN_ENCODE_QR_ERR_NULL_INFO;
	if(!check_suffix(outfile,"png")&&!check_suffix(outfile,"PNG"))
		return -EN_ENCODE_QR_ERR_FMT;
	InitImageParam(&param);
	qrcode = encode(intext, length,&param);
	if(qrcode == NULL) {
		return -EN_ENCODE_QR_ERR_ENCODE;;
	}
	switch(param.image_type) {
		case PNG_TYPE:
			ret = writePNG(qrcode, outfile,&param);
			break;
			#if 0
		case EPS_TYPE:
			writeEPS(qrcode, outfile);
			break;
		case SVG_TYPE:
			writeSVG(qrcode, outfile);
			break;
		case ANSI_TYPE:
		case ANSI256_TYPE:
			writeANSI(qrcode, outfile);
			break;
		case ASCIIi_TYPE:
			writeASCII(qrcode, outfile,  1);
			break;
		case ASCII_TYPE:
			writeASCII(qrcode, outfile,  0);
			break;
		case UTF8_TYPE:
			writeUTF8(qrcode, outfile, 0);
			break;
		case ANSIUTF8_TYPE:
			writeUTF8(qrcode, outfile, 1);
			break;
			#endif
		default:
			//fprintf(stderr, "Unknown image type.\n");
			ret = -EN_ENCODE_QR_ERR_FMT;
	}
	QRcode_free(qrcode);
	return ret;
}

int qr_image_create(const char * text,const char *fn)
{
	return qrencode(text, strlen(text), fn);
}

const char *qr_image_err(int err_code)
{
	const char *errs[EN_ENCODE_QR_XXX];
	/*
	EN_ENCODE_QR_OK =0,
	EN_ENCODE_QR_ERR_FMT,
	EN_ENCODE_QR_ERR_LONG_INFO,
	EN_ENCODE_QR_ERR_NULL_INFO,
	EN_ENCODE_QR_ERR_ENCODE,
	EN_ENCODE_QR_ERR_OPENFILE,
	EN_ENCODE_QR_ERR_MALLOC,
	EN_ENCODE_QR_XXX
	*/
	errs[EN_ENCODE_QR_OK] = "No occur error.";
	errs[EN_ENCODE_QR_ERR_FMT] = "Error output file format, only support png image.";
	errs[EN_ENCODE_QR_ERR_LONG_INFO] = MACRO_COMB("Ehe encode information is longer than ",QRCODE_MAX_LEN)  " .";
	errs[EN_ENCODE_QR_ERR_NULL_INFO] = "Encode information is NULL";
	errs[EN_ENCODE_QR_ERR_OPENFILE] = "Open file failed.";
	errs[EN_ENCODE_QR_ERR_ENCODE] = "Encode error.";
	errs[EN_ENCODE_QR_ERR_MALLOC] = "Malloc error.";
	if(err_code > 0 ||err_code<=-EN_ENCODE_QR_XXX)
		return "Unkown error.";
	else
		return errs[-err_code];
}

