#pragma once

#define WM_VOLDOWN		(WM_USER+300)
#define WM_VOLUP		(WM_USER+400)
#define WM_MCUINT		WM_USER+500
#define WM_IRINT		WM_USER+600
#define WM_EPFDATA		WM_USER+700
#define WM_SETTITLETEXT	(WM_USER+82)

#define WM_BTSTATUS		(WM_USER+84)
#define WM_GETTITLETEXT	(WM_USER+85)
#define WM_RELOADUI		(WM_USER+86)
#define WM_SETCHANGE	(WM_USER+87)
#define WM_WIFIUPDATE	(WM_USER+88)
#define WM_IPOD			WM_USER+89
#define WM_MUTE			(WM_USER+90)

//#define WM_NAIVSOUND	WM_USER+81
#define WM_NAIVSOUND	RegisterWindowMessage(L"NaviSound")
#define WM_NAVISOUND_KLD	RegisterWindowMessage(L"NaviSound_KLD")
#define WM_NAVISOUND_GD	RegisterWindowMessage(L"NaviSound_GD")