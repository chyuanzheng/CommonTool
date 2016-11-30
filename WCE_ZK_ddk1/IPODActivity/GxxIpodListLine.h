#pragma once
#include "IPODDllModule.h"
#include "GxxView.h"
#include "GxxLBLine.h"
//#include "bluetooth.h"
class GxxSwText;
class GxxPicture;

class CE_IPODACTIVITY_API GxxIpodListLine : public GxxLBLine
{
public:

	GxxIpodListLine();
	const wstring& GetTextName();
	virtual ~GxxIpodListLine();

	void setIpodLine( int nth, const string * s_id, const wstring * s );
protected:
	virtual void Draw();


private: 
	static GxxSwText *S_pTextName;
	wstring    m_strText;
	const wstring    *m_strText_id;
};
