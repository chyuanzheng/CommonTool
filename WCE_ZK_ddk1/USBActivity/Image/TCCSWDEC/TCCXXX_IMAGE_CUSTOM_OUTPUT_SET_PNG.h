/******************************************************************************
 file name : TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_PNG.h (V1.55)
******************************************************************************/
#ifndef __TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_PNG_H__
#define __TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_PNG_H__

typedef struct {
	int Comp_1;
	int Comp_2;
	int Comp_3;
	int Comp_4;		//V.1.52~
	int Offset;
	int x;
	int y;
	int Src_Fmt;
}PNG_IM_PIX_INFO;

#define PNG_IM_SRC_YUV		0
#define PNG_IM_SRC_RGB		1
#define PNG_IM_SRC_OTHER	2

extern unsigned int	PNG_IM_2nd_Offset;
extern unsigned int	PNG_IM_3rd_Offset;
extern unsigned int	PNG_IM_LCD_Half_Stride;
extern unsigned int	PNG_IM_LCD_Addr;

void PNG_TCC_CustomOutput_RGB565(PNG_IM_PIX_INFO out_info);
void PNG_TCC_CustomOutput_RGB888_With_Alpha(PNG_IM_PIX_INFO out_info);
void PNG_TCC_CustomOutput_RGB888(PNG_IM_PIX_INFO out_info);
void PNG_TCC_CustomOutput_YUV420(PNG_IM_PIX_INFO out_info);
void PNG_TCC_CustomOutput_YUV444(PNG_IM_PIX_INFO out_info);

#endif //__TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_H__
