#include "StdAfx.h"
#include "GxxAniLable.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
//
//#include "aygshell.h"
static RegisterHelp help("GxxAniLable", GxxAniLable::CreateControl);
GxxView* GxxAniLable::CreateControl()
{
	return new GxxAniLable;
}

GxxAniLable::GxxAniLable()
{
	m_picIcon[0] = m_picIcon[1] = m_picIcon[2] = NULL;
	m_swtext[0] = m_swtext[1] = m_swtext[2] = NULL;
}

GxxAniLable::~GxxAniLable()
{
	for (int i =0;i<3;i++)
	{
		if (m_swtext[i] != NULL)
		{
			delete m_swtext[i];
		}
		if (m_picIcon[i] != NULL)
		{
			delete m_picIcon[i];
		}
	}

}

void GxxAniLable::setCtrLayout( TiXmlElement * ele )
{
	GxxAniButton::setCtrLayout(ele);
	//m_ctrText->setCtrLayout(ele);
	setChildLayout(ele);

}



void GxxAniLable::SetText( const wstring &str, bool bDraw /*= true*/ )
{	
	m_swtext[0]->setText(str);
	if (bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}

void GxxAniLable::SetText( const wstring &str,int index, bool bDraw /*= true*/ )
{
	ASSERT(index < 3);
	ASSERT(m_swtext[index] != NULL);
	m_swtext[index]->setText(str);
	if (bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}

}

void GxxAniLable::SetText( const char *str,bool bDraw /*= true*/ )
{
	ASSERT(m_swtext[0] != NULL);
	m_swtext[0]->setText(str);
	if (bDraw)
	{
		AfxInvalidateRect(&m_ActRect);
	}
}

void GxxAniLable::setChildLayout( TiXmlElement * ele )
{
	int itext = 0;
	int iicom = 0;
	TiXmlElement * chid = ele->FirstChildElement();

	GxxView *ctr=NULL;
	while(chid)
	{	
		ASSERT(itext<3);
		const char *cval = chid->Value();
		if (string(cval) == "GxxSwText")
		{
			ASSERT(itext<3);
			ctr = m_swtext[itext] = new GxxSwText;
			itext++;	
		}
		else if (string(cval) == "GxxPicIcon")
		{
			ASSERT(iicom<3);
			ctr= m_picIcon[iicom]=  new GxxPicIcon;
			iicom++;
			
		}
		ASSERT(NULL!=ctr);
		if (NULL!=ctr)
		{

			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();
		
	}

}


void GxxAniLable::SetLayout( int center_x,int center_y,const char *picDisable )
{

	GxxAniButton::SetLayout(center_x,center_y,NULL,NULL,NULL,picDisable);
	ASSERT(NULL == m_swtext[0]);
	m_swtext[0] = new GxxSwText;
	AddCtrl(m_swtext[0]);
	m_swtext[0]->setCtrRect(m_ActRect);
	m_swtext[0]->setTextFont(0xff000000,25);
	//m_swtext[0]->setColor(0xff000000);


}

GxxSwText* GxxAniLable::GetTextView()
{
	return m_swtext[0];
}
