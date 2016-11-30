#include <windows.h>

#ifndef _TCCUTIL_H_
#define _TCCUTIL_H_

typedef unsigned char	U8;
typedef unsigned short	U16;
typedef unsigned int	U32;

#define	BITSET(X, MASK)				( (X) |= (U32)(MASK) )
#define	BITSCLR(X, SMASK, CMASK)	( (X) = ((((U32)(X)) | ((U32)(SMASK))) & ~((U32)(CMASK))) )
#define	BITCSET(X, CMASK, SMASK)	( (X) = ((((U32)(X)) & ~((U32)(CMASK))) | ((U32)(SMASK))) )
#define	BITCLR(X, MASK)				( (X) &= ~((U32)(MASK)) )
#define	BITXOR(X, MASK)				( (X) ^= (U32)(MASK) )

#define MCHw1(x)  ( (0x00000001<<(x)))
#define	MCHw0(x)  (~(0x00000001<<(x)))

#if !defined (SAFE_RELEASE)
#define SAFE_RELEASE(x) if(x){x->Release();x=NULL;}
#endif

#if !defined (SAFE_DELETE)
#define SAFE_DELETE(x) if(x){delete(x);x = NULL;}
#endif

extern void* TC_Allocate_Memory (unsigned int iSize);
extern int TC_Deallocate_Memory(void *pvPtr);
extern int TC_Check_Pointer(unsigned uNum, char *pSrc, unsigned uLine, ...);

#endif