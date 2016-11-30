#include "StdAfx.h"
#include "GxxAppButton.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"
#include "GxxAppPage.h"
#include "GxxAppGroup.h"
#include "GxxAniPictureA.h"

RECT GxxAppButton::m_pageActRect[A_PAGE_SIZE] = {};
RECT GxxAppButton::m_pageEditRect[A_PAGE_SIZE] = {};

GxxAppButton::GxxAppButton( int nth ) :GxxAtButton(nth)
{

}



GxxAppButton::~GxxAppButton()
{

}







void GxxAppButton::setCtrLayout( TiXmlElement * ele )
{

}



void GxxAppButton::setLocal(int local)
{
	m_local = local;
	if (GxxAtButton::getEditMode())
	{
		setCtrRect(m_pageEditRect[local]);
	}
	else
	{
		setCtrRect(m_pageActRect[local]);
	}
	RectChanged();
}

int GxxAppButton::GetPageMoveX()
{
	return ((GxxAppPage *)(getParentView()))->GetXmove();
}
