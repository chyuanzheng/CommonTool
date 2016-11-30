#include "StdAfx.h"
#include "GxxButtonTest.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GxxVedioSetup.h"
//
//#include "aygshell.h"
static RegisterHelp help("GxxButtonTest", GxxButtonTest::CreateControl);
GxxView* GxxButtonTest::CreateControl()
{
	return new GxxButtonTest;
}
GxxButtonTest::GxxButtonTest()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_handleUp = NULL;
	m_isGxxButtonDown = FALSE;
	m_setupV = NULL;
}

GxxButtonTest::~GxxButtonTest()
{
	if (m_handleUp!=NULL)
	{
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleUp);
	}
}



void GxxButtonTest::Draw(  )
{
	
	if( m_isGxxButtonDown == TRUE )
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleUp,&m_ActRect,80);//80
		
	}
	else 
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleUp);
		
	}

}

BOOL GxxButtonTest::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL GxxButtonTest::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
		{	
			//::SetCapture( m_hWnd );
			m_isGxxButtonDown = TRUE;
			//AfxInvalidateRect(&m_ActRect);
			//m_time = GetTickCount();
			return TRUE;
		}
		return FALSE;
	//case WM_MOUSEMOVE:
	//	if ( m_isGxxButtonDown &&  InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
	//	{
	//		if (GetTickCount() - m_time >500)
	//		{
	//			Activity::startActivity(NULL,"MainPad");
	//			m_isGxxButtonDown = FALSE;
	//			AfxInvalidateRect(&m_ActRect);
	//		}
	//		return TRUE;
	//	}
	//	return FALSE;
	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( m_isGxxButtonDown  )
		{
			//::ReleaseCapture();
			m_isGxxButtonDown = FALSE;
			
			if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
			{
#if _DEBUG
				//if (m_setupV==NULL)
				//{
				//	m_setupV = (GxxVedioSetup *)Activity::findActivity("MainPad")->safeFindViewByName("setup_fun");
				//}
				//m_setupV->OpenVedioSetup();
				//PROCESS_INFORMATION pi;
				//CreateProcess(_T("\\windows\\explorer.exe"), NULL, NULL, NULL, 0, 0, NULL, NULL, NULL, &pi);
				//AfxPostMessage(WM_CLOSE,0,0);
				//DestroyWindow(AfxGetHWND());
	//exit(0);
				
	return TRUE;
#else

#endif

				//if (getCtrName() == "test_btn")
				//{
				//	AfxPostMessage( CTR_TOOL_ANIMATION, 0, 0 );
				//}
			}
			//AfxInvalidateRect(&m_ActRect);
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
	return FALSE;
}

void GxxButtonTest::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);

	string path;
	AfxGetWorkPathA(path);

	const char* pa = ele->Attribute(BTN_UP);
	//string strTail;
	if (NULL!=pa)
	{
		m_handleUp = SkiaBitmapManager::GetInstance()->InitImage((path + string(pa)).c_str());
		SkiaBitmapManager::GetInstance()->SetRect(m_handleUp,&m_ActRect);
	}
}


