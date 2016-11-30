/**************************************************************************			
***                                                                          
***   Telechips SYS1-1 Team                          
***                                                                          
***   Module : iPod_interface_USB.h                
***                                                              
**************************************************************************/


/*************************************************************************/
/*Command ID define                                                                                               */
/*************************************************************************/

#ifndef _IPOD_USB_INTERFACE_
#define _IPOD_USB_INTERFACE_


#if defined(__cplusplus)
extern "C" {
#endif


extern int IPOD_API_USB_MountDev(void);


#ifdef WINCE
extern IPOD_ERROR IPOD_API_WINCE_USB_InitChannelParam(pIPOD_INIT_CHANNRL_PARAM pParam, void *Hid_Handle,void *I2C_Handle, unsigned long EventThreadID, unsigned long I2C_ChannelNum);

extern IPOD_ERROR IPOD_API_WINCE_USB_InitParam(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType);
extern IPOD_ERROR IPOD_API_WINCE_USB_InitParamRDisplay(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType);
extern IPOD_ERROR IPOD_API_WINCE_USB_InitParamOSApp(void *Handle, pIPOD_INIT_PARAM pParam, const IPOD_LINGO_INFO_DATA *pLingo_InfoData, IAP_CONNECTION_MODE connectionType);

#endif


#if defined(__cplusplus)
};
#endif


#endif /* _IPOD_USB_INTERFACE_ */



