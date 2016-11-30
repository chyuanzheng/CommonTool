
#define 	T5MP4_BSMODE_CONT		0
#define	T5MP4_BSMODE_FRAME		1
#define	T5MP4_BSMODE_946		-1

typedef struct {
	unsigned char	*y;
	unsigned char	*u;
	unsigned char	*v;
} t5mp4_image_t;


/* not supported features - error return codes */
//NOT_SUPPORTED_FEATURE_NOTVIDEO : Video Object is not video
#define NOT_SUPPORTED_FEATURE_NOTVIDEO			-100
//NOT_SUPPORTED_FEATURE_NONREC : the shape of encoded frame is not rectangular.
#define NOT_SUPPORTED_FEATURE_NONREC			-101
//NOT_SUPPORTED_FEATURE_INTERLACE : Interlaced Mode(!= Progressive Mode)
//Interlaced Mode(!= Progressive Mode) uses two field frame instead of 1 frame.
#define NOT_SUPPORTED_FEATURE_INTERLACE			-102
//NOT_SUPPORTED_FEATURE_OBMC : represent for Overlapped Block Motion Compensation
#define NOT_SUPPORTED_FEATURE_OBMC				-103
//NOT_SUPPORTED_FEATURE_SPRITE : sprite object is encoded(invariant in time)
#define NOT_SUPPORTED_FEATURE_SPRITE				-104
//NOT_SUPPORTED_FEATURE_GREYSCALE : Grey scale video is encoded(there's no cb or cr)
#define NOT_SUPPORTED_FEATURE_GREYSCALE			-105
//NOT_SUPPORTED_FEATURE_QPEL : Quater-Pel is used in interpolation routine(only Half-pel and integer-pel are allowed)
#define NOT_SUPPORTED_FEATURE_QPEL				-106
//NOT_SUPPORTED_FEATURE_COMPLEXITY : If this field is set, additional "complexity estimation header" is present.
#define NOT_SUPPORTED_FEATURE_COMPLEXITY		-107
//NOT_SUPPORTED_FEATURE_DP : Data Partitioning
//The macroblock data is rearranged differently, specifically, motion vector data is separated from the texture data
#define NOT_SUPPORTED_FEATURE_DP					-108
//NOT_SUPPORTED_FEATURE_SCAL : (Scalabilty)Video is encoded in hierarchycal layer
#define NOT_SUPPORTED_FEATURE_SCAL				-109
//NOT_SUPPORTED_FEATURE_NEWPRED : One of error resilience function
#define NOT_SUPPORTED_FEATURE_NEWPRED			-111
//NOT_SUPPORTED_FEATURE_REDUCED_RESOL : (Reduced Resolution)
//Reduced Resolution : Resolution of current frame could be smaller than reference frames
#define NOT_SUPPORTED_FEATURE_REDUCED_RESOL		-112

#define	_SHARED_ERRORINFO_HANGCGI				-1001
/* T5MP4_DEC_CREATE param 1
	image width & height may be specified here when the dimensions are
	known in advance. */

// ------------------------------------
typedef struct {
	int version;
	int bs_mode;
	int width;     /* [in:opt] image width */
	int height;    /* [in:opt] image width */
	void *handle; /* [out]	   decore context handle */
	//t5mp4_image_t output; /* [in]     output image (written to) */
	t5mp4_image_t 	curfrm;

	t5mp4_image_t 	idle;
	t5mp4_image_t 	reffrm0;
	t5mp4_image_t 	reffrm1;

	//void *vmcbuffer;
	void *acbuf;
	//void *vmcbuffer;
	void *sdramaddr;

	void *bitstream;
	int length;
} t5mp4_dec_create_t;

// ------------------------------------
typedef struct {
	//int version;
	int general;         /* [in:opt] general flags */
	int bs_mode;		/* [in]		bitstream mode */
	//int out_flag;
	void *bitstream;     /* [in]     bitstream (read from)*/
	int length;          /* [in]     bitstream length */
	//t5mp4_image_t output; /* [in]     output image (written to) */
	t5mp4_image_t	*cur;
	t5mp4_image_t	*ref;
	int real_num_frames; /* [in] */
} t5mp4_dec_frame_t;


// ------------------------------------
typedef struct	{
	int type;
	union	{
		struct	{
			unsigned int	sw_refaddr;
			unsigned int	hw_refaddr;
		} vac;
		struct	{
			unsigned int	good;
			unsigned int	bad;
		} tmp;
	} data;
} t5mp4_dec_out_errorinfo_t;


// ------------------------------------
typedef struct {
	int type;
	int out_flag;
	unsigned int used_bytes;
	unsigned int numframes;
	union	{
		struct	{
			int time_base;
			int time_increment;
		} vop;
		struct	{
			int width;
			int height;
		} vol;
	} data;

	t5mp4_dec_out_errorinfo_t	error_info;
	int profile_and_level_indication;
} t5mp4_dec_out_t;
