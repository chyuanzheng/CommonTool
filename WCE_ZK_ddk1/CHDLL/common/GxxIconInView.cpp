#include "StdAfx.h"
#include "GxxIconInView.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"

static RegisterHelp help("GxxIconInView", GxxIconInView::CreateControl);
GxxView* GxxIconInView::CreateControl()
{
	return new GxxIconInView;
}


GxxIconInView::GxxIconInView()
{


}

GxxIconInView::~GxxIconInView()
{

}

void GxxIconInView::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	if (setPicHandle(ele,BTN_UP))
	{
		setCtrRectUseCenter(ele,getPicWidth(),getPicHeight());	
		RECT rect = getParentView()->getCtrRect();
		m_ActRect.left += rect.left;
		m_ActRect.top += rect.top;
		m_ActRect.right += rect.right;
		m_ActRect.bottom += rect.bottom;
		bindHandleRect();//m_pPicDisable
	}
	else
	{
		setCtrRectUseCenter(ele);
	}
}


