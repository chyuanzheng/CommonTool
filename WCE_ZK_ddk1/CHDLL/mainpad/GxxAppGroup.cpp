#include "StdAfx.h"
#include "GxxAppGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"
#include "ControlHelp.h"
#include "GxxRationPage.h"
#include "AppManage.h"

#define  APP_LOCAL  		 "app_local"
#define  APP_LOCAL_NO_B  		 "app_local_no_bluetooth"

struct T_MarginI
{
	int  x_margin;
	int  y_margin;
	int  x_interval;
	int  y_interval;

};

static RegisterHelp help("GxxAppGroup", GxxAppGroup::CreateControl);
GxxView* GxxAppGroup::CreateControl()
{
	return new GxxAppGroup;
}


#define  ANIMATION_MOVE  80

GxxAppGroup::GxxAppGroup()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	m_isGxxButtonDown = FALSE;
	setOnlyDrawActRect(true);
	//GxxAtButton::m_app_group = this;
}



GxxAppGroup::~GxxAppGroup()
{
	ASSERT(m_hAni!=NULL);
	AnimationManage::GetInstance()->DeInitAniSet(m_hAni);
}

void GxxAppGroup::Draw(  )
{
	if (AnimationManage::GetInstance()->IsInAction(m_hAni))
	{

		//AnimationManage::GetInstance()->setDirect(m_hAni,m_bDownToUp);
		//m_bDownToUp = !m_bDownToUp;
		int xmove = (int)m_AniCurToRight->getTranXValue();
		if (!AnimationManage::GetInstance()->getDirect(m_hAni))//向右移动
		{
			m_fromCurPage->SetXmove(xmove);
			m_toCurPage->SetXmove(xmove-(m_ActRect.right-m_ActRect.left));
		}
		else//向左移动
		{
			m_toCurPage->SetXmove(xmove);
			m_fromCurPage->SetXmove(xmove-(m_ActRect.right-m_ActRect.left));
		}		

		return;
	}
	(*m_pagepos)->SetXmove(0);
}



BOOL GxxAppGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	switch( nMsg )//
	{
	case CTR_APP_LEFT_MODE:
		if (checkPostPage((GxxView*)wParam))
		{
			startRightAnimation(false);
		}	
		return TRUE;
	case CTR_APP_RIGHT_MODE:
		if (checkPrePage((GxxView*)wParam))
		{
			startRightAnimation(true);
		}
		return TRUE;
	case CTR_ANIMATION_MES://MES_ANIMATION_END  MAKELONG
		if (m_ActionCurToRight == (AnimationAction*)wParam)
		{
			if ( (ANIMATION_END == LOWORD( lParam )&&FALSE==HIWORD( lParam ))
				||( ANIMATION_START == LOWORD( lParam )&&TRUE==HIWORD( lParam )) )
			{
				ReLoadCtrls();
				SetPosRation();
				(*m_pagepos)->setEnable(TRUE);
				AfxInvalidateRect(NULL);
			}
			
		}
		return FALSE;

	case WM_LBUTTONDOWN://这里动画的时候运行按键
		if( InMyArea( LOWORD( lParam ), 240) )
		{	
			//::SetCapture( m_hWnd );
			m_xMove = LOWORD( lParam );
			m_isGxxButtonDown = TRUE;
			return TRUE;
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if( m_isGxxButtonDown )
		{	
			int n_move = LOWORD( lParam ) - m_xMove;
			if (n_move > ANIMATION_MOVE)
			{
				m_isGxxButtonDown = FALSE;
				startRightAnimation(TRUE);
				return TRUE;
			}
			if (n_move<-ANIMATION_MOVE)
			{
				m_isGxxButtonDown = FALSE;
				startRightAnimation(FALSE);
				return TRUE;
			}
			//::SetCapture( m_hWnd );
			
		}
		return FALSE;
	case WM_LBUTTONUP:
		if( m_isGxxButtonDown )
		{
			m_isGxxButtonDown = FALSE;
		}
		return FALSE;
	default:
		return FALSE;
	}
}

void GxxAppGroup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);

	
	RECT editRect;

	int nleft,ntop,nwidth,nheight;
	ele->Attribute(LAYOUT_X_E,&nleft);
	ele->Attribute(LAYOUT_Y_E,&ntop);
	ele->Attribute(LAYOUT_WIDTH_E,&nwidth);
	ele->Attribute(LAYOUT_HEIGHT_E,&nheight);
	SetRect(&editRect,nleft,ntop,nleft+nwidth,ntop+nheight);


	T_MarginI  actMI;
	T_MarginI  editMI;

	ele->Attribute(X_MARGIN,&actMI.x_margin);
	ele->Attribute(Y_MARGIN,&actMI.y_margin);
	ele->Attribute(X_INTERVAL,&actMI.x_interval);
	ele->Attribute(Y_INTERVAL,&actMI.y_interval);

	ele->Attribute(X_MARGIN_E,&editMI.x_margin);
	ele->Attribute(Y_MARGIN_E,&editMI.y_margin);
	ele->Attribute(X_INTERVAL_E,&editMI.x_interval);
	ele->Attribute(Y_INTERVAL_E,&editMI.y_interval);

	ComputeRect(m_ActRect,actMI,GxxAppButton::m_pageActRect);
	ComputeRect(editRect,editMI,GxxAppButton::m_pageEditRect);


	int r_width;
	ele->Attribute(PAGEL_X,&nleft);
	ele->Attribute(PAGEL_Y,&ntop);
	ele->Attribute(PAGEL_WIDTH,&nwidth);
	ele->Attribute(PAGEL_HEIGHT,&nheight);
	ele->Attribute(PAGE_LINE_HEIGHT,&r_width);

	GxxAppPage::SetLineRect(nleft,ntop,nwidth,nheight,r_width);


	const char* pa = ele->Attribute(PAGELINE);
	GxxAppPage::m_handleLine = SkiaBitmapManager::GetInstance()->InitImage( AfxAddWorkPathA(pa) );
	ASSERT(NULL!=GxxAppPage::m_handleLine);

	//ReadAppBtnLayout(ele);
	SetAppBtnByLayout(ele);
	SetAniLayout(ele);



	TiXmlElement *child2 = ele->FirstChildElement();
	setCtrList(child2);
	m_posRation = (GxxRationPage *)findViewByName("page_pos");
	ASSERT(NULL != m_posRation);

	GxxAtButton::SetAppGroup(this);
	ReLoadCtrls();
	m_ActRect.bottom += 40;//这里加上40为了让下面的 分页点 显示出来
	
	
}

void GxxAppGroup::SetAniLayout( TiXmlElement * ele )
{
	const char* strAni = ele->Attribute(ANIMATION);
	ASSERT(NULL!=strAni);
	m_hAni= AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA(strAni));


	m_ActionCurToRight = AnimationManage::GetInstance()->GetAction(m_hAni,"CurToRight");
	m_ActionLeftToCur = AnimationManage::GetInstance()->GetAction(m_hAni,"LeftToCur");
	ASSERT(NULL!=m_ActionCurToRight);
	ASSERT(NULL!=m_ActionLeftToCur);

	m_AniLeftToCur =  (TranslateAnimation *)m_ActionLeftToCur->getAnimation();
	m_AniCurToRight =  (TranslateAnimation *)m_ActionCurToRight->getAnimation();



	m_ActionCurToRight->SetAniRect(m_ActRect);//使之刷新的区域
	m_ActionLeftToCur->SetAniRect(m_ActRect);//使之刷新的区域
}


bool GxxAppGroup::ReadAppBtnLayout( TiXmlElement * ele )
{
	//以下代码 加载具体的app btn
	const CHAR *slocal ;
	if (!Activity::s_bluetooth_exist)
	{
		slocal  = ele->Attribute(APP_LOCAL_NO_B);
	}
	else
	{
		slocal  = ele->Attribute(APP_LOCAL);
	}
	
	ASSERT (NULL!=slocal);
	m_appLocal = slocal;


	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	bool ret = xmlDoc->LoadFile( AfxAddWorkPathA(slocal) );

	if(!ret)//不成功则启用备份档案
	{
		string path = m_appLocal +  ".back";
		bool ret_backup = xmlDoc->LoadFile( AfxAddWorkPathA(path.c_str()) );
		ASSERT(ret_backup);// 备份档案 必须保证成功
		//return false;
	}


	const CHAR * ctrname = NULL;
	TiXmlElement *eleApp = xmlDoc->RootElement();


	while(eleApp)
	{
		ctrname = eleApp->Value();
		if (NULL==ctrname || strcmp(ctrname,APPPAGEPAD)!= 0)
		{
			return false;
		}


		TiXmlElement *child = eleApp->FirstChildElement();

		T_S_INT ts;
		while(child)
		{
			ctrname = child->Value();
			if (NULL==ctrname || strcmp(ctrname,GXXAPPBUTTON)!= 0)
			{
				return false;
			}

			int nth =0;
			child->Attribute(NTH_APP,&nth);//LOCAL
			ts.push_back(nth);
			if (!AppManage::GetInstance()->GetModule(nth))
			{
				//return false;
			}
			child = child->NextSiblingElement();				
		}
		if (ts.size()>0)
		{
			m_appNthList.push_back(ts);
		}
		eleApp = eleApp->NextSiblingElement();
	}
	return true;

}

void GxxAppGroup::WriteAppBtnLayout()
{
	try
	{
		auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
		for (T_PageGroup::iterator pos = m_allPage.begin(); pos != m_allPage.end(); ++pos)
		{
			(*pos)->WritePageNth(*xmlDoc);
		}
		xmlDoc->SaveFile(AfxAddWorkPathA(m_appLocal.c_str()) );
	}
	catch (string& )
	{
		return;
	}
	return;

}
void GxxAppGroup::SetAppBtnByLayout(TiXmlElement * ele )
{
	if ( !ReadAppBtnLayout(ele) )
	{
		ASSERT(0);//允许执行到这里。

		m_appNthList.clear();
		int nth = 0;
		T_AppModule*  ta = NULL;
		for (int i=0;i<3;i++)//直接设置btn
		{
			T_S_INT ts;
			for ( int j=0;j<8;j++)
			{
				ta = AppManage::GetInstance()->GetModule(nth);
				if (NULL == ta)
				{
					break;
				}
				ts.push_back(nth);
				nth++;
			}

			if (ts.size()>0)
			{
				m_appNthList.push_back(ts);
			}

			if (ts.size() != 8)
			{
				break;
			}
		}
	}


	for (T_S_S_INT::iterator ss_pos = m_appNthList.begin(); ss_pos != m_appNthList.end(); ++ss_pos)
	{
		GxxAppPage  *pPage = new GxxAppPage;
		for (T_S_INT::iterator pos = ss_pos->begin(); pos != ss_pos->end(); ++pos)
		{
			GxxAppButton * abtn= new GxxAppButton( *pos);
			pPage->AddCtrl(abtn);
		}
		pPage->resetRect();
		m_allPage.push_back(pPage);
	}

	ASSERT(m_allPage.size()>0);
	m_pagepos = m_allPage.begin();
}


void GxxAppGroup::startRightAnimation(bool isRight)
{
	if (AnimationManage::GetInstance()->IsInAction(m_hAni))
	{
		return;
	}
	m_fromCurPage = *m_pagepos;
	m_toCurPage = NULL;
	if (isRight)//向右移动，也就是前一页
	{
		if(m_allPage.size()<=1)
		{
			return;
		}
		if (m_pagepos==m_allPage.begin())
		{
			//已经是第一页了
			return;
		}
		m_pagepos--;
		m_toCurPage = *m_pagepos;

		
		//ControlList::iterator pos;

		//m_ActionCurToRight->ClearHandles();
		//m_fromCurPage->AddHandlesToAction(m_ActionCurToRight);


		//m_ActionLeftToCur->ClearHandles();
		//m_toCurPage->AddHandlesToAction(m_ActionLeftToCur);


		AnimationManage::GetInstance()->setDirect(m_hAni,FALSE);//方向
		AnimationManage::GetInstance()->StartAction(m_hAni);
	}
	else//向左移动，也就是后一页
	{
		
		if(m_allPage.size()<=1)
		{
			return;
		}
		if (m_pagepos==--m_allPage.end())
		{
			//已经是最后一页了
			return;
		}
		m_pagepos++;
		m_toCurPage = *m_pagepos;

		//ControlList::iterator pos;
		//m_ActionCurToRight->ClearHandles();
		//m_toCurPage->AddHandlesToAction(m_ActionCurToRight);

		//m_ActionLeftToCur->ClearHandles();
		//m_fromCurPage->AddHandlesToAction(m_ActionLeftToCur);


		AnimationManage::GetInstance()->setDirect(m_hAni,TRUE);//方向
		AnimationManage::GetInstance()->StartAction(m_hAni);
	}

	ClearCtrls();
	AddCtrl(m_fromCurPage);
	AddCtrl(m_toCurPage);
	AddCtrl(m_posRation);
	m_fromCurPage->setEnable(FALSE);
}


void GxxAppGroup::ComputeRect( const RECT &groupRect,const T_MarginI &tm, RECT *pageRect )
{
	int lineSize = (A_PAGE_SIZE/2);
	int width =   (groupRect.right-groupRect.left -tm.x_margin*2 - tm.x_interval*3)/lineSize;
	int height =   (groupRect.bottom-groupRect.top - tm.y_margin*2 - tm.y_interval)/2;
	for (int i=0;i<A_PAGE_SIZE;i++)
	{
		int y_add = i/lineSize;
		int x_add = i%lineSize;
		pageRect[i].left = groupRect.left + tm.x_margin + (tm.x_interval+width)*x_add;
		pageRect[i].right = pageRect[i].left + width;
		pageRect[i].top = groupRect.top + tm.y_margin + (tm.y_interval+height)*y_add;
		pageRect[i].bottom = pageRect[i].top + height;
	}
}


bool GxxAppGroup::SetEidtMode( bool e )
{
	if (GxxAtButton::getEditMode() == e)
	{
		return false;

	}
	if (AnimationManage::GetInstance()->IsInAction(m_hAni))
	{
		return true;//可以设但是在移动
	}
	GxxAtButton::setEditMode(e);
	
	T_PageGroup::iterator pos;
	for ( pos = m_allPage.begin();pos != m_allPage.end(); pos++)
	{
		(*pos)->resetRect();
	}
	AfxInvalidateRect(&m_ActRect);
	if (!e)
	{
		checkClearPage();
		SetPosRation();
		WriteAppBtnLayout();
		//保存 xml
	}
	return true;
}

//滑动到某一页，把按键加入这一页
bool GxxAppGroup::MoveAddBtn( GxxAppButton* at )
{
	
	GxxAppPage   * prePage = (GxxAppPage   * )at->getParentView();
	if ((*m_pagepos)->checkAddBtn(at))//添加成功
	{
		
		//if (AnimationManage::GetInstance()->IsInAction(m_hAni))
		//{
		//	ASSERT(*m_pagepos == m_toCurPage);
		//	//在动画中加入按键
		//	if (AnimationManage::GetInstance()->getDirect(m_hAni))
		//	{
		//		m_ActionCurToRight->AddHandle(at->getAppActHandle());
		//		m_ActionLeftToCur->RemoveHandle(at->getAppActHandle());
		//	}
		//	else
		//	{
		//		m_ActionLeftToCur->AddHandle(at->getAppActHandle());
		//		m_ActionCurToRight->RemoveHandle(at->getAppActHandle());
		//	}
		//}
		//prePage->sortBtn()
		if (prePage!=(*m_pagepos) )//将以前的那一页调整顺序
		{
			prePage->resetRect();
		}
		
		return true;
	}
	//ASSERT(0);
	return false;
	
}


//交换两个按键
bool GxxAppGroup::MoveExchangeBtn( GxxAppButton * downBtn, GxxAppButton * toBtn )
{

	GxxAppPage   * downPage = (GxxAppPage   * )downBtn->getParentView();
	GxxAppPage   * toPage = (GxxAppPage   * )toBtn->getParentView();
	ASSERT(toPage == *m_pagepos);
	if (downPage == toPage)//本页和本页交换，要保证顺序
	{
		toPage->exchangeBtn(downBtn,toBtn);
		AfxInvalidateRect(NULL);
		return true;

	}
	else//非本页的按键进行插入
	{
		if(toPage->getCtrlsSize()==8)
		{
			GxxAppPage::ExchangeBtn(downBtn,toBtn,downPage,toPage);
		}
		else
		{
			downPage->removeCtrl(downBtn);
			downPage->resetRect();
			toPage->InsertBtn(toBtn,downBtn);
		}
		AfxInvalidateRect(NULL);
		return true;
		
	}
	
	return false;
}

bool GxxAppGroup::checkPrePage(GxxView* v)
{

	if ((*m_pagepos)==m_allPage.front())
	{
		if (m_allPage.size()<4)
		{
			GxxAppPage  *pPage = new GxxAppPage;
			m_allPage.push_front(pPage);
			return true;
		}	
	}
	//else
	//{
	//		T_PageGroup::iterator pos = --m_pagepos;
	//		m_pagepos++;
	//		if ((*pos)->findView(v) || (*pos)->getCtrlsSize()<8)
	//		{
	//			return true;
	//		}
	//}
	return true;
}
//测试后一个页面，以及是否要增加一个页面
//如果总页面数大于4，或者后一个页面大于等于8，则返回false。
bool GxxAppGroup::checkPostPage(GxxView* v)
{

	ASSERT (m_pagepos!=m_allPage.end());

	if ((*m_pagepos)==m_allPage.back())
	{
		if (m_allPage.size()<4)
		{
			GxxAppPage  *pPage = new GxxAppPage;
			m_allPage.push_back(pPage);
			return true;
		}
	}
	//else 
	//{
	//	T_PageGroup::iterator pos = ++m_pagepos;
	//	m_pagepos--;
	//	if ((*pos)->findView(v) || (*pos)->getCtrlsSize()<8)
	//	{
	//		return true;
	//	}
	//}


	return true;
}


void GxxAppGroup::checkClearPage()
{
	if (AnimationManage::GetInstance()->IsInAction(m_hAni))
	{
		return;
	}

	T_PageGroup::iterator pos;

	bool rload = false;
	for ( pos = m_allPage.begin();pos != m_allPage.end(); )
	{
		if ((*pos)->getCtrlsSize()==0)
		{
			if (m_pagepos == pos)
			{
				if (m_pagepos != m_allPage.begin())
				{
					--m_pagepos;
				}
				else if (m_pagepos != m_allPage.end())
				{
					++m_pagepos;
				}
				else
				{
					ASSERT(0);
				}
				rload = true;
			}
			delete (*pos);
			pos = m_allPage.erase(pos);
		}
		else
		{
			pos++;
		}
	}
	if (rload)
	{
		ReLoadCtrls();

	}
}

void GxxAppGroup::SetPosRation()
{
	int sun = m_allPage.size();
	int i=0;
	for (T_PageGroup::iterator pos = m_allPage.begin();pos != m_allPage.end(); pos++,i++)
	{
		if (pos==m_pagepos)
		{
			m_posRation->setRation(i,sun);
			break;
		}
	}
}

void GxxAppGroup::ReLoadCtrls()
{
	ClearCtrls();
	AddCtrl(*m_pagepos);
	AddCtrl(m_posRation);
	SetPosRation();
}

//恢复出厂设置
void GxxAppGroup::resetToFactory()
{
	map<int, GxxAppButton*> mapBtnList;
	
	for (T_PageGroup::iterator pos = m_allPage.begin();pos != m_allPage.end(); ++pos)
	{
		ControlList * btnlist = (*pos)->getCtrlsList();//得到每一页的所有Btn集合
		for (ControlList::iterator btn_pos = btnlist->begin(); btn_pos != btnlist->end(); ++btn_pos)
		{
			GxxAppButton* pBtn = (GxxAppButton*)*btn_pos;
			mapBtnList.insert( std::make_pair(pBtn->getNth(),pBtn) );
		}
		delete (*pos);
	}

	ASSERT(mapBtnList.size() >0);
	
	GxxAppPage  *pPage = NULL;
	m_allPage.clear();

	int i = 0;
	for (map<int, GxxAppButton*>::iterator pos1=mapBtnList.begin(); pos1 != mapBtnList.end(); ++pos1,++i)
	{
		int n = i%8;
		if (0 == n)
		{
			pPage = new GxxAppPage;
			m_allPage.push_back(pPage);
		}
		pPage->AddCtrl( pos1->second);
	}

	ASSERT(m_allPage.size());

	for (T_PageGroup::iterator pos = m_allPage.begin(); pos != m_allPage.end(); ++ pos)
	{
		(*pos)->resetRect();
	}
	

	m_pagepos = m_allPage.begin();

	ReLoadCtrls();

	WriteAppBtnLayout();

	//for (T_S_S_INT::iterator ss_pos = m_appNthList.begin(); ss_pos != m_appNthList.end(); ++ss_pos)
	//{
	//	GxxAppPage  *pPage = new GxxAppPage;
	//	for (T_S_INT::iterator pos = ss_pos->begin(); pos != ss_pos->end(); ++pos)
	//	{
	//		GxxAppButton * abtn= new GxxAppButton( *pos);
	//		pPage->AddCtrl(abtn);
	//	}
	//	pPage->resetRect();
	//	m_allPage.push_back(pPage);
	//}
}







