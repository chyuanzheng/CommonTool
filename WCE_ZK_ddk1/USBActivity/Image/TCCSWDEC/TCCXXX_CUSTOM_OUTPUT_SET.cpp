#include "stdAfx.h"
#include "TCCXXX_IMAGE_CUSTOM_OUTPUT_SET.h"

/*************************************************************************************
1. comp_1, comp_2, comp_2 usually represent for Y, U, and V respectively (Could be any Color Space).

*************************************************************************************/

unsigned int	IM_2nd_Offset;
unsigned int	IM_3rd_Offset;
unsigned int	IM_LCD_Half_Stride;
unsigned int	IM_LCD_Addr;

void TCC_CustomOutput_RGB565(IM_PIX_INFO out_info)
{
	int R, G, B;
	unsigned short RGB;

	//Color Conversion
	if(out_info.Src_Fmt == IM_SRC_YUV)
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
	else if(out_info.Src_Fmt == IM_SRC_RGB)
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

	(*(volatile unsigned short *)((IM_LCD_Addr+2 * out_info.Offset)))=(unsigned short)RGB;
}

void TCC_CustomOutput_RGB888(IM_PIX_INFO out_info)
{
	int R, G, B;
	unsigned int RGB;

	//Color Conversion
	if(out_info.Src_Fmt == IM_SRC_YUV)
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
#if 1
	else if(out_info.Src_Fmt == IM_SRC_RGB)
	{
		R = out_info.Comp_1;
		G = out_info.Comp_2;
		B = out_info.Comp_3;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	RGB = R << 16;
	RGB |= (G << 8);
	RGB |= (B << 0);
	
	(*(volatile unsigned int *)((IM_LCD_Addr + 4 * out_info.Offset)))=(unsigned int)RGB;
#endif
}

void TCC_CustomOutput_YUV420(IM_PIX_INFO out_info)
{
	int Y, U, V;

	//Color Conversion
	if(out_info.Src_Fmt == IM_SRC_YUV)
	{
		Y = out_info.Comp_1;
		U = out_info.Comp_2;
		V = out_info.Comp_3;
	}
	else if(out_info.Src_Fmt == IM_SRC_RGB)
	{
		Y = ((313524 * out_info.Comp_1) >> 20) + ((645514 * out_info.Comp_2) >> 20) + ((119537 * out_info.Comp_3) >> 20);
		if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;
		
		U = ((-177209 * out_info.Comp_1) >> 20) + ((-307079 * out_info.Comp_2) >> 20) + ((524288 * out_info.Comp_3) >> 20) + 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V = ((524288 * out_info.Comp_1) >> 20) + ((-439353 * out_info.Comp_2) >> 20) + ((-84934 * out_info.Comp_3) >> 20) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	(*(volatile unsigned char *)((IM_LCD_Addr + out_info.Offset)))=(unsigned char)Y;

	//Formatting for YUV420
	if(((out_info.x) & 0x1) && ((out_info.y ) & 0x1))
	{
		int temp = (out_info.y >> 1) * (IM_LCD_Half_Stride) + (out_info.x >> 1);
		(*(volatile unsigned char *)((IM_LCD_Addr + IM_2nd_Offset + temp))) = (unsigned char)U;
		(*(volatile unsigned char *)((IM_LCD_Addr + IM_3rd_Offset + temp))) = (unsigned char)V;
	}
}

void TCC_CustomOutput_YUV444(IM_PIX_INFO out_info)
{
	int Y, U, V;

	//Color Conversion
	if(out_info.Src_Fmt == IM_SRC_YUV)
	{
		Y = out_info.Comp_1;
		U = out_info.Comp_2;
		V = out_info.Comp_3;
	}
	else if(out_info.Src_Fmt == IM_SRC_RGB)
	{
		Y = ((313524 * out_info.Comp_1) >> 20) + ((645514 * out_info.Comp_2) >> 20) + ((119537 * out_info.Comp_3) >> 20);
		if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;
		
		U = ((-177209 * out_info.Comp_1) >> 20) + ((-307079 * out_info.Comp_2) >> 20) + ((524288 * out_info.Comp_3) >> 20) + 128;
		if(U > 255) U = 255;	if(U < 0) U = 0;
		
		V = ((524288 * out_info.Comp_1) >> 20) + ((-439353 * out_info.Comp_2) >> 20) + ((-84934 * out_info.Comp_3) >> 20) + 128;
		if(V > 255) V = 255;	if (V < 0) V = 0;
	}
	else//src_fmt == JD_SRC_OTHER
	{
	}
	
	(*(volatile unsigned char *)((IM_LCD_Addr + out_info.Offset)))=(unsigned char)Y;
	(*(volatile unsigned char *)((IM_LCD_Addr + IM_2nd_Offset + out_info.Offset)))=(unsigned char)U;
	(*(volatile unsigned char *)((IM_LCD_Addr + IM_3rd_Offset + out_info.Offset)))=(unsigned char)V;
}