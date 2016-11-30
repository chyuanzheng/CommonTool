#include "StdAfx.h"
#include "GxxAniButton.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"

//btn_up2
//#include "aygshell.h"
static RegisterHelp help("GxxAniButton", GxxAniButton::CreateControl);

#define  SEL_ENABLE              "sel_enable"  //相对父窗口

GxxView* GxxAniButton::CreateControl()
{
	return new GxxAniButton;
}

GxxAniButton::GxxAniButton()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_pAniPicBack =  new GxxAniPictureA;
	m_pPicUp = new GxxPicture;
	m_pPicDisable = new GxxPicture;
	m_pPicUpTwo = new GxxPicture;
	m_pPicSel = new GxxPicture;
	m_pPicSel->setDraw(false);

	m_isBtnDown = false;
	m_idTimer = 0;
	m_isClick = true;
	m_isSelEnable = true;

}


GxxAniButton::~GxxAniButton()
{
	delete m_pAniPicBack;
	delete m_pPicUp;
	delete m_pPicDisable;
	delete m_pPicUpTwo;
	delete m_pPicSel;
	if (m_idTimer != 0)
	{
		UnRegisterTimer(m_idTimer);
	}

}

void GxxAniButton::Start_AniBack()
{
	m_pAniPicBack->setCtrRect(m_ActRect);
	m_pAniPicBack->bindHandleRect();
	m_pAniPicBack->Start();

	AddCtrl(m_pAniPicBack,m_pPicUp);

	m_pPicUp->setDraw(false);
	m_isBtnDown = true;
	AfxInvalidateRect(&m_ActRect);
}

void GxxAniButton::Stop_AniBack()
{
	m_pAniPicBack->Stop();
	removeCtrl(m_pAniPicBack);

	m_pPicUp->setDraw(true);
	m_isBtnDown = false;
	AfxInvalidateRect(&m_ActRect);
}



BOOL GxxAniButton::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if (!m_isSelEnable && m_pPicSel->getDraw())
		{
			return FALSE;
		}
		if( m_isClick && InMyArea(lParam) )//选中状态也能按键 暂定
		{	
			AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONDOWN );
			Start_AniBack();

			if (m_idTimer!=0)
			{
				StartTimer(m_idTimer);
			}
			return TRUE;
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if (m_isBtnDown&&m_idTimer!=0)
		{
			if (!InMyArea(lParam))
			{
				StopTimer(m_idTimer);
			}
			//StartTimer(m_idTimer);
			return TRUE;
		}
		return FALSE;
	case WM_LBUTTONUP:
		if( m_isBtnDown  )
		{
			Stop_AniBack();
			if( InMyArea( lParam) )
			{
				AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONUP );
			}
			if (m_idTimer!=0)
			{
				StopTimer(m_idTimer);
			}
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}



void GxxAniButton::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	int ntime = 0;
	const char * pchar = ele->Attribute(BTN_LONG,&ntime);
	if (pchar != NULL)
	{
		ASSERT(ntime > 0);
		m_idTimer = RegisterTimer(ntime);
	}



	pchar = ele->Attribute(SEL_ENABLE);
	if (pchar!=0)
	{
		if ( StrHelp::StringEqual( string(pchar),string("true") ) )
		{
			m_isSelEnable = true;
		}
		else
		{
			m_isSelEnable = false;
		}
	}

	if (m_pPicUp->setPicHandle(ele,BTN_UP))
	{
		setCtrRectUseCenter(ele,m_pPicUp->getPicWidth(),m_pPicUp->getPicHeight());	
		checkToParent(ele);
		m_pPicUp->setCtrRect(m_ActRect);
		m_pPicUp->bindHandleRect();//
		AddCtrl(m_pPicUp);

	}
	else
	{
		if (!setCtrRectUseCenter(ele))
		{
			setCtrRect(ele);
		}
		
		checkToParent(ele);
		//ASSERT(0);
	}



	if (m_pPicUpTwo->setPicHandle(ele,BTN_UP_TWO))
	{
		m_pPicUpTwo->setCtrRectUseCenter( (m_ActRect.right+m_ActRect.left)/2, (m_ActRect.top+m_ActRect.bottom)/2, m_pPicUpTwo->getPicWidth(),m_pPicUpTwo->getPicHeight());	
		m_pPicUpTwo->bindHandleRect();//
		AddCtrl(m_pPicUpTwo);
	}
	if (m_pPicSel->setPicHandle(ele,BTN_SEL))
	{
		m_pPicSel->setCtrRect(m_ActRect);	
		m_pPicSel->bindHandleRect();//
		m_pPicSel->setDraw(false);
		AddCtrl(m_pPicSel);
	}

	m_pPicDisable->setPicHandle(ele,BTN_DISABLE);

	if (!m_pAniPicBack->setPicHandle(ele,BTN_ANI_BACK))
	{
		m_isClick = false;
	}
	setEnableFromXml(ele);
}

//特地为设置写的函数
void GxxAniButton::SetLayout( int center_x,int center_y,const char *picUp,const char* picTwo, const char* Ani,const char* disable )
{
	//ASSERT(picUp);
	bool b = false;
	if (m_pPicUp->setPicHandle(picUp))
	{
		center_x -= m_pPicUp->getPicWidth()/2;
		m_pPicUp->setPicRect(center_x,center_y);
		m_pPicUp->bindHandleRect();
		setCtrRectUseCenter(center_x,center_y,m_pPicUp->getPicWidth(),m_pPicUp->getPicHeight());	
		AddCtrl(m_pPicUp);
		b = true;
	}
	if (m_pPicUpTwo->setPicHandle(picTwo))
	{
		m_pPicUpTwo->setPicRect(center_x,center_y);
		m_pPicUpTwo->bindHandleRect();
		AddCtrl(m_pPicUpTwo);
	}

	if (m_pPicDisable->setPicHandle(disable))
	{
		if (!b)
		{
			center_x -= m_pPicDisable->getPicWidth()/2;

		}
		if (!b)
		{
			setCtrRectUseCenter(center_x,center_y,m_pPicDisable->getPicWidth(),m_pPicDisable->getPicHeight());
		}	
	}

	if (!m_pAniPicBack->setPicHandle(Ani))
	{
		setEnable(false);
	}
}


void GxxAniButton::onEnable( bool e )
{
	m_pPicDisable->setDraw(!e);
	m_pPicUp->setDraw(e);

	if (!e)
	{
		m_pPicDisable->setCtrRect(m_ActRect);
		m_pPicDisable->bindHandleRect();
		AddCtrl(m_pPicDisable,m_pPicUp);
		removeCtrl(m_pPicUp);
	}
	else
	{
		m_pPicUp->setCtrRect(m_ActRect);
		m_pPicUp->bindHandleRect();
		AddCtrl(m_pPicUp,m_pPicDisable);
		removeCtrl(m_pPicDisable);
	}
}

void GxxAniButton::TimerTick( UINT nIDEvent )
{
	StopTimer(m_idTimer);
	Stop_AniBack();

	AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONLONG );
}

HANDLE GxxAniButton::GetActionHandle()
{
	return m_pPicUp->getPicHandle();
}

void GxxAniButton::SetSelect( bool b )
{
	if (b == m_pPicSel->getDraw()|| m_pPicSel->getPicHandle() == NULL)
	{
		return;
	}
	m_pPicSel->setDraw(b);
	m_pPicSel->invalidateRect();

}



