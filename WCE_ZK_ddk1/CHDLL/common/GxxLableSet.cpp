#include "StdAfx.h"
#include "GxxLableSet.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GxxSwText.h"
#include "GxxAniLable.h"

static RegisterHelp help("GxxLableSet", GxxLableSet::CreateControl); 
GxxView* GxxLableSet::CreateControl()
{
	return new GxxLableSet;
}

GxxLableSet::GxxLableSet()
{
	m_hAni = NULL;
}

GxxLableSet::~GxxLableSet()
{
	AnimationManage::GetInstance()->DeInitAniSet(m_hAni);
}



void GxxLableSet::Draw(  )
{
	
}


void GxxLableSet::onPause()
{
	//AnimationManage::GetInstance()->StopAction(m_hAni);
	
	for (TL_TEXT::iterator pos = m_alltext.begin(); pos!= m_alltext.end();++pos)
	{
		(*pos)->setDraw(true);
	}
}


BOOL GxxLableSet::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_ANIMATION_MES://MES_ANIMATION_END 
		if ( (  ANIMATION_START == LOWORD(lParam) && m_moveAction_1 == (AnimationAction*)wParam   &&  TRUE==HIWORD( lParam ))
			|| ( (ANIMATION_END == LOWORD(lParam))  &&  m_moveAction_2== (AnimationAction*)wParam &&  FALSE==HIWORD( lParam )) )
		{
			for (TL_TEXT::iterator pos = m_alltext.begin(); pos!= m_alltext.end();++pos)
			{
				(*pos)->setDraw(true);
			}
			if (NULL!=m_sel_lable)
			{
				m_sel_lable->SetSelect(true);//动画结束的时候显示 选中
			}
			return TRUE;
		}


		return FALSE;
	default:
		return FALSE;
	}
}




void GxxLableSet::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	if (!setCtrRect(ele))
	{
		setCtrRectUseCenter(ele);
	}
	

	const char* pa = ele->Attribute(ANIMATION);
	m_hAni= AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA (pa));
	m_moveAction_1 = AnimationManage::GetInstance()->GetAction(m_hAni,"set_move_1");
	m_moveAction_1->SetAniRect(m_ActRect);

	m_moveAction_2 = AnimationManage::GetInstance()->GetAction(m_hAni,"set_move_2");
	m_moveAction_2->SetAniRect(m_ActRect);



	TiXmlElement * chid = ele->FirstChildElement();

	GxxView *ctr=NULL;
	while(chid)
	{	
		const char *cval = chid->Value();
		if (string(cval) == "GxxAniLable")
		{
			ctr = new GxxAniLable;
			ctr->setCtrLayout(chid);
		    m_moveAction_1->AddHandle( ((GxxAniLable *)ctr)->GetActionHandle() );//添加句柄 
			m_moveAction_2->AddHandle( ((GxxAniLable *)ctr)->GetActionHandle() );//添加句柄 
			m_alltext.push_back( ((GxxAniLable *)ctr)->GetTextView());
			m_all_lable.push_back((GxxAniLable *)ctr);
		}
		else if (string(cval) == "GxxPicIcon")
		{
			ctr = new GxxPicIcon;
			ctr->setCtrLayout(chid);
			m_moveAction_2->AddHandle( ((GxxPicIcon *)ctr)->getPicHandle() );
			m_moveAction_1->AddHandle( ((GxxPicIcon *)ctr)->getPicHandle() );
		}
		ASSERT(NULL!=ctr);
		if (NULL!=ctr)
		{
			AddCtrl(ctr);
		}
		chid = chid->NextSiblingElement();
	}

}


void GxxLableSet::StartAction(bool bright)
{
	AnimationManage::GetInstance()->setDirect(m_hAni,!bright);
	AnimationManage::GetInstance()->StartAction(m_hAni);
	for (TL_TEXT::iterator pos = m_alltext.begin(); pos!= m_alltext.end();++pos)
	{
		(*pos)->setDraw(false);
	}
	m_sel_lable = NULL;
	for (TL_Lable::iterator pos = m_all_lable.begin(); pos!= m_all_lable.end();++pos)
	{
		if ( (*pos)->GetSelect())
		{
			m_sel_lable = *pos;
			m_sel_lable->SetSelect(false);//动画开始的时候不显示 选中
			break;
		}
	}
}

