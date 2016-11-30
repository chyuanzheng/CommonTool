#include "StdAfx.h"
#include "Activity.h"
#include "StrHelp.h"
//#include "Launch.h"
#include "XmlDef.h"
//#include "aygshell.h"
#include "GxxToolButton.h"
#include "SkiaBitmapManager.h"
#include "GxxToolGroup.h"
#include "GXCreateControls.h"
#include "GxxAppGroup.h"
#include "GxxCommonCtr.h"
#include "AppManage.h"
#include "VersionXml.h"
#include "../HardwareDll/WMMsg.h"
#include "GXNotify.h"

/////////////////////////////////////////////////////////////////////////
// BaseBoard message map and member functions
bool   Activity::s_isAccOff = false;
HANDLE Activity::s_hAniScaleUp = NULL;
HANDLE Activity::s_hAniScaleDown = NULL;
HANDLE Activity::s_hAniApha = NULL;
HANDLE Activity::s_hAniRotateY = NULL;

TMapStr_Str Activity::S_ActivityDllContainer;
Activity * Activity::s_popup_active = NULL;
Activity * Activity::s_active = NULL;
Activity * Activity::s_preAct = NULL;
Activity * Activity::s_fuctionAct  = NULL;
AnimationAction *  Activity::s_bottomAction = NULL;
AnimationAction *  Activity::s_topAction = NULL;
Activity::T_TRASIT Activity::s_bInTransition = Activity::T_OK_USE;

HANDLE    Activity::s_handleBtpTrasitBottom = NULL;//退出动画
HANDLE    Activity::s_handleBtpTrasitTop = NULL;//进入动画

TMapStr_Int Activity::s_int_content;
TMapStr_Str Activity::s_str_content;

TMapStr_Activity Activity::s_allActivity= TMapStr_Activity();
UINT Activity::s_backColor = 0;
bool Activity::m_bPermitStart = true;
bool Activity::m_bBrake = true;
bool Activity::m_bInSetupNotOperate = false;

Activity *Activity::S_testMain = NULL;

bool Activity::s_bluetooth_exist = false;
bool Activity::s_is_init_sound = true;

bool   Activity::S_isPowerInLanguage=true;

Activity::Activity()
{
	m_isMainPad = false;
	m_pPreActivity=NULL ;
	m_pNextActiviy=NULL;
	//m_pbackColor = NULL;
	m_bShowBottom = m_bShowTop = FALSE;

	if (NULL == s_hAniScaleUp)
	{
		s_hAniScaleUp = AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA ("\\layout\\AniActivityScaleUp.xml"));
		s_hAniScaleDown = AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA ("\\layout\\AniActivityScaleDown.xml") );
		s_hAniApha  = AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA("\\layout\\AniActivityAlpha.xml"));
		s_hAniRotateY  = AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA("\\layout\\AniActivityRotateY.xml"));
	}
	ASSERT(NULL!=s_hAniScaleUp && NULL!=s_hAniScaleDown && NULL!=s_hAniApha);

}


Activity::~Activity ()
{

	//if (NULL!=m_pbackColor)
	//{
	//	delete m_pbackColor;
	//}
}




void Activity::Draw( )
{
	static bool b = true;
	if (b)
	{
		//AfxPostMessage(CTR_START_ALL_MODULE,0,0);
		//if (Activity::s_is_init_sound )
		//{
		//	AfxPostMessage(CTR_INIT_MUTE,0,0);//发消息通知设置声音，1表示只更新
		//}
		b = false;
	}

	//pImageManager->DrawAlphaImage(m_handleBack,hdcDst,NULL,&m_ActRect);
	ASSERT (0!=Activity::s_backColor);
	if (!m_isMainPad/*&&NULL!=getPicHandle()*/)
	{
		SkiaBitmapManager::GetInstance()->DrawColor(Activity::s_backColor,&AfxGetDcRect());
	}
	
	GxxPicture::Draw();
	

}



BOOL Activity::setContentView( const CHAR* layout )
{
	BOOL ret = FALSE;
	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	ret = xmlDoc->LoadFile(AfxAddWorkPathA(layout));
	if (!ret)
	{
		OutputDebugString(L"setContentView LoadFile error! \r\n");
		ASSERT(0);
		return FALSE;
	}
	
	TiXmlElement *root = xmlDoc->RootElement();
	if (strcmp(root->Value(), ABSOLUTE) != 0)
	{
		ASSERT(0);
		return FALSE;
	}

	setCtrName(root);
	setCtrRect(root);
	setPicHandle(root,BACKGROUD);
	bindHandleRect();



	TiXmlElement * chid = root->FirstChildElement();
	setCtrList(chid);

	return TRUE;
}


/**控件根据 ele中的参数设置自己的属性
   并递归设置子控件
*/




//这里并不删除activity
bool Activity::finish()
{
	//AfxFinishActiviy(this);
	//m_pLater = NULL;
	if(NULL==m_pPreActivity)
	{
		return false;
	}
	//if (m_pPreActivity == Activity::s_fuctionAct)
	//{
	//	RetToFucActivity();//这里为了不改变功能模块的参数
	//	return true;
	//}
	
	ASSERT(this == Activity::s_active);
	if (DoTransiteActivity(m_pPreActivity,NULL,"finish",true))
	{
		defaultPendingTransition();
	}
	return true;
}
void Activity::RetToFucActivity()
{
	//if(Activity::s_fuctionAct==m_pPreActivity)
	//{
	//	finish();
	//	return;
	//}
	if (Activity::s_fuctionAct != NULL)
	{
		if (DoTransiteActivity(Activity::s_fuctionAct,NULL,Activity::s_fuctionAct->m_param,true))
		{
			defaultPendingTransition();
		}

	}
}


void Activity::startPopupActivity( const string& tostart )
{
	Activity * Act = findActivity(tostart);	
	ASSERT(NULL!=Act);
	s_popup_active = Act;
	AfxShowPopupWnd(true);
	//AfxInvalidateRect(NULL);
	AfxInvalidatePopupRect(NULL);
}

Activity * Activity::startActivity( Activity *pActActivity,const string& tostart ,const string& param_id/*= ""*/ )
{
	if (!Activity::m_bPermitStart)
	{
		return NULL;
	}
	if (Activity::s_bInTransition == T_OK_USE  && transiteActivity(tostart, pActActivity, param_id))
	{
		defaultPendingTransition();
	}
	
	m_bInSetupNotOperate = false;

	return Activity::s_active;

}
bool Activity::transiteActivity( const string &tostart, Activity * pActActivity, const string& param_id )
{
	if (tostart.size()==0)
	{
		return false;
	}
	Activity * pModuleAct = findActivity(tostart);	
	return DoTransiteActivity(pModuleAct, pActActivity, param_id);

}



Activity * Activity::findActivity( const string& tostart)
{

	TMapStr_Activity::iterator pos;
	for (pos=s_allActivity.begin(); pos!=s_allActivity.end();++pos)
	{
		if (tostart==(*pos).first)
		{
			break;
		}
	}

	if (pos == s_allActivity.end())
	{
		Activity * pAct =GXCreateControl::CreateAcitviyByType(tostart.c_str());
		ASSERT(NULL!=pAct);
		pAct->m_strActivityName = tostart;
		pAct->onCreate();
		s_allActivity.insert(std::make_pair(tostart,pAct));
		AppManage::GetInstance()->SetActivity(tostart,pAct);
		return pAct;
	} 
	else
	{
		return pos->second;
	}
}

void Activity::renewParent()
{
	ControlList::iterator pos;
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		(*pos)->setParentView(this);
	}
}

void Activity::setBackColor(UINT color)
{
	return;//这个函数不再使用。

	//if (NULL == m_pbackColor)
	//{
	//	m_pbackColor = new UINT;
	//}
	//*m_pbackColor = color;
}

void Activity::overridePendingTransition( GxxView *topView,GxxView *bottomView,HANDLE hAni_handle )
{
	AfxInvalidateRect(NULL);
	if (NULL == topView || NULL == bottomView)
	{
		return;
	}
	if (hAni_handle==NULL)
	{
		//ASSERT(0);
		hAni_handle=Activity::s_hAniApha;
	}
	//ASSERT(NULL!=hAni_handle);
	RECT rect = AfxGetDcRect();
	ASSERT (NULL ==  Activity::s_handleBtpTrasitTop && NULL == Activity::s_handleBtpTrasitBottom);

	//const RECT &top_rect = topView->getCtrRect();
	//const RECT &bottom_rect = bottomView->getCtrRect();
	Activity::s_handleBtpTrasitTop = SkiaBitmapManager::GetInstance()->InitImage(&rect);
	Activity::s_handleBtpTrasitBottom = SkiaBitmapManager::GetInstance()->InitImage(&rect);

	SkiaBitmapManager::GetInstance()->SetRect(Activity::s_handleBtpTrasitTop,&rect);
	SkiaBitmapManager::GetInstance()->SetRect(Activity::s_handleBtpTrasitBottom,&rect);

	setSelView(GxxCommonCtr::s_commonCtrl);//让公共控件被选中

	//topView->setMoveRect(-top_rect.left,-top_rect.top);
	//bottomView->setMoveRect(-bottom_rect.left,-bottom_rect.top);
	SkiaBitmapManager::GetInstance()->setActivityScreen(topView, Activity::s_handleBtpTrasitTop);//上面
	SkiaBitmapManager::GetInstance()->setActivityScreen(bottomView,Activity::s_handleBtpTrasitBottom);
	//topView->setMoveRect( top_rect.left,top_rect.top);
	//bottomView->setMoveRect( bottom_rect.left, bottom_rect.top);


	Activity::s_topAction =  AnimationManage::GetInstance()->GetAction(hAni_handle,"top");
	ASSERT(NULL!=Activity::s_topAction);
	if (NULL!=Activity::s_topAction)
	{
		Activity::s_topAction->ClearHandles();
		Activity::s_topAction->SetAniRect(rect);
		Activity::s_topAction->AddHandle(Activity::s_handleBtpTrasitTop);
	}

	Activity::s_bottomAction =  AnimationManage::GetInstance()->GetAction(hAni_handle,"bottom");
	ASSERT(NULL!=Activity::s_bottomAction);
	if (NULL!=Activity::s_bottomAction)
	{
		Activity::s_bottomAction->ClearHandles();
		Activity::s_bottomAction->SetAniRect(rect);
		Activity::s_bottomAction->AddHandle(Activity::s_handleBtpTrasitBottom);
	}
	AnimationManage::GetInstance()->setDirect(hAni_handle,FALSE);
	AnimationManage::GetInstance()->StartAction(hAni_handle);

	
	Activity::s_active->setEnable(FALSE);//禁止按键
	Activity::s_bInTransition = T_DRAW_TRASITION;
}



void Activity::Paint()
{
	if (T_DRAW_TRASITION == s_bInTransition)
	{
		//RECT rect = AfxGetDcRect();
		SkiaBitmapManager::GetInstance()->DrawColor(0xff000000,&AfxGetDcRect());
		ASSERT(s_handleBtpTrasitBottom && s_handleBtpTrasitTop);
		SkiaBitmapManager::GetInstance()->DrawImage(s_handleBtpTrasitBottom);
		SkiaBitmapManager::GetInstance()->DrawImage(s_handleBtpTrasitTop);	
	}
	else
	{
		GxxView::Paint();
	}
}

void Activity::EnableActivity( const string &actName,bool b_enable )
{
	if (!b_enable && Activity::s_fuctionAct!=NULL && Activity::s_fuctionAct->m_strActivityName == actName)
	{
		Activity::s_fuctionAct = NULL;
	}
	AppManage::GetInstance()->SetAppEnable(actName,b_enable);//设置正在运行
	AfxInvalidateRect(NULL);
}



BOOL Activity::DealActivityMsg( UINT nMsg, WPARAM wParam, LPARAM lParam )//ANIMATION_START
{
	switch(nMsg)
	{
	case  CTR_DVD_ENABLE_OR_NOT:
		Activity::EnableActivity("DiscActivity",(bool)wParam);
		return TRUE;
	case  CTR_EXIT_DVD_INTERFACE:
		startActivity(NULL,"MainPad");
		Activity::EnableActivity("DiscActivity",false);
		return TRUE;
	case CTR_INTO_DVD_INTERFACE:
		startActivity(NULL ,"DiscActivity");
		return TRUE;
	case  CTR_INTO_MAIN_INTERFACE:
		startActivity(NULL,"MainPad");
		return TRUE;
	case  CTR_START_ALL_MODULE:
		StartAllModule();
		// 发送信息,主动判断手刹状态,解决开机手刹状态无效问题
		::PostMessage(AfxGetHWND(), WM_MCUINT, 26, 0);
		return TRUE;
	default:
		break;
	}
	if (T_OK_USE == s_bInTransition)
	{
		return FALSE;
	}
	switch( nMsg )
	{  
	case CTR_ANIMATION_MES://MES_ANIMATION_END 
		if ( Activity::s_topAction == (AnimationAction*)wParam )
		{
			if ( (ANIMATION_END == LOWORD(lParam)))//第一个动画结束 
			{
				m_bShowTop = FALSE;
				Activity::s_topAction = NULL;
				CheckTransitionStatus();
				return TRUE;
			}
			else if ( ANIMATION_START == LOWORD(lParam)) 
			{
				m_bShowTop = TRUE;
			}
		}
		else if ( Activity::s_bottomAction == (AnimationAction*)wParam)
		{
			if ( (ANIMATION_END == LOWORD(lParam)))//第一个动画结束 
			{
				m_bShowBottom = FALSE;
				Activity::s_bottomAction = NULL;
				CheckTransitionStatus();
				return TRUE;
			}
			else if ( ANIMATION_START == LOWORD(lParam)) 
			{
				m_bShowBottom = TRUE;
			}
		}
		return FALSE;


/*	case CTR_ALL_ANIMATION_END://所有动画结束的时候 这里依赖于消息的顺序
		//if (T_NEED_ENABLE == s_bInTransition)
		//{
		//	
		//	//setSelView(NULL);
		//	//s_bInTransition = T_OK_USE;
		//	//Activity::s_active->setEnable(TRUE);
		//	return TRUE;
		//}
		return TRUE;	
		*/
	default:
		return FALSE;
	}
	return FALSE;
}

void Activity::onStop()
{
	return;
}

void Activity::defaultPendingTransition()
{
	if (!Activity::s_active->GetAnimation() )
	{
		AfxInvalidateRect(NULL);
		Activity::s_active->onStart();
		return;
	}
	if (Activity::s_preAct && !Activity::s_preAct->GetAnimation() )
	{
		AfxInvalidateRect(NULL);
		Activity::s_active->onStart();
		return;
	}
	if (Activity::s_active->getCtrName() == "main_pad")
	{
		overridePendingTransition(Activity::s_preAct,Activity::s_active,Activity::s_hAniScaleDown);
	}
	else if (Activity::s_preAct!=NULL)
	{
		if (Activity::s_preAct->getCtrName()== "main_pad")
		{
			overridePendingTransition(Activity::s_active,Activity::s_preAct,Activity::s_hAniScaleUp);
		}
		else
		{
			overridePendingTransition(Activity::s_preAct,Activity::s_active,Activity::s_hAniApha);
		}
	}

}

void Activity::CheckTransitionStatus()
{
	if (NULL==Activity::s_bottomAction && NULL==Activity::s_topAction)
	{
		s_bInTransition = T_NEED_ENABLE;

		setSelView(NULL);
		s_bInTransition = T_OK_USE;
		Activity::s_active->setEnable(TRUE);

		SkiaBitmapManager::GetInstance()->DeInitImage(Activity::s_handleBtpTrasitTop);
		SkiaBitmapManager::GetInstance()->DeInitImage(Activity::s_handleBtpTrasitBottom);
		Activity::s_handleBtpTrasitTop=Activity::s_handleBtpTrasitBottom=NULL;
		onStart();
	}
}

bool Activity::DoTransiteActivity( Activity * pModuleAct, Activity * pActActivity, const string& param_id,bool bforce )
{
	Activity *pToStartAct = pModuleAct;
	ASSERT (NULL!=pModuleAct);

	if (NULL==pActActivity)
	{
		if (!bforce && Activity::s_active!= NULL)//bforce = true 强制切换，不需要检查,false则需要检查
		{
			Activity *cur_prest = Activity::s_active;
			do
			{
				if (cur_prest == pToStartAct)
				{
					return false;
				}
				cur_prest = cur_prest->m_pPreActivity;
			}while(cur_prest!= NULL);

		}

		if (Activity::s_active == pToStartAct && Activity::s_active->m_param == param_id)
		{
			return false;
		}
		if (param_id!="finish")
		{
			pToStartAct->m_pPreActivity = NULL;
		}
		pToStartAct->m_pNextActiviy = NULL;//需要启动的没有前后 Activity
	}
	else 
	{
		pActActivity->m_pNextActiviy = pToStartAct;
		pToStartAct->m_pPreActivity = pActActivity;
	}


	//pModuleAct=pToStartAct;

	Activity::s_preAct = Activity::s_active;
	Activity::s_active = pToStartAct;
	Activity::s_active->m_param = param_id;//注意参数可能被finish改变。
	if (NULL!=Activity::s_preAct)//暂停以前的Activity
	{
		Activity::s_preAct->setPause();
	}
	if (NULL==pActActivity && param_id!="finish")//检查是否启动新的功能模块
	{
		if (pModuleAct->getCtrName() != "main_pad" && pModuleAct->getCtrName()  != "setup_pad" && pModuleAct->getCtrName()  != "navi_pad" )//
		{

			if (NULL!=Activity::s_fuctionAct && Activity::s_fuctionAct != pModuleAct)
			{
				Activity::s_fuctionAct->onStop();
			}
			Activity::s_fuctionAct=pModuleAct;
			AppManage::GetInstance()->SetAppPlaying(Activity::s_fuctionAct->m_strActivityName,Activity::s_fuctionAct->m_param);//设置正在运行
		}

#ifdef _DEBUG
		if (S_testMain&&pModuleAct->getCtrName()  != "setup_pad")
		{
			S_testMain->TranslateMessage(TEST_ACTIVITY,(WPARAM)pModuleAct, 0);
		}
#endif

	}

	Activity::s_active->setResume();//开始现在的Activity
	Activity::s_active->renewParent();

	Activity::s_int_content.clear();//删除参数
	Activity::s_str_content.clear();
	return true;
}

void Activity::SetContentInt( const string &name,int n )
{
	s_int_content[name] = n;
}

void Activity::SetContentStr( const string &name,const string &s )
{
	s_str_content[name] = s;
}

bool Activity::GetContentInt( const string &name,int &n )
{
	TMapStr_Int::iterator pos = s_int_content.find(name);
	if (pos!=s_int_content.end())
	{
		n=pos->second;
		return true;
	}
	return false;
}

bool Activity::GetContentStr( const string &name,string &s )
{
	TMapStr_Str::iterator pos = s_str_content.find(name);
	if (pos!=s_str_content.end())
	{
		s=pos->second;
		return true;
	}
	return false;
}

void Activity::SetBrake( bool b )
{
	m_bBrake = b;
	if(!m_bBrake)
	{
		Activity *pFirst = s_active;
		while( NULL != pFirst->m_pPreActivity )
		{
			pFirst = pFirst->m_pPreActivity;
		}
		if (pFirst->getCtrName() == "setup_pad")
		{
			//startActivity(NULL,"MainPad");
			RECT rc;
			::SetRect(&rc,220,15,620,55);
			AfxMessageBox("operation_drive_31",-1,&rc);
			m_bInSetupNotOperate = true;
		}
	}
	else
	{
		AfxMessageBox("operation_drive_31",0,NULL);
		m_bInSetupNotOperate = false;
	}

}


void Activity::failedStart( const string& tostart )
{
	if (!m_bBrake)
	{
		if (tostart == "SetupActivity")
		{
			RECT rc;
			::SetRect(&rc,220,15,620,55);
			AfxMessageBox("operation_drive_31",3,&rc);
		}
	}
}

void Activity::AddActivityDll( const string & act,const string & dll )
{
	S_ActivityDllContainer.insert(std::make_pair(act,dll));
}

void Activity::loadDllModule( const char * strName, const char * strActivity )
{
	string dll_path = AfxAddWorkPathA (strName) + string(".dll") ;//work_path+elename+".dll";
	wstring wdll_path = StrHelp::StringToWString(dll_path);
	LoadLibrary(wdll_path.c_str());
	if (strActivity!=NULL)
	{
		Activity::findActivity(string(strActivity));
	}
}

void Activity::StartAllModule()
{
	for (TMapStr_Str::iterator pos = S_ActivityDllContainer.begin(); pos != S_ActivityDllContainer.end(); ++pos)
	{
		loadDllModule(pos->second.c_str(),pos->first.c_str());
	}
	S_ActivityDllContainer.clear();

	if (!s_isAccOff)
	{
		GXNotify::SendNotifyAsync(AfxGetHWND(),"restore_factory_set", 0, 0);
	}

	AfxMessageBox("wait_app_31",0);//去掉对话框
}

void Activity::CheckAccOff()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	s_isAccOff = false;
	if (systime.wYear > 2013)
	{
		s_isAccOff = true;
	}
	else if (systime.wYear == 2013 )
	{
		if (systime.wMonth >= 9)
		{
			s_isAccOff = true;
		}
	}

	if (s_isAccOff)
	{
		Activity::S_isPowerInLanguage = false;
	}
	Activity::s_bluetooth_exist = ( VersionXml::GetInstance()->GetBtModule() == VersionXml::BT_Module_Added );
}

