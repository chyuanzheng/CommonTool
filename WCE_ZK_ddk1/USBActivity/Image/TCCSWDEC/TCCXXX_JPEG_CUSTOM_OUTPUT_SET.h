typedef struct {
	int Comp_1;
	int Comp_2;
	int Comp_3;
	int Comp_4;
	int Offset;
	int x;
	int y;
	int Src_Fmt;
}IM_PIX_INFO;

#define IM_SRC_YUV		0
#define IM_SRC_RGB		1
#define IM_SRC_OTHER	2

extern unsigned int	JPG_IM_2nd_Offset;
extern unsigned int	JPG_IM_3rd_Offset;
extern unsigned int	JPG_IM_LCD_Half_Stride;
extern unsigned int	JPG_IM_LCD_Addr;

/* JPEG Decoder */
void TCC_JPEG_CustomOutput_RGB565_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt);
void TCC_JPEG_CustomOutput_RGB888_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt);
void TCC_JPEG_CustomOutput_YUV420_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt);
void TCC_JPEG_CustomOutput_YUV444_Block(IM_PIX_INFO *pix_info, unsigned int count, int Src_Fmt);

#define USE_ARM11_ASM_OPT_CODE
