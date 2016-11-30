#include "stdafx.h"
#include "TVOut.h"
#include "DSSINTF.h"
#include "../i2c/chip.h"

typedef struct _DRVDEVMODEW
{
	DEVMODEW        devmodew;       // DDI definition of mode
	DWORD temp1[10];
} DRVDEVMODEW;

#define NTSC_M		0x0000
#define	NTSC_M_J	0x0001
#define	NTSC_N		0x0010
#define	NTSC_N_J	0x0011
#define	NTSC_443	0x0020
#define PAL_M		0x0100
#define	PAL_N		0x0110
#define	PAL_B		0x0120
#define	PAL_G		0x0130
#define	PAL_H		0x0140
#define	PAL_I		0x0150
#define	PSEUDO_NTSC	0x1000
#define	PSEUDO_PAL	0x1010

TccTVOut* TccTVOut::pinstance = NULL;
CDSSINTF m_CDSS;

int CtrlFunc[] = {3, 0};
unsigned int UIChOnOff[]={0, 1};
typedef struct saveparam{
	unsigned int DemoType;
	unsigned int MainDisplay;
	unsigned int UIChannel;
	unsigned int UIBaseAddr;
	unsigned int UIImgFmt;
	unsigned int ConnectPath[4];
	unsigned int CtrlFunc[2];
	unsigned int CtrlLayerorder;
	unsigned int CtrlPxlFmt;
	unsigned int UIChOnOff[2];
}SAVEPARAM,*PSAVEPARAM;
saveparam m_SaveParam;

TccTVOut* TccTVOut::Instance()
{
	if (pinstance == NULL)
	{
		pinstance = new TccTVOut();
		if(1)
		{
			//RETAILMSG(1, (TEXT("----------------xxxx----------------\r\n")));
			{
				TCHAR KeyString[256] = {0};
				HKEY hkey;
				DWORD dwStatus;
				DWORD dwType;
				DWORD dwSize;
				wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS");
				dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("DemoType"), NULL, &dwType,(LPBYTE) &m_SaveParam.DemoType, &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("MainDisplay"), NULL, &dwType,(LPBYTE) &m_SaveParam.MainDisplay, &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("RGBLCD"), NULL, &dwType,(LPBYTE) &m_SaveParam.ConnectPath[0], &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("LVDS"), NULL, &dwType,(LPBYTE) &m_SaveParam.ConnectPath[1], &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("HDMI"), NULL, &dwType,(LPBYTE) &m_SaveParam.ConnectPath[2], &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("TVOUT"), NULL, &dwType,(LPBYTE) &m_SaveParam.ConnectPath[3], &dwSize);
				if(dwStatus == ERROR_SUCCESS)
					dwStatus = RegQueryValueEx(hkey, _T("CurUIChannel"), NULL, &dwType,(LPBYTE) &m_SaveParam.UIChannel, &dwSize);

				RegCloseKey(hkey);

				if(m_SaveParam.DemoType) // dual
				{
					wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",m_SaveParam.MainDisplay);
					dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
					if(dwStatus == ERROR_SUCCESS)
						dwStatus = RegQueryValueEx(hkey, _T("Function"), NULL, &dwType,(LPBYTE) &m_SaveParam.CtrlFunc[m_SaveParam.MainDisplay], &dwSize);
					RegCloseKey(hkey);

					wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",(m_SaveParam.MainDisplay+1)%2);
					dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
					if(dwStatus == ERROR_SUCCESS)
						dwStatus = RegQueryValueEx(hkey, _T("Function"), NULL, &dwType,(LPBYTE) &m_SaveParam.CtrlFunc[(m_SaveParam.MainDisplay+1)%2], &dwSize);
					RegCloseKey(hkey);
				}
				else
				{

					wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",m_SaveParam.MainDisplay);
					dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
					if(dwStatus == ERROR_SUCCESS)
						dwStatus = RegQueryValueEx(hkey, _T("Function"), NULL, &dwType,(LPBYTE) &m_SaveParam.CtrlFunc[m_SaveParam.MainDisplay], &dwSize);
					RegCloseKey(hkey);
				}

				wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",m_SaveParam.MainDisplay);
				dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
				dwStatus = RegQueryValueEx(hkey, _T("LayerOrder"),  NULL, &dwType,(LPBYTE) &m_SaveParam.CtrlLayerorder,   &dwSize);
				dwStatus = RegQueryValueEx(hkey, _T("PXDataWidth"), NULL, &dwType,(LPBYTE) &m_SaveParam.CtrlPxlFmt,  &dwSize);
				RegCloseKey(hkey);

				wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d\\ImgChannel%d",m_SaveParam.MainDisplay,m_SaveParam.UIChannel);
				dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
				dwStatus = RegQueryValueEx(hkey, _T("BaseAddress"),  NULL, &dwType,(LPBYTE) &m_SaveParam.UIBaseAddr,   &dwSize);
				dwStatus = RegQueryValueEx(hkey, _T("ImgFormat"), NULL, &dwType,(LPBYTE) &m_SaveParam.UIImgFmt, &dwSize);
				RegCloseKey(hkey);
			}
			for(int i=0; i<4;i++)
			{
				CtrCfgInfo[i].LayerOrder = m_SaveParam.CtrlLayerorder;
				CtrCfgInfo[i].PXDataWidth = m_SaveParam.CtrlPxlFmt;
				ImgCHCfgInfo[i].BaseAddress = m_SaveParam.UIBaseAddr;
				ImgCHCfgInfo[i].ImgFormat = m_SaveParam.UIImgFmt;
			}

			DRIVERPARAM		Info;
			DWORD	onoff = 0;
			Info.CtrlId = 2;
			Info.ImgCh = 1;
			Info.pParam = &onoff;
			Info.Size = sizeof(DWORD);

			m_CDSS.RequestDriver(IOCTL_DDIC_DDIBUSPOWERDOWN, &Info, NULL);
			m_CDSS.RequestDriver(IOCTL_DDIC_DDIBUSSWRESET, &Info, NULL);

			Info.CtrlId = 0;
			Info.ImgCh = Info.CtrlId? 1:0;
			Info.pParam = &ImgCHCfgInfo[0];
			Info.Size = sizeof(IMGCFGPARAM);
			m_CDSS.RequestDriver(IOCTL_LCDC_CONFIG_IMGCH, &Info, NULL);



			//-----------------------------------------------------------
			m_CDSS.ConfigController(1,0, &CtrCfgInfo[0]);
			m_CDSS.ConfigImageChannel(1,1,1,&ImgCHCfgInfo[0]);

			m_CDSS.ConfigController( 0, 3, &CtrCfgInfo[3]);
			m_CDSS.ConfigImageChannel(0,0,0,&ImgCHCfgInfo[3]);




			for(int idx=0;idx<1;idx++)
			{
				DRIVERPARAM		Info;
				DISPMODEPARAM	Disp;
				Info.CtrlId = idx;
				Info.ImgCh = idx? 1:0;
				Info.pParam = &Disp;
				Info.Size = sizeof(DISPMODEPARAM);

				Disp.pCtrParam = &CtrCfgInfo[CtrlFunc[idx]];
				Disp.pImgParam = &ImgCHCfgInfo[0]; //Test

				if(0) // HDMI
				{
					//Disp.pCtrParam = &CtrCfgInfo[0];
					//Disp.pImgParam = &ImgCHCfgInfo[0]; //Test
					//m_CDSS.RequestDriver(IOCTL_LCDC_CHANGECTRLMODE, &Info, NULL);

					Info.pParam = &UIChOnOff[idx];
					Info.Size = sizeof(unsigned int);
					m_CDSS.RequestDriver(IOCTL_LCDC_IMGCH_DISPLAY, &Info, NULL);
					continue;
				}
				else
				{
					m_CDSS.RequestDriver(IOCTL_LCDC_CHANGECTRLMODE, &Info, NULL);
					Info.pParam = &UIChOnOff[idx];
					Info.Size = sizeof(unsigned int);
					m_CDSS.RequestDriver(IOCTL_LCDC_IMGCH_DISPLAY, &Info, NULL);
				}
				if(CtrlFunc[idx] == 3) // TVOUT
				{

					m_CDSS.TvoutSetting(idx, 0, 12, &ImgCHCfgInfo[CtrlFunc[idx]]);
					m_CDSS.SetTVOState(1);
				}
			}
		}
		
	}
	return pinstance;
}

TccTVOut::TccTVOut()
{
	IsTvOutOpen = 0;
	hTVDevice = INVALID_HANDLE_VALUE;
}


void TccTVOut::TVOutOpen()
{
	chip_fms6502.Output1Select(FMS6502::INPUT_5);
	chip_fms6502.Output2Select(FMS6502::INPUT_5);
	//if (hTVDevice == INVALID_HANDLE_VALUE)
	//{
	//	hTVDevice = CreateFile(L"TVO1:", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//	if ( hTVDevice == INVALID_HANDLE_VALUE )
	//	{
	//		// 无法打开 TVout 驱动
	//		return;
	//	}
	//}
	//if (IsTvOutOpen)
	//{
	//	return;
	//}
	////if (m_CDSS.GetTVOState())
	////{
	////	return;
	////}
	////DRIVERPARAM		Info;
	////DISPMODEPARAM	Disp;
	////m_CDSS.ConfigController(1,0, &CtrCfgInfo[0]);
	////m_CDSS.ConfigImageChannel(1,1,1,&ImgCHCfgInfo[0]);

	////m_CDSS.ConfigController( 0, 3, &CtrCfgInfo[3]);
	////m_CDSS.ConfigImageChannel(0,0,0,&ImgCHCfgInfo[3]);
	////



	////for(int idx=0;idx<2;idx++)
	////{
	////	Info.CtrlId = idx;
	////	Info.ImgCh = idx? 1:0;
	////	Info.pParam = &Disp;
	////	Info.Size = sizeof(DISPMODEPARAM);

	////	Disp.pCtrParam = &CtrCfgInfo[CtrlFunc[idx]];
	////	Disp.pImgParam = &ImgCHCfgInfo[0]; //Test

	////	if(0) // HDMI
	////	{
	////		//Disp.pCtrParam = &CtrCfgInfo[0];
	////		//Disp.pImgParam = &ImgCHCfgInfo[0]; //Test
	////		//m_CDSS.RequestDriver(IOCTL_LCDC_CHANGECTRLMODE, &Info, NULL);

	////		Info.pParam = &idx;
	////		Info.Size = sizeof(unsigned int);
	////		m_CDSS.RequestDriver(IOCTL_LCDC_IMGCH_DISPLAY, &Info, NULL);
	////		continue;
	////	}
	////	else
	////	{
	////		m_CDSS.RequestDriver(IOCTL_LCDC_CHANGECTRLMODE, &Info, NULL);
	////		Info.pParam = &idx;
	////		Info.Size = sizeof(unsigned int);
	////		m_CDSS.RequestDriver(IOCTL_LCDC_IMGCH_DISPLAY, &Info, NULL);
	////	}

	////	if(CtrlFunc[0] == 3) // TVOUT
	////	{
	////		
	////		m_CDSS.TvoutSetting(idx, 0, 1, &ImgCHCfgInfo[CtrlFunc[idx]]);
	////		m_CDSS.SetTVOState(1);
	////	}

	////}
	////return ;

	//DWORD LCDNumber=0;
	//DeviceIoControl(hTVDevice, IOCTL_TVOUT_CONNECT_LCDC,  &LCDNumber, sizeof(DWORD), NULL, 0,NULL, NULL);
	//DWORD Type;
	//Type = NTSC_M;
	//DeviceIoControl(hTVDevice, IOCTL_TVOUT_TYPE,  &Type, sizeof(Type), NULL, 0,NULL, NULL);
	//DeviceIoControl(hTVDevice, IOCTL_TVOUT_OPEN,  &ImgCHCfgInfo[3], sizeof(IMGPARAM), 0, 0, NULL, NULL);

	////DWORD Type;
	////Type = NTSC_M;
	////DeviceIoControl(hTVDevice, IOCTL_TVOUT_TYPE,  &Type, sizeof(Type), NULL, 0,NULL, NULL);
	////DeviceIoControl(hTVDevice, IOCTL_TVOUT_OPEN,  NULL, NULL, 0, 0, NULL, NULL);

	////DWORD maxModeIndex=0;
	////DRVDEVMODEW DevMode;
	////DWORD width, height;
	////DWORD Ret=0;

	////switch(Type)
	////{
	////case	NTSC_M:		
	////case	NTSC_M_J:
	////case	PAL_M:	
	////case	NTSC_443:
	////case	PSEUDO_PAL:
	////default:
	////	width = 720; height = 480;
	////	break;
	////case	NTSC_N:
	////case	NTSC_N_J:
	////case	PAL_N:
	////case	PAL_B:
	////case	PAL_G:
	////case	PAL_H:
	////case	PAL_I:
	////case	PSEUDO_NTSC:
	////	width = 720; height = 576;
	////	break;
	////}

	////while (TRUE == EnumDisplaySettings(NULL, maxModeIndex, &DevMode.devmodew))
	////{
	////	if (DevMode.devmodew.dmPelsWidth == width && DevMode.devmodew.dmPelsHeight == height)
	////	{
	////		RETAILMSG(1, (TEXT("    Mode %d: %dx%dx%d\r\n"), maxModeIndex, DevMode.devmodew.dmPelsWidth,
	////			DevMode.devmodew.dmPelsHeight, DevMode.devmodew.dmBitsPerPel));

	////		Ret = ChangeDisplaySettingsEx(NULL,&DevMode.devmodew,NULL,CDS_RESET,NULL) ;
	////		if(Ret != DISP_CHANGE_SUCCESSFUL)
	////		{
	////			RETAILMSG(1, (TEXT("Display mode resolution test failed.[%x]\n"), Ret));
	////		}else{
	////			RETAILMSG(1, (TEXT("ChangeDisplaySettingsEx dwRet = %d \r\n"), Ret));
	////		}
	////		break;
	////	}
	////	maxModeIndex++;
	////}
	//IsTvOutOpen = 1;
}



void TccTVOut::TVOutClose()
{
	chip_fms6502.Output1Select(FMS6502::INPUT_OFF);
	chip_fms6502.Output2Select(FMS6502::INPUT_OFF);
	//DWORD ModeIndex=0;
	//DRVDEVMODEW DevMode;
	//DWORD Ret=0;

	//if ( hTVDevice != INVALID_HANDLE_VALUE && IsTvOutOpen)
	////if (m_CDSS.GetTVOState())
	//{
	//	//ModeIndex = 0;
	//	//if (TRUE == EnumDisplaySettings(NULL, ModeIndex, &DevMode))
	//	//{
	//	//	//RETAILMSG(1, (TEXT("    Mode %d: %dx%dx%d\r\n"), ModeIndex, DevMode.dmPelsWidth,
	//	//	//	DevMode.dmPelsHeight, DevMode.dmBitsPerPel));

	//	//	/*Ret = ChangeDisplaySettingsEx(NULL,&DevMode,NULL,CDS_RESET,NULL) ;
	//	//	if(Ret != DISP_CHANGE_SUCCESSFUL)
	//	//	{
	//	//		RETAILMSG(1, (TEXT("Display mode resolution test failed.[%x]\n"), Ret));
	//	//	}else{
	//	//		RETAILMSG(1, (TEXT("ChangeDisplaySettingsEx dwRet = %d \r\n"), Ret));
	//	//	}*/
	//	//}
	//	//hTVDevice = CreateFile(L"TVO1:", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//	DeviceIoControl(hTVDevice, IOCTL_TVOUT_CLOSE, &ImgCHCfgInfo[0], sizeof(IMGPARAM), NULL, 0, NULL, NULL);
	//	CloseHandle( hTVDevice );
	//	hTVDevice = INVALID_HANDLE_VALUE;
	//}
	//IsTvOutOpen = 0;
}