#include "StdAfx.h"
#include "GxxNormalKeys.h"

#include "XmlDef.h"
//#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxLabel.h"
#include "ControlHelp.h"
#include "GxxVedioSetup.h"
#include "TVCommand.h"

GxxNormalKeys::GxxNormalKeys()
{
	m_mesView = NULL;

}

GxxNormalKeys::~GxxNormalKeys()
{

}

void GxxNormalKeys::SetMessageView( GxxView * mesView )
{
	m_mesView = mesView;

}


void GxxNormalKeys::setCtrLayout( TiXmlElement * ele )
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


	m_play_pause = safeFindViewByName("label_play_and_pause");
	m_content = safeFindViewByName("Label_Contents");
	m_showlist = safeFindViewByName("Label_ShowList");
	m_stop = safeFindViewByName("label_stop");
	m_full_screen = safeFindViewByName("label_fullscreen");
	m_fast_forward = safeFindViewByName("Label_FastForward");
	m_fast_backward = safeFindViewByName("Label_FastBackward");
	m_replay = safeFindViewByName("label_replay");
	m_setup_audio = safeFindViewByName("LabelToSetupAudio");
	m_page_one = safeFindViewByName("Label_Page1");
	m_page_two = safeFindViewByName("Label_Page2");
	m_ok = safeFindViewByName("label_OK");
	m_vol_add = safeFindViewByName("Label_Vol_Add");
	m_vol_dec = safeFindViewByName("Label_Vol_Dec");
	m_setup_vedio = safeFindViewByName("Label_Set_Vedio");
	m_leave = safeFindViewByName("Label_leave");

	m_group_one = safeFindViewByName("page_one_group");
	m_group_two = safeFindViewByName("page_two_group");

}

BOOL GxxNormalKeys::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_play_pause)	
			{
				PostDtvMessage(DTV_Play_Pause);
				return TRUE;
			}
			if ((GxxView *)wParam == m_content)	
			{
				PostDtvMessage(DTV_Content);
				return TRUE;
			}
			if ((GxxView *)wParam == m_showlist)	
			{
				PostDtvMessage(DTV_ShowList);
				return TRUE;
			}
			if ((GxxView *)wParam == m_stop)	
			{
				PostDtvMessage(DTV_Stop);
				return TRUE;
			}
			if ((GxxView *)wParam == m_full_screen)	
			{
				PostDtvMessage(DTV_Full_Screen);
				return TRUE;
			}
			if ((GxxView *)wParam == m_fast_forward)	
			{
				PostDtvMessage(DTV_Fast_Forward);
				return TRUE;
			}
			if ((GxxView *)wParam == m_fast_backward)	
			{
				PostDtvMessage(DTV_Fast_Backward);
				return TRUE;
			}
			if ((GxxView *)wParam == m_replay)	
			{
				PostDtvMessage(DTV_Replay);
				return TRUE;
			}
			if ((GxxView *)wParam == m_setup_audio)	
			{
				PostDtvMessage(DTV_SetupAudio);
				return TRUE;
			}
			if ((GxxView *)wParam == m_ok)	
			{
				PostDtvMessage(DTV_OK);
				return TRUE;
			}
			if ((GxxView *)wParam == m_vol_add)	
			{
				PostDtvMessage(DTV_Channel_Add);
				return TRUE;
			}
			if ((GxxView *)wParam == m_vol_dec)	
			{
				PostDtvMessage(DTV_Channel_Dec);
				return TRUE;
			}
			if ((GxxView *)wParam == m_setup_vedio)	
			{
				PostDtvMessage(DTV_SetupVedio);
				return TRUE;
			}
			if ((GxxView *)wParam == m_leave)
			{
				PostDtvMessage(DTV_Leave);
				return TRUE;
			}
			if ((GxxView *)wParam == m_page_one)	
			{
				//PostDtvMessage(DTV_Content);
				m_group_one->setDraw(false);
				m_group_two->setDraw(true);
				AfxInvalidateRect(NULL);
				return TRUE;
			}
			if ((GxxView *)wParam == m_page_two)
			{
				m_group_one->setDraw(true);
				m_group_two->setDraw(false);
				AfxInvalidateRect(NULL);
				return TRUE;
			}


		}
	}

	return 0;
}

GxxView* GxxNormalKeys::CreateControl()
{
	return new GxxNormalKeys;
}

void GxxNormalKeys::PostDtvMessage( UINT msg )
{
	if (m_mesView)
	{
		m_mesView->TranslateMessage(msg,(WPARAM)this,0);
	}
}

static RegisterHelp help("GxxNormalKeys", GxxNormalKeys::CreateControl);