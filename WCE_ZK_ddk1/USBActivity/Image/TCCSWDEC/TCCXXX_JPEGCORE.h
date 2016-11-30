#ifndef __JPEG_CORE_H__
#define __JPEG_CORE_H__

/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Defines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/

#define Zigzag(i) 			izigzag_index[i]
#define BUFFERSIZE 			1024
#define END_QUANTIZATION_TABLE 	0xFF
#define END_CODE_TABLE			0xFF
#define SHORT_BLOCK			128
#define MARKER_MARKER			0xff
#define MARKER_FIL			0xff

#define MARKER_SOI			0xd8	/* Represent the start of image. */
#define MARKER_EOI			0xd9	/* Represent the end of image. */
#define MARKER_SOS			0xda	/* Represent the start of scan header*/
#define MARKER_DQT			0xdb	/* Represent the quantization table definition */
#define MARKER_DNL			0xdc
#define MARKER_DRI			0xdd	/* Represent the restart interval definition */
#define MARKER_EXP			0xdf
#define MARKER_DHT			0xc4
#define MARKER_RSC			0xd0
#define MARKER_APP			0xe0
#define MARKER_JPG			0xf0

#define MARKER_SOF0			0xc0	/* Baseline DCT */
#define MARKER_SOF1			0xc1	/* Extended sequantial DCT, Huffman Coding */
#define MARKER_SOF2			0xc2	/* Progressive DCT, Huffman Coding */
#define MARKER_SOF3			0xc3	/* Losseless, Not support */
#define MARKER_SOF5			0xc5	/* Differential sequantial DCT */
#define MARKER_SOF6			0xc6	/* Differential prograssive DCT */
#define MARKER_SOF7			0xc7	/* Differential Lossless(sequential), Not support */

#define MARKER_RSC_MASK		0xf8
#define HTABLE_SIZE			8
#define VLC_TYPE				int16
#define CHUNK_SIZE			30000

#define IDCTSCALE(x) ((x)>>5)

//#define CONSTSHT			8
//#define FIX_1_082392200			((int32)  277)		/* FIX(1.082392200) */
//#define FIX_1_414213562			((int32)  362)		/* FIX(1.414213562) */
//#define FIX_1_847759065			((int32)  473)		/* FIX(1.847759065) */
//#define FIX_2_613125930			((int32)  669)		/* FIX(2.613125930) */

/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Functional Defines
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/
#define read_byte()			readbits(br, 8)
#define read_byte()			readbits(br, 8)
#define show_byte()			showbits(br, 8)
#define skip_byte()			skipbits(br, 8)

#define NEG_USR32(a,s)			(((uint32)(a))>>(32-(s)))
#define HUFF_EXTEND(x,s)		((x) < (1<<((s)-1)) ? (x) + (((-1)<<(s)) + 1) : (x))
	
	
#define	YUV420				0
#define	YUV422_V			1
#define	YUV422_H			2
#define	YUV444				3

/*
#define GET_VLC(code, table, bits, max_depth)\
{\
	int n, id, nb_bits;\
	\
	id= showbits(bits);\
	code = table[id][0];\
	n    = table[id][1];\
	\
	if(max_depth > 1 && n < 0){\
		skipbits(bits);\
		nb_bits = -n;\
		\
		id= showbits( nb_bits) + code;\
		code = table[id][0];\
		n    = table[id][1];\
		if(max_depth > 2 && n < 0){\
			\
			skipbits(nb_bits);\
			nb_bits = -n;\
			\
			id= showbits(nb_bits) + code;\
			code = table[id][0];\
			n    = table[id][1];\
		}\
	}\
	skipbits(n);\
}
*/

#define GET_VLC(code, table, bits, br)\
{\
	int n, id, nb_bits;\
	\
	id= showbits(br, bits);\
	code = table[id][0];\
	n    = table[id][1];\
	\
	if(n < 0){\
		skipbits(br, bits);\
		nb_bits = -n;\
		\
		id= showbits( br, nb_bits) + code;\
		code = table[id][0];\
		n    = table[id][1];\
	}\
	skipbits(br, n);\
}

#define GET_DATA(v, table, i, wrap, size) \
{\
	BYTE *ptr = (BYTE *)table + i * wrap;\
	switch(size) {\
	case 1:\
		v = *(BYTE *)ptr;\
		break;\
	case 2:\
		v = *(uint16 *)ptr;\
		break;\
	default:\
		v = *(uint32 *)ptr;\
		break;\
	}\
}

/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Variables for Decoder
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/
typedef struct VLC {
	int bits;
	VLC_TYPE (*table)[2];
	int table_size, table_allocated;
}VLC;

typedef void(*init_8x8)(int16*);
typedef void(*vld_ac)(int16*,int16*);
typedef void(*idctfast)(int16*, int16*, int16*);

//extern BitStreamInfo stBit;
//extern BYTE BitBuffer[2048]; 
//static int ret_bit;
typedef struct
{
	uint32	JD_readed_word;
	int32	JD_readed_bits;
	int32	JD_current_buffer;
	uint32	JD_FF00DECTION;
	int32	JD_read_point;

	BYTE *	JD_file_buf_ptr;

	void *	JD_datasource;					// File descriptor
	JD_CALLBACKS	JD_callbacks;			// FS I/O callback
	
	BYTE	JD_file_buf[BUFFERSIZE*2];
	
}BitReaderInfo;

typedef struct	//asm code 에서도 이용되므로 수정시 asm-code의 헤더파일도 수정할 것, 
{
	int32 				*JD_blk_resized_map;
	int32 				*JD_pel_resized_map;
	uint8				*JD_range_limit;
	
	int16				JD_resized_h;
	int16				JD_resized_v;
	int16				JD_scr_offset_v;
	int16				JD_scr_offset_h;
	int32				JD_f_resized_offset;
	
	int16				JD_LCD_WIDTH;
	int16				JD_LCD_HEIGHT;
	int16				JD_GlobalNumberComponents;
	
	int32				pix_num;
	int32               Src_Fmt;

	IM_CUSTOM_OUTPUT	*CustomOut;

#ifdef	ENABLE_CUSTOM_OUTPUT

#ifndef	SAVE_BLOCK_PIX
	IM_PIX_INFO			pix_info;
#else
	IM_PIX_INFO			pix_info[256+1];
#endif

#else
	int32	JD_LCD_FRAME_BUFFER_ADDR;
	int16	JD_CFrame_Real_CI[MAXIMUM_COMPONENTS];
#endif

}TCC_JPEGDEC_MDU_Info;

typedef struct
{
	TCC_JPEGDEC_MDU_Info	*MDU_Info;
	
	BitReaderInfo			*Bitreader;

	int32 *	JD_blk_resized_map;
	int32 *	JD_pel_resized_map;
	int16	JD_LCD_WIDTH;
	int16	JD_LCD_HEIGHT;
	int32	JD_LCD_FRAME_BUFFER_ADDR;

	int16	JD_GlobalHeight;				/* Dimensions of overall image */
	int16	JD_GlobalWidth;
	int16	JD_DecodingMode;
	int16	JD_ResyncInterval;             /* Resync interval (0 disables) */
	int16	JD_Resync_Togo;             /* Resync interval (0 disables) */

	int16	JD_scr_offset_h;
	int16	JD_scr_offset_v;
	int32	JD_f_resized_offset;
	int16	JD_NumberComponents;
	int16	JD_GlobalNumberComponents;		/* Global number of components */
	int16	JD_Type;
	int16	JD_resized_h;
	int16	JD_resized_v;
	uint32	JD_CurrentMDU;             /* Holds the value of the current MDU */
	uint32	JD_NumberMDU;              /* This number is the number of MDU's */
	int16	JD_CleartoResync;       /* Return black blocks until last Resync reached*/

	int16 *	JD_input1;
	int16 *	JD_input2;
	int16 *	JD_input3;
	int16	JD_LastDC[4];
	int16	JD_DataPrecision;			/* Data Precision (not used) */

	int16	JD_CScan_MDUWide;
	int16	JD_CScan_MDUHigh;

	int16 *	JD_OUTPUT[MAXIMUM_SOURCES];
	int16	JD_block_num[MAXIMUM_SOURCES];

	int16 *	JD_Calc[3];
	int 	JD_Calc_Offset[3];

	int16	JD_CScan_ci[MAXIMUM_SOURCES];           /* Index */
	int16	JD_CScan_ta[MAXIMUM_SOURCES];           /* AC Tables for that scan index */
	int16	JD_CScan_td[MAXIMUM_SOURCES];           /* DC Tables for scan index */
	int16	JD_CFrame_hf[MAXIMUM_COMPONENTS];	/* Horizontal frequency */
	int16	JD_CFrame_vf[MAXIMUM_COMPONENTS];	/* Vertical frequency */
	int16	JD_CFrame_tq[MAXIMUM_COMPONENTS];	/* Quantization table used by */
	int16	JD_CFrame_Real_CI[MAXIMUM_COMPONENTS];	/* Quantization table used by */
	int16	JD_CPlane_idx[MAXIMUM_COMPONENTS];	/* Quantization table used by */

	int16	JD_CFrame_Maxv;
	int16	JD_CFrame_Maxh;
	int16	JD_CFrame_MDUWide;
	int16	JD_CFrame_MDUHigh;	/* Number MDU wide */
	int32	JD_CFrame_MDUNum;

	int16	JD_QuantizationMatrices[MAXIMUM_DEVICES][64]; /* Pointers to q-matrices */

	int16	JD_Ss;
	int16	JD_Se;

	int16	JD_Ah;
	int16	JD_Al;

	int16 *	JD_Cur_Block;

	uint8	JD_Under_Decoding;
	uint8	JD_No_More_Scan;

	int16	JD_EOBRUN;
	VLC		vlcs[2][4];

	int32	JD_chunk_size;
	BYTE *	JD_chunk_ptr;//=JD_CHUNK;
	VLC *	JD_dcvlc;
	VLC *	JD_acvlc;
	VLC *	JD_vlc;

	BYTE	JD_IS_JFIF;

	IM_CUSTOM_OUTPUT		JD_out_callback;
	IM_PIX_INFO				JD_out_info;
	
	BYTE	JD_CHUNK[CHUNK_SIZE];
	int32	JD_resized_map_Buffer[1280 * 2];
	uint8	JD_range_limit[1024];
	BitReaderInfo			stBitreader;

	//IM_PIX_INFO pix_info[64*4];
}TC_JPEG_Decoder;

//TC_JPEG_Decoder stJPEG_DEC;

/*
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  Function Prototypes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*/

//Input Bitstream Related
static void		init_io_buffer(BitReaderInfo *br);
static void		skipbits (BitReaderInfo *br, int32 bits);
static void		skipbits_nochk (BitReaderInfo *br, int32 bits);
static void		sync_byte(BitReaderInfo *br);
static int32	x_readbits (BitReaderInfo *br, int32 bits);
static uint32	readbits (BitReaderInfo *br,int32 bits);
static uint32	showbits (BitReaderInfo *br, int32 rbits);
static uint8 	_show_byte(BitReaderInfo *br);
static uint8	_read_byte(BitReaderInfo *br);
static uint8	_read_byte_nochk(BitReaderInfo *br);

//VLD Table and Memory Management Related
#ifndef ASM_OPT
static void		jmemset(uint8 *dst, int8 val, uint32 size);
#else
extern void		jmemset(uint8 *dst, int8 val, uint32 size);
#endif
static void		build_huffman_codes(uint8 * huff_size, uint16 * huff_code, uint8 * bits_table, uint8 * val_table);
static void*	jrealloc(TC_JPEG_Decoder *pDecoder, void *ptr, uint32 size);
static int32	alloc_table(TC_JPEG_Decoder *pDecoder, VLC *vlc, int32 size);
static int32	build_vlc(TC_JPEG_Decoder *pDecoder, VLC *vlc, uint8 *bits_table, uint8 * val_table, int32 nb_codes);
static int32	build_table(TC_JPEG_Decoder *pDecoder, VLC *vlc, int32 table_nb_bits, int32 nb_codes, const void * bits, int32 bits_wrap,
							int32 bits_size, const void * codes, int32 codes_wrap, int32 codes_size, uint32 code_prefix,
							int32 n_prefix);
static int32	init_vlc(TC_JPEG_Decoder *pDecoder, VLC *vlc, int32 nb_bits, int32 nb_codes, const void * bits, int32 bits_wrap, int32 bits_size,
						 const void *codes, int32 codes_wrap, int32 codes_size);

//Initialization Related
static void		Initialize_Variable(TC_JPEG_Decoder *pDecoder, int32 lcd_width,int32 lcd_height);
static void		init_resize_mem(TC_JPEG_Decoder *pDecoder, int32 lcd_width, int32 lcd_height);
static void		prepare_range_limit_table(TC_JPEG_Decoder *pDecoder);

//Header Parsing Related
static int32	ScreenSOImarker(BitReaderInfo *br);
static int32	GetFrameHeader(TC_JPEG_Decoder *pDecoder);
static int32	ReadFrameHeader(TC_JPEG_Decoder *pDecoder);
static int32	GetScanHeader(TC_JPEG_Decoder *pDecoder);
static int32	ReadScanHeader(TC_JPEG_Decoder *pDecoder);

static int32	ReadDHT(TC_JPEG_Decoder *pDecoder);
static int32	ReadDQT(TC_JPEG_Decoder *pDecoder);
static int32	ReadAPP(BitReaderInfo *br);
static int32	ReadCOM(BitReaderInfo *br);
static int32	ReadDRI(TC_JPEG_Decoder *pDecoder);

//Image Size and Block number Decision Related
static void		CheckScan(TC_JPEG_Decoder *pDecoder);
static void		MakeConsistentFrameSize(TC_JPEG_Decoder *pDecoder);

//Baseline Decoding Related
static int32	TCC77X_JPEG_Decode_Base(TC_JPEG_Decoder *pDecoder);

static int16	DecodeDC(TC_JPEG_Decoder *pDecoder, int32 index);
static void		resync_process(TC_JPEG_Decoder *pDecoder);

void			idctfast0(int16 * x, int16 *y);
void			idctfast1(int16 * x,int16 * y);
static void		idctsimple(int16 * x, int16 * y, int16 * qmatrix);

void			clear_block(int16 *p);
void			clear_block9(int16 *p);

static int32		DecodeAC0(TC_JPEG_Decoder *pDecoder, int16 *matrix, int16 *qmatrix);
static int32		DecodeAC1(TC_JPEG_Decoder *pDecoder, int16 *matrix, int16 *qmatrix);
static void		SKIPDecodeAC(TC_JPEG_Decoder *pDecoder);

void			sWriteMDU(TCC_JPEGDEC_MDU_Info *pMDUInfo, 
					  	int16 * Block_Input1, int32 hf1,int32 vf1, int16 * Block_Input2, int32 hf2, int32 vf2,
						int16 * Block_Input3, int32 hf3,int32 vf3, int32 x, int32 y);

void			rWriteMDU_YUV444(TCC_JPEGDEC_MDU_Info *pMDUInfo, 
					  	int16 * Block_Input1, int32 hf1,int32 vf1, int16 * Block_Input2, int32 hf2, int32 vf2,
						int16 * Block_Input3, /*int32 hf3,int32 vf3,*/ int32 x, int32 y);
void			rWriteMDU_YUV420(TCC_JPEGDEC_MDU_Info *pMDUInfo, 
					  	int16 * Block_Input1, int32 hf1,int32 vf1, int16 * Block_Input2, int32 hf2, int32 vf2,
						int16 * Block_Input3, /*int32 hf3,int32 vf3,*/ int32 x, int32 y);
void			rWriteMDU_YUV422(TCC_JPEGDEC_MDU_Info *pMDUInfo, 
					  	int16 * Block_Input1, int32 hf1,int32 vf1, int16 * Block_Input2, int32 hf2, int32 vf2,
						int16 * Block_Input3, /*int32 hf3,int32 vf3,*/ int32 x, int32 y, int yuv_format);


//Progressive Decoding Related
static int32	TCC77X_JPEG_Decode_Prog(TC_JPEG_Decoder *pDecoder);

static int32	Decode_DC_Prog(TC_JPEG_Decoder *pDecoder);
static int32	Decode_AC_Prog(TC_JPEG_Decoder *pDecoder);

static int32	Decode_Huff_AC_First(TC_JPEG_Decoder *pDecoder, int16 * block, VLC * Huff_table);
static int32	Decode_Huff_AC_Refine(TC_JPEG_Decoder *pDecoder, int16 * block, VLC * Huff_table);

static void		Dequant(int16 *matrix, int16 *qmatrix );

#endif	//__JPEG_CORE_H__
