
#ifndef _VIRTUAL_H_
#define _VIRTUAL_H_

#include <windows.h>

#if defined(__TCC89XX_WINCE__)||defined(__TCC88XX_WINCE__)

	#define __HDMI_INCLUDE__
	//#define __ROTATE_INCLUDE__                    // this define used at TCMovieManager Video Rotation
	//#define __2DACCELATE_CHECK__				// After BSP v2664
	//#define __SCALER1_INCLUDE__					// this define used at TCMovieManager CM2MScaler Class - CaptureScreenByScaler();
	//#define __WITH_PHOTOPLAY__
#ifdef __TCC89XX_WINCE__
	//#define DUAL_DISPLAY                        // Video output to LCD and CVBS 
#elif __TCC88XX_WINCE__
	//#define DUAL_DISPLAY                        // Default on TWS88X            Video output to LCD and CVBS 
#endif
	
	//#define __3D_DISPLAY_INCLUDE__                // this define used at TCMovieManager for 3D video play

	#ifdef __HDMI_INCLUDE__
		#define __HDMI_SUBTITLE__
	#endif

	#ifdef __HDMI_INCLUDE__
	#define SCALER_YSIZE	0x00200000
	#else
	#define SCALER_YSIZE	0x00100000	
	#endif

	#define UV_FACTOR  1			// M2M Scaler Output UV data Size factor. YUV422->1, YUV420 -> 2
									// YUV422[2]->(Y[1]+U[1/2]+V[1/2]) -> Y[1] + UV[1]
									// YUV420[1+1/2]->(Y[1]+U[1/4]+V[1/4] -> Y[1] + UV[1/2]

	#define SCALER_UVSIZE	    SCALER_YSIZE/UV_FACTOR
	#define SCALER_USIZE		SCALER_YSIZE/UV_FACTOR/2
	#define SCALER_BUFF_SIZE	(SCALER_YSIZE + SCALER_UVSIZE)

	#ifdef __ROTATE_INCLUDE__
	#define ROTATE_BUFF_SIZE	SCALER_BUFF_SIZE
	#else
	#define ROTATE_BUFF_SIZE	0
	#endif	
	
	#define HDMI_SUBTITLE_SCALE_RATIO 2
	#ifdef __HDMI_SUBTITLE__	
		#if (HDMI_SUBTITLE_SCALE_RATIO==2)
		#define HDMI_SUBTITLE_BUFF_SIZE 0x00200000 // if HDMI_SUBTITLE_SCALE_RATIO is 2 set 0x00200000
		#else if(HDMI_SUBTITLE_SCALE_RATIO==1)
		#define HDMI_SUBTITLE_BUFF_SIZE 0x00400000 // if HDMI_SUBTITLE_SCALE_RATIO is 1 set 0x00400000
		#endif	
	#else
	#define HDMI_SUBTITLE_BUFF_SIZE 0
	#endif	

	#ifdef __SCALER1_INCLUDE__ 
	#define SCALER1_BUFF_SIZE	SCALER_BUFF_SIZE
	#define JPEG_ENC_BUFF_SIZE	0x00080000
	#else
	#define SCALER1_BUFF_SIZE	0
	#define JPEG_ENC_BUFF_SIZE	0
	#endif

	#ifdef DUAL_DISPLAY	
	#undef SCALER1_BUFF_SIZE
	#define SCALER1_BUFF_SIZE SCALER_BUFF_SIZE
	#define SCALER2_BUFF_SIZE SCALER_BUFF_SIZE
	#else
	#define SCALER2_BUFF_SIZE 0
	#endif

	#ifdef __WITH_PHOTOPLAY__
	#define PHOTODEC_BUFF_SIZE 0x02000000
	#else
	#define PHOTODEC_BUFF_SIZE	0
	#endif

	#ifdef __3D_DISPLAY_INCLUDE__
	#define _3D_FRAME_BUFFER_SIZE SCALER_BUFF_SIZE
	#else
	#define _3D_FRAME_BUFFER_SIZE 0
	#endif
	
	// Current Offset = Previous Offset + Previous Region Size(Not Current Region Size)
	///////////////////////////////////////////////////////////////////////////
	#define SCALER0_MEM0_OFFSET			(PHOTODEC_BUFF_SIZE)
	#define SCALER0_MEM1_OFFSET			(SCALER0_MEM0_OFFSET + SCALER_BUFF_SIZE)

	#define SCALER1_MEM0_OFFSET			(SCALER0_MEM1_OFFSET + SCALER_BUFF_SIZE)
	#define SCALER1_MEM1_OFFSET			(SCALER1_MEM0_OFFSET + SCALER1_BUFF_SIZE)

	#define ROTATE1_MEM_OFFSET			(SCALER1_MEM1_OFFSET + SCALER2_BUFF_SIZE)
	#define ROTATE2_MEM_OFFSET			(ROTATE1_MEM_OFFSET + ROTATE_BUFF_SIZE)

	#define JPEG_ENC_MEM_OFFSET 		(ROTATE2_MEM_OFFSET + ROTATE_BUFF_SIZE)

	#define HDMI_SUBTITLE_MEM_OFFSET1	(JPEG_ENC_MEM_OFFSET + JPEG_ENC_BUFF_SIZE)
	#define HDMI_SUBTITLE_MEM_OFFSET2	(HDMI_SUBTITLE_MEM_OFFSET1 + HDMI_SUBTITLE_BUFF_SIZE)

	#define _3D_FRAME_BUFFER1_OFFSET		(HDMI_SUBTITLE_MEM_OFFSET2 + HDMI_SUBTITLE_BUFF_SIZE)
	#define _3D_FRAME_BUFFER2_OFFSET		(_3D_FRAME_BUFFER1_OFFSET + _3D_FRAME_BUFFER_SIZE)

	#define	CAPTURE_MEM_OFFSET			(_3D_FRAME_BUFFER2_OFFSET + _3D_FRAME_BUFFER_SIZE)

	#define VIDEO_DEC_MEM_OFFSET		(CAPTURE_MEM_OFFSET + SCALER_BUFF_SIZE)

	#define CAMERA_MEM_OFFSET			(VIDEO_DEC_MEM_OFFSET)
	#define CAMERA_MEM_SIZE				(0x900000)	// preview 3 frame(max 1280x729 YUV422) + capture 1 frame(max 1600x1200)
	#define VIDEO_ENC_MEM_OFFSET		(CAMERA_MEM_OFFSET + CAMERA_MEM_SIZE)


typedef struct _UID_MEM {
	DWORD dwHwBaseAddress;
	DWORD dwAllocBaseAddress;
	DWORD dwSize;
}UID_MEM;

extern volatile LPVOID SetVirtual(unsigned int HwBaseAddress, unsigned int nSize);
extern void FreeVirtual(LPVOID pVirtualAddress, unsigned int nSize);

#else

#include "Pkfuncs.h"

#define SHARED_MEM_PHYSADDR		0xA0000000

//#define RAM128
#ifdef RAM128
#define HW_MEM_BASE			0x27C00000
#else
#define HW_MEM_BASE			0x23C00000 
#endif

#define HW_MEM_LIMIT			0x00400000

#define OUTBUFFER_BASE			HW_MEM_BASE 
#define OUTBUFFER_LIMIT			0x00300000
#define INBUFFER_BASE			(HW_MEM_BASE + OUTBUFFER_LIMIT) 
#define INBUFFER_LIMIT			0x00040000 
#define DATABUFFER_BASE			(HW_MEM_BASE + OUTBUFFER_LIMIT + INBUFFER_LIMIT)
#define DATABUFFER_LIMIT		0x00040000
#define SCALER_OUT1			(HW_MEM_BASE + OUTBUFFER_LIMIT + INBUFFER_LIMIT + DATABUFFER_LIMIT)
#define SCALER_OUT2			(HW_MEM_BASE + OUTBUFFER_LIMIT + INBUFFER_LIMIT + DATABUFFER_LIMIT + SCALER_LIMIT)
#define SCALER_LIMIT			0x00040000

#define HW_MEM_BASE_TCC79X		0x20100000 // for TCC79x (defaul value)
#define SCALER_TCC79X_OUT1		0x20480000 // for TCC79x (default value) 
#define SCALER_TCC79X_OUT2		0x204C0000 // for TCC79x (default value) 

#define DFLT_BASE_WMV9_ROBASE			0x10004000
#define DFLT_BASE_MPEG2_ROBASE			0x10008000
#define DFLT_BASE_MPEG2_HTBASE			0x10016000
#define DFLT_BASE_MPEG4SP_ROBASE		0x10004000 
#define DFLT_BASE_MPEG4SP_HTBASE		0x10016000

#define MBMEM0BASE				0x10010000
#define MBMEM0BASE_SIZE				6144

#define DFLT_BASE_JPEGDEC_ROBASE		0x10008000
#define DFLT_BASE_JPEGDEC_ROBASE_LIBV033 0x10004000

#define	DFLT_BASE_JPEGENC_ROBASE		0x10008000
#define PHY_ADDR_R_PINGPONG_1			0x10014000
#define PHY_ADDR_R_PINGPONG_2			0x10016000

extern volatile LPVOID SetVirtual(unsigned int physical_addr, unsigned int mem_size);
extern volatile LPVOID SetVirtualCache(unsigned int physical_addr, unsigned int mem_size);
extern void FreeVirtual(LPVOID virtual_ptr, unsigned int mem_size);

#endif	// __TCC89XX_WINCE__

#endif	// _VIRTUAL_H_
