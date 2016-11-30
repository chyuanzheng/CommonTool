#include "StdAfx.h"
#include "GxxLBList.h"
#include "GxxListGroupSetup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
//
//#include "aygshell.h"
static RegisterHelp help("GxxListGroupSetup", GxxListGroupSetup::CreateControl);
GxxView* GxxListGroupSetup::CreateControl()
{
	return new GxxListGroupSetup;
}
GxxListGroupSetup::GxxListGroupSetup()
{
	m_curListBox = NULL;
	m_upBtn = NULL;
	m_downBtn = NULL;
	m_progress = NULL;
}

GxxListGroupSetup::~GxxListGroupSetup()
{

}
BOOL GxxListGroupSetup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniButton *)wParam == m_upBtn)
			{
				m_curListBox->MovePage(false);
				return TRUE;
			}
			if ((GxxAniButton *)wParam == m_downBtn)
			{
				m_curListBox->MovePage(true);
				return TRUE;
			}
		}
		return FALSE;
	case CTR_TRANLATE_MES:
		CacuViewSatus();
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}

void GxxListGroupSetup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	TiXmlElement * chid = ele->FirstChildElement();
	setListBoxList(chid);
}

//���ﲢ����GxxLBList�����ӿؼ����������㶯̬�����ض���GxxLBList��
void GxxListGroupSetup::setListBoxList( TiXmlElement * ele )
{
	string ctrname;

	while(ele)
	{
		GxxView *ctr=NULL;
		ctrname = ele->Value();
		if(ctrname == "GxxListBox")
		{
			ctr = new GxxLBList;//GXCreateControl::CreateControlByType(ctrname.c_str());
			ctr->setCtrLayout(ele);
			m_allListBox.insert( make_pair(ctr->getCtrName(),(GxxLBList*)ctr) );
		}
		else 
		{
			ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
			ctr->setCtrLayout(ele);
			AddCtrl(ctr);
		}
		ele = ele->NextSiblingElement();
	}
	ASSERT(m_allListBox.size()>0);
}

/************************************************************************/
/* ���õ�ǰ��       GxxLBList                                         */
/************************************************************************/
void GxxListGroupSetup::setActiveListBox( const string & listname,bool isReStart /*= true*/ )
{
	removeCtrl(m_curListBox);
	GxxLBList *preListBox = NULL;
	if (isReStart)
	{
		preListBox = m_curListBox;//��סǰһ���Ա㷵��
	}
	m_curListBox = m_allListBox[listname];
	ASSERT(NULL!=m_curListBox);
	AddCtrl(m_curListBox);
	m_curListBox->setPreListBox(preListBox);
	//����Ҫ�� GxxLBList ��Ӧ��Xml�ļ� m_curListBox.open();

	m_upBtn = (GxxAniButton *)findViewByName("btn_box_up");
	m_downBtn = (GxxAniButton *)findViewByName("btn_box_down");
	m_progress = (GxxProgressV *)findViewByName("progress1");
	CacuViewSatus();
}


void GxxListGroupSetup::CacuViewSatus()
{
	float fs,fe;
	m_curListBox->getFRation(fs,fe);
	m_progress->SetProgress(fs,fe);
	m_downBtn->setEnable(!(fe == 1.0));
	m_upBtn->setEnable(!(fs == 0.0));
}


