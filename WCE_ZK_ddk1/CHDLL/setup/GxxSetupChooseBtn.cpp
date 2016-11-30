#include "StdAfx.h"
#include "GxxSetupChooseBtn.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxAniLable.h"
#include "ResStringManager.h"
#include "SetupFuction.h"

GxxSetupChooseBtn::GxxSetupChooseBtn( int x,int y, const string &strName )
{
	
	m_btnleft = new GxxAniButton;
	m_btnright = new GxxAniButton;
	m_midlable = new GxxAniLable;
	AddCtrl(m_btnleft);
	AddCtrl(m_btnright);
	AddCtrl(m_midlable);

	const char *strAni = ResStringManager::GetInstance()->getString("IconDirectAni");
	const char *strDisable = ResStringManager::GetInstance()->getString("IconDirectDisable");
	const char *strPicup = ResStringManager::GetInstance()->getString("IconDirectPicUp");//底图
	const char *strRight = ResStringManager::GetInstance()->getString("IconDirectRight");//2
	const char *strLeft = ResStringManager::GetInstance()->getString("IconDirectLeft");//2
	const char *strMid = ResStringManager::GetInstance()->getString("IconLableMid");



	m_btnright->SetLayout(x,y,strPicup,strRight,strAni,strDisable);
	RECT rc = m_btnright->getCtrRect();
	x -= rc.right - rc.left + 4;
	y -= 3;

	m_midlable->SetLayout(x,y,strMid);
	rc = m_midlable->getCtrRect();
	x -= rc.right - rc.left;
	m_midlable->setEnable(false);

	y += 3;
	m_btnleft->SetLayout(x,y,strPicup,strLeft,strAni,strDisable);


	m_minCursor =-0x7FFFFFFF;
	m_maxCursor = 0x7FFFFFFF;
	
	m_strName = strName;
}

GxxSetupChooseBtn::~GxxSetupChooseBtn()
{
	delete m_midlable;
	delete m_btnright;
	delete m_btnleft;
}

BOOL GxxSetupChooseBtn::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	static bool  sbtn_down =false;
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if ( InMyArea(m_btnright->getCtrRect(),LOWORD(lParam ), HIWORD(lParam)) || InMyArea(m_btnleft->getCtrRect(),LOWORD(lParam ), HIWORD(lParam)) )
		{
			sbtn_down = true;
			return TRUE;
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if (sbtn_down)
		{
			return TRUE;
		}
		return FALSE;
	case WM_LBUTTONUP:
		if (sbtn_down)
		{
			sbtn_down = false;
			return TRUE;
		}
		
		return FALSE;
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if (m_btnleft == (GxxAniButton *)wParam)
			{
				m_curCursor--;
				WriteSetData();
				return TRUE;
			}
			if (m_btnright == (GxxAniButton *)wParam)
			{
				m_curCursor++;
				WriteSetData();

				return TRUE;
			}
		}
		return FALSE;
	case CTR_SETUP_READ_CURSOR:
		SetupFuction::GetInstance()->ReadMinMax(m_strName,m_minCursor,m_maxCursor);
		return FALSE;
	case CTR_SETUP_READ_LIST:
		ReadSetData( (const char *)wParam);
		return FALSE;//还有其他控件需要更新
	default:
		return FALSE;
	}
	return FALSE;
}

void GxxSetupChooseBtn::ReadSetData( const char * pStr )
{
	if (pStr!=NULL&&m_strName!=pStr)
	{
		return;
	}
	string text;
	bool b=SetupFuction::GetInstance()->ReadSetup(m_strName,m_curCursor,text);
	if (!b){
		DisableAll();
		getParentView()->TranslateMessage(MES_CHOOSE_BTN_DISABLE,0,0);
		return;
	}

	int ns = SetupFuction::GetInstance()->GetStatus(m_strName);
	if (ns == SETUP_FUN_WAITING)
	{
		DisableWaiting();
		return;
	}

	CheckEnable();

	string::size_type idx = text.find("_31_line");//"_31"表示ID
	if (string::npos == idx)
	{
		m_midlable->SetText(text.c_str());
	}
	else
	{
		m_midlable->GetTextView()->setTextFromId(text);
	}

	//m_midlable->SetText(text.c_str());
}

void GxxSetupChooseBtn::WriteSetData()
{
	string text;
	bool b=SetupFuction::GetInstance()->WriteSetup(m_strName,m_curCursor,text);
	if (!b)
	{
		DisableAll();
		getParentView()->TranslateMessage(MES_CHOOSE_BTN_DISABLE,0,0);
		return;
	}

	int ns = SetupFuction::GetInstance()->GetStatus(m_strName);
	if (ns == SETUP_FUN_WAITING)
	{
		DisableWaiting();
		return;
	}

	CheckEnable();
	string::size_type idx = text.find("_31_line");//"_31"表示ID
	if (string::npos == idx)
	{
		m_midlable->SetText(text.c_str());
	}
	else
	{
		m_midlable->GetTextView()->setTextFromId(text);
	}
	
}

void GxxSetupChooseBtn::CheckEnable()
{
	if (m_curCursor <= m_minCursor){
		m_btnleft->setEnable(false);
	}
	else{ 
		m_btnleft->setEnable(true);
	}
	if (m_curCursor >= m_maxCursor){
		m_btnright->setEnable(false);
	}
	else{
		m_btnright->setEnable(true);
	}
}

void GxxSetupChooseBtn::DisableAll()
{
	m_btnleft->setEnable(false);
	m_btnright->setEnable(false);
	m_midlable->SetText("No Data");
}

void GxxSetupChooseBtn::DisableWaiting()
{
	m_btnleft->setEnable(false);
	m_btnright->setEnable(false);
	//m_midlable->SetText("Waiting");
}