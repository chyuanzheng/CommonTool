#include "TCCXXX_JPEG_CUSTOM_OUTPUT_SET.h"

/*************************************************************************************
1. comp_1, comp_2, comp_2 usually represent for Y, U, and V respectively (Could be any Color Space).

*************************************************************************************/

unsigned int	JPG_IM_2nd_Offset;
unsigned int	JPG_IM_3rd_Offset;
unsigned int	JPG_IM_LCD_Half_Stride;
unsigned int	JPG_IM_LCD_Addr;

/*******************************************************************************************************/
/* JPEG DECODER (SW) */
/*******************************************************************************************************/
#ifdef	USE_ARM11_ASM_OPT_CODE


extern "C" void TCC_JPEG_YUV_To_RGB565(IM_PIX_INFO *pix_info, unsigned int count, unsigned int	lcd_addr);

#else

void TCC_JPEG_YUV_To_RGB565(IM_PIX_INFO *pix_info, unsigned int count, unsigned int	lcd_addr)
{
	int R, G, B;
	unsigned short RGB;
	unsigned int i;

	for(i = 0; i < count; i++)
	{
		IM_PIX_INFO *out_info = &pix_info[i];
		//Color Conversion
		out_info->Comp_2 -= 128;
		out_info->Comp_3 -= 128;
		R = out_info->Comp_1 + ((1470103 * out_info->Comp_3) >> 20);
		if(R > 255) R = 255;	if(R < 0) R = 0;
				
		G = out_info->Comp_1 - ((360857 * out_info->Comp_2) >> 20) - ((748830 * out_info->Comp_3) >> 20);
		if(G > 255) G = 255;	if(G < 0) G = 0;
			
		B = out_info->Comp_1 + ((1858076 * out_info->Comp_2) >> 20);
		if(B > 255) B = 255;	if(B < 0) B = 0;

		RGB = (R & 0xF8)<<8;
		RGB |= (G & 0xFC) << 3;
		RGB |=(B>>3);

		out_info->Comp_2 += 128;
		out_info->Comp_3 += 128;

		(*(volatile unsigned short *)((lcd_addr+2 * out_info->Offset)))=(unsigned short)RGB;
	}
}

#endif

void TCC_JPEG_CustomOutput_RGB565_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt)
{
	int R, G, B;
	unsigned short RGB;
	unsigned int i;

	switch(Src_Fmt)
	{
	case IM_SRC_YUV:
		TCC_JPEG_YUV_To_RGB565(pix_info, count, JPG_IM_LCD_Addr);
		break;

	case IM_SRC_RGB:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			//Color Conversion
			R = out_info->Comp_1;
			G = out_info->Comp_2;
			B = out_info->Comp_3;

			RGB = (R & 0xF8)<<8;
			RGB |= (G & 0xFC) << 3;
			RGB |=(B>>3);

			(*(volatile unsigned short *)((JPG_IM_LCD_Addr+2 * out_info->Offset)))=(unsigned short)RGB;
		}
		break;
	default:
#if 0
		//src_fmt == JD_SRC_OTHER
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			//Color Conversion
			{
				add conversion code here!
			}

			RGB = (R & 0xF8)<<8;
			RGB |= (G & 0xFC) << 3;
			RGB |=(B>>3);

			(*(volatile unsigned short *)((JPG_IM_LCD_Addr+2 * out_info->Offset)))=(unsigned short)RGB;
		}
#endif
		break;
	}
}

void TCC_JPEG_CustomOutput_RGB888_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt)
{
	int R, G, B;
	unsigned int RGB;
	unsigned int i;

	//Color Conversion
	switch(Src_Fmt)
	{
	case IM_SRC_YUV:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			out_info->Comp_2 -= 128;
			out_info->Comp_3 -= 128;
			R = out_info->Comp_1 + ((1470103 * out_info->Comp_3) >> 20);
			if(R > 255 ) R = 255;	if(R < 0) R = 0;
			
			G = out_info->Comp_1 - ((360857 * out_info->Comp_2) >> 20) - ((748830 * out_info->Comp_3) >> 20);
			if(G > 255) G = 255;	if(G < 0) G = 0;
			
			B = out_info->Comp_1 + ((1858076 * out_info->Comp_2) >> 20);
			if(B > 255) B = 255;	if (B < 0) B = 0;

			RGB = R << 8;
			RGB |= (G << 16);
			RGB |= (B << 24);
			
			(*(volatile unsigned int *)((JPG_IM_LCD_Addr + 4 * out_info->Offset)))=(unsigned int)RGB;
		}
		break;
	case IM_SRC_RGB:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			R = out_info->Comp_1;
			G = out_info->Comp_2;
			B = out_info->Comp_3;

			RGB = R << 8;
			RGB |= (G << 16);
			RGB |= (B << 24);
			
			(*(volatile unsigned int *)((JPG_IM_LCD_Addr + 4 * out_info->Offset)))=(unsigned int)RGB;
		}
	default:
#if 0
		//src_fmt == JD_SRC_OTHER
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			//Color Conversion
			{
				add conversion code here!
			}

			RGB = R << 8;
			RGB |= (G << 16);
			RGB |= (B << 24);
	
			(*(volatile unsigned int *)((JPG_IM_LCD_Addr + 4 * out_info->Offset)))=(unsigned int)RGB;
		}
#endif
		break;
	}
}

void TCC_JPEG_CustomOutput_YUV420_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt)
{
	int Y, U, V;
	unsigned int i;

	//Color Conversion
	switch(Src_Fmt)
	{
	case IM_SRC_YUV:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			Y = out_info->Comp_1;
			U = out_info->Comp_2;
			V = out_info->Comp_3;
			
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;

			//Formatting for YUV420
			if(((out_info->x + 1) & 0x1) && ((out_info->y + 1) & 0x1))
			{
				int temp = (out_info->y >> 1) * (JPG_IM_LCD_Half_Stride) + (out_info->x >> 1);
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + temp))) = (unsigned char)U;
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + temp))) = (unsigned char)V;
			}
		}
		break;
	case IM_SRC_RGB:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];

			Y = ((313524 * out_info->Comp_1) >> 20) + ((645514 * out_info->Comp_2) >> 20) + ((119537 * out_info->Comp_3) >> 20);
			if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;
			
			U = ((-177209 * out_info->Comp_1) >> 20) + ((-307079 * out_info->Comp_2) >> 20) + ((524288 * out_info->Comp_3) >> 20) + 128;
			if(U > 255) U = 255;	if(U < 0) U = 0;
			
			V = ((524288 * out_info->Comp_1) >> 20) + ((-439353 * out_info->Comp_2) >> 20) + ((-84934 * out_info->Comp_3) >> 20) + 128;
			if(V > 255) V = 255;	if (V < 0) V = 0;

			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;

			//Formatting for YUV420
			if(((out_info->x + 1) & 0x1) && ((out_info->y + 1) & 0x1))
			{
				int temp = (out_info->y >> 1) * (JPG_IM_LCD_Half_Stride) + (out_info->x >> 1);
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + temp))) = (unsigned char)U;
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + temp))) = (unsigned char)V;
			}
		}
		break;
	default:
#if 0	
		//src_fmt == JD_SRC_OTHER
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			//Color Conversion
			{
				add conversion code here!
			}
		
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;

			//Formatting for YUV420
			if(((out_info->x + 1) & 0x1) && ((out_info->y + 1) & 0x1))
			{
				int temp = (out_info->y >> 1) * (JPG_IM_LCD_Half_Stride) + (out_info->x >> 1);
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + temp))) = (unsigned char)U;
				(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + temp))) = (unsigned char)V;
			}
		}
#endif
		break;
	}
}

void TCC_JPEG_CustomOutput_YUV444_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt)
{
	int Y, U, V;
	unsigned int i;
	
	switch(Src_Fmt)
	{
	case IM_SRC_YUV:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];

			Y = out_info->Comp_1;
			U = out_info->Comp_2;
			V = out_info->Comp_3;

			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + out_info->Offset)))=(unsigned char)U;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + out_info->Offset)))=(unsigned char)V;
		}
		break;
	case IM_SRC_RGB:
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];

			Y = ((313524 * out_info->Comp_1) >> 20) + ((645514 * out_info->Comp_2) >> 20) + ((119537 * out_info->Comp_3) >> 20);
			if(Y > 255 ) Y = 255;	if(Y < 0) Y = 0;
			
			U = ((-177209 * out_info->Comp_1) >> 20) + ((-307079 * out_info->Comp_2) >> 20) + ((524288 * out_info->Comp_3) >> 20) + 128;
			if(U > 255) U = 255;	if(U < 0) U = 0;
			
			V = ((524288 * out_info->Comp_1) >> 20) + ((-439353 * out_info->Comp_2) >> 20) + ((-84934 * out_info->Comp_3) >> 20) + 128;
			if(V > 255) V = 255;	if (V < 0) V = 0;

			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + out_info->Offset)))=(unsigned char)U;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + out_info->Offset)))=(unsigned char)V;
		}
		break;
	default:
#if 0
		//src_fmt == JD_SRC_OTHER
		for(i = 0; i < count; i++)
		{
			IM_PIX_INFO *out_info = &pix_info[i];
			//Color Conversion
			{
				add conversion code here!
			}

			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + out_info->Offset)))=(unsigned char)Y;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_2nd_Offset + out_info->Offset)))=(unsigned char)U;
			(*(volatile unsigned char *)((JPG_IM_LCD_Addr + JPG_IM_3rd_Offset + out_info->Offset)))=(unsigned char)V;
		}
#endif
		break;
	}	
}
