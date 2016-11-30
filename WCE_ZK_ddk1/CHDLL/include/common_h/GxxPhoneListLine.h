#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"

class GxxSwText;

class CE_CONTROL_API GxxPhoneListLine : public GxxLBLine
{
public:

	GxxPhoneListLine();
	virtual ~GxxPhoneListLine();
	void setPhoneLine( int index, int top,const wstring& wstr,const wstring& wstr2);//index 是第几行，nline可以计算line的Rect
	const wstring & getLineName();
protected:
	GxxSwText *m_pPhoneNumText;
	GxxSwText *m_pTextTitle;
};
