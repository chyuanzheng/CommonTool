#ifndef __TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_H__
#define __TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_H__

typedef struct {
	int Comp_1;
	int Comp_2;
	int Comp_3;
	int Offset;
	int x;
	int y;
	int Src_Fmt;
}IM_PIX_INFO;

#define IM_SRC_YUV	0
#define IM_SRC_RGB	1
#define IM_SRC_OTHER	2

extern "C"
{
	extern unsigned int	IM_2nd_Offset;
	extern unsigned int	IM_3rd_Offset;
	extern unsigned int	IM_LCD_Half_Stride;
	extern unsigned int	IM_LCD_Addr;

	void TCC_CustomOutput_RGB565(IM_PIX_INFO out_info);
	void TCC_CustomOutput_RGB888(IM_PIX_INFO out_info);
	void TCC_CustomOutput_YUV420(IM_PIX_INFO out_info);
	void TCC_CustomOutput_YUV444(IM_PIX_INFO out_info);
}

#endif //__TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_H__
