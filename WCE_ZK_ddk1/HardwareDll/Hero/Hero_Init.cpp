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


/*-----------------Scaling config start----------------------*/
//GEQ + TONE + VOLUME + CHANNEL GAIN + CHANNEL PEQ=48.16dB
//chang the dB data to hex Y memory data and replace below

#define ADSP_Y_Vol_DesScalBMTP_Data 0x0200    //ref to max tone gain 		12db
#define ADSP_Y_Vol_DesScalGEq_Data 0x0200   //ref to max geq gain			12db
#define  ADSP_X_Vol_OneOverMaxBoostP_Data  0x081385//ref to GeqMaxResp+ToneBoostMaxP

//peq gain max =6db
#define ADSP_Y_Vol_ScalF_Data   0x400   //ref to max front peq gain                        
#define ADSP_Y_Vol_ScalR_Data   0x400    //ref to max rear peq gain                      
#define ADSP_Y_Vol_ScalSwL_Data 0x400  //ref to max subwoofer left peq gain                       
#define ADSP_Y_Vol_ScalSwR_Data 0x400  //ref to max subwoofer right peq gain 

// the max gain is used do not need to compensate
//comp=48.16dB-(GEQ(12) + TONE(12) + CHANNEL PEQ(6) + MAX VOLUME(12)+ CHANNEL GAIN(6))
#define ADSP_Y_Vol_UpScalF_Data 0x07FF 	 //front compensation
#define ADSP_Y_Vol_UpScalR_Data 0x07FF   	 //rear compensation
#define ADSP_Y_Vol_UpScalSwL_Data 0x07FF	//subwoofer left compensation 
#define ADSP_Y_Vol_UpScalSwR_Data 0x07FF	 //subwoofer right compensation	
/*-----------------Scaling config end-----------------------*/

/*-----------------channel gain config start----------------------*/
//chang the dB data to hex Y memory data and replace below
//all channel use gain is max
#define ADSP_Y_Vol_ChanGainPFL_DefaultData  0x07FF	   //front left channel gain
#define ADSP_Y_Vol_ChanGainPFR_DefaultData  0x07FF	   //front rigt channel gain
#define ADSP_Y_Vol_ChanGainPRL_DefaultData  0x07FF	   //rear left channel gain
#define ADSP_Y_Vol_ChanGainPRR_DefaultData  0x07FF	   //rear right channel gain
#define ADSP_Y_Vol_ChanGainSwL_DefaultData  0x07FF	   //subwoofer left channel gain
#define ADSP_Y_Vol_ChanGainSwR_DefaultData  0x07FF	   //subwoofer right channel gain
#define ADSP_Y_Vol_ChanGainSL_DefaultData   0x07FF	   //secondary left channel gain
#define ADSP_Y_Vol_ChanGainSR_DefaultData   0x07FF	   //secondary right channel gain
#define ADSP_Y_Vol_ChanGainN_DefaultData    0x07FF	   //navigation channel gain
#define ADSP_Y_Vol_ChanGainT_DefaultData    0x07FF	   //phone channel gain
/*-----------------channel gain config end----------------------*/



#define DEMO_KEYCODE 0x800001

/* Spurious signal*/
const U8 SpuriosSignal_init_tab1[]= {0xFF, 0x00, 0x04, 0x01, 0x84, 0xFE, 0xC5, 0xFF, 0xC7 };
const U8 SpuriosSignal_init_tab2[]= {
	0xFF, 0x00, 0x04, 0x0D, 0x68, 0x01, 0x2C, 0x23, 0xD2, 0xFE, 0xC5, 0x24, 0xAE, 0x01, 0x3B, 0x27,
	0x06, 0xFE, 0xC0, 0x27, 0x2E ,0x01 ,0x3B, 0x27, 0x7E, 0x01, 0x3B, 0x27, 0xA6 ,0x01, 0x2C, 0x27, 
	0xCE, 0xFE, 0xD4, 0x20, 0x9E, 0xFE ,0xD4, 0x25, 0xC1, 0xFE, 0xD4, 0x29, 0xE5, 0xFE, 0xC5, 0x29,
	0xEA, 0x01, 0x2C, 0x24, 0x0E, 0xFE, 0xD4, 0x28, 0x2D, 0x01, 0x2C, 0x29 ,0xEF, 0x01, 0x2C, 0x22,
	0xE7, 0x01, 0x2C, 0x22, 0xF1, 0xFE, 0xD4, 0x21, 0xA2 ,0xFE, 0xD4, 0x22, 0x88  };	
const U8 SpuriosSignal_init_tab3[]={ 
 0xFF,0x00,0x04,0x01,0xC0,0x00,0x00,0xFD,0xE8,0x80,0x01,0x43,0xD4,0x00,0x01,0x46,
 0x2D,0x80,0x01,0x6C,0x74,0x00,0x01,0x6E,0xCD,0x80,0x01,0x95,0x14,0x00,0x01,0x97, 
 0x6D};
const U8 SpuriosSignal_init_tab4[]= {0xFF,0x00,0x04,0x01,0xE8,0x00,0x00,0x02, 0x97 };

/*REQUIRED_INITIALISATION**: Host I2S Spurious*/
const U8 I2S_Spurious_Init[]={ 0xFF,0xFF, 0xFF, 0xB0, 0x74, 0x00,0x00,0x00,0xFF};
/*REQUIRED_INITIALISATION**: VCO operation point control*/
const U8 VCO_Control_init_tab1[]={ 
0xF0,0x80,0x00,0x5C,0x00,0xF6,0x1D,0x14,0x00,0x50,0x10,0x7C,0x60,0x80,0x0A,0x7C, 
0x00,0x00,0x00,0x40,0x00,0x06,0x1D,0x49,0x00,0x00,0x10,0x40,0x00,0x00,0x1B,0x49, 
0x00,0x00,0xF4,0x40,0x00,0x01,0x1A,0x49,0x00,0x80,0x2A,0x5C,0x02,0xF0,0x1A,0x14, 
0x00,0x50,0x90,0x14,0x00,0xF6,0x1C,0x68,0x00,0x01,0xFF,0x14,0x00,0x90,0x50,0x50, 
0x00,0x01,0x00,0x14,0x00,0x30,0x00,0x7C,0x10,0x80,0x16,0x7C,0x58,0xD4,0x10,0x68, 
0x00,0x02,0x00,0x08,0x00,0x50,0x50,0x14,0x00,0x30,0x10,0x5C,0x03,0xF0,0x1B,0x14, 
0x00,0x30,0xC0,0x7C,0x10,0x80,0x1D,0x14,0x00,0x70,0x10,0x5C,0x00,0xF6,0x1E,0x14, 
0x00,0x50,0x10,0x14,0x00,0xD0,0x10,0x14,0x00,0xF6,0x1E,0x5C,0x00,0xF6,0x1D,0x14, 
0x00,0x30,0x00,0x7C,0x10,0x80,0x27,0x14,0x00,0x50,0xD0,0x14,0x00,0xE0,0x10,0x14, 
0x00,0x70,0x10,0x14,0x00,0xF6,0x1E,0x14,0x00,0x50,0xD0,0x14,0x00,0xD0,0x10,0x7F, 
0xFC,0x01,0x15,0x14,0x00,0xF0,0x1A,0x7C,0x00,0x00,0x00,0x68,0x00,0x10,0x00,0x5C, 
0x00,0xF0,0x20,0x14,0x00,0x50,0x10,0x50,0x00,0x00,0x01,0x14,0x00,0x30,0x00,0x7C, 
0x58,0x54,0x50,0x7F,0xFC,0x01,0x1B,0x7C,0x68,0x74,0x10,0x26,0x00,0xF0,0x0A
};
const U8 VCO_Control_init_tab2[]={ 0xF0,0x01,0x15,0x00,0x05,0xBA};
const U8 VCO_Control_init_tab3[]={ 0xF0,0x01,0x14,0x00,0x80,0x00};

/*-----------------primary channel volume config start----------------------*/

static U32 Hero_Init_Timer;


/*init step*/
Hero_InitStepDef Hero_Init_Step;




/*-------------------------------------------------------------------------------------------------------------------
function define start
---------------------------------------------------------------------------------------------------------------------*/
S8 Hero_Reset(void);
#if HERO_VER_V1C03
void Hero_Init_ImproveRadioSettingA(void);
void Hero_Init_ImproveRadioSettingA2(void);
void Hero_Init_ImproveAudioSettingA(void);
void Hero_Init_ImproveRadioSettingB(void);
void Hero_Init_ImproveAudioSettingB(void);
void Hero_Init_ImproveAudioSettingC(void);
void Hero_Init_SpuriosSignal(void);
void Hero_Init_IIS_VCOControl(void);
#endif
void Send_Usecase_Command(U8 UseCase);
void Send_keycode_Command(U32 keycode);
 
S8 Hero_Keycode(void);
S8 Hero_AcitveDevice(void);
void Hero_RadioConfigInit(void);
S8 Hero_InitAudioPointer(void);
S8 Hero_InitPeripheral(void);
S8 Hero_InitGPIO(void);
S8 Hero_InitSource(void);
S8 Hero_InitAudio(void);
S8 Hero_InitRadio(void);

S8 Audio_ScalingInit(void);
S8 Audio_InitChannelGain(void);
S8 Audio_LoudnessInit(void);
void Audio_PEQInit(void);
void Audio_DCFilterInit(void);
void Audio_NavPhoneFilterInit(void);
void Audio_CompExpInit(void);
void Audio_LimiterClipDetectInit(void);
S8 Audio_LoudnessInit(void);
void Audio_GSAInit(void);
/*hero power manager*/
void Hero_ShutDownAllGen(void);
void Hero_WarmBootInit(void);
void Audio_DelayInit(void);
void Audio_UltraBassInit(void);
void Audio_ALEInit(void);
/*-------------------------------------------------------------------------------------------------------------------
function define end
---------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------
Input:	
Output:	

Description:  hero cold boot init proc:
For V1C05 Initialize procedure:
1. [Enter the Key codes obtained from NXP to activate the optional features listed in
section 3.1.2]
2. Select the required Use Case (Refer section 1.2.1)
3. Configure the GPIO's that are used in the application, using the ¡°GPIO define¡± highlevel
control (sub address 0xC0 in [RUM], Refer section 2.3)
4. Change the mode of the device to ¡°Active¡± by sending a ¡°Tune¡±-command, for
example ¡°s c0 00 10 26 2A p¡± to tune to an FM-frequency of 97.7 MHz.
5. [Update the audio pointers (only necessary if some optional features should be
integrated in the audio path)] note 1)
6. [Enable the optional features listed in section 3.1.2 using appropriate Easy
Programming commands.]
7. Configure the audio peripherals that are used in the application, using the ¡°Peripheral
Configuration¡± high-level control (sub address 0xA9 in [RUM], Refer section 2.2)
8. Select Source for all supported streams in the selected Use Case, using the
appropriate high-level controls. (Refer sections 2.1 and 3.3 for an overview of the
Source selection commands.)
9. [Initialize specific wanted parameters. Typical examples are the maximum desired
boost for Loudness (refer section 4.8.6) and the desired scaling settings (refer
section 4.2)]note 1)
10. Disable Audio Mute for the appropriate streams
(Primary/Secondary/Navigation/Telephone).
------------------------------------------------------------------------*/
void Init_Hero(void)
{
	Hero_Reset();
#if HERO_VER_V1C03
	Hero_Init_ImproveRadioSettingA();   	//improve audio cmd for V1C 					
#endif
#if HERO_VER_V1C03
	Hero_Init_ImproveAudioSettingA(); 	//improve radio cmd for V1C   
	Hero_Init_ImproveRadioSettingA2();
	Hero_Init_SpuriosSignal();
	Hero_Init_IIS_VCOControl();
#endif
	Hero_Keycode()==HERO_STEP_INIT_OK;
	//Send_Usecase_Command(1); // set the usecase 1
	Send_Usecase_Command(7); // set the usecase 1
	Hero_InitRadio()==HERO_STEP_INIT_OK;
	Hero_AcitveDevice();
#if HERO_VER_V1C03
	Hero_Init_ImproveRadioSettingB();//improve radio cmd for V1C   
#endif
#if HERO_VER_V1C03
	Hero_Init_ImproveAudioSettingB();//improve audio cmd for V1C   
#endif
	Audio_DrvPeripheralSwitch(PERIOHERALID_FDAC,1);	  //enable the front DAC
	Audio_DrvPeripheralSwitch(PERIOHERALID_RDAC,1);	  //enable the rear DAC
	Hero_InitPeripheral()==HERO_STEP_INIT_OK;
	Hero_InitGPIO();//config the GPIO function
	Hero_InitAudio()==HERO_STEP_INIT_OK;
#if HERO_VER_V1C03
	Hero_Init_ImproveAudioSettingC();//improve audio cmd for V1C 
#endif
}

/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: reset the hero and wait untill the hero is able to communicate 	  
------------------------------------------------------------------------*/
S8 Hero_Reset(void)
{
	static U8 Step=0;
	return(HERO_STEP_INIT_OK);
}
#if HERO_VER_V1C03
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: send cmd to improve radio setting for V1C
------------------------------------------------------------------------*/
void Hero_Init_ImproveRadioSettingA(void)
{
	U8 Buffer[6];    

	//Prepare for AM divider/IFAD
	Buffer[0]=0xE1;  
	Buffer[1]=0xD0;
	Buffer[2]=0x61; 
	Buffer[3]=0x23;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,4);	 //start to send data to i2c1 bus

	//Prepare for AM divider/IQC
	Buffer[0]=0xE1;  
	Buffer[1]=0xB0;
	Buffer[2]=0x56; 
	Buffer[3]=0x65;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,4);	 //start to send data to i2c1 bus

	//Set IQC
	Buffer[0]=0xF0;  
	Buffer[1]=0x00;
	Buffer[2]=0x46; 
	Buffer[3]=0x01;
	Buffer[4]=0x10;
	Buffer[5]=0x22;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

}

void Hero_Init_ImproveRadioSettingA2(void)
{
     U8 Buffer[17];
	 
	/* Prepare setting VCO operation point control*/
     Buffer[0]=0xE1;  
	Buffer[1]=0x40;
	Buffer[2]=0xD9; 
	Buffer[3]=0xB1;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,4);	 
     /*Image suppression*/
     Buffer[0]=0xf0;  
	Buffer[1]=0x00;
	Buffer[2]=0x46; 
	Buffer[3]=0x01;
	Buffer[4]=0x10;
	Buffer[5]=0x22;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 
	/* FM Startup*/
	Buffer[0]=0xFF;  
	Buffer[1]=0xFF;
	Buffer[2]=0xFF; 
	Buffer[3]=0xb0;
	Buffer[4]=0x3c;
	Buffer[5]=0x10;
     Buffer[6]=0x0;  
	Buffer[7]=0x01;
	Buffer[8]=0x00; 
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	
	Buffer[0]=0xFF;  
	Buffer[1]=0xc0;
	Buffer[2]=0x60; 
	Buffer[3]=0x00;
	Buffer[4]=0x20;
	Buffer[5]=0x0;
     Buffer[6]=0x0;  
	Buffer[7]=0x0;
	Buffer[8]=0x04; 
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	
     
/* Host I2S Spurious signal*/
	Buffer[0]=0xFF;  
	Buffer[1]=0xFF;
	Buffer[2]=0xFF; 
	Buffer[3]=0xb0;
	Buffer[4]=0x74;
	Buffer[5]=0x0;
     Buffer[6]=0x0;  
	Buffer[7]=0x0;
	Buffer[8]=0xff; 
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: send cmd to improve Audio setting for V1C
------------------------------------------------------------------------*/
void Hero_Init_ImproveAudioSettingA(void)
{
	U8 Buffer[6];    
    /*Prepare for (Host I2S) Spurious */
	Buffer[0]=0xE1;  
	Buffer[1]=0xC1;
	Buffer[2]=0xBC; 
	Buffer[3]=0x11;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,4);	 

}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: send cmd to improve radio setting for V1C
------------------------------------------------------------------------*/
void Hero_Init_ImproveRadioSettingB(void)
{
	U8 Buffer[6];    
     /*IF ADC performance*/
	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x11; 
	Buffer[3]=0x00;
	Buffer[4]=0xDC;
	Buffer[5]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 
     /*Audio Rear output startup*/
	Buffer[0]=0xF2;  
	Buffer[1]=0x06;
	Buffer[2]=0xE9; 
	Buffer[3]=0x7F;
	Buffer[4]=0xFF;
	Buffer[5]=0xFF;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 
     /* AM LO frequency*/	
	Buffer[0]=0xF0;  
	Buffer[1]=0x40;
	Buffer[2]=0x0A; 
	Buffer[3]=0x07;
	Buffer[4]=0xFF;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,5);	

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0E; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x36;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0D; 
	Buffer[3]=0x80;
	Buffer[4]=0x00;
	Buffer[5]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0E; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x37;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0E; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x36;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0D; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x01;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0E; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x5B;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF8;  
	Buffer[1]=0x00;
	Buffer[2]=0x0E; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	Buffer[5]=0x5A;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,6);	 //start to send data to i2c1 bus

	Buffer[0]=0xF0;  
	Buffer[1]=0x40;
	Buffer[2]=0x0A; 
	Buffer[3]=0x00;
	Buffer[4]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,5);	 //start to send data to i2c1 bus
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: send cmd to improve Audio setting for V1C
------------------------------------------------------------------------*/
void Hero_Init_ImproveAudioSettingB(void)
{
	U8 Buffer[13];    
    /*ADC performance*/
	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x20;
	Buffer[5]=0x0A;
	Buffer[6]=0x00;
	Buffer[7]=0xB5;
	Buffer[8]=0xBE;
	Buffer[9]=0x00;
	Buffer[10]=0x12;
	Buffer[11]=0x73;
	Buffer[12]=0xC8;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,13);	 //start to send data to i2c1 bus

	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x18;
	Buffer[5]=0x47;
	Buffer[6]=0x00;
	Buffer[7]=0xF8;
	Buffer[8]=0x00;
	Buffer[9]=0x47;
	Buffer[10]=0x00;
	Buffer[11]=0xF8;
	Buffer[12]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,13);	 //start to send data to i2c1 bus

	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x2C;
	Buffer[5]=0x00;
	Buffer[6]=0x00;
	Buffer[7]=0x07;
	Buffer[8]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	 //start to send data to i2c1 bus
	
	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x48;
	Buffer[5]=0x00;
	Buffer[6]=0x11;
	Buffer[7]=0x80;
	Buffer[8]=0x80;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	 //start to send data to i2c1 bus
	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x50;
	Buffer[5]=0x00;
	Buffer[6]=0x10;
	Buffer[7]=0x80;
	Buffer[8]=0x80;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	 //start to send data to i2c1 bus
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: send cmd to improve Audio setting for V1C
------------------------------------------------------------------------*/
void Hero_Init_ImproveAudioSettingC(void)
{
	U8 Buffer[9];    

	Buffer[0]=0xFF;  
	Buffer[1]=0xC0;
	Buffer[2]=0x60; 
	Buffer[3]=0x70;
	Buffer[4]=0x2C;
	Buffer[5]=0x00;
	Buffer[6]=0x00;
	Buffer[7]=0x01;
	Buffer[8]=0x00;
	I2C1_WriteData(TEF663x_SlaveAddr,Buffer,9);	 //start to send data to i2c1 bus

}

void Hero_Init_SpuriosSignal(void)
{
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)SpuriosSignal_init_tab1,9);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)SpuriosSignal_init_tab2,77);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)SpuriosSignal_init_tab3,33);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)SpuriosSignal_init_tab4,9);	 
}

void Hero_Init_IIS_VCOControl(void)
{

  	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)I2S_Spurious_Init,9);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)VCO_Control_init_tab1,0xcf);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)VCO_Control_init_tab2,6);	 
	I2C1_WriteData(TEF663x_SlaveAddr,(U8 *)VCO_Control_init_tab3,6);	
}
#endif
/*-----------------------------------------------------------------------
Input:	UseCase: hero usecase value:1~4,7
Output:			
Description: set hero work usecase	  
------------------------------------------------------------------------*/
void Send_Usecase_Command(U8 UseCase)
{
	U8 TempData[2];
	U8 Data,i;

	TempData[0]=TEF663x_SUBADDR_USECASE;
	TempData[1]=UseCase<<4;

	for(i=0;i<10;i++)
	{
		I2C1_WriteData(TEF663x_SlaveAddr,TempData,2);	 //start to send data to i2c1 bus

		Hero_ReadBack(TEF663x_SUBADDR_USECASE,1,&Data);//check if write is ok
		if(Data==TempData[1])
		{
			break;
		}
	}	
} 

/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step
Description: send keycode to hero 	  
------------------------------------------------------------------------*/
S8 Hero_Keycode(void)
{
	static U8 Step=0;
	switch(Step)
	{
		case 0:
		{   
#if POLYCHIME_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE); 
#endif
#if FM_CES_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif
#if ULTRABASS_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif
#if ALE_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif
#if GEQ_9BAND_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE); 
#endif
#if AM_PACS_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif

#if WBAND_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif
#if FM_SCANNING_KEYCODE
			Send_keycode_Command(DEMO_KEYCODE);
#endif
		
			Step++;
			return(HERO_STEP_INIT_OK);
		}
		case 1:				   //this will be the last init step
		{
			Step=0;
			return(HERO_STEP_INIT_OK);
		}
	}
	return(HERO_STEP_INIT_OK);
}
/*-----------------------------------------------------------------------

Input:	NULL		
Output:	NULL		
Description: 	active hero device from power down mode 
------------------------------------------------------------------------*/
S8 Hero_AcitveDevice(void)
{	
    Radio_SetFreq(Radio_SEARCHMODE,FM1_BAND,8750); 
	return SUCCESS;	 
}

/*-----------------------------------------------------------------------
Input:	
Output:			 
Description: set scaling, see scaling data value define for more
------------------------------------------------------------------------*/
static const sMemAddr_Data ScalingInitTab[] = {
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_DesScalBMTP,	ADSP_Y_Vol_DesScalBMTP_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_DesScalGEq,	ADSP_Y_Vol_DesScalGEq_Data},
	{I2CDRV_X_MEM,	ADSP_X_Vol_OneOverMaxBoostP,	ADSP_X_Vol_OneOverMaxBoostP_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ScalF,		ADSP_Y_Vol_ScalF_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ScalR,		ADSP_Y_Vol_ScalR_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ScalSwL,		ADSP_Y_Vol_ScalSwL_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ScalSwR,		ADSP_Y_Vol_ScalSwR_Data}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_UpScalF,		ADSP_Y_Vol_UpScalF_Data},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_UpScalR,		ADSP_Y_Vol_UpScalR_Data}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_UpScalSwL,	ADSP_Y_Vol_UpScalSwL_Data}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_UpScalSwR,	ADSP_Y_Vol_UpScalSwR_Data}, 
 	
	//end flag
	{I2CDRV_INVALID,	0,			0},
};

S8 Audio_ScalingInit(void)
{        
	WriteHero_MEM_Tab(ScalingInitTab);//write scaling data to hero

	return SUCCESS;
}
/*-----------------------------------------------------------------------
		  
Input:	
Output:			
Description: set channel gain, see value define for more
------------------------------------------------------------------------*/
static const sMemAddr_Data ChannelGainInitTab[] = {
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainPFL,	ADSP_Y_Vol_ChanGainPFL_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainPFR,	ADSP_Y_Vol_ChanGainPFR_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainPRL,	ADSP_Y_Vol_ChanGainPRL_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainPRR,	ADSP_Y_Vol_ChanGainPRR_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainSwL,	ADSP_Y_Vol_ChanGainSwL_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainSwR,	ADSP_Y_Vol_ChanGainSwR_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainSL,	ADSP_Y_Vol_ChanGainSL_DefaultData}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainSR,	ADSP_Y_Vol_ChanGainSR_DefaultData},
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainN,	ADSP_Y_Vol_ChanGainN_DefaultData}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Vol_ChanGainT,	ADSP_Y_Vol_ChanGainT_DefaultData}, 
 	
	//end flag
	{I2CDRV_INVALID,	0,			0},
};
S8 Audio_InitChannelGain(void)
{
	WriteHero_MEM_Tab(ChannelGainInitTab);//write channel gain data to hero
	
	return SUCCESS;                  
}



/*-----------------------------------------------------------------------
Input:	
Output:			
Description: 	init loudness 
------------------------------------------------------------------------*/
static const sMemAddr_Data LoudnessInitTab[] = {
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_StatLev,		0x07FF},//bass control
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_StatLevT,	0x07FF},//treble control

	//below don`t known because not inmentioned in um, just find in GUI          
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KpBL,		0x02B6},
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KpBH,		0x0809},
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KmBL,		0x0273},
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KmBH,		0x0012},
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KpTL,		0x02B6}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KpTH,		0x02B6}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KmTL,		0x0273}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_KmTH,		0x0012}, 
	{I2CDRV_Y_MEM,	ADSP_Y_Loudf_GchanCorrect,		0x0400}, 
 	
	//end flag
	{I2CDRV_INVALID,	0,			0},
};

S8 Audio_LoudnessInit(void)
{
     Hero_EasyProgrammWrite(ADSP_EASYP_Loudf_StaticCoupled);
	WriteHero_MEM_Tab(LoudnessInitTab);
	return SUCCESS;
}




/*-----------------------------------------------------------------------
Input:	
Output:			
Description: update use of the radio setting	  
------------------------------------------------------------------------*/
void Hero_RadioConfigInit(void)
{
	U8 TempData[3];

	//set audio sample rate frequency shift mode
	TempData[0]=0xC9;
	TempData[1]=0x02;
	TempData[2]=0x01;
	I2C1_WriteData(TEF663x_SlaveAddr,TempData,3);	 //start to send data to i2c1 bus	
}
/*-----------------------------------------------------------------------
Input:	dPAR1,dPAR2,dPAR3: keycode
Output:			
Description: sent keycode to hero	  
------------------------------------------------------------------------*/
 void Send_keycode_Command(U32 keycode)
{
	U8 TempData[4];
	TempData[0]=TEF663x_SUBADDR_KEYCODE;
	TempData[1]=(keycode&0xf00)>>16;
	TempData[2]=(keycode&0xf0)>>8;
	TempData[3]=(keycode&0x0f);

	I2C1_WriteData(TEF663x_SlaveAddr,TempData,4);	 //start to send data to i2c1 bus	
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: 	  graphical spectrum analyzer init
------------------------------------------------------------------------*/
void Audio_GSAInit(void)
{
	Audio_DrvGSASwitch(1);	  //enable the gsa
	WriteHero_MEM_1Word(I2CDRV_X_MEM,ADSP_X_Gsa_InPntr,ADSP_X_PChannelMode_OutL);  //set input to be the GSA source
}
/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: init the audio pointers 	  
------------------------------------------------------------------------*/
S8 Hero_InitAudioPointer(void)
{
	Audio_LimiterClipDetectInit();   //clip detect and limiter init
	return(HERO_STEP_INIT_OK);
}
/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: init the peripherals if used 	  
------------------------------------------------------------------------*/
S8 Hero_InitPeripheral(void)
{
	Audio_DrvSetSPDIFInMode(0);          //analog mode
	//set the AD input mode
	Audio_DrvSetADInMode(0,2);          //AD_0, High common mode  2Vrms
	Audio_DrvSetADInMode(1,2);          //AD_1,High common mode, 2 Vrms
	Audio_DrvSetADInMode(2,2);          //AD_2,High common mode, 2 Vrms
	Audio_DrvSetADInMode(3,2);          //AD_2,High common mode  2Vrms
	//set the I2S input mode
	Audio_DrvSetI2SInMode(0,0);          //I2S_0, philips
	Audio_DrvSetI2SInMode(1,0);          //I2S_1,philips
	Audio_DrvSetI2SInMode(2,0);          //I2S_2,philips
	Audio_DrvSetI2SInMode(3,0);          //Host I2S,philips

	Audio_DrvSetI2SOutMode(0, 0);
	Audio_DrvSetI2SOutMode(1, 0);
	// ÉèÖÃ IIS1 ÎªÊä³ö Rear
	WriteHero_MEM_1Word(I2CDRV_X_MEM, ADSP_X_HIIS0Outpntr, ADSP_X_FrontOutL_REL);
	WriteHero_MEM_1Word(I2CDRV_X_MEM, ADSP_X_HIIS1Outpntr, ADSP_X_RearOutL_REL);


	return(HERO_STEP_INIT_OK);
}

/*-----------------------------------------------------------------------
Function name:	void AudioPEQRRSet( void)
Input:			NULL                           
Output:			NULL
Description:	
               Set PEQ RR channel
------------------------------------------------------------------------*/
/*this table is RearRight channel Parametric EQ setting ,band0- band7,
filters parametrics can get by NXP gui software*/
const U32 tbl_PEQ_Flat_Curve[PEQ_BAND_MAX][10]={
	/*BAND 1:flat,0db*/
	{0x01F2,0x0007 ,0x03E4,0x0C0E, 0x0275, 0x07F1, 0x0000},

	/*BAND 2:flat,0db*/
	{0x0313,0x000e ,0x0627,0x0C1c, 0x0342, 0x07e2, 0x0000},

	/*BAND 3:flat,0db*/
	{0x02F7 ,0x001C ,0x05EE ,0x0C38 ,0x0035,0x07C4,0x0000},

	/*BAND 4:flat,0db*/
	{0x02F7 ,0x001C ,0x05EE ,0x0C38 ,0x0035,0x07C4,0x0000},

	/*BAND 5:flat */
	{0,0x400,0,0,0,0,0,0,0,0,},

	/*BAND 6:flat */
	{0,0x400,0,0,0,0,0,0,0,0},

	/*BAND 7:flat */
	{0,0x400,0,0,0,0,0,0,0,0},
};
void AudioPEQRRSet(void)
{
	int band;
	for(band=BAND1;band<PEQ_BAND_MAX;band++)
	{
	     Audio_DrvPEQSet(RearRight,band,(U32*)tbl_PEQ_Flat_Curve[band]);
	}
}



/*this table is RearLeft channel Parametric EQ setting ,band0- band7,
filters parametrics can get by NXP gui software  ??*/
const U32 tbl_PEQ_RL_Curve[PEQ_BAND_MAX][10]={
	/*BAND 1:100HZ,Q=1.0,Gain=-4db*/
	{0x0375, 0x000B, 0x06EB, 0x0C16, 0x0770 ,0x07E8 ,0x0F43},

	/*BAND 2:200HZ,Q=1.0,Gain=-2db*/
	{0x0059 ,0x0012 ,0x00B2 ,0x0C24 ,0x00C5 ,0x07DB ,0x0F97},

	/*BAND 3:400HZ,Q=1.0,Gain=-1db*/
	{0x05CD ,0x001F ,0x039A ,0x0C3F ,0x029F,0x07BD,0x0FC8},

	/*BAND 4:800HZ,Q=1.0,Gain=0db*/
	{ 0x01B1 ,0x0037 ,0x0362 ,0x0C6E ,0x0009 ,0x0785, 0x0000},

	/*BAND 5:1600HZ,Q=1.0,Gain=-2db*/
	{0x0492 ,0x03E5 ,0x02A7 ,0x092F ,0x0374 ,0x0319 ,0x0559 ,0x06D0 ,0x07F9 ,0x0D00},

	/*BAND 6:3200HZ,Q=1.0,Gain=-4db*/
	{0x05A1 ,0x039B ,0x01C5,0x0AB9 ,0x05F9 ,0x0244 ,0x063A ,0x0546 ,0x0465 ,0x0E1F},

	/*BAND 7:6400HZ,Q=1.0,Gain=-6db*/
	{0x057D ,0x030C ,0x02EC ,0x0D6F ,0x05EF ,0x0123 ,0x0513 ,0x0290,0x0493 ,0x0FCF},

};



/*-----------------------------------------------------------------------
Function name:	void AudioPEQRLSet( void)
Input:			NULL                           
Output:			NULL
Description:	
               Set PEQ RL channel
------------------------------------------------------------------------*/
void AudioPEQRLSet(void)
{
	int band;
	for(band=BAND1;band<PEQ_BAND_MAX;band++)
	{
	     Audio_DrvPEQSet(RearLeft,band,(U32*)tbl_PEQ_Flat_Curve[band]);
	}
}
/*-----------------------------------------------------------------------
Input:			NULL                           
Output:			NULL
Description:	
               Set PEQ FL channel
------------------------------------------------------------------------*/
void AudioPEQFLSet(void)
{
	int band;
	for(band=BAND1;band<PEQ_BAND_MAX;band++)   //using the same para to rear left channel
	{
	     Audio_DrvPEQSet(FrontLeft,band,(U32*)tbl_PEQ_Flat_Curve[band]);
	}

}
/*-----------------------------------------------------------------------
Input:			NULL                           
Output:			NULL
Description:	
               Set PEQ FR channel
------------------------------------------------------------------------*/
void AudioPEQFRSet(void)
{
	int band;
	for(band=BAND1;band<PEQ_BAND_MAX;band++)//using the same para to rear left channel
	{
	     Audio_DrvPEQSet(FrontLeft,band,(U32*)tbl_PEQ_Flat_Curve[band]);
	}

}

/*-----------------------------------------------------------------------
Input:			NULL                           
Output:			NULL
Description:	
               Set PEQ init
------------------------------------------------------------------------*/
void Audio_PEQInit(void)
{
	/*set RL PEQ*/ 
	AudioPEQRLSet();
	/*set RR PEQ*/
	AudioPEQRRSet();

	/*set RL PEQ */
	AudioPEQFLSet();
	/*set RR PEQ*/
	AudioPEQFRSet();
}
/*-----------------------------------------------------------------------
Input:			NULL                           
Output:			NULL
Description:	
               dc filter  init
------------------------------------------------------------------------*/
void Audio_DCFilterInit(void)
{
	/*set primary DCFilter On*/
	Audio_DrvDCFilterSet(PrimaryStr, AUDIO_ON);
}	

 /*-----------------------------------------------------------------------
Input:			locate:USE_RAM,USE_ROM                     
Output:			
Description:	
              Init ClickClack Feature
------------------------------------------------------------------------*/
void ClickClack_Init(void)
{	
	/*extern input connect to click clack generator*/
	Audio_DrvSuperPositionConnect(3,ClickClack,Left);
	/*impose ext on FR*/
	Audio_ImposeExtOnFR(-10);			 
	/*Click clack use ROM*/
	Audio_DrvClickClack_Locate(USE_ROM);
	/*use IIC Command control*/
	Audio_DrvClickClack_ModeSel(I2C_CONTROL);
}


/*-----------------------------------------------------------------------
Input:			NULL                   
Output:			NULL
Description:	
                  Audio Chime Initialize
------------------------------------------------------------------------*/
void AudioChimePDCInit(){
/*Do Nothing Here*/
 
}
/*-----------------------------------------------------------------------
Input:			NULL
Output:			NULL
Description:	
                Auido Tone Init
------------------------------------------------------------------------*/
void AudioToneInit(void)
{
	S8 dBVal=0;
	Audio_DrvBassSet(PrimaryStr, dBVal, _100_HZ); /* primary, bass, +12 db gain, fc = 100 */
	Audio_DrvMidSet(PrimaryStr, dBVal,_500_HZ); /* primary, mid, +12 db gain, fc = 500 */
	Audio_DrvTrebSet(PrimaryStr,dBVal, _10000_HZ); /* primary, treble, +12 db gain, fc = 10kHz */
}
/*Filter Paras
   type: 1st LP shlv
   gain: 0db
   cutoff freq:3400hz*/
U32 tbl_NavPhone_Filter1Coefs[10]=
{
       0x0000 ,0x0200 ,0x06F2 ,0x0ECA ,0x0000,0x0000,0x021C,0x026A,0x0000,0x0000 
};



/*Filter Paras
   type: 1st HP shlv
   gain: 0db
   cutoff freq:100hz*/
U32 tbl_NavPhone_Filter2Coefs[10]=
{
       0x0000 ,0x0200 ,0x01F2 ,0x0E07 ,0x0000,0x0000,0x041B,0x03F1,0x0000,0x0000
};

/*-------------------------------------------------------------------------
input:
     none
output:
      none
 description:
      Nav/Phone filter init,this function is called in Init_Hero

--------------------------------------------------------------------------*/
void Audio_NavPhoneFilterInit(void)
{
	/*Nav Filter set :band pass (100hz--3400hz)*/
	Audio_DrvNavPhoneFilterSet(NavigationFilter,0,tbl_NavPhone_Filter1Coefs);
	Audio_DrvNavPhoneFilterSet(NavigationFilter,1,tbl_NavPhone_Filter2Coefs);
	/*Phone Filter set: band pass (100hz--3400hz)*/
	Audio_DrvNavPhoneFilterSet(PhoneFilter,0,tbl_NavPhone_Filter1Coefs);
	Audio_DrvNavPhoneFilterSet(PhoneFilter,1,tbl_NavPhone_Filter2Coefs);

    //phone stream input and volume set
	//Audio_DrvSetStreamInput(PhoneStr,INPUT_SOURCE_AIN2);
	//Audio_DrvSetVolume(PhoneStr,-26);

	//Audio_DrvSetStreamInput(NavigationStr, INPUT_SOURCE_IIS1);
	//Audio_DrvSetVolume(NavigationStr, -26);
}

/*----------------------------------------------------------------------------
* Input       :null                                                                                                                                      
* Output      :null                                                                                       
* FUNCTION    :Init compressor expander ,this function be called in Init_Hero                       
*---------------------------------------------------------------------------*/
void Audio_CompExpInit(void)
{
	/*enable Compressor and expander*/
	Audio_DrvCompExpControl(AUDIO_OFF,AUDIO_OFF);

	/*Expander parametric set,set expander Threshold -60db*/
	Audio_DrvExpanderSet(-60);

	/*compressor parametric set*/
	Audio_DrvCompressorSet(CompCurve_High, 0, 0, 0);//cure_High ratio=3.0,
}

/*--------------------------------------------------------------------------
 Input 					
 Output      :null                                                                                        
 FUNCTION    :Limiter Clip detect init                                   
-------------------------------------------------------------------------*/
void Audio_LimiterClipDetectInit(void)
{
	/* select limiter configuration 1*/
	Audio_DrvLimiterConfigurationSel(1);

	/*set  front&rear limiter  -1db,*/
	Audio_DrvLimiterSet(Front,-1,AUDIO_ON);

	/*set subcenter limiter  */
	Audio_DrvLimiterSet(SubCenter,-1,AUDIO_ON);

	/*set subwoofer limiter */
	Audio_DrvLimiterSet(SubWoofer,-1,AUDIO_ON);

	/* Front/Rear Limiter Flag generator set,SCD0  ,hight active*/
	Audio_DrvLimiterFlagGenerSet(Front,LimiterFlag_Mask_SCD0,0);
	/*SubCenter Limiter Flag generator set,SCD1  high active*/
	Audio_DrvLimiterFlagGenerSet(SubCenter,LimiterFlag_Mask_SCD1,0);
	/*Subwoofer Limiter Flag generator set,SCD2 , high active*/
	Audio_DrvLimiterFlagGenerSet(SubWoofer,LimiterFlag_Mask_SCD2,0);

	/*Set Clip detector 0 treshold gain=-20 dbFS*/
	Audio_DrvSoftClipDetectSet(SCD0,-20);
	/*Set Clip detector 1 treshold gain=-20 dbFS*/
	Audio_DrvSoftClipDetectSet(SCD1,-20);
	/*Set Clip detector 2 treshold gain=-20 dbFS*/
	Audio_DrvSoftClipDetectSet(SCD2,-20);
}

/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: config the GPIO 	  
------------------------------------------------------------------------*/
S8 Hero_InitGPIO(void)
{
	//Audio_DrvFastMuteConfig(HERO_GPIO_2,1,5,5);//init fastmute,GPIO 2=fastmute function,and release attack time are 5ms,polarity=high
	return(HERO_STEP_INIT_OK);
}
/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: select the source input 	  
------------------------------------------------------------------------*/
S8 Hero_InitSource(void)
{
	return(HERO_STEP_INIT_OK);
}

void VolumeProcInit(void)
{
	Audio_SetVolume(PrimaryStr,20); 

	WriteHero_MEM_1Word(I2CDRV_X_MEM,ADSP_X_Vol_Boost12dB,0);
}

/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step		
Description: config all the audio config 	  
------------------------------------------------------------------------*/
S8 Hero_InitAudio(void)
{
	Audio_ScalingInit();  //init scaling data
	Audio_InitChannelGain(); //init every channel gain
	Audio_DrvPeripheralSwitch(0x28,1); //enable the ADC module
	Audio_DrvSoftMuteSwitch(0xFFFF,0);		//shut down all channels softmute
	Audio_LoudnessInit();//init loudness
	VolumeProcInit();//init volume and set a default volume
	Audio_GSAInit();//graphical spectrum analyzer init
#if (GEQ_9BAND_ENABLE)
	Audio_DrvGEQ9Band_Enable();
#endif
	Audio_SetEQMode(HERO_GEQMODE_NONE);//set the graphical EQ mode to flat
	Audio_PEQInit();//init every channels parametric EQ
	Audio_DCFilterInit();//DC filter init config
	Audio_NavPhoneFilterInit();//navigation and phone channels filter init
	Audio_CompExpInit();//compressor and expander init
	BeepInit();//beep init
	ClickClack_Init();//click-clack init
	Audio_DelayInit();//delay init
	Audio_UltraBassInit();
	Audio_ALEInit();

	return HERO_STEP_INIT_OK;
}

/*-----------------------------------------------------------------------
Input:	
Output:	HERO_STEP_INITTING: hero is initting
		HERO_STEP_INIT_OK: hero has already inited the radio config, the system can go through next step
Description: config radio parameters 	  
------------------------------------------------------------------------*/
S8 Hero_InitRadio(void)
{
     U8 buffer[2];
	buffer[0]=0x00; 
	Radio_Para_Init();
	Hero_RadioConfigInit();//radio special function set
	buffer[1]=0x00;  
	I2C1_WriteData(TEF663x_SlaveAddr,buffer,2);
	Radio_FM_Para_Write();//write Fm default parameters 
	buffer[1]=0x02;
	I2C1_WriteData(TEF663x_SlaveAddr,buffer,2);
	Radio_AM_Para_Write();
	return HERO_STEP_INIT_OK;
}
/*-----------------------------------------------------------------------
Input:	 OnOff: 0=off,others=on
Output:	
Description: 	hero power switch  
------------------------------------------------------------------------*/
void Hero_PowerSwitch(U8 OnOff)
{
	if(OnOff)
	{
	//power on not call this 
	}
	else
	{
		Hero_ShutDownAllGen();    //must shut down all the generator before power down
		TimerDelayMs(30);         //wait for 30ms for the generator to shut down
		//Tuner_Stop();             //hero shut down
	}
}
/*-----------------------------------------------------------------------
Input:	
Output:	
Description: 	shut down all the generator  
------------------------------------------------------------------------*/
void Hero_ShutDownAllGen(void)
{
	Audio_DrvDisableChime();
	Audio_DrvDisableClickClack();  
	Audio_DrvPolyChimeStop();
	Audio_DrvSinGenSwitch(0);  //shut down sin and noise generator, sin and noise use the same disable
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: warm boot init
------------------------------------------------------------------------*/
void Hero_WarmBootInit(void)
{
#if HERO_VER_V1C03
	Hero_Init_ImproveAudioSettingA();   	//improve audio cmd for V1C 
#endif
#if HERO_VER_V1C03
	Hero_Init_ImproveRadioSettingA(); 	//improve radio cmd for V1C   
#endif
	Hero_InitRadio()==HERO_STEP_INIT_OK;
	Hero_AcitveDevice();//A preset or search tuning action is needed to get the Hero out of power down mode
	Audio_DrvPeripheralSwitch(PERIOHERALID_FDAC,1);	 //enable the front DAC
	Audio_DrvPeripheralSwitch(PERIOHERALID_RDAC,1);	 //enable the rear DAC
	Hero_InitAudio()==HERO_STEP_INIT_OK;
	Hero_InitPeripheral()==HERO_STEP_INIT_OK;
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: delay init
------------------------------------------------------------------------*/
void Audio_DelayInit(void)
{
	U16 Channel;

	//all channels
	Channel=Audio_PFLCHANNEL+Audio_PFRCHANNEL+Audio_PRLCHANNEL
		+Audio_PRRCHANNEL+Audio_SWLCHANNEL+Audio_SWRCHANNEL;
	Audio_DrvSetDelay(Channel,0);//all channel delay 0ms	
}
/*-----------------------------------------------------------------------
Input:	
Output:			
Description: Audio Feature UltraBass init
------------------------------------------------------------------------*/
void Audio_UltraBassInit(void)
{
    Audio_DrvUltraBassDisable();
}

/*-----------------------------------------------------------------------
Input:	
Output:			
Description:Audio Feature ALE init
------------------------------------------------------------------------*/
void Audio_ALEInit(void)
{
    Audio_DrvALEDisable();
}

