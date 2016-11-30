#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"
#include "bluetooth.h"
class GxxSwText;
class GxxPicture;
class CE_CONTROL_API GxxRecordListLine : public GxxLBLine
{
public:

	GxxRecordListLine();
	virtual ~GxxRecordListLine();
	void setRecordLine( int index, int top,const wstring& wstr,RecordItem::RecordType rt, const wstring &date, const wstring &strPerson);//index 是第几行，nline可以计算line的Rect
	const wstring & getLineName();
	const wstring & getDate();
	const wstring & getPerson();
	RecordItem::RecordType getRecordType(){ return m_rtype;}

protected:
	virtual void Draw();
private: 

	static GxxPicture *S_iconInCall;//左边 icon
	static GxxPicture *S_iconOutCall;//左边 icon
	static GxxPicture *S_iconCallMiss;//左边 icon
	static GxxSwText  *S_pText;
	static  int  S_nwith;
	static  int  S_nheight;

	wstring    m_strName;
	wstring    m_strDate;
	RecordItem::RecordType m_rtype;
	wstring  m_strPerson;
};
