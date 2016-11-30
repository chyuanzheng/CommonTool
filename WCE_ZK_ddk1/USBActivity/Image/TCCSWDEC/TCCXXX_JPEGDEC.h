#ifndef JPEG_DONE_16BIT
#define JPEG_DONE_16BIT

#include "TCCXXX_JPEGTYPES.h"
#include "TCCXXX_JPEGVAL.h"
#ifdef __TCC89XX_WINCE__
#include "TCCXXX_JPEG_CUSTOM_OUTPUT_SET.h"
#else
#include "TCCXXX_IMAGE_CUSTOM_OUTPUT_SET.h"
#endif

#define ENABLE_CUSTOM_OUTPUT

#define JD_SRC_YUV	0
#define JD_SRC_RGB	1
#define JD_SRC_OTHER	2
#define JD_SRC_RGB_888	3

#ifdef __TCC89XX_WINCE__
#define resize_buf_size 1024*4
#else
#define RESIZE_BUF_SIZE(LCD_WIDTH, LCD_HEIGHT)	(MAX(LCD_WIDTH, LCD_HEIGHT) * 8)
#endif

#ifdef __TCC89XX_WINCE__
typedef struct {
	uint16	(*read_func)	(void *ptr, uint32 size, uint32 nmemb, void *datasource);
	void* (*malloc_func)	(unsigned int);
	void  (*free_func)		(void *);
} JD_CALLBACKS;
#else
typedef struct {
	uint16	(*read_func)	(void *ptr, uint32 size, uint32 nmemb, void *datasource);
} JD_CALLBACKS;
#endif

#ifdef __TCC89XX_WINCE__
typedef struct {
	uint32	JD_Color_Space;
	uint8	JD_Block_Freq[6];
	uint32	JD_Calc_Buf_Size;
	uint32	JD_Image_Width;
	uint32	JD_Image_Height;
	uint32	Origin_Size_Decode;
} JD_SRC_FMT;
#else
typedef struct {
	uint32	JD_Color_Space;
	uint8	JD_Block_Freq[6];
	uint32	JD_Calc_Buf_Size;
	uint32	JD_Image_Width;
	uint32	JD_Image_Height;
} JD_SRC_FMT;
#endif

#ifdef __TCC89XX_WINCE__
typedef struct {
	uint8 *	LCD_OUTPUT_BUFFER;
	uint16 *	Calc_Buf;
	void	(*write_func)	(IM_PIX_INFO out_info);
	void	(*write_block_func)	(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt);
} IM_CUSTOM_OUTPUT;
#else
typedef struct {
	uint8 *	LCD_OUTPUT_BUFFER;
	uint16 *	Calc_Buf;
	void	(*write_func)	(IM_PIX_INFO out_info);
} IM_CUSTOM_OUTPUT;
#endif

/* functions definitions */
extern "C"
{
#ifdef __TCC89XX_WINCE__
extern int TCCXXX_JPEGDEC_Init(unsigned int *Handle,
					void *datasource,
					int lcd_width,
					int lcd_height,
					JD_SRC_FMT * image_info,
					JD_CALLBACKS *callbacks);

extern int TCCXXX_JPEGDEC_Init2(unsigned int *Handle,
					void *datasource,
					int lcd_width,
					int lcd_height,
					int ** lcd_resize_buf,
					JD_SRC_FMT * image_info,
					JD_CALLBACKS *callbacks);

extern int TCCXXX_JPEGDEC_Decode(unsigned int *Handle, IM_CUSTOM_OUTPUT custom_output);

extern int TCCXXX_JPEGDEC_Close(uint32 *h_jpeg_dec);
#else
extern int TCCXXX_JPEGDEC_Init(void *datasource,
					int lcd_width,
					int lcd_height,
					JD_SRC_FMT * image_info,
					JD_CALLBACKS callbacks);

extern int TCCXXX_JPEGDEC_Init2(void *datasource,
					int lcd_width,
					int lcd_height,
					int * lcd_resize_buf,
					JD_SRC_FMT * image_info,
					JD_CALLBACKS callbacks);

extern int TCCXXX_JPEGDEC_Decode(IM_CUSTOM_OUTPUT custom_output);
#endif
}
#endif
/* file end */