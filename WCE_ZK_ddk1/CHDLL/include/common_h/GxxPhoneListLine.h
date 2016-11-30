#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"

class GxxSwText;

class CE_CONTROL_API GxxPhoneListLine : public GxxLBLine
{
public:

	GxxPhoneListLine();
	virtual ~GxxPhoneListLine();
	void setPhoneLine( int index, int top,const wstring& wstr,const wstring& wstr2);//index �ǵڼ��У�nline���Լ���line��Rect
	const wstring & getLineName();
protected:
	GxxSwText *m_pPhoneNumText;
	GxxSwText *m_pTextTitle;
};
