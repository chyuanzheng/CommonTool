#include "StdAfx.h"
#include "GxxToolGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"

//
//#include "aygshell.h"





#define  TOOL_LOCAL  		 "layout\\app_tools.xml"
#define  TOOL_LOCAL_NO_B  		 "layout\\app_tools_no_bluetooth.xml"
GxxToolGroup::GxxToolGroup()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_handleback = NULL;
	m_bDownToUp = FALSE;
	m_bLock = FALSE;
	m_isBtnDown = false;
	setDraw(false);
}

GxxToolGroup::~GxxToolGroup()
{

	if (m_handleback!=NULL)
	{
		
		SkiaBitmapManager::GetInstance()->DeInitImage(m_handleback);
	}

	AnimationManage::GetInstance()->DeInitAniSet(m_hAni);
	deleteAllCtrls();
}



void GxxToolGroup::Draw( )
{



	if (NULL!=m_handleback)
	{
		SkiaBitmapManager::GetInstance()->DrawImage(m_handleback);
	}
}

BOOL GxxToolGroup::InMyArea( int x, int y )
{
	//判断区域
	POINT pt = {x,y};
	return ::PtInRect(&m_ActRect, pt);
}

BOOL GxxToolGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{  
	case WM_LBUTTONDOWN:
		if (!m_bLock&&m_bDownToUp)//在非主界面时，会事先响应toolgroup
		{
			m_isBtnDown = true;
			return TRUE;
		}
		return FALSE;

	case WM_LBUTTONUP:
		if (m_isBtnDown)
		{
			if( !InMyArea( LOWORD( lParam ), HIWORD( lParam )) )
			{
				startAnimation(!m_bDownToUp);
			}
			
			m_isBtnDown = false;
			return TRUE;
		}
		return FALSE;
	case CTR_ANIMATION_MES://MES_ANIMATION_END
		if (m_traAction == (AnimationAction*)wParam)
		{
			return AniationTraMsg(lParam);
		}
		else if (m_scaleAction == (AnimationAction*)wParam)
		{
			return AniationScaleMsg(lParam);
		}
		return FALSE;
	case CTR_TOOL_ANIMATION://MES_ANIMATION_END
	case MCU_POPMENU:
		startAnimation(!m_bDownToUp);
		return TRUE;
	case MCU_POPMENU_LONG:
		if (GxxAtButton::getEditMode())
		{
			AfxPostMessage(CTR_EXIT_EDIT_MODE,0,0);//先检查是否退出edit
		}
		else
		{
			Activity::startActivity(NULL,"MainPad");
		}
		
		return TRUE;
	default:
		return FALSE;
	}
}


BOOL GxxToolGroup::AniationTraMsg( UINT lp )
{
	if ( (ANIMATION_START == LOWORD(lp)) && FALSE == HIWORD(lp))//第一个动画结束 
	{
		setChildDraw(TRUE);
		return TRUE;
	}
	else if ( (ANIMATION_START == LOWORD(lp)) && TRUE == HIWORD(lp))
	{
		setChildDraw(FALSE);
		return TRUE;
	}
	return TRUE;
}


BOOL GxxToolGroup::AniationScaleMsg( UINT lp  )
{
	if ( (ANIMATION_END == LOWORD(lp)) && FALSE == HIWORD(lp))
	{
		setChildShowBtn(TRUE);
		AfxInvalidateRect(&m_ActRect);
		return TRUE;
	}
	else if ( (ANIMATION_END == LOWORD(lp)) && TRUE == HIWORD(lp))
	{
		setChildShowBtn(FALSE);
		return TRUE;
	}
	return TRUE;
}


void GxxToolGroup::setCtrLayout( TiXmlElement * ele )
{

	LoadAppTools();
	setCtrName(ele);
	setCtrRect(ele);

	string path;
	AfxGetWorkPathA(path);

	const char* pa = ele->Attribute(BACKGROUD);
	const char* strAni = ele->Attribute(ANIMATION);
	if (NULL!=pa)
	{
		m_handleback =  SkiaBitmapManager::GetInstance()->InitImage((path + string(pa)).c_str());
		SkiaBitmapManager::GetInstance()->SetRect(m_handleback,&m_ActRect);
	}

	TiXmlElement * chid = ele->FirstChildElement();
	string ctrname;
	GxxToolButton *ctr;
	int i=0;
	while(chid&&i<SIZE_TOOL_APP)
	{
		ctrname = chid->Value();

		if (ctrname == GXXTOOLBUTTON)
		{
			ctr = new GxxToolButton(m_nth[i]);
		}
        ASSERT(NULL!=ctr);
		if (ctr)
		{
			AddCtrl(ctr);
			ctr->setCtrLayout(chid);
		}
		chid = chid->NextSiblingElement();
		i++;
	}
	
	setChildShowBtn(FALSE);
	setChildDraw(FALSE);

	AfxGetWorkPathA(path);
	ASSERT(NULL!=strAni);

	m_hAni= AnimationManage::GetInstance()->InitAniSet((path + string(strAni)).c_str());
	SetUpAni();
	GxxAtButton::SetToolGroup(this);
}

//给tools加载app的序号位置，放在m_nth数组中
void GxxToolGroup::LoadAppTools()
{

	if (!Activity::s_bluetooth_exist)
	{
		m_toolLocal  = AfxAddWorkPathA(TOOL_LOCAL_NO_B);
	}
	else
	{
		m_toolLocal  = AfxAddWorkPathA(TOOL_LOCAL);
	}

	ASSERT(m_toolLocal.size()>0);


	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);

	bool ret = xmlDoc->LoadFile(m_toolLocal.c_str());
	if(!ret)//不成功则启用备份档案
	{
		string path = m_toolLocal +  ".back";
		bool ret_backup = xmlDoc->LoadFile( path.c_str());
		ASSERT(ret_backup);// 备份档案 必须保证成功
		//return false;
	}

	TiXmlElement *ele = xmlDoc->RootElement();


	const CHAR * ctrname = NULL;
	int i=0;
	while(ele&&i<SIZE_TOOL_APP)
	{
		ctrname = ele->Value();
		if (NULL==ctrname || strcmp(ctrname,"AppTool")!= 0)
		{
			ret = false;
			break;
		}

		int data =0;
		ele->Attribute(NTH_APP,&data);
		m_nth[i]=data;
		ele = ele->NextSiblingElement();
		i++;
	}
	
	ASSERT(SIZE_TOOL_APP==i);

	//if (!ret)
	//{
	//	i=0;
	//	while(i<SIZE_TOOL_APP)
	//	{
	//		m_nth[i]=i;
	//		i++;
	//	}
	//	return;
	//}

}

void GxxToolGroup::WriteToolBtnLayout()
{
	try
	{
		auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);//
		
		for (ControlList::iterator pos = m_pCtrlVet->begin(); pos != m_pCtrlVet->end(); ++pos)
		{
			TiXmlElement *eleBtn = new TiXmlElement("AppTool");
			xmlDoc->LinkEndChild(eleBtn);

			int nth = ((GxxToolButton*)(*pos))->getNth();
			eleBtn->SetAttribute(NTH_APP, nth);	
		}
		xmlDoc->SaveFile( m_toolLocal.c_str());
	}
	catch (string& )
	{
		return;
	}
	return;
}

void GxxToolGroup::startAnimation(BOOL up)
{
	if (m_bLock)
	{
		return;
	}
	if (m_bDownToUp == up)
	{
		return;
	}
	setDraw(true);
	if (AnimationManage::GetInstance()->IsInAction(m_hAni))
	{
		AnimationManage::GetInstance()->setDirect(m_hAni,m_bDownToUp);
		m_bDownToUp = !m_bDownToUp;
		return;
	}
	
	AnimationManage::GetInstance()->setDirect(m_hAni,!up );
	AnimationManage::GetInstance()->StartAction(m_hAni);
	m_bDownToUp = up;
}

void GxxToolGroup::setChildDraw(BOOL e)
{
	setDraw(e);
	//ControlList::iterator pos;  //*m_pCtrlVet;//所有子控件
	//for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	//{
	//	(*pos)->setDraw(e);
	//}		
}
void GxxToolGroup::setChildShowBtn( BOOL e )
{
	ControlList::iterator pos;  //*m_pCtrlVet;//所有子控件
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		( (GxxToolButton*)(*pos))->showButton(e);
	}	
}

void GxxToolGroup::SetUpAni()
{
		m_traAction = AnimationManage::GetInstance()->GetAction(m_hAni,"tool_tra");//new AnimationAction();
		ASSERT(NULL!=m_traAction);
		ASSERT(NULL!=m_handleback);

		m_traAction->AddHandle(m_handleback);//添加句柄
		m_traAction->SetAniRect(m_ActRect);//使之刷新的区域


		m_scaleAction = AnimationManage::GetInstance()->GetAction(m_hAni,"tool_scale");//new AnimationAction()
		ASSERT(NULL!=m_scaleAction);

		ControlList::iterator pos;  //*m_pCtrlVet;//所有子控件
		for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
		{
			HANDLE h = ((GxxToolButton*)(*pos))->getAniHandle();		
			m_scaleAction->AddHandle(h);//添加句柄
			m_traAction->AddHandle(h);

		}

		m_scaleAction->SetAniRect(m_ActRect);//使之刷新的区域
		//m_scaleAction->setDuration(300);
}



bool GxxToolGroup::ModuleInGroup(  T_AppModule *m)
{
	//throw std::exception("The method or operation is not implemented.");
	ControlList::iterator pos;
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		if ( ( (GxxToolButton *)(*pos))->getBtnModule() == m)
		{
			return true;
		}
	}
	return false;	
}


void GxxToolGroup::MoveSetModule( GxxToolButton * btn, T_AppModule * module )
{
	if ( !ModuleInGroup(module))
	{
		btn->renewModule(module);
	}
}

void GxxToolGroup::MoveExchangeModule( GxxToolButton * a, GxxToolButton * b )
{
	T_AppModule *am = a->getBtnModule();
	T_AppModule *bm = b->getBtnModule();
	a->renewModule(bm);
	b->renewModule(am);
}

void GxxToolGroup::resetToFactory()
{
	ControlList::iterator pos;
	int i=0;
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();++pos,++i)
	{
		( (GxxToolButton *)(*pos))->renewModule(AppManage::GetInstance()->GetModule(i));
	}
	WriteToolBtnLayout();
}



