/***************************************************************************************
* (C) Copyright NXP semiconductor, All rights reserved
* FILE NAME:	<Ftun.c>
* VERSION:		<1.0>
* DESCRIPTION:	Tuner control module
* DOCUMENT REF: <References to specification or other documents related to this module>
* NOTES:		<File notes>
***************************************************************************************/

// =================================================================================================
// Header files
// =================================================================================================
#include "stdafx.h"
#include "6606.h"
#include "Ftun.h"
#include "Dtef6606.h"

// =================================================================================================
// External data
// =================================================================================================
extern uint32 seek_count;	//Timer for waiting action while seeking stations
extern uint8 status;		//Bit4 ~ bit7 indicates Source selected like "Radio","CD","USB","AUX", 
							//while bit0 ~ bit3 indicates status of related source like "Seek","AMS".

// =================================================================================================
// Public data
// =================================================================================================
uint32 CurrentFrequency = Frequency_Default;	//current tuning frequency
enum BAND CurrentBand = Band_Default;			//current tuning band
uint8 CurrentForceMono = Forcemono_Default;		//FM band stereo disabled

//Save frequency of different band, restore when switching band
static uint32 LastBandFreq[5] = 
{LW_Threshold_Freq, MW_Threshold_Freq, FM_Threshold_Freq, SW_Threshold_Freq, OIRT_Threshold_Freq};

static uint32 Preset_Freq[5][PresetNum] = 
{
	{LW_Threshold_Freq,LW_Threshold_Freq,LW_Threshold_Freq,LW_Threshold_Freq,LW_Threshold_Freq,LW_Threshold_Freq},
 	{MW_Threshold_Freq,MW_Threshold_Freq,MW_Threshold_Freq,MW_Threshold_Freq,MW_Threshold_Freq,MW_Threshold_Freq},
 	{FM_Threshold_Freq,FM_Threshold_Freq,FM_Threshold_Freq,FM_Threshold_Freq,FM_Threshold_Freq,FM_Threshold_Freq},
 	{SW_Threshold_Freq,SW_Threshold_Freq,SW_Threshold_Freq,SW_Threshold_Freq,SW_Threshold_Freq,SW_Threshold_Freq},
 	{OIRT_Threshold_Freq,OIRT_Threshold_Freq,OIRT_Threshold_Freq,OIRT_Threshold_Freq,OIRT_Threshold_Freq,OIRT_Threshold_Freq}
 };												//Default Setting of preset stations

uint8 PresetFlag = OFF; 						//Preset station Flag
enum SEEKSTATE SeekState = Seek_Configure; 		//Seek Status while doing seek action

/*-----------------------------------------------------------------------
Function name:	Ftun_TunetoFrequency
Input:			band,frequency,tuner_write_mode
Output:			N/A
Description:	Tune to target frequency.
------------------------------------------------------------------------*/
void Ftun_TunetoFrequency(enum BAND band, uint32 freq, uint8 write_mode)
{
	uint32 fmin,fmax;
	
	switch (band)
	{
		case Band_LW:	fmin = LWmin;
						fmax = LWmax;
						break;
		
		case Band_MW:	fmin = MWmin;
						fmax = MWmax;
						break;
										
		case Band_FM:	fmin = FMmin;
						fmax = FMmax;
						break;
		
		case Band_SW:	fmin = SWmin;
						fmax = SWmax;
						break;
						
		case Band_OIRT: fmin = OIRTmin;
						fmax = OIRTmax;
						break;
		default:break;
		
	}
	if (freq < fmin)
		{	freq = fmin;
			CurrentFrequency = fmin;
		}
	if (freq > fmax)
		{	freq = fmax;
			CurrentFrequency = fmax;
		}
	setFrequency(band,freq,write_mode);
	
}

/*---------------------------------------------------------------------
Function name:	Ftun_Init
Input:			band,frequency
Output:			N/A
Description:	Tuner initialization, including all the parameters and
				weak signal processing setting up,user can specify
				particular configuration for each band according to
				actual test results sepearately.
---------------------------------------------------------------------*/
void Ftun_Init(enum BAND band, uint32 freq)
{	/*****14 write mode registers, can be specified according to different band*****/
	uint8 SetupBuffer_FM[14] = {0x00,0x00,0x09,0x4D,0x99,0x0E,0xCD,0x66,0x15,0xCD,0xEE,0x14,0x40,0x14};
	uint8 SetupBuffer_AM[14] = {0x00,0x24,0x0E,0x56,0x08,0x12,0x55,0x00,0x00,0x00,0x00,0x14,0x40,0x14};
	
	switch(band)
	{
	case Band_FM:
	case Band_OIRT:
	writeTunerRegister(ATomIC_I2C_Addr, ATomIC_I2C_SubType, ATomIC_I2C_WriteMode_None|ATomIC_I2C_SetupAdr, SetupBuffer_FM, 14);
	break;
	case Band_MW:
	case Band_LW:
	case Band_SW:
	writeTunerRegister(ATomIC_I2C_Addr, ATomIC_I2C_SubType, ATomIC_I2C_WriteMode_None|ATomIC_I2C_SetupAdr, SetupBuffer_AM, 14);
	break;
	}
	Ftun_TunetoFrequency(band,freq,ATomIC_I2C_WriteMode_Preset);
}

/*---------------------------------------------------------------------
Function name:	Ftun_IsPreset
Input:			frequency
Output:			preset station
Description:	Judge if preset station or not
---------------------------------------------------------------------*/
enum PRESET Ftun_IsPreset (uint32 freq)
{	uint8 i;
	
	if (PresetFlag != OFF)		//Tuner already tunes to a preset station 
		{
		return PRESET(PresetFlag-1);}
	
	for (i=0;i<PresetNum;i++)	//query if it's a preset station
		if (freq == Preset_Freq[CurrentBand][i])
			return PRESET(i);
}

/*---------------------------------------------------------------------
Function name:	Ftun_Seek
Input:			direction,auto_store,single_step
Output:			N/A
Description:	Tuning action including single step tune, seek, 
				auto search and store
---------------------------------------------------------------------*/
void Ftun_Seek(enum DIRECTION direction, uint8 ams, uint8 singlestep)
{	
	static uint32 step,max,min;
	static uint8 i=0;						//Total numbers of preset stations
	uint8 j=0,ifc_value=0;
	static uint32 freq;
	static uint16 stepnum;					//Step numbers going on of seeking action
	static uint32 temp_preset_level[64]; 	//Buffer of preset stations,MSB 8 bit stores level, 
											//LSB 24 bit stores frequency
	
	switch (SeekState) {
	
		case Seek_Idle:
			Ftun_TunetoFrequency(CurrentBand,CurrentFrequency,ATomIC_I2C_WriteMode_Preset);
			stepnum = 0;
			//status = (status & 0xf0) | Status_Idle;
			SeekState = Seek_Configure;
		break;
		case Seek_Configure:
			switch(CurrentBand)				//setting up of tuning step and edge limit subject to different bands
			{
			case Band_LW:	step = LWSeekStep;
							max = LWmax;
							min = LWmin;
							break;
			case Band_MW:	step = MWSeekStep;
							max = MWmax;
							min = MWmin;
							break;
			case Band_FM:	step = FMSeekStep;
							max = FMmax;
							min = FMmin;
							break;
			case Band_SW:	step = SWSeekStep;
							max = SWmax;
							min = SWmin;
							break;
			case Band_OIRT:	step = OIRTSeekStep;
							max = OIRTmax;
							min = OIRTmin;
							break;
			}
			
			while(temp_preset_level[j])							//Clear preset stations buffer
				temp_preset_level[j++] = 0;
			stepnum = 0;
			i = 0;
			j = 0;
			SeekState = Seek_Request;
			//if (singlestep == TRUE)								//Single step tuning up or down
			//	status = (status & 0xf0)| ((uint8)Status_Idle);
			//else
			//	if (ams == TRUE)								//Auto search and store
			//		status = status | ((uint8)Status_AMS);
			//	else											//Seek up or down
			//		status = status | ((uint8)Status_Seek);
			break;
		case Seek_Request:
			if (direction == UP)
				freq=CurrentFrequency+step;
			else
				freq=CurrentFrequency-step; 
			if (freq > max)
				freq= min;
			if (freq < min)
				freq = max;
			if((stepnum++) <= (max-min)/step)
				{SeekState = Seek_Change_Freqency;
				}
			else												//No available stations within the whole band
				if(ams == TRUE)
				SeekState = Seek_AMS;
				else
				SeekState = Seek_Idle;
			break;
		case Seek_Change_Freqency:
			Ftun_TunetoFrequency(CurrentBand,freq,ATomIC_I2C_WriteMode_Search);
			CurrentFrequency = freq;
			if (singlestep == FALSE)							//Seek action, begins to wait level result
				SeekState = Seek_Wait_Level;
			else												//Single step tuning action, turn to Idle
			{	
				SeekState = Seek_Idle;
			}
			break;
		case Seek_Wait_Level:
			if(CurrentBand == Band_LW || CurrentBand == Band_MW || CurrentBand == Band_SW)
				//seek_count = SeekDelay_AM;
				Sleep(SeekDelay_AM);
			else
				//seek_count = SeekDelay_FM;
				Sleep(SeekDelay_FM);
			SeekState = Seek_Check_Level;
			break;
		case Seek_Check_Level:
			//if(seek_count > 0) break;							//Waiting until timer runs up
			if(Ftun_CheckLevel(CurrentBand) == TRUE)			//Meet level condition
			{	if(CurrentBand == Band_FM || CurrentBand == Band_OIRT)
				{
					if(Check_USN_WAM == TRUE)					//Going on with checking USN and WAM
						SeekState = Seek_Check_USN;
					else										//Check IF counter
						SeekState = Seek_Wait_IFC;
				}
				else											//USN and WAM are involved only in FM
					SeekState = Seek_Wait_IFC;
			}
			else												//Not an available station, going on seeking
				SeekState = Seek_Request;
			break;
		case Seek_Check_USN:
			if(getUSN() <= SeekCondition_FM_USN)	
				SeekState = Seek_Check_WAM;
			else
				SeekState = Seek_Request;
			break;
		case Seek_Check_WAM:
			if(getWAM() <= SeekCondition_FM_WAM)
				SeekState = Seek_Wait_IFC;
			else
				SeekState = Seek_Request;
			break;
		case Seek_Wait_IFC:
			if(getIFCounter(FALSE,CurrentBand) == Read_Bit_IFCREADY)		//Waiting until 32ms IF counter result is available
				{
				SeekState = Seek_Check_IFC;
			if(CurrentBand==Band_FM||CurrentBand==Band_OIRT)
				ifc_value=SeekCondition_FM_Ifcount;
			else
				ifc_value=SeekCondition_AM_Ifcount;
				}
			break;
		case Seek_Check_IFC:
			if(getIFCounter(TRUE,CurrentBand) <= ifc_value)          //Jimmy modify 20081203
				{
					if(ams == TRUE)
						SeekState = Seek_AMS;
					else
						SeekState = Seek_Idle;
				}
			else
				SeekState = Seek_Request;
		  
			break;
		case Seek_AMS:
			if(stepnum <= (max-min)/step)
			{
																				
				temp_preset_level[i++] = (getLevel() << 24) | CurrentFrequency;	//save each available station to temp buffer
				SeekState = Seek_Request;
			}
			else
			{													
				PresetSort(i,temp_preset_level,&Preset_Freq[CurrentBand][0]);	//sort total stations according to field 
																				//strength (LEVEL) and save to Preset array
				SeekState = Seek_Idle;
			}
			break;

		default:
			break;
	}
}
/*---------------------------------------------------------------------
Function name:	Ftun_CheckLevel
Input:			band
Output:			N/A
Description:	Check level while doing seek action
---------------------------------------------------------------------*/
uint8 Ftun_CheckLevel(enum BAND band)
{	
	if (band == Band_FM || band == Band_OIRT)
		{ if(getLevel() >= SeekCondition_FM_Level)
			return(TRUE);
		  else
		  	return(FALSE);
		}
	else
		{	if(getLevel() >= SeekCondition_AM_Level)
				return(TRUE);
			else
				return(FALSE);
		}
}
/*---------------------------------------------------------------------
Function name:	PresetSort
Input:			count,*preset_level,*preset_station
Output:			*preset_sta
Description:	Sort preset stations according to signal level, number
				of presets are defined in PresetNum. The bit6 and bit7
				of *preset_level indicate level of each frequency while
				the rest 6 bits	carry the frequency.Save the preset
				stations in sort to *preset_sta.
---------------------------------------------------------------------*/
void PresetSort(uint8 count, uint32 *preset_level, uint32 *preset_sta)
{
	uint8 i,num;
	uint8 j;
	uint32 temp;
	uint32 temp_sta;
	if (count>PresetNum)
		num = PresetNum;
	else
		num = count;
	for (j=0;j<num;j++){
		for(i=count-1;i>j;i--)
  		{
      		if (preset_level[i-1] < preset_level[i])
      		{
      			temp = preset_level[i];
      			preset_level[i] = preset_level[i-1];
      			preset_level[i-1] = temp;
      		}
     	}
	}

	for (j=0;j<num;j++){
		for(i=num-1;i>j;i--)
		{
			if ((preset_level[i-1]&0x00FFFFFF) > (preset_level[i]&0x00FFFFFF))
			{
				temp_sta = preset_level[i]&0x00FFFFFF;
				preset_level[i] = preset_level[i-1]&0x00FFFFFF;
      			preset_level[i-1] = temp_sta;
      		}
    	 }
    	preset_sta[j] = preset_level[j]&0x00FFFFFF;
	} 
} 
/*---------------------------------------------------------------------
Function name:	Ftun_BandSwitch
Input:			N/A
Output:			N/A
Description:	Switch bands among FM,MW,LW,SW,OIRT by means of rotation.
---------------------------------------------------------------------*/
void Ftun_BandSwitch(void)
{	enum BAND band;
	if (CurrentBand == Band_MW)
		band = Band_FM;
	else
		band = (BAND)(CurrentBand + 1);
	LastBandFreq[CurrentBand] = CurrentFrequency;
	Ftun_TunetoFrequency(band, LastBandFreq[band], ATomIC_I2C_WriteMode_Preset);
	CurrentBand = band;
	CurrentFrequency = LastBandFreq[band];
			
}
/*---------------------------------------------------------------------
Function name:	Ftun_StereoMonoSwitch
Input:			N/A
Output:			N/A
Description:	Force mono output
---------------------------------------------------------------------*/
void Ftun_StereoMonoSwitch(void)
{	
	setMono (CurrentForceMono);
	CurrentForceMono = ~CurrentForceMono;
	
}
/*---------------------------------------------------------------------
Function name:	Ftun_SaveCurrentStation
Input:			frequency,preset
Output:			N/A
Description:	Save current frequency to preset station
---------------------------------------------------------------------*/
void Ftun_SaveCurrentStation(uint32 freq, enum PRESET preset)
{	
		Preset_Freq[CurrentBand][preset] = freq;
}
/*---------------------------------------------------------------------
Function name:	Ftun_TunetoPreset
Input:			preset
Output:			N/A
Description:	Tune to preset station
---------------------------------------------------------------------*/
void Ftun_TunetoPreset(enum PRESET preset)
{	uint32 max,min,preset_default;					//preset_default, threshold preset stations
	switch (CurrentBand)
				{
				case Band_LW:	max = LWmax;min = LWmin;
								preset_default = LW_Threshold_Freq; 
								break;
				case Band_MW:	max = MWmax;min = MWmin;	
								preset_default = MW_Threshold_Freq;
								break;
				case Band_FM:	max = FMmax;min = FMmin;				
								preset_default = FM_Threshold_Freq;
								break;
				case Band_SW:	max = SWmax;min = SWmin;	
								preset_default = SW_Threshold_Freq;
								break;
				case Band_OIRT:	max = OIRTmax;min = OIRTmin;	
								preset_default = OIRT_Threshold_Freq;
								break;
				default: break;
				}
	
	/******** read frequency from Preset array ***********/
	if (Preset_Freq[CurrentBand][preset] > max || Preset_Freq[CurrentBand][preset] < min)
		Preset_Freq[CurrentBand][preset] = preset_default;
	
	CurrentFrequency = Preset_Freq[CurrentBand][preset];
	Ftun_TunetoFrequency(CurrentBand,CurrentFrequency,ATomIC_I2C_WriteMode_Preset);
	PresetFlag = (uint8)(preset) + 1;
	
}

