#include "stdafx.h"

#include "ipod.h"
#include "i2c/chip.h"
#include "pip/PIP.h"
#include "Audio/Audio.h"
#include "Video/Video.h"
#include "GxxPopWindow.h"
#include "Navi.h"
//#include "MediaMsg.h"

#define TIMER_CHECKVIDEO	20
#define TIMER_CHECKIPOD		21

//#define IPOD_CRACK_TEST
#define IPODDEBUG 0

void IpodWnd::Init()
{
	//pIpodHardware = IpodHardware::Instance(pWindow->GetHwnd());
	//pIpodHardware->RegisterMsg(HandlerIpodMsg, (DWORD)this);

	pIPodLib = iPodLib::Instance(pWindow->GetHwnd());
	pIPodLib->RegisterMsg(HandlerIpodMsg, (DWORD)this);

	iCurTime = iTotalTime = 0;
	bHasIpod = NOIPOD;
	ipodPlayStatus = IPOD_STOP;
	videoType = -1;

	pProbarIpod->SetFunLeave(ClickIpodBar, this);
	pProbarList->Enable(0);

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = IpodDetectNotify;
	GXNotify::RegisterNotifyHandler("ipod_detect", notify);
	notify.dwParam = this;
	notify.funNotify = PowerOff;
	GXNotify::RegisterNotifyHandler("system_poweroff", notify);
	notify.dwParam = this;
	notify.funNotify = SystemMute;
	GXNotify::RegisterNotifyHandler("system_mute", notify);
	notify.dwParam = this;
	notify.funNotify = SystemNext;
	GXNotify::RegisterNotifyHandler("system_next", notify);
	notify.dwParam = this;
	notify.funNotify = SystemPrev;
	GXNotify::RegisterNotifyHandler("system_prev", notify);
	notify.dwParam = this;
	notify.funNotify = SysRightKey;
	GXNotify::RegisterNotifyHandler("right_key", notify);
	notify.dwParam = this;
	notify.funNotify = NaviMediaControl;
	GXNotify::RegisterNotifyHandler("navi_media_control", notify);

	pPlayList->SetFun(IpodListClick, this);


	pMainWnd = (GxxWindow*)pWindow->GetParent()->GetChildFromID(L"main");
	pListWnd = (GxxWindow*)pWindow->GetParent()->GetChildFromID(L"ipodlist");
	pWndMusic = (GxxWindow*)pMainWnd->GetChildFromID(L"ipod");

	bPreviewMode = 0;

	pLabRepeatFolder->Enable(0);
	
}

void IpodWnd::Start()
{
	Audio::ToIpod();
	pIPodLib->RegisterMsg(HandlerIpodMsg, (DWORD)this);
	pIPodLib->MusicResume();
}

void IpodWnd::End()
{
	if (!pWindow)
	{
		return;
	}
	pIPodLib->IpodPause();
	SelectionToHome(NULL);
	PreviewStop();
}

void IpodWnd::Entry()
{
}

void IpodWnd::Leave()
{
}

void IpodWnd::Deinit()
{

}

void IpodWnd::SetControlFun(GXBaseControl *pControl, const char *funtype, const char *funval)
{
	if (0 == cmpAstr(funtype, "label"))
	{
		if (0 == cmpAstr(funval, "curtime_ipod"))
		{
			pCurTime = (GxxLabel* )pControl;
		}
		if (0 == cmpAstr(funval, "totaltime_ipod"))
		{
			pTotalTime = (GxxLabel *)pControl;
		}
		if (0 == cmpAstr(funval, "display1_ipod"))
		{
			pLabDisplay1 = (GxxLabel*)pControl;
		}
		if (0 == cmpAstr(funval, "display2_ipod"))
		{
			pLabDisplay2 = (GxxLabel*)pControl;
		}
		if (0 == cmpAstr(funval, "display3_ipod"))
		{
			pLabDisplay3 = (GxxLabel*)pControl;
		}
		COMBINE_LABEL(pLabIpodInfo, IpodInfo);
	}
	if (0 == cmpAstr(funtype, "probar"))
	{
		if (0 == cmpAstr(funval, "MusicBar_ipod"))
		{
			pProbarIpod = (GxxProBar *)pControl;
		}
		if (0 == cmpAstr(funval, "probar_main"))
		{
			pProbarList = (GxxProBar*)pControl;
		}
	}
	if (0 == cmpAstr(funtype, "listview"))
	{
		if (0 == cmpAstr(funval, "ipodlist"))
		{
			pPlayList = (GxxListView*)pControl;
		}
	}
	if (0 == cmpAstr(funtype, "click"))
	{
		COMBINE_BUTTON_FUN(IpodSelection);
		COMBINE_BUTTON_FUN(IpodBack);
		COMBINE_BUTTON_FUN(IpodListDown);
		COMBINE_BUTTON_FUN(IpodListUp);
		COMBINE_BUTTON_FUN(SelectionToHome);
		COMBINE_LABEL_FUN(pButtPlay, KeyPlay);
		COMBINE_LABEL_FUN(pButtPause, KeyPause);
		COMBINE_BUTTON_FUN(KeyNext);
		COMBINE_BUTTON_FUN(KeyPrev);
		COMBINE_LABEL_FUN(pLabKeyMode, KeyMode);
		COMBINE_LABEL_FUN(pLabModePreview, ModePreview);
		COMBINE_LABEL_FUN(pLabModeRandom, ModeRand);
		COMBINE_LABEL_FUN(pLabKeyRepeat, KeyRepeat);
		COMBINE_LABEL_FUN(pLabRepeatTrack, RepeatTrack);
		COMBINE_LABEL_FUN(pLabRepeatFolder, RepeatFolder);
	}
}

void IpodWnd::KeyPlay(GXBaseControl *pControl)
{
	pIPodLib->IpodPlay();
	pButtPlay->ShowWindow(0, 1);
	pButtPause->ShowWindow(1, 1);
}

void IpodWnd::KeyPause(GXBaseControl *pControl)
{
	pIPodLib->IpodPause();
	pButtPause->ShowWindow(0, 1);
	pButtPlay->ShowWindow(1, 1);
}

void IpodWnd::KeyNext(GXBaseControl *pControl)
{
	if (pLabKeyRepeat->GetTextID() != L"ID_REPEAT")
	{
		KeyRepeat(NULL);
	}
	KeyRight(NULL);
}

void IpodWnd::KeyPrev(GXBaseControl *pControl)
{
	KeyLeft(NULL);
}

void IpodWnd::KeyFF(GXBaseControl *pControl)
{
	KeyRight(NULL);
}

void IpodWnd::KeyFB(GXBaseControl *pControl)
{
	KeyLeft(NULL);
}

void IpodWnd::KeyMenu(GXBaseControl *pControl)
{
	//ipodList.ReturnToTop();
}

void IpodWnd::KeyOK(GXBaseControl *pControl)
{
}

void IpodWnd::KeyStop(GXBaseControl *pControl)
{
	//pIpodHardware->Stop();
}

void IpodWnd::KeyUp(GXBaseControl *pControl)
{
	{
	//	ipodList.GetPrevList();
	}
}

void IpodWnd::KeyDown(GXBaseControl *pControl)
{
	{
		//ipodList.GetNextList();
	}
}

void IpodWnd::KeyLeft(GXBaseControl *pControl)
{
	//if (ipodAuthMode == IPOD_CPAUTH)
	{
		pIPodLib->IpodPrev();
	}
}

void IpodWnd::KeyRight(GXBaseControl *pControl)
{
	//if (ipodAuthMode >= IPOD_CRACKAUTH)
	{
		pIPodLib->IpodNext();
	}
	
}

void IpodWnd::KeyPlayPause(GXBaseControl *pControl)
{
	{
		/*pIpodHardware->Play();
		pIpodHardware->ReleaseKey();
		if (ipodPlayStatus != IPOD_PLAYING || ipodPlayStatus != IPOD_PAUSE)
		{
			pIpodHardware->GetPlayStatus();
		}*/
	}
}

DWORD IpodWnd::HandlerIpodMsg(CHardware *pControl, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case IPOD_AUTHSUCCESS:
		{
			if (lParam == 0)
			{
				GXNotify::SendNotifyAsync(pWindow->GetHwnd(), "device_notify", DEV_IPOD, ATTACH_START);
				// 开始播放并且获取播放状态
				//pIpodHardware->ResetDBSelection();
				//pIpodHardware->SelectDBRecord(IpodHardware::CATE_TRACK, 0);
				//pIpodHardware->SetRepeat(IpodHardware::REPEAT_ALL);
			}
			if (lParam == 1)
			{
				GXNotify::SendNotifyAsync(pWindow->GetHwnd(), "device_notify", DEV_IPOD, ATTACH_END);
			}
			break;
		}
	case IPOD_NAME:
		{
			if (lParam != 0)
			{
				if (pLabDisplay1->GetText().IsEmpty())
				{
					GXNotify::SendNotifyAsync(pWindow->GetHwnd(), "device_notify", DEV_IPOD, ATTACH_START);
				}
				pLabDisplay1->SetText((LPCTSTR)lParam, 1);
				
			}
			else
			{
				pLabDisplay1->SetText(L"", 1);
				//ipodList.ReturnToTop();
				GXNotify::SendNotifyAsync(pWindow->GetHwnd(), "device_notify", DEV_IPOD, DETACH_END);
			}
			break;
		}
	case IPOD_TIME:
		{
			int curTime = pIPodLib->GetCurTime();
			int totalTime = pIPodLib->GetTotalTime();
			if (totalTime)
			{
				pProbarIpod->SetRange(0, totalTime);
				pProbarIpod->SetDisplayPos(curTime);
			}
			GXString str;
			str.TimeStr(curTime);
			pCurTime->SetText(str, 1);
			str.TimeStr(totalTime-curTime);
			pTotalTime->SetText((GXString)L"-"+str, 1);
			if (bPreviewMode)
			{
				if (curTime > 10)
				{
					KeyNext(NULL);
				}
			}
			break;
		}
	case IPOD_PLAYSTATUS:
		{
			ipodPlayStatus = lParam;
			if (lParam == IPOD_PLAYING)
			{
				pButtPlay->ShowWindow(0, 1);
				pButtPause->ShowWindow(1, 1);
				Navi::SendPlayStatus(TYPE_IPOD, 0);
			}
			if (lParam == IPOD_STOP || lParam == IPOD_PAUSE)
			{
				pButtPlay->ShowWindow(1, 1);
				pButtPause->ShowWindow(0, 1);
				Navi::SendPlayStatus(TYPE_IPOD, 1);
			}
			break;
		}
	case IPOD_ARTIST:
		{
			pLabDisplay3->SetText((LPCTSTR)lParam, 1);
			break;
		}
	case IPOD_ALBUM:
		{
			break;
		}
	case IPOD_GENRE:
		{
			break;
		}
	case IPOD_TITLE:
		{
			//RETAILMSG(1, (TEXT("IPOD_TITLE = %s\r\n"), (TCHAR*)lParam));
			pLabDisplay2->SetText((LPCTSTR)lParam, 1);
			Navi::SendMediaStatus(TYPE_IPOD, L"IPOD", ipodPlayStatus-1,(LPCTSTR)lParam);
			break;
		}
	case IPOD_NUMRECORD:
		{
			//ipodList.ReturnNumberCategorizedDBRecords((BYTE*)lParam);
			break;
		}
	case IPOD_CATRECORD:
		{
			//ipodList.ReturnCategorizedDBRecords((BYTE*)lParam);
			break;
		}
	case IPOD_SHUFFLE:
		{
			// 0x00 shuffle off
			// 0x01 shuffle tracks
			// 0x02 shuffle albums
			if (lParam == 0x00)
			{
				pLabKeyMode->SetTextID(L"ID_MODE", 1);
			}
			if (lParam == 0x01)
			{
				pLabKeyMode->SetTextID(L"ID_PREFIXRANDOM", 1);
			}
			if (lParam == 0x02)
			{
				pLabKeyMode->SetTextID(L"ID_PREFIXRANDOM", 1);
			}
			break;
		}
	case IPOD_REPEAT:
		{
			// 0x00 repeat off
			// 0x01 repeat one track
			// 0x02 repeat all track
			if (lParam == 0x00)
			{
				pLabKeyRepeat->SetTextID(L"ID_REPEAT", 1);
			}
			if (lParam == 0x01)
			{
				pLabKeyRepeat->SetTextID(L"ID_REPEATTRACK", 1);
			}
			if (lParam == 0x02)
			{
				pLabKeyRepeat->SetTextID(L"ID_REPEAT", 1);
			}
			break;
		}
	case IPOD_MSG_SETPATH:
		{
			pLabIpodInfo->SetText((LPCTSTR)lParam, 1);
			break;
		}
	}
	switch(wParam)
	{
	case IPOD_LIST_INIT:
		{
			pPlayList->DeleteAllItem();
			InsertSongID(L"ID_PLAYLIST");
			InsertSongID(L"ID_ARTIST");
			InsertSongID(L"ID_ALBUM");
			InsertSongID(L"ID_GENRE");
			InsertSongID(L"ID_TRACK");
			pPlayList->Invalidate(1);
			pProbarList->SetRange(0, 0);
			pProbarList->Invalidate(1);
			break;
		}
	case IPOD_LIST_CLEAR:
		{
			pPlayList->DeleteAllItem();
			//pPlayList->Invalidate(1);
			break;
		}
	case IPOD_LIST_INSERT:
		{
			ListItem *p = InsertSong((LPCTSTR)lParam);
			//if (ipodList.IsInTrackList() && pRecord->index == pIpodHardware->GetNowIndex())
			//{
			//	pPlayList->SetItemStatus(p, LVIS_SELECTED);
			//}
			break;
		}
	case IPOD_LIST_INSERTEND:
		{
			//IpodRecord *pRecord = (IpodRecord*)lParam;
			//ListItem *p = InsertSong(pRecord->sRecord);
			//if (ipodList.IsInTrackList() && pRecord->index == pIpodHardware->GetNowIndex())
			//{
			//	pPlayList->SetItemStatus(p, LVIS_SELECTED);
			//}
			pPlayList->Invalidate(1);
			pProbarList->SetRange(0, pIPodLib->GetCount());
			pProbarList->SetDisplayPos(pIPodLib->GetNowIndex());
			pProbarList->Invalidate(1);
			break;
		}
	}
	return 0;
}

LRESULT IpodWnd::DoTimer(GXBaseControl *pControl, UINT nID)
{
	return 0;
}

GXString IpodWnd::FormatTimeString(int time)
{
	int hour = time/3600;
	int min = (time - hour*3600)/60;
	int sec = time % 60;
	GXString str;
	if (hour)
	{
		str.Format(_T("%0d:%02d:%02d"), hour, min, sec);
	}
	else
	{
		str.Format(_T("%02d:%02d"), min, sec);
	}
	return str;
}

LRESULT IpodWnd::DoLButtonDown(GXBaseControl *pControl, POINT pt)
{
	return CONTINUECLICK;
}


LRESULT IpodWnd::DoLButtonUp(GXBaseControl *pControl, POINT pt)
{
	bPressed = 0;
	return 0;
}


LRESULT IpodWnd::IpodDetectNotify(DWORD param1, DWORD param2)
{
	if (param1 == 1)
	{
		if (pWindow->IsVisible())
		{
			RETAILMSG(IPODDEBUG, (TEXT("Ipod detect-------\r\n")));
			if (bHasIpod == NOIPOD)
			{
			}
		}
	}
	else
	{
		RETAILMSG(IPODDEBUG, (TEXT("No Ipod-------\r\n")));
		bHasIpod = NOIPOD;
		sIpodName.Empty();
		pPlayList->DeleteAllItem();
		pPlayList->Invalidate(1);
	}
	return 0;
}

LRESULT IpodWnd::IpodClick(DWORD param1, DWORD param2)
{
	int type = pPlayList->GetSelected();
	if (type >= 0)
	{
	//	ipodList.IpodListSelect(type, ((GxxPlayList*)pPlayList)->GetSelectedSong());
	}
	return 0;
}

void IpodWnd::IpodListClick(GXBaseControl *pControl)
{
	int type = pPlayList->GetSelected();
	pIPodLib->IpodListSelect(type, ((GxxPlayList*)pPlayList)->GetSelectedSong());
}

void IpodWnd::IpodSelection(GXBaseControl *pControl)
{
	//if (pIpodHardware->GetHierarchy() != IpodHardware::HIERARCHY_MUSIC)
	//{
	//	ipodList.ReturnToTop();
	//}
	//ipodList.Select(pIpodHardware->GetNowIndex());
	pMainWnd->ShowWindow(0, 1);
	pListWnd->ShowWindow(1, 1);
}

void IpodWnd::IpodBack(GXBaseControl *pControl)
{
	pIPodLib->ListBack();
}

void IpodWnd::IpodListDown(GXBaseControl *pControl)
{
	pIPodLib->GetNextList();
}

void IpodWnd::IpodListUp(GXBaseControl *pControl)
{
	pIPodLib->GetPrevList();
}

void IpodWnd::SelectionToHome(GXBaseControl *pControl)
{
	pMainWnd->ShowWindow(1, 1);
	pListWnd->ShowWindow(0, 1);
}


void IpodWnd::KeyRepeat(GXBaseControl *pControl)
{
	// steven
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionRepeat");
	if (pWnd && pWnd->IsVisible())
	{
		pWnd->ShowWindow(0, 1);
		return;
	}

	if (pLabKeyRepeat->GetTextID() != L"ID_REPEAT")
	{
		pIPodLib->SetRepeat(REPEATALLTRACKS);
		pLabKeyRepeat->SetTextID(L"ID_REPEAT", 1);
	}
	else
	{
		if (pWnd)
		{
			pWnd->AddUnCoverControl(pControl);
		}
		pLabKeyRepeat->DoMotionFromXml(NULL);
	}
	
}
void IpodWnd::RepeatFolder(GXBaseControl *pControl)
{
	pIPodLib->SetRepeat(REPEATALLTRACKS);
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionRepeat");
	pWnd->ShowWindow(0, 1);
	pLabKeyRepeat->SetTextID(L"ID_REPEATALL", 1);
	PreviewStop();
}
void IpodWnd::RepeatTrack(GXBaseControl *pControl)
{
	pIPodLib->SetRepeat(REPEATONETRACK);
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionRepeat");
	pWnd->ShowWindow(0, 1);
	pLabKeyRepeat->SetTextID(L"ID_REPEATTRACK", 1);
	PreviewStop();
}

void IpodWnd::KeyMode(GXBaseControl *pControl)
{
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionMode");
	if (pWnd && pWnd->IsVisible())
	{
		pWnd->ShowWindow(0, 1);
		return;
	}
	if (pLabKeyMode->GetTextID() != L"ID_MODE")
	{
		pIPodLib->SetShuffle(SHUFFLEOFF);
		pLabKeyMode->SetTextID(L"ID_MODE", 1);
		bPreviewMode = 0;
	}
	else
	{
		if (pWnd)
		{
			pWnd->AddUnCoverControl(pControl);
		}
		pLabKeyMode->DoMotionFromXml(NULL);
	}
}
void IpodWnd::ModeRand(GXBaseControl *pControl)
{
	pIPodLib->SetShuffle(SHUFFLETRACKS);
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionMode");
	pWnd->ShowWindow(0, 1);
	pLabKeyMode->SetTextID(L"ID_PREFIXRANDOM", 1);
}
void IpodWnd::ModePreview(GXBaseControl *pControl)
{
	GxxPopWindow *pWnd = (GxxPopWindow*)pWndMusic->GetChildFromID(L"motionMode");
	pWnd->ShowWindow(0, 1);
	pLabKeyMode->SetTextID(L"ID_PREFIXPREVIEW", 1);
	bPreviewMode = 1;
}

BOOL IpodWnd::IsDeviceExist()
{
	return pIPodLib->IsConnected();
}

LRESULT IpodWnd::PowerOff(DWORD param1, DWORD param2)
{
	return 0;
}

LRESULT IpodWnd::SystemMute(DWORD param1, DWORD param2)
{
	if (eRunningStatus == NOTRUNNING)
	{
		return 0;
	}
	if (param1 == 1)
	{
		KeyPause(NULL);
	}
	else
	{
		KeyPlay(NULL);
	}
	return 0; 
}

LRESULT IpodWnd::SystemNext(DWORD param1, DWORD param2)
{
	if (eRunningStatus == RUNNING)
	{
		KeyNext(NULL);
	}
	return 0;
}

LRESULT IpodWnd::SystemPrev(DWORD param1, DWORD param2)
{
	if (eRunningStatus == RUNNING)
	{
		KeyPrev(NULL);
	}
	return 0;
}

ListItem* IpodWnd::InsertSong(GXString song)
{
	ListItem *p = pPlayList->CreateItem();
	if (p)
	{
		p->SetFunStatus(FileListStatus);
		GxxLabel *pLabel = (GxxLabel*)p->GetChildFromID(L"song");
		pLabel->SetText(song, 0);
	}
	pPlayList->PushBackItem(p);
	return p;
}

void IpodWnd::InsertSongID(GXString sid)
{
	ListItem *p = pPlayList->CreateItem();
	if (p)
	{
		GxxLabel *pLabel = (GxxLabel*)p->GetChildFromID(L"song");
		pLabel->SetTextID(sid, 0);
	}
	pPlayList->PushBackItem(p);
}

void IpodWnd::FileListStatus(GXBaseControl *pControl, DWORD status, BOOL redraw)
{
	ListItem *p = (ListItem*)pControl;
	if (p)
	{
		if (status == LVIS_SELECTED)
		{
			if (redraw)
			{
				GxxLabel *pLabel = (GxxLabel*)p->GetChildFromID(L"file");
				if (pLabel)
				{
					pLabel->SetStatus(GxxButton::SELECTED, 1);
				}
				pLabel = (GxxLabel*)p->GetChildFromID(L"song");
				if (pLabel)
				{
					pLabel->ScrollEnable(1);
					pLabel->SetStatus(GxxButton::SELECTED, 1);
				}
			}
		}
		if (status == 0)
		{
			GxxLabel *pLabel = (GxxLabel*)p->GetChildFromID(L"file");
			if (pLabel)
			{
				pLabel->SetStatus(GxxButton::NORMAL, 1);
			}
			pLabel = (GxxLabel*)p->GetChildFromID(L"song");
			if (pLabel)
			{
				pLabel->ScrollEnable(0);
				pLabel->SetStatus(GxxButton::NORMAL, 1);
			}
		}
	}
}

void IpodWnd::PreviewStop()
{
	if (bPreviewMode)
	{
		KeyMode(NULL);
	}
}

LRESULT IpodWnd::SysRightKey(DWORD param1, DWORD param2)
{
	if (eRunningStatus == RUNNING)
	{
		if (bPreviewMode)
		{
			KeyMode(NULL);
		}
		else
		{
			ModePreview(NULL);
		}
	}
	return 0;
}

LRESULT IpodWnd::NaviMediaControl(DWORD param1, DWORD param2)
{
	if (eRunningStatus != NOTRUNNING)
	{
		if (param1 == TYPE_IPOD)
		{
			switch(param2)
			{
			case 1:
				{
					KeyPrev(NULL);
					break;
				}
			case 2:
				{
					if (pButtPlay->IsVisible())
					{
						KeyPlay(NULL);
					}
					if (pButtPause->IsVisible())
					{
						KeyPause(NULL);
					}
					break;
				}
			case 3:
				{
					KeyNext(NULL);
					break;
				}
			}
		}
	}
	return 0;
}

void IpodWnd::ClickIpodBar(GXBaseControl *pControl)
{
	pIPodLib->SetPlayTime(pProbarIpod->GetPos());
}