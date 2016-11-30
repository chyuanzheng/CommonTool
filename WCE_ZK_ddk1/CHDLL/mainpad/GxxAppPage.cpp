#include "StdAfx.h"
#include "GxxAppPage.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"

//
HANDLE    GxxAppPage::m_handleLine = NULL;
RECT      GxxAppPage::m_lineLeftRect = RECT();
RECT      GxxAppPage::m_lineRightRect = RECT();
GxxAppPage::GxxAppPage(  )
{
	::SetRect(&m_ActRect,0,0,0,0);
}



GxxAppPage::~GxxAppPage()
{


}

void GxxAppPage::Draw(  )
{
	if (GxxAtButton::getEditMode()&&m_move==0)
	{
		ASSERT(NULL!=m_handleLine);
		RECT rt;
		::SetRect(&rt,m_lineLeftRect.left+m_move, m_lineLeftRect.top,m_lineLeftRect.right+m_move,m_lineLeftRect.bottom);
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleLine,&rt,255);
		::SetRect(&rt,m_lineRightRect.left+m_move, m_lineRightRect.top,m_lineRightRect.right+m_move,m_lineRightRect.bottom);
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleLine,&rt,255);
	}
	
}



BOOL GxxAppPage::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	return FALSE;
}


//重新设定位置 按照顺序
void GxxAppPage::resetRect()
{
	ControlList::iterator pos;
	int i = 0;
	for (pos = (m_pCtrlVet)->begin();pos != (m_pCtrlVet)->end();pos++ )
	{
		((GxxAppButton*)(*pos))->setLocal(i);//添加句柄
		i++;
	}
}

//加入一个按键
bool GxxAppPage::checkAddBtn( GxxAppButton* at )
{
	if (getCtrlsSize()==8)
	{
		return false;
	}

	GxxView *p_at =  at->getParentView();
	if (p_at != this)//另一页加入到本页
	{
		p_at->removeCtrl(at);
		AddCtrl(at);
		at->setLocal(getCtrlsSize()-1);
	}	
	return true;
}

void GxxAppPage::sortBtn()
{
	
}
//downBtn ,toBtn 都属于本页
void GxxAppPage::exchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn )
{
	int downLocal = downBtn->getLocal();
	downBtn->setLocal(toBtn->getLocal());
	toBtn->setLocal(downLocal);
	m_pCtrlVet->remove(toBtn);
	m_pCtrlVet->remove(downBtn);
	InsertBtn(toBtn);
	InsertBtn(downBtn);
}



void GxxAppPage::ExchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn, GxxAppPage * downPage, GxxAppPage * toPage )
{
	int downLocal = downBtn->getLocal();
	downBtn->setLocal(toBtn->getLocal());
	toBtn->setLocal(downLocal);
	toPage->m_pCtrlVet->remove(toBtn);
	downPage->m_pCtrlVet->remove(downBtn);
	downPage->InsertBtn(toBtn);
	toPage->InsertBtn(downBtn);
}


void GxxAppPage::InsertBtn( GxxAppButton* at )
{
	ControlList::iterator pos;
	for (pos = m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		if ( ((GxxAppButton*)(*pos))->getLocal() > at->getLocal())
		{
			break;
		}
	}
	m_pCtrlVet->insert(pos,at);
	at->setParentView(this);
}

//按键 down 插在 to的位置
void GxxAppPage::InsertBtn( GxxAppButton* to, GxxAppButton* down )
{
	
	ControlList::iterator pos;
	for (pos = m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		if ((*pos) == to)
		{
			break;
		}
	}

	down->setLocal( to->getLocal());
	
	ASSERT(pos!=m_pCtrlVet->end());
	//
	ControlList::iterator pos2;
	for (pos2 = pos;pos2!=m_pCtrlVet->end();pos2++)
	{
		((GxxAppButton*)(*pos2))->setLocal( ((GxxAppButton*)(*pos2))->getLocal() + 1);
	}
	InsertBtn(down);

}

//void GxxAppPage::AddHandlesToAction( AnimationAction * action )
//{
//	ControlList::iterator pos;
//
//	for (pos = (m_pCtrlVet)->begin();pos != (m_pCtrlVet)->end();pos++ )
//	{
//		action->AddHandle( ( (GxxAppButton*)(*pos))->getAppActHandle());
//
//	}
//}

void GxxAppPage::SetLineRect( int nleft, int ntop, int nwidth, int nheight, int r_width )
{
	::SetRect(&m_lineLeftRect,  nleft,                         ntop,               nleft+nwidth,                  ntop+nheight);
	::SetRect(&m_lineRightRect,  m_lineLeftRect.left+r_width,  m_lineLeftRect.top,  m_lineLeftRect.right+r_width, m_lineLeftRect.bottom);
	GxxAtButton::setBorder(m_lineLeftRect.left, m_lineRightRect.right);
}

void GxxAppPage::WritePageNth( TiXmlDocument &tDoc )
{
	TiXmlElement *elePage = new TiXmlElement(APPPAGEPAD);
	tDoc.LinkEndChild(elePage);

	for (ControlList::iterator pos=m_pCtrlVet->begin(); pos!=m_pCtrlVet->end(); ++pos)
	{
		TiXmlElement *eleBtn = new TiXmlElement(GXXAPPBUTTON);
		elePage->LinkEndChild(eleBtn);

		int nth = ((GxxAppButton*)(*pos))->getNth();
		eleBtn->SetAttribute(NTH_APP, nth);	
	}
}
