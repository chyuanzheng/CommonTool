#pragma once
#include "IPODDllModule.h"
#include "StrHelp.h"
#include "GxxListGroupBase.h"

class GxxListPercent;



#define		Command_Base					12200
#define		GX_INIT_MOVIE_LIST				Command_Base+0
#define		GX_INIT_MUSIC_LIST				Command_Base+1

#define		GX_LISTBOX_BUTTON_DOWNM  				Command_Base+2
#define		GX_LISTBOX_BACK_TO_ACTIVITY  			Command_Base+3
#define		GX_LISTBOX_BACK_TO_LIST       			Command_Base+4





class CE_IPODACTIVITY_API GxxIpodListGroup : public GxxListGroupBase
{
public:
	virtual void AddItem(wstring name) ;	//ÎªÄ¿Â¼¼ÓITEM
	void InitList();
	void InitFirstList();

	void ResetList();
	void BackToMenu();
	void StartReceiveList();
	void SetMessageView(GxxView * mesView){m_mesView = mesView;}
	void SetIpodName( const WCHAR *name );



public:
	GxxIpodListGroup();
	virtual ~GxxIpodListGroup();
	
	static GxxView* CreateControl();

protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

private:
	GxxListPercent   *m_percentBtn;
	enum{FIRST_LIST, MUSIC_MENU_LIST, MUSIC_CLASS_LIST,MOVIE_CLASS_LIST};
	int				m_listType;
	GxxView			*m_mesView;
	LPARAM            m_param;
	wstring         m_ipodName;
	wstring         m_lineName;

private:
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	void SetGroupTitle(const wstring &str);
	void InitMusicList();
	void DeleteAllItem();
	void SendGxxMessage( UINT msg,LPARAM lParam = 0 );
	
	


};
