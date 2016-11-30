#include "StdAfx.h"
#include "GxxProgressBar.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
// back_conver
//#include "aygshell.h"
#define  BACK_CONVER             "back_conver"
static RegisterHelp help("GxxProgressBar", GxxProgressBar::CreateControl);
GxxView* GxxProgressBar::CreateControl()
{
	return new GxxProgressBar;
}

GxxProgressBar::GxxProgressBar()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_handleBack = NULL;
	m_handleProgress = NULL;
	m_handleConver = NULL;
	iMax = 100;
	iMin = iPos = 0;
}

GxxProgressBar::~GxxProgressBar()
{

	if (m_handleBack!=NULL)
	{		
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleBack);
	}
	if (m_handleProgress!=NULL)
	{
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleProgress);
	}
	if (m_handleConver!=NULL)
	{
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleConver);
	}
}



void GxxProgressBar::Draw(  )
{
	//被按下为真
	if(m_handleBack)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleBack);
	}
	if(m_handleProgress)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleProgress,&m_ProRect);
	}
	if(m_handleConver)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleConver);
	}

}


BOOL GxxProgressBar::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	
	return FALSE;
}

void GxxProgressBar::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	setCtrRect(ele);
	
	int data =0;
	ele->Attribute(PROGRESS_SUM,&data);
	iMax = data;
	ASSERT(iMax > 0);

	ele->Attribute(PROGRESS_NUM,&data);
	GxxProgressBar::SetDisplayPos(data);	




	const char* pa = ele->Attribute(BACK_BMP);
	//string strTail;
	if (NULL!=pa)
	{
		m_handleBack = SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pa));
		SkiaBitmapManager::GetInstance()->SetRect(m_handleBack,&m_ActRect);
	}
	 
	
    pa = ele->Attribute(PROGRESS_BMP);
	if (NULL!=pa)
	{
		m_handleProgress =  SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pa));
		SkiaBitmapManager::GetInstance()->SetRect(m_handleProgress,&m_ProRect);
	}

	pa = ele->Attribute(BACK_CONVER);
	if (NULL!=pa)
	{
		m_handleConver =  SkiaBitmapManager::GetInstance()->InitImage(AfxAddWorkPathA(pa));
		//m_ActRect.top++;
		//m_ActRect.bottom++;
		SkiaBitmapManager::GetInstance()->SetRect(m_handleConver,&m_ActRect);
	}
	
}




void GxxProgressBar::SetDisplayPos( int n )
{
	//ASSERT(n >= 0);
	//ASSERT(n <= iMax);
	if(n <0 || n > iMax)	return;

	iPos = n;
	::SetRect(&m_ProRect,m_ActRect.left,m_ActRect.top, m_ActRect.left + (m_ActRect.right - m_ActRect.left)*iPos/iMax, m_ActRect.bottom);
	AfxInvalidateRect(&m_ActRect);
}

int GxxProgressBar::GetRatioNum()
{
	return iPos;
}

//设置滚动条数值范围
void GxxProgressBar::SetRange(int _iMin, int _iMax)
{
	if(_iMin < iMax)
	{
		iMin = _iMin;
		iMax = _iMax;
	}
	if (iMax == iMin)
	{
		iMax = iMin+100;
	}
}