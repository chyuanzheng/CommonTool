// MailBox.h: interface for the CMailBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MAILBOX_H_
#define _MAILBOX_H_

#include <windows.h>

#if defined(__TCC79XX_WINCE__) 
#include "TCC79x_Physical.h"
#elif defined(__TCC78XX_WINCE__) 
#include "TCC78xPhysical.h"
#endif

typedef	volatile struct {
	unsigned	TXD;
	unsigned	uRsv1[7];
	unsigned	RXD;
	unsigned	uRsv2[7];
	unsigned	CTR;
	unsigned	STR;
} sMBOX;

enum {
	MBOX_MAIN,
	MBOX_SUB
};

typedef struct {
	HANDLE	MailBoxEvent;
	int		Irq;
	int		Sysintr;
} IntrParam;
	

int			IO_MB_InitMBOX(unsigned uMainSub);
void			IO_MB_DeInitMBOX(void);
unsigned int	IO_MB_RcvMSG(unsigned int *pData);
unsigned int	IO_MB_SendMSG (unsigned int *pData, unsigned int nNum);

#endif

