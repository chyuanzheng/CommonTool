#include "stdafx.h"
#include "iPodConfig.h"
#include "iPodCommandControl.h"
#include "iPodEventControl.h"
#include "iPodAudio.h"
#include "IPodAppLib.h"
//#include "WMMsg.h" 
#include "GXNotify.h"
#include "MsgHandle.h"
#include "../resource.h"

#define  WM_IPOD 1

IPodAppLib* IPodAppLib::pInstance = NULL;

void IPodAppLib::InitBrws()
{
	m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = IPODUI_BRWS_MAX;
	m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth = 0;
	m_pPlayerContext->m_stBrwsViewInfo.eCategory = IPOD_LIB_ALL;
	m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
	m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;
	//SendMsg(IPOD_LIST_INIT, 0, 0);
	//GXNotify::SendNotify("ipod_msg", IPOD_LIST_INIT, 0);
	//ipod_path[0] = 0;
	//SendMsg(IPOD_MSG_SETPATH, 0, (LPARAM)ipod_path);
	//GXNotify::SendNotify("ipod_msg", IPOD_MSG_SETPATH, (LPARAM)ipod_path);

}

void IPodAppLib::ClearBrws()
{
	//SendMsg(IPOD_LIST_START, 0, 0);
	//GXNotify::SendNotify("ipod_msg", IPOD_LIST_CLEAR, 0);
}

DWORD IPodAppLib::GetLogoImageForIPOD(BYTE *pRGB565Data,int width,int height) {
	HDC hDC=::GetDC(hWnd);
	HDC hMemDC1 = CreateCompatibleDC(hDC);
	HDC hMemDC2 = CreateCompatibleDC(hDC);
	HBITMAP hOldBitmap1;
	HBITMAP bmp;
	HINSTANCE h3 = GetModuleHandle(L"IPODActivity.dll");
	bmp = ::LoadBitmap(h3, MAKEINTRESOURCE(IDB_BITMAP_LOGO1));
	hOldBitmap1 = (HBITMAP)SelectObject(hMemDC1, bmp);

	BITMAPINFO    bmi;

	ZeroMemory(&bmi, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width + 12 - (width%12); // 4byte-aligned
	bmi.bmiHeader.biHeight = -(height + 12 - (height%12)); //prevint flipping
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	BYTE* pBits;

	HBITMAP bitmap = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
	if ((long)bitmap==ERROR_INVALID_PARAMETER) {
		bitmap=0;
	} else {
		HBITMAP hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, bitmap);
		BITMAP bmpinfo;
		//bmp.GetBitmap(&bmpinfo);
		::GetObject(bmp, sizeof(BITMAP), &bmpinfo);
		StretchBlt(hMemDC2,0,0,width,height,hMemDC1,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,SRCCOPY);
		//BitBlt(hMemDC2,0,0,width,height,hMemDC1,0,0,SRCCOPY);

		BYTE* pCur;
		int i,j;
		for (i=0; i<height;i++) {
			pCur = pBits + i*3*bmi.bmiHeader.biWidth;
			for (j=0; j<width; j++) {
				// get bmp pixel
				pRGB565Data[0]=((*pCur>>3) & 0x1F) | ((*(pCur+1)<<3) & 0xE0);
				pRGB565Data[1]=((*(pCur+1)>>5) & 0x07) | ((*(pCur+2)) & 0xF8);
				pCur +=3;
				pRGB565Data+=2;
			}
		}

		SelectObject(hMemDC2, hOldBitmap2);
		DeleteDC(hMemDC2);
		SelectObject(hMemDC1, hOldBitmap1);
		DeleteDC(hMemDC1);

		DeleteObject(bitmap);
	}
	DeleteObject(bmp);
	::ReleaseDC(hWnd,hDC);
	return 0;
}

void IPodAppLib::PostMsg_ToAudioReadThread(DWORD msgID, WPARAM wParam, LPARAM lParam)
{
	TLOG(CH_UI, LV_DEBUG, 
		(TEXT("PostMsg_ToAudioReadThread() > msgID=%d, wParam=%d, lParam=%d\r\n"), msgID, wParam, lParam));

	if ( m_pPlayerContext ){
		HANDLE hThread = m_pPlayerContext->m_hAudioThread;
		DWORD ThreadID = m_pPlayerContext->m_AudioReadThreadID;

		if ( hThread ){
			PostThreadMessage( ThreadID, msgID, wParam, lParam);
		}
	}
	else{
		TLOG(CH_UI, LV_WARN, 
			(TEXT("PostMsg_ToAudioReadThread() >  m_pPlayerContext is null\r\n")));
	}
}

void IPodAppLib::PostMsg_ToCMDControlThread(DWORD msgID, WPARAM wParam, LPARAM lParam)
{
#ifdef TIME_CHECK
	g_nMSGRequestCheckTick[msgID] = GetTickCount();
	//DWORD nCurrentTick = GetTickCount();
	//CString str;
	//str.Format(_T("POST > %s > %d\r\n"), GetMessageName(msgID), nCurrentTick);
	//TLOG(CH_UI, LV_TIME, (str ));
#endif

	if ( m_pPlayerContext ){
		HANDLE hThread = m_pPlayerContext->m_hControlThread;
		DWORD ThreadID = m_pPlayerContext->m_ControlThreadID;

		if ( hThread ){
			PostThreadMessage( ThreadID, msgID, wParam, lParam);
		}
	}
	else{
		TLOG(CH_UI, LV_WARN, 
			(TEXT("PostMsg_ToCMDControlThread() >  m_pPlayerContext is null\r\n")));
	}
}

void IPodAppLib::PostMsg_ToDisconnectionDetectThread(DWORD msgID, WPARAM wParam, LPARAM lParam)
{
	if ( m_pPlayerContext ){
		HANDLE hThread = m_pPlayerContext->m_hDisconnectionDetectThread;
		DWORD ThreadID = m_pPlayerContext->m_DisconnectionDetectThreadID;

		if ( hThread ){
			int ret;
			ret = PostThreadMessage( ThreadID, msgID, wParam, lParam);
			TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("Send disconnect msg to disconnectdetectThread\r\n")));

		}
	}
	else{
		TLOG(CH_UI, LV_WARN, 
			(TEXT("PostMsg_ToDisconnectionDetectThread() >  Disconnection Event\r\n")));
	}
}

void IPodAppLib::PostMsg_ToEventControlThread(DWORD msgID, WPARAM wParam, LPARAM lParam)
{
	TLOG(CH_UI, LV_DEBUG, 
		(TEXT("PostMsg_ToEventControlThread() > msgID=%d, wParam=%d, lParam=%d\r\n"), msgID, wParam, lParam));

	if ( m_pPlayerContext ){
		HANDLE hThread = m_pPlayerContext->m_hEventThread;
		DWORD ThreadID = m_pPlayerContext->m_EventThreadID;

		if ( hThread ){
			PostThreadMessage( ThreadID, msgID, wParam, lParam);
		}
	}
	else{
		TLOG(CH_UI, LV_WARN, 
			(TEXT("PostMsg_ToEventControlThread() >  m_pPlayerContext is null\r\n")));
	}
}


CategoryType IPodAppLib::GetBrowserTopCategory( DWORD zIndex )
{
	CategoryType eCategory = IPOD_LIB_ALL;

	TLOG(CH_UI, LV_DEBUG, 
		(TEXT("GetBrowserTopCategory() > zIndex = %d\r\n"), zIndex ));

	switch( zIndex ){
		case IPODUI_BRWS_GENRE:
			eCategory = IPOD_LIB_GENRE;
			break;

		case IPODUI_BRWS_ARTIST:
			eCategory = IPOD_LIB_ARTIST;
			break;

		case IPODUI_BRWS_ALBUM:
			eCategory = IPOD_LIB_ALBUM;
			break;

		case IPODUI_BRWS_TRACK:
			eCategory = IPOD_LIB_TRACK;
			break;

		case IPODUI_BRWS_PLAYLIST:
			eCategory = IPOD_LIB_PLAYLIST;
			break;

		default :
			TLOG(CH_UI, LV_WARN, 
				(TEXT("GetBrowserTopCategory() > Invalid index= %d\r\n"), zIndex ));
			break;
	}

	return eCategory;
}

IPodAppLib::IPodAppLib()
{
	hasVideo = 1;
	m_ipod_hierarchy = DBSEL_AUDIO;
	current_video_index = 0;
	isConnect = 0;
	m_isToReceiveList = true;

	nCurrentFileNum = 0;
	nTotalFileNum = 0;

	iCurTime = 0;
	iTotalTime = 0;
}

void IPodAppLib::Init(HWND hwnd)
{

	//
	hWnd = hwnd;
	m_pAlbumArtRawData = 0;
	SetMsgHandler(WM_MESSAGE_DETECTHID, OnMessageDetectHID, (DWORD)this);
	SetMsgHandler(WM_MESSAGE_DETECTAUDIO, OnMessageDetectAudio, (DWORD)this);
	
	SetMsgHandler(WM_UI_UPDATE_CURRENTTRACKINFO, OnMessageUpdateCurrentTrackInfo, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_CURRENTTRACKNUM, OnMessageUpdateCurrentTrackNumber, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_TRACKPLAYBACKPOSITION, OnMessageUpdateTrackPlaybackPosition, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_FFSEEKSTOP, OnMessageUpdateFFSeekStop, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_REWSEEKSTOP, OnMessageUpdateREWSeekStop, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_SAMPLINGFREQUENCE, OnMessageUpdateSamplingFrequency, (DWORD)this);
	
	

	SetMsgHandler(WM_CMDCTRL_RES_INIT, OnMessageControlRes_Init, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_SEND_HANDLE, OnMessageSetiPodHandle, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_STOP, OnMessageControlRes_Stop, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_TERMINATE, OnMessageControlRes_Terminate, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_PLAY, OnMessageControlRes_Play, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_PAUSE, OnMessageControlRes_Pause, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_NEXTTRACK, OnMessageControlRes_NextTrack, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_PREVIOUSTRACK, OnMessageControlRes_PrevTrack, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_FF, OnMessageControlRes_FF, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_REW, OnMessageControlRes_REW, (DWORD)this);

	SetMsgHandler(WM_CMDCTRL_RES_GETCURRENTTRACKINDEX, OnMessageControlRes_GetCurrentTrackIndex, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_GETTOTALPLAYTRACKS, OnMessageControlRes_GetTotalPlayTracks, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_GETTITLE, OnMessageControlRes_GetTitle, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_GETARTIST, OnMessageControlRes_Artist, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_GETALBUM, OnMessageControlRes_Album, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_GETALBUMART, OnMessageControlRes_AlbumArt, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_INFORM_SAMPLINGFREQ_CHECKED, OnMessageControlRes_InformSamplingFreqChecked, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_DEVICEDISPLAYINFO, OnMessageControlRes_GetDeviceDisplayInfo, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_RES_DEVICEDISPLAYIMAGE, OnMessageControlRes_SetDeviceDisplayImage, (DWORD)this);

	SetMsgHandler(WM_CMDCTRL_BRWS_RES_INIT, OnMessageControlBrwsRes_Init, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_BRWS_RES_SELECT, OnMessageControlBrwsRes_Select, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_BRWS_RES_MOVEUPPER, OnMessageControlBrwsRes_MoveUpper, (DWORD)this);
	SetMsgHandler(WM_CMDCTRL_BRWS_RES_GETNAME, OnMessageControlBrwsRes_GetName, (DWORD)this);

	SetMsgHandler(WM_CMDCTRL_RES_GETIPODNAME, OnMessageGetiPodName, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_SHUFFLE, OnMessageShuffle, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_REPEAT, OnMessageRepeat, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_PLAYING, OnMessagePlaying, (DWORD)this);
	SetMsgHandler(WM_UI_UPDATE_PAUSE, OnMessagePause, (DWORD)this);

	m_pPlayerContext=new IPOD_PLAYER_CONTEXT;
	if (m_pPlayerContext!=0) {
		memset(m_pPlayerContext,0,sizeof(IPOD_PLAYER_CONTEXT));
		//m_pPlayerContext->m_hControlThread=0;
		//m_pPlayerContext->m_hAudioThread=0;
		DWORD dwVolume;
		waveOutGetVolume(0,&dwVolume);
		#define VOLUME_MAX		30
		m_pPlayerContext->m_dwVolume=VOLUME_MAX*dwVolume/65536;
		m_pPlayerContext->m_playstatus=PS_PAUSED;
		m_pPlayerContext->m_HIDConnected=FALSE;
		m_pPlayerContext->m_AudioConnected=FALSE;

	}
	IPOD_API_Init();

	if (m_pPlayerContext) {
		m_pPlayerContext->hWnd=hWnd;
	}

	m_pPlayerContext->m_HIDDrvierNumber = 0;
	m_pPlayerContext->m_hControlThread = 0;
	m_pPlayerContext->m_ControlThreadID = 0;

	m_pPlayerContext->m_hEventThread = 0;
	m_pPlayerContext->m_EventThreadID = 0;

	m_pPlayerContext->m_AudioDrvierNumber = 0;
	m_pPlayerContext->m_hAudioThread = 0;
	// Playback info
	m_pPlayerContext->m_nTotalNumOfPlayTracks = 0;
	m_pPlayerContext->m_zCurrentTrackIndex = 0xFFFFFFFF;
	m_pPlayerContext->m_bBrwsInitializedFlag = 1;

	// Thread
	DWORD ThreadID = 0;
	HANDLE hThread = 0;
	// Audio thread
	if (1){
		DWORD DeviceNumber = 0;

		// Retrieve registry
		DeviceNumber = iPod_RetrieveAudioDeviceDriverNumber();
		if ( 0 < DeviceNumber ){
			HANDLE fd;
			WCHAR strDeviceDriverName[16] = {0,};

			wsprintf(strDeviceDriverName, (L"AUD%d:"), DeviceNumber);

			fd=CreateFile(strDeviceDriverName,GENERIC_READ | FILE_SHARE_READ,0,NULL,OPEN_EXISTING,0,NULL);
			if (INVALID_HANDLE_VALUE == fd) {
				TLOG(CH_UI, LV_WARN, (TEXT("OnMessageDetectAudio() > INVALID_HANDLE = 0x%x\r\n"), fd));
			}
			else{
				// connected
				CloseHandle(fd);
				if (!(m_pPlayerContext->m_AudioConnected)) {
					// newly connected
					m_pPlayerContext->m_AudioDrvierNumber = DeviceNumber;
					m_pPlayerContext->m_AudioConnected = iPod_StartAudioThread(m_pPlayerContext);
				}
			}
		}
	}

	// Event control thread
	hThread = iPod_StartEventControlThread(m_pPlayerContext->hWnd, &ThreadID);
	if ( hThread ){
		m_pPlayerContext->m_hEventThread = hThread;
		m_pPlayerContext->m_EventThreadID = ThreadID;
	}

	hThread = iPod_DisconnectionDetectThread(m_pPlayerContext->hWnd, &ThreadID);
	if(hThread)
	{
		m_pPlayerContext->m_hDisconnectionDetectThread = hThread;
		m_pPlayerContext->m_DisconnectionDetectThreadID = ThreadID;

	}

	// command control thread
	hThread = iPod_StartCMDControlThread(m_pPlayerContext->hWnd, &ThreadID);
	if ( hThread ){
		DWORD DeviceNumber = 0;
		DWORD UniqueID = 0;

		pIPOD_CMD_CTRL_PARAM piPodCMDCtrlParam;
		DWORD CMDCtrlParamSize;
		unsigned long iPodDevHandle;
		m_pPlayerContext->m_hControlThread = hThread;
		m_pPlayerContext->m_ControlThreadID = ThreadID;

		iPod_RetrieveControlDeviceDriverNumber(&DeviceNumber, &UniqueID);
		if ( 0 < DeviceNumber ){
			DWORD param = 0;

			IAP_CONNECTION_MODE eConnnectionType = ONE_WIRE_CONNECTION;

			// Audio condition check
			if ( m_pPlayerContext->m_AudioConnected  ){
				eConnnectionType = ONE_WIRE_CONNECTION;
			}
			m_pPlayerContext->m_HIDConnected = TRUE;

			m_pPlayerContext->m_uniqueID = UniqueID;
			m_pPlayerContext->m_HIDDrvierNumber = DeviceNumber;

			param = (eConnnectionType<<16) | DeviceNumber;	
			CMDCtrlParamSize = sizeof(IPOD_CMD_CTRL_PARAM);
			piPodCMDCtrlParam = (pIPOD_CMD_CTRL_PARAM)malloc(CMDCtrlParamSize);
			memset(piPodCMDCtrlParam, 0x00, CMDCtrlParamSize);

			m_pPlayerContext->m_uniqueID = UniqueID;
			m_pPlayerContext->m_HIDDrvierNumber = DeviceNumber;

			piPodCMDCtrlParam->m_DeviceNumber = DeviceNumber;
			piPodCMDCtrlParam->m_ConnectionType = eConnnectionType;
			piPodCMDCtrlParam->m_EventThreadID = (DWORD)m_pPlayerContext->m_EventThreadID;
			IPOD_API_Open(&iPodDevHandle);
			piPodCMDCtrlParam->m_iPodDev = (void *)iPodDevHandle;
			IPOD_API_Malloc_ExtInfo((void *)iPodDevHandle);

			PostMsg_ToCMDControlThread(WM_CMDCTRL_INIT, (WPARAM)piPodCMDCtrlParam, CMDCtrlParamSize);	// 初始化控制命令,可以获知iPod是否连接
			
			isConnect = 1;
			SendMsg(IPOD_MSG_AUTHSUCCESS, 0, 0);
			//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_AUTHSUCCESS, 0);

			//SendMsg(WM_IPOD, IPOD_MSG_AUTHSUCCESS, 0);
			//PostMsg_ToCMDControlThread( WM_CMDCTRL_INIT, eConnnectionType, m_pPlayerContext->m_HIDDrvierNumber );
			//PostMsg_ToCMDControlThread( WM_CMDCTRL_INIT, param, (DWORD)m_pPlayerContext->m_EventThreadID )
		}
	}

	m_pPlayerContext->m_stDeviceDisplayInfo.pImage=0;
}


DWORD IPodAppLib::OnMessageDetectHID(UINT msg, WPARAM wParam, LPARAM lParam)
{
	DWORD UniqueID = (DWORD) lParam;
	DWORD DeviceNumber = 0;
	pIPOD_CMD_CTRL_PARAM piPodCMDCtrlParam;
	DWORD CMDCtrlParamSize;
	unsigned long iPodDevHandle;

	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageDetectHID() > wParam = %d\r\n"), wParam));
	static int bFirst = 1;
	switch (wParam) {
		case 0:		// attached
			
			if (bFirst)
			{
				bFirst = 0;
				//waveOutSetVolume(0,0);
			}
			m_pPlayerContext->m_uniqueID = UniqueID;
			if ( !m_pPlayerContext->m_HIDConnected ){
				IAP_CONNECTION_MODE eConnnectionType = TWO_WIRE_CONNECTION;
				m_pPlayerContext->m_HIDConnected = TRUE;
				// Audio condition check
				if ( 1 ){
					if ( m_pPlayerContext->m_AudioConnected  ){
						eConnnectionType = ONE_WIRE_CONNECTION;
					}
					else{
					}
				}

				// Retrieve registry
				DeviceNumber = iPod_GetControlDeviceDriverNumber( UniqueID );
				if ( 0 < DeviceNumber ){
					CMDCtrlParamSize = sizeof(IPOD_CMD_CTRL_PARAM);
					piPodCMDCtrlParam = (pIPOD_CMD_CTRL_PARAM)malloc(CMDCtrlParamSize);
					memset(piPodCMDCtrlParam, 0x00, CMDCtrlParamSize);

					m_pPlayerContext->m_uniqueID = UniqueID;
					m_pPlayerContext->m_HIDDrvierNumber = DeviceNumber;

					piPodCMDCtrlParam->m_DeviceNumber = DeviceNumber;
					piPodCMDCtrlParam->m_ConnectionType = eConnnectionType;
					piPodCMDCtrlParam->m_EventThreadID = (DWORD)m_pPlayerContext->m_EventThreadID;
					IPOD_API_Open(&iPodDevHandle);
					piPodCMDCtrlParam->m_iPodDev = (void *)iPodDevHandle;
					IPOD_API_Malloc_ExtInfo((void *)iPodDevHandle);
					PostMsg_ToCMDControlThread(WM_CMDCTRL_INIT, (WPARAM)piPodCMDCtrlParam, CMDCtrlParamSize);

					//SetPlayerState( PLAYER_CONNECTING );
					// 正在连接
					isConnect = 1;
					SendMsg(IPOD_MSG_AUTHSUCCESS, 0, 0);
					//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_AUTHSUCCESS, 0);
				}
			}
			break;

		case 1:		// detached
			TLOG(CH_DISCNTCTL, LV_DEBUG, (TEXT("Get a Disconnect msg\r\n")));
			//if ( m_pPlayerContext->m_HIDConnected ){
			if(m_pPlayerContext->m_uniqueID == UniqueID)
			{
				if (1) 
				{		// 1-wire
					iPod_AudioStop();
				}

				// Retrieve registry
				//DeviceNumber = iPod_GetControlDeviceDriverNumber( UniqueID );
				///if ( 1 || DeviceNumber ==  m_pPlayerContext->m_HIDDrvierNumber ) {
				m_pPlayerContext->m_HIDDrvierNumber = 0;

				//IPOD_SetDisconnectionStatus(piPodLibApiHandle);

				PostMsg_ToDisconnectionDetectThread(WM_DISCNTDETECT_EVENT, m_pPlayerContext->m_iPodHandle, 0);

				PostMsg_ToCMDControlThread( WM_CMDCTRL_STOP, 0, 0 );

				//SetPlayerState( PLAYER_DISCONNECTING ); // Disconnecting ?
				// 发送已经断开的状态
				isConnect = 0;
				SendMsg(IPOD_MSG_NAME, 0, 0);
				//GXNotify::SendNotify("ipod_msg", IPOD_MSG_NAME, 0);
				hasVideo = 1;
#ifdef TEST_TERMINATE_THREAD
				if ( FALSE == m_pPlayerContext->m_bControlThreadClosing ) {
					HANDLE hThread = NULL;

					hThread=CreateThread(NULL,0,iPodTerminateCMDThread, this,0, NULL );
					if ( NULL!=hThread ){
						m_pPlayerContext->m_hTerminateControlThread = hThread;
						m_pPlayerContext->m_bControlThreadClosing = TRUE;
					}
				}
#endif
				//}
			}

			//}
			break;
	}
	return 0;
}

DWORD IPodAppLib::OnMessageDetectAudio(UINT msg, WPARAM wParam, LPARAM lParam)
{
	DWORD UniqueID = (DWORD) lParam;
	DWORD DeviceNumber = 0;
	HANDLE fd;

	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageDetectAudio() > wParam = %d\r\n"), wParam));

	switch (wParam) {
		case 0:		// attached
			if ( !m_pPlayerContext->m_hAudioThread ){
				if (1) {		// 1-wire

					// Retrieve registry
					DeviceNumber = iPod_GetAudioDeviceDriverNumber( UniqueID );
					if ( 0 < DeviceNumber ){
						DWORD param = 0;
						WCHAR strDeviceDriverName[16] = {0,};

						wsprintf(strDeviceDriverName, (L"AUD%d:"), DeviceNumber);

						fd=CreateFile(strDeviceDriverName,GENERIC_READ | FILE_SHARE_READ,0,NULL,OPEN_EXISTING,0,NULL);
						if (INVALID_HANDLE_VALUE == fd) {
							TLOG(CH_UI, LV_WARN, (TEXT("OnMessageDetectAudio() > INVALID_HANDLE = 0x%x\r\n"), fd));
						}
						else{
							// connected
							CloseHandle(fd);
							if (!(m_pPlayerContext->m_AudioConnected)) {
								// newly connected
								m_pPlayerContext->m_AudioDrvierNumber = DeviceNumber;
								m_pPlayerContext->m_AudioConnected = iPod_StartAudioThread(m_pPlayerContext);
							}
						}
					}
				}
			}
			break;
		case 1:		// detached
			//if (m_pPlayerContext->m_AudioConnected) {
			// disconnected
			m_pPlayerContext->m_AudioConnected=FALSE;

			iPod_StopAudioThread();
			Sleep(100);
			iPod_CloseAudioThread();

			m_pPlayerContext->m_hAudioThread = NULL;

			m_pPlayerContext->m_AudioDrvierNumber = 0;
			//}
			break;
	}

	TLOG(CH_UI, LV_LOG, (TEXT("HID %s, Audio %s\r\n"),
		m_pPlayerContext->m_HIDConnected?TEXT("Connected"):TEXT("Not Connected"),
		m_pPlayerContext->m_AudioConnected?TEXT("Connected"):TEXT("Not Connected")));

	return 0;
}

DWORD IPodAppLib::OnMessageUpdateCurrentTrackInfo(UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

DWORD IPodAppLib::OnMessageUpdateCurrentTrackNumber(UINT msg, WPARAM wParam, LPARAM lParam)
{
 nTotalFileNum = m_pPlayerContext->m_nTotalNumOfPlayTracks;
	nCurrentFileNum = (DWORD)(wParam); 
	GxxString strCurrentFileNum;
	
	TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageUpdateCurrentTrackNumber() > (%d)\r\n"), wParam) );

	if(nCurrentFileNum == -1)
	{
		/*
			[2012.10.15]
			Sometimes, iPod(iPhone3GS iOS6.0) doesn't response for playback command.Play status is always pause.
		*/
		PostMsg_ToCMDControlThread(WM_CMDCTRL_PLAY,0,0);
	}
	if ( m_pPlayerContext->m_zCurrentTrackIndex !=  nCurrentFileNum && nCurrentFileNum != -1){
		m_pPlayerContext->m_zCurrentTrackIndex =  nCurrentFileNum;
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTITLE, m_pPlayerContext->m_zCurrentTrackIndex, 0 );
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETARTIST, m_pPlayerContext->m_zCurrentTrackIndex, 0 );
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETALBUM, m_pPlayerContext->m_zCurrentTrackIndex, 0 );
		if (m_pAlbumArtRawData==0) {
			m_pAlbumArtRawData=new BYTE[2*600*600];
		}
		// 取消获取封面,会导致程序崩溃; bug已修正 m_pAlbumArtRawData 没有置初值
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETALBUMART, m_pPlayerContext->m_zCurrentTrackIndex,(LPARAM)m_pAlbumArtRawData );

		//strCurrentFileNum.Format( L"%5d/%5d", (nCurrentFileNum+1), nTotalFileNum);
		//GetDlgItem(IDC_STATIC_CURRENTFILENUM)->SetWindowText(strCurrentFileNum);
		// 发送当前数/总数
	}

	GXNotify::SendNotifyAsync(AfxGetHWND(),"ipod_msg_current_and_total_filenum", (nCurrentFileNum+1), nTotalFileNum);
	return 0;
}

DWORD IPodAppLib::OnMessageUpdateTrackPlaybackPosition(UINT msg, WPARAM wParam, LPARAM lParam)
{
	DWORD nPlaybackSec = (DWORD)((wParam/1000)); 
	DWORD nSec = (nPlaybackSec%60);
	DWORD nMin = (nPlaybackSec%3600)/60; 
	DWORD nHour = (nPlaybackSec/3600); 
	//WCHAR strPlaybackPosition[32];

	//TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageUpdateTrackPlaybackPosition() > (%d)\r\n"), wParam) );

	//if ( nPlaybackPosition != m_pPlayerContext->){
	//wsprintf( strPlaybackPosition, L"%2d:%2d:%2d", nHour, nMin, nSec );
	//GetDlgItem(IDC_STATIC_PLAYTIME)->SetWindowText(strPlaybackPosition);
	// 发送当前播放时间
	//}

	iCurTime = nPlaybackSec;
	SendMsg(IPOD_MSG_TIME, 0, 0);
	//RETAILMSG(COUT_MSG, (TEXT("ipod time = %d:%d \r\n"), nMin, nSec ));
	
	//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_TIME, 0);
	
	return 0;
}

//DWORD IPodAppLib::OnMessageUpdateFFSeekStop(UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}
//
//DWORD IPodAppLib::OnMessageUpdateREWSeekStop(UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}

DWORD IPodAppLib::OnMessageUpdateFFSeekStop(UINT msg, WPARAM wParam, LPARAM lParam) {

	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageUpdateFFSeekStop() \r\n")) );

	if (PS_FFREW==m_pPlayerContext->m_playstatus){
		m_pPlayerContext->m_playstatus = PS_PLAY;
		//GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"||");
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_PLAY, 0);

		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageUpdateREWSeekStop(UINT msg, WPARAM wParam, LPARAM lParam) {

	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageUpdateFFSeekStop() \r\n")) );

	if (PS_FFREW==m_pPlayerContext->m_playstatus){
		m_pPlayerContext->m_playstatus = PS_PLAY;
		//GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"||");
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_PLAY, 0);

		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageUpdateSamplingFrequency(UINT msg, WPARAM wParam, LPARAM lParam)
{
	DWORD nSamplingFreq = (DWORD)wParam;
	unsigned short Info= (unsigned short)lParam;

	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageUpdateSamplingFrequency() > SamplingFreq(%d)\r\n"), nSamplingFreq ) );

	iPod_SetAudioSamplingFreq( nSamplingFreq );

	PostMsg_ToCMDControlThread( WM_CMDCTRL_INFORM_SAMPLINGFREQ_CHECKED, Info, 0 );

	return 0;
}


DWORD IPodAppLib::OnMessageControlRes_Init(UINT msg, WPARAM wParam, LPARAM lParam)
{

	int nResult = wParam;
	DWORD nCurrentIndex = (DWORD)lParam;
	if ( 0 < nResult /*success*/){

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_Init() > IsSuccess(%d)\r\n"), wParam) );

		isConnect = 1;
		m_pPlayerContext->m_HIDConnected = TRUE;

		// Init browser
		m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = IPODUI_BRWS_MAX;
		m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth = 0;
		m_pPlayerContext->m_stBrwsViewInfo.eCategory = IPOD_LIB_ALL;
		m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
		m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;

		// 恢复列表到默认
		SendMsg(IPOD_LIST_INIT, 0, 0);
		//GXNotify::SendNotify("ipod_msg", IPOD_LIST_INIT, 0);
		// Get display info of device to set Bitmap
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GET_DEVICEDISPLAYINFO, (DWORD)&(m_pPlayerContext->m_stDeviceDisplayInfo), 0 );
		//
		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETCURRENTTRACKINDEX, 0, 0 );

		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );
		
		// 获取iPod名字
		PostMsg_ToCMDControlThread( WM_CMDCTRL_RES_GETIPODNAME, 0, 0 );

		//PostMessage(WM_UI_UPDATE_CURRENTTRACKINFO,0,0);
		

	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Init() > Failed(%d)\r\n"), wParam) );

		m_pPlayerContext->m_HIDConnected = FALSE;
		isConnect = 0;
		//SetPlayerState( PLAYER_DISCONNECTED );
		//发送断开消息
	}

	return 0;
}

DWORD IPodAppLib::OnMessageSetiPodHandle(UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_pPlayerContext->m_iPodHandle = wParam;
	TLOG(CH_UI, LV_LOG, (TEXT("OnMessageSetiPodHandle() > iPod Handle(0x%x)\r\n"), wParam) );
	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Stop(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;


	DWORD DeviceNumber = 0;
	pIPOD_CMD_CTRL_PARAM piPodCMDCtrlParam;
	DWORD CMDCtrlParamSize;
	unsigned long iPodDevHandle;

#ifdef TEST_TERMINATE_THREAD
	if ( m_pPlayerContext->m_bControlThreadClosing ) {
		TerminateThread(m_pPlayerContext->m_hTerminateControlThread,0);
		m_pPlayerContext->m_hTerminateControlThread = NULL;
		m_pPlayerContext->m_bControlThreadClosing = FALSE;
	}
#endif

	if ( 0 < nResult /*success*/){

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_Stop() > IsSuccess(%d)\r\n"), wParam) );

		m_pPlayerContext->m_HIDConnected = FALSE;

		// Init browser
		InitBrws();
		
		//SetPlayerState( PLAYER_DISCONNECTED );
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Stop() > Failed(%d)\r\n"), wParam) );

		m_pPlayerContext->m_HIDConnected = FALSE;
		//SetPlayerState( PLAYER_DISCONNECTED );
	}
	if(iPod_GetControlDeviceDriverNumber(m_pPlayerContext->m_uniqueID) > 0)
	{
		IAP_CONNECTION_MODE eConnnectionType = TWO_WIRE_CONNECTION;
		m_pPlayerContext->m_HIDConnected = TRUE;
		// Audio condition check
		if ( 1 ){
			if ( m_pPlayerContext->m_AudioConnected  ){
				eConnnectionType = ONE_WIRE_CONNECTION;
			}
			else{
			}
		}

		// Retrieve registry
		DeviceNumber = iPod_GetControlDeviceDriverNumber(m_pPlayerContext->m_uniqueID);
		if ( 0 < DeviceNumber ){
			CMDCtrlParamSize = sizeof(IPOD_CMD_CTRL_PARAM);
			piPodCMDCtrlParam = (pIPOD_CMD_CTRL_PARAM)malloc(CMDCtrlParamSize);
			memset(piPodCMDCtrlParam, 0x00, CMDCtrlParamSize);


			m_pPlayerContext->m_HIDDrvierNumber = DeviceNumber;

			piPodCMDCtrlParam->m_DeviceNumber = DeviceNumber;
			piPodCMDCtrlParam->m_ConnectionType = eConnnectionType;
			piPodCMDCtrlParam->m_EventThreadID = (DWORD)m_pPlayerContext->m_EventThreadID;
			IPOD_API_Open(&iPodDevHandle);
			piPodCMDCtrlParam->m_iPodDev = (void *)iPodDevHandle;
			IPOD_API_Malloc_ExtInfo((void *)iPodDevHandle);
			PostMsg_ToCMDControlThread(WM_CMDCTRL_INIT, (WPARAM)piPodCMDCtrlParam, CMDCtrlParamSize);

			//SetPlayerState( PLAYER_CONNECTING );
			// 发送连接中
		}
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Terminate(UINT msg, WPARAM wParam, LPARAM lParam) {
	int nResult = wParam;

	m_pPlayerContext->m_HIDConnected = FALSE;
	if ( 0 < nResult /*success*/){

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_Terminate() > IsSuccess(%d)\r\n"), wParam) );

		//SetPlayerState( PLAYER_DISCONNECTED );

		m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = 0;
		m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth = 0;
		m_pPlayerContext->m_stBrwsViewInfo.eCategory = IPOD_LIB_ALL;
		m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
		m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;

		//m_BrwsList.DeleteString(zIndex);

	}
	else/* fail */{ 

		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Terminate() > Failed(%d)\r\n"), wParam) );

		//SetPlayerState( PLAYER_NONE );
	}


	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Play(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Play() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Play() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_PLAY], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_Play() > IsSuccess(%d)\r\n"), wParam) );

		m_pPlayerContext->m_playstatus=PS_PLAY;
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_PLAY, 0);
		//SendMsg(WM_IPOD, IPOD_MSG_PLAYSTATUS, IPOD_PLAYING);
		//GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"||");
	}
	else/* fail */{ 
		m_pPlayerContext->m_playstatus=PS_PAUSED;
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_PAUSED, 0);
		//SendMsg(WM_IPOD, IPOD_MSG_PLAYSTATUS, IPOD_PAUSED);
		//GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"|>");

		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Play() > Failed = %d\r\n"), wParam));
	}

	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Pause(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Pause() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Pause() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_PAUSE], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_Pause() > IsSuccess(%d)\r\n"), wParam) );

		m_pPlayerContext->m_playstatus=PS_PAUSED;
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_PAUSED, 0);
		///GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"|>");
		//SendMsg(WM_IPOD, IPOD_MSG_PLAYSTATUS, IPOD_PAUSED);
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Pause() > Failed = %d\r\n"), wParam));
	}


	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
		
	}


	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_NextTrack(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_NextTrack() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_NextTrack() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_NEXTTRACK], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_NextTrack() > IsSuccess(%d)\r\n"), wParam) );

		if (PS_PAUSED == m_pPlayerContext->m_playstatus) {
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETCURRENTTRACKINDEX, 0, 0 );
			
		}
		//获取当前播放的曲目和全部的曲目
		//PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_NextTrack() > Failed = %d\r\n"), wParam));
	}

	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_PrevTrack(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_PrevTrack() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_PrevTrack() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_PREVIOUSTRACK], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_PrevTrack() > IsSuccess(%d)\r\n"), wParam) );

		if (PS_PAUSED == m_pPlayerContext->m_playstatus) {
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETCURRENTTRACKINDEX, 0, 0 );	
			
		}
		//获取当前播放的曲目和全部的曲目
		//PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );

	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_PrevTrack() > Failed = %d\r\n"), wParam));
	}

	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_FF(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_FF() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_FF() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_FF], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		///GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"|>");
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_FFREW, 0);
		m_pPlayerContext->m_playstatus=PS_FFREW;

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_FF() > IsSuccess(%d)\r\n"), wParam) );
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_FF() > Failed = %d\r\n"), wParam));
	}

	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_REW(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_REW() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_REW() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_REW], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 < nResult /*success*/){
		///GetDlgItem(IDC_PLAYCONTROL_PLAYPAUSE)->SetWindowText(L"|>");
		SendMsg(IPOD_PLAY_STATUS_FRESH, PS_FFREW, 0);
		m_pPlayerContext->m_playstatus=PS_FFREW;

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_REW() > IsSuccess(%d)\r\n"), wParam) );
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_FF() > Failed = %d\r\n"), wParam));
	}

	if ( m_pPlayerContext->m_HIDConnected ){
		SetPlayControlButtonEnable(TRUE);
	}

	return 0;
}

void IPodAppLib::SetShuffle(int mode)
{
	ShuffleMode shuffle;
	IPOD_ERROR Err;
	//set Shuffle mode
	Err = IPOD_GetShuffle((void*)m_pPlayerContext->m_iPodHandle, &shuffle);
	if(IPOD_NO_ERROR == Err)
	{
		Err = IPOD_SetShuffle((void*)m_pPlayerContext->m_iPodHandle, (ShuffleMode)mode, RESTORE_ORG_SETTING);
		//pPlayInfo->ShuffleStatus = (unsigned char)shuffle;
	}
}

void IPodAppLib::SetRepeat(int mode)
{
	//set repeat mode
	CurrentRepeatState repeat;
	IPOD_ERROR Err;

	Err = IPOD_GetRepeat((void*)m_pPlayerContext->m_iPodHandle, &repeat);
	if(IPOD_NO_ERROR == Err)
	{
		Err = IPOD_SetRepeat((void*)m_pPlayerContext->m_iPodHandle,(CurrentRepeatState)mode, RESTORE_ORG_SETTING);
		//pPlayInfo->RepeatStatus = (unsigned char)repeat;
	}
}

void IPodAppLib::SetPlayFrew()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
	switch (m_pPlayerContext->m_playstatus) {
		case PS_PLAY:
			PostMsg_ToCMDControlThread( WM_CMDCTRL_REW, 0, 0 );
			SetPlayControlButtonEnable(FALSE);
			break;
	}
}

void IPodAppLib::SetPlayFf()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
	switch (m_pPlayerContext->m_playstatus) {
		case PS_PLAY:
			PostMsg_ToCMDControlThread( WM_CMDCTRL_FF, 0, 0 );
			SetPlayControlButtonEnable(FALSE);
			break;
	}
}

void IPodAppLib::SetPlayTime(int time)
{
	IPOD_DR_SETSTATEINFO_PARAM StateParam;
	StateParam.m_InfoType = IPOD_DR_STATUS_TRACK_POS_MS;
	StateParam.m_data.m_TrackPos_ms = time*1000;
	StateParam.m_RestoreOpt = RESTORE_ORG_SETTING;
	IPOD_DR_SetiPodStateInfo((void*)m_pPlayerContext->m_iPodHandle, &StateParam);
}

void IPodAppLib::SetPlayTime2(int time)
{
	IPOD_DR_SETSTATEINFO_PARAM StateParam;
	StateParam.m_InfoType = IPOD_DR_STATUS_TRACK_POS_S;
	StateParam.m_data.m_TrackPos_s = time;
	StateParam.m_RestoreOpt = RESTORE_ORG_SETTING;
	IPOD_DR_SetiPodStateInfo((void*)m_pPlayerContext->m_iPodHandle, &StateParam);
}



DWORD IPodAppLib::OnMessageShuffle(UINT msg, WPARAM wParam, LPARAM lParam)
{
	RETAILMSG(1, (TEXT("OnMessageShuffle wParam=%d, lParam=%d\r\n"), wParam, lParam));
	SendMsg(IPOD_MSG_SHUFFLE, 0, wParam);
	//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_SHUFFLE, wParam);
	return 0;
}

DWORD IPodAppLib::OnMessageRepeat(UINT msg, WPARAM wParam, LPARAM lParam)
{
	RETAILMSG(1, (TEXT("OnMessageRepeat wParam=%d, lParam=%d\r\n"), wParam, lParam));
	SendMsg(IPOD_MSG_REPEAT, 0, wParam);
	//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_REPEAT, wParam);
	return 0;
}

DWORD IPodAppLib::OnMessagePlaying(UINT msg, WPARAM wParam, LPARAM lParam)
{
	RETAILMSG(COUT_MSG, (TEXT("OnMessagePlaying wParam=%d, lParam=%d\r\n"), wParam, lParam));
	pIPOD_PLAY_INFO pInfo;
	void *ExtInfo = IPOD_GetExtInfo((void*)m_pPlayerContext->m_iPodHandle);

	if(NULL != ExtInfo)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;
		pInfo->Rd_playStatus = IPOD_DR_PLAYING;
	}
	SendMsg(IPOD_MSG_PLAYSTATUS, 0, 1);
	//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_PLAYSTATUS, 1);
	return 0;
}

DWORD IPodAppLib::OnMessagePause(UINT msg, WPARAM wParam, LPARAM lParam)
{
	RETAILMSG(COUT_MSG, (TEXT("OnMessagePause wParam=%d, lParam=%d\r\n"), wParam, lParam));
	pIPOD_PLAY_INFO pInfo;
	void *ExtInfo = IPOD_GetExtInfo((void*)m_pPlayerContext->m_iPodHandle);

	if(NULL != ExtInfo)
	{
		pInfo = (pIPOD_PLAY_INFO)ExtInfo;
		pInfo->Rd_playStatus = IPOD_DR_PLAYBACK_PAUSED;
	}
	SendMsg(IPOD_MSG_PLAYSTATUS, 0, 2);
	//GXNotify::SendNotifyAsync(hWnd, "ipod_msg", IPOD_MSG_PLAYSTATUS, 2);
	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_GetCurrentTrackIndex(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetCurrentTrackIndex() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetCurrentTrackIndex() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETCURRENTTRACKINDEX], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 <= nResult /*success*/){

		nTotalFileNum = m_pPlayerContext->m_nTotalNumOfPlayTracks;
		nCurrentFileNum = (DWORD)(wParam); 
		GxxString strCurrentFileNum;

		if (m_ipod_hierarchy == DBSEL_VIDEO)
		{
			current_video_index = nCurrentFileNum;
		}
		else
		{
			current_music_index = nCurrentFileNum;
		}

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_GetCurrentTrackIndex() > IsSuccess(%d)\r\n"), wParam) );

		//if ( m_pPlayerContext->m_zCurrentTrackIndex !=  nCurrentFileNum && nCurrentFileNum != -1){
		if(1){
			m_pPlayerContext->m_zCurrentTrackIndex =  nCurrentFileNum;
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTITLE, m_pPlayerContext->m_zCurrentTrackIndex, 0 );
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETARTIST, m_pPlayerContext->m_zCurrentTrackIndex, 0 );
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETALBUM, m_pPlayerContext->m_zCurrentTrackIndex, 0 );

			 if (m_pAlbumArtRawData==0) {
				m_pAlbumArtRawData=new BYTE[2*600*600];
			}
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETALBUMART, m_pPlayerContext->m_zCurrentTrackIndex,(LPARAM)m_pAlbumArtRawData );

			//strCurrentFileNum.Format( L"%5d/%5d", (nCurrentFileNum+1), nTotalFileNum);
			///GetDlgItem(IDC_STATIC_CURRENTFILENUM)->SetWindowText(strCurrentFileNum);
		}
		GXNotify::SendNotifyAsync(AfxGetHWND(),"ipod_msg_current_and_total_filenum", (nCurrentFileNum+1), nTotalFileNum);
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetCurrentTrackIndex() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_GetTotalPlayTracks(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetTotalPlayTracks() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetTotalPlayTracks() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETTOTALPLAYTRACKS], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 <= nResult /*success*/){

		nTotalFileNum = (DWORD)(wParam); 
		nCurrentFileNum = m_pPlayerContext->m_zCurrentTrackIndex; 



		GxxString strCurrentFileNum;

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlRes_GetTotalPlayTracks() > IsSuccess(%d)\r\n"), wParam) );

		if ( m_pPlayerContext->m_nTotalNumOfPlayTracks !=  nTotalFileNum ){
			m_pPlayerContext->m_nTotalNumOfPlayTracks = nTotalFileNum;

			//strCurrentFileNum.Format( L"%5d/%5d", (nCurrentFileNum+1), nTotalFileNum);
			//发送当前曲目和总曲目
			GXNotify::SendNotifyAsync(AfxGetHWND(),"ipod_msg_current_and_total_filenum", (nCurrentFileNum+1), nTotalFileNum);
			// 当前/总数
			///GetDlgItem(IDC_STATIC_CURRENTFILENUM)->SetWindowText(strCurrentFileNum);
			
		}
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetTotalPlayTracks() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_GetTitle(UINT msg, WPARAM wParam, LPARAM lParam) {

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetTitle() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_GetTitle() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETTITLE], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 != wParam /*success*/){
		LPCTSTR lpString = (LPCTSTR) wParam;
		if ( IS_NULL(lpString) ){
			TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetTitle() > NULL parameter\r\n"), wParam));
		}
		else{
			///GetDlgItem(IDC_DISPLAY_TITLE)->SetWindowText( lpString );
			SendMsg(IPOD_MSG_TITLE, 0, (LPARAM)lpString);
			//GXNotify::SendNotify("ipod_msg", IPOD_MSG_TITLE, (LPARAM)lpString);
		}
		int lTotalTrackLength, lTime;
		int lStatus;
		IPOD_ERROR Err  = IPOD_GetStatus((void*)m_pPlayerContext->m_iPodHandle, &lTotalTrackLength, &lTime, &lStatus);
		iTotalTime = lTotalTrackLength/1000;
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetTitle() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Artist(UINT msg, WPARAM wParam, LPARAM lParam) {

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Artist() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Artist() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETARTIST], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 != wParam /*success*/){
		LPCTSTR lpString = (LPCTSTR) wParam;
		if ( IS_NULL(lpString) ){
			TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Artist() > NULL parameter\r\n"), wParam));
		}
		else{
			///GetDlgItem(IDC_DISPLAY_ARTIST)->SetWindowText( lpString );
			SendMsg(IPOD_MSG_ARTIST, 0, (LPARAM)lpString);
			//GXNotify::SendNotify("ipod_msg", IPOD_MSG_ARTIST, (LPARAM)lpString);
		}
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Artist() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_Album(UINT msg, WPARAM wParam, LPARAM lParam) {

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Album() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_Album() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETALBUM], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 != wParam /*success*/){
		LPCTSTR lpString = (LPCTSTR) wParam;
		if ( IS_NULL(lpString) ){
			TLOG(CH_UI, LV_WARN, (TEXT(" OnMessageControlRes_Album() > NULL parameter\r\n"), wParam));
		}
		else{
			///GetDlgItem(IDC_DISPLAY_ALBUM)->SetWindowText( lpString );
			SendMsg(IPOD_MSG_ALBUM, 0, (LPARAM)lpString);
			//GXNotify::SendNotify("ipod_msg", IPOD_MSG_ALBUM, (LPARAM)lpString);
		}
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_Album() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_AlbumArt(UINT msg, WPARAM wParam, LPARAM lParam) {

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_AlbumArt() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlRes_AlbumArt() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_GETALBUMART], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if (IS_NULL(m_pAlbumArtRawData)) {
		TLOG(CH_UI, LV_WARN, (TEXT(" OnMessageControlRes_AlbumArt() > Raw data fail\r\n")));
	} 
	else 
	{
		m_AlbumArtBitmap_Width=wParam;
		m_AlbumArtBitmap_Height=lParam;

		if ((wParam==0) || (lParam==0)) {
			// No Album art
			GXNotify::SendNotifyAsync(hWnd, "ipod_albumart", 0, 0);
			TLOG(CH_UI, LV_LOG, (TEXT(" OnMessageControlRes_AlbumArt() > No album art\r\n")));
		} else {
			//CPaintDC dc(this);

			//HBITMAP hTest=MakeBitmapFromRawData(dc.m_hDC,m_pAlbumArtRawData,wParam,lParam);
			GXNotify::SendNotifyAsync(hWnd, "ipod_albumart", (DWORD)m_pAlbumArtRawData, (wParam<<16)|lParam);
			/*hTest=((CStatic*)GetDlgItem(IDC_STATIC_ALBUMART))->SetBitmap(hTest);
			if ( hTest ){
				DeleteObject(hTest);
				hTest=0;
			}*/

			TLOG(CH_UI, LV_LOG, (TEXT(" OnMessageControlRes_AlbumArt() > album art ready\r\n")));
		}
	}
	//Invalidate();
	//UpdateWindow();

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_InformSamplingFreqChecked(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;
	if ( 0 <= nResult /*success*/){
		TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageControlRes_InformSamplingFreqChecked() > Success\r\n")));
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_InformSamplingFreqChecked() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_GetDeviceDisplayInfo(UINT msg, WPARAM wParam, LPARAM lParam) {

	// 显示我们的logo在iPod上
	int nResult = wParam;
	if ( 0 <= nResult /*success*/){

		DEVICEDISPLAY_INFO *pstDeviceDisplayInfo = (DEVICEDISPLAY_INFO*)lParam;

		if ( pstDeviceDisplayInfo && (pstDeviceDisplayInfo ==  &(m_pPlayerContext->m_stDeviceDisplayInfo)) )
		{
			TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageControlRes_GetDeviceDisplayInfo() > Success\r\n")));


			if (pstDeviceDisplayInfo->pImage) {
				delete [] pstDeviceDisplayInfo->pImage;
				pstDeviceDisplayInfo->pImage=0;
			}			

			if ((pstDeviceDisplayInfo->width>192) && (pstDeviceDisplayInfo->height>100)) {
				pstDeviceDisplayInfo->width=192;
				pstDeviceDisplayInfo->height=100;
			}
			pstDeviceDisplayInfo->pImage = new BYTE[2*pstDeviceDisplayInfo->width*pstDeviceDisplayInfo->height];	// rgb565
			if (pstDeviceDisplayInfo->pImage) {
				GetLogoImageForIPOD(pstDeviceDisplayInfo->pImage, pstDeviceDisplayInfo->width, pstDeviceDisplayInfo->height);
			}

			PostMsg_ToCMDControlThread( WM_CMDCTRL_SET_DEVICEDISPLAYIMAGE, (DWORD)pstDeviceDisplayInfo, 0 );

		}
		else
		{
			TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetDeviceDisplayInfo() > lParam=0x%x\r\n"), lParam));
		}
	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_GetDeviceDisplayInfo() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlRes_SetDeviceDisplayImage(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;
	if ( 0 <= nResult /*success*/){
		TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageControlRes_SetDeviceDisplayImage() > Success\r\n")));

		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETCURRENTTRACKINDEX, 0, 0 );

		PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );


	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlRes_SetDeviceDisplayImage() > Failed = %d\r\n"), wParam));
	}

	return 0;
}



DWORD IPodAppLib::OnMessageControlBrwsRes_Init(UINT msg, WPARAM wParam, LPARAM lParam) {

	int nResult = wParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_Init() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_Init() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_BRWS_INIT], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 <= nResult /*success*/){
		DWORD nTotalNum = (DWORD)wParam;
		CategoryType eCategory = (CategoryType)lParam;

		TLOG(CH_UI, LV_LOG, (TEXT("OnMessageControlBrwsRes_Init() > eCategory=%d, nTotalNum=%d\r\n"), lParam, wParam) );

		///GetDlgItem(IDC_STATIC_BRWS_CATEGORY)->SetWindowText( GetBrowserCategoryName(eCategory) );
		

		m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = nTotalNum;
		m_pPlayerContext->m_stBrwsViewInfo.nUpdatedCnt = 0;
		m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth = 1;
		m_pPlayerContext->m_stBrwsViewInfo.cateHistory[m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth] = eCategory;
		m_pPlayerContext->m_stBrwsViewInfo.eCategory = eCategory;
		m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
		m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;

		if ( 0 < nTotalNum ){
			m_pPlayerContext->m_stBrwsReqInfo.eCategory = eCategory;
			m_pPlayerContext->m_stBrwsReqInfo.zStartIndex=0;
			m_pPlayerContext->m_stBrwsReqInfo.nCount = (UI_BRWS_UPDATE_UNIT_CNT < nTotalNum ) ? UI_BRWS_UPDATE_UNIT_CNT : nTotalNum;

			SendMsg(IPOD_LIST_START, 0, 0);
			m_isToReceiveList = false;//可以接收新的列表
			PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_GETNAME, (DWORD)(&(m_pPlayerContext->m_stBrwsReqInfo)), 0);

			//AddPath();
			///SetBrwsState( FALSE );	
		}
		else{
			//ClearBrws();
			///AddToBrws(0, L"< EMPTY >");
			///SetBrwsState( TRUE );	
		}
	}
	else/* fail */{ 
		SetControlUIState(TRUE);
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlBrwsRes_Init() > Failed = %d\r\n"), wParam));
	}

	return 0;
}


void IPodAppLib::SetControlUIState(BOOL bEnable) {

	SetPlayControlButtonEnable( bEnable );
	//SetBrwsState( bEnable );
}

DWORD IPodAppLib::OnMessageControlBrwsRes_Select(UINT msg, WPARAM wParam, LPARAM lParam) {
	CategoryType eCategory = (CategoryType)wParam;
	long nTotalNum = (DWORD)lParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_Select() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_Select() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_BRWS_SELECT], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 <= nTotalNum /*success*/){
		if ( (IPOD_LIB_TRACK == eCategory) && (IPOD_LIB_TRACK == m_pPlayerContext->m_stBrwsViewInfo.eCategory) ){
			// Play
			if (1) {		// 1-wire
				iPod_AudioStart();
			}

			PostMsg_ToCMDControlThread( WM_CMDCTRL_PLAY_IN_BRWSLIST, 0, 0 );

			if(m_pPlayerContext->m_bBrwsInitializedFlag == 1)
			{
				m_pPlayerContext->m_zCurrentTrackIndex = 0xFFFFFFFF;
				m_pPlayerContext->m_bBrwsInitializedFlag = 0;
			}
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETCURRENTTRACKINDEX, 0, 0 );
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );

			
			SetPlayControlButtonEnable(FALSE);
			//SetBrwsState(TRUE);
		}
		else{
			///GetDlgItem(IDC_STATIC_BRWS_CATEGORY)->SetWindowText( GetBrowserCategoryName(eCategory) );

			m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = nTotalNum;

			m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth++;
			m_pPlayerContext->m_stBrwsViewInfo.cateHistory[m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth] = eCategory;
			//m_pPlayerContext->m_stBrwsViewInfo.eCategory = GetBrowserSubCategory( eCategory );
			m_pPlayerContext->m_stBrwsViewInfo.eCategory = eCategory;

			m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
			m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;

			if ( 0 < nTotalNum ){
				m_pPlayerContext->m_stBrwsReqInfo.eCategory = eCategory;
				m_pPlayerContext->m_stBrwsReqInfo.zStartIndex=0;
				m_pPlayerContext->m_stBrwsReqInfo.nCount = (UI_BRWS_UPDATE_UNIT_CNT < nTotalNum ) ? UI_BRWS_UPDATE_UNIT_CNT : nTotalNum;

				SendMsg(IPOD_LIST_START, 0, 0);
				m_isToReceiveList = false;//可以接收新的列表
				PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_GETNAME, (DWORD)(&(m_pPlayerContext->m_stBrwsReqInfo)), 0);

				//AddPath();
				///SetBrwsState( FALSE );	
			}
			else{
				//ClearBrws();
				///AddToBrws(0, L"< EMPTY >");
				///SetBrwsState( TRUE );	
			}
		}
	}
	else/* fail */{ 
		SetControlUIState(TRUE);
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlBrwsRes_Select() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlBrwsRes_MoveUpper(UINT msg, WPARAM wParam, LPARAM lParam) {
	CategoryType eCategory = (CategoryType)wParam;
	long nTotalNum = (DWORD)lParam;

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_MoveUpper() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_MoveUpper() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_BRWS_MOVEUPPER], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if ( 0 <= nTotalNum /*success*/){

		m_pPlayerContext->m_stBrwsViewInfo.nTotalNum = nTotalNum;
		m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth--;

		//m_pPlayerContext->m_stBrwsViewInfo.eCategory = GetBrowserUpperCategory(eCategory);
		m_pPlayerContext->m_stBrwsViewInfo.eCategory = eCategory;
		m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = 0;
		m_pPlayerContext->m_stBrwsViewInfo.nCount = 0;

		m_pPlayerContext->m_stBrwsReqInfo.eCategory = eCategory;
		m_pPlayerContext->m_stBrwsReqInfo.zStartIndex=0;
		m_pPlayerContext->m_stBrwsReqInfo.nCount = (UI_BRWS_UPDATE_UNIT_CNT < nTotalNum ) ? UI_BRWS_UPDATE_UNIT_CNT : nTotalNum;

		SendMsg(IPOD_LIST_START, 0, 0);
		m_isToReceiveList = false;//可以接收新的列表
		PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_GETNAME, (DWORD)(&(m_pPlayerContext->m_stBrwsReqInfo)), 0);

		///GetDlgItem(IDC_STATIC_BRWS_CATEGORY)->SetWindowText( GetBrowserCategoryName(eCategory) );

		///SetBrwsState( FALSE );
	}
	else/* fail */{ 
		SetControlUIState(TRUE);
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlBrwsRes_MoveUpper() > Failed = %d\r\n"), wParam));
	}

	return 0;
}

DWORD IPodAppLib::OnMessageControlBrwsRes_GetName(UINT msg, WPARAM wParam, LPARAM lParam) {

#ifdef TIME_CHECK
	DWORD nCurrentTick = GetTickCount();
	//TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_GetName() > %d\r\n"),  nCurrentTick ));
	TLOG(CH_UI, LV_TIME, (TEXT("OnMessageControlBrwsRes_GetName() > %d %d\r\n"),  g_nMSGRequestCheckTick[WM_CMDCTRL_BRWS_GETNAME], (nCurrentTick-g_nMSGResCheckTick) ));
#endif

	if (m_isToReceiveList)//准备接受新的列表
	{
		return 0;
	}
	if ( 0 != wParam /*success*/){
		BRWSGetNameResInfo *pBrwsResInfo = (BRWSGetNameResInfo*)wParam;
		PIPOD_RECORD_TYPE pBrwsDBRecord = NULL;
		DWORD nCnt = 0;
		DWORD zIndex = 0;

		TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageControlBrwsRes_GetName() > wParam=0x%x\r\n"), wParam));

		if ( IS_NULL(pBrwsResInfo) || IS_NULL(pBrwsResInfo->pBrwsDBRecord)){
			TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlBrwsRes_GetName() > Invalid parameter\r\n")));
			goto EXIT;
		}

		TLOG(CH_UI, LV_DEBUG, (TEXT("Category=%d, nBrwsDBRecordNum=%d, DBRecordList=0x%x\r\n"), 
			pBrwsResInfo->eCategory, pBrwsResInfo->nBrwsDBRecordNum, pBrwsResInfo->pBrwsDBRecord ));

		nCnt = pBrwsResInfo->nBrwsDBRecordNum;
		pBrwsDBRecord = pBrwsResInfo->pBrwsDBRecord;

		// Clear broser lsit
		// ClearBrws();

		// Insert string
		for (zIndex=1; zIndex<=nCnt; zIndex++ )
		{
			SendMsg(IPOD_LIST_INSERT, 0, (LPARAM)(LPCTSTR)(LPSTR)(pBrwsDBRecord->Data));
			//GXNotify::SendNotify("ipod_msg", IPOD_LIST_INSERT, (LPARAM)(LPCTSTR)(LPSTR)(pBrwsDBRecord->Data));
			pBrwsDBRecord++;
		}
		SendMsg(IPOD_LIST_INSERT_END,0,0);
		// Insert string

		m_pPlayerContext->m_stBrwsViewInfo.zStartIndex = m_pPlayerContext->m_stBrwsReqInfo.zStartIndex;
		m_pPlayerContext->m_stBrwsViewInfo.nCount = m_pPlayerContext->m_stBrwsReqInfo.nCount;


		{//继续发送下一页
			DWORD nTotalNum = m_pPlayerContext->m_stBrwsViewInfo.nTotalNum;
			DWORD zRequestStartIndex = m_pPlayerContext->m_stBrwsViewInfo.zStartIndex 
				+ m_pPlayerContext->m_stBrwsViewInfo.nCount;
			DWORD nRequestCount = 0;

			if ((zRequestStartIndex+UI_BRWS_UPDATE_UNIT_CNT) < nTotalNum) {
				nRequestCount = UI_BRWS_UPDATE_UNIT_CNT;
			}
			else{
				nRequestCount = nTotalNum - zRequestStartIndex;
			}

			if (nRequestCount>0)
			{
				//m_pPlayerContext->m_stBrwsReqInfo.eCategory = eCategory;
				m_pPlayerContext->m_stBrwsReqInfo.zStartIndex=zRequestStartIndex;
				m_pPlayerContext->m_stBrwsReqInfo.nCount = nRequestCount;
				PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_GETNAME, (DWORD)(&(m_pPlayerContext->m_stBrwsReqInfo)), 0);
			}

		}

	}
	else/* fail */{ 
		TLOG(CH_UI, LV_WARN, (TEXT("OnMessageControlBrwsRes_GetName() > Failed = %d\r\n"), wParam));
	}

EXIT:

	return 0;
}

DWORD IPodAppLib::OnMessageGetiPodName(UINT msg, WPARAM wParam, LPARAM lParam)
{
	TLOG(CH_UI, LV_DEBUG, (TEXT("OnMessageGetiPodName() > wParam=0x%x\r\n"), wParam));

	if (wParam > 0)
	{
		//SendMsg(WM_IPOD, IPOD_MSG_NAME, lParam);
		//SendMsg(WM_IPOD, IPOD_MSG_AUTHSUCCESS, 1);	// 跳转到iPod

		GXNotify::SendNotify("ipod_name", lParam, 0);
	}
	return 0;
}


void IPodAppLib::IpodPlay()
{
	if (1)
	{		// 1-wire
		iPod_AudioStart();
	}
	PostMsg_ToCMDControlThread( WM_CMDCTRL_PLAY, 0, 0 );
}
void IPodAppLib::IpodPause()
{
	PostMsg_ToCMDControlThread( WM_CMDCTRL_PAUSE, 0, 0 );
}

void IPodAppLib::SetPlaypause()
{
	// TODO: 咯扁俊 牧飘费 舅覆 贸府扁 内靛甫 眠啊钦聪促.
	switch (m_pPlayerContext->m_playstatus) {
		case PS_PAUSED:
			/*if ((int)nCurrentFileNum <= 0)
			{
				break;
			}*/
			//if (m_radio1wire.GetCheck()) 
			{		// 1-wire
				iPod_AudioStart();
			}

			PostMsg_ToCMDControlThread( WM_CMDCTRL_PLAY, 0, 0 );

			SetPlayControlButtonEnable(FALSE);
			break;

		case PS_FFREW:
			PostMsg_ToCMDControlThread( WM_CMDCTRL_PLAY, 0, 0 );
			SetPlayControlButtonEnable(FALSE);
			break;

		case PS_PLAY:
			// Moved to OnMessageControlRes_Pause()
			//if (m_radio1wire.GetCheck()) {		// 1-wire
			//	iPod_AudioStop();
			//}
			
			PostMsg_ToCMDControlThread( WM_CMDCTRL_PAUSE, 0, 0 );

			SetPlayControlButtonEnable(FALSE);

			break;
	}

}

void IPodAppLib::IpodNext()
{
	switch (m_pPlayerContext->m_playstatus) {
		case PS_PAUSED:
#ifdef TEST_CLEAR_BUFFER
			iPod_SetAudioBufferClearFlag( TRUE );
#endif

		case PS_PLAY:
			PostMsg_ToCMDControlThread( WM_CMDCTRL_NEXTTRACK, 0, 0 );
			break;
	}
}

void IPodAppLib::IpodPrev()
{
	switch (m_pPlayerContext->m_playstatus) {
		case PS_PAUSED:
#ifdef TEST_CLEAR_BUFFER
			iPod_SetAudioBufferClearFlag( TRUE );
#endif

		case PS_PLAY:
			PostMsg_ToCMDControlThread( WM_CMDCTRL_PREVIOUSTRACK, 0, 0 );
			break;
	}
}

BOOL IPodAppLib::IsConnected()
{
	return isConnect;
}

BOOL IPodAppLib::HasVideo()
{
	return hasVideo;
}





BOOL IPodAppLib::ListBack()
{
	m_pPlayerContext->m_zCurrentTrackIndex = 0xFFFFFFFF;
	m_isToReceiveList = true;
	if ( 1< m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth ){
		CategoryType eCategory = m_pPlayerContext->m_stBrwsViewInfo.eCategory;

		//eCategory = GetBrowserUpperCategory(eCategory);
		PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_MOVEUPPER, (DWORD)eCategory, 0);
		return TRUE;
	}
	InitBrws();
	return FALSE;
}




// for video
void IPodAppLib::ResetDBSelectionHierarchy(IPOD_SEL_DB_TYPE hierachy)
{
	m_ipod_hierarchy = hierachy;
	IPOD_SelectDBHierarchy((void*)m_pPlayerContext->m_iPodHandle, (IPOD_SEL_DB_TYPE)hierachy);
}


void IPodAppLib::MusicRestore()
{
	music_brws_info = m_pPlayerContext->m_stBrwsViewInfo;
}


void IPodAppLib::VideoRestore()
{
	video_brws_info = m_pPlayerContext->m_stBrwsViewInfo;
	// 记录下当前播放的曲目

}







void IPodAppLib::InitHierarchy( IPOD_SEL_DB_TYPE hierachy, int index )//初始化第一层目录
{

	//ipod_path[0] = 0;
	ASSERT(hierachy == DBSEL_AUDIO || hierachy == DBSEL_VIDEO);
	m_ipod_hierarchy = hierachy;

	InitBrws();
	CategoryType eCategory = IPOD_LIB_TRACK;
	if (DBSEL_AUDIO == hierachy)
	{
		eCategory = GetBrowserTopCategory( index );
	}
	m_isToReceiveList = true;
	PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_INIT, eCategory, m_ipod_hierarchy );
}



BOOL IPodAppLib::IpodSelectList(int index)
{
	ASSERT(m_ipod_hierarchy == DBSEL_AUDIO || m_ipod_hierarchy == DBSEL_VIDEO);

	int zSelectedIndex = index;

	if ( zSelectedIndex < 0 ){
		zSelectedIndex = 0;
	}

	TLOG(CH_UI, LV_LOG, (TEXT("OnBnClickedButtonBrwsSelectItem() > %d is selected\r\n"), zSelectedIndex));

	if ( 0 == m_pPlayerContext->m_stBrwsViewInfo.BrwsDepth ){
		CategoryType eCategory = IPOD_LIB_TRACK;
		if (DBSEL_AUDIO == m_ipod_hierarchy)
		{
			eCategory = GetBrowserTopCategory( zSelectedIndex );
		}

		PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_INIT, eCategory, m_ipod_hierarchy);
		m_isToReceiveList = true;
	}
	else{
		CategoryType eCategory = m_pPlayerContext->m_stBrwsViewInfo.eCategory;

		//zSelectedIndex = m_pPlayerContext->m_stBrwsViewInfo.zStartIndex + zSelectedIndex;
		ASSERT(zSelectedIndex<m_pPlayerContext->m_stBrwsViewInfo.nTotalNum);
		PostMsg_ToCMDControlThread( WM_CMDCTRL_BRWS_SELECT, (DWORD)eCategory, zSelectedIndex);


		if (eCategory == IPOD_LIB_TRACK)
		{
			PostMsg_ToCMDControlThread( WM_CMDCTRL_GETTOTALPLAYTRACKS, 0, 0 );
			return TRUE;
		}
		m_isToReceiveList = true;
		
	}

	
	return FALSE;
}


void IPodAppLib::SetPlayControlButtonEnable( BOOL bEnable )
{
	SendMsg(IPOD_PLAY_CONTROL, (WPARAM)bEnable, 0);
}


extern HWAVEOUT h_output;

void IPodAppLib::Ipod_Mute(BOOL mute)
{
	ipod_mute = mute;
	if (mute)
	{
		Ipod_SetVolume(0);
	}
	else
	{
		Ipod_SetVolume(ipod_volume);
	}
}

void IPodAppLib::Ipod_SetVolume(DWORD dwVolume) {
#if 0
	HWAVEOUT hwo;
	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 1;
	wf.nSamplesPerSec = 8000 * 1000;
	wf.wBitsPerSample = 8;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	wf.cbSize = 0;
	if (waveOutOpen(&hwo, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL)==MMSYSERR_NOERROR) {
		waveOutSetVolume(hwo, dwVolume); 
		waveOutClose(hwo);
	}
#else
	
	if (dwVolume < 0)
	{
		dwVolume = 0;
	}
	if (dwVolume > 30)
	{
		dwVolume = 30;
	}
	if (dwVolume)
	{
		ipod_volume = dwVolume;
	}
	if (ipod_mute == 1)
	{
		dwVolume = 0;
	}
	if (h_output == NULL)
	{
		return;
	}
	dwVolume = dwVolume*65535/30;
	waveOutSetVolume(h_output,dwVolume|(dwVolume<<16));
#endif
}