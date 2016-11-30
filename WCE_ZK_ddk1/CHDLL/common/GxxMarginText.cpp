#include "StdAfx.h"
#include "GxxMarginText.h"
#include "XmlDef.h"
#include "ControlHelp.h"
#include "StrHelp.h"
#include "LangStringManager.h"
static RegisterHelp help("GxxMarginText", GxxMarginText::CreateControl);
GxxView* GxxMarginText::CreateControl()
{
	return new GxxMarginText;
}

GxxMarginText::GxxMarginText()
{
	m_marginColor = NULL;
}

GxxMarginText::~GxxMarginText()
{
	FreeColor();

}

void GxxMarginText::setMargin( UINT mc )
{
	FreeColor();
	m_marginColor = new UINT;
	*m_marginColor = mc;
}

void GxxMarginText::FreeColor()
{
	if (m_marginColor)
	{
		delete m_marginColor;
		m_marginColor = NULL;
	}
}

void GxxMarginText::Draw()
{
	if (m_marginColor)
	{
		RECT pre_rc = m_ActRect;
		UINT pre_color = m_color;
		setColor(*m_marginColor);
		int nmove = 1;
		m_ActRect.left += nmove;
		m_ActRect.right+= nmove;
		GxxSwText::Draw();

		m_ActRect=pre_rc;
		nmove = -1;
		m_ActRect.left += nmove;
		m_ActRect.right+= nmove;
		GxxSwText::Draw();


		m_ActRect=pre_rc;
		nmove = 1;
		m_ActRect.top += nmove;
		m_ActRect.bottom += nmove;
		GxxSwText::Draw();

		m_ActRect=pre_rc;
		nmove = -1;
		m_ActRect.top += nmove;
		m_ActRect.bottom += nmove;
		GxxSwText::Draw();

		m_ActRect=pre_rc;
		setColor(pre_color);
		GxxSwText::Draw();
	}
	else
	{
		GxxSwText::Draw();
	}
}

void GxxMarginText::setCtrLayout( TiXmlElement * ele )
{
	int data;
	const char *catrri = ele->Attribute("margin_color",&data);
	if (NULL != catrri)
	{
		setMargin(data);
	}
	GxxSwText::setCtrLayout(ele);
}
