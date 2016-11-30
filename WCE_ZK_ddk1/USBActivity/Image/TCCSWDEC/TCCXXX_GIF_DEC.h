#ifndef __TCCXXX_GIF_DEC_H__
#define __TCCXXX_GIF_DEC_H__

#include "TCCXXX_JPEGTYPES.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==========================================================================
	Constant Definitions
==========================================================================*/
#define GIFD_OUT_RGB888		1	// R0 G0 B0 R1 G1 B1 .., (byte unit output)
#define GIFD_OUT_BGR888		2	// B0 G0 R0 B1 G1 R1 .., (byte unit output)
#define GIFD_OUT_RGB888D	3	// R0 G0 B0 D0 R1 G1 B1 D0 .., (byte unit output)
#define GIFD_OUT_BGR888D	4	// B0 G0 R0 D0 B1 G1 R1 D0 .., (byte unit output)
#define GIFD_OUT_RGB32BIT	5	// (MSB) [D0 R0 G0 B0] (LSB), (32bit unit output)
#define GIFD_OUT_RGB565		6	// 16bit unit output


/*==========================================================================
	Type Definitions
==========================================================================*/
#ifndef __GIF_PORT__
#if defined(_WINDOWS) || defined(_WIN32_WCE)
#	include <windows.h>
#else
#	define BYTE		unsigned char
#	define BOOL		signed long
#	define TRUE		1
#	define FALSE	0
#	define NULL		0
#endif
typedef unsigned long		GIFD_HANDLE;
typedef signed long			GIFD_RESULT;
#endif //__GIF_PORT__

typedef struct __tagGIFDPIXRGB
{
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
	unsigned char	reserved;
} GIFD_PIXRGB;


/*==========================================================================
	GIFD_RESULT values
==========================================================================*/
#define ERROR_NOT_ENOUGH_HEAP_MEMORY	-1
#define ERROR_INVALID_COLOR_FORMAT		-2
#define ERROR_GIF_VERSION_NOT_SUPPORTED	-3
#define ERROR_GIF_SIZE_TOO_BIG			-4

#define ERROR_IMAGE_SIZE_TOO_BIG		-10
#define ERROR_INVALID_LZW_CODESIZE		-11
#define ERROR_COLOR_TABLE_NOT_EXIST		-12
#define ERROR_IMAGE_FAILED				-13	// LZW Decoding failed
#define ERROR_DECODE_FAILED				-14

#define RESULT_INIT_SUCCESS				100	// initialization success
#define RESULT_IMAGE_COMPLETE			101	// complete decoding one image
#define RESULT_IMAGE_INCOMPLETE			102	// incomlete decoding one image
#define RESULT_SEQUENCE_COMPLETE		103	// complete one sequence
#define RESULT_DECODE_COMPLETE			110	// complete gif decoding


/*==========================================================================
	TCCXXX_GIFDEC_Init() function input/output param
==========================================================================*/
typedef struct {
	unsigned long	(*read_func)	(void *dst, unsigned long size, unsigned long count, void *iosrc);	//fread
	unsigned long	(*seek_func)	(void *iosrc, long offset, long origin);				//fseek
} GIFD_CALLBACKS;

typedef struct {
	void *				input_src;			// file pointer
	GIFD_CALLBACKS		callback;			// callback functions

	unsigned char		*heap_buff;			// heap buffer
	unsigned long		heap_size;			// beap size

	long				out_width;			// output width
	long				out_height;			// output height
	long				out_format;			// output color format
	int 				out_flip;			// flipped out (for Windows DIB, etc ..)

	/* options for transparent pixels */
	#define	OPT_KEEP_BACKRGOUND				0x000003	// keep contents of the output region (default)
	#define OPT_USE_BACKGROUND_COLOR		0x000005	// use background color in GIF for transparent pixels
	#define OPT_USE_USER_BACKGROUND_COLOR	0x000006	// use user_bgcolor for transparent pixels
	/* options for the output position (0: center)*/
	#define OPT_OUT_TOP						0x000300	// output to the top of the output region
	#define OPT_OUT_BOTTOM					0x000500	// output to the bottom of the output region
	#define OPT_OUT_LEFT					0x030000	// output to the left of the output region
	#define OPT_OUT_RIGHT					0x050000	// output to the right of the output region
	unsigned long		out_option;			// output option (0 : default)
	GIFD_PIXRGB			user_bgcolor;		// user background color (for OPT_USE_USER_BACKGROUND_COLOR option)
} GIFD_INIT;

typedef struct {
	long			width;				// original GIF width
	long			height;				// original GIF height
	long			resized_width;		// resized GIF width for out_width/out_height
	long			resized_height;		// resized GIF height for out_width/out_height
	long			out_xoff;			// output horizontal offset from the out_buffer left
	long			out_yoff;			// output vertical offset from the out_buffer top
	long			pixel_depth;		// number of bits per primary color available to the original image
	GIFD_RESULT		init_result;		// 
} GIFD_INFO;


/*==========================================================================
	TCCXXX_GIFDEC_Decode() function input/output param
==========================================================================*/
typedef struct {
	/* 
		<< output buffer >>
		SIZE : out_width * out_height * bytes_per_pixel
	*/
	unsigned char*	out_buffer;			// set output buffer (video memory / output region / ..)
	long			reserved0;			// .
	long			reserved1;			// .
	long			reserved2;			// .
} GIFD_DECIN;

typedef struct {
	unsigned long	image_number;		// #
	long			image_xoff;			// image x offset from the GIF left
	long			image_yoff;			// image y offset from the GIF top
	long			image_width;		// image width
	long			image_height;		// image height
	unsigned long	delay_time;			// 1/100 sec (*)
	long			user_input;			// use user input (*)
	unsigned long	iteration_max;		// iteration max
	unsigned long	iteration_count;	// iteration count
} GIFD_DECOUT;


/*==========================================================================
	GIF Decoder Main Functions
==========================================================================*/
/* 
	Description: 
		calculate heap size before initialization 
*/
unsigned long							// return	: heap size
TCCXXX_GIFDEC_GetHeapSize (
		long out_width,		// output width (width of the output buffer / video region / ..)
		long out_height,		// output height (height of the output buffer / video region / ..)
		long out_format	// video format (output format. ex> RGB888, RGB565, ..)
		);

/* 
	Description: 
		decoder initialization 
*/
GIFD_HANDLE						// return	: GIF Decoder Handle
TCCXXX_GIFDEC_Init (
		GIFD_INIT *init,		// input	: initialization information
		GIFD_INFO *info			// output	: GIF file info / initialization result
		);

/* 
	Description: 
		decode one image 
*/
GIFD_RESULT						// return	: decoding result
TCCXXX_GIFDEC_Decode (
		GIFD_HANDLE hGif,		// handle	: GIF decoder handle returned from TCCXXX_GIF_Init()
		GIFD_DECIN *in,			// input	: video memory buffer
		GIFD_DECOUT *out);		// output	: information of the decoded image


#ifdef __cplusplus
}
#endif
#endif //__TCCXXX_GIF_DEC_H__