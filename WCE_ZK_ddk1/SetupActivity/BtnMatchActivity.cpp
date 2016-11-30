#include "stdAfx.h"
#include "ControlHelp.h"
#include "MesDef.h"
#include "BtnMatchActivity.h"
#include "ControlHelp.h"
#include "GxxBtnMatchListGroup.h"
#include "GxxAniLable.h"
#include "LangStringManager.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "Audio/Audio.h"
#include "MesDef.h"
#include "WMMsg.h"
#include "Hardware.h"
#include "GxxSetupListLine.h"
#include "MsgHandle.h"
#include "WheelMsg.h"
const string cs_switch = "switch_set";
const string cs_back = "back_set";
const string cs_wave_band = "wave_band_set";

const string cs_mode = "mode_set";
const string cs_answer = "answer_set";
const string cs_drop = "drop_set";

const string cs_mute = "mute_set";
const string cs_previous = "previous_set";
const string cs_next = "next_set";

const string cs_vol_add = "vol_add_set";
const string cs_vol_dec = "vol_dec_set";
const string cs_play = "play_set";
const int N_SAME = 6;
static RegisterHelp help("BtnMatchActivity", BtnMatchActivity::CreateControl);

Activity* BtnMatchActivity::CreateControl()
{
	return new BtnMatchActivity;
}

BtnMatchActivity::BtnMatchActivity()
{
	Notify notify;
	notify.dwParam = this;
	notify.funNotify = RestoreDefault;
	GXNotify::RegisterNotifyHandler("restore_factory_set", notify);
}



BtnMatchActivity::~BtnMatchActivity()
{

}

//恢复出厂设置
LRESULT BtnMatchActivity::RestoreDefault(DWORD param1, DWORD param2)
{
	m_codeMsg.clear();
	m_curCodeMsg.clear();
	ResetConfig(sysConfig.sysParam.curCodeSwitch);
	ResetConfig(sysConfig.sysParam.curCodeBack);
	ResetConfig(sysConfig.sysParam.curCodeWaveBand);

	ResetConfig(sysConfig.sysParam.curCodeMode);
	ResetConfig(sysConfig.sysParam.curCodeAnswer);
	ResetConfig(sysConfig.sysParam.curCodeDrop);

	ResetConfig(sysConfig.sysParam.curCodeMute);
	ResetConfig(sysConfig.sysParam.curCodePrevious);
	ResetConfig(sysConfig.sysParam.curCodeNext);

	ResetConfig(sysConfig.sysParam.curCodeVolAdd);
	ResetConfig(sysConfig.sysParam.curCodeVolDec);
	ResetConfig(sysConfig.sysParam.curCodeVolPaly);
	return 0;
}

void BtnMatchActivity::ResetConfig( BYTE & byte )
{
	byte = 0;
	sysConfig.WriteConfig(&byte);
}

void BtnMatchActivity::onCreate()
{
	m_IsInMatch = false;
	m_nCurCode = -1;

	Activity::onCreate();
	if (!Activity::s_bluetooth_exist)
	{
		setContentView("layout\\BtnMatchPad_no_bluetooth.xml");
	}
	else
	{
		setContentView("layout\\BtnMatchPad.xml");
	}
	

	m_btx = findViewByName("x_btn");
	ASSERT(m_btx!=NULL);

	m_matchGroup = (GxxBtnMatchListGroup *)findViewByName("btn_match_group");
	ASSERT(m_matchGroup!=NULL);

	
	SetMsgHandler(WM_MCUINT, MCUEventHandler, (DWORD)this, this);

	m_okLable = (GxxAniLable *)findViewByName("set_ok");
	ASSERT(m_okLable!=NULL);

	LoadMsgFromRom();
}

//从 EEROM中读取消息号翻译。
void BtnMatchActivity::LoadMsgFromRom()
{
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeSwitch, HardwareBtnMatch::POWER_KEY );

	InsertCodeMsg( (int)sysConfig.sysParam.curCodeBack, HardwareBtnMatch::BACK_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeWaveBand,HardwareBtnMatch::WAVE_BAND_KEY );

	InsertCodeMsg( (int)sysConfig.sysParam.curCodeMode,HardwareBtnMatch::MODE_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeAnswer,HardwareBtnMatch::ANSWER_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeDrop,HardwareBtnMatch::DROP_KEY );

	InsertCodeMsg( (int)sysConfig.sysParam.curCodeMute,HardwareBtnMatch::MUTE_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodePrevious,HardwareBtnMatch::PRE_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeNext,HardwareBtnMatch::NEXT_KEY );

	InsertCodeMsg( (int)sysConfig.sysParam.curCodeVolAdd,HardwareBtnMatch::VOL_ADD_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeVolDec,HardwareBtnMatch::VOL_DEC_KEY );
	InsertCodeMsg( (int)sysConfig.sysParam.curCodeVolPaly,HardwareBtnMatch::PLAY_KEY );
	//m_codeMsg.insert(make_pair(code,KEY_VOLU));

	//下面要完成Msg对接显示text

	//InsertMsgLine(cs_switch,HardwareBtnMatch::POWER_KEY); //开关暂时不做了
	InsertMsgLine(cs_back,HardwareBtnMatch::BACK_KEY);
	InsertMsgLine(cs_wave_band,HardwareBtnMatch::WAVE_BAND_KEY);

	InsertMsgLine(cs_mode,HardwareBtnMatch::MODE_KEY);
	InsertMsgLine(cs_answer,HardwareBtnMatch::ANSWER_KEY);
	InsertMsgLine(cs_drop,HardwareBtnMatch::DROP_KEY);

	InsertMsgLine(cs_mute,HardwareBtnMatch::MUTE_KEY);
	InsertMsgLine(cs_previous,HardwareBtnMatch::PRE_KEY);
	InsertMsgLine(cs_next,HardwareBtnMatch::NEXT_KEY);

	InsertMsgLine(cs_vol_add,HardwareBtnMatch::VOL_ADD_KEY);
	InsertMsgLine(cs_vol_dec,HardwareBtnMatch::VOL_DEC_KEY);
	InsertMsgLine(cs_play,HardwareBtnMatch::PLAY_KEY);

}
void BtnMatchActivity::InsertMsgLine( const string & lineName, int nMsg )
{
	LINE_TEXT lt;

	lt.txt_line = (GxxSetupListLine *)findViewByName(lineName.c_str());
	if (lt.txt_line)
	{
		lt.txt_show = (GxxSwText *) lt.txt_line->safeFindViewByName("txt_match");
		m_MsgLine.insert(make_pair(nMsg, lt));
	}
}

void BtnMatchActivity::InsertCodeMsg( int code, int msg )
{
	if (code>0)
	{
		m_codeMsg.insert( make_pair(code,msg) );
	}
}


void BtnMatchActivity::RenewText()
{
	for (M_MSG_LINE_TXT::iterator pos = m_MsgLine.begin(); pos != m_MsgLine.end(); ++pos )
	{
		pos->second.txt_show->setText("-1");
	}

	char text_v[16];
	//_itoa_s(m_nCurVolume,text_v,sizeof(text_v),10 ); 
	
	for (M_CODE_MSG::iterator pos_c = m_curCodeMsg.begin(); pos_c != m_curCodeMsg.end(); ++pos_c )
	{
		M_MSG_LINE_TXT::iterator pos_line = m_MsgLine.find(pos_c->second);
		ASSERT( pos_line != m_MsgLine.end() );
		int code = pos_c->first;
		sprintf(text_v,"%d",code);
		pos_line->second.txt_show->setText(text_v);
	}

}

void BtnMatchActivity::onResume()
{
	m_matchGroup->SetSelLine(0,true);//选中第0个
	m_curCodeMsg = m_codeMsg;
	RenewText();
}

void BtnMatchActivity::onPause()
{
	m_IsInMatch = false;
}


BOOL BtnMatchActivity::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_SET_BTN_MATCH:
		SetMatchInfo( (GxxSetupListLine *)(wParam) );
		m_nLine = (int)lParam;
		return TRUE;

	case	CTR_LIST_BACK_ACTIVITY://back_btn
		if (!finish())
		{
			startActivity(NULL,"MainPad");
		}
		return TRUE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				RetToFucActivity();
				return TRUE;
			}
			else if ((GxxView *)wParam == m_okLable)
			{
				SaveMatch();
				if (!finish())
				{
					startActivity(NULL,"MainPad");
				}
				return TRUE;
			}
		}
		return FALSE;

	default:
		return FALSE;
	}
	return FALSE;
}

void BtnMatchActivity::SetMatchInfo( GxxSetupListLine * line )
{
	m_IsInMatch = true;
	ASSERT(line != NULL);

	m_nCurMsg = 0;
	for (M_MSG_LINE_TXT::iterator pos = m_MsgLine.begin(); pos != m_MsgLine.end(); ++pos )
	{
		if (pos->second.txt_line == line)
		{
			m_nCurMsg = pos->first;
			break;
		}
	}
	ASSERT(m_nCurMsg);
}

//保存方控学习的信息
void BtnMatchActivity::SaveMatch()
{
	m_codeMsg = m_curCodeMsg;

	SaveMsg(sysConfig.sysParam.curCodeSwitch,HardwareBtnMatch::POWER_KEY );
	SaveMsg(sysConfig.sysParam.curCodeBack,HardwareBtnMatch::BACK_KEY );
	SaveMsg(sysConfig.sysParam.curCodeWaveBand,HardwareBtnMatch::WAVE_BAND_KEY );

	SaveMsg(sysConfig.sysParam.curCodeMode, HardwareBtnMatch::MODE_KEY );
	SaveMsg(sysConfig.sysParam.curCodeAnswer,HardwareBtnMatch::ANSWER_KEY );
	SaveMsg(sysConfig.sysParam.curCodeDrop,HardwareBtnMatch::DROP_KEY);

	SaveMsg(sysConfig.sysParam.curCodeMute,HardwareBtnMatch::MUTE_KEY );
	SaveMsg(sysConfig.sysParam.curCodePrevious,HardwareBtnMatch::PRE_KEY );
	SaveMsg(sysConfig.sysParam.curCodeNext,HardwareBtnMatch::NEXT_KEY );

	SaveMsg(sysConfig.sysParam.curCodeVolAdd,HardwareBtnMatch::VOL_ADD_KEY);
	SaveMsg(sysConfig.sysParam.curCodeVolDec,HardwareBtnMatch::VOL_DEC_KEY);
	SaveMsg(sysConfig.sysParam.curCodeVolPaly,HardwareBtnMatch::PLAY_KEY );



}

void BtnMatchActivity::SaveMsg( BYTE &ebyte, int nMsg )
{
	for (M_CODE_MSG::iterator pos = m_codeMsg.begin(); pos != m_codeMsg.end(); ++pos)
	{
		if (pos->second == nMsg)
		{
			ebyte = pos->first;
			sysConfig.WriteConfig(&ebyte);
			return;
		}
	}
}



DWORD BtnMatchActivity::MCUEventHandler(void *pControl, DWORD dwParam, UINT& msg, WPARAM wParam, LPARAM lParam)
{
	BtnMatchActivity *pMainWnd = (BtnMatchActivity *)dwParam;
	BYTE ircode = 0;	// 为了让程序能够主动获取车状态信息,而非仅依靠单片机中断 010427
	if (wParam != 0)
	{
		ircode = wParam;
	}
	else
	{
		ircode = Hardware::ReadHardwareCode();
	}


	BtnMatchActivity *pAct = (BtnMatchActivity *)dwParam;
	// 公用命令
	switch(ircode)
	{
	case MEM_WHEEL_KEY:	//
		pAct->OnWheelMsg();
		break;
	case MEM_IR_ARM:
		pAct->OnIrMsg();

	default:
		break;
	}
	return 0;
}

void BtnMatchActivity::OnWheelMsg()
{
	int code =Hardware::ReadWheelKey();
	if (m_IsInMatch)
	{
		if (code>250)//按键弹起,开始下一个学习
		{
			GXNotify::SendNotify("Wheel_Msg_Up", 0, 0);
			if (m_nCurCode==-1)
			{
				return;
			}
			m_nLine++;
			if (!m_matchGroup->SetSelLine(m_nLine,true))
			{
				bool b=m_matchGroup->SetSelLine(0,true);
				ASSERT(b);
			}
			m_nCurCode = -1;
			return;
		}
		//去掉相同的消息
		for (M_CODE_MSG::iterator pos = m_curCodeMsg.begin(); pos != m_curCodeMsg.end(); ++pos)
		{
			if (pos->second == m_nCurMsg)
			{
				m_curCodeMsg.erase(pos);
				break;
			}
		}
		m_nCurCode = code;
		m_curCodeMsg[code] = m_nCurMsg;

		////去掉相近的code对应的消息
		EraseLikeCode(code);

		RenewText();
		AfxInvalidateRect(NULL);
	}
	else
	{
		
		if (code>250)//方控用 250 表示弹起
		{
			GXNotify::SendNotify("Wheel_Msg_Up", 0, 0);
			return;
		}
		M_CODE_MSG::iterator pos_3;
		for (pos_3 = m_codeMsg.begin(); pos_3 != m_codeMsg.end(); ++pos_3)
		{
			if (pos_3->first>(code-N_SAME) && pos_3->first< (code+N_SAME) )
			{
				break;
			}
		}

		if (pos_3 != m_codeMsg.end())
		{
			GXNotify::SendNotify("Wheel_Msg", pos_3->second, 0);
			if (pos_3->second == HardwareBtnMatch::BACK_KEY)
			{
				AfxPostMessage(CTR_BTN_MATCH_BACK,0,0);
			}
			else if (pos_3->second == HardwareBtnMatch::MUTE_KEY)
			{
				AfxPostMessage(CTR_SWITCH_MUTE,0,0);
			}
		}
	}
}

void BtnMatchActivity::EraseLikeCode( int code )
{
	for (int i =code-N_SAME+1; i< code+N_SAME; i++)
	{
		if (i != code)
		{
			m_curCodeMsg.erase(i);
		}
	}
	
}

//16	MUTE
//15	VOL_DOWN
//14	VOL_UP
//13	REW
//12	FF
//0a	MODE
//56      接听
//5C      挂断
void BtnMatchActivity::OnIrMsg()
{
	static DWORD timeTick = 0;
	static int    code = 0;
	BYTE ircode = Hardware::ReadIRCode();
	switch(ircode)
	{
		case 0x16://16	MUTE
			timeTick = 0;
			code = HardwareBtnMatch::MUTE_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::MUTE_KEY , 1);//1表示 IR的信号
			AfxPostMessage(CTR_SWITCH_MUTE,0,0);
			break;
		case 0x15://15	VOL_DOWN
			timeTick = ::GetTickCount();
			code = HardwareBtnMatch::VOL_DEC_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::VOL_DEC_KEY , 1);
			break;
		case 0x14://14	VOL_UP
			timeTick = ::GetTickCount();
			code = HardwareBtnMatch::VOL_ADD_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::VOL_ADD_KEY , 1);
			break;
		case 0x13://13	REW 上一曲
			timeTick = 0;
			code = HardwareBtnMatch::PRE_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::PRE_KEY , 1);
			break;
		case 0x12://12	FF 下一曲
			timeTick = 0;
			code = HardwareBtnMatch::NEXT_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::NEXT_KEY , 1);
			break;
		case 0x0a://0a	MODE
			timeTick = 0;
			code = HardwareBtnMatch::MODE_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::MODE_KEY , 1);
			break;
		case 0x56://接听
			timeTick = 0;
			code = HardwareBtnMatch::ANSWER_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::ANSWER_KEY , 1);
			break;
		case 0x5c://挂断
			timeTick = 0;
			code = HardwareBtnMatch::DROP_KEY;
			GXNotify::SendNotify("Wheel_Msg", HardwareBtnMatch::DROP_KEY , 1);
			break;
		case 0xFF:
			{
				DWORD nowTick = ::GetTickCount();
				if ( nowTick-timeTick < 300 && (0!=ircode) )
				{
					timeTick = nowTick;
					GXNotify::SendNotify("Wheel_Msg", ircode , 1);//连续码
					if (HardwareBtnMatch::MUTE_KEY == ircode)
					{
						AfxPostMessage(CTR_SWITCH_MUTE,0,0);
					}
				}
			}
			break;
		default:
			break;
	}
}












