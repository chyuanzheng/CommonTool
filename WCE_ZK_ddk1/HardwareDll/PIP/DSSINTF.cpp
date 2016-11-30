#include "StdAfx.h"
#include "DSSINTF.h"
#include "ioctl_code.h"

CDSSINTF::CDSSINTF(void)
{
	m_TvoStatus =0;
}

CDSSINTF::~CDSSINTF(void)
{
}

static TCHAR gszDDSRegistryKey[128] = _T("Drivers\\Builtin\\TCC_DSS");

void CDSSINTF::SetDemoType(unsigned int demotype)
{
    HKEY    hkey;
    DWORD dwStatus,dwType,dwSize;

    dwSize = sizeof(DWORD);
    dwType = REG_DWORD;

    dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, gszDDSRegistryKey, 0, 0, &hkey);
    if(dwStatus == ERROR_SUCCESS)
        dwStatus = RegSetValueEx(hkey, _T("DemoType"), NULL, dwType,(LPBYTE) &demotype, dwSize);
    RegCloseKey(hkey);
}

void CDSSINTF::ConfigController(unsigned int id, unsigned int func, PCTRCFGPARAM pParam)
{
  
    HKEY    hkey;
    DWORD dwStatus,dwType,dwSize;
    TCHAR   KeyString[128];

    wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",id);

    dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
    dwSize = sizeof(DWORD);
    dwType = REG_DWORD;
         
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("Function"), NULL, dwType,(LPBYTE) &pParam->Function, dwSize);
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("DispWidth"), NULL, dwType,(LPBYTE) &pParam->DispWidth, dwSize);
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("DispHeight"), NULL, dwType,(LPBYTE) &pParam->DispHeight, dwSize);
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("LayerOrder"), NULL, dwType,(LPBYTE) &pParam->LayerOrder, dwSize);
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("PXDataWidth"), NULL, dwType,(LPBYTE) &pParam->PXDataWidth, dwSize);
     if(dwStatus == ERROR_SUCCESS)
         dwStatus = RegSetValueEx(hkey, _T("Interlaced"), NULL, dwType,(LPBYTE) &pParam->Interlaced, dwSize);

     RegCloseKey(hkey);
}

void CDSSINTF::ConfigImageChannel(unsigned int id, unsigned int ch, unsigned int mode, PIMGCFGPARAM pParam)
{
    DWORD   Func;
    HKEY    hkey;
    DWORD dwStatus,dwType,dwSize;
    TCHAR   KeyString[128];
    DWORD CurCtrl, CurUI;

    dwSize = sizeof(DWORD);
    dwType = REG_DWORD;

    wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d",id);
    dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
    dwStatus = RegQueryValueEx(hkey, _T("Function"), NULL, &dwType,(LPBYTE) &Func, &dwSize);
    RegCloseKey(hkey);


    wsprintf((LPWSTR)KeyString,L"Drivers\\Builtin\\TCC_DSS\\LCDController%d\\ImgChannel%d",id,ch);
    dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, KeyString, 0, 0, &hkey);
    
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("Function"), NULL, dwType,(LPBYTE) &mode, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("ImgSizeWidth"), NULL, dwType,(LPBYTE) &pParam->ImgSizeWidth, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("ImgSizeHeight"), NULL, dwType,(LPBYTE) &pParam->ImgSizeHeight, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("ImgFormat"), NULL, dwType,(LPBYTE) &pParam->ImgFormat, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("BaseAddress"), NULL, dwType,(LPBYTE) &pParam->BaseAddress, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("Interlaced"), NULL, dwType,(LPBYTE) &pParam->Interlaced, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("ChromaKey"), NULL, dwType,(LPBYTE) &pParam->ChromaKey, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("AlphaValue"), NULL, dwType,(LPBYTE) &pParam->AlphaValue, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("Hue"), NULL, dwType,(LPBYTE) &pParam->Hue, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("Bright"), NULL, dwType,(LPBYTE) &pParam->Bright, dwSize);
    if(dwStatus == ERROR_SUCCESS)
    dwStatus = RegSetValueEx(hkey, _T("Contrast"), NULL, dwType,(LPBYTE) &pParam->Contrast, dwSize);
    RegCloseKey(hkey);

    // Ready parameters here
    if(mode == 1) // in case of GUI
    {
        dwStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, gszDDSRegistryKey, 0, 0, &hkey);

        if(dwStatus == ERROR_SUCCESS)
            dwStatus = RegSetValueEx(hkey, _T("CurUICtrl"), NULL, dwType,(LPBYTE) &id, dwSize);
    
        if(dwStatus == ERROR_SUCCESS)
            dwStatus = RegSetValueEx(hkey, _T("CurUIChannel"), NULL, dwType,(LPBYTE) &ch, dwSize);

        if(dwStatus == ERROR_SUCCESS)
            dwStatus = RegSetValueEx(hkey, _T("CurFunction"), NULL, dwType,(LPBYTE) &Func, dwSize);
        RegCloseKey(hkey);
    }
}

int CDSSINTF::RequestDriver(unsigned int ioctlcode, PDRIVERPARAM pInParam, PDRIVERPARAM pOutParam)
{
    DWORD ret;
    DWORD RetByte;
    HANDLE hLCDC;

    hLCDC = CreateFile(L"DSS1:",
                        GENERIC_READ|GENERIC_WRITE, 
						NULL, 
						NULL, 
						OPEN_ALWAYS, 
						FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH, 
						NULL);

	if( hLCDC == NULL)
	{
		RETAILMSG(TRUE,(TEXT("Cannot Open DSS Driver\n")));
		return NULL;
	}

    ret = DeviceIoControl(hLCDC, ioctlcode, pInParam, sizeof(DRIVERPARAM),pOutParam,sizeof(DRIVERPARAM),&RetByte,NULL);
    if(ret == NULL)
        RETAILMSG(TRUE,(TEXT("Request Driver Fail\n")));

    CloseHandle(hLCDC);
    return ret;
}

void CDSSINTF::SetDisplayMode(int function)
{
    unsigned int maxModeIndex=0;
    unsigned int Ret = 0;
    DEVMODEW    ModeW;

    memset(&ModeW, 0, sizeof(DEVMODEW));
    ModeW.dmSize = sizeof(DEVMODEW);

	if( function == 2) // HDMI case
		function = 0; //RGB size

    EnumDisplaySettings(NULL, function, &ModeW);

    RETAILMSG(1, (TEXT("TESTLCDC ChangeDispMode %d: %dx%dx%d\r\n"), maxModeIndex, ModeW.dmPelsWidth,
    ModeW.dmPelsHeight, ModeW.dmBitsPerPel));
    Ret = ChangeDisplaySettingsEx(NULL,&ModeW,NULL,CDS_RESET,NULL) ;

    if(Ret != DISP_CHANGE_SUCCESSFUL)
        RETAILMSG(1, (TEXT("Display mode resolution test failed.[%x]\n"), Ret));
    else
        RETAILMSG(1, (TEXT("ChangeDisplaySettingsEx dwRet = %d \r\n"), Ret));
}

// TV Out Driver Definitions : Copy from TV Out Drivers Header File
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


const DWORD TV_OUT_TYPE[] = 
{
	NTSC_M,
	NTSC_M_J,
	NTSC_N,
	NTSC_N_J,
	NTSC_443,
	PAL_M,
	PAL_N,
	PAL_B,
	PAL_G,
	PAL_H,	
	PAL_I,	
	PSEUDO_NTSC,
	PSEUDO_PAL
};

void CDSSINTF::TvoutSetting(unsigned int channel, unsigned int tvtype,unsigned int demotype, PIMGCFGPARAM pImgCfgParam )
{
    DWORD Type;
    DEVMODEW DevMode;
    DWORD width, height;
    DWORD Ret=0;
    DWORD maxModeIndex=0;
    HANDLE hTvout;
    DWORD LCDNumber=1;

	width = 720; height = 480;

    hTvout = CreateFile(L"TVO1:", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DeviceIoControl(hTvout, IOCTL_TVOUT_CONNECT_LCDC,  &channel, sizeof(DWORD), NULL, 0,NULL, NULL);

    Type = TV_OUT_TYPE[tvtype];
	DeviceIoControl(hTvout, IOCTL_TVOUT_TYPE,  &Type, sizeof(Type), NULL, 0,NULL, NULL);
	DeviceIoControl(hTvout, IOCTL_TVOUT_OPEN,  pImgCfgParam, sizeof(IMGCFGPARAM), 0, 0, NULL, NULL);

    memset(&DevMode, 0, sizeof(DEVMODEW));
	DevMode.dmSize = sizeof(DEVMODEW);
	if( demotype == 0)
	{
		while (TRUE == EnumDisplaySettings(NULL, maxModeIndex, &DevMode))
		{
			if (DevMode.dmPelsWidth == width && DevMode.dmPelsHeight == height)
			{
				RETAILMSG(1, (TEXT("    Mode %d: %dx%dx%d\r\n"), maxModeIndex, DevMode.dmPelsWidth,
					DevMode.dmPelsHeight, DevMode.dmBitsPerPel));

				Ret = ChangeDisplaySettingsEx(NULL,&DevMode,NULL,CDS_RESET,NULL) ;
				if(Ret != DISP_CHANGE_SUCCESSFUL)
				{
					RETAILMSG(1, (TEXT("Display mode resolution test failed.[%x]\n"), Ret));
				}else{
					RETAILMSG(1, (TEXT("ChangeDisplaySettingsEx dwRet = %d \r\n"), Ret));
				}
				break;
			}
			maxModeIndex++;
		}
	}
	CloseHandle(hTvout);

}

void CDSSINTF::SetTVOState(int enable)
{
	m_TvoStatus = enable;
}

int CDSSINTF::GetTVOState(void)
{
	return m_TvoStatus;
}
