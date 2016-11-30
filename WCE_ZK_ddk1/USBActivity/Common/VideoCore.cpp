// VideoCore.cpp: implementation of the CVideoCore class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "VideoCore.h"
#include "Virtual.h"
#include "TCCUtil.h"

#if defined(__TCC79XX_WINCE__) 
#include "TCC79x_Physical.h"
typedef volatile struct{
	/* UNUSED must be declared to access BCLKCTR and SWRESET. see VirtualCopy()*/
	unsigned int UNUSED[6];	//0xF3000000 ~ 0xF3000014
	unsigned int BCLKCTR;	//0xF3000018
	unsigned int BCLKCTR1;	//0xF300001C
	unsigned int SWRESET;	//0xF3000020
	//skip other registers
}sCKCReg;
#elif defined(__TCC78XX_WINCE__) 
#include "TCC78xPhysical.h"
typedef volatile struct{
	/* UNUSED must be declared to access BCLKCTR and SWRESET. see VirtualCopy()*/
	unsigned int UNUSED[6];	//0xF3000000 ~ 0xF3000014
	unsigned int BCLKCTR;	//0xF3000018
	unsigned int SWRESET;	//0xF300001C
	//skip other registers
}sCKCReg;
#endif

typedef volatile struct{	
	unsigned int REMAP;	//0xF3005000
	unsigned int VCFG0;	//0xF3005004
	//skip other registers
}sSYSCReg;

#if defined(__TCC79XX_WINCE__)||defined(__TCC78XX_WINCE__)
int VCORE_Open(unsigned uCODEC, unsigned uCODE, unsigned uCODESize, unsigned int nROBASE,
								unsigned uCODE2, unsigned uCODESize2, unsigned int nROBASE2)
{
	volatile sCKCReg *pCKCReg = NULL;
	volatile sSYSCReg *pSYSCReg = NULL;
	volatile unsigned char *pSPBASE = NULL;
	volatile unsigned char *pSPBASE2 = NULL;
	
	//HwCLKCTRL
	pCKCReg = (volatile sCKCReg*)SetVirtual(0xF3000000,sizeof(sCKCReg));
	if(!pCKCReg)
		return -1;

	//HwREMAP
	pSYSCReg = (volatile sSYSCReg*)SetVirtual(0xF3005000,sizeof(sSYSCReg));
	if(!pSYSCReg)
	{
		FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
		return -1;
	}
	pSPBASE = (volatile unsigned char*)SetVirtual(nROBASE,uCODESize);
	if(!pSPBASE)
	{
		FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
		FreeVirtual((void*)pSYSCReg, sizeof(sSYSCReg));
		return -1;
	}
	if( uCODESize2 ) 
	{
		pSPBASE2 = (volatile unsigned char*)SetVirtual(nROBASE2,uCODESize2);
		if(!pSPBASE2)
		{
			FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
			FreeVirtual((void*)pSYSCReg, sizeof(sSYSCReg));
			FreeVirtual((void*)pSPBASE, uCODESize);
		}
	}
	BITSET( pCKCReg->SWRESET, HwSWRESET_VCH_ON|HwSWRESET_SUBPRO|HwSWRESET_SUBPROPERI );
	BITSET( pCKCReg->BCLKCTR, HwBCLKCTR_SUBPRO|HwBCLKCTR_VCH_ON|HwBCLKCTR_SUBPROPERI );
	pSYSCReg->VCFG0 = nROBASE;
	BITCLR( pCKCReg->SWRESET,  HwSWRESET_VCH_ON);	 // Release Reset to access the region of 0x10010000 ~ 0x10018000
	if ((uCODE|nROBASE) & 3)
	{
		printf("[Error!!] SubCore Code Base is not Aligned\n");
		Sleep(1000);
		return -1;
	}
	//CAPP_SetModeClock(0, 196, 98, VCORE_PRIORITY_CLOCK);
	memcpy( (void*)pSPBASE, (void*)uCODE, uCODESize);
	if(pSPBASE2)
	{
		memcpy( (void*)pSPBASE2, (void*)uCODE2,uCODESize2);
	}
	Sleep(10);
	BITCLR(pCKCReg->SWRESET, HwSWRESET_SUBPRO|HwSWRESET_SUBPROPERI);
	Sleep(10);

	FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
	FreeVirtual((void*)pSYSCReg, sizeof(sSYSCReg));
	FreeVirtual((void*)pSPBASE, uCODESize);
	if( pSPBASE2 )
		FreeVirtual((void*)pSPBASE2, uCODESize2);

	return 0;
}

void VCORE_Close()
{
	volatile sCKCReg *pCKCReg = NULL;
	volatile sSYSCReg *pSYSCReg = NULL;

	//HwCLKCTRL
	pCKCReg = (volatile sCKCReg*)SetVirtual(0xF3000000, sizeof(sCKCReg));
	if(!pCKCReg)
		return;
	//HwREMAP
	pSYSCReg = (volatile sSYSCReg*)SetVirtual(0xF3005000, sizeof(sSYSCReg));
	if(!pSYSCReg)
	{
		FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
		return;
	}
	BITSET( pCKCReg->SWRESET, HwSWRESET_VCH_ON|HwSWRESET_SUBPRO|HwSWRESET_SUBPROPERI );
	BITCLR( pCKCReg->BCLKCTR, HwBCLKCTR_SUBPRO|HwBCLKCTR_VCH_ON|HwBCLKCTR_SUBPROPERI );

	FreeVirtual((void*)pCKCReg, sizeof(sCKCReg));
	FreeVirtual((void*)pSYSCReg, sizeof(sSYSCReg));
}
#endif
