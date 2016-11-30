// VideoCore.h: interface for the CVideoCore class.
//
//////////////////////////////////////////////////////////////////////

#ifndef	_VIDEOCORE_H_
#define	_VIDEOCORE_H_

int	VCORE_Open(unsigned uCODEC, unsigned uCODE, unsigned uCODESize, unsigned int nROBASE,
								unsigned uCODE2=0, unsigned uCODESize2=0, unsigned int nROBASE2=0);
void VCORE_Close();

#endif
