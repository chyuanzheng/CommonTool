/******************************************************************************
 file name : TCCXXX_IMAGE_CUSTOM_OUTPUT_SET.c (V1.55)
******************************************************************************/

#include "TCCXXX_IMAGE_CUSTOM_OUTPUT_SET_PNG.h"

/******************************************************************************
1. comp_1, comp_2, comp_2 usually represent for Y, U, and V respectively 
   (Could be any Color Space).
******************************************************************************/

unsigned int	PNG_IM_2nd_Offset;
unsigned int	PNG_IM_3rd_Offset;
unsigned int	PNG_IM_LCD_Half_Stride;
unsigned int	PNG_IM_LCD_Addr;

void PNG_TCC_CustomOutput_RGB565(PNG_IM_PIX_INFO out_info)
{
	int R, G, B;
	unsigned short RGB;

	//Color Conversion
	if(out_info.Src_Fmt == PNG_IM_SRC_YUV)
	{
		out_info.Comp_2 -= 128;
		out_info.Comp_3 -= 128;
		R = out_info.Comp_1 + ((1470103 * out_info.Comp_3) >> 20);
		if(R > 255) R = 255;	if(R < 0) R = 0;
		
		G = out_info.Comp_1 - ((360857 * out_info.Comp_2) >> 20) - ((748830 * out_info.Comp_3) >> 20);
		if(G > 255) G = 255;	if(G < 0) G = 0;
		
		B = out_info.Comp_1 + ((1858076 * out_info.Comp_2) >> 20);
		if(B > 255) B = 255;	if(B < 0) B = 0;
	}
	else if(out_info.Src_Fmt == PNG_IM_SRC_RGB)
	{
		R = out_info.Comp_1;
		G = out_info.Comp_2;
		B = out_info.Comp_3;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}

	RGB = (R & 0xF8)<<8;
	RGB |= (G & 0xFC) << 3;
	RGB |=(B>>3);

	(*(volatile unsigned short *)((PNG_IM_LCD_Addr+2 * out_info.Offset)))=(unsigned short)RGB;
}

void PNG_TCC_CustomOutput_RGB888_With_Alpha(PNG_IM_PIX_INFO out_info)
{
	int R, G, B;
	unsigned int RGB;

	//Color Conversion
	if(out_info.Src_Fmt == PNG_IM_SRC_YUV)
	{
		out_info.Comp_2 -= 128;
		out_info.Comp_3 -= 128;
		R = out_info.Comp_1 + ((1470103 * out_info.Comp_3) >> 20);
		if(R > 255 ) R = 255;	if(R < 0) R = 0;
		
		G = out_info.Comp_1 - ((360857 * out_info.Comp_2) >> 20) - ((748830 * out_info.Comp_3) >> 20);
		if(G > 255) G = 255;	if(G < 0) G = 0;
		
		B = out_info.Comp_1 + ((1858076 * out_info.Comp_2) >> 20);
		if(B > 255) B = 255;	if (B < 0) B = 0;
	}
	else if(out_info.Src_Fmt == PNG_IM_SRC_RGB)
	{
		RGB = ((out_info.Comp_4 & 0xF0) << 20) | (out_info.Comp_1 << 16) | (out_info.Comp_2 << 8) | out_info.Comp_3;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	(*(volatile unsigned int *)((PNG_IM_LCD_Addr + 4 * out_info.Offset)))=(unsigned int)RGB;
	//(*(volatile unsigned char *)((IM_LCD_Addr + out_info.Offset))) = (unsigned char)(out_info.Comp_4);
}

void PNG_TCC_CustomOutput_RGB888(PNG_IM_PIX_INFO out_info)
{
	int R, G, B;
	unsigned int RGB;

	//Color Conversion
	if(out_info.Src_Fmt == PNG_IM_SRC_YUV)
	{
		out_info.Comp_2 -= 128;
		out_info.Comp_3 -= 128;
		R = out_info.Comp_1 + ((1470103 * out_info.Comp_3) >> 20);
		if(R > 255 ) R = 255;	if(R < 0) R = 0;
		
		G = out_info.Comp_1 - ((360857 * out_info.Comp_2) >> 20) - ((748830 * out_info.Comp_3) >> 20);
		if(G > 255) G = 255;	if(G < 0) G = 0;
		
		B = out_info.Comp_1 + ((1858076 * out_info.Comp_2) >> 20);
		if(B > 255) B = 255;	if (B < 0) B = 0;
	}
	else if(out_info.Src_Fmt == PNG_IM_SRC_RGB)
	{
		R = out_info.Comp_1;
		G = out_info.Comp_2;
		B = out_info.Comp_3;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
#if 1 //BGR
	RGB = R << 8;
	RGB |= (G << 16);
	RGB |= (B << 24);
#else //RGB
	RGB = B << 8;
	RGB |= (G << 16);
	RGB |= (R << 24);
#endif
	
	(*(volatile unsigned int *)((PNG_IM_LCD_Addr + 4 * out_info.Offset)))=(unsigned int)RGB;
}

#define TC_CONV_YUV_ASR //modified by soo 20080313 : LSR -> ASR	

void PNG_TCC_CustomOutput_YUV420(PNG_IM_PIX_INFO out_info)
{
	int Y, U, V;

	//Color Conversion
	if(out_info.Src_Fmt == PNG_IM_SRC_YUV)
	{
		Y = out_info.Comp_1;
		U = out_info.Comp_2;
		V = out_info.Comp_3;
	}
	else if(out_info.Src_Fmt == PNG_IM_SRC_RGB)
	{
		Y =   ((313524 * out_info.Comp_1) >> 20) 
			+ ((645514 * out_info.Comp_2) >> 20) 
			+ ((119537 * out_info.Comp_3) >> 20);
		if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;

	#if !defined(TC_CONV_YUV_ASR)
		U =   ((-177209 * out_info.Comp_1) >> 20) 
			+ ((-307079 * out_info.Comp_2) >> 20) 
			+ (( 524288 * out_info.Comp_3) >> 20) + 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V =   (( 524288 * out_info.Comp_1) >> 20) 
			+ ((-439353 * out_info.Comp_2) >> 20) 
			+ (( -84934 * out_info.Comp_3) >> 20) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	#else //!defined(TC_CONV_YUV_ASR)
		U =   ((-177209 * out_info.Comp_1)/1048576) 
			+ ((-307079 * out_info.Comp_2)/1048576) 
			+ (( 524288 * out_info.Comp_3)/1048576)	+ 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V =   (( 524288 * out_info.Comp_1)/1048576) 
			+ ((-439353 * out_info.Comp_2)/1048576) 
			+ (( -84934 * out_info.Comp_3)/1048576) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	#endif ////!defined(TC_CONV_YUV_ASR)
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	(*(volatile unsigned char *)((PNG_IM_LCD_Addr + out_info.Offset)))=(unsigned char)Y;

	//Formatting for YUV420
	//if(((out_info.x + 1) & 0x1) && ((out_info.y + 1) & 0x1))
	if(((out_info.x) & 0x1) && ((out_info.y) & 0x1))
	{
		int temp = (out_info.y >> 1) * (PNG_IM_LCD_Half_Stride) + (out_info.x >> 1);
		(*(volatile unsigned char *)((PNG_IM_LCD_Addr + PNG_IM_2nd_Offset + temp))) = (unsigned char)U;
		(*(volatile unsigned char *)((PNG_IM_LCD_Addr + PNG_IM_3rd_Offset + temp))) = (unsigned char)V;
	}
}

void PNG_TCC_CustomOutput_YUV444(PNG_IM_PIX_INFO out_info)
{
	int Y, U, V;

	//Color Conversion
	if(out_info.Src_Fmt == PNG_IM_SRC_YUV)
	{
		Y = out_info.Comp_1;
		U = out_info.Comp_2;
		V = out_info.Comp_3;
	}
	else if(out_info.Src_Fmt == PNG_IM_SRC_RGB)
	{
		Y = ((313524 * out_info.Comp_1) >> 20) + ((645514 * out_info.Comp_2) >> 20) + ((119537 * out_info.Comp_3) >> 20);
		if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;

	#if !defined(TC_CONV_YUV_ASR)
		U =   ((-177209 * out_info.Comp_1) >> 20) 
			+ ((-307079 * out_info.Comp_2) >> 20) 
			+ (( 524288 * out_info.Comp_3) >> 20) + 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V =   (( 524288 * out_info.Comp_1) >> 20) 
			+ ((-439353 * out_info.Comp_2) >> 20) 
			+ (( -84934 * out_info.Comp_3) >> 20) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	#else //!defined(TC_CONV_YUV_ASR)
		U =   ((-177209 * out_info.Comp_1) /1048576) 
			+ ((-307079 * out_info.Comp_2) /1048576) 
			+ (( 524288 * out_info.Comp_3) /1048576) + 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V =   (( 524288 * out_info.Comp_1) /1048576) 
			+ ((-439353 * out_info.Comp_2) /1048576) 
			+ (( -84934 * out_info.Comp_3) /1048576) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	#endif //!defined(TC_CONV_YUV_ASR)
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	(*(volatile unsigned char *)((PNG_IM_LCD_Addr + out_info.Offset)))=(unsigned char)Y;
	(*(volatile unsigned char *)((PNG_IM_LCD_Addr + PNG_IM_2nd_Offset + out_info.Offset)))=(unsigned char)U;
	(*(volatile unsigned char *)((PNG_IM_LCD_Addr + PNG_IM_3rd_Offset + out_info.Offset)))=(unsigned char)V;
}

