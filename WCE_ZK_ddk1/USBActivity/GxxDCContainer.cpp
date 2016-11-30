#include "stdafx.h"
#include "GxxDCContainer.h"
#include "ControlHelp.h"
#include "SkiaBitmapManager.h"
#include "GxxSwText.h"
#include "LangStringManager.h"
#include "PhotoControl.h"

GxLock     GxxDCContainer::S_lock;
wstring   GxxDCContainer::S_picToPath;
wstring   GxxDCContainer::S_picBackPath;
bool       GxxDCContainer::S_StartDecoding = false;
GxxSwText  *GxxDCContainer::S_pText= NULL;

HDC GxxDCContainer::GetDC()
{
	return m_hDrawDC;
}

GxxDCContainer::GxxDCContainer()
{
	m_hDrawDC = NULL;
	m_hDevice = NULL;
	m_hDrawBmp = NULL;
	m_showText = NULL;
	m_isFullScreen =false;
	m_isBtnDown = false;
	m_isShowText = false;

	m_typePlayOk = PlayStop;

	if (NULL == S_pText)
	{
		S_pText = new GxxSwText;
		S_pText->setFormat(DT_VCENTER|DT_CENTER);
		S_pText->setTextFont(0xffffffff,26);
	}

	m_strDecode = LangStringManager::GetInstance()->getString("Decoding_02");
	m_decodeTimer = RegisterTimer(200);


}

GxxDCContainer::~GxxDCContainer()
{
	if (m_hDrawDC)
	{
		delete m_hDrawDC;
		SkiaBitmapManager::GetInstance()->DeInitImage(m_hDevice);
		DeleteObject(m_hDrawBmp);
		DeleteObject(m_hColor);
		delete m_showText;
	}
}

void GxxDCContainer::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRectUseCenter(ele);
	checkToParent(ele);
	m_layoutRect = m_ActRect;


	HDC hdc = ::GetDC(AfxGetHWND());
	m_hDrawDC = CreateCompatibleDC(hdc);
	ReleaseDC(AfxGetHWND(),hdc);

	RECT rc;
	::SetRect(&rc,0,0,AfxGetDevWidth(),AfxGetDevHeight());
	m_hDevice = SkiaBitmapManager::GetInstance()->InitImage(m_hDrawDC,&rc,&m_hDrawBmp);
	COLORREF colBack = 0xFF000000 | (RGB(16,16,16));
	m_hColor = CreateSolidBrush(colBack);
	SetFullScreen(false);

	m_showText = new GxxSwText;
	m_showText->setTextFont(0xffffffff,22);

	PhotoControl::Init();
	PhotoControl::SetDcContainter(this);

	DWORD dwTheadID;
	m_decodeHandle = CreateThread(NULL, 0, DecodePicThread, (LPVOID)this, 0, &dwTheadID);


}



void GxxDCContainer::onPause()
{
	s_pauseCheck = true;
	
}


void GxxDCContainer::onResume()
{
	s_pauseCheck = false;
	ResumeThread(m_decodeHandle);
}


void GxxDCContainer::SetImage(const wchar_t* strPath)
{

	//刷新旧的区域
	//if (bDraw)
	//{
	//	AfxInvalidateRect(&m_ActRect);
	//}

	if (!S_StartDecoding)
	{
		StartTimer(m_decodeTimer);
		m_isShowText = false;
	}

	S_lock.Lock();
	S_picToPath = strPath;
	S_StartDecoding = true;
	//PrePaly();
	S_lock.UnLock();

}

//void GxxDCContainer::SetStop(BOOL bDraw/* = TRUE*/)
//{
//	PhotoControl::Release();//释放图片
//	m_typePlayOk = PlayStop;
//	if (bDraw)
//	{
//		AfxInvalidateRect(&m_ActRect);
//	}
//}

void GxxDCContainer::Rotate()//旋转图片
{
	if (S_StartDecoding)
	{
		return ;
	}
	if (m_typePlayOk == PlayOk)
	{
		AfxInvalidateRect(&m_ActRect);
		PrePaly();
		PhotoControl::Rotate();
	}
}

void GxxDCContainer::Draw()
{

	//SkiaBitmapManager::GetInstance()->DrawColorToDevice(colBack,m_hDevice,&m_ActRect);
	if (S_StartDecoding)
	{
		COLORREF colBack = 0xFF000000 | (RGB(16,16,16));
		SkiaBitmapManager::GetInstance()->DrawColor(colBack,&m_ActRect);

		if (m_isShowText)
		{
			S_pText->DrawTextWithRect( *m_strDecode,m_ActRect);
		}
		return;
	}
	if (PlayErr == m_typePlayOk) 
	{
		const wstring *strError = LangStringManager::GetInstance()->getString("ID_FailurePic");//L"图片显示失败";
		m_showText->DrawTextWithRect(*strError,m_ActRect);
	}
	else if (PlayOk == m_typePlayOk) 
	{
		if (m_isFullScreen)
		{
			SkiaBitmapManager::GetInstance()->DrawImage(m_hDevice);
		}
		else
		{
			RECT rc;
			::SetRect(&rc,0,0,m_ActRect.right - m_ActRect.left, m_ActRect.bottom - m_ActRect.top);
			SkiaBitmapManager::GetInstance()->DrawImage(m_hDevice,&rc,&m_ActRect);
		}
	}
	else if (PlayStop == m_typePlayOk) 
	{
	}

	
}



GxxView* GxxDCContainer::CreateControl()
{
	return new GxxDCContainer;
}

void GxxDCContainer::PrePaly()
{
	RECT rc;
	::SetRect(&rc,0,0,m_ActRect.right -m_ActRect.left,m_ActRect.bottom - m_ActRect.top);
	FillRect(m_hDrawDC,&rc,m_hColor);	
}

bool GxxDCContainer::SetFullScreen( bool b )
{
	if (m_isFullScreen == b)
	{
		return true;
	}

	if (S_StartDecoding)//正在解码中
	{
		return false;
	}

	m_isFullScreen = b;
	if (b)
	{
		m_ActRect.left = 0;
		m_ActRect.top = 0;
		m_ActRect.right = AfxGetDevWidth();
		m_ActRect.bottom = AfxGetDevHeight();
	}
	else
	{
		m_ActRect = m_layoutRect;
	}

	if (m_typePlayOk == PlayOk)
	{
		PrePaly();
		PhotoControl::Draw();
		invalidateRect();
		AfxPostMessage(CTR_MESSAGE,(WPARAM)this,0);//重新计时
		//S_lock.Lock();
		//if (!S_picBackPath.empty())
		//{
		//	S_StartDecoding = true;
		//	S_picToPath =  S_picBackPath;
		//}
		//S_lock.UnLock();

		//StartTimer(m_decodeTimer);
		//m_isShowText = false;

		return true;
	}
	return false;
}

 CRect GxxDCContainer::getDcRect()
{
	CRect rc;
	::SetRect(&rc,0,0,m_ActRect.right - m_ActRect.left, m_ActRect.bottom - m_ActRect.top);
	return rc;
}



bool GxxDCContainer::s_pauseCheck = true;
 DWORD GxxDCContainer::DecodePicThread(LPVOID lpParam)
 {
	 GxxDCContainer * pAty = (GxxDCContainer *)lpParam;
	 while (1) 
	 {
		 if (S_StartDecoding)
		 { 
			 wstring pic_path;

			 S_lock.Lock();
			 bool b = S_picToPath.empty();
			 if (!b){
				 pic_path = S_picBackPath =  S_picToPath;
				 S_picToPath.clear();
			 }
			 else{
				 S_StartDecoding = false;//空目录不需要解码
			 }
			 S_lock.UnLock();

			if (b)//空目录不需要解码
			{
				continue;
			}

			pAty->DoSetImage(pic_path.c_str());
		 }
		 else
		 {
			 if (s_pauseCheck)
			 {
				 SuspendThread (pAty->m_decodeHandle);
			 }
			 Sleep(100);
		 }
	 }

	 return 0;
 }

 void GxxDCContainer::DoSetImage( const wchar_t* strPath )
 {
	 PrePaly();
	 if (PhotoControl::PlayFile(strPath))
	 {
		 m_typePlayOk = PlayOk;
	 }
	 else
	 {
		 m_typePlayOk = PlayErr;
	 }
	 AfxPostMessage(CTR_POST_PAINT,(WPARAM)this,0);
	 AfxPostMessage(CTR_MESSAGE,(WPARAM)this,0);
 }

 BOOL GxxDCContainer::Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam )
 {
	 switch( nMsg )
	 {
	 case CTR_POST_PAINT:
		 if ((GxxDCContainer *)wParam == this)
		 {
			 invalidateRect();
			 return TRUE;
		 }
		 return FALSE;
	 case WM_LBUTTONDOWN:
		 if (InMyArea( lParam ))
		 {
			 m_isBtnDown = true;
			 return TRUE;
		 }
		 return FALSE;
	 case WM_LBUTTONUP:
		 if (m_isBtnDown)
		 {
			 m_isBtnDown = false;
			 if (InMyArea(lParam))
			 {
				AfxPostMessage( CTR_MESSAGE, (WPARAM)this, MES_LBUTTONUP );
			 }
			 return TRUE;
		 }
		 return FALSE;
	 default:
		 return FALSE;
	 }
	return FALSE;
 }

 void GxxDCContainer::TimerTick( UINT nIDEvent )
 {
	StopTimer(m_decodeTimer);
	m_isShowText = true;
	invalidateRect();
 }





 RegisterHelp help("GxxDCContainer", GxxDCContainer::CreateControl);