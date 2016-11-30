
#ifndef _SHARED_H_
#define _SHARED_H_

////////////////////////////////////////////////////////////////

#define TCC_CODEC_ERROR_MAILBOX_INIT			-11
#define TCC_CODEC_ERROR_LOADTABLE_INIT			-12
#define TCC_CODEC_ERROR_CODEC_LOAD				-13
#define TCC_CODEC_ERROR_MEMORY_ALLOC			-14
#define TCC_CODEC_ERROR_NOT_DECODABLE_TYPE		-21
#define TCC_CODEC_ERROR_INPUT_SIZE				-22
#define TCC_CODEC_ERROR_OUTPUT_BUFFER_SIZE		-23
#define TCC_CODEC_ERROR_CODEC_INIT				-24
#define TCC_CODEC_ERROR_DECODING				-31

#define EC_USER_UNSUPPORTTED_VIDEO				EC_USER + 1001
#define EC_USER_NUMBER_OF_CAPTION				EC_USER + 1002
#define EC_USER_GET_SAMPLE_FAIL					EC_USER + 1003
#define EC_USER_GET_ASF_ASPECT_RATIO			EC_USER + 1004
#define EC_USER_UPDATE_SEEKABLE_DURATION		EC_USER + 1005

#define EC_USER_UPDATE_IS_SEEKABLE				EC_USER + 1006
#define EC_USER_UPDATE_NO_AUDIO					EC_USER + 1007

////////////////////////////////////////////////////////////////

#ifndef __TCC88XX_WINCE__
#ifndef __TCC89XX_WINCE__

#include "T5MP4.h"

/* All variables in this header are shared between A926 and A946 */
// DO NOT USE VALUE 0 
#define	LCD_HSIZE	480
#define	LCD_VSIZE	272

#define	_SHARED_SYNC_REG			0

#define	_SHARED_MSG_REG				3
#define	_SHARED_MSGVAL_DS			1
#define	_SHARED_MSGVAL_DSDONE		1			// from 966
#define	_SHARED_MSGVAL_VOL			2
#define	_SHARED_MSGVAL_VOLDONE		2			// from 966
#define	_SHARED_MSGVAL_VOP			3
#define	_SHARED_MSGVAL_VOPDONE		3			// from 966
#define	_SHARED_MSGVAL_END			9
#define	_SHARED_MSGVAL_SIZE			4

#define	_SHARED_MSGVAL_BSUPDATE		0xF
#define	_SHARED_MSGVAL_BSDONE		0xF			// from 946


#define	_SHARED_MSGVAL_ERROR_NOTDS		-1		// from 966
#define	_SHARED_MSGVAL_ERROR_NOTVOL		-2		// from 966
#define	_SHARED_MSGVAL_ERROR_VOPDEC		-3		// from 966
#define	_SHARED_MSGVAL_ERROR_BSUPDATE	-15		// from 966

#define _SHARED_MSG_IDLE			0			// from 946
#define _SHARED_MSG_SEND			1			// from 946
#define _SHARED_MSG_ENC_INIT		2			// from 946
#define _SHARED_MSG_ENC_MAIN		3			// from 946

#define _SHARED_MSG_ENC_BUSY		4
#define _SHARED_MSG_ENC_DONE		5
#define _SHARED_MSG_ENC_READY		6
#define _SHARED_MSG_ENC_IDLE		0

#define   _SHARED_MSGVAL_DISPLAYCUR 1
#define   _SHARED_MSGVAL_DISPLAYREF 0
#define   _SHARED_MSGVAL_IVOP       0
#define   _SHARED_MSGVAL_PVOP       1
#define   _SHARED_MSGVAL_BVOP       2
#define   _SHARED_MSGVAL_NVOP       3
#define   _SHARED_MSGVAL_NOTHING    4

#define T5MP4_PROFILE_S_L0    0x08 /* simple */
#define T5MP4_PROFILE_S_L1    0x01
#define T5MP4_PROFILE_S_L2    0x02
#define T5MP4_PROFILE_S_L3    0x03
#define T5MP4_PROFILE_ARTS_L1 0x91 /* advanced realtime simple */
#define T5MP4_PROFILE_ARTS_L2 0x92
#define T5MP4_PROFILE_ARTS_L3 0x93
#define T5MP4_PROFILE_ARTS_L4 0x94
#define T5MP4_PROFILE_AS_L0   0xf0 /* advanced simple */
#define T5MP4_PROFILE_AS_L1   0xf1
#define T5MP4_PROFILE_AS_L2   0xf2
#define T5MP4_PROFILE_AS_L3   0xf3
#define T5MP4_PROFILE_AS_L4   0xf4

#define ENC_INIT		11
#define ENC_MAIN	12

/* from A926 to A946 */
#define TCC_VCORE_SHARED_COMMAND_CODEC_INIT                 1
#define TCC_VCORE_SHARED_COMMAND_CODEC_CLOSE                2
#define TCC_VCORE_SHARED_COMMAND_CODEC_RESET                3
#define TCC_VCORE_SHARED_COMMAND_CODEC_ENC                  4
#define TCC_VCORE_SHARED_COMMAND_CODEC_DEC                  5

/* from A946 to A926 */
#define TCC_VCORE_SHARED_RESPONSE_CODEC_INIT                1
#define TCC_VCORE_SHARED_RESPONSE_CODEC_CLOSE               2
#define TCC_VCORE_SHARED_RESPONSE_CODEC_RESET               3
#define TCC_VCORE_SHARED_RESPONSE_CODEC_DEC                 4
#define TCC_VCORE_SHARED_RESPONSE_CODEC_ENC                 5

#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE1_DONE         1
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE2_DONE         2
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE3_DONE         3
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE4_DONE         4

#define TCC_VCORE_SHARED_CODEC_STATUS_MORE_DATA_REQUIREMENT 5
#define TCC_VCORE_SHARED_CODEC_STATUS_ENDOFSEQUENCE         6 

#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE1_ERROR       -1
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE2_ERROR       -2
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE3_ERROR       -3
#define TCC_VCORE_SHARED_CODEC_STATUS_VOPTYPE4_ERROR       -4

#define TCC_VCORE_SHARED_CODEC_STATUS_ERROR1               -5
#define TCC_VCORE_SHARED_CODEC_STATUS_ERROR2               -6
#define TCC_VCORE_SHARED_CODEC_STATUS_ERROR3               -7
#define TCC_VCORE_SHARED_CODEC_STATUS_ERROR4               -8


#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG1ENC                1
#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG1DEC                2

#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG2ENC                3
#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG2DEC                4

#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG4ENC                5
#define TCC_VCORE_SHARED_CODEC_TYPE_MPEG4DEC                6

#define TCC_VCORE_SHARED_CODEC_TYPE_DIVXENC                 7
#define TCC_VCORE_SHARED_CODEC_TYPE_DIVXDEC                 8

#define TCC_VCORE_SHARED_CODEC_TYPE_H263ENC                 9
#define TCC_VCORE_SHARED_CODEC_TYPE_H263DEC                10

#define TCC_VCORE_SHARED_CODEC_TYPE_H264ENC                11
#define TCC_VCORE_SHARED_CODEC_TYPE_H264DEC                12

#define TCC_VCORE_SHARED_CODEC_TYPE_WMV9ENC                13
#define TCC_VCORE_SHARED_CODEC_TYPE_WMV9DEC                14

/////////////////////////////////////////////////////////////////////////////
/* Command from MCORE */
#define TC_JPEGENC_CMD_BASE						0x10000000
#define TC_JPEGENC_CMD_INIT						TC_JPEGENC_CMD_BASE+1
#define TC_JPEGENC_CMD_PUTHEADER				TC_JPEGENC_CMD_BASE+2
#define TC_JPEGENC_CMD_FRAMEENCODE				TC_JPEGENC_CMD_BASE+3
#define TC_JPEGENC_CMD_FINISH					TC_JPEGENC_CMD_BASE+4
#define TC_JPEGENC_CMD_CLOSE					TC_JPEGENC_CMD_BASE+5
#define TC_JPEGENC_CMD_THUMBNAIL				TC_JPEGENC_CMD_BASE+6
#define TC_JPEGENC_CMD_VCORE_READY				TC_JPEGENC_CMD_BASE+21
#define TC_JPEGENC_CMD_VCORE_BUSY				TC_JPEGENC_CMD_BASE+22
#define TC_JPEGENC_CMD_VCORE_DONE				TC_JPEGENC_CMD_BASE+23

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////Interrupt Interface////////////////////////////////
//Channel #1 : main command
#define TC_JPEGDEC_CMD_BASE						0x11000000
#define TC_JPEGDEC_CMD_INIT						TC_JPEGDEC_CMD_BASE+1
#define TC_JPEGDEC_CMD_DECODE						TC_JPEGDEC_CMD_BASE+2
#define TC_JPEGDEC_CMD_VCORE_READY				TC_JPEGDEC_CMD_BASE+3
#define TC_JPEGDEC_CMD_VCORE_BUSY				TC_JPEGDEC_CMD_BASE+4
#define TC_JPEGDEC_CMD_VCORE_DONE				TC_JPEGDEC_CMD_BASE+5

//Channel #2 : Input Buffer Channel
//From V-core
#define TC_JPEGDEC_VCORE_INPUT_REQUEST_1			TC_JPEGDEC_CMD_BASE+11
#define TC_JPEGDEC_VCORE_INPUT_REQUEST_2			TC_JPEGDEC_CMD_BASE+12
//From M-core
#define TC_JPEGDEC_MCORE_INPUT_FILL_DONE_1		TC_JPEGDEC_CMD_BASE+13
#define TC_JPEGDEC_MCORE_INPUT_FILL_DONE_2		TC_JPEGDEC_CMD_BASE+14

//Channel #3 : Output Buffer Channel
//From V-core
#define TC_JPEGDEC_VCORE_OUTPUT_REQUEST_1		TC_JPEGDEC_CMD_BASE+21
#define TC_JPEGDEC_VCORE_OUTPUT_REQUEST_2		TC_JPEGDEC_CMD_BASE+22
//From M-core
#define TC_JPEGDEC_MCORE_OUTPUT_FLUSH_DONE_1	TC_JPEGDEC_CMD_BASE+23
#define TC_JPEGDEC_MCORE_OUTPUT_FLUSH_DONE_2	TC_JPEGDEC_CMD_BASE+24

//Channel #4 : Control Channel
#define TC_JPEGDEC_VCORE_INPUT_PROCESS			TC_JPEGDEC_CMD_BASE+31
#define TC_JPEGDEC_VCORE_OUTPUT_PROCESS			TC_JPEGDEC_CMD_BASE+32

//Merged Channel
#define TC_JPEGDEC_V_CORE_OUT_0_IN_0	TC_JPEGDEC_CMD_BASE + 40
#define TC_JPEGDEC_V_CORE_OUT_0_IN_1	TC_JPEGDEC_CMD_BASE + 41
#define TC_JPEGDEC_V_CORE_OUT_0_IN_2	TC_JPEGDEC_CMD_BASE + 42
#define TC_JPEGDEC_V_CORE_OUT_1_IN_0	TC_JPEGDEC_CMD_BASE + 43
#define TC_JPEGDEC_V_CORE_OUT_1_IN_1	TC_JPEGDEC_CMD_BASE + 44
#define TC_JPEGDEC_V_CORE_OUT_1_IN_2	TC_JPEGDEC_CMD_BASE + 45
#define TC_JPEGDEC_V_CORE_OUT_2_IN_0	TC_JPEGDEC_CMD_BASE + 46
#define TC_JPEGDEC_V_CORE_OUT_2_IN_1	TC_JPEGDEC_CMD_BASE + 47
#define TC_JPEGDEC_V_CORE_OUT_2_IN_2	TC_JPEGDEC_CMD_BASE + 48

//Merged Channel
#define TC_JPEGDEC_M_CORE_OUT_0_IN_0	TC_JPEGDEC_CMD_BASE + 50
#define TC_JPEGDEC_M_CORE_OUT_0_IN_1	TC_JPEGDEC_CMD_BASE + 51
#define TC_JPEGDEC_M_CORE_OUT_0_IN_2	TC_JPEGDEC_CMD_BASE + 52
#define TC_JPEGDEC_M_CORE_OUT_1_IN_0	TC_JPEGDEC_CMD_BASE + 53
#define TC_JPEGDEC_M_CORE_OUT_1_IN_1	TC_JPEGDEC_CMD_BASE + 54
#define TC_JPEGDEC_M_CORE_OUT_1_IN_2	TC_JPEGDEC_CMD_BASE + 55
#define TC_JPEGDEC_M_CORE_OUT_2_IN_0	TC_JPEGDEC_CMD_BASE + 56
#define TC_JPEGDEC_M_CORE_OUT_2_IN_1	TC_JPEGDEC_CMD_BASE + 57
#define TC_JPEGDEC_M_CORE_OUT_2_IN_2	TC_JPEGDEC_CMD_BASE + 58

/////////////////////////////////////////////////////////////////////////////
/* Command from MCORE */
#define TC_MPEG4ENC_CMD_BASE					0x20000000
#define TC_MPEG4ENC_CMD_INIT					TC_MPEG4ENC_CMD_BASE+1
#define TC_MPEG4ENC_CMD_PUTHEADER				TC_MPEG4ENC_CMD_BASE+2
#define TC_MPEG4ENC_CMD_FRAMEENCODE				TC_MPEG4ENC_CMD_BASE+3
#define TC_MPEG4ENC_CMD_FINISH					TC_MPEG4ENC_CMD_BASE+4
#define TC_MPEG4ENC_CMD_CLOSE					TC_MPEG4ENC_CMD_BASE+5

#define TC_MPEG4ENC_CMD_VCORE_READY				TC_MPEG4ENC_CMD_BASE+21
#define TC_MPEG4ENC_CMD_VCORE_BUSY				TC_MPEG4ENC_CMD_BASE+22
#define TC_MPEG4ENC_CMD_VCORE_DONE				TC_MPEG4ENC_CMD_BASE+23


/**************************************************************
 * TYPE
 *************************************************************/
typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;
typedef char	S8;
typedef short	S16;
typedef int	S32;

typedef struct	{
	unsigned int	msg_from926[4];
	unsigned int	msg_from946[4];
} MsgBlk;

typedef struct	{
	unsigned int	addr;
	unsigned int	length;
	unsigned int	cur_offset;
	unsigned int	end;
	unsigned int	bssize;
	unsigned int	remained_bytes;
} hwBS;

typedef	union	{
	unsigned char 	cuTypeParam[400];
	signed 	 char 	csTypeParam[400];
	int		isTypeParam[100];
	unsigned int	iuTypeParam[100];
}TCC_SHARE_MEM;

typedef	struct	_IPCHeader {
	U32		sdram_addr;
	U32		heap;
	U32		internal_heap;
	
	U32		nFramenum;
	U16		nCodedWidthY;
	U16		nCodedHeightY;
	U16		nCodedWidthC;
	U16		nCodedHeightC;

	//2 for Frame Information
	U8 *		pFRefFrame;					// forward reference frame address
	U8 *		pBRefFrame;					// backward reference frame address
	U8 *		pCurFrame;						// current frame base address

	//2 for Bitstream Buffer Management
	U8 *		pBitStreamBase;					// bitstream base address
	U32		nBitStreamIdx;					// bitstream offset for slice_header code
	U32		nBitStreamSize;					// bitstream size
	U32		nBitStreamMask;					//

	//2 for Misc. Information
	U8		nSecondField;
	U8		nMpeg2Flag;
	U8		block_count;
}	IPCHeader;

typedef	struct	_IPCHeaderInfo {
	U8		f_code[2][2];
	U8		intra_dc_precision;
	U8		top_field_first;
	U8		chroma_format;
	U8		picture_structure;
	U8		picture_coding_type;
	U8		frame_pred_frame_dct;
	U8		forward_f_code;
	U8		full_pel_forward_vector;
	U8		concealment_motion_vectors;
	U8		intra_vlc_format;
	U8		full_pel_backward_vector;
	U8		backward_f_code;
	U8		q_scale_type;
	U8		alternate_scan;
	
	U8		intra_quantizer_matrix[64];
	U8		non_intra_quantizer_matrix[64];
	U8		chroma_intra_quantizer_matrix[64];
	U8		chroma_non_intra_quantizer_matrix[64];
}	IPCHeaderInfo;
typedef struct	{
	U32 		type;
	U32 		out_flag;
	U32 		used_bytes;
	U32 		numframes;
	U32		general[8];
}	IPCSubStatus;

typedef struct	{
	IPCHeader			Header;
	IPCHeaderInfo		HeaderInfo;
	IPCSubStatus		SubStatus;
} TCC_MPEG2_SHARE_MEM;

typedef struct	{
	t5mp4_dec_create_t 	_shared_t5mp4_dec_create;		
	t5mp4_dec_out_t 	_shared_t5mp4_dec_out;	
	unsigned int *		_macroblock_info;
	t5mp4_image_t cur;
	t5mp4_image_t refn0;	
	t5mp4_image_t refn1;	
}TCC_MPEG4_SHARE_MEM;

typedef struct _TC_JPEGENC_SharedMem{
	unsigned int		Command_from_MCORE[16];
	unsigned int		Command_from_VCORE[16];
	unsigned int		SendData_from_MCORE[16];
	unsigned int		SendData_from_VCORE[16];
}TC_JPEGENC_SharedMem;

typedef union tagTCCSharedInstance {
	TCC_SHARE_MEM 		_shared_dec_mem;
	TCC_MPEG4_SHARE_MEM 	_shared_mp4_dec_mem;
	TCC_MPEG2_SHARE_MEM	_shared_mp2_dec_mem;
	TC_JPEGENC_SharedMem	_shared_jpg_enc_mem;
} uTCCSharedInstance;	

typedef volatile struct{
	// Order is never changed!!!
	hwBS gHwBS;
	MsgBlk gMsg;
	uTCCSharedInstance guTCCSharedInstance;
}sSHAREDMEM;

typedef volatile struct {
	unsigned int	SRCBASEY;		
	unsigned int	SRCBASEU;		
	unsigned int	SRCBASEV;		
	unsigned int	SRCSIZE;		
	unsigned int	SRCOFF;		
	unsigned int	SRCCFG;		
	unsigned int	UNUSED1;
	unsigned int	UNUSED2;     
	unsigned int	DSTBASEY;		
	unsigned int	DSTBASEU;		
	unsigned int	DSTBASEV;		
	unsigned int 	DSTSIZE;		
	unsigned int	DSTOFF;		
	unsigned int	DSTCFG;		
	unsigned int	UNUSED3;
	unsigned int	UNUSED4;
	unsigned int	MSCINF;		
	unsigned int	MSCCTR;		
	unsigned int	MSCSTR;		
	unsigned int	STROBE;	
}MSC_REG;

#endif
#endif
#endif
