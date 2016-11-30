#include <windows.h>

#include ".\include\Clock.H"
#include ".\include\ioctl_pwrstr.h"
#include ".\include\windev.h"
#include "pkfuncs.h"
#include "ioctl_code.h"
#include ".\include\globals.h"
#include ".\include\ioctl_ckcstr.h"
#include "virtual.h"

//////////////////////////////////////////////////////////////////////////////////////
// TCCxxx style API
#ifdef __TCC88XX_WINCE__
int TWS_CKC_CheckChipsetVerion()
{
	volatile unsigned int *pChipsetVersionValue = (volatile unsigned int *)SetVirtual(0x30000000,sizeof(unsigned int)*40);
	unsigned int ChipsetVersionValue = *(pChipsetVersionValue+35);
	int ChipsetVersion = TCC88X_AX;

	switch(ChipsetVersionValue)
	{
	case 0x10004444: //AX
		ChipsetVersion = TCC88X_AX;
		printf("%s Set Clock for TCC88X_AX\n",TWS_CKC_LOG);
		break;
	case 0x10004450: //XX
		ChipsetVersion = TCC88X_XX;
		printf("%s Set Clock for TCC88X_XX\n",TWS_CKC_LOG);
		break; 	
	default:
		printf("%s TCC88X Unknown version\n",TWS_CKC_LOG);
	}	
	FreeVirtual((void*)pChipsetVersionValue, sizeof(unsigned int)*40);

	return 	ChipsetVersion;
}
#endif

int TWS_CKC_GetBUS(int pckname,int *pckcfreq)
{     
	int iBusClock = 0;

#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_CLOCKINFO;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
	if(pckcfreq!=NULL)
	{
		*pckcfreq = pCKCINFO.currentbusfreq;
	}

	printf("======================================\n");
	printf("%s PLL0 Clock       : %10d[MHz]\n",TWS_CKC_LOG,pCKCINFO.currentsysfreq/10000);
	printf("%s CPU Clock        : %10d[MHz]\n",TWS_CKC_LOG,pCKCINFO.currentcpufreq/10000);
	printf("%s Memory BUS Clock : %10d[MHz]\n",TWS_CKC_LOG,pCKCINFO.currentbusfreq/10000);
	printf("======================================\n");

	iBusClock = pCKCINFO.currentbusfreq;
#endif

	return iBusClock;
}

int TWS_CKC_GetCPU()
{     
	int iCPUClock = 0;

#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_CLOCKINFO;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	printf("%s CPU   : %10d\n",TWS_CKC_LOG,pCKCINFO.currentcpufreq/10000);

	iCPUClock = pCKCINFO.currentcpufreq;
#endif

	return iCPUClock;
}

int TWS_CKC_GetMemoryBus()
{     
	int iVBusClock = 0;

#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_CLOCKINFO;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	printf("%s Memory Bus   : %d[MHz]\n",TWS_CKC_LOG,pCKCINFO.currentbusfreq/10000);

	iVBusClock = pCKCINFO.currentbusfreq;
#endif

	return iVBusClock;
}

int TWS_CKC_GetVBusClock()
{
	return TWS_CKC_GetFBUS(CLKCTRL6);
}

void TWS_CKC_SetFCPU(int pckcfreq)
{
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_CHANGECPU;
	pCKCIOCTL.cpuvalue = pckcfreq;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	TWS_CKC_GetCPU();
#endif
}

void TWS_CKC_SetFMBUS(int pckcfreq)
{
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_CHANGEMEM;
	pCKCIOCTL.busvalue = pckcfreq;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	TWS_CKC_GetMemoryBus();
#endif
}

char *szFBusName[]={
	"CPU   ",
	"DDI   ",
	"BUS   ",
	"GRP   ",
	"IOB   ",
	"VBUS  ",
	"VCODEC",
	"SMU   ",
};
	
void TWS_CKC_SetFBUS(int pckname,int mode, int pckcfreq, int source)
{           
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl    pCKCIOCTL;
	stckcinfo	 pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode	=  IOCTL_CKC_SET_CHANGEFBUS;
	pCKCIOCTL.fbusname	= pckname;
	pCKCIOCTL.fbusfreq	= pckcfreq;
	pCKCIOCTL.mode      = mode;

	BOOL ret = KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	// check a frequency	
	//printf("%s Set FBUS : %d, %10d\n",TWS_CKC_LOG, pckname, TWS_CKC_GetFBUS(pckname));

	// check a relative PMU status
	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_PMUPOWER;
	pCKCIOCTL.pmuoffname = pckname;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	if(pckname < sizeof(szFBusName)/sizeof(szFBusName[0]))
	{
		printf("%s Set FBus %s PMU : %s\n",TWS_CKC_LOG,szFBusName[pckname],pCKCINFO.state?"Disable":"Enable");
	}
#endif
}

int TWS_CKC_GetFBUS(int pckname)
{                     
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode =  IOCTL_CKC_GET_FBUS;  
	pCKCIOCTL.fbusname = pckname;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	return pCKCINFO.fbusfreq;
#else
	return 0;
#endif
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
void TWS_CKC_SetDynamicModeForVPU(unsigned int mode, unsigned int dynamicmax, unsigned int dynamicmin, unsigned int dynamiccycle)
{
#ifdef CKC_DRIVER_INCLUDE
#ifdef __TCC89XX_WINCE__
	stckcioctl pCKCIOCTL;
	stckcinfo  pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode	  = IOCTL_CKC_SET_CHANGEFBUS;
	
	if(mode==DYNAMIC_MD)
	{
		pCKCIOCTL.fbusname	  = CLKCTRL6;
		pCKCIOCTL.dynamicmax  = dynamicmax;
        pCKCIOCTL.dynamicmin  = dynamicmin;
        pCKCIOCTL.dynamiccycle= dynamiccycle;
        pCKCIOCTL.mode        = mode;
		KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
	}
	// check a frequency	
	//printf("%s MODE=%d\n\t Dynamic Max=%d, Min=%d, cycle=%d\n",TWS_CKC_LOG, mode, dynamicmax, dynamicmin, dynamiccycle);
#endif
#endif
}

void TWS_CKC_SetDynamicVPUOn(void)
{
#ifdef __TCC89XX_WINCE__
	int iVCoreSource = VCORE_HIGH_CKC_SRC;

#ifdef __TCC88XX_WINCE__
	if(TWS_CKC_CheckChipsetVerion()==TCC88X_XX)
	{
		iVCoreSource = DIRECTPLL4;
	}
#endif
	
	TWS_CKC_SetFBUS(CLKCTRL6, NORMAL_MD, 2340000, iVCoreSource); // FBUS_VCODEC
#endif
}

//////////////////////////////////////////////////////////////////////////////////////
void TWS_CKC_SetVPU_Init(void)
{
}

void TWS_CKC_SetVPU_DeInit(void)
{
}

void TWS_CKC_SetVPUOff(void)
{
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl    pCKCIOCTL;
	stckcinfo	 pCKCINFO;
	unsigned long returnedbyte;

	pCKCIOCTL.ioctlcode	=  IOCTL_CKC_SET_VIDEOCFGPWDN;
	pCKCIOCTL.videobuscfgname = VIDEOBUSCFG_PWDNVIDEOCODEC;
	pCKCIOCTL.mode = 0;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	/*pCKCIOCTL.ioctlcode	=  IOCTL_CKC_SET_FBUS;
	pCKCIOCTL.fbusname	= CLKCTRL6;
	pCKCIOCTL.fbusfreq	= 2340000;
	pCKCIOCTL.fbusenable	= 0;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);*/
#endif
}

void TWS_CKC_SetVPUOn(void)
{
#ifdef CKC_DRIVER_INCLUDE
	stckcioctl    pCKCIOCTL;
	stckcinfo	 pCKCINFO;
	unsigned long returnedbyte;
	
	pCKCIOCTL.ioctlcode	=  IOCTL_CKC_SET_VIDEOCFGPWDN;
	pCKCIOCTL.videobuscfgname = VIDEOBUSCFG_PWDNVIDEOCODEC;
	pCKCIOCTL.mode = 1;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	/*pCKCIOCTL.ioctlcode	=  IOCTL_CKC_SET_FBUS;
	pCKCIOCTL.fbusname	= CLKCTRL6;
	pCKCIOCTL.fbusfreq	= 2340000;
	pCKCIOCTL.fbusenable	= 1;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);*/
#endif
}
//////////////////////////////////////////////////////////////////////////////////////

void TWS_CKC_SetFBUSForVPUOn(void)
{
#ifdef CKC_DRIVER_INCLUDE
	int iVBusClock;
	int iVCoreClock;
	int iVBusSource;
	int iVCoreSource;

	if(TWS_CKC_GetMemoryBus() >= 3300000 )
	{
		iVBusClock   = VBUS_HIGH_CKC;
		iVBusSource  = VBUS_HIGH_CKC_SRC;
		iVCoreClock  = VCORE_HIGH_CKC;
		iVCoreSource = VCORE_HIGH_CKC_SRC;
	}
	else
	{
		iVBusClock   = VBUS_LOW_CKC;
		iVBusSource  = VBUS_LOW_CKC_SRC;
		iVCoreClock  = VCORE_LOW_CKC;
		iVCoreSource = VCORE_LOW_CKC_SRC;
	}

#ifdef __TCC88XX_WINCE__
	if(TWS_CKC_CheckChipsetVerion()==TCC88X_XX)
	{
		iVBusSource  = DIRECTPLL4;
		iVCoreSource = DIRECTPLL4;
	}
#endif

	TWS_CKC_SetFBUS(CLKCTRL5, NORMAL_MD, iVBusClock,  iVBusSource); // FBUS_VBUS
	TWS_CKC_SetFBUS(CLKCTRL6, NORMAL_MD, iVCoreClock, iVCoreSource); // FBUS_VCODEC

	printf("======================================\n");
	printf("%s VPU Bus Clock   : %d[MHz]\n",TWS_CKC_LOG,iVBusClock/10000);
	printf("%s VPU Bus Source  : PLL%d\n",TWS_CKC_LOG,iVBusSource);
	printf("%s VPU Core Clock  : %d[MHz]\n",TWS_CKC_LOG,iVCoreClock/10000);
	printf("%s VPU Core Source : PLL%d\n",TWS_CKC_LOG,iVCoreSource);
	printf("======================================\n");
#endif
}

void TWS_CKC_SetFBUSForVPUOff(void)
{
#ifdef CKC_DRIVER_INCLUDE
	TWS_CKC_SetFBUS(CLKCTRL5, NORMAL_MD, 0, DIRECTXIN); // FBUS_VBUS
	TWS_CKC_SetFBUS(CLKCTRL6, NORMAL_MD, 0, DIRECTXIN); // FBUS_VCODEC

	printf("======================================\n");
	printf("%s VPU Bus Clock   : %d[MHz]\n",TWS_CKC_LOG,0/10000);
	printf("%s VPU Bus Source  : DIRECTXIN\n",TWS_CKC_LOG);
	printf("%s VPU Core Clock  : %d[MHz]\n",TWS_CKC_LOG,0/10000);
	printf("%s VPU Core Source : DIRECTXIN\n",TWS_CKC_LOG);
	printf("======================================\n");
#endif
}

void TWS_CKC_SetFBUSForVPU(int VBUS, int VCODEC)
{
#ifdef CKC_DRIVER_INCLUDE
	int iVBusSource  = VBUS_LOW_CKC_SRC;
	int iVCoreSource = VCORE_LOW_CKC_SRC;

#ifdef __TCC88XX_WINCE__
	if(TWS_CKC_CheckChipsetVerion()==TCC88X_XX)
	{
		iVBusSource  = DIRECTPLL4;
		iVCoreSource = DIRECTPLL4;
	}
#endif

	printf("%s VBus : %d, Vore %d\n",TWS_CKC_LOG,VBUS,VCODEC);
	TWS_CKC_SetFBUS(CLKCTRL5, NORMAL_MD, VBUS,  iVBusSource); // FBUS_VBUS
	TWS_CKC_SetFBUS(CLKCTRL6, NORMAL_MD, VCODEC, iVCoreSource); // FBUS_VCODEC
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int TWS_CKC_GetGraphicBus()
{     
	int iGraphicBusClock = 0;
#ifdef CKC_DRIVER_INCLUDE
	unsigned long returnedbyte;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_CLOCKINFO;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
	printf("%s Graphic Bus Clock : %d[MHz]\n",TWS_CKC_LOG,pCKCINFO.grpfreq/10000);

	iGraphicBusClock = pCKCINFO.grpfreq;
#endif

	return iGraphicBusClock;
}

void TWS_CKC_SetFBUSForGRPOn(void)
{
#ifdef CKC_DRIVER_INCLUDE
	int iGRPClock;
	int iGRPClockSource;

	if(TWS_CKC_GetMemoryBus() >= 3300000 ) // This is for TCC89x only
	{
		// Set Clock for Full HD
		iGRPClock       = GRP_HIGH_CKC;
		iGRPClockSource = GRP_HIGH_CKC_SRC;
	}
	else
	{
		// Set Clock for HD		
		iGRPClock       = GRP_LOW_CKC;
		iGRPClockSource = GRP_LOW_CKC_SRC;
	}

#ifdef __TCC88XX_WINCE__
	if(TWS_CKC_CheckChipsetVerion()==TCC88X_XX)
	{
		iGRPClockSource  = DIRECTPLL4;
	}
#endif

	TWS_CKC_SetFBUS(CLKCTRL3, NORMAL_MD, iGRPClock, iGRPClockSource); // FBUS_GRP

	printf("======================================\n");
	printf("%s Set Graphic bus Clock    : %d[MHz]\n",TWS_CKC_LOG,iGRPClock/10000);
	printf("%s Graphic bus Clock Source : PLL%d \n",TWS_CKC_LOG,iGRPClockSource);
	printf("======================================\n");

	//Set Overlay Mixer ON, 3D block OFF
	TWS_CKC_SetOverlayMix(1);
	TWS_CKC_Set3DGPU(0);
#endif
}

void TWS_CKC_SetFBUSForGRPOff(void)
{
#ifdef CKC_DRIVER_INCLUDE
	//Remark:: If set BSP_MAX_FGRP_EN=1, Ignore
	printf("%s Disable Graphic bus\n",TWS_CKC_LOG);

	TWS_CKC_SetOverlayMix(0);//Set Overlay Mixer OFF
	TWS_CKC_SetFBUS(CLKCTRL3, NORMAL_MD, 0, DIRECTXIN); 
#endif
}

char *DDIBusName[]={
	"CIF  ",
	"VIQE ",
	"LCDC0",
	"LCDC1",
	"LCDSI",
	"MSC0 ",
	"MSC1 ",
	"DDIC ",
	"HDMI "
};

void TWS_CKC_SetDDIBUS(int ddibusname, unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
	int retVal = -1;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;
#ifdef __TCC89XX_WINCE__
	if((ddibusname < DDIPWDN_CIF) || (ddibusname >= DDIPWDN_STEPMAX))
	{
		printf("%s Invalid DDI BUS : %d\n",TWS_CKC_LOG, ddibusname);
		return;
	}
#endif
	/* mode : 0(ddi bus disable), 1(ddi bus enable) */
	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_DDIPWDN;
	pCKCIOCTL.ddipdname = ddibusname;	
	pCKCIOCTL.mode = (mode>0)?1:0;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_DDIPWDN;	
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	if(pCKCIOCTL.ddipdname < (sizeof(DDIBusName)/5))
	{
		printf("%s Set %s DDI BUS : %s\n" ,TWS_CKC_LOG, DDIBusName[pCKCIOCTL.ddipdname],pCKCINFO.retVal?"Off":"On");
	}
	else
	{
		printf("%s Set No.%d DDI BUS : %s\n" ,TWS_CKC_LOG, pCKCIOCTL.ddipdname,pCKCINFO.retVal?"Off":"On");
	}
#endif
}

void TWS_CKC_SetIOBUS(int iobusname, unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
	int retVal = -1;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;
#ifdef __TCC89XX_WINCE__
	if((iobusname < RB_USB11H) || (iobusname >= RB_ALLPERIPERALS))
	{
		printf("%s Set Invalid IO BUS : %d\n",TWS_CKC_LOG, iobusname);
		return;
	}
#endif
	/* mode : 0(io bus disable), 1(io bus enable) */
	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_PERIBUS;
	pCKCIOCTL.prbname = iobusname;
	pCKCIOCTL.mode = (mode>0)?1:0;

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);

	pCKCIOCTL.ioctlcode = IOCTL_CKC_GET_PERIBUS;
	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
	if(pCKCINFO.retVal == 0)
		printf("%s %d IOBUS : Disable\n",TWS_CKC_LOG, pCKCIOCTL.prbname);
	else 
		printf("%s %d IOBUS : Enable\n",TWS_CKC_LOG, pCKCIOCTL.prbname);
#endif
}

void TWS_CKC_SetETC(unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
	int retVal = -1;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_ETCBLOCK;
	pCKCIOCTL.etcblock = (mode>0)?ETCMASK_USBPHYON:ETCMASK_USBPHYOFF;

	printf("%s Set USB Phy %s\n",TWS_CKC_LOG, (mode>0)?"On":"Off");

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
#endif
}

void TWS_CKC_SetOverlayMix(unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
#ifdef __TCC89XX_WINCE__
	int retVal = -1;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_ETCBLOCK;
	pCKCIOCTL.etcblock = (mode>0)?ETCMASK_OVERLAYMIXERON:ETCMASK_OVERLAYMIXEROFF;

	printf("%s Set OverlayMix %s\n",TWS_CKC_LOG, (mode>0)?"On":"Off");

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
#elif __TCC88XX_WINCE__
	TWS_CKC_SetIOBUS(RB_OVERAYMIXERCONTROLLER,mode);
#endif
#endif
}

void TWS_CKC_Set3DGPU(unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
	int retVal = -1;
	stckcioctl pCKCIOCTL;
	stckcinfo pCKCINFO;
	unsigned long	returnedbyte;

	pCKCIOCTL.ioctlcode = IOCTL_CKC_SET_ETCBLOCK;
	pCKCIOCTL.etcblock = (mode>0)?ETCMASK_3DGPUON:ETCMASK_3DGPUOFF;

	printf("%s Set 3D GPU : %s\n",TWS_CKC_LOG, (mode>0)?"On":"Off");

	KernelIoControl(IOCTL_HAL_TCCCKC, &pCKCIOCTL, sizeof(stckcioctl), &pCKCINFO, sizeof(stckcinfo), &returnedbyte);
#endif
}

void TWS_CKC_SetPWRControl(unsigned char ucDeviceID,unsigned char mode)
{
#ifdef CKC_DRIVER_INCLUDE
	stpwrioctl	pwrioctl;	// for input

	pwrioctl.deviceid = ucDeviceID;
	
	if(mode==0)
	{
		pwrioctl.cmd = PWR_STATUS_OFF;
	}
	else if(mode==1)
	{
		pwrioctl.cmd = PWR_CMD_ON;
	}
	
	KernelIoControl(IOCTL_PWR_CONTROL, &pwrioctl, sizeof(pwrioctl), NULL, NULL, NULL);
#endif
}

void TWS_CKC_SetMSCBUSOn(int iMSCNum)
{
	TWS_CKC_SetDDIBUS(DDIPWDN_MSCL0+iMSCNum,1);
}

void TWS_CKC_SetMSCBUSOff(int iMSCNum)
{
	TWS_CKC_SetDDIBUS(DDIPWDN_MSCL0+iMSCNum,0);
}

void TWS_CKC_SetLCDCBUSOn(int iLCDCNum)
{
	TWS_CKC_SetDDIBUS(DDIPWDN_LCDC0+iLCDCNum,1);
}

void TWS_CKC_SetLCDCBUSOff(int iLCDCNum)
{
	TWS_CKC_SetDDIBUS(DDIPWDN_LCDC0+iLCDCNum,0);
}

void TWS_CKC_SetVIQEBUSOn()
{
	TWS_CKC_SetDDIBUS(DDIPWDN_VIQE,1);
}

void TWS_CKC_SetVIQEBUSOff()
{
	TWS_CKC_SetDDIBUS(DDIPWDN_VIQE,0);
}

