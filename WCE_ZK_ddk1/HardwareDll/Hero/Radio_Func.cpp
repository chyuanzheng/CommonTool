/***********************************************************************//**
 * @file		Hero.c
 * @purpose		This example used to test NXP HERO function
 * @version		0.1
 * @date		1. Oct. 2010
 * @author		NXP BU Automotive Car Entertainment Team & VITEC ELECTRONICS(SHENZHEN) AE Team
 *---------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors and VITEC Electronics assume no responsibility or liability for the
 * use of the software, convey no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors and VITEC Electronics
 * reserve the right to make changes in the software without
 * notification. NXP Semiconductors and VITEC Electronics also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

 #include "public.h"

/* station */
StationMemType StationRecord[MaxStationNum]; 

/* area config*/
#define AreaSelect Radio_CHN

#if (AreaSelect==Radio_CHN)   /*China */          
const Radio_AreaConfigDef Radio_AreaConfig={
    //FM_MaxFreq  FM_MinFreq  AM_MaxFreq  AM_MinFreq  FM_AutoSeekStep/k  FM_ManualSeekStep/k  AM_AutoSeekStep/k  AM_ManualSeekStep/k
    10800,        8750,      1620,       522,         FM_Step_100k,        FM_Step_100k,                 9,                  9};
	
const FreqBaundDef FreqBaundConfig[MaxBandNum]={		
   /*0-FM1,1-FM2,2-FM3,3-LW,4-MW,5-SW*/
    {8750,10800},{8750,10800},{8750,10800},{522,1710},{144,288},{2300,27000}};    
    
#elif (AreaSelect==Radio_EUR)  /*Europe */   	                        
const Radio_AreaConfigDef Radio_AreaConfig={
//FM_MaxFreq  FM_MinFreq  AM_MaxFreq  AM_MinFreq  FM_AutoSeekStep/k  FM_ManualSeekStep/k  AM_AutoSeekStep/k  AM_ManualSeekStep/k
10800,        8750,      1602,       531,         FM_Step_100k,        FM_Step_100k,               9,                  9};
const FreqBaundDef FreqBaundConfig[MaxBandNum]={		 //0-FM1,1-FM2,2-FM3,3-LW,4-MW,5-SW
    {6500,10800},{6500,10800},{6500,10800},{144,288},{522,1710},{2300,27000}};    // 
    
#elif (AreaSelect==Radio_USA)      /*USA */                
const Radio_AreaConfigDef Radio_AreaConfig={
//FM_MaxFreq  FM_MinFreq  AM_MaxFreq  AM_MinFreq  FM_AutoSeekStep/k  FM_ManualSeekStep/k  AM_AutoSeekStep/k  AM_ManualSeekStep/k
10790,        8750,      1710,       530,        FM_Step_100k,        FM_Step_100k,         10,                  10};
const FreqBaundDef FreqBaundConfig[MaxBandNum]={		 //0-FM1,1-FM2,2-FM3,3-LW,4-MW,5-SW
    {6500,10800},{6500,10800},{6500,10800},{144,288},{522,1710},{2300,27000}};    // 
    
#elif (AreaSelect==Radio_JPN)      /*Japan */                
const Radio_AreaConfigDef Radio_AreaConfig={
//FM_MaxFreq  FM_MinFreq  AM_MaxFreq  AM_MinFreq  FM_AutoSeekStep/k  FM_ManualSeekStep/k  AM_AutoSeekStep/k  AM_ManualSeekStep/k
9000,        7600,      1629,       522,          FM_Step_100k,        FM_Step_100k,               9,                   9};
const FreqBaundDef FreqBaundConfig[MaxBandNum]={		 //0-FM1,1-FM2,2-FM3,3-LW,4-MW,5-SW
    {6500,10800},{6500,10800},{6500,10800},{144,288},{522,1710},{2300,27000}};    // 
    
#endif

#if 0
/*Hero radio default parameters */
const U8 Hero_Radio_DefParameters[CONFIG_PARA_LEN]=
{
  0,	  //FM TUNER(AGC&Bandwidth)  //,0  
  0x00/*0x06*/,	  //AM TUNER(AGC&Bandwidth)  // 1	modify	nick 20110707
  0,     //TUNER_OPT (Antenna type&Antenna atteuation) no atteuation (only am )fm=0x00 //2
  0x4a,// FM RADIO (EMS,CNS,CE,NBSA,NBSB,//3
  0x4a,//AM  RADIO (EMS,CNS,CE,NBSA,NBSB,//4
  0x01,	//fm_Signal//5
  0x06/*0x0a*//* 0x05*/,	//am Signal//6					  modify	nick 20110707
  0x05,	//fm_BWCTRL(only fm),am=0x05//7
  0x00,	//Special (only fm) am=0x00//8
  0x30,	//fm Level offset	//9
  0x30,	//am Level offset	//10

   //softmute
   0x65,	//fm softmute time	 //11
   0x0e,	//am softmute time	//12
   0x3f/*0x10*//*0x00*/,	   //fm           softmute det    //13			 modify	nick 20110707
   0xd0,	   // am         softmute det    //14
   0x4a/*0x3A*/,		// fm  softmue lev  //15
   0x40,		//  am softmue lev  //16
   0x77/*0x33*/,		//fm softmute N_M	(fm only am:0x33)//17
   0x0a/*0x0C*/,	//fm softmute limit	//18		/*-20db*/				    modify	nick 20110707
   0x04,	//am softmute limit	//19

   //highcut
   0x6E, //fm_Highcut time//20
   0x12, //am Highcut time	//21
   0x35/*0x00*/,	//	fm  Highcut det//22			 modify	nick 20110707
   0xb5,	//	am  Highcut det   //23
   0x23/*0x33*/,	//	fm  Highcut level   //24	 modify	nick 20110707
   0x5b,	//	am  Highcut level   //25
   0x33,	//	Highcut N_M	(fm only am:0x33)//26
   0x04/*0x02*/,	//	fm   Highcut lim  //27			 modify	nick 20110707
   0x02,	//	am   Highcut lim  //28		
   0x04,   //fm Highcut low cut	//29
   0x05,   //am Highcut low cut	//30

 //stereo
   0x75,	 //fm stereo time(only fm ,am=0x75)	 	//31
   0x3f/* 0x00*/,	//	 stereo det(only fm ,am=0x10)	 	//32 modify	nick 20110707	
   0x4A,			//  stereo level	 (only fm ,am=0x4a)	 	//33
   0x33,	//	stereo N_M	   (only fm ,am=0x33)	 //34
   0x00,	//	stereo lim     (only fm ,am=0x0)	 //35
   0x3f/*0x00*/,	//	  stereo HB DET    (only fm ,am=0x10)	//36    modify	nick 20110707
   0x13,          // stereo HB LNM   (only fm ,am=0x4a)	 //37
};
#endif
U8 Hero_Radio_AM_Parameters[CONFIG_PARA_LEN]; 
U8 Hero_Radio_FM_Parameters[CONFIG_PARA_LEN];

/*Hero radio default parameters */
const U8 Hero_Radio_AM_DefParameters[CONFIG_PARA_LEN]=
{
	AM_TUNER_RES|AM_RFAGC_97DBUV|AM_BW_AUTO,	  /*AM TUNER(AGC&Bandwidth)  03 if no keycode AM_BW_AUTO==5*/
	AM_TUNER_OPT_RES|AM_ANT_PASSIVE|AM_ATT_0DB,     /*TUNER_OPT (Antenna type&Antenna atteuation) no atteuation (only am )fm=0x00 //04*/
	AM_RADIO_RES|NBSA_MID_SENS|AM_NBSB_MID_SENS,//AM  RADIO (EMS,CNS,CE,NBSA,NBSB,//05
	AM_SIGNAL_RES|DRADIO_OFF|AM_FLOC_100HZ|AM_LP_2KHZ,	//am Signal//06					
	AM_BWCTRL_RES,	//fm_BWCTRL(only fm),am=0x05//07
	AM_SPECIAL_RES|QSI_NO_INT,	//Special (only fm) am=0xE0//08
	AM_RDS_RES,   //RDS(FM only) AM=0X41  //09

	0x00,   //reserve  0A
	0x00,   //RESERVE 0B 
	AM_LEVEL_OFFSET_RES|LEVO_DB(0),	// Level offset	//0C
	//softmute
	AM_SOFTMUT_TIME_RES|MAT_500MS|MDT_8TIMES,	//0x0eam softmute time	//0D
	AM_SOFTMUTE_DET_RES|AM_MMOD_MID|MSOL_ON,	   // am         softmute det    //0E
	AM_SOFTMUTE_LEV_RES|AM_MST_DBUV(32),//0x40,		//  am softmue lev  //0F
	AM_SOFTMUTE_N_M_RES,//0x33,    //softmute_n_m  fm only AM=0x33 10
	AM_SOFTMUTE_LIM_RES|MLIM_LIMIT_GAIN_DB(-16),//0x04,	//am softmute limit	//11

	//highcut
	AM_HIGHCUT_TIME_RES|HAT_1S|HDT_8TIMES,//0x12, //am Highcut time	//12
	AM_HIGHCUT_DET_RES|HMOD_MID|HSOL_ON,//0xb5,	//	am  Highcut det   //13
	AM_HIGHCUT_LEV_RES|AM_HST_DBUV(52)|HSL_18DB,//0x5b,	//	am  Highcut level   //14
	AM_HIGHCUT_N_M_RES,//0x33,	//	Highcut N_M	(fm only am:0x33)//15
	AM_HIGHCUT_LIM_RES|HSLIM_BW_START_UNLIMIT|HLIM_BW_CUT_2KHZ,//0x02,	//	am   Highcut lim  //16		
	AM_HIGHCUT_LOC_RES|HLOC_200HZ,   //am Highcut low cut	//17

	//stereo
	AM_STEREO_TIME_RES,	 //fm stereo time(only fm ,am=0x75)	 	//18
	AM_STEREO_DET_RES,// 0x3f/* 0x00*/,	//	 stereo det(only fm ,am=0x10)	 	//19 modify	nick 20110707	
	AM_STEREO_LEV_RES,//0x4A,			//  stereo level	 (only fm ,am=0x4a)	 	//1a
	AM_STEREO_N_M_RES,//0x33,	//	stereo N_M	   (only fm ,am=0x33)	 //1b
	AM_STEREO_LIM_RES,//0x00,	//	stereo lim     (only fm ,am=0x0)	 //1c
	AM_STEREOHB_DET_RES,//0x3f/*0x00*/,	//	  stereo HB DET    (only fm ,am=0x10)	//1d    modify	nick 20110707
	AM_STEREOHB_LNM_RES,//0x13,          // stereo HB LNM   (only fm ,am=0x4a)	 //1e
};

/*Hero radio default parameters */
const U8 Hero_Radio_FM_DefParameters[CONFIG_PARA_LEN]=
{
  FM_TUNER_RES|FM_RFAGC_89DBUV|FM_BW_AUTO,	  //FM TUNER(AGC&Bandwidth)  03
  FM_TUNER_OPT_RES|FM_SAD_OFF,     //TUNER_OPT (Antenna type&Antenna atteuation) no atteuation  SAD //04
  FM_RADIO_RES|FM_IMS_ON|FM_CE_OFF|FM_CNS_ON|NBSA_MID_SENS,//0xc2,//FM  RADIO (iMS=1,CNS=1,CE,NBSA,NBSB,//05
  FM_SIGNAL_RES|DRADIO_OFF|FM_DEMP_50US,// 0x01,	//fm Signal 50us //06 					
  0x06,//FM_BWCTRL_RES|FM_BWS_HIGH_SENS|FM_BWLEV_HIGHEST_SENS,//0x05,	//fm_BWCTRL(only fm),am=0x05//07
  FM_SPECIAL_RES|QSI_NO_INT|FM_FQCI_OFF|FM_AFUP_OFF,//0xE0,	//Special (only fm) am=0xE0//08
  FM_RDS_RES,//0x41,   //RDS(FM only) AM=0X41  //09
 
  0x00,   //reserve  0A
  0x00,   //RESERVE 0B 
  FM_LEVEL_OFFSET_RES|LEVO_DB(0),//0x30,	// Level offset	//0C

   //softmute
   FM_SOFTMUT_TIME_RES|FM_MFT_8MS|MAT_500MS|MDT_8TIMES,//0x65,	//fm softmute time	 //0d
   FM_SOFTMUTE_DET_RES|FM_MFOL_ON|MSOL_ON|FM_MFON_ON|FM_MSON_ON|FM_MFOM_ON|FM_MSOM_ON,//0x3f/*0x10*//*0x00*/,	   //fm           softmute det    //0E			 modify	nick 20110707
   FM_SOFTMUTE_LEV_RES|FM_MST_DBUV(18)|MSL_22DB,//0x4a/*0x3A*/,		// fm  softmue lev  //0f
   FM_SOFTMUTE_N_M_RES|FM_MNS_26PERCENT_START|FM_MMS_26PERCENT_START,//0x77/*0x33*/,		//fm softmute N_M	(fm only am:0x33)//10
   FM_SOFTMUTE_LIM_RES|MLIM_LIMIT_GAIN_DB(-16),//0x0a/*0x0C*/,	//fm softmute limit	//11		/*-20db*/				    modify	nick 20110707


   //highcut
   FM_HIGHCUT_TIME_RES|FM_HFT_8MS|HAT_500MS|HDT_8TIMES,//0x6E, //fm_Highcut time//12
   FM_HIGHCUT_DET_RES|FM_HFOL_ON|HSOL_ON|FM_HFON_ON|FM_HSON_ON|FM_HFOM_ON|FM_HSOM_ON,//0x35/*0x00*/,	//	fm  Highcut det//13			 
   FM_HIGHCUT_LEV_RES|FM_HST_DBUV(32)|HSL_18DB,//0x23/*0x33*/,	//	fm  Highcut level   //14	 
   FM_HIGHCUT_N_M_RES|FM_MNS_36PERCENT_START|FM_MMS_36PERCENT_START,//0x33,	//	Highcut N_M	(fm only am:0x33)//15
   FM_HIGHCUT_LIM_RES|FM_HFIL_LP_NO_ATT|HSLIM_BW_START_UNLIMIT|HLIM_BW_CUT_3KHZ,//0x04/*0x02*/,	//	fm   Highcut lim  //16			 
   FM_HIGHCUT_LOC_RES|HLOC_140HZ,//0x04,   //fm Highcut low cut	//17

   //stereo
   FM_STEREO_TIME_RES|FM_SFT_8MS|FM_SAT_1S|FM_SDT_8TIMES,//0x72,	 //fm stereo time(only fm ,am=0x72)	 	//18
   FM_STEREO_DET_RES|FM_SMOD_OFF|FM_SFOL_ON|FM_SFON_ON|FM_SSON_ON|FM_SFOM_ON|FM_SSOM_ON,//0x3f/* 0x00*/,	//	 stereo det(only fm ,am=0x3f)	 	//19 modify	nick 20110707	
   FM_STEREO_LEV_RES|FM_SST_DBUV(48)|FM_SSL_22DB,//0x4A,			//  stereo level	 (only fm ,am=0x4a)	 	//1a
   FM_STEREO_N_M_RES|FM_SSLIM_30DB|FM_SMS_24PERCENT_START,//0x33,	//	stereo N_M	   (only fm ,am=0x33)	 //1b
   FM_STEREO_LIM_RES|FM_SSLIM_UNLIMITE,//0x00,	//	stereo lim     (only fm ,am=0x0)	 //1c
   FM_STEREOHB_DET_RES|FM_BMOD_OFF|FM_BFOL_ON|FM_BSOL_ON|FM_BFON_ON|FM_BSOL_ON|FM_BFOM_ON|FM_BSOM_ON,//0x3f,	//	  stereo HB DET    (only fm ,am=0x3f)	//1d    modify	nick 20110707
   FM_STEREOHB_LNM_RES|STEREOHB_USN_WAM_SENS_1|STEREOHB_LEV_SENS_3,//0x13,          // stereo HB LNM   (only fm ,am=0x13)	 //1e
};
/* radio default station */
const StationMemType StationDefaultRecord[MaxStationNum]=			 //now config: MaxBandNum=6, MaxStationNum=7 
{
	{10000,10000,10000,10000,10000,10000,10000},     //fm1				  
	{10000,10000,10000,10000,10000,10000,10000},		//fm2
	{10000,10000,10000,10000,10000,10000,10000},     //fm3
	{522,522,522,522,522,522,522},		//mw
	{144,144,144,144,144,144,144},		//lw
	{2300,2300,2300,2300,2300,2300,2300}		//sw
};

/*radio parameters */
//U8 RadioConfig[CONFIG_PARA_LEN];
/*check station step*/
static U8 CheckIfStep;

/*current radio  band*/
U8 Radio_CurrentBand;
/*current radio  freqency*/
U16 Radio_CurrentFreq;
/*current radio  station*/
U8 Radio_CurrentStation;

/*-----------------------------------------------------------------------
Function name:	Radio_SetFreq
Input:		mode:
                              TEF663X_PRESETMODE.,TEF663X_SEARCHMODE
                              TEF663X_AFUPDATEMODE,TEF663X_JUMPMODE...
                        Freq:
Output:			
Description:	 
------------------------------------------------------------------------*/
void Radio_SetFreq(U8 mode,U8 Band,U16 Freq)
{
       /*frequency baundary check*/
	if((Freq>FreqBaundConfig[Radio_CurrentBand].MaxFreq)||(Freq<FreqBaundConfig[Radio_CurrentBand].MinFreq)){
		Freq = FreqBaundConfig[Radio_CurrentBand].MinFreq;
	}
	if(Band>=MaxBandNum){
		return;
	}
	Radio_CurrentBand=Band;
	switch(Band)
	{
	   case FM1_BAND:
	   case FM2_BAND:
	   case FM3_BAND:
	        Band=0;
	 		break;
		case LW_BAND:
		    Band=1;
			break;
		case MW_BAND:
		    Band=2;
			break;
		case SW_BAND:
		    Band=3;
			break;
	
	}

	/*update pll*/
	RadioDrv_UpdatePll(mode,Band,Freq);
    	
	Radio_CurrentFreq=Freq;
	StationRecord[Radio_CurrentBand].Freq[0]=Radio_CurrentFreq;
}
/*====================================================
 Function:Radio_ChangeFreqOneStep
 Input: 
      UP/DOWN
 OutPut:
      Null
 Desp:
     change curren freq on step
=========================================================*/
void Radio_ChangeFreqOneStep(U8 UpDown )
{
	int step;

	step=Radio_GetFreqStep(Radio_CurrentBand);
	if(UpDown==1)
	{	/*increase one step*/
		Radio_CurrentFreq+=step;
		/*frequency baundary check	*/
		if(Radio_CurrentFreq>FreqBaundConfig[Radio_CurrentBand].MaxFreq)	
		{  
			Radio_CurrentFreq=FreqBaundConfig[Radio_CurrentBand].MinFreq;
		}
	}
	else	
	{      /*decrease one step*/
		Radio_CurrentFreq-=step;  
		/*frequency baundary check*/	
		if(Radio_CurrentFreq<FreqBaundConfig[Radio_CurrentBand].MinFreq)	
		{	
		    	Radio_CurrentFreq=FreqBaundConfig[Radio_CurrentBand].MaxFreq;
		}		
	}

}
/*-----------------------------------------------------------------------
Function name:	Radio_GetCurrentFreq
Input:			
Output:			
Description:	return current freq
------------------------------------------------------------------------*/
U16 Radio_GetCurrentFreq(void)
{
	 return Radio_CurrentFreq;
}
/*-----------------------------------------------------------------------
Function name:	Radio_GetCurrentBand
Input:			
Output:			
Description:	 return current band 
------------------------------------------------------------------------*/
U8 Radio_GetCurrentBand(void)
{
	 return Radio_CurrentBand;
}

/*-----------------------------------------------------------------------
Function name:	Radio_GetCurrentStation
Input:			
Output:			
Description:	 return current station 
------------------------------------------------------------------------*/
U8 Radio_GetCurrentStation(void)
{
	 return Radio_CurrentStation;
}
/*-----------------------------------------------------------------------
Function name:	Radio_ClearCurrentStation
Input:			
Output:			
Description:	 set current station 
------------------------------------------------------------------------*/
void Radio_ClearCurrentStation(void)
{
	  Radio_CurrentStation=0;
}
/*-----------------------------------------------------------------------
Function name:	Radio_GetFreqStep
Input:			
Output:			
Description:	 Get current band freq step
------------------------------------------------------------------------*/
U32 Radio_GetFreqStep(U8 band)
{
	return (band<=FM3_BAND)? Radio_AreaConfig.FM_ManualSeekStep : Radio_AreaConfig.AM_ManualSeekStep;
}
/*-----------------------------------------------------------------------
Function name:	Radio_IsFMBand
Input:			
Output:			
Description:	 check current band is fm band
------------------------------------------------------------------------*/
U8 Radio_IsFMBand(void)
{ 
      return ((Radio_CurrentBand<=FM3_BAND)?1:0 )	;
}

/*-----------------------------------------------------------------------
Function name:	Radio_SetBand
Input:			Band
Output:			
Description:	 set band
------------------------------------------------------------------------*/
void Radio_SetBand(U8 Band)
{
	U16 Freq;
	U8 VirtualBand;

	if(Band>=MaxBandNum)	
	{
	    	return;
	}
	VirtualBand=Band;
    switch(Band)
	{
	   case FM1_BAND:
	   case FM2_BAND:
	   case FM3_BAND:
	        Band=0;
	 		break;
		case LW_BAND:
		    Band=1;
			break;
		case MW_BAND:
		    Band=2;
			break;
		case SW_BAND:
		    Band=3;
			break;
	
	}
	Freq=StationRecord[VirtualBand].Freq[0];
	/*update pll*/
	RadioDrv_UpdatePll(Radio_PRESETMODE,Band,Freq);
		
	Radio_CurrentFreq=Freq;
	Radio_CurrentBand=VirtualBand;

	Audio_DrvSetStreamInput(NavigationStr, INPUT_SOURCE_IIS1);

}
/*-----------------------------------------------------------------------
Function name:	Radio_NextBand
Input:			NULL
Output:			
Description:	 set to next band
------------------------------------------------------------------------*/
void Radio_NextBand(void)
{
	Radio_CurrentBand++;
	/*check band avilable*/
	if(Radio_CurrentBand>=MaxBandNum)	
	{
		Radio_CurrentBand=0;
	}
	/*set to current band*/
	Radio_SetBand(Radio_CurrentBand);
	Radio_CurrentFreq=StationRecord[Radio_CurrentBand].Freq[0];
	Radio_CurrentStation=0;
}
/*-----------------------------------------------------------------------
Function name:	Radio_ValidFreq
Input:			band and freqencey pointer
Output:			valid freqency
Description:	 	min<= freq <= max, aligned by step
------------------------------------------------------------------------*/
static void Radio_ValidFreq(U8 band,U16 *pFreq)
{
	U16 step,min,max;

	step = Radio_GetFreqStep(band);
	max = FreqBaundConfig[band].MaxFreq;
	min = FreqBaundConfig[band].MinFreq;

	if((*pFreq > max)||(*pFreq < min))	//frequency baundary check
		*pFreq = min;
	else {  //step check
		int num  = (*pFreq - min)/step;	//align freq by step
		*pFreq = min + num * step;
	}
}
/*-----------------------------------------------------------------------
Function name:	Radio_ReadStationRecord
Input:			
Output:			
Description:	 write  one station to eeprom
------------------------------------------------------------------------*/
void Radio_StoreStation(U8 Band,U8 Station)
{
 //   EEPROM_Write(EEPRom_StationRecordDefaultAddr + Band *sizeof(StationRecord[0]) +2*Station,
	//(U8 *)(&StationRecord[Band].Freq[Station]),2);

}
/*-----------------------------------------------------------------------
Function name:	Radio_ReadStationRecord
Input:			
Output:			
Description:	 read  one station from eeprom
------------------------------------------------------------------------*/
void Radio_ReadStation(U8 Band,U8 Station)
{
 //   EEPROM_Read(EEPRom_StationRecordDefaultAddr + Band *sizeof(StationRecord[0]) +2*Station,
	//(U8 *)(&StationRecord[Band].Freq[Station]),2);

}
/*-----------------------------------------------------------------------
Function name:	Radio_ReadStationRecord
Input:			
Output:			
Description:	 read all station from eeprom
------------------------------------------------------------------------*/
void Radio_ReadStationRecord(void)
{
	U16 band,station;
	U16 *pFreq;
	
	//EEPROM_Read(EEPRom_StationRecordDefaultAddr,(U8 *)(&StationRecord[0].Freq[0]),sizeof(StationRecord));
        /* for(band=0;band<MaxBandNum;band++)
	     for(station=0;station<MaxStationNum;station++)
	     	Radio_ReadStation( band, station);*/
		 
	/*set all frequency to valid value*/
	/*for(band=0;band<MaxBandNum;band++)
	{	
	        EEPROM_Read(EEPRom_StationRecordDefaultAddr+ band *sizeof(StationRecord[0]),(U8 *)(&StationRecord[band].Freq[0]),sizeof(StationRecord[0]));
		pFreq = &StationRecord[band].Freq[0];	
		for(station=0;station<MaxStationNum;station++,pFreq++) 
		{
			Radio_ValidFreq(band,pFreq);
		}
	}*/
}
/*-----------------------------------------------------------------------
Function name:	Radio_StoreStationRecord
Input:			
Output:			
Description:	 store one band of station to eeprom
------------------------------------------------------------------------*/
void Radio_StoreStationRecord(U8 Band)
{
/*
	EEPROM_Write(EEPRom_StationRecordDefaultAddr + Band *sizeof(StationRecord[0]) ,
	(U8 *)(&StationRecord[Band].Freq[0]),
	sizeof(StationRecord[0]));	 */
	int i;
	for(i=0;i<MaxStationNum;i++)
	{
		 Radio_StoreStation( Band, i);
	}
	      
}

/*-----------------------------------------------------------------------
Function name:	Radio_ReadCurrentBand
Input:			
Output:			
Description:	read station from eeprom 
------------------------------------------------------------------------*/
U8 Radio_ReadCurrentBand(void)
{
	U8 band;
	/*read current band from eeprom*/
	//EEPROM_Read(EEPRom_CurrentBandAddr,&band, 1);
	/*if band not aviliable*/
	if(band>=MaxBandNum)
		band=FM1_BAND;
	return band;
}
/*-----------------------------------------------------------------------
Function name:	Radio_StoreCurrentBand
Input:			
Output:			
Description:	 store current band  to eeprom
------------------------------------------------------------------------*/
void Radio_StoreCurrentBand(void)
{
	//EEPROM_Write(EEPRom_CurrentBandAddr,&Radio_CurrentBand,1);
}
/*-----------------------------------------------------------------------
Function name:	Radio_ReadConfig
Input:			
Output:			
Description:	read parameters from eeprom 
------------------------------------------------------------------------*/
void Radio_ReadConfig(void)
{

}
/*-----------------------------------------------------------------------
Function name:	Radio_StoreConfig
Input:			
Output:			
Description:	 store parameters into eeprom
------------------------------------------------------------------------*/
void Radio_StoreConfig(void)
{     
 //   int i;
	//for(i=0;i<CONFIG_PARA_LEN;i=i+2)
	//	{
 //           EEPROM_Write(EEPRom_FM_ConfigAddr+i,Hero_Radio_FM_Parameters+i,2);
	//	  EEPROM_Write(EEPRom_AM_ConfigAddr+i,Hero_Radio_AM_Parameters+i,2);
	//}
}
/*-----------------------------------------------------------------------
Function name:	Radio_StoreAll
Input:			
Output:			
Description:	 store all the radio para,station to eeprom
------------------------------------------------------------------------*/
void Radio_StoreAll(void)
{
 //       U8 i;
	///*store radio parameters*/
	//Radio_StoreConfig();			
	///*write eeprom available flag*/
	//i=AvailableDataFlag;
	//EEPROM_Write(EEPRom_CheckAddr,&i,1);
	///*store current band*/
	//Radio_StoreCurrentBand();
	///*store station*/
	//for(i=0;i<MaxBandNum;i++)	
	//{
	//    	Radio_StoreStationRecord(i);
	//}
}
U8 FM_Seek_Sens=Radio_FMScanSen;
U8 AM_Seek_Sens=Radio_AMScanSen;
void Radio_SetSeekSenLevel(U8 Lev)
{
	if(Lev==1) 	{
	     	FM_Seek_Sens=Radio_FMScanSen_Loc;
                AM_Seek_Sens=Radio_AMScanSen_Loc;
	}else{

                FM_Seek_Sens=Radio_FMScanSen;
                AM_Seek_Sens=Radio_AMScanSen;

       }


}
/*--------------------------------------------------------------------
 Function:Radio_CheckStation
 Input: 
      Null
 OutPut:
      Null
 Desp:
     check station if aviable
---------------------------------------------------------------------*/
void Radio_CheckStation(void)
{
	unsigned char TunerStatus,TempData,Tuner_Level;
	unsigned char Tuner_UNoise,Tuner_MNoise,Tuner_Offset;
	unsigned char threshold;
	unsigned char i;
	switch(CheckIfStep)
	{
		case 10:/*start check init*/
			CheckIfStep = 20;
			break;
		case 20:/*Check QRS(quality of read status)	 */
			CheckIfStep=NO_STATION;
			RadioDrv_ReadData(1);
			TunerStatus=RadioDrv_GetData(Radio_STATUS);   //get status
			TempData=TunerStatus&0xE0;
			if(Radio_CurrentBand<=FM3_BAND)//FM
				threshold=Radio_FM_Status;//0x20;
			else
				threshold=Radio_AM_Status;//0XA0

			if(TempData>=threshold){	/*Set to next step*/	
				CheckIfStep=30;  
			}
			break;   
		case 30:/*check level */
			CheckIfStep=40;

			for(i=0;i<3;i++)
			{/*Check 3 times*/
				/*read status data*/
				RadioDrv_ReadData(2);
				/*get signal strength level*/	
				Tuner_Level=RadioDrv_GetData(Radio_LEVEL);   		 

				if(Radio_CurrentBand<=FM3_BAND)//FM
					threshold=FM_Seek_Sens;
				else//AM
					threshold=AM_Seek_Sens;

				if(Tuner_Level<threshold) 
				{//exit check
					CheckIfStep=NO_STATION;
					break;
				}
			}
			break;
		case 40:
			CheckIfStep=NO_STATION;
			/*read status data*/
			RadioDrv_ReadData(5);
			/*get noise*/	 
			Tuner_UNoise=RadioDrv_GetData(Radio_USN);
			/*get multpath*/	
			Tuner_MNoise=RadioDrv_GetData(Radio_WAM);
			/*get freqency offset*/	
			Tuner_Offset=RadioDrv_GetData(Radio_FOF);
			Tuner_Offset&=~0x80;
			if(Radio_CurrentBand<=FM3_BAND)
			{//FM	
				if((Tuner_UNoise<Radio_FMScanUNoise)
				&&(Tuner_MNoise<Radio_FMScanMNoise)
				&&(Tuner_Offset<Radio_FMScanOffset))		 // Tuner_UNoise  Tuner_MNoise  Tuner_Offset
				 { 
					CheckIfStep=PRESENT_STATION;
				}
			}	
			else//AM
			{
				if((Tuner_Offset<Radio_AMScanOffset))		 //valuable station	Tuner_Offset	
				{
					CheckIfStep=PRESENT_STATION;
				}
			}
			break;
            case NO_STATION:
			break; 
            case PRESENT_STATION:
			break; 
            default:
			CheckIfStep = NO_STATION;
			break;        
        }
}
/*--------------------------------------------------------------------
 Function:Radio_CheckStationStatus
 Input: 
      Null
 OutPut:
      CheckIfStep
 Desp:
     get check station step
---------------------------------------------------------------------*/
U8 Radio_CheckStationStatus(void)
{
	return CheckIfStep;
}

/*--------------------------------------------------------------------
 Function:Radio_CheckStationInit
 Input: 
      Null
 OutPut:
      NULL
 Desp:
      check station init
---------------------------------------------------------------------*/
void Radio_CheckStationInit(void)
{
	CheckIfStep=10;
}

U8 Radio_HasStation(void)
{
	Radio_CheckStationInit();
	for (int i=0;i<100;i++)
	{
		if (CheckIfStep == NO_STATION)
		{
			return 0;
		}
		if (CheckIfStep == PRESENT_STATION)
		{
			return 1;
		}
		Radio_CheckStation();
	}
	return 0;
}
/*-----------------------------------------------------------------------
Function name:	Radio_SelectPreset
Input:		Station :1~6	
Output:		
Description:	 select preset station
------------------------------------------------------------------------*/
void Radio_SelectPreset(U8 Station)
{
	if(StationRecord[Radio_CurrentBand].Freq[Station]==0) 
	{		//no station record
		return;
	}
	/*set radio freqency*/	
	Radio_SetFreq(Radio_PRESETMODE,Radio_CurrentBand,StationRecord[Radio_CurrentBand].Freq[Station]);
	/*reset station*/
	StationRecord[Radio_CurrentBand].Freq[0]=StationRecord[Radio_CurrentBand].Freq[Station];
	Radio_CurrentStation=Station;
	Radio_CurrentFreq=StationRecord[Radio_CurrentBand].Freq[0];
}
/*-----------------------------------------------------------------------
Function name:	Radio_SaveCurrentFreq2Preset
Input:			
Output:		
Description:	preset station save
------------------------------------------------------------------------*/
void Radio_SaveCurrentFreq2Preset(U8 Station)
{
	if(StationRecord[Radio_CurrentBand].Freq[Station]==Radio_CurrentFreq)
	{
		return;
	}
	StationRecord[Radio_CurrentBand].Freq[Station]=StationRecord[Radio_CurrentBand].Freq[0];
	Radio_CurrentStation=Station;
	Radio_CurrentFreq=StationRecord[Radio_CurrentBand].Freq[0];
	/*store  station*/
	//Radio_StoreStationRecord(Radio_CurrentBand);
	Radio_StoreStation(Radio_CurrentBand,Radio_CurrentStation);
}
/*-----------------------------------------------------------------------
Function name:	
Input:			
Output:			
Description:	 
------------------------------------------------------------------------*/
void Radio_Para_Init(void)
{
	/*get the tef663x last config stored in eeprom*/		
	/*not store the config in eeprom*/
	if(1)	
	{       
		/*load default parameters*/
		memcpy(Hero_Radio_AM_Parameters,Hero_Radio_AM_DefParameters,CONFIG_PARA_LEN);
		memcpy(Hero_Radio_FM_Parameters,Hero_Radio_FM_DefParameters,CONFIG_PARA_LEN);
		memcpy(StationRecord,StationDefaultRecord,sizeof(StationRecord));	
		/*store config to eeprom*/
		Radio_StoreAll();
	}
	else
	{	    /*load station from eeprom*/    
     	Radio_ReadStationRecord();		
	} 
	  /*init band*/
	Radio_CurrentStation=1;
	Radio_CurrentBand=FM1_BAND;
	Radio_CurrentFreq=StationRecord[Radio_CurrentBand].Freq[Radio_CurrentStation];

}
/*-----------------------------------------------------------------------
Function name:	Radio_Para_WriteAll
Input:			
Output:			
Description:	 write all the radio parameters to hereo
------------------------------------------------------------------------*/
void Radio_Para_WriteAll(void)
{

	if((Radio_CurrentBand<=FM3_BAND))	{
        Radio_FM_Para_Write();
	 }else{
        Radio_AM_Para_Write();
	 }

    
}
void  Radio_AM_Para_Write(void)
{
	
	#if 0
	U8 IIcDataBuff[29];
	IIcDataBuff[0] = 0x03;
	IIcDataBuff[1] = rPara_AM_TUNER;//TUNER//
	IIcDataBuff[2] = rPara_AM_TUNER_OPT;//TUNER_OPT
	IIcDataBuff[3] = rPara_AM_RADIO;//RADIO
	IIcDataBuff[4] = rPara_AM_SIGNAL;//SIGNAL

	IIcDataBuff[5] = 0X05;//BWCTRL
	IIcDataBuff[6] = 0X00;//SPECIAL
	IIcDataBuff[7] = 0X41;//RDS
	IIcDataBuff[8]=0;
	IIcDataBuff[9]=0;
	IIcDataBuff[10] = rPara_AM_LEVEL;//LEVEL_OFFSET
	IIcDataBuff[11] = rPara_AM_SOFTMUTE_TIME;//
	IIcDataBuff[12] = rPara_AM_SOFTMUTE_DET;//
	IIcDataBuff[13] = rPara_AM_SOFTMUTE_LEV;//
	IIcDataBuff[14] = 0x33;//
	IIcDataBuff[15] = rPara_AM_SOFTMUTE_LIM;//
	IIcDataBuff[16] = rPara_AM_HIGHCUT_TIME;//
	IIcDataBuff[17] = rPara_AM_HIGHCUT_DET;//
	IIcDataBuff[18] = rPara_AM_HIGHCUT_LEV;//
	IIcDataBuff[19] = 0x33;//
	IIcDataBuff[20] = rPara_AM_HIGHCUT_LIM;//
	IIcDataBuff[21] = rPara_AM_HIGHCUT_LOC;//
	IIcDataBuff[22] = 0x75;//
	IIcDataBuff[23] = /*0x10*/0x3F;//nick modify 2011-06-28
	IIcDataBuff[24] = 0x4A;//
	IIcDataBuff[25] = 0x33;//
	IIcDataBuff[26] = 0x00;//
	IIcDataBuff[27] = /*0x10*/0x3F;////nick modify 2011-06-28
	IIcDataBuff[28] = /*0x4A*/0x5b;//
	#endif

	U8 IIcDataBuff[29];
	IIcDataBuff[0] = 0x03;
	memcpy(&IIcDataBuff[1],Hero_Radio_AM_Parameters,CONFIG_PARA_LEN);
	I2C1_WriteData(TEF663x_SlaveAddr,IIcDataBuff,CONFIG_PARA_LEN+1);
}
void Radio_FM_Para_Write(void)
{
#if 0
	U8 IIcDataBuff[29];
	IIcDataBuff[0] = 0x03;
	IIcDataBuff[1] = rPara_FM_TUNER;//TUNER//
	IIcDataBuff[2] = 0x00;//TUNER_OPT
	IIcDataBuff[3] = rPara_FM_RADIO;//RADIO
	IIcDataBuff[4] = rPara_FM_SIGNAL;//SIGNAL
	IIcDataBuff[5] = rPara_FM_BWCTRL;//BWCTRL
	IIcDataBuff[6] = rPara_FM_SPECIAL;//SPECIAL
	IIcDataBuff[7] = 0X41;//RDS
	IIcDataBuff[8]=0;
	IIcDataBuff[9]=0;
	IIcDataBuff[10] = rPara_FM_LEVEL;//LEVEL_OFFSET

	//Softmute 
	IIcDataBuff[11] = rPara_FM_SOFTMUTE_TIME;//
	IIcDataBuff[12] = rPara_FM_SOFTMUTE_DET;//
	IIcDataBuff[13] = rPara_FM_SOFTMUTE_LEV;//
	IIcDataBuff[14] = rPara_FM_SOFTMUTE_NM;//
	IIcDataBuff[15] = rPara_FM_SOFTMUTE_LIM;//

	//high cut
	IIcDataBuff[16] = rPara_FM_HIGHCUT_TIME;//
	IIcDataBuff[17] = rPara_FM_HIGHCUT_DET;//
	IIcDataBuff[18] = rPara_FM_HIGHCUT_LEV;//
	IIcDataBuff[19] = rPara_FM_HIGHCUT_NM;//
	IIcDataBuff[20] = rPara_FM_HIGHCUT_LIM;//
	IIcDataBuff[21] = rPara_FM_HIGHCUT_LOC;//

	//stereo
	IIcDataBuff[22] = rPara_FM_STEREO_TIME;//
	IIcDataBuff[23] = rPara_FM_STEREO_DET;
	IIcDataBuff[24] = rPara_FM_STEREO_LEV;//
	IIcDataBuff[25] = rPara_FM_STEREO_NM;//
	IIcDataBuff[26] = rPara_FM_STEREO_LIM;//
	IIcDataBuff[27] = rPara_FM_STEREOHB_DET;//
	IIcDataBuff[28] = rPara_FM_STEREOHB_NM;//
	#endif
	U8 IIcDataBuff[29];
	IIcDataBuff[0] = 0x03;
	
	memcpy(&IIcDataBuff[1],Hero_Radio_FM_Parameters,CONFIG_PARA_LEN);
	I2C1_WriteData(TEF663x_SlaveAddr,IIcDataBuff,CONFIG_PARA_LEN+1);
        
}

/*====================================================
 Function:Radio_Save_Station
 Input: 
      Null
 OutPut:
      Null
 Desp:
     Save one station to mem
=========================================================*/
void Radio_Save_Station(U8 StationNumber ,U16 StationFreq)
{	
	//StationRecord[Radio_CurrentBand].Freq[StationNumber]=StationFreq;

	//EEPROM_Write(EEPRom_StationRecordDefaultAddr + Radio_CurrentBand *sizeof(StationRecord[0]) ,
	//	(U8 *)(&StationRecord[Radio_CurrentBand].Freq[StationNumber]),
	//	2);

}

