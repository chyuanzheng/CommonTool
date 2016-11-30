#ifndef	_TYPEDEFINE_H_
#define	_TYPEDEFINE_H_

#include <dmo.h>

#define	MAX_FRAMES_IN_STREAMBUF		100//4
#define	INBUF_BLOCK_SIZE				(4*1024)			// should be 2 ^ N
#define	NUM_OF_BLOCK					(64*4)				// should be 2 ^ N
#define	SIZE_OF_BITSTREAM_BUFFER	(INBUF_BLOCK_SIZE * NUM_OF_BLOCK)
#define	MAX_WIDTH		720
#define	MAX_HEIGHT		576
#define	BITSTREAM_ADDR_MASK			(~(SIZE_OF_BITSTREAM_BUFFER-1))
#define	DECODER_OPEN		((0x1)<<0)

#define	LIST_NEXT(x)		((x) = (x)->pNext)
#define	LIST_PREV(x)		((x) = (x)->pPrev)

typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;

#define MCHw1(x)  ( (0x00000001<<(x)))
#define	MCHw0(x)  (~(0x00000001<<(x)))

#define	PICTURE_START_CODE		0x00000100
#define	SLICE_START_CODE_MIN		0x00000101
#define	SLICE_START_CODE_MAX		0x000001AF
#define	USER_DATA_START_CODE		0x000001B2
#define	SEQUENCE_HEADER_CODE	0x000001B3
#define	SEQUENCE_ERROR_CODE		0x000001B4
#define	EXTENSION_START_CODE		0x000001B5
#define	SEQUENCE_END_CODE		0x000001B7
#define	GROUP_START_CODE			0x000001B8
#define	SYSTEM_START_CODE_MIN	0x000001B9
#define	SYSTEM_START_CODE_MAX	0x000001FF

#define	ISO_END_CODE				0x000001B9
#define	PACK_START_CODE			0x000001BA
#define	SYSTEM_START_CODE		0x000001BB

#define	VIDEO_ELEMENTARY_STREAM	0x000001E0
/* picture structure */
#define	TOP_FIELD		1
#define	BOTTOM_FIELD	2
#define	FRAME_PICTURE	3

/* chroma_format */
#define CHROMA420 1
#define CHROMA422 2
#define CHROMA444 3

/* extension start code IDs */
#define SEQUENCE_EXTENSION_ID                    1
#define SEQUENCE_DISPLAY_EXTENSION_ID            2
#define QUANT_MATRIX_EXTENSION_ID                3
#define COPYRIGHT_EXTENSION_ID                   4
#define SEQUENCE_SCALABLE_EXTENSION_ID           5
#define PICTURE_DISPLAY_EXTENSION_ID             7
#define PICTURE_CODING_EXTENSION_ID              8
#define PICTURE_SPATIAL_SCALABLE_EXTENSION_ID    9
#define PICTURE_TEMPORAL_SCALABLE_EXTENSION_ID  10

/* picture coding type */
#define	I_TYPE		1
#define	P_TYPE		2
#define	B_TYPE		3
#define	D_TYPE		4

/* scalable_mode */
#define	SC_NONE	0
#define	SC_DP		1
#define	SC_SPAT	2
#define	SC_SNR		3
#define	SC_TEMP	4

//Error Code Definition	: < 0
#define	ERR_EMPTY_BITSTREAM				(-1)		// Bitstream Empty, But Decode Command Executed
#define	UNEXPECTED_STREAM_HEADER		(-2)		// Header of Bitstream is neither SEQUENCE_HEADER nor PICTURE_START
#define	ERR_EMPTY_OUTPUT_BUFFER			(-3)

#define	ERR_SEQ_IN_PROGRESS		(-4) //(0x90)

#define ZIG_ZAG                                  0

#define	DECODER_OPEN		((0x1)<<0)
#define	SEQUENCE_OPEN		((0x1)<<1)

//
#define Q_DEFAULT_SIZE			100
/*enum {
	ST_ONEFRM_EMPTY = 0,
	ST_ONEFRM_LOADED,
	ST_ONEFRM_ERROR
};*/
enum {
	ST_ONEFRM_EMPTY = 0,
	ST_ONEFRM_LOADING,
	ST_ONEFRM_LOADED,
	ST_ONEFRM_DECODING,
	ST_ONEFRM_DECODED,
	ST_ONEFRM_ERROR,
};

typedef	struct	_HeaderInfo {
	///////////////////////////////////////////////////
	//	Sequence Layer Information
	///////////////////////////////////////////////////
	/* ISO/IEC 13818-2 section 6.2.2.1:  sequence_header() */
	U16		horizontal_size;			// 12 bits + horizontal_size_extension(2 bits)
	U16		vertical_size;				// 12 bits + vertical_size_extension(2 bits)
	U8		aspect_ratio_information;		// 4 bits
	U8		frame_rate_code;			// 4 bits
	U32		bit_rate_value;				// 18 bits + bit_rate_extension(10 bits)
	U32		vbv_buffer_size;			// 10 bits + vbv_buffer_size_extension (8 bits)
	U8		constrained_parameters_flag;		// 1 bits

	/* ISO/IEC 13818-2 section 6.2.2.3:  sequence_extension() */
	U8		load_intra_quantizer_matrix;		// 1 bit
	U8		load_non_intra_quantizer_matrix;	// 1 bit
	U8		load_chroma_intra_quantizer_matrix;	// 1 bit
	U8		load_chroma_non_intra_quantizer_matrix;	// 1 bit

	U8		profile_and_level_indication;		// 8 bits
	U8		progressive_sequence;			// 1 bit

	U8		low_delay;				// 1 bit
	U8		frame_rate_extension_n;			// 2 bits
	U8		frame_rate_extension_d;			// 5 bits

	/* ISO/IEC 13818-2 section 6.2.2.4:  sequence_display_extension() */
	U8		video_format;  				// 3 bits
	U8		color_description;			// 1 bits
	U8		color_primaries;			// 8 bits
	U8		transfer_characteristics;		// 8 bits
	U8		matrix_coefficients;			// 8 bits
	U16		display_horizontal_size;		// 14 bits
	U16		display_vertical_size;			// 14 bits

	/* ISO/IEC 13818-2 section 6.2.2.5: sequence_scalable_extension() header */
	U8		scalable_mode;				// 2 bits ( added by '1' )
	U8		layer_id;				// 4 bits
	U16		lower_layer_prediction_horizontal_size;	// 14 bits
	U16		lower_layer_prediction_vertical_size;	// 14 bits
	U8		horizontal_subsampling_factor_m;	// 5 bits
	U8		horizontal_subsampling_factor_n;	// 5 bits
	U8		vertical_subsampling_factor_m;		// 5 bits
	U8		vertical_subsampling_factor_n;		// 5 bits

	///////////////////////////////////////////////////
	//	Picture Layer Information
	///////////////////////////////////////////////////
	/* ISO/IEC 13818-2 section 6.2.3: picture_header() */
	U16		temporal_reference;			// 10 bits
	U16		vbv_delay;				// 16 bits

	/* ISO/IEC 13818-2 section 6.2.3.1: picture_coding_extension() header */
	U8		repeat_first_field;			// 1 bit
	U8		chroma_420_type;			// 1 bit
	U8		progressive_frame;			// 1 bit
	U8		composite_display_flag;			// 1 bit
	U8		v_axis;					// 1 bit
	U8		field_sequence;				// 3 bits
	U8		sub_carrier;				// 1 bit
	U8		burst_amplitude;			// 7 bits
	U8		sub_carrier_phase;			// 8 bits

	/* ISO/IEC 13818-2 section 6.2.3.3: picture_display_extension() header */
	U16		frame_center_horizontal_offset[3];	// 16 bits
	U16		frame_center_vertical_offset[3];	// 16 bits

	/* ISO/IEC 13818-2 section 6.2.3.5: picture_spatial_scalable_extension() header */
	U16		lower_layer_temporal_reference;		// 10 bits
	U16		lower_layer_horizontal_offset;		// 15 bits
	U16		lower_layer_vertical_offset;		// 15 bits
	U8		spatial_temporal_weight_code_table_index;	// 2 bits
	U8		lower_layer_progressive_frame;		// 1 bits
	U8		lower_layer_deinterlaced_field_select;	// 1 bits

	/* ISO/IEC 13818-2 section 6.2.3.6: copyright_extension() header */
	U8		copyright_flag;				// 1 bits
	U8		copyright_identifier;			// 8 bits
	U8		original_or_copy;			// 1 bits
	U32		copyright_number_1;			// 20 bits
	U32		copyright_number_2;			// 22 bits
	U32		copyright_number_3;			// 22 bits

	/* ISO/IEC 13818-2 section 6.2.2.6: group_of_pictures_header()  */
	U8		drop_flag;				// 1 bits
	U8		hour;					// 5 bits
	U8		minute;					// 6 bits
	U8		sec;					// 6 bits
	U8		frame;					// 6 bits
	U8		closed_gop;				// 1 bits
	U8		broken_link;				// 1 bits

	/* ISO/IEC 13818-2 section 6.2.4: slice_header */
	U8		priority_breakpoint;			// 7 bits
	U8		intra_slice;				// 1 bit
	U8		quantizer_scale_code;			// 5 bits
	U8		quantizer_scale;			// derived value from quantizer_scale_code
}	HeaderInfo;

typedef	struct _OneFrameInfo {
	int							nState;
	int							nStart;
	int							nEnd;
	int							nOffset;
	int							nSize;
	int							nNowState;
	int							nNowIndex;

	// jinhong
	unsigned int					nCode;
	int							num;
	
	// for Time Stamp
	REFERENCE_TIME				nTimeStamp;		// 100ns unit in DShow
	
	struct _OneFrameInfo *	pNext;
	struct _OneFrameInfo *	pPrev;
}	OneFrameInfo;

typedef	struct	_DecoderInfo {
	U8		nNumBlocks;
	U8		mb_width;
	U8		mb_height;

	int		nTrueFrameNum;

	float		bit_rate;
	float		frame_rate; 
	U8		profile;
	U8		level;

	U32		nBitstreamFramenum;
	U8		nSequenceInProgress;
	U32		nSequenceFrameNum;
}	DecoderInfo;

typedef	struct _InBufferInfo {
	//2 for File Interface
	int						nFileDesc;
	int						nEndOfFile;
	
	//2 for Frame Management
	OneFrameInfo			pFrameInfo[MAX_FRAMES_IN_STREAMBUF];
	OneFrameInfo *		pFramePush;
	OneFrameInfo *		pFramePop;
	int					nFrameValidCount;
	REFERENCE_TIME		nTimeStamp;		// 100ns unit in DShow
	REFERENCE_TIME		nTimeLength;		// 100ns unit in DShow
	
	//2 for Buffer Management
	U32					nBfrFront;
	U32					nBfrRear;
	U32					nBfrFilled;
	
	//2 for Stream Buffer Management
	U8 *					pInBuffer;			// frame bitstream buffer ( word-aligned )
	
	//2 for Header Parsing
	U32					nBitFrameIdx;
	U32					Bfr;
	U32					Incnt;
	U32					Bitcnt;
	BOOL				nRound;
}	InBufferInfo;

#define	OUTBUFFER_MAX_COUNT				8

#define	OUTBUFFER_NOT_USED		(0x00000000)
#define	OUTBUFFER_DECODING		(0x00000001)
#define	OUTBUFFER_DISPLAYING		(0x00000002)
#define	OUTBUFFER_DISPLAYED		(0x00000004)

#define	OUTBUFFER_INVALID_INDEX		((unsigned char) 255)

typedef	struct _OutBufferElem {
	U8					nID;
	U8					nLock;
	REFERENCE_TIME		nTimeStamp;
	U8 *					pVirAddr;
	U8 *					pPhyAddr;
}	OutBufferElem;

typedef	struct _OutBufferEntry{
	OutBufferElem *			pOutBufferElem;
	struct _OutBufferEntry *	pPrev;
	struct _OutBufferEntry *	pNext;
}	OutBufferList;

typedef	struct _OutBufferInfo {
	//2 for Frame Memory
	OutBufferElem			mOutBufferElem[OUTBUFFER_MAX_COUNT];		// Max Frames
	OutBufferList			mOutBufferList[OUTBUFFER_MAX_COUNT];
	OutBufferList *		pOutBufferFront;
	OutBufferList *		pOutBufferRear;
	int					nOutBufValidCount;
	
	//2 for Video Processing
	U8 					nForward;				// Forward Reference Frame Pointer
	U8 					nBackward;				// Backward Reference Frame Pointer
	U8 					nCurrent;				// Current Frame Pointer
	U8 					nDisplay;				// Display Frame Pointer

	//2 for Frame Reordering
	U8					nIdxCurrent;			// Index of Current Frame
	U8					nIdxRef[2];				// Previous Reference Frame ( Previous I or P Frame )
}	OutBufferInfo;


#define RESERVED    -1 

#define PROFILE_422                             (128+5)
#define MAIN_LEVEL                              8

static double gpMPEG2_FrameRateTable[16] =
{
	0.0,
	((23.0*1000.0)/1001.0),
	24.0,
	25.0,
	((30.0*1000.0)/1001.0),
	30.0,
	50.0,
	((60.0*1000.0)/1001.0),
	60.0,

	RESERVED,
	RESERVED,
	RESERVED,
	RESERVED,
	RESERVED,
	RESERVED,
	RESERVED
};

/* default intra quantization matrix */
const	U8	default_intra_quantizer_matrix[64] =
	{
		8, 16, 19, 22, 26, 27, 29, 34,
		16, 16, 22, 24, 27, 29, 34, 37,
		19, 22, 26, 27, 29, 34, 34, 38,
		22, 22, 26, 27, 29, 34, 37, 40,
		22, 26, 27, 29, 32, 35, 40, 48,
		26, 27, 29, 32, 35, 40, 48, 58,
		26, 27, 29, 34, 38, 46, 56, 69,
		27, 29, 35, 38, 46, 56, 69, 83
	};

const	U8	default_scan[2][64] =
	{
		{ // Zig-Zag scan pattern
			0,1,8,16,9,2,3,10,17,24,32,25,18,11,4,5,
			12,19,26,33,40,48,41,34,27,20,13,6,7,14,21,28,
			35,42,49,56,57,50,43,36,29,22,15,23,30,37,44,51,
			58,59,52,45,38,31,39,46,53,60,61,54,47,55,62,63
		},
		{ // Alternate scan pattern
			0,8,16,24,1,9,2,10,17,25,32,40,48,56,57,49,
			41,33,26,18,3,11,4,12,19,27,34,42,50,58,35,43,
			51,59,20,28,5,13,6,14,21,29,36,44,52,60,37,45,
			53,61,22,30,7,15,23,31,38,46,54,62,39,47,55,63
		}
	};

#endif
