#include "StdAfx.h"
#include "GxxIpodIcon.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"

static RegisterHelp help("GxxIpodIcon", GxxIpodIcon::CreateControl);
GxxView* GxxIpodIcon::CreateControl()
{
	return new GxxIpodIcon;
}


GxxIpodIcon::GxxIpodIcon()
{
	m_hIpod = NULL;
	m_isIconOk = false;
	m_isReceiveIcon = true;

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = ReceiveIcon;
	GXNotify::RegisterNotifyHandler("ipod_albumart", notify);

}

GxxIpodIcon::~GxxIpodIcon()
{

}


void GxxIpodIcon::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	//setCtrName(ele);
	if (setPicHandle(ele,BTN_UP))
	{
		if ( !setCtrRectUseCenter(ele,getPicWidth(),getPicHeight()) ){
			if (!setCtrRectUseCenter(ele))
			{
				if (!setCtrRect(ele) )
				{
					ASSERT(0);
				}
			}
		}
		checkToParent(ele);
		bindHandleRect();//m_pPicDisable
	}
	else
	{
		setCtrRectUseCenter(ele);
		//ASSERT(0);
	}
	m_hIpod = SkiaBitmapManager::GetInstance()->InitImage();
}



LRESULT GxxIpodIcon::ReceiveIcon(DWORD param1, DWORD param2)
{
	if (!m_isReceiveIcon)
	{
		return 0;
	}
	int h = param2 & 0xFFFF;
	int w = param2 >> 16;
	m_isIconOk = false;
	if (param1!=0 && h != 0 && w != 0)
	{
		SkiaBitmapManager::GetInstance()->SetIconConfig(m_hIpod,(void *)param1,w,h);
		m_isIconOk = true;
	}
	AfxInvalidateRect(&m_ActRect);
	return 0;
}

void GxxIpodIcon::Draw()
{
	if (m_hIpod && m_isIconOk && m_isReceiveIcon)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_hIpod,&m_ActRect);
	}
	else
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_hPicture,&m_ActRect);
	}
}

void GxxIpodIcon::SetReceiveIcon( bool brec )
{
	m_isReceiveIcon  = brec;
	if (!m_isReceiveIcon)
	{
		m_isIconOk = false;
	}
}

void GxxIpodIcon::ResetIcon()
{
	m_isIconOk = false;
	invalidateRect();
}
