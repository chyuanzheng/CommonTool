/***************************************************************************************
* (C) Copyright NXP semiconductor, All rights reserved
* FILE NAME:	<Ftun.h>
* VERSION:		<1.0>
* DESCRIPTION:	Header file for Ftun.c
* DOCUMENT REF: <References to specification or other documents related to this module>
* NOTES:		<File notes>
***************************************************************************************/

#ifndef __FTUN_H 
#define __FTUN_H
#include "6606.h"
/*----------------------------------------
define for tuning step,frequency range,
Seek level,ifcounter for all bands.
-----------------------------------------*/
#ifdef THAILAND
#define FMTuneStep 50  	// unit: KHz
#define FMSeekStep 50 		// unit: KHz
#else
#define FMTuneStep 100  	// unit: KHz
#define FMSeekStep 100 		// unit: KHz
#endif
#define FMmin 87000
#define FMmax 108000
#define FMlevel 0x60
#define FMifcount 15		//unit: KHz	

#define LWmax 288
#define LWmin 144
#define LWTuneStep 9
#define LWSeekStep 9
#define LWlevel 0xB4
#define LWifcount 15		//uint: 0.1KHz	

#define MWmax 1602
#ifdef THAILAND
#define MWmin 531
#else
#define MWmin 522
#endif
#define MWTuneStep 9
#define MWSeekStep 9
#define MWlevel 0xB4
#define MWifcount 15		//uint: 0.1KHz

#define SWmax 18135
#define SWmin 2940
#define SWTuneStep 5
#define SWSeekStep 5
#define SWlevel 0xB4
#define SWifcount 15		//uint: 0.1KHz

#define OIRTmax 74000
#define OIRTmin 65000
#define OIRTTuneStep 10
#define OIRTSeekStep 10
#define OIRTlevel 0xB4
#define OIRTifcount 15 		//uint: KHz	

/*--------------------------------------------------
define for initialization of frequency, band, mono
---------------------------------------------------*/
#define Band_Default Band_FM
#define Frequency_Default FM_Threshold_Freq
#define Forcemono_Default N
#define LW_Threshold_Freq LWmin
#define MW_Threshold_Freq MWmin
#define FM_Threshold_Freq FMmin
#define SW_Threshold_Freq SWmin
#define OIRT_Threshold_Freq OIRTmin

/*-------------------------------------------------
define for Seek Condition
--------------------------------------------------*/
#define Check_USN_WAM TRUE				//Check USN and WAM while doing seek action 
#define SeekCondition_FM_Level 0x80		//FM station stop LEVEL condition
//#define SeekCondition_Ifcount 15		//AM,FM station stop IFCounter condition
#define SeekCondition_FM_Ifcount 15		//FM station stop IFCounter condition    Jimmy modify 20081202 for adding SeekCondition_AM_Ifcount
#define SeekCondition_AM_Ifcount 6		//AM station stop IFCounter condition
#define	SeekCondition_FM_USN 5			//FM station stop USN condition
#define SeekCondition_FM_WAM 5			//FM station stop WAM condition
#define StereoSeparation_Level 0x80		//Stereo indication by LEVEL
#define SeekCondition_AM_Level 210		//AM station stop LEVEL condition
#define SeekDelay_FM 50					//FM delay 5ms in seek action
#define SeekDelay_AM 200				//AM delay 20ms in seek action
#define PresetNum 60						//Preset stations number

/*---------------------------------------------------
Public enum type definition
----------------------------------------------------*/
//enum BAND {Band_LW,Band_MW,Band_FM,Band_SW,Band_OIRT};		//Bands supported in TEF6606
enum BAND{Band_FM, Band_MW, Band_LW, Band_SW,Band_OIRT};
enum DIRECTION {DOWN,UP};									//Seek action direction
enum FORCEMONO {N,Y};										//Force mono output
enum STIN {STIN_MONO,STIN_STEREO,FORCE_MONO};				//Stereo indicator
enum PRESET {PRESET1,PRESET2,PRESET3,PRESET4,PRESET5,PRESET6,NOPRESET};

/*---------------------------------------------------------------------------------------------------
SEEKSTATE is the status while controlling the whole process during the seek action, the detailed
description is given in TEF6606_SW_GUIDELINE_V1.pdf.
---------------------------------------------------------------------------------------------------*/
enum SEEKSTATE {Seek_Configure,Seek_Idle,Seek_Request,Seek_Change_Freqency,Seek_Wait_Level,
				Seek_Check_Level,Seek_Check_USN,Seek_Check_WAM,Seek_Wait_IFC,Seek_Check_IFC,Seek_AMS};

/*------------------------------------------------------------------
STATUS_RADIO implements the radio actions and status in the whole
system which is refered to in resource.c. In version 1.0, the status
except Status_RDS are involved in AtomIC reference design v1.0.
-------------------------------------------------------------------*/
enum STATUS_RADIO{Status_Idle, Status_Seek, Status_AMS, Status_RDS};

/*---------------------------------------------------
Function declaration in Ftun.c
----------------------------------------------------*/
extern void Ftun_Seek(enum DIRECTION direction, uint8 ams, uint8 singlestep);
extern void Ftun_BandSwitch(void);
extern void Ftun_StereoMonoSwitch(void);
extern void Ftun_SaveCurrentStation(uint32 freq, enum PRESET preset);
extern void Ftun_TunetoPreset(enum PRESET preset);
extern enum PRESET Ftun_IsPreset(uint32 freq);
uint8 Ftun_CheckLevel(enum BAND band);
void PresetSort(uint8 count, uint32 *preset_level, uint32 *preset_sta);
extern void Ftun_TunetoFrequency(enum BAND band, uint32 freq, uint8 write_mode);
extern void Ftun_Init(enum BAND band, uint32 freq);

#endif