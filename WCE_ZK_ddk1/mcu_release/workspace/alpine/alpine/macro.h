#ifndef MACRO_H
#define MACRO_H

// utiles
#define uchar unsigned char
#define uint unsigned int

/* Peripheral Clock Speed set up in ConfigureOperatingFrequency() */
#define	f1_CLK_SPEED		20000000
#define XIN_FREQ 			f1_CLK_SPEED

/* Switches */
#define POWER
#define FAN_SW		p0_4
#define TFT_SW		p1_5
#define EXTAMP_SW	p1_6
#define DVD_SW		p1_4
#define VDD12_SW	p6_3 //p6_4
#define DTV_SW  	p3_6
//#define LED_SW		p3_3
#define LED_SW		p3_2

#define POWER_SW	p6_2
#define LCD_SW		p4_5


#define NJWSW1		p0_2
#define NJWSW2		p0_7
#define NJW_OUTPUT1	{NJWSW1=0;NJWSW2=0;}
#define NJW_OUTPUT2	{NJWSW1=0;NJWSW2=1;}
#define NJW_OUTPUT3	{NJWSW1=1;NJWSW2=0;}

#define AMPMUTE		p6_0
#define AMPSTBY		p6_1

#define DISK_IN		p5_2

/* car status */
#define ACC			p8_3
#define BACK		p8_4
#define LIGHT		p8_5
#define BRAKE		p8_6

/* KEY */
#define R1RKEY		p1_0
#define R1LKEY		p1_1 
#define R2RKEY		p1_2
#define R2LKEY		p1_3
#define POWERKEY	p5_3


/* DSA */


/* DVD */
#define DVD_SW1		p2_3
#define DVD_SW2		p2_4
#define DISK_EJECT	p2_5
#define DVD_VMUTE	p2_6
#define DVD_AMUTE	p2_7
#define DVDRST		p6_5


/* IR */
#define IR_IN		p1_7
#define DTV_IR		p8_2
#define DVD_IR		p6_4	
#define CUSTOMER_CODE 0x00FF

/* int to 2440 */
#define INT_IR		p8_1
#define INT_MCU		p8_0

/* radio */

/* rds */

/* LEDs */

#define POWERHOLD		p3_7



/* IIC */
#define SDA			p6_6
#define SCL			p6_7
#define SDAD		pd6_6
#define SCLD		pd6_7

/* Common Defines */
#ifndef TRUE
#define TRUE			1
#endif
#ifndef FALSE
#define FALSE			0
#endif

#define ENABLE_IRQ		{_asm(" FSET I");}
#define DISABLE_IRQ		{_asm(" FCLR I");}

//#define IRC_LEFT		0x5e
//#define IRC_RIGHT		0x05
//#define IRC_UP			0x55
//#define IRC_DOWN		0x07
//#define IRC_SELECT		0x06
//#define IRC_RETURN		0x0f

// dvd


#endif /* MACRO_H_INCLUDED */