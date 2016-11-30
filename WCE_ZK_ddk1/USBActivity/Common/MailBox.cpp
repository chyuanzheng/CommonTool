// MailBox.cpp: implementation of the CMailBox class.
//
//////////////////////////////////////////////////////////////////////

#include "MailBox.h"
#if defined(__TCC79XX_WINCE__) 
#include "TCC79x_Physical.h"
#define HwIEN_SCORE HwINT_SCORE
#define _STATIC_INTERRUPT_
//#define _MASK_INTERRUPT_
#else // TCC78x
#include "TCC78xPhysical.h"
//#define _STATIC_INTERRUPT_
// CAUTION: To use _STATIC_INTERRUPT_, 
// Must change setting in \PLATFORM\Tcc7801\Src\Common\Intr\intr.c
#endif

#ifdef _STATIC_INTERRUPT_
#define STATIC_INTERRUPT_USED
#define SYSINTR_SCORE_ALARM 43
#endif

#include "Virtual.h"
#include "TCCUtil.h"
#include ".\include\clock.h"

#if defined(__TCC79XX_WINCE__)||defined(__TCC78XX_WINCE__)

volatile sMBOX *pMBOX = NULL;
volatile sHwINT *pHwINT = NULL;
IntrParam IntrInfo;

int IO_MB_InitMBOX(unsigned uMainSub)
{
	TWS_CKC_Enable_SubCoreMailBox();

	pMBOX	= (uMainSub == MBOX_MAIN) ? (volatile sMBOX *)SetVirtual((unsigned int)&HwMBOX_BASE,sizeof(sMBOX)) : (sMBOX *)SetVirtual( (unsigned int)&HwSUBMBOX_BASE, sizeof(sMBOX));
	if(!pMBOX)
		return -1;
	BITSCLR(pMBOX->CTR, HwMBOXCTR_FLUSH|HwMBOXCTR_IEN, HwMBOXCTR_OEN);

	if (uMainSub == MBOX_MAIN)
	{
#ifdef MESSAGE_HANDLING_BY_POLLING
		pHwINT	= (volatile sHwINT*)SetVirtual( (unsigned int)&HwVIC_BASE, sizeof(sHwINT) ) ;
		BITSET(pHwINT->IEN, HwIEN_SCORE);
#else
		memset(&IntrInfo, 0, sizeof(IntrParam));

		pHwINT	= (volatile sHwINT*)SetVirtual( (unsigned int)&HwVIC_BASE, sizeof(sHwINT) ) ;

#ifdef _MASK_INTERRUPT_
		BITCLR(pHwINT->IRQMSK, HwIEN_SCORE);
#else
		BITCLR(pHwINT->IEN, HwIEN_SCORE);
#endif
		BITSET(pHwINT->ICLR, HwIEN_SCORE);
		BITCLR(pHwINT->MODE, HwIEN_SCORE);
		BITCLR(pHwINT->MODEA, HwIEN_SCORE);
		BITSET(pHwINT->IPOL, HwIEN_SCORE);
		BITSET(pHwINT->ISEL, HwIEN_SCORE);
		BITSET(pHwINT->IRQMSK, HwIEN_SCORE);
#endif		

#ifndef STATIC_INTERRUPT_USED
		IntrInfo.Irq = IRQ_SCORE;
		if( !KernelIoControl(IOCTL_HAL_REQUEST_SYSINTR, &IntrInfo.Irq, sizeof(DWORD), &IntrInfo.Sysintr, sizeof(DWORD), NULL) ) {
			return -1;
		}
		
		IntrInfo.MailBoxEvent = CreateEvent(0, FALSE, FALSE, NULL);
		if ( !(InterruptInitialize(IntrInfo.Sysintr, IntrInfo.MailBoxEvent, 0, 0)) ) {
			return -1;
		}
#else		
		IntrInfo.MailBoxEvent = CreateEvent(0, FALSE, FALSE, NULL);
		if ( !(InterruptInitialize(SYSINTR_SCORE_ALARM, IntrInfo.MailBoxEvent, 0, 0)) ) {
			return -1;
		}
#endif

#ifdef _MASK_INTERRUPT_
		BITSET(pHwINT->IRQMSK, HwIEN_SCORE);
#else
		BITSET(pHwINT->IEN, HwIEN_SCORE);
#endif
	}
	else
	{
		pHwINT	= (volatile sHwINT*)SetVirtual( (unsigned int)&HwSUBVIC_BASE, sizeof(sHwINT) );

		BITSET(pHwINT->IPOL, 0x8000);		// active low
		BITSET(pHwINT->ISEL, 0x8000);		// IRQ
		BITSET(pHwINT->MODE, 0x8000);		// level-triggered
		BITSET(pHwINT->IEN, 0x8000);		// Interrupt enabled.);
	}

	return 0;
}

void IO_MB_DeInitMBOX()
{
	TWS_CKC_Disable_SubCoreMailBox();

#ifndef STATIC_INTERRUPT_USED
	KernelIoControl(IOCTL_HAL_RELEASE_SYSINTR, &IntrInfo.Sysintr, sizeof(DWORD), NULL, NULL, NULL);
#endif
	if( IntrInfo.MailBoxEvent ) {
		CloseHandle(IntrInfo.MailBoxEvent);
	}
	if(pMBOX) {	FreeVirtual((void*)pMBOX, sizeof(sMBOX));	pMBOX = NULL; 	}
	if(pHwINT) { FreeVirtual((void*)pHwINT, sizeof(sHwINT));	pHwINT = NULL;	}	
}

unsigned int IO_MB_RcvMSG(unsigned int *pData)
{
	unsigned int  idx;
	unsigned int  nRet=0;

// MESSAGE_HANDLING_BY_POLLING
#ifdef  MESSAGE_HANDLING_BY_POLLING
	int state=1;

	/* nRet is the number of received data from another processor */
	idx = 0;	
	while(state)
	{
		nRet = (unsigned int)(pMBOX->STR & (MCHw1(23)|MCHw1(22)|MCHw1(21)|MCHw1(20)))>>20;
		if( nRet ) break;
		Sleep(10);
		idx++;
		if (idx > 100)	return 0;
	}

	for ( idx = 0 ; idx < nRet ; idx ++ ) 
	{
		*(pData + idx) = (unsigned int)(pMBOX->RXD);
		/* read the received data */
	}
#else
	DWORD	ret;
	ret = WaitForSingleObject(IntrInfo.MailBoxEvent, 1000);
	if( ret == WAIT_TIMEOUT ) {
		printf("MailBox:[WAIT_TIMEOUT]\r\n");
		//nRet = (unsigned int)(pMBOX->STR & (MCHw1(23)|MCHw1(22)|MCHw1(21)|MCHw1(20)))>>20;
		return 0;
	}
	
	nRet = (unsigned int)(pMBOX->STR & (MCHw1(23)|MCHw1(22)|MCHw1(21)|MCHw1(20)))>>20;
	for ( idx = 0 ; idx < nRet ; idx ++ ) {
		*(pData + idx) = (unsigned int)(pMBOX->RXD);
		/* read the received data */
	}
#ifndef STATIC_INTERRUPT_USED
	InterruptDone(IntrInfo.Sysintr);
#else

#ifdef _MASK_INTERRUPT_
	BITSET(pHwINT->IRQMSK, HwIEN_SCORE);
#else
	InterruptDone(SYSINTR_SCORE_ALARM);
#endif

#endif
#endif
	return nRet;
}

unsigned int IO_MB_SendMSG(unsigned int *pData, unsigned int nNum)
{

//	#ifdef MESSAGE_HANDLING_BY_POLLING
	unsigned int   idx, i, j;
	unsigned int   nControl;

	/* wait until the transmit fifo being empty */
	i = j = 0;
	while(1)
	{
  		if ( pMBOX->STR & MCHw1(0) ) break;
			i++;

		if ( !(i & 0x3F) )
		{
			j++;
			Sleep(10);
		}
		if (j > 100)
			return	0;
  	}

	nControl = pMBOX->CTR;
	nControl &= MCHw0(5);
	
	/* clear OEN */
	pMBOX->CTR = nControl;

	for ( idx = 0 ; idx < nNum ; idx ++ ) 
	{
		pMBOX->TXD = *(pData + idx);
		/* write data to transmit
		but, if the "OEN" is '0', the status is not transferred to another processor */
	}

	nControl |= MCHw1(5);
	pMBOX->CTR	= nControl;
	/* set OEN
	Just after, the status will be passed to another processor */

	return (nNum);
}
#endif
