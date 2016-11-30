#pragma once
#include "USBDllModule.h"
#include "GxxView.h"
#include "CRect.h"
#include "GxLock.h"

class GxxSwText;
class CE_USBACTIVITY_API GxxDCContainer : public GxxView,GxxTimer
{
	friend class PhotoControl;
public:
	enum {PlayOk,PlayErr,PlayStop};
	GxxDCContainer();
	~GxxDCContainer();

	HDC		GetDC();
	bool	getFullScreen(){return m_isFullScreen;}
	virtual void setCtrLayout( TiXmlElement * ele);
	static GxxView* CreateControl();
	bool SetFullScreen(bool b);
	bool IsInDecoding(){return S_StartDecoding;}
	void SetImage(const wchar_t* strPath);
	//void SetStop(BOOL bDraw = TRUE);
	void Rotate();
	

private:
	virtual void TimerTick(UINT nIDEvent);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void onPause();
	virtual void onResume();

	void    PrePaly();
	void	DoSetImage( const wchar_t* strPath );
	virtual void Draw();
	CRect	getDcRect();
	static	DWORD	DecodePicThread(LPVOID lpParam);
	
private:
	HDC	m_hDrawDC;
	static wstring    S_picToPath;//准备解码好的路径
	static GxLock     S_lock;
	static wstring	  S_picBackPath;//已经解码好的路径
	static bool       S_StartDecoding;
	static  bool      s_pauseCheck;//是否停止检测

	HANDLE				m_hDevice;
	HBITMAP    m_hDrawBmp ;
	RECT    m_layoutRect;
	HBRUSH   m_hColor;
	bool     m_isFullScreen;
	GxxSwText *m_showText;
	static GxxSwText  *S_pText;
	int     m_typePlayOk;
	UINT    m_decodeTimer;
	
	bool    m_isBtnDown;
	HANDLE m_decodeHandle;
	const wstring *m_strDecode;
	bool  m_isShowText;
};