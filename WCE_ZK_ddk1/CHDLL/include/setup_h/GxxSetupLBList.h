#pragma once
#include "GxxLBList.h"
class GxxSetupListLine;
class CE_CONTROL_API GxxSetupLBList : public GxxLBList
{
    

public:
	GxxSetupLBList();
	virtual ~GxxSetupLBList();
	virtual void setCtrLayout( TiXmlElement * ele);
protected:
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	void AddSetupLine( TiXmlElement * ele );
	
private:
	ControlList  *m_pCtrline_1;//所有line 1
	ControlList  *m_pCtrline_0;//所有line 1
	void RemoveLine( ControlList * pListLine );
	void AddLine( ControlList * pListLine );
};
