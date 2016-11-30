#include "StdAfx.h"
#include "GxxFullSKeyBoard.h"

#include "XmlDef.h"
//#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxLabel.h"
#include "ControlHelp.h"
#include "TVCommand.h"


GxxFullSKeyBoard::GxxFullSKeyBoard()
{
	m_isLeft  = false;
}

GxxFullSKeyBoard::~GxxFullSKeyBoard()
{

}



void GxxFullSKeyBoard::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);

	int iVisible = 1;
	if(ele->Attribute(VISIBLE, &iVisible))	//是否出现控件
	{
		if(iVisible == 0)
		{
			setDraw(FALSE);
		}
	}
	setCtrList( ele->FirstChildElement() );

	m_left_right_btn = safeFindViewByName("Label_KeyBoard_ToleftOrRight");
	m_picToLeft = m_left_right_btn->safeFindViewByName("picToLeft");
	m_picToRight= m_left_right_btn->safeFindViewByName("picToRight");
	m_picToRight->setDraw(false);

	m_ok_btn = safeFindViewByName("Label_KeyBoard_OK");
	m_up_btn =safeFindViewByName("Label_KeyBoard_up");
	m_left_btn = safeFindViewByName("Label_KeyBoard_left");
	m_right_btn = safeFindViewByName("Label_KeyBoard_right");
	m_down_btn = safeFindViewByName("Label_KeyBoard_down");
}



void GxxFullSKeyBoard::SetMessageView( GxxView * mesView )
{
	m_mesView = mesView;
}

BOOL GxxFullSKeyBoard::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_ok_btn)	
			{
				PostDtvMessage(DTV_OK);
				//setDraw(false);
				//AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxView *)wParam == m_up_btn)	
			{
				PostDtvMessage(DTV_Channel_Add);
				return TRUE;
			}
			if ((GxxView *)wParam == m_down_btn)	
			{
				PostDtvMessage(DTV_Channel_Dec);
				return TRUE;
			}
			if ((GxxView *)wParam == m_left_btn)	
			{
				PostDtvMessage(DTV_Vol_Dec);
				return TRUE;
			}
			if ((GxxView *)wParam == m_right_btn)	
			{
				PostDtvMessage(DTV_Vol_Add);
				return TRUE;
			}
			if( (GxxView *)wParam == m_left_right_btn)
			{
				if (m_isLeft)
				{
					setMoveRect(220,0);
					m_picToRight->setDraw(false);
					m_picToLeft->setDraw(true);
				}
				else
				{
					setMoveRect(-220,0);
					m_picToRight->setDraw(true);
					m_picToLeft->setDraw(false);
				}
				m_isLeft = !m_isLeft;
				AfxInvalidateRect(NULL);
			}
		}
	}

	return 0;
}

void GxxFullSKeyBoard::PostDtvMessage( UINT msg )
{
	if (m_mesView)
	{
		m_mesView->TranslateMessage(msg,(WPARAM)this,0);
	}
}


GxxView* GxxFullSKeyBoard::CreateControl()
{
	return new GxxFullSKeyBoard;
}

static RegisterHelp help("GxxFullSKeyBoard", GxxFullSKeyBoard::CreateControl);