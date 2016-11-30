#ifndef _HERO_RADIO_DRV_H

#define _HERO_RADIO_DRV_H
#include "HardwareDllModule.h"	//cyf add

//============mac define==================//
#define Radio_ReadBufferLen 0x16

/*tuner read address define*/
#define Radio_STATUS	0x00
#define Radio_LEVEL		0x01
#define Radio_USN		0x02
#define Radio_WAM		0x03
#define Radio_FOF		0x04
#define Radio_IFBW		0x05
#define Radio_MOD		0x06
#define Radio_RDS		0x07
#define Radio_AGCATT 	0x12
#define TEF663x_IDENT 	0x15 

/*hero tuner mode */
#define Radio_POWERDOWNMODE 0
#define Radio_PRESETMODE 	0x10
#define Radio_SEARCHMODE 	0x20
#define Radio_AFUPDATEMODE	0x30
#define Radio_JUMPMODE		0x40
#define Radio_CHECKMODE		0x50
#define Radio_ENDMODE		0x70


/*==REG TUNER==*/
#define FM_TUNER_RES      (0x00)
#define AM_TUNER_RES      (0x00)
/*RF AGC*/
#define FM_RFAGC_92DBUV   (0x00<<6)
#define FM_RFAGC_89DBUV   (0x01<<6)
#define FM_RFAGC_86DBUV   (0x02<<6)
#define FM_RFAGC_83DBUV   (0x03<<6)
#define AM_RFAGC_97DBUV   (0x00<<6)
#define AM_RFAGC_94DBUV   (0x01<<6)
#define AM_RFAGC_91DBUV   (0x02<<6)
#define AM_RFAGC_88DBUV   (0x03<<6)
/*IF Bandwidth */
#define FM_BW_AUTO     0x00
#define FM_BW_KHZ(x)   ((x-72)/17+1)&0x0F
#define AM_BW_AUTO     0x00
#if HERO_VER_V1C05
#define AM_BW_HZ(x)   ((x-1800)/400+1)&0x0F
#else 
#define AM_BW_HZ(x)   ((x-2400)/400+1)&0x0F
#endif
/*==REG TUNER_OPT==*/
#define FM_TUNER_OPT_RES      (0x00)
#define AM_TUNER_OPT_RES      (0x00)
/*AM Anttenna type*/
#define AM_ANT_PASSIVE  (0x00)
#define AM_ANT_ACTIVE   (0x01<<7)
/*Antenna attenuation*/
#define AM_ATT_0DB      (0x00)
#define AM_ATT_6DB      (0x01<<4)
#define AM_ATT_12DB     (0x02<<4)
#define AM_ATT_18DB     (0x03<<4)
#define AM_ATT_24DB     (0x04<<4)
#define AM_ATT_30DB     (0x05<<4)
#define AM_ATT_36DB     (0x06<<4)
#define AM_ATT_42DB     (0x07<<4)
/*Scanning antenna diversity */
#define FM_SAD_OFF      (0x00)
#define FM_SAD_ON       (0x01<<1)


/*==REG RADIO==*/
#define FM_RADIO_RES      (0x02)
#define AM_RADIO_RES      (0x40)
/*Improved Multpath suppression*/
#define FM_IMS_ON       (0x01<<7)
#define FM_IMS_OFF      (0x00)
#define FM_EMS_ON FM_IMS_ON
/*Click Noise Suppression*/
#define FM_CNS_ON       (0X01<<6)
#define FM_CNS_OFF      (0x00)
/*Channel Equalizer*/
#define FM_CE_ON        (0x01<<5)
#define FM_CE_OFF       (0x00)
/*Noise Blanker*/
#define NBSA_OFF       (0x00)
#define NBSA_LOW_SENS  (0x01<<2)
#define NBSA_MID_SENS  (0x02<<2)
#define NBSA_HIGH_SENS (0x03<<2)
/*Sencondary  Noise blanker*/
#define AM_NBSB_OFF       (0x00)
#define AM_NBSB_LOW_SENS  (0x01<<2)
#define AM_NBSB_MID_SENS  (0x02<<2)
#define AM_NBSB_HIGH_SENS (0x03<<2)

/*==REG SIGNAL==*/
#define FM_SIGNAL_RES        (0x00)
#define AM_SIGNAL_RES        (0x00)
/*Force Mono On/Off*/
#define FM_MONO_ON           (0x01<<7)
#define FM_MONO_OFF          (0x00)
/*digital radio on/off*/
#define DRADIO_ON            (0x01<<6)
#define DRADIO_OFF           (0x00)
/*AM High Pass */
#define AM_FLOC_20HZ          (0x00)
#define AM_FLOC_50HZ          (0x01<<2)
#define AM_FLOC_100HZ         (0x02<<2)
#define AM_FLOC_200HZ         (0x03<<2)
/*AM Low Pass */
#define AM_LP_5KHZ          (0x00)
#define AM_LP_3KHZ          (0x01)
#define AM_LP_2KHZ          (0x02)
#define AM_LP_1P5KHZ        (0x03)
/*FM De-emphasis*/
#define FM_DEMP_75US        (0x02)
#define FM_DEMP_50US        (0x01)

/*==REG BWCTRL==*/
#define FM_BWCTRL_RES        (0x00)
#define AM_BWCTRL_RES        (0x05)
/*Automatic bandwidth control sensitivity*/
#define FM_BWS_LOW_SENS      (0x00<<2)
#define FM_BWS_MID_SENS      (0x01<<2)
#define FM_BWS_HIGH_SENS     (0x02<<2)
#define FM_BWS_HIGHEST_SENS  (0x03<<2)
/*Automatic bandwidth control sensitivity at low level */
#define FM_BWLEV_LOW_SENS      (0x00<<2)
#define FM_BWLEV_MID_SENS      (0x01<<2)
#define FM_BWLEV_HIGH_SENS     (0x02<<2)
#define FM_BWLEV_HIGHEST_SENS  (0x03<<2)

/*==REG SPECIAL==*/
#define FM_SPECIAL_RES        (0x00)
#define AM_SPECIAL_RES        (0x00)
/*Quality status interrupt */
#define QSI_NO_INT            (0x00)
/*Fast quality change interrupt  (premium feature) */
#define FM_FQCI_ON            (0x01<<4)
#define FM_FQCI_OFF           (0x00)
/*AF-update on Pause  (premium feature) */
#define FM_AFUP_ON            (0x01)
#define FM_AFUP_OFF           (0x00)

/*==REQ RDS==*/
#define FM_RDS_RES           (0x00)
#define AM_RDS_RES           (0x41)
/*New RDS start */
#define FM_NWSY_RESTART      (0x01<<7)
/*New RDS start on tuning */
#define FM_TUSY_ON        (0x01<<6)
#define FM_TUSY_OFF       (0x00)
/* Legacy MMBS mode  */
#define FM_RBDS_ON        (0x01<<5)
#define FM_RBDS_OFF       (0x00)
/*RDS output mode */
#define FM_RDO_NO_PIN                  (0x00<<2)
#define FM_RDO_DEMODULATOR_OUTPUT      (0x01<<2)
#define FM_RDO_INT_OUTPUT              (0x02<<2)
/*RDS operation mode */
#define FM_RDSM_DECODER                (0x01)
#define FM_RDSM_DEMODULATOR            (0x00)

/*==REG LEVEL_OFFSET==*/
#define FM_LEVEL_OFFSET_RES           (0x00)
#define AM_LEVEL_OFFSET_RES           (0x00)
/*level offset*/
#define LEVO_DB(x)  (0x30+x)

/*==REG SOFTMUT_TIME==*/
#define FM_SOFTMUT_TIME_RES           (0x00)
#define AM_SOFTMUT_TIME_RES           (0x60)
/*Fast softmute attack and decay time */
#define FM_MFT_1MS     (0x00<<5)
#define FM_MFT_2MS     (0x01<<5)
#define FM_MFT_4MS     (0x02<<5)
#define FM_MFT_8MS     (0x03<<5)
#define FM_MFT_15MS    (0x04<<5)
#define FM_MFT_30MS    (0x05<<5)
#define FM_MFT_60MS    (0x06<<5)
#define FM_MFT_120MS   (0x07<<5)
/*Slow softmute attack time */
#define MAT_60MS     (0x00<<2)
#define MAT_120MS    (0x01<<2)
#define MAT_250MS    (0x02<<2)
#define MAT_500MS    (0x03<<2)
#define MAT_1S       (0x04<<2)
/*Slow softmute decay time */
#define MDT_2TIMES      (0x00)
#define MDT_4TIMES      (0x01)
#define MDT_8TIMES      (0x02)
#define MDT_16TIMES     (0x03)

/*==REG SOFTMUTE_DET==*/
#define FM_SOFTMUTE_DET_RES           (0x00)
#define AM_SOFTMUTE_DET_RES           (0x00)
/*Softmute on modulation  (premium feature) */
#define AM_MMOD_OFF          (0x00)
#define AM_MMOD_WEAK         (0x01<<6)
#define AM_MMOD_MID          (0x02<<6)
#define AM_MMOD_STRONG       (0x03<<6)
/* Softmute fast timing on level */
#define FM_MFOL_OFF          (0x00)
#define FM_MFOL_ON           (0x01<<5)
/*Softmute slow timing on level */
#define MSOL_OFF          (0x00)
#define MSOL_ON           (0x01<<4)
/*Softmute fast timing on noise (USN) */
#define FM_MFON_OFF          (0x00)
#define FM_MFON_ON           (0x01<<3)
/*Softmute slow timing on noise (USN) */ 
#define FM_MSON_OFF          (0x00)
#define FM_MSON_ON           (0x01<<2)
/*MFOM  Softmute fast timing on multipath (WAM) */
#define FM_MFOM_OFF          (0x00)
#define FM_MFOM_ON           (0x01<<1)
/*0  MSOM  Softmute slow timing on multipath (WAM)  */
#define FM_MSOM_OFF          (0x00)
#define FM_MSOM_ON           (0x01)

/*==REG SOFTMUTE_LEV==*/
#define FM_SOFTMUTE_LEV_RES           (0x00)
#define AM_SOFTMUTE_LEV_RES           (0x00)
/*Softmute start on level 

FM  0000 = 0 dB V, start on low level (weak control) 
  
	0001  
	|    = 2 dB V dB V, 2 dB step size  
	0110 
	0111 = 14 dB V, default start on level   
	1000 
	|    = 16 dB V dB V, 2 dB step size  
	1110 
	1111 = 30 dB V, start on high level (strong control) 
AM   0000 = 16 dB V, start on low level (weak control) 
	0001  
	|    = 18 dB V dB V, 2 dB step size  
	0110 
	0111 = 30 dB V, default start on level   
	1000 
	|    =  32 dB V dB V, 2 dB step size  
	1110 */
#define FM_MST_DBUV(x)   ((x/2)<<3)
#define AM_MST_DBUV(x)   (((x-16)/2)<<3)
/*Softmute slope on level
000 = 30 dB wide level range (weak control) 
001 = 26 dB level range 
010 = 22 dB level range   
011 = 18 dB level range 
100 = 15 dB level range 
101 = 12 dB level range 
110 = 9 dB level range  
111 = 6 dB narrow level range (strong control)  */
#define MSL_30DB     0x00
#define MSL_26DB     0x01
#define MSL_22DB     0x02
#define MSL_18DB     0x03
#define MSL_15DB     0x04
#define MSL_12DB     0x05
#define MSL_9DB      0x06
#define MSL_6DB      0x07

/*==REG SOFTMUTE_N_M.==*/ 
#define FM_SOFTMUTE_N_M_RES           (0x00)
#define AM_SOFTMUTE_N_M_RES           (0x33)

/*[ 6:4 ]  MNS  Softmute on noise (USN) sensitivity 
FM   000 = 68% USN start, weak control on noise 
001 = 62% USN start 
010 = 56% USN start 
011 = 50% USN start, moderate control on noise   
100 = 44% USN start 
101 = 38% USN start 
110 = 32% USN start 
111 = 26% USN start, strong control on noise */
#define FM_MNS_68PERCENT_START  (0x00<<4) 
#define FM_MNS_62PERCENT_START  (0x01<<4) 
#define FM_MNS_56PERCENT_START  (0x02<<4) 
#define FM_MNS_50PERCENT_START  (0x03<<4) 
#define FM_MNS_44PERCENT_START  (0x04<<4) 
#define FM_MNS_38PERCENT_START  (0x05<<4) 
#define FM_MNS_32PERCENT_START  (0x06<<4) 
#define FM_MNS_26PERCENT_START  (0x07<<4) 
/*[ 2:0 ]  MMS  Softmute on multipath (WAM) sensitivity 
FM   000 = 68% WAM start, weak control on multipath 
001 = 62% WAM start 
010 = 56% WAM start 
011 = 50% WAM start, moderate control on multipath   
100 = 44% WAM start 
101 = 38% WAM start 
110 = 32% WAM start 
111 = 26% WAM start, strong control on multipath */
#define FM_MMS_68PERCENT_START  (0x00) 
#define FM_MMS_62PERCENT_START  (0x01) 
#define FM_MMS_56PERCENT_START  (0x02) 
#define FM_MMS_50PERCENT_START  (0x03) 
#define FM_MMS_44PERCENT_START  (0x04) 
#define FM_MMS_38PERCENT_START  (0x05) 
#define FM_MMS_32PERCENT_START  (0x04) 
#define FM_MMS_26PERCENT_START  (0x05) 
/*== REG SOFTMUTE_LIM == */
#define FM_SOFTMUTE_LIM_RES           (0x00)
#define AM_SOFTMUTE_LIM_RES           (0x00)
/*[ 3:0 ]  MLIM  Softmute limit 
	0000 = -40 dB gain limit (maximum softmute attenuation) 
	0001 
	|    = --18 dB gain limit, 2 dB step size 
	1011 
	1100 = -16 dB default gain limit 
	1101 
	|    = -14 -12 dB gain limit 
	1110     
	1111 = -10 dB gain limit (minimum softmute attenuation) 
*/
#define MLIM_LIMIT_GAIN_DB(x)   (((x+40)/2)&0x0F)

/*==REG HIGHCUT_TIME==*/
#define FM_HIGHCUT_TIME_RES           (0x00)
#define AM_HIGHCUT_TIME_RES           (0x60)
/*Fast highcut attack and decay time */
#define FM_HFT_1MS     (0x00<<5)
#define FM_HFT_2MS     (0x01<<5)
#define FM_HFT_4MS     (0x02<<5)
#define FM_HFT_8MS     (0x03<<5)
#define FM_HFT_15MS    (0x04<<5)
#define FM_HFT_30MS    (0x05<<5)
#define FM_HFT_60MS    (0x06<<5)
#define FM_HFT_120MS   (0x07<<5)
/*Slow highcut attack time */
#define HAT_60MS     (0x00<<2)
#define HAT_120MS    (0x01<<2)
#define HAT_250MS    (0x02<<2)
#define HAT_500MS    (0x03<<2)
#define HAT_1S       (0x04<<2)
/*Slow highcut decay time */
#define HDT_2TIMES      (0x00)
#define HDT_4TIMES      (0x01)
#define HDT_8TIMES      (0x02)
#define HDT_16TIMES     (0x03)

/*==REG HIGHCUT_DET==*/
#define FM_HIGHCUT_DET_RES           (0x00)
#define AM_HIGHCUT_DET_RES           (0x00)
/*highcut on modulation 
01 = weak control on modulation, 25% shift 
10 = moderate control on modulation, 50% shift 
11 = strong control on modulation, 75% shift  */
#define HMOD_OFF          (0x00)
#define HMOD_WEAK         (0x01<<6)
#define HMOD_MID          (0x02<<6)
#define HMOD_STRONG       (0x03<<6)
/* highcut fast timing on level */
#define FM_HFOL_OFF          (0x00)
#define FM_HFOL_ON           (0x01<<5)
/*highcut slow timing on level */
#define HSOL_OFF          (0x00)
#define HSOL_ON           (0x01<<4)
/*highcut fast timing on noise (USN) */
#define FM_HFON_OFF          (0x00)
#define FM_HFON_ON           (0x01<<3)
/*highcut slow timing on noise (USN) */ 
#define FM_HSON_OFF          (0x00)
#define FM_HSON_ON           (0x01<<2)
/*MFOM  highcut fast timing on multipath (WAM) */
#define FM_HFOM_OFF          (0x00)
#define FM_HFOM_ON           (0x01<<1)
/*0  MSOM  highcut slow timing on multipath (WAM)  */
#define FM_HSOM_OFF          (0x00)
#define FM_HSOM_ON           (0x01)

/*==REG HIGHCUT_LEV==*/
#define FM_HIGHCUT_LEV_RES           (0x00)
#define AM_HIGHCUT_LEV_RES           (0x00)
/*Highcut start on level 
FM   0000 = 20 dB V, start on low level (weak control) 
	0001  
	|    = 22 dB V 30 dB V, 2 dB step size  
	0101 
	0110 = 32 dB V, default start on level   
	0111 
	|    = 34 dB V 48 dB V, 2 dB step size  
	1110 
	1111 = 50 dB V, start on high level (strong control) 

AM   0000 = 30 dB V, start on low level (weak control) 
	0001  
	|    = 32 dB V 40 dB V, 2 dB step size  
	0101 
	0110 = 42 dB V, default start on level   
	0111 
	|    =  44 dB V 58 dB V, 2 dB step size  
	1110 
	1111 = 60 dB V, start on high level (strong control) 
*/
#define FM_HST_DBUV(x)   (((x-20)/2)<<3)
#define AM_HST_DBUV(x)   (((x-30)/2)<<3)
/*Highcut slope on level 
FM   000 = 30 dB wide level range (weak control) 
AM 
	001 = 26 dB level range 
	010 = 22 dB level range   
	011 = 18 dB level range  
	100 = 15 dB level range 
	101 = 12 dB level range 
	110 = 9 dB level range  
	111 = 6 dB narrow level range (strong control) */
#define HSL_30DB     0x00
#define HSL_26DB     0x01
#define HSL_22DB     0x02
#define HSL_18DB     0x03
#define HSL_15DB     0x04
#define HSL_12DB     0x05
#define HSL_9DB      0x06
#define HSL_6DB      0x07

/*==REG HIGHCUT_N_M.==*/ 
#define FM_HIGHCUT_N_M_RES           (0x00)
#define AM_HIGHCUT_N_M_RES           (0x33)

/*[ 6:4 ]  MNS  Highcut on noise (USN) sensitivity 
FM   000 = 54% USN start, weak control on noise 
	001 = 48% USN start 
	010 = 42% USN start 
	011 = 36% USN start, moderate control on noise   
	100 = 30% USN start 
	101 = 24% USN start 
	110 = 18% USN start 
	111 = 12% USN start, strong control on noise  */
#define FM_MNS_54PERCENT_START  (0x00<<4) 
#define FM_MNS_48PERCENT_START  (0x01<<4) 
#define FM_MNS_42PERCENT_START  (0x02<<4) 
#define FM_MNS_36PERCENT_START  (0x03<<4) 
#define FM_MNS_30PERCENT_START  (0x04<<4) 
#define FM_MNS_24PERCENT_START  (0x05<<4) 

/*[ 2:0 ]  MMS  Softmute on multipath (WAM) sensitivity 
Highcut on multipath (WAM) sensitivity 
FM   000 = 54% WAM start, weak control on multipath 
	001 = 48% WAM start 
	010 = 42% WAM start 
	011 = 36% WAM start, moderate control on multipath   
	100 = 30% WAM start 
	101 = 24% WAM start 
	110 = 18% WAM start 
	111 = 12% WAM start, strong control on multipath */
#define FM_MMS_54PERCENT_START  (0x00) 
#define FM_MMS_48PERCENT_START  (0x01) 
#define FM_MMS_42PERCENT_START  (0x02) 
#define FM_MMS_36PERCENT_START  (0x03) 
#define FM_MMS_20PERCENT_START  (0x04) 
#define FM_MMS_24PERCENT_START  (0x05) 

/*== REG HIGHCUT_LIM == */
#define FM_HIGHCUT_LIM_RES           (0x00)
#define AM_HIGHCUT_LIM_RES           (0x00)
/*Highcut filter type 
    0 = low pass filter with controlled frequency 
FM  1 = low pass filter 1 kHz with controlled stop band attenuation  
         + low pass filter with controlled frequency (7 kHz limit) 
AM  1 = reserved, keep logic 0 */
#define FM_HFIL_LP_NO_ATT  (0x00)
#define FM_HFIL_LP_WITH_ATT  (0x01<<7)

/*[ 5:4 ]  HSLIM  Highcut start limit 
FM  00 = unlimited, no fixed bandwidth limitation 
AM 
01 = 15 kHz fixed bandwidth limitation 
10 = 10 kHz fixed bandwidth limitation 
11 = 7 kHz fixed bandwidth limitation */
#define HSLIM_BW_START_UNLIMIT  (0x00)
#define HSLIM_BW_START_15KHZ    (0x01<<4)
#define HSLIM_BW_START_10KHZ    (0x02<<4)
#define HSLIM_BW_START_7KHZ     (0x03<<4)
/*[ 2:0 ]  HLIM  Highcut limit 
FM  	000 = 1 kHz bandwidth limit (strong highcut filter)  
AM 	001 = 1.5 kHz bandwidth limit
	010 = 2 kHz bandwidth limit 
	011 = 2.5 kHz bandwidth limit     
	100 = 3 kHz bandwidth limit     
	101 = 4 kHz bandwidth limit     
	110 = 5 kHz bandwidth limit     
	111 = 7 kHz bandwidth limit (weak highcut filter) */
#define HLIM_BW_CUT_1KHZ    0x00
#define HLIM_BW_CUT_1P5KHZ  0x01
#define HLIM_BW_CUT_2KHZ    0x02
#define HLIM_BW_CUT_2P5KHZ  0x03
#define HLIM_BW_CUT_3KHZ    0x04
#define HLIM_BW_CUT_4KHZ    0x05
#define HLIM_BW_CUT_5KHZ    0x06
#define HLIM_BW_CUT_7KHZ    0x07

/*==REG  HIGHCUT_LOC.==*/
#define FM_HIGHCUT_LOC_RES           (0x00)
#define AM_HIGHCUT_LOC_RES           (0x00)
/*[ 2:0 ]  HLOC  Low cut limit  (premium feature) 
FM   000 = off, no low cut  
AM 	001 = 30 Hz, weak low cut 
	010 = 70 Hz 
	011 = 100 Hz     
	100 = 140 Hz, moderate low cut     
	101 = 200 Hz     
	110 = 300 Hz     
	111 = 500 Hz, strong low cut */
#define HLOC_OFF    0x00
#define HLOC_30HZ   0x01
#define HLOC_70HZ   0x02
#define HLOC_100HZ  0x03
#define HLOC_140HZ  0x04
#define HLOC_200HZ  0x05
#define HLOC_300HZ  0x06
#define HLOC_500HZ  0x07

/*==REG STEREO_TIME==*/
#define FM_STEREO_TIME_RES           (0x00)
#define AM_STEREO_TIME_RES           (0x72)
/*Fast softmute attack and decay time */
#define FM_SFT_1MS     (0x00<<5)
#define FM_SFT_2MS     (0x01<<5)
#define FM_SFT_4MS     (0x02<<5)
#define FM_SFT_8MS     (0x03<<5)
#define FM_SFT_15MS    (0x04<<5)
#define FM_SFT_30MS    (0x05<<5)
#define FM_SFT_60MS    (0x06<<5)
#define FM_SFT_120MS   (0x07<<5)
/*Slow stereo attack time */
#define FM_SAT_60MS     (0x00<<2)
#define FM_SAT_120MS    (0x01<<2)
#define FM_SAT_250MS    (0x02<<2)
#define FM_SAT_500MS    (0x03<<2)
#define FM_SAT_1S       (0x04<<2)
/*Slow stereo decay time */
#define FM_SDT_2TIMES      (0x00)
#define FM_SDT_4TIMES      (0x01)
#define FM_SDT_8TIMES      (0x02)
#define FM_SDT_16TIMES     (0x03)

/*==REG STEREO_DET==*/
#define FM_STEREO_DET_RES           (0x00)
#define AM_STEREO_DET_RES           (0x3F)
/*Stereo on modulation  (premium feature) */
#define FM_SMOD_OFF          (0x00)
#define FM_SMOD_WEAK         (0x01<<6)
#define FM_SMOD_MID          (0x02<<6)
#define FM_SMOD_STRONG       (0x03<<6)
/* Stereo fast timing on level */
#define FM_SFOL_OFF          (0x00)
#define FM_SFOL_ON           (0x01<<5)
/*Stereo slow timing on level */
#define FM_SSOL_OFF          (0x00)
#define FM_SSOL_ON           (0x01<<4)
/*Stereo fast timing on noise (USN) */
#define FM_SFON_OFF          (0x00)
#define FM_SFON_ON           (0x01<<3)
/*Stereo slow timing on noise (USN) */ 
#define FM_SSON_OFF          (0x00)
#define FM_SSON_ON           (0x01<<2)
/*MFOM  Stereo fast timing on multipath (WAM) */
#define FM_SFOM_OFF          (0x00)
#define FM_SFOM_ON           (0x01<<1)
/*0  MSOM  Stereo slow timing on multipath (WAM)  */
#define FM_SSOM_OFF          (0x00)
#define FM_SSOM_ON           (0x01)

/*==REG STEREO_LEV==*/
#define FM_STEREO_LEV_RES           (0x00)
#define AM_STEREO_LEV_RES           (0x4A)
/*Stereo start on level 

FM   0000 = 30 dB V, start on low level (weak control) 
	0001  
	|    = 32 dB V dB V, 2 dB step size  
	1000 
	1001 = 48 dB V, default start on level   
	1010 
	|    = 50 dB V dB V, 2 dB step size  
	1110 
	1111 = 60 dB V, start on high level (strong control) 
*/
#define FM_SST_DBUV(x)   (((x-30)/2)<<3)

/*Stereo slope on level
000 = 30 dB wide level range (weak control) 
001 = 26 dB level range 
010 = 22 dB level range   
011 = 18 dB level range 
100 = 15 dB level range 
101 = 12 dB level range 
110 = 9 dB level range  
111 = 6 dB narrow level range (strong control)  */
#define FM_SSL_30DB     0x00
#define FM_SSL_26DB     0x01
#define FM_SSL_22DB     0x02
#define FM_SSL_18DB     0x03
#define FM_SSL_15DB     0x04
#define FM_SSL_12DB     0x05
#define FM_SSL_9DB      0x06
#define FM_SSL_6DB      0x07

/*==REG STEREO_N_M.==*/ 
#define FM_STEREO_N_M_RES           (0x00)
#define AM_STEREO_N_M_RES           (0x33)

/*[ 6:4 ]  MNS  Stereo on noise (USN) sensitivity 
FM   000 = 36% USN start, weak control on noise 
001 = 32% USN start 
010 = 28% USN start 
011 = 24% USN start, moderate control on noise   
100 = 20% USN start 
101 = 16% USN start 
110 = 12% USN start 
111 = 8% USN start, strong control on noise */
#define FM_SNS_36PERCENT_START  (0x00<<4) 
#define FM_SNS_32PERCENT_START  (0x01<<4) 
#define FM_SNS_28PERCENT_START  (0x02<<4) 
#define FM_SNS_24PERCENT_START  (0x03<<4) 
#define FM_SNS_20PERCENT_START  (0x04<<4) 
#define FM_SNS_16PERCENT_START  (0x05<<4) 

/*[ 2:0 ]  MMS  Stereo on multipath (WAM) sensitivity 
FM   000 = 36% WAM start, weak control on multipath 
001 = 32% WAM start 
010 = 28% WAM start 
011 = 24% WAM start, moderate control on multipath   
100 = 20% WAM start 
101 = 16% WAM start 
110 = 12% WAM start 
111 = 8% WAM start, strong control on multipath */
#define FM_SMS_36PERCENT_START  (0x00) 
#define FM_SMS_32PERCENT_START  (0x01) 
#define FM_SMS_28PERCENT_START  (0x02) 
#define FM_SMS_24PERCENT_START  (0x03) 
#define FM_SMS_20PERCENT_START  (0x04) 
#define FM_SMS_16PERCENT_START  (0x05) 

/*== REG STEREO_LIM == */
#define FM_STEREO_LIM_RES           (0x00)
#define AM_STEREO_LIM_RES           (0x00)
/* SSLIM  Stereo start limit   
	FM   000 = >> 40 dB channel separation, unlimited stereo 
		001 = 40 dB channel separation 
		010 = 35 dB channel separation 
		011 = 30 dB channel separation     
		100 = 27 dB channel separation 
		101 = 24 dB channel separation 
		110 = 20 dB channel separation 
		111 = 16 dB channel separation 
*/
#define FM_SSLIM_UNLIMITE  0x00
#define FM_SSLIM_40DB      (0x01<<4)
#define FM_SSLIM_35DB      (0x02<<4)
#define FM_SSLIM_30DB      (0x03<<4)
#define FM_SSLIM_27DB      (0x04<<4)
#define FM_SSLIM_24DB      (0x05<<4)
#define FM_SSLIM_20DB      (0x06<<4)
#define FM_SSLIM_16DB      (0x07<<4)

/*== STEREOHB_DET 
FM stereo high blend detector selection.  
Available for premium variant TEF6638 only.== */
#define FM_STEREOHB_DET_RES           (0x00)
#define AM_STEREOHB_DET_RES           (0x3F)
/*[ 7:6 ]   BMOD  Stereo high blend on modulation  (premium feature) 
FM   00 = off 
	01 = weak control on modulation, 33% shift 
	10 = moderate control on modulation, 67% shift 
	11 = strong control on modulation, 100% shift */
#define FM_BMOD_OFF       0x00
#define FM_BMOD_WEAK     (0x01<<6)
#define FM_BMOD_MID      (0x01<<6)
#define FM_BMOD_STRONG   (0x01<<6)

/*5  BFOL  Stereo high blend fast timing on level  (premium feature) 
FM  	0 = off 
	1 = on */
#define FM_BFOL_OFF   0x00
#define FM_BFOL_ON    (0x01<<5)
/*4  BSOL  Stereo high blend slow timing on level  (premium feature) 
FM  0 = off 
    1 = on */
#define FM_BSOL_OFF  0x00
#define FM_BSOL_ON   (0x01<<4)
/*3  BFON  Stereo high blend fast timing on noise (USN)  (premium feature) 
FM  0 = off 
    1 = on */
#define FM_BFON_OFF  0x00
#define FM_BFON_ON   (0x01<<3)
/*2  BSON  Stereo high blend slow timing on noise (USN)  (premium feature) 
FM  0 = off 
    1 = on */
#define FM_BSON_OFF  0x00
#define FM_BSON_ON   (0x01<<2)    
/*1  BFOM  Stereo high blend fast timing on multipath (WAM)  (premium feature) 
FM  0 = off 
    1 = on */
#define FM_BFOM_OFF  0x00
#define FM_BFOM_ON   (0x01<<1)    
/*
0  BSOM  Stereo high blend slow timing on multipath (WAM)  (premium feature) 
FM  0 = off 
    1 = on */
#define FM_BSOM_OFF  0x00
#define FM_BSOM_ON   (0x01)   


/*==Data byte 1Eh; STEREOHB_LNM 
FM stereo high blend level, ultrasonic noise and multipath detector control sensitivity. 
Available for TEF6638. ==*/
#define FM_STEREOHB_LNM_RES           (0x00)
#define AM_STEREOHB_LNM_RES           (0x13)
/*
[ 6:4 ]  BNMS  Stereo high blend noise (USN) and multipath (WAM) sensitivity   
(premium feature) 
FM   00 = USN and WAM sensitivity equal to SNS, SMS 
	01 = USN and WAM start at 0.7* stereo blend start 
	10 = USN and WAM start at 0.5* stereo blend start 
	11 = USN and WAM start at 0.4* stereo blend start */
#define STEREOHB_USN_WAM_SENS_0           (0x00)
#define STEREOHB_USN_WAM_SENS_1           (0x01<<4)
#define STEREOHB_USN_WAM_SENS_2           (0x02<<4)
#define STEREOHB_USN_WAM_SENS_3           (0x03<<4)

/*[ 2:0 ]  BLS  Stereo high blend level sensitivity   (premium feature) 
FM   000 = start at stereo blend start + 0.06* stereo blend range 
	001 = start at stereo blend start +0.2* stereo blend range 
	010 = start at stereo blend start +0.33* stereo blend range 
	011 = start at stereo blend start +0.46* stereo blend range 
	100 = start at stereo blend start +0.6* stereo blend range 
	101 = start at stereo blend start +0.73* stereo blend range 
	110 = start at stereo blend start +0.87* stereo blend range 
	111 = start at stereo blend start + stereo blend range  */
#define STEREOHB_LEV_SENS_0           (0x00)
#define STEREOHB_LEV_SENS_1           (0x01)
#define STEREOHB_LEV_SENS_2           (0x02)
#define STEREOHB_LEV_SENS_3           (0x03)
#define STEREOHB_LEV_SENS_4           (0x04)
#define STEREOHB_LEV_SENS_5           (0x05)
#define STEREOHB_LEV_SENS_6           (0x06)
#define STEREOHB_LEV_SENS_7           (0x07)
#define STEREOHB_LEV_SENS_8           (0x08)


extern void RadioDrv_Stop(void);
extern void RadioDrv_UpdatePll(U8 Mode,U8 Band,U16 Pll);

extern void RadioDrv_ReadData(U8 Num);
extern U8 CE_HardwareDll_API RadioDrv_GetData(U8 Addr);
extern U8 CE_HardwareDll_API RadioDrv_CheckStereoIndicator(void);		//cyf add "CE_HardwareDll_API"

#endif
