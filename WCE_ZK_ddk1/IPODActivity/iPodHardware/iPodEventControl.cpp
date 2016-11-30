
#include "stdafx.h"
#include "iPodConfig.h"

//#include "iPodPlayer.h"
//#include "iPodPlayerDlg.h"
#include "iPodEventControl.h"
#include <winioctl.h>


typedef enum {
	IPOD_STATE_INITIALIZED,
	IPOD_STATE_TERMINATED,

	IPOD_STATE_MAX
} EVENTPROCESSOR_STATE;

WM_UI_MSGID iPodGet_AppiPodStatusMsg(IPOD_DR_PLAY_STATUS status)
{
	WM_UI_MSGID UI_StatusMsg = WM_UI_UPDATE_NONE;
	switch(status)
	{
		case(IPOD_DR_PLAYBACK_STOPPED):
			UI_StatusMsg = WM_UI_UPDATE_PAUSE;
			break;

		case(IPOD_DR_PLAYING):
			UI_StatusMsg = WM_UI_UPDATE_PLAYING;
			break;

		case(IPOD_DR_PLAYBACK_PAUSED):
			UI_StatusMsg = WM_UI_UPDATE_PAUSE;
			break;

		case(IPOD_DR_FAST_FORWARD):
			break;

		case(IPOD_DR_FAST_REWIND):
			break;

		case(IPOD_DR_END_FAST_FORWARD_OR_REWIND):
			/* WM_UI_UPDATE_FFSEEKSTOP & WM_UI_UPDATE_FFSEEKSTOP happens same response*/
			 UI_StatusMsg = WM_UI_UPDATE_FFSEEKSTOP;
			//WM_UI_UPDATE_FFSEEKSTOP
			break;

		default:
			break;

	}

	return UI_StatusMsg;
}



DWORD iPodEventControlThread(LPVOID pData) {
	HWND hWnd=(HWND)pData;

	EVENTPROCESSOR_STATE	iPodEventState = IPOD_STATE_INITIALIZED;
	MSG MsgToUI;
	MSG ReceivedMsg;
	BOOL IsSuccess = FALSE;
	IPOD_DR_PLAY_STATUS Rd_playStatus;
	WM_UI_MSGID UI_Msg;
	

	TLOG(CH_EVTCTL, LV_LOG, (TEXT("+ iPodEventControlThread() > \r\n")));

	
	MsgToUI.hwnd = hWnd;
	MsgToUI.message = 0;
	MsgToUI.wParam = 0;
	MsgToUI.lParam = 0;
	
	while ( IPOD_STATE_TERMINATED != iPodEventState ) {

		// Check message
		if ( FALSE == GetMessage(&ReceivedMsg, NULL, 0, 0) ){
			//Sleep(100);
			break;
		}
		else{
			IsSuccess = FALSE;
			MsgToUI.wParam = 0;
			MsgToUI.lParam = 0;
			switch( ReceivedMsg.message ){
				case WM_EVENTCTRL_TERMINATE:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> WM_EVENTCTRL_TERMINATE > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));


					iPodEventState = IPOD_STATE_TERMINATED;
					break;


				//////////////////////////////////////////////////////////////////
				//
				//
				//
				case IPOD_APP_EVT_STOPPED:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_STOPPED > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

				case IPOD_APP_EVT_TRACKCHANGED:
				case IPOD_APP_DR_EVT_TRACK_INDEX:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_TRACKCHANGED > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					MsgToUI.message = WM_UI_UPDATE_CURRENTTRACKNUM;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					break;

				case IPOD_APP_EVT_FFSEEKSTOP:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_FFSEEKSTOP > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					MsgToUI.message = WM_UI_UPDATE_FFSEEKSTOP;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);

					break;
				case IPOD_APP_EVT_REWSEEKSTOP:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_REWSEEKSTOP > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					MsgToUI.message = WM_UI_UPDATE_REWSEEKSTOP;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					break;

				case IPOD_APP_EVT_TRACKPOSITION:
				case IPOD_APP_DR_EVT_TRACK_POSITION:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_TRACKPOSITION > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					MsgToUI.message = WM_UI_UPDATE_TRACKPLAYBACKPOSITION;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					break;

				case IPOD_APP_EVT_CHANGE_SAMPLEFREQ:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_CHANGE_SAMPLEFREQ > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					MsgToUI.message = WM_UI_UPDATE_SAMPLINGFREQUENCE;
					MsgToUI.wParam = (ReceivedMsg.wParam & 0x0000FFFF);
					MsgToUI.lParam = (ReceivedMsg.lParam & 0x0000FFFF);
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					break;

				case IPOD_APP_EVT_CATEGORIZED_DATABASE_RECORD:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_EVT_CATEGORIZED_DATABASE_RECORD > WPARAM=0x%x, LPARAM=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));
					break;


				case IPOD_APP_DR_EVT_CHAPTER_INFO:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_CHAPTER_INFO > current index=0x%x, chapter index=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

				case IPOD_APP_DR_EVT_PLAY_STATUS:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_PLAY_STATUS > Playstatus=0x%x \r\n"), 
												ReceivedMsg.wParam));
					Rd_playStatus = (IPOD_DR_PLAY_STATUS)ReceivedMsg.wParam;
					UI_Msg = iPodGet_AppiPodStatusMsg(Rd_playStatus);
					MsgToUI.message = UI_Msg;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					
					break;

				case IPOD_APP_DR_EVT_MUTE_UI_VOL:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_MUTE_UI_VOL > MuteState=0x%x, UIvolLevel=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

				case IPOD_APP_DR_EVT_POWER_BATTERY:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_POWER_BATTERY > PowerStatus=0x%x, BatteryLevel=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;
	
				case IPOD_APP_DR_EVT_EQALIZER_STATE:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_EQALIZER_STATE > EqStatus=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_SHUFFLE:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_SHUFFLE > ShuffleStatus=0x%x \r\n"), 
												ReceivedMsg.wParam));
					MsgToUI.message = WM_UI_UPDATE_SHUFFLE;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);

					break;

				case IPOD_APP_DR_EVT_REPEAT:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_REPEAT > RepeatStatus=0x%x \r\n"), 
												ReceivedMsg.wParam));
					MsgToUI.message = WM_UI_UPDATE_REPEAT;
					MsgToUI.wParam = ReceivedMsg.wParam;
					PostMessage(MsgToUI.hwnd, MsgToUI.message, MsgToUI.wParam, MsgToUI.lParam);
					break;

				case IPOD_APP_DR_EVT_DATE_TIME:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_DATE_TIME > Hour=0x%x, Minute=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

				case IPOD_APP_DR_EVT_ALARM:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_ALARM > AlarmStatus=0x%x, Hour(0x0000FF00) + Min(0x000000FF)=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

				case IPOD_APP_DR_EVT_BACKLIGHT:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_BACKLIGHT > BackLight=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_HOLD_SWITCH:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_HOLD_SWITCH > Holdswitch=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_SOUND_CHECK:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_SOUND_CHECK > SoundCheck=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_AUDIOBOOK:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_AUDIOBOOK > AudioBook=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_TRACK_POSITION_IN_SECONDS:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_TRACK_POSITION_IN_SECONDS > TimePosition(ms)=0x%x \r\n"), 
												ReceivedMsg.wParam));

					break;

				case IPOD_APP_DR_EVT_MUTE_UI_ABSOLUTE_VOL:
					TLOG(CH_EVTCTL, LV_DEBUG,(TEXT("> IPOD_APP_DR_EVT_ALARM > MuteState=0x%x, (int) UIVolume(0x0000FF00) + AbsoluteVolume(0x000000FF)=0x%x\r\n"), 
												ReceivedMsg.wParam, ReceivedMsg.lParam));

					break;

					
				default:
					TLOG(CH_EVTCTL, LV_WARN, (TEXT("> Invalid message\r\n")));

					Sleep(100);

					IsSuccess = FALSE;
					break;
			}			

		}

	}
		

	TLOG(CH_EVTCTL, LV_LOG, (TEXT("- iPodEventControlThread() > \r\n")));

	return 0;
}


HANDLE iPod_StartEventControlThread( HANDLE hWnd, DWORD *pThreadID ) {
	BOOL fRet = FALSE;
	HANDLE hThread = NULL;
	DWORD ThreadID = 0;

	TLOG(CH_EVTCTL, LV_LOG, (TEXT("+ iPod_StartEventControlThread() > \r\n")));

	if ( IS_NULL(hWnd) ){
		TLOG(CH_EVTCTL, LV_LOG, (TEXT("iPod_StartEventControlThread() > Invalid parameter\r\n")));
		goto EXIT;
	}
	
	
	hThread=CreateThread(NULL,0,iPodEventControlThread, hWnd,0, &ThreadID );
	if ( NULL!=hThread ){
		if ( pThreadID ) *pThreadID = ThreadID;
	}

EXIT:
	
	TLOG(CH_EVTCTL, LV_LOG, (TEXT("- iPod_StartEventControlThread() > \r\n")));

	return hThread;
}

BOOL iPod_StopEventControlThread( HANDLE hThread, DWORD ThreadID ) {
	BOOL fRet = FALSE;
	
	TLOG(CH_EVTCTL, LV_LOG, (TEXT("+ iPod_StopEventControlThread() > \r\n")));

	if ( hThread && ThreadID ){
		DWORD ExitCode = 0;
		
		PostThreadMessage( ThreadID, WM_EVENTCTRL_TERMINATE, 0, 0);

		Sleep(500); // ?

		if ( GetExitCodeThread( hThread, &ExitCode ) ){
			ExitThread( ExitCode );

			fRet = TRUE;
		}
		else{
			TLOG(CH_EVTCTL, LV_ERROR, (TEXT("iPod_StopEventControlThread() > %d \r\n"), GetLastError()));
		}
		//TerminateThread(hThread,0);

		CloseHandle( hThread );
		hThread = NULL;

	}

	TLOG(CH_EVTCTL, LV_LOG, (TEXT("- iPod_StopEventControlThread() > \r\n")));

	return fRet;
}



