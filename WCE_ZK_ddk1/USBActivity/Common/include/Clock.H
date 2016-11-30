
#ifndef __CLOCK_H__
#define __CLOCK_H__

enum{
	TWS_CLK_RETURN,
	TWS_CLK_SET,	
};

#define TWS_CKC_LOG "[TWS CLOCK]"

///////////////////////////////////////////////////////////////////////////////////
// TCC79x only

extern int SetAllIOClockOn();
extern int SetAllIOClockOff();
extern int SetSystemClock(int m_CPU_Val,int m_BUS_Val);
extern int ReturnSystemMaxClock(void);
extern int SetSystemIdleClock(int m_CPU_Val,int m_BUS_Val);
extern int GetCurrentSystemClock(void *stCKCInfo);
extern int SetSystemMaxClock(void);
extern int GetCurrentSystemClockExt(int *CPU_CLK, int *BUS_CLK);
extern int ReturnSystemLowClock(void);
extern int SetSystemLowClock(void);
extern int GetMaxSystemClock(void *CKCInfo);

extern int TWS_CKC_Enable_SubCoreMailBox();
extern int TWS_CKC_Disable_SubCoreMailBox();
extern int TWS_CKC_Enable_GPSB0(unsigned int New_Clock_Source, unsigned int New_Clock, int Mode);
extern int TWS_CKC_Disable_GPSB0();
extern int TWS_CKC_Enable_GPSB1(unsigned int New_Clock_Source, unsigned int New_Clock, int Mode);
extern int TWS_CKC_Disable_GPSB1();
extern int TWS_CKC_Enable_M2MScaler();
extern int TWS_CKC_Disable_M2MScaler();

///////////////////////////////////////////////////////////////////////////////////
// TCCxxx only

#ifdef __TCC89XX_WINCE__
#define VBUS_HIGH_CKC      2640000
#define VBUS_HIGH_CKC_SRC  DIRECTPLL1
#define VCORE_HIGH_CKC     2340000
#define VCORE_HIGH_CKC_SRC DIRECTPLL3

#define VBUS_LOW_CKC       1760000
#define VBUS_LOW_CKC_SRC   DIRECTPLL3
#define VCORE_LOW_CKC      1560000
#define VCORE_LOW_CKC_SRC  DIRECTPLL2

#define GRP_HIGH_CKC       2640000
#define GRP_HIGH_CKC_SRC   DIRECTPLL3
#define GRP_LOW_CKC        1760000
#define GRP_LOW_CKC_SRC    DIRECTPLL3

#elif __TCC88XX_WINCE__
#define VBUS_HIGH_CKC      2700000
#define VBUS_HIGH_CKC_SRC  DIRECTPLL3
#define VCORE_HIGH_CKC     2700000
#define VCORE_HIGH_CKC_SRC DIRECTPLL3

#define VBUS_LOW_CKC       2700000
#define VBUS_LOW_CKC_SRC   DIRECTPLL3
#define VCORE_LOW_CKC      2700000
#define VCORE_LOW_CKC_SRC  DIRECTPLL3

#define GRP_HIGH_CKC       2700000
#define GRP_HIGH_CKC_SRC   DIRECTPLL3
#define GRP_LOW_CKC        2700000
#define GRP_LOW_CKC_SRC    DIRECTPLL3
#endif

enum{
	TCC88X_XX,
	TCC88X_AX,	
};

extern 	int  TWS_CKC_GetFBUS(int pckname);
extern 	void TWS_CKC_SetFBUS(int pckname,int mode, int pckcfreq, int source);
extern 	void TWS_CKC_SetIOBUS(int iobusname, unsigned char mode);
extern 	void TWS_CKC_SetETC(unsigned char mode);	
	
extern 	int  TWS_CKC_GetBUS(int pckname,int *pckcfreq);
extern 	int  TWS_CKC_GetCPU();
extern 	int  TWS_CKC_GetMemoryBus();
extern 	int  TWS_CKC_GetVBusClock();

	///////////////////////////////////////////////////////////////////
extern 	void TWS_CKC_SetFCPU(int pckcfreq);
extern 	void TWS_CKC_SetFMBUS(int pckcfreq);

	///////////////////////////////////////////////////////////////////
extern 	void TWS_CKC_SetFBUSForVPUOn(void);
extern 	void TWS_CKC_SetFBUSForVPUOff(void);
extern 	void TWS_CKC_SetFBUSForVPU(int VBUS, int VCODEC);
extern 	void TWS_CKC_SetDDIBUS(int ddibusname, unsigned char mode);	

	///////////////////////////////////////////////////////////////////
extern 	void TWS_CKC_SetVPU_Init(void);
extern 	void TWS_CKC_SetVPU_DeInit(void);
extern 	void TWS_CKC_SetVPUOff(void);
extern 	void TWS_CKC_SetVPUOn(void);
extern 	void TWS_CKC_SetDynamicVPUOn(void);
extern 	void TWS_CKC_SetDynamicModeForVPU(unsigned int mode, unsigned int dynamicmax, unsigned int dynamicmin, unsigned int dynamiccycle);

	///////////////////////////////////////////////////////////////////
extern 	int TWS_CKC_GetGraphicBus();

extern 	void TWS_CKC_SetFBUSForGRPOn(void);
extern 	void TWS_CKC_SetFBUSForGRPOff(void);

extern 	void TWS_CKC_SetMSCBUSOn(int iMSCNum);
extern 	void TWS_CKC_SetMSCBUSOff(int iMSCNum);
extern 	void TWS_CKC_SetLCDCBUSOn(int iLCDCNum);
extern 	void TWS_CKC_SetLCDCBUSOff(int iLCDCNum);

extern 	void TWS_CKC_SetVIQEBUSOn();
extern 	void TWS_CKC_SetVIQEBUSOff();

extern 	void TWS_CKC_SetOverlayMix(unsigned char mode);
extern 	void TWS_CKC_Set3DGPU(unsigned char mode);
extern 	void TWS_CKC_SetPWRControl(unsigned char ucDeviceID,unsigned char mode);
#endif
