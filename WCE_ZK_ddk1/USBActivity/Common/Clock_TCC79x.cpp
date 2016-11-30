#include <windows.h>

#include ".\include\Clock.H"
#include ".\include\ioctl_pwrstr.h"
#include ".\include\windev.h"
#include "Virtual.h"
#include ".\include\globals.h"
#include ".\include\ioctl_ckcstr.h"

#include "pkfuncs.h"
#if defined(__TCC79XX_WINCE__)||defined(__TCC80XX_WINCE__)
#include ".\include\TCC_IoCtlCode.H"
#endif

//////////////////////////////////////////////////////////////////////////////////////
// Old style API

int SetAllIOClockOn()
{
	BOOL	state = false;
#ifdef __TCC79XX_WINCE__
	stCKCIOCTL stCKC;
	stCKCINFO	stCKCInfo;
	unsigned long	returnedbyte;

	stCKC.ControlCode = IOCTL_CKC_POWERON_APPCLKCTL;

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
#endif
	return state;
}

int SetAllIOClockOff()
{
	BOOL	state = false;
#ifdef __TCC79XX_WINCE__
	stCKCIOCTL stCKC;
	stCKCINFO	stCKCInfo;
	unsigned long	returnedbyte;	
	stCKC.ControlCode = IOCTL_CKC_POWEROFF_APPCLKCTL;

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
#endif
	return state;
}

//////////////////////////////////////////////////////////////////////////////////////
// Peripheral Clocks

int TWS_CKC_SetPeriBus(unsigned int PeriRBName,int Mode) 
{
#ifdef __TCC79XX_WINCE__	
	stCKCIOCTL stCKC;
	stCKCINFO	stCKCInfo;
	unsigned long	returnedbyte;
	BOOL	state;

	stCKC.ControlCode = IOCTL_CKC_SET_PERIBUSCLKCTL;
	stCKC.PeriRBName = PeriRBName;			//RB79_USB11HOST
	stCKC.Mode = Mode;										//Enable
	
	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);

	if(state == TRUE)
	{
		if(stCKCInfo.retVal == 1)
		{
			//printf("[TWS_CKC_SetPeriBus]Enable Success\n");
		}
		else if(stCKCInfo.retVal == 0)
		{
			printf("[TWS_CKC_SetPeriBus]Enable Fail");
			return -1;
		}
		else
		{
			printf("[TWS_CKC_SetPeriBus]invalid Set Peri. Bus %d\n",stCKCInfo.retVal);
			return -2;
		}
	}
	else
	{
		printf("[TWS_CKC_SetPeriBus]KernelIoControl Faile\n");
		return -3;
	}
#endif
	return 0;
}

int TWS_CKC_SetPeriCKC(unsigned int PeriClockName,unsigned int PeriClockSource, unsigned int PeriFreq) 
{
#ifdef __TCC79XX_WINCE__	
	stCKCIOCTL stCKC;
	stCKCINFO	stCKCInfo;
	unsigned long	returnedbyte;
	BOOL	state;

	stCKC.ControlCode = IOCTL_CKC_SET_PERICLOCK;
	stCKC.PeriClockName = PeriClockName;		//PERI79_USB11H
	stCKC.PeriClockSource = PeriClockSource;	//CLKFROM48M
	stCKC.PeriUnit = MHz;								//Mhz
	stCKC.PeriFreq = PeriFreq;						//48 (48Mhz)

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
	if(state != TRUE)
	{
		return -1;
	}
#endif
	return 0;
}

int TWS_CKC_Enable_SubCoreMailBox()
{
#ifdef __TCC79XX_WINCE__	
	printf("[TWS_CKC_Enable_SubCoreMailBox]\n");
	TWS_CKC_SetPeriBus(RB79_SUBPERI,ON);
	TWS_CKC_SetPeriBus(RB79_SUBPORCESSOR,ON);
	TWS_CKC_SetPeriBus(RB79_VIDEOCONHW,ON);
	TWS_CKC_SetPeriBus(RB79_MAILBOX,ON);
#endif	
	return 0;
}

int TWS_CKC_Disable_SubCoreMailBox()
{
#ifdef __TCC79XX_WINCE__	
	printf("[TWS_CKC_Disable_SubCoreMailBox]\n");
	TWS_CKC_SetPeriBus(RB79_SUBPERI,OFF);
	TWS_CKC_SetPeriBus(RB79_SUBPORCESSOR,OFF);
	TWS_CKC_SetPeriBus(RB79_VIDEOCONHW,OFF);
	TWS_CKC_SetPeriBus(RB79_MAILBOX,OFF);
#endif	
	return 0;
}


int TWS_CKC_Enable_M2MScaler()
{
#ifdef __TCC79XX_WINCE__	
	printf("[TWS_CKC_Enable_M2MScaler]\n");
	TWS_CKC_SetPeriBus(RB79_M2MSCALER,ON);
#endif	
	return 0;
}

int TWS_CKC_Disable_M2MScaler()
{
#ifdef __TCC79XX_WINCE__	
	printf("[TWS_CKC_Disable_M2MScaler]\n");
	TWS_CKC_SetPeriBus(RB79_M2MSCALER,OFF);
#endif	
	return 0;
}

int TWS_CKC_Enable_GPSB0(unsigned int New_Clock_Source, unsigned int New_Clock, int Mode)
{
#ifdef __TCC79XX_WINCE__		
	unsigned int Clock_Source = DIRECTXIN;
	unsigned int Clock = 12;

	printf("[TWS_CKC_Enable_GPSB0]\n");

	if(Mode)
	{
		Clock_Source = New_Clock_Source;
		Clock = New_Clock;
	}
	
	TWS_CKC_SetPeriBus(RB79_GPSB0,ON);
	TWS_CKC_SetPeriCKC(PERI79_GPSB0,Clock_Source,Clock);
#endif	
	return 0;
}

int TWS_CKC_Disable_GPSB0()
{
#ifdef __TCC79XX_WINCE__
	printf("[TWS_CKC_Disable_GPSB0]\n");
	TWS_CKC_SetPeriBus(RB79_GPSB0,OFF);
	TWS_CKC_SetPeriCKC(PERI79_GPSB0,DIRECTXIN,0);
#endif	
	return 0;
}

int TWS_CKC_Enable_GPSB1(unsigned int New_Clock_Source, unsigned int New_Clock, int Mode)
{
#ifdef __TCC79XX_WINCE__		
	unsigned int Clock_Source = DIRECTXIN;
	unsigned int Clock = 12;

	printf("[TWS_CKC_Enable_GPSB1]\n");

	if(Mode)
	{
		Clock_Source = New_Clock_Source;
		Clock = New_Clock;
	}
	
	TWS_CKC_SetPeriBus(RB79_GPSB1,ON);
	TWS_CKC_SetPeriCKC(PERI79_GPSB1,Clock_Source,Clock);
#endif	
	return 0;
}

int TWS_CKC_Disable_GPSB1()
{
#ifdef __TCC79XX_WINCE__	
	printf("[TWS_CKC_Disable_GPSB1]\n");
	TWS_CKC_SetPeriBus(RB79_GPSB1,OFF);
	TWS_CKC_SetPeriCKC(PERI79_GPSB1,DIRECTXIN,0);
#endif	
	return 0;
}



////////////////////////////////////////////////////////////////////////////////////
// CPU/BUS Clock

int SetSystemClockWithPriority(int m_CPU_Val,int m_BUS_Val,int Priority,int Set) 
{
	BOOL	state  = false;
	
#ifdef __TCC79XX_WINCE__
	// TODO: Add your control notification handler code here
	stCKCIOCTL stCKC;
	stCKCINFO	stCKCInfo;
	unsigned long	returnedbyte;			

	GetCurrentSystemClock(&stCKCInfo);

	if(stCKCInfo.CurrentCpuFreq/10000 == (unsigned int)m_CPU_Val 
		&& stCKCInfo.CurrentBusFreq/10000 == (unsigned int)m_BUS_Val
		&& stCKCInfo.CurrentPriority == (unsigned int)Priority)
	{
		return 1;
	}

	switch(Set)
	{
	case TWS_CLK_SET:
		{
			if(m_CPU_Val== 0 || m_BUS_Val == 0 ||
				m_CPU_Val > 498 || m_BUS_Val > 166)
			{
				printf("[TCW:SetSystemClockWithPriority]clock is wrong : %d,%d\n",m_CPU_Val,m_BUS_Val);
				return -1;
			}
			
			if(Priority != IDLE_PRIORITY)
			{
				// Set system(CPU/BUS) Clock	
				if(m_CPU_Val == 0 || m_BUS_Val == 0)
				{
					printf("[TCW:SetSystemClockWithPriority]CPU[%d],BUS[%d]\n",m_CPU_Val,m_BUS_Val);
					return -1;
				}
				printf("[TCW:SetSystemClockWithPriority]IOCTL_CKC_SET_SYSTEMCLKCTL\n");
				stCKC.ControlCode	=	IOCTL_CKC_SET_SYSTEMCLKCTL;				
			}
			else
			{
				stCKC.ControlCode	= IOCTL_CKC_SET_INITCLKCTL;
			}
			
			stCKC.CpuValue		=	m_CPU_Val;
			stCKC.BusValue		=	m_BUS_Val;
		}
		break;
	case TWS_CLK_RETURN:
		{
			printf("[TCW:SetSystemClockWithPriority]TWS_CLK_RETURN\n");
			// Return(Release) Clock
			stCKC.CpuValue		=	m_CPU_Val;
			stCKC.BusValue		=	m_BUS_Val;
			stCKC.ControlCode	=	IOCTL_CKC_SET_RETURNCLKCTL;
		}
		break;
	default : 
		printf("[TCW:SetSystemClockWithPriority]Unknown Clock operation : %d\n",Set);
		return -1;
	}

	if(Priority < IDLE_PRIORITY || Priority > MAX_PRIORITY 
		||((Priority == IDLE_PRIORITY) && (Set == TWS_CLK_RETURN)))
	{
		printf("[TCW:SetSystemClockWithPriority]Wrong Priority[%d]\n",Priority);
		return -1;
	}
	
	stCKC.Priority		=	Priority;

	printf("[TCW:SetSystemClockWithPriority]KernelIoControl : %d\n",Priority);
	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
	if(state != TRUE)
	{
		printf("[TCW:SetSystemClockWithPriority]Fail to call KernelIoControl\n");
	}	
#endif	
	return state;
}

int SetSystemClock(int m_CPU_Val,int m_BUS_Val)
{
#ifdef __TCC79XX_WINCE__
	stCKCINFO stCKCInfo;
	
	GetCurrentSystemClock(&stCKCInfo);

	if(stCKCInfo.CurrentCpuFreq/10000 == (unsigned int)m_CPU_Val && stCKCInfo.CurrentBusFreq/10000 == (unsigned int)m_BUS_Val)
	{
		return 1;
	}
#endif	
	return SetSystemClockWithPriority(m_CPU_Val,m_BUS_Val,MAX_PRIORITY,TWS_CLK_SET);
}

int SetSystemIdleClock(int m_CPU_Val,int m_BUS_Val)
{
#ifdef __TCC79XX_WINCE__
	printf("[TCW:SetSystemIdleClock]Idle clock : CPU %d, BUS %d\n",m_CPU_Val,m_BUS_Val);
#endif
	return SetSystemClockWithPriority(m_CPU_Val,m_BUS_Val,IDLE_PRIORITY,TWS_CLK_SET);
}

int ReturnSystemLowClock(void)
{
	return SetSystemClockWithPriority(0,0,LOW_PRIORITY,TWS_CLK_RETURN);
}

int SetSystemLowClock(void)
{
	int m_CPU_Val = 480;
	int m_BUS_Val = 160;
#ifdef __TCC79XX_WINCE__
	stCKCINFO	stCKCInfo;
	
	GetMaxSystemClock(&stCKCInfo);
	m_CPU_Val = stCKCInfo.CurrentCpuFreq / 10000;
	m_BUS_Val = stCKCInfo.CurrentBusFreq / 10000;

	if(!stCKCInfo.CurrentCpuFreq || !stCKCInfo.CurrentBusFreq)
	{
		printf("[TCW:SetSystemLowClock]Max clock is 0 : CPU %d, BUS %d\n",m_CPU_Val,m_BUS_Val);
		return 0;
	}
		
	printf("[TCW:SetSystemLowClock]Max clock : CPU %d, BUS %d\n",m_CPU_Val,m_BUS_Val);	
#endif	
	return SetSystemClockWithPriority(m_CPU_Val,m_BUS_Val,LOW_PRIORITY,TWS_CLK_SET);
}

int ReturnSystemMaxClock(void)
{
	return SetSystemClockWithPriority(0,0,MAX_PRIORITY,TWS_CLK_RETURN);
}

int SetSystemMaxClock(void)
{
	int m_CPU_Val = 480;
	int m_BUS_Val = 160;
#ifdef __TCC79XX_WINCE__
	stCKCINFO	stCKCInfo;
	
	GetMaxSystemClock(&stCKCInfo);
	m_CPU_Val = stCKCInfo.CurrentCpuFreq / 10000;
	m_BUS_Val = stCKCInfo.CurrentBusFreq / 10000;

	if(!stCKCInfo.CurrentCpuFreq || !stCKCInfo.CurrentBusFreq)
	{
		printf("[TCW:SetSystemLowClock]Max clock is 0 : CPU %d, BUS %d\n",m_CPU_Val,m_BUS_Val);
		return 0;
	}
		
	printf("[TCW:SetSystemMaxClock]Max clock : CPU %d, BUS %d\n",m_CPU_Val,m_BUS_Val);
#endif	
	return SetSystemClockWithPriority(m_CPU_Val,m_BUS_Val,MAX_PRIORITY,TWS_CLK_SET);
}

int GetCurrentSystemClock(void *CKCInfo) 
{
	BOOL	state = false;
	
#ifdef __TCC79XX_WINCE__
	stCKCINFO	*stCKCInfo = (stCKCINFO	*)CKCInfo;
	stCKCIOCTL stCKC;
	unsigned long	returnedbyte;
	
	stCKC.ControlCode	=	IOCTL_CKC_GET_CURRENTCLKCTL;

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
	if(state != TRUE)
	{
		printf("[TCW:GetCurrentSystemClock]Fail to get current Clock\n");
		// wsprintf(tstr, L"PLL:%d CPU:%d ", stCKCInfo.CurrentSysFreq/10000 , stCKCInfo.CurrentCpuFreq/10000 );
		// wsprintf(tstr, L"BUS:%d Pri.:%d", stCKCInfo.CurrentBusFreq/10000 , (unsigned int)stCKCInfo.CurrentPriority);
	}	
#endif
	return state;
}

int GetMaxSystemClock(void *CKCInfo) 
{
	BOOL	state = false;
	
#ifdef __TCC79XX_WINCE__
	stCKCINFO	*stCKCInfo = (stCKCINFO	*)CKCInfo;
	stCKCIOCTL stCKC;
	unsigned long	returnedbyte;
	
	stCKC.ControlCode	=	IOCTL_CKC_GET_MAXCLKCTL;

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
	if(state != TRUE)
	{
		printf("[TCW:GetMaxSystemClock]Fail to get Max system Clock\n");
		// wsprintf(tstr, L"PLL:%d CPU:%d ", stCKCInfo.CurrentSysFreq/10000 , stCKCInfo.CurrentCpuFreq/10000 );
		// wsprintf(tstr, L"BUS:%d Pri.:%d", stCKCInfo.CurrentBusFreq/10000 , (unsigned int)stCKCInfo.CurrentPriority);
	}	
#endif
	return state;
}

int GetCurrentSystemClockExt(int *CPU_CLK, int *BUS_CLK) 
{
	BOOL	state = false;
	
#ifdef __TCC79XX_WINCE__
	stCKCINFO	stCKCInfo;
	stCKCIOCTL stCKC;
	unsigned long	returnedbyte;
	
	stCKC.ControlCode	=	IOCTL_CKC_GET_CURRENTCLKCTL;

	state = KernelIoControl(IOCTL_HAL_TCCCKC, &stCKC, sizeof(stCKCIOCTL), &stCKCInfo, sizeof(stCKCINFO), &returnedbyte);
	if(state != TRUE)
	{
		printf("[TCW:GetCurrentSystemClock]Fail to get current Clock\n");		
	}	

	*CPU_CLK = stCKCInfo.CurrentCpuFreq;
	*BUS_CLK = stCKCInfo.CurrentBusFreq;
#endif
	return state;
}

