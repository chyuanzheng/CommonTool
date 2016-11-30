/****************************************************************************/
/* MODULE:                                                                 	*/
/*   TCC89x_HW_JPG_Proc.h - JPEG Encode Functions                                      */
/****************************************************************************/
/*
 *   TCC Version 0.1
 *   Copyright (c) Telechips, Inc.
 *   ALL RIGHTS RESERVED
*/

#ifndef __JPEG89HWDEC_H__
#define __JPEG89HWDEC_H__

#include <stdio.h>

#define	MAX_RESOLUTION_W			4096
#define	MAX_RESOLUTION_H			4096
#define MAX_DEC_W					(MAX_RESOLUTION_W/4)
#define MAX_DEC_H					(MAX_RESOLUTION_H/4)

#define PHYSICAL_REG_SIZE			1024*4
#define	MAX_STREAM_BUF				1000//100   // kbyte unit

#define JPEG_PARSE_START_IMAGE 		0xd8
#define JPEG_PARSE_DQT_IMAGE 		0xdb
#define JPEG_PARSE_SOF_IMAGE 		0xc0
#define JPEG_PARSE_PROGRESSIVE 		0xc2
#define JPEG_PARSE_DHT_IMAGE 		0xc4
#define JPEG_PARSE_DRI_IMAGE 		0xdd
#define JPEG_PARSE_SOS_IMAGE 		0xda
#define JPEG_PARSE_END_IMAGE 		0xd9

#ifndef HwJPD_OUT_SCL_4
#define	HwJPD_OUT_SCL_4				Hw0										/* 1/4 (Area Ratio) */
#endif
#ifndef HwJPD_OUT_SCL_16
#define	HwJPD_OUT_SCL_16			Hw1										/* 1/16 (Area Ratio) */
#endif
#ifndef HwJP_START_RUN
#define	HwJP_START_RUN				Hw0										// Codec Start
#endif

////////////////////////////////////////////////////////////////////////////
/* Structure															  */
////////////////////////////////////////////////////////////////////////////
typedef struct {
	unsigned int PhyAddr;
	unsigned int VirAddr;
	unsigned int MemSize;
}Jpeg_Ip_Memory_Structure_Element;


typedef struct{
	JPEGDECODER *pHWJPReg;	
	CKC	 *pCKCReg;	
}Jpeg_Ip_Variable_Register_Structure;


typedef struct{
	int Ip_Scale_Width;
	int Ip_Scale_Height;	
	int Ip_Scale_Down;	
}Jpeg_Ip_Variable_DecScaler_Structure;


typedef struct {	
	Jpeg_Ip_Memory_Structure_Element	Dec_In;
	Jpeg_Ip_Memory_Structure_Element	Dec_Out_Y;
	Jpeg_Ip_Memory_Structure_Element	Dec_Out_U;
	Jpeg_Ip_Memory_Structure_Element	Dec_Out_V;
}Jpeg_Ip_Memory_Structure;	


typedef struct{
	Jpeg_Ip_Variable_Register_Structure	reg;	
	Jpeg_Ip_Variable_DecScaler_Structure Scale;
	FILE *fp;
	int JPEGDEC_ResetInterVal;	
	int JPEGDEC_orgCodeSize;	
	int JPEGDEC_CodeSize;	
	int JPEGDEC_Chroma;
	int JPEGDEC_In_Width;
	int JPEGDEC_In_Height; 
	int JPEGDEC_Out_Width;
	int JPEGDEC_Out_Height; 	
	int JPEGDEC_PartialCnt;	
	int JPEGDEC_End;	
}Jpeg_Ip_Variable_Structure;



/**********************************************/
/* Final Resource Struct */
/**********************************************/
typedef struct {
	Jpeg_Ip_Memory_Structure Mem;
	Jpeg_Ip_Variable_Structure Vari;
} Jpeg_Ip_Dec_Info_Struct;	


/**********************************************/
/* Parse Error Type Enum Struct */
/**********************************************/
enum{
	//NO_ERROR = 0,
	SOS_WITHOUT_SOF, 			// 0x1
	SOF_WITHOUT_SOI, 			// 0x2
	MARKER_NOT_FOUND, 			// 0x3
	MARKER_NOT_SUPPORT, 		// 0x4
	CHROMA_NOT_SUPPORT, 		// 0x5
	RESOLUTION_NOT_SUPPORT,		// 0x6	
	QTABLE_PREC_ERROR, 			// 0x7
	SOF_PREC_ERROR, 			// 0x8
	SOS_COMP_ERROR, 			// 0x9
	END_OF_IMAGE, 				// 10 0xa
	
	INT_FLAG_CODED_BUF_STAT, 	// 11 0xb
	INT_FLAG_IFIFO_STAT, 		// 12 0xc
	INT_FLAG_OFIFO_STAT,		// 13 0xd
	INT_FLAG_DECODING_ERR, 		// 14 0xe
	INT_NONE, 					// 15 0xf 

	BUFFER_OVERFLOW, 			// 16 0x10
	FILE_READ_ERROR, 			// 17 0x11
	PROGRESSIVE_JPEG 			// 18 0x12
	
};

/**********************************************/
/* Error Type Enum Struct */
/**********************************************/
enum {

	JPEG_IP_ERROR_NONE,
	JPEG_IP_VIRTUAL_HANDLE,
	JPEG_IP_SET_REGISTER,
	JPEG_IP_SET_SCALE_REGISTER,
	JPEG_IP_SET_FILE_FP,
	JPEG_IP_SET_MEM_DECIN,
	JPEG_IP_PARSE_HEADER,
	JPEG_IP_SET_MEM_DECOUT,	
	JPEG_IP_ERROR_MAX
};

/**********************************************/
/* Function */
/**********************************************/
extern unsigned long TCC_ALLOC_MEM(unsigned long HwBaseAddress, unsigned long nSize);

extern unsigned long TC_JpegLength(FILE * iHandle);
extern int Jpeg_Ip_Init(void);
extern int Jpeg_Ip_DeInit(void);
extern void Jpeg_Ip_Info_Init(unsigned int JPEG_PHYSICAL_MEMORY_BASE);
extern void Jpeg_Ip_Info_DeInit(void);
extern void *Jpeg_Ip_Info_Get_Mem_Srtuct_Ptr(void);
extern void *Jpeg_Ip_Info_Get_Vari_Srtuct_Ptr(void);
extern int Jpeg_Ip_Info_Set_Vari_FileFp(FILE *fp);
extern int Jpeg_Ip_Info_Set_Vari_Dec_Out_Size(int *width, int *height);
extern int Jpeg_Ip_Info_Set_Vari_Dec_Scaler_Size( int *d_w,int *d_h, int *new_w, int *new_h);
extern int Jpeg_Ip_Info_Set_Vari_Dec_Scaler(void);
extern int Jpeg_Ip_Info_Set_Vari_PartialCnt(void);
extern int Jpeg_Ip_Info_Set_Mem_Dec_In(void);
extern int Jpeg_Ip_Info_Set_Mem_Dec_Out(int width,int height);
extern int Jpeg_Ip_Info_Set_Mem_Scale_Out(Jpeg_Ip_Memory_Structure_Element *pScaleMem, int size);
extern int Jpeg_Ip_Info_Init_Vari_Reg_Struct(void);
extern int Jpeg_Ip_Info_DeInit_Vari_Reg_Struct(void);
extern int Jpeg_Ip_SetDQT();
extern int Jpeg_Ip_SetSOF(int *chsize, int *cvsize, int *chroma);
extern int Jpeg_Ip_SetDHT();
extern int Jpeg_Ip_SetDRI(int *rsti);
extern int Jpeg_Ip_SetSOS(int chsize, int cvsize);
extern void Jpeg_Ip_SkipHeader();
extern int Jpeg_Ip_Set_HWReg(void);
extern int Jpeg_Ip_SetImageInfo(unsigned int code_addr, unsigned int raw_addr_Y,unsigned int raw_addr_U,unsigned int raw_addr_V, int img_w, int img_h, int g_chroma, unsigned int codesize, unsigned int rsti);
extern int Jpeg_Ip_Memory_Recover();
extern int Jpeg_Ip_Parse_Header(void);
extern int Jpeg_Ip_Parse_Header_Process(FILE * hFile, int * img_w, int * img_h, unsigned int * g_chroma, unsigned int * codesize, unsigned int * g_codesize, int * rsti);
extern int Jpeg_Ip_Decoder_Init(FILE *hFile,int *dec_out_width,int *dec_out_height, int* format, unsigned int uiHDMI_INCLUDE_Codition);
extern int Jpeg_Ip_Deocder_WriteCodeStream(void);
extern int  Jpeg_Ip_Decoder_Polling(int hFile);
extern int Jpeg_Ip_Decode(int hFile, unsigned int OutPhyAddr, unsigned int *dec_out_width, unsigned int *dec_out_height);

#endif	// __JPEGDEC_H__

/* end of file */