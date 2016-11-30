/**************************************************************************			
***                                                                          
***   Telechips SYS1-1 Team                          
***                                                                          
***   Module : iPod_interface_UART.h                
***                                                              
**************************************************************************/


/*************************************************************************/
/*Command ID define                                                                                               */
/*************************************************************************/

#ifndef _IPOD_UART_INTERFACE_
#define _IPOD_UART_INTERFACE_


#ifdef IPOD_UART_INCLUDE
#ifdef TCC78X
//uart
#define IPOD_RTX_PORT	HwGPEDAT
#define IPOD_RTX_CON	HwGPEEN
#define IPOD_RX_PIN		Hw5
#define IPOD_TX_PIN		Hw4
//remove detect
#ifdef _BOARD_VERSION_TCC7801_CD_HOST_V10
#define IPOD_RMV_PORT	HwGPBEN
#define IPOD_RMV_CON	HwGPBEN
#define IPOD_RMV_PIN	Hw27
#else
#define IPOD_RMV_PORT	HwGPADAT
#define IPOD_RMV_CON	HwGPAEN
#define IPOD_RMV_PIN	Hw19
#endif
//usb/uart sw switch
#define IPOD_SW_PORT	HwGPADAT
#define IPOD_SW_CON	HwGPAEN
#define IPOD_SW_PIN		Hw20
#endif

#if defined(TCC860x)
#define IPOD_RTX_PORT	HwGDATA_B
#define IPOD_RTX_CON	HwGIOCON_B
#define IPOD_RX_PIN		Hw9
#define IPOD_TX_PIN		Hw8
//remove detect
#define IPOD_RMV_PORT	HwGDATA_A
#define IPOD_RMV_CON	HwGIOCON_A
#define IPOD_RMV_PIN	Hw3
//usb/uart sw switch
#define IPOD_SW_PORT
#define IPOD_SW_CON
#define IPOD_SW_PIN
#endif

#if defined(TCC83XX)
//uart 0	//don't used uart0 because of BM pin
//#define IPOD_RTX_PORT	HwGDATA_B
//#define IPOD_RTX_CON	HwGIOCON_B
//#define IPOD_RX_PIN		Hw8
//#define IPOD_TX_PIN		Hw9
//uart 3
#define IPOD_RTX_PORT	HwGDATA_F
#define IPOD_RTX_CON	HwGIOCON_F
#define IPOD_RX_PIN		Hw12
#define IPOD_TX_PIN		Hw13
//remove detect
#define IPOD_RMV_PORT	HwGDATA_B
#define IPOD_RMV_CON	HwGIOCON_B
#define IPOD_RMV_PIN	Hw6
//usb/uart sw switch
#define IPOD_SW_PORT	HwGDATA_B
#define IPOD_SW_CON	HwGIOCON_B
#define IPOD_SW_PIN		Hw15
#endif

#if defined(TCC80XX)
#define IPOD_RTX_PORT	HwGPIOPU_DAT
#define IPOD_RTX_CON	HwGPIOPU_DOE
#define IPOD_RTX_SEL	HwGPIOPU_FS0
#define IPOD_RX_PIN		Hw1
#define IPOD_TX_PIN		Hw0
#endif



#endif

extern int IPOD_API_UART_MountDev(void);



#ifdef TCC860x
extern void IPOD_UartInit(void);
#endif

extern void IPOD_API_UART_InitPort(void);

extern int IPOD_UFD_Insert(void);
extern void IPOD_UFD_Remove(void);
extern void IPOD_Gpio2Usb(void);
extern void IPOD_Usb2Gpio(void);
extern void IPOD_Gpio2Uart(void);
extern void IPOD_Uart2Gpio(void);
extern int IPOD_Ioctl(int function, void *param);

#endif /* _IPOD_UART_INTERFACE_ */



