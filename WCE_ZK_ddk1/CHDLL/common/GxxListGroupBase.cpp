#include "StdAfx.h"
#include "GxxLBList.h"
#include "GxxListGroupBase.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxSwText.h"

#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
//
GxxListGroupBase::GxxListGroupBase()
{
	m_curListBox = NULL;
	m_upBtn = NULL;
	m_downBtn = NULL;
	m_progress = NULL;
	m_titleText = NULL;
}

GxxListGroupBase::~GxxListGroupBase()
{

}
BOOL GxxListGroupBase::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxAniButton *)wParam == m_upBtn)
			{
				m_curListBox->MovePage(false);
				AfterMovePage();
				return TRUE;
			}
			if ((GxxAniButton *)wParam == m_downBtn)
			{
				m_curListBox->MovePage(true);
				AfterMovePage();
				return TRUE;
			}
		}
		return FALSE;
	case CTR_TRANLATE_MES:
		CacuViewSatus();
		return TRUE;
	case CTR_LIST_PERCENT_BTN:
		m_curListBox->MoveToLineMid(m_curListBox->getCtrlsSize()*(int(wParam))/100-1);
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}




void GxxListGroupBase::CacuViewSatus()
{
	float fs,fe;
	m_curListBox->invalidateRect();
	m_curListBox->getFRation(fs,fe);
	m_progress->SetProgress(fs,fe);
	m_downBtn->setEnable(!(fe == 1.0));
	m_upBtn->setEnable(!(fs == 0.0));
	//AfxInvalidateRect(&m_ActRect);
}

void GxxListGroupBase::FindChildCtrls()
{
	m_upBtn = (GxxAniButton *)findViewByName("btn_box_up");
	m_downBtn = (GxxAniButton *)findViewByName("btn_box_down");
	m_progress = (GxxProgressV *)findViewByName("progress1");
	m_titleText = (GxxSwText *)findViewByName("list_title");
	m_btx = findViewByName("x_btn");
	m_btnBack = findViewByName("back_btn");
	

	ASSERT(m_upBtn&&m_downBtn&&m_progress);
}


