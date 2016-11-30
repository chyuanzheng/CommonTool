#pragma once
#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "RadioActivity.h"
#include "AVSet.h"
#include "VolumeControl.h"
#include "AnimationManage.h"
#include "WheelMsg.h"
#include "GxxLableSet.h"
#include "Hardware.h"
RadioActivity::RadioActivity()
{
	curFMCH = 0;
	curAMCH = 0;
	curFMPage = 0;
	curAMPage = 0;
}

RadioActivity::~RadioActivity()
{
	
}

Activity* RadioActivity::CreateControl()
{
	return new RadioActivity;
}

void RadioActivity::onCreate()
{
	
	setContentView("layout\\RadioPad.xml");
	Activity::onCreate();

	VolumeControl::ApplayForPermission(VolumeModuleId::RADIO, 0, L"radio");

	pLabel_CurrentFreq = (GxxAniLable*)safeFindViewByName("Label_CurrentFreq");
	pLabel_CurrentFreq_invert = (GxxSwText*)safeFindViewByName("Label_CurrentFreq_invert");
	pLabel_uint_invert = (GxxSwText*)safeFindViewByName("Label_Unit_invert");
	pLabel_uint = (GxxSwText*)safeFindViewByName("Label_Unit");

	pLabel_Auto_Memory = (GxxAniLable*)safeFindViewByName("Label_Auto_Memory");
	pLabFreq[0] = (GxxAniLable*)safeFindViewByName("Label_feqbt1");
	pLabFreq[1] = (GxxAniLable*)safeFindViewByName("Label_feqbt2");
	pLabFreq[2] = (GxxAniLable*)safeFindViewByName("Label_feqbt3");

	pLabel_PageUp = (GxxAniLable*)safeFindViewByName("Label_PageUp");
	pLabel_PageDown = (GxxAniLable*)safeFindViewByName("Label_PageDown");
	m_lable_set =  (GxxLableSet* )safeFindViewByName("GxxLableSet_1");

	pLabel_SwitchBand = (GxxAniLable*)safeFindViewByName("Label_SwitchBand");
	pLabel_CurrentBand = (GxxAniLable*)safeFindViewByName("Label_CurrentBand");
	pLabel_CurrentFreqNum = (GxxAniLable*)safeFindViewByName("Label_CurrentFreqNum");

	pLabel_SearchPrev = (GxxAniLable*)safeFindViewByName("Label_SearchPrev");
	pLabel_SearchNext = (GxxAniLable*)safeFindViewByName("Label_SearchNext");

	pLabel_SwitchInfoOrMain = (GxxAniLable*)safeFindViewByName("Label_SwitchInfoOrMain");

	pControlGroup_info = (GxxControlGroup*)safeFindViewByName("ControlGroup_info");
	pControlGroup_main = (GxxControlGroup*)safeFindViewByName("ControlGroup_main");

	pLabelToSetupAudio = (GxxAniLable*)safeFindViewByName("LabelToSetupAudio");

	pInc_Label_Return_Main = (GxxAniLable*)safeFindViewByName("Inc_Into_MainInterface");

	pRadioHardware = new TEF6638Hardware();
	pRadioHardware->Init();


	pRadioHardware->RegisterMsg(RadioSearchHandler, (DWORD)this);


	//��ʼ��Ƶ��
	ReadBandTable(pRadioHardware->GetFMTable(), 0);
	for (int i=0;i<MAXNUM;i++)
	{
		if (FREQ(pRadioHardware->GetFMTable()[i])<FMmin || FREQ(pRadioHardware->GetFMTable()[i])>FMmax)
		{
			pRadioHardware->GetFMTable()[i] = 0;
		}
	}
	ReadBandTable(pRadioHardware->GetAMTable(), true);
	for (int i=0;i<MAXNUM;i++)
	{
		if (FREQ(pRadioHardware->GetAMTable()[i]) < MWmin || FREQ(pRadioHardware->GetAMTable()[i]) > MWmax)
		{
			pRadioHardware->GetAMTable()[i] = 0;
		}
	}

	//��ʼ������
	BAND band = (BAND)ReadCurBand();
	if (band > Band_MW)
	{
		band = Band_FM;
	}
	pRadioHardware->SwitchBand((BAND)band);
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		pLabel_CurrentBand->SetText(_T("FM"), true);
		strUnits = "MHz";

	}
	else
	{
		pLabel_CurrentBand->SetText(_T("AM"), true);
		strUnits = "KHz";

	}

	totalFMPage = TOTAL_FM_PAGE;
	totalAMPage = TOTAL_AM_PAGE;

	curFMFreq = 87500;
	curAMFreq = 531;
	curFMFreq = pRadioHardware->GetFMTable()[0];
	curAMFreq = pRadioHardware->GetAMTable()[0];

	int curPage = 0;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMPage = ReadCurPage();
		curFMCH = ReadCurChannel(RadioHardware::FMMODE);
		if (curFMPage > totalFMPage || curFMPage < 0)
		{
			curFMPage = 0;
			curFMCH = 0;
		}
		curPage = curFMPage;


		curFMFreq = ReadCurFreq();
		pRadioHardware->SetFreq(curFMFreq);

	}
	else
	{
		curAMPage = ReadCurPage();
		curAMCH = ReadCurChannel(RadioHardware::AMMODE);
		if (curAMPage > totalAMPage || curAMPage < 0)
		{
			curAMPage = 0;
			curAMCH = 0;
		}
		curPage = curAMPage;

		curAMFreq = ReadCurFreq();
		pRadioHardware->SetFreq(curAMFreq);

	}

	SetFreqNow(pRadioHardware->GetCurFreq(), true);
	SetPage(curPage);

	//��ʾ��ǰ��Ƶ��ID
	int iFreqNum = sysConfig.sysParam.CurrentFreqNum;
	if(iFreqNum >= 0 && iFreqNum < 50)
	{
		ShowCurrentFreqNum(iFreqNum+1);
	}
	else
	{
		ShowCurrentFreqNum(0);
	}
	


	Notify notify;
	notify.dwParam = this;
	notify.funNotify = NotifyWheel_Msg;
	GXNotify::RegisterNotifyHandler("Wheel_Msg", notify);
	
	
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);
}

LRESULT RadioActivity::NotifyWheel_Msg(DWORD param1, DWORD param2)
{
	//���ڱ�������
	if( Activity::GetActiveActiviy() != (RadioActivity*)this)
	{
		return 0;
	}

	int iMsg = param1;
	switch(iMsg)
	{
	case HardwareBtnMatch::WAVE_BAND_KEY:	//����
		{
			Band();
		}
		break;
	case HardwareBtnMatch::PRE_KEY:	//��һ��
		{
			SearchPrev();
		}
		break;
	case HardwareBtnMatch::NEXT_KEY:	//��һ��
		{
			SearchNext();
		}
		break;
	case HardwareBtnMatch::BACK_KEY:	//����
		{
			AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
		}

	}
	return 0;
}


void RadioActivity::Band()
{
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
	}
	else
	{
		if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
		{
			pRadioHardware->SwitchBand((BAND)RadioHardware::AMMODE);
		}
		else
		{
			pRadioHardware->SwitchBand((BAND)RadioHardware::FMMODE);
		}
		if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
		{
			pRadioHardware->SetFreq(curFMFreq);
			pLabel_CurrentBand->SetText(_T("FM"), true);
			strUnits = L"MHz";
			SetPage(curFMPage);
		}
		else
		{
			pRadioHardware->SetFreq(curAMFreq);
			pLabel_CurrentBand->SetText(_T("AM"), true);
			strUnits = L"KHz";
			SetPage(curAMPage);
		}
		SetFreqNow(pRadioHardware->GetCurFreq(), true);
		WriteCurBand(pRadioHardware->GetBand());
	}
}

void RadioActivity::PageUp()
{

	int *curPage;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMPage--;
		curPage = &curFMPage;
	}
	else
	{
		curAMPage--;
		curPage = &curAMPage;
	}
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		if (*curPage < 0)
		{
			*curPage = totalFMPage - 1;
		}
	}
	else
	{
		if (*curPage < 0)
		{
			*curPage = totalAMPage - 1;
		}
	}
	
	SetPage(*curPage);
	

}

void RadioActivity::PageDown()
{
	int *curPage;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMPage++;
		curPage = &curFMPage;
	}
	else
	{
		curAMPage++;
		curPage = &curAMPage;
	}
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		if (*curPage > totalFMPage - 1)
		{
			*curPage = 0;
		}
	}
	else
	{
		if (*curPage > totalAMPage - 1)
		{
			*curPage = 0;
		}
	}

	SetPage(*curPage);
}

 

BOOL RadioActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONLONG==lParam)
		{
			if ((GxxAniLable *)wParam == pLabel_SearchPrev)	//�����Զ�����
			{
				SearchPrev();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SearchNext)	//�����Զ�����
			{
				SearchNext();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[0])	//����Ƶ�ʵĴ�����
			{
				LongClickFreq(1, pLabFreq[0]);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[1])	//����Ƶ�ʵĴ�����
			{
				LongClickFreq(2, pLabFreq[1]);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[2])	//����Ƶ�ʵĴ�����
			{
				LongClickFreq(3, pLabFreq[2]);
				return TRUE;

			}
			return FALSE;
		}
		if (MES_LBUTTONUP==lParam)
		{
			
			if ((GxxAniLable *)wParam == pInc_Label_Return_Main)	//����������
			{
				AfxPostMessage(CTR_INTO_MAIN_INTERFACE, 0, 0);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_Auto_Memory)	//�Զ�����
			{
				AutoSearch();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_PageUp)	//���Ϸ�ҳ
			{
				PageUp();
				m_lable_set->StartAction(false);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_PageDown)	//���·�ҳ
			{
				PageDown();
				m_lable_set->StartAction(true);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SwitchBand)	//�л�band
			{
				Band();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[0])	//���Ƶ�ʵĴ�����
			{
				ClickFreq(1);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[1])	//���Ƶ�ʵĴ�����
			{
				ClickFreq(2);
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabFreq[2])	//���Ƶ�ʵĴ�����
			{
				ClickFreq(3);
				return TRUE;

			}
			if ((GxxAniLable *)wParam == pLabel_SearchPrev)	//��̨
			{
				UpStep();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SearchNext)	//��̨
			{
				DownStep();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabel_SwitchInfoOrMain)
			{
				SwitchInfoOrMain();
				return TRUE;
			}
			if ((GxxAniLable *)wParam == pLabelToSetupAudio)	//��ת�����ý���
			{
				Activity::startActivity(this,"SetupActivity","2_sound_setup");
				return true;
			}
		}
		return FALSE;
	default:
		return FALSE;
	}
}

void RadioActivity::onStop()
{
	// �ر����������ߵ�Դ
	Hardware::RadioAntPower(0);
}

void  RadioActivity::onResume()
{

	// �л�������radio
	AVSET::ToRadio();

	// �����������ߵ�Դ 
	Hardware::RadioAntPower(1);

	//�趨����
	VolumeControl::ApplyForVolumeControl(VolumeModuleId::RADIO);

	
	
}


void RadioActivity::onPause()
{
	
}

void RadioActivity::SearchNext()
{
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
		//pLabScanInfo->SetTextID(_T(""), true);
	}
	else
	{
		pRadioHardware->StartManualSearch(1);
	}
}

void RadioActivity::SearchPrev()
{

	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
		//pLabScanInfo->SetTextID(_T(""), true);
	}
	else
	{
		pRadioHardware->StartManualSearch(0);
	}
}

//�л����������Ϣ����
void RadioActivity::SwitchInfoOrMain()
{
	static bool bInMainInterface = true;
	if(bInMainInterface)
	{
		pControlGroup_info->setDraw(TRUE);
		pControlGroup_main->setDraw(FALSE);
		
		Activity::overridePendingTransition(pControlGroup_main,pControlGroup_info,Activity::s_hAniRotateY);
	}
	else
	{
		
		pControlGroup_info->setDraw(FALSE);
		pControlGroup_main->setDraw(TRUE);
		
		Activity::overridePendingTransition(pControlGroup_info,pControlGroup_main,Activity::s_hAniRotateY);
		
	}
	bInMainInterface = !bInMainInterface;	//ȡ��
	
}

void RadioActivity::DownStep()
{
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
		return;
	}
	
	pRadioHardware->FreqAdd();
	SetFreqNow(pRadioHardware->GetCurFreq(), true);
	int preset = pRadioHardware->GetFreqPreset(pRadioHardware->GetCurFreq());

	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		if (preset != -1)
		{
			curFMCH = preset;
			WriteCurChannel(curFMCH, pRadioHardware->GetFMorAM());
			curFMPage = curFMCH/PER_PAGE_NUM;

			SetPage(curFMPage);
			//��ʾ��ǰ��Ƶ��ID��
			ShowCurrentFreqNum(preset+1);
		}
		//��ť�趨Ϊѡ��״̬
		SelectFreq(preset);
		
	}
	else
	{
		if (preset != -1)
		{
			curAMCH = preset;
			WriteCurChannel(curAMCH, pRadioHardware->GetFMorAM());
			curAMPage = curAMCH/PER_PAGE_NUM;

			SetPage(curAMPage);
			//��ʾ��ǰ��Ƶ��ID��
			ShowCurrentFreqNum(preset+1);

			
		}
		//��ť�趨Ϊѡ��״̬
		SelectFreq(preset);
	}

}

void RadioActivity::UpStep()
{
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
		return;
	}

	pRadioHardware->FreqSub();
	SetFreqNow(pRadioHardware->GetCurFreq(), true);
	int preset = pRadioHardware->GetFreqPreset(pRadioHardware->GetCurFreq());
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		if (preset != -1)
		{
			curFMCH = preset;
			WriteCurChannel(curFMCH, pRadioHardware->GetFMorAM());
			curFMPage = curFMCH/PER_PAGE_NUM;

			SetPage(curFMPage);
			
		}
		//��ʾ��ǰ��Ƶ��ID��
		ShowCurrentFreqNum(preset+1);

		//��ť�趨Ϊѡ��״̬
		SelectFreq(preset);
		
	}
	else
	{
		if (preset != -1)
		{
			curAMCH = preset;
			WriteCurChannel(curAMCH, pRadioHardware->GetFMorAM());
			curAMPage = curAMCH/PER_PAGE_NUM;

			SetPage(curAMPage);

			
			
		}
		//��ʾ��ǰ��Ƶ��ID��
		ShowCurrentFreqNum(preset+1);

		//��ť�趨Ϊѡ��״̬
		SelectFreq(preset);
		
	}
}

DWORD RadioActivity::RadioSearchHandler(CHardware *pControl, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_RADIOSEARCHEND)
	{
		if (wParam == 1)
		{
			// ���Զ���������
			pRadioHardware->SetFreq(pRadioHardware->GetCurFreq());
			SetFreqNow(pRadioHardware->GetCurFreq(), true);
			int preset = pRadioHardware->GetFreqPreset(pRadioHardware->GetCurFreq());
			if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
			{
				if (preset != -1)
				{
					curFMCH = preset;
					WriteCurChannel(curFMCH, pRadioHardware->GetFMorAM());
					curFMPage = curFMCH/PER_PAGE_NUM;
					ShowCurrentFreqNum(curFMCH+1);
				}
				SetPage(curFMPage);
				
			}
			else
			{
				if (preset != -1)
				{
					curAMCH = preset;
					WriteCurChannel(curAMCH, pRadioHardware->GetFMorAM());
					curAMPage = curAMCH/PER_PAGE_NUM;
					ShowCurrentFreqNum(curAMCH+1);
				}
				SetPage(curAMPage);
				
			}
		}
		else
		{
			// ȫ�Զ���������
			if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
			{
				curFMPage = 0;
				totalFMPage = TOTAL_FM_PAGE;
				SetPage(curFMPage);
			}
			else
			{
				curAMPage = 0;
				totalAMPage = TOTAL_AM_PAGE;
				SetPage(curAMPage);
			}
		}
		return 0;
	}
	if (lParam == -1)
	{
		// ������
		SetFreqNow(wParam, true);
	}
	else if (lParam == -2)
	{
		// ��������
		SetFreqNow(wParam, true);
	}
	else
	{
		// ������,�ѵ�̨
		GxxString strFreq = pRadioHardware->FormatFreq(wParam);
		strFreq += " ";
		strFreq += strUnits;
		

		pLabFreq[lParam%PER_PAGE_NUM]->SetText(strFreq.GetData(), true);

	}
	return 0;
}

void RadioActivity::AutoSearch()
{
	//STOPSCAN;
	/*if (inputMode)
	{
		ReturnFormInput();
		return ;
	}*/
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
//		pLabScanInfo->SetTextID(_T(""), true);
	}
	else
	{
		pRadioHardware->StartSearch();
//		pLabScanInfo->SetTextID(_T("ID_SEARCHING"), true);
	}
}

void RadioActivity::SetFreqNow(int freq, bool bredraw)
{
	
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMFreq = freq;
		WriteCurFreq(curFMFreq);
	}
	else
	{
		curAMFreq = freq;
		WriteCurFreq(curAMFreq);
	}
	
	if(freq == 0)				//��̨ʱ
	{
		pLabel_CurrentFreq->SetText(L"---", true);
		return;
	}

	CStdString str = pRadioHardware->FormatFreq(freq);

	pLabel_CurrentFreq->SetText(str.GetData(), bredraw);
	pLabel_CurrentFreq_invert->setText(str.GetData());
	pLabel_uint_invert->setText(strUnits.GetData());
	pLabel_uint->setText(strUnits.GetData());

	AfxInvalidateRect(NULL);
}

void RadioActivity::SetPage(int page)
{
	if (page<0 || page>10)
	{
		return;
	}
	for (int i=0;i<PER_PAGE_NUM;i++)
	{
		if(pRadioHardware->GetCurFreqTable()[i+page*PER_PAGE_NUM] == 0)				//��̨ʱ
		{
			pLabFreq[i]->SetText(L"---", true);
		}
		else
		{
			GxxString strFreq = pRadioHardware->FormatFreq(pRadioHardware->GetCurFreqTable()[i+page*PER_PAGE_NUM]);
			strFreq += " ";
			strFreq += strUnits;
			pLabFreq[i]->SetText(strFreq.GetData(), true);
		}
		
	}

	//��ť�趨Ϊѡ��״̬
	SelectFreq(-1);
	for (int i=0;i<PER_PAGE_NUM;i++)
	{
		if (FREQ(pRadioHardware->GetCurFreqTable()[i+page*PER_PAGE_NUM]) == FREQ(pRadioHardware->GetCurFreq()))
		{
			SelectFreq(i+page*PER_PAGE_NUM);
			break;
		}

	}

	WriteCurPage(page);
}

void RadioActivity::SelectFreq(int iNum)	//��ť�趨Ϊѡ��״̬
{
	pLabFreq[0]->SetSelect(false);
	pLabFreq[1]->SetSelect(false);
	pLabFreq[2]->SetSelect(false);

	int page = iNum/PER_PAGE_NUM;
	
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		if(page == curFMPage)
		{
			switch(iNum%PER_PAGE_NUM+1)
			{
			case 1:
				{
					pLabFreq[0]->SetSelect(true);
				}
				break;
			case 2:
				{
					pLabFreq[1]->SetSelect(true);
				}
				break;
			case 3:
				{
					pLabFreq[2]->SetSelect(true);
				}
				break;
			}
		}
	}
	else
	{
		if(page == curAMPage)
		{
			switch(iNum%PER_PAGE_NUM+1)
			{
			case 1:
				{
					pLabFreq[0]->SetSelect(true);
				}
				break;
			case 2:
				{
					pLabFreq[1]->SetSelect(true);
				}
				break;
			case 3:
				{
					pLabFreq[2]->SetSelect(true);
				}
				break;
			}
		}	
	} 

}

void RadioActivity::LongClickFreq(int iNum, GxxAniLable* pControl)		//����Ƶ�ʰ�ť
{	
	int curPage;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curPage = curFMPage;
	}
	else
	{
		curPage = curAMPage;
	}

	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMCH = curPage*PER_PAGE_NUM+iNum-1;
		WriteCurChannel(curFMCH, pRadioHardware->GetFMorAM());

		//��ť�趨Ϊѡ��״̬
		SelectFreq(curFMCH);
	}
	else
	{
		curAMCH = curPage*PER_PAGE_NUM+iNum-1;
		WriteCurChannel(curAMCH, pRadioHardware->GetFMorAM());

		//��ť�趨Ϊѡ��״̬
		SelectFreq(curAMCH);
	}
	pRadioHardware->GetCurFreqTable()[curPage*PER_PAGE_NUM+iNum-1] = pRadioHardware->GetCurFreq();
	
	int freq;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		UpdateBandFreq(pRadioHardware->GetCurFreq(), curFMCH, pRadioHardware->GetFMorAM());
		freq = curFMFreq;
	}
	else
	{
		UpdateBandFreq(pRadioHardware->GetCurFreq(), curAMCH, pRadioHardware->GetFMorAM());
		freq = curAMFreq;
	}


	//��ʾ��ǰ��Ƶ��ID��
	ShowCurrentFreqNum(curPage*PER_PAGE_NUM + iNum);
	
	//��ť����ʾ��ǰƵ��
	GxxString strFreq = pRadioHardware->FormatFreq(freq);
	strFreq += " ";
	strFreq += strUnits;
	pControl->SetText(strFreq.GetData(), true);

}

void RadioActivity::ClickFreq(int iNum)
{
	if (pRadioHardware->IsSearch())
	{
		pRadioHardware->StopSearch();
	}
	
	int curPage;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curPage = curFMPage;
	}
	else
	{
		curPage = curAMPage;
	}
	if (pRadioHardware->GetCurFreqTable()[curPage*PER_PAGE_NUM + iNum -1] == 0)
	{
		return;
	}

	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMCH = curPage*PER_PAGE_NUM+iNum-1;
		WriteCurChannel(curFMCH, pRadioHardware->GetFMorAM());

		//��ť�趨Ϊѡ��״̬
		SelectFreq(curFMCH);
	}
	else
	{
		curAMCH = curPage*PER_PAGE_NUM+iNum-1;
		WriteCurChannel(curAMCH, pRadioHardware->GetFMorAM());

		//��ť�趨Ϊѡ��״̬
		SelectFreq(curAMCH);
	} 
	//�趨��ǰ��Ƶ��
	pRadioHardware->SetFreq(pRadioHardware->GetCurFreqTable()[curPage*PER_PAGE_NUM + iNum -1]);
	//��ʾ��ǰ��Ƶ��
	SetFreqNow(pRadioHardware->GetCurFreqTable()[curPage*PER_PAGE_NUM + iNum -1], true);

	
	//��ʾ��ǰ��Ƶ��ID��
	ShowCurrentFreqNum(curPage*PER_PAGE_NUM + iNum);
}

//��ʾ��ǰ��Ƶ�ʵ�ID��
void RadioActivity::ShowCurrentFreqNum(int iNum)
{

	if(iNum == 0)
	{
		pLabel_CurrentFreqNum->SetText(L"", true);
		return;
	}

	//��ʾƵ��ID��
	GxxString strNum;
	
	strNum.Format(L"%d", iNum);

	if(pLabel_CurrentFreqNum)
	{
		pLabel_CurrentFreqNum->SetText(strNum.GetData(), true);
	}

	sysConfig.sysParam.CurrentFreqNum = iNum-1;
	sysConfig.WriteConfig(&sysConfig.sysParam.CurrentFreqNum);
	
}

LRESULT RadioActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	// ����Ĭ��FMƵ��
	UINT defaultFMTable[60] = {87500, 90000, 98000, 106000, 108000};
	WriteBandTable(defaultFMTable, 0);
	// ����Ĭ��AMƵ��
	UINT defaultAMTable[60] = {522, 603, 999, 1404, 1602};
	WriteBandTable(defaultAMTable, 1);
	WriteCurFreq(87500);
	WriteCurPage(0);
	
	Sleep(100);
	//��ʼ��Ƶ��
	ReadBandTable(pRadioHardware->GetFMTable(), 0);
	for (int i=0;i<MAXNUM;i++)
	{
		if (FREQ(pRadioHardware->GetFMTable()[i])<FMmin || FREQ(pRadioHardware->GetFMTable()[i])>FMmax)
		{
			pRadioHardware->GetFMTable()[i] = 0;
		}
	}
	ReadBandTable(pRadioHardware->GetAMTable(), true);
	for (int i=0;i<MAXNUM;i++)
	{
		if (FREQ(pRadioHardware->GetAMTable()[i]) < MWmin || FREQ(pRadioHardware->GetAMTable()[i]) > MWmax)
		{
			pRadioHardware->GetAMTable()[i] = 0;
		}
	}

	//��ʼ������
	BAND band = (BAND)ReadCurBand();
	if (band > Band_MW)
	{
		band = Band_FM;
	}
	pRadioHardware->SwitchBand((BAND)band);
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		pLabel_CurrentBand->SetText(_T("FM"), true);
		strUnits = "MHz";

	}
	else
	{
		pLabel_CurrentBand->SetText(_T("AM"), true);
		strUnits = "KHz";

	}

	totalFMPage = TOTAL_FM_PAGE;
	totalAMPage = TOTAL_AM_PAGE;

	curFMFreq = 87500;
	curAMFreq = 531;
	curFMFreq = pRadioHardware->GetFMTable()[0];
	curAMFreq = pRadioHardware->GetAMTable()[0];

	int curPage = 0;
	if (pRadioHardware->GetFMorAM() == RadioHardware::FMMODE)
	{
		curFMPage = ReadCurPage();
		curFMCH = ReadCurChannel(RadioHardware::FMMODE);
		if (curFMPage > totalFMPage || curFMPage < 0)
		{
			curFMPage = 0;
			curFMCH = 0;
		}
		curPage = curFMPage;


		curFMFreq = ReadCurFreq();
		pRadioHardware->SetFreq(curFMFreq);

	}
	else
	{
		curAMPage = ReadCurPage();
		curAMCH = ReadCurChannel(RadioHardware::AMMODE);
		if (curAMPage > totalAMPage || curAMPage < 0)
		{
			curAMPage = 0;
			curAMCH = 0;
		}
		curPage = curAMPage;

		curAMFreq = ReadCurFreq();
		pRadioHardware->SetFreq(curAMFreq);

	}

	SetFreqNow(pRadioHardware->GetCurFreq(), true);
	SetPage(curPage);

	//�ָ�Ƶ�ʵ�ID��
	ShowCurrentFreqNum(1);

	return 0;
}

static RegisterHelp help("RadioActivity", RadioActivity::CreateControl);