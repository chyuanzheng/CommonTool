#ifndef _HWJPG_MAIN_H_
#define _HWJPG_MAIN_H_

#include "Common/TCC89x_Physical.h"
#include "Common/TCC89x_Structures.h"
#include "Common/Ioctl_code.h"

#include "TCC89X_HW_JPG_Proc.h"
#include "TCC89X_HW_JPG_Decode.h"

/**************************************************************
 * Global TYPE
 *************************************************************/
typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;

/**************************************************************
 * Define
 *************************************************************/
#define	HwREG(X)					*(volatile unsigned long *)(X)
#define	BITSET(X, MASK)				( (X) |= (U32)(MASK) )
#define	BITSCLR(X, SMASK, CMASK)	( (X) = ((((U32)(X)) | ((U32)(SMASK))) & ~((U32)(CMASK))) )
#define	BITCSET(X, CMASK, SMASK)	( (X) = ((((U32)(X)) & ~((U32)(CMASK))) | ((U32)(SMASK))) )
#define	BITCLR(X, MASK)				( (X) &= ~((U32)(MASK)) )
#define	BITXOR(X, MASK)				( (X) ^= (U32)(MASK) )

#define PHYSICAL_REG_SIZE			1024*4

/******************************************************************************
* typedefs & structure
******************************************************************************/

enum{
	PHY_MEMORY_NO_ERROR = 0,
	PHY_MEMORY_OPEN_ERR,	
	PHY_MEMORY_MALLOC_ERR,
	PHY_MEMORY_REG_ERROR 
};

const int ZOOM_IN_LIMIT = 4;

inline int Screen2Image(int length, double ratioZoom){return static_cast<int>(length/ratioZoom);}
inline int Image2Screen(int length, double ratioZoom){return static_cast<int>(length*ratioZoom);}

inline int MAKEMULTI_16(int value){return (value<<4)>>4;}
inline int MAKEMULTI_8(int value){return (value<<3)>>3;}

#endif