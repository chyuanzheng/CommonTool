/*
 * bmplib.h : header for bmplib(simple bmp reading library)
 *
 * Copyright(C) 2002 holelee
 *
 */

#include "TCCXXX_BMPTYPES.h"
#include "TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_PNG.h"

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELD 3
#define ERROR_MARKER  -4
#define ROW_EXCHANGE_ERROR -100

extern unsigned int	Output_Format;


struct bmphandle_s;

typedef struct bmphandle_s *bmphandle_t;

struct palette_s
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char filter;
};

#define BUF_SIZE 2560				//1024*1024*2

struct bmphandle_s
{
	/* bmp header contents */
	int filesize;
	int reserved;
	int dataoffset;
	int headersize;
	int width;
	int height;
	int nplanes;		//short nplanes;
	int bpp; 			//short bpp;
	int compression;
	int bitmapsize;
	int hres;
	int vres;
	int ncolors;
	int importantcolors;

	/* palette, pixel data, getpixel function pointer */
	int npalette;
	int bytes_per_line;
	struct palette_s *palette;
	unsigned char *data;
	struct bgrpixel (*getpixel)(bmphandle_t, int, int);
	unsigned int bsize_blue, bsize_green, bsize_red;
	unsigned int boffset_blue, boffset_green, boffset_red;
};



typedef struct {
	uint32	(*read_func)	(void *ptr, uint32 size, uint32 nmemb, void *datasource);
} BMP_CALLBACKS_INIT;

#ifndef SIMAGE_CALLBACKS
typedef struct {
	uint32	(*read_func)	(void *ptr, uint32 size, uint32 nmemb, void *datasource);
} SIMAGE_CALLBACKS;
#endif

typedef struct {
	uint32	(*seek_func)	(void *stream,   long offset,   int origin);
	void	(*write_func)	(PNG_IM_PIX_INFO out_info);
} BMP_CALLBACKS_DECODE;

typedef struct tagGDI
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}GDBUF;

struct bgrpixel
{
	unsigned char b, g, r;
};

/* functions definitions */
extern "C"
{

bmphandle_t TCCXXX_BMP_Init(void *filename, BMP_CALLBACKS_INIT BMP_callbacks_init,  int LCD_height, int LCD_width);

int  TCCXXX_BMP_Decode( BMP_CALLBACKS_DECODE BMP_callbacks_decode, unsigned int *BMP_FILE_BUF);

int rle4decode(BMP_CALLBACKS_DECODE BMP_callbacks_decode);

int rle8decode(BMP_CALLBACKS_DECODE BMP_callbacks_decode);

struct bgrpixel bmp_getpixel(bmphandle_t bh, int x, int y);
}