#include "StdAfx.h"
#include "GxxControlGroup.h"

#include "XmlDef.h"
//#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "GxxLabel.h"
#include "ControlHelp.h"


GxxControlGroup::GxxControlGroup()
{
	bIsVisible = false;
	m_handleBack = NULL;
	backColor = -1;
}

GxxControlGroup::~GxxControlGroup()
{
	if (m_handleBack!=NULL)
	{
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleBack);
	}

}
void GxxControlGroup::Draw( )
{


	if(backColor != -1)	//绘制背景
	{
		SkiaBitmapManager::GetInstance()->DrawColor(backColor,&AfxGetDcRect());
	}
	if(m_handleBack)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleBack);
	}
	

}


COLORREF GxxControlGroup::getColor(const char* str)
{
	if (!str)
	{
		return 0;
	}
	DWORD color = (strtoul(str, NULL, 16));
	if ((color >> 24) == 0)
	{
		color |= 0xFF000000;
	}
	return color;
}

void GxxControlGroup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);


	const char* pback = ele->Attribute(BACKGROUD);

	if (NULL!=pback)
	{
		m_handleBack =  SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pback), &AfxGetDcRect());

	}

	if(ele->Attribute(BACKCOLOR))	//背景颜色
	{
		const char* szBackColor;
		szBackColor = ele->Attribute(BACKCOLOR);
		backColor = getColor(szBackColor);
		
	}
	

	if(ele->Attribute(VISIBLE))	//是否出现控件
	{
		int iVisible = 1;
		ele->Attribute(VISIBLE, &iVisible);

		if(iVisible == 0)
		{
			setDraw(FALSE);
		}
		
	}


	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);

}

void GxxControlGroup::MoveSubControls(int iRelateX, int iRelateY)
{
	list<GxxView*>::iterator it;
	for(it = m_pCtrlVet->begin(); it != m_pCtrlVet->end(); it++)
	{
		RECT rc;
		(*it)->getCtrRect(rc);
		rc.left = rc.left + iRelateX;
		rc.right = rc.right + iRelateX;
		rc.top = rc.top + iRelateY;
		rc.bottom = rc.bottom + iRelateY;
		(*it)->setCtrRect(rc);
	}
}



GxxView* GxxControlGroup::CreateControl()
{
	return new GxxControlGroup;
}

static RegisterHelp help("GXX_CONTROL_GROUP", GxxControlGroup::CreateControl);