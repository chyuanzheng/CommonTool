#include "StdAfx.h"
#include "GxxAtButton.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "AppManage.h"
#include "GxxAppGroup.h"
#include "GxxToolGroup.h"
#include "GxxToolButton.h"
#include "GxxAniPictureA.h"
#include "GxxSwText.h"
const int LEN_DEC = 5;

class EDIT_VALUE : protected GxxTimer
 {
 public:	 
	 EDIT_VALUE()
	 {
		 m_timerId = RegisterTimer(500);
		 m_timerEnterEdit = RegisterTimer(3000);
		 border_left = 0;
		 border_right =0;
		 app_group = NULL;
		 ResetMove();		 
	 }
	~EDIT_VALUE()
	{
		UnRegisterTimer(m_timerId);
		UnRegisterTimer(m_timerEnterEdit);
	}
	 void ResetMove() 
	 {
		 start_x=0;
		 start_y=0;
		 end_y=0;
		 end_x=0;
		 ch_btn=NULL;
		 down_btn =NULL;
		 StopTimer(m_timerId);
		 StopTimer(m_timerEnterEdit);
	 }

	 void StartEnterEdit()
	 {
		 StartTimer(m_timerEnterEdit);
	 }
	 void StopEnterEdit()
	 {
		 StopTimer(m_timerEnterEdit);
	 }

	 void SetDownBtn( GxxAtButton* db ) 
	 {
		 down_btn = db;
	 }

	 GxxAtButton*  GetDownBtn(  ) 
	 {
		 return down_btn;
	 }

	 void SetChooseBtn( GxxAtButton* ch ) 
	 {
		 ch_btn = ch;
	 }

	 GxxAtButton   * GetChooseBtn()
	 {
		return ch_btn;
	 }
	 int move_x()
	 {
		 return end_x - start_x;
	 }
	 int move_y()
	 {
		return end_y - start_y;
	 }


	 void SetStartMove(int x, int y)
	 {
		 end_x = start_x = x;
		 end_y = start_y = y;
	 }

	 void SetEnd( int x, int y ) 
	 {
		 end_x = x;
		 end_y = y;
		 if ( border_right + 100 > end_x  && end_x > border_right )
		 {
			 StartTimer(m_timerId);
		 }
		 else if ( border_left - 100 < end_x && end_x <  border_left )
		 {
			 StartTimer(m_timerId);
		 }
		 else
		 {
			 StopTimer(m_timerId);
		 }
	 }

	 virtual void TimerTick(UINT nIDEvent)
	 {
		 if (m_timerId == nIDEvent)//
		 {
			 StopTimer(m_timerId);
			 if ( border_right + 100 > end_x  && end_x > border_right )
			 {
				 AfxPostMessage(CTR_APP_LEFT_MODE,(WPARAM)down_btn,0);
			 }
			 else if ( border_left - 100 < end_x && end_x <  border_left )
			 {
				 AfxPostMessage(CTR_APP_RIGHT_MODE,(WPARAM)down_btn,0);
			 }	
		 }
		 else if (m_timerEnterEdit == nIDEvent)
		 {
			  StopTimer(m_timerEnterEdit);
			 AfxPostMessage(CTR_ENTER_EDIT_MODE,(WPARAM)down_btn,0);
		 }
	
	 }
	 void  setInvalidateRect( const RECT &invalidRect )
	 {
		 RECT rc;
		 ::SetRect(&rc ,invalidRect.left+move_x(),invalidRect.top+move_y(),invalidRect.right+move_x(),invalidRect.bottom+move_y());
		 AfxInvalidateRect(&rc);
	 }

	 int getEnd_x() {return end_x; }

	 int getEnd_y() {return end_y;}



	 void setBorder( int left, int right ) 
	 {
		 border_left = left;
		 border_right = right;
	 }

	 void setEditMode( bool b ) 
	 {
		 is_edit = b;
		 ResetMove();
	 }

	 bool getEditMode() {return is_edit;}

	 void setAppGroup( GxxAppGroup* g ) { app_group = g;}
	 GxxAppGroup*  getAppGroup(){return app_group;}

	 void setToolGroup( GxxToolGroup* g ) { tool_group = g;}
	 GxxToolGroup*  getToolGroup(){return tool_group;}



 private:
	 bool	        is_edit;
	 int            m_timerId;
	 int            m_timerEnterEdit;
	 int			start_x;
	 int			start_y;

	 int            end_x;
	 int            end_y;


	 int			border_left;
	 int			border_right;

	 GxxAtButton   *ch_btn;
	 GxxAtButton   *down_btn;
	 GxxAppGroup   *app_group;
	 GxxToolGroup  *tool_group;
	 

 };
 EDIT_VALUE        *GxxAtButton::s_editValue = new EDIT_VALUE;


GxxAniPictureA *GxxAtButton::s_pAniPicBack =  new GxxAniPictureA;
 GxxPicture *GxxAtButton::m_pPicPlaying  = NULL;
GxxAtButton::GxxAtButton( int nth)
{
	//AddCtrl(s_pAniPicBack);
	m_pPicUpEnable = new GxxPicture;
	m_pPicUpDisable = new GxxPicture;
	m_pS_PicUpEnable = new GxxPicture;
	m_pS_PicUpDisable = new GxxPicture;
	m_titleText = new GxxSwText;
	bool b = setBtnModule(nth);
	m_bStartAniBack = false;
	ASSERT(b);
	
}

bool GxxAtButton::setBtnModule( int nth )
{
	return setBtnModule (AppManage::GetInstance()->GetModule(nth) );
}


GxxAtButton::~GxxAtButton()
{
	delete m_pPicUpEnable;
	delete m_pPicUpDisable;
	delete m_pS_PicUpEnable;
	delete m_pS_PicUpDisable;
	delete m_titleText;

}



int GxxAtButton::getNth()
{
	return m_appModule->m_nth;
}

void GxxAtButton::Draw(  )
{
	if (m_bStartAniBack)
	{
		s_pAniPicBack->DrawPic();
	}
	GxxPicture *pic_up = GetAniPic();

	ASSERT(pic_up&& pic_up->getPicHandle());
	
	if (s_editValue->getEditMode()&&this == s_editValue->GetDownBtn())
	{
		pic_up->DrawPicWithRect(s_editValue->move_x(),s_editValue->move_y());
		m_titleText->DrawTextWithRect(s_editValue->move_x(),s_editValue->move_y());
		return;
	}

	int nx = GetPageMoveX();

	

	if((this == s_editValue->GetChooseBtn()) ) //被选中的状态和按下的状态是一样的
	{
		pic_up->DrawPicWithRect(m_ActRect,60);
		
	}else if (this == s_editValue->GetDownBtn())
	{
		pic_up->DrawPicWithRect(m_ActRect,60);
	}
	else 
	{
		RECT rc;
		::SetRect(&rc, m_ActRect.left + nx, m_ActRect.top,m_ActRect.right+nx,m_ActRect.bottom);
		pic_up->DrawPicWithRect(rc);
	}

	

	if (!s_editValue->getEditMode())
	{
		if (m_appModule->b_playing)
		{
			RECT rc;
			::SetRect(&rc, m_playRect.left + nx, m_playRect.top,m_playRect.right+nx,m_playRect.bottom);
			GxxAtButton::m_pPicPlaying->DrawPicWithRect(rc);
		}
	}
	

	m_titleText->DrawTextWithRect(nx,0);
}



BOOL GxxAtButton::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;
	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if ( InMyArea( LOWORD( lParam ), HIWORD( lParam )) )
		{
			s_editValue->SetDownBtn(this);
			if (s_editValue->getEditMode() )
			{
				s_editValue->SetStartMove((m_ActRect.left + m_ActRect.right)/2,  (m_ActRect.top + m_ActRect.bottom)/2);
				InvalidateMoveRect(LOWORD( lParam ), HIWORD( lParam ));
				setSelView(this);
				return TRUE;
			}
			else 
			{	
				AfxInvalidateRect(&m_ActRect);//画图片
				AfxInvalidateRect(&m_titleText->getCtrRect());
				s_editValue->StartEnterEdit();
				StartAniBtn();
				
				return TRUE;
			}
		}
		return FALSE;
	case WM_MOUSEMOVE:
		if (s_editValue->getEditMode())
		{
			if (s_editValue->GetDownBtn() == this)
			{
				InvalidateMoveRect(LOWORD( lParam ), HIWORD( lParam ));
			}
			else
			{
				if ( InMyArea(s_editValue->getEnd_x(),s_editValue->getEnd_y()))
				{
					if (( this != s_editValue->GetChooseBtn() ) )
					{
						s_editValue->SetChooseBtn(this);
						AfxInvalidateRect(&m_ActRect);//画背景黄 和图片
					}

				}
				else if (this == s_editValue->GetChooseBtn())
				{
					s_editValue->SetChooseBtn(NULL);
					AfxInvalidateRect(&m_ActRect);//画图片
				}
			}
		}
		else
		{
			if (s_editValue->GetDownBtn() == this &&  !InMyArea( LOWORD( lParam ), HIWORD( lParam ))  )
			{
				s_editValue->StopEnterEdit();
			}
		}
		return FALSE;
	case WM_LBUTTONUP:
		//若本按钮曾经被按下
		if( s_editValue->GetDownBtn() == this )
		{
			//::ReleaseCapture();
			StopAniBtn();
			
			if (s_editValue->getEditMode())
			{
				moveBtnEnd();
				clearSelView();
			}
			else 
			{
				if( InMyArea( LOWORD( lParam ), HIWORD( lParam ) ) )
				{
					if (m_appModule->b_enable)
					{
						Activity::startActivity(NULL,m_appModule->activity,m_appModule->param_id);
					}
					else
					{
						Activity::failedStart(m_appModule->activity);
					}
					
				}
			}
			s_editValue->ResetMove();	
			AfxInvalidateRect(NULL);
			return TRUE;

		}
		return FALSE;
	default:
		return FALSE;
	}
}



void GxxAtButton::InvalidateMoveRect( int x/*=0*/,int y/*=0*/ )
{
	s_editValue->setInvalidateRect(m_ActRect);
	s_editValue->setInvalidateRect(m_titleText->getCtrRect());
	s_editValue->SetEnd(x, y);
	s_editValue->setInvalidateRect(m_ActRect);
	s_editValue->setInvalidateRect(m_titleText->getCtrRect());
}


// 这里插入按键 或 交换按键 或 返回按键 等等
void GxxAtButton::moveBtnEnd( )
{
	GxxAtButton * choose_btn = s_editValue->GetChooseBtn();
	GxxAppGroup *app_group = s_editValue->getAppGroup();
	GxxToolGroup *tool_group = s_editValue->getToolGroup();

	ASSERT(NULL!=app_group && NULL != tool_group);
	if (getBtnType()==APP_BTN)
	{
		if (choose_btn == NULL)//没有选中的 ，而且 当前按键是 APP_BTN
		{
			app_group->MoveAddBtn((GxxAppButton *)this);
		}
		else 
		{
			if (choose_btn->getBtnType() ==APP_BTN)//有 选中的，而且两者都是 APP_BTN
			{
				app_group->MoveExchangeBtn( (GxxAppButton *)this,(GxxAppButton *)choose_btn);
			}
			else
			{//abtn->getBtnType() == TOOL_BTN)
				tool_group->MoveSetModule((GxxToolButton *)choose_btn,m_appModule);
			}
		}
	}
	else if (getBtnType()==TOOL_BTN)
	{
		if (choose_btn!=NULL && choose_btn->getBtnType() ==TOOL_BTN)//有 选中的，而且两者都是 TOOL_BTN
		{
			tool_group->MoveExchangeModule((GxxToolButton *)this, (GxxToolButton *)choose_btn);
		}
	}
	
	
}


bool GxxAtButton::setBtnModule( T_AppModule * m )
{
	if (NULL == m)
	{
		return false;
	}
	m_appModule = m;
	//if (m_appModule->title_id.size()!=0)
	//{
	//	m_titleText->setTextFromId(m_appModule->title_id);
	//}
	//else
	{
		m_titleText->setText(m_appModule->title.c_str());
	}
	
	bool b1= m_pPicUpEnable->setPicHandle(m_appModule->icon.c_str());
	bool b2= m_pPicUpDisable->setPicHandle(m_appModule->icong.c_str());
	ASSERT(b1&&b2);

	b1= m_pS_PicUpEnable->setPicHandle(m_appModule->s_icon.c_str());
	b2= m_pS_PicUpDisable->setPicHandle(m_appModule->s_icong.c_str());
	ASSERT(b1&&b2);

	return true;
}


void GxxAtButton::RectChanged()
{
	RECT rc;
	::SetRect(&rc,m_ActRect.left-5*LEN_DEC,m_ActRect.bottom+1*LEN_DEC,m_ActRect.right+5*LEN_DEC ,m_ActRect.bottom+6*LEN_DEC);
	m_titleText->setCtrRect(rc);


	m_pPicUpEnable->setCtrRect(m_ActRect);
	m_pPicUpEnable->bindHandleRect();

	m_pPicUpDisable->setCtrRect(m_ActRect);
	m_pPicUpDisable->bindHandleRect();

	m_pS_PicUpEnable->setCtrRect(m_ActRect);
	m_pS_PicUpEnable->bindHandleRect();

	m_pS_PicUpDisable->setCtrRect(m_ActRect);
	m_pS_PicUpDisable->bindHandleRect();

	if (GxxAtButton::m_pPicPlaying == NULL)
	{
		GxxAtButton::m_pPicPlaying = new GxxPicture;
		GxxAtButton::m_pPicPlaying->setPicHandle(T_AppModule::iconplay.c_str());
	}
	int nw = GxxAtButton::m_pPicPlaying->getPicWidth()/2;
	int nh = GxxAtButton::m_pPicPlaying->getPicHeight()/2;
	::SetRect(&m_playRect,m_ActRect.right-nw,m_ActRect.top -nh,
							m_ActRect.right+nw,  m_ActRect.top+nh);
}



void GxxAtButton::setBorder( int left, int right )
{

	s_editValue->setBorder(left, right);
}

void GxxAtButton::setEditMode( bool b )
{
	GxxAtButton *atBtn = s_editValue->GetDownBtn();
	if (NULL != atBtn)
	{
		atBtn->StopAniBtn();
	}
	
	s_editValue->setEditMode(b);
	if (!b)
	{
		GxxToolGroup *tool_group = s_editValue->getToolGroup();
		tool_group->WriteToolBtnLayout();

	}
	
	AfxInvalidateRect(NULL);
}

bool GxxAtButton::getEditMode()
{
	return s_editValue->getEditMode();
}

BOOL GxxAtButton::getBtnIsDown()
{
	return this == s_editValue->GetDownBtn();
}

void GxxAtButton::SetAppGroup( GxxAppGroup* g )
{
	s_editValue->setAppGroup(g);
}

void GxxAtButton::SetToolGroup( GxxToolGroup* g )
{
	s_editValue->setToolGroup(g);
}

void GxxAtButton::StartAniBtn()
{
	
	
	if (s_pAniPicBack->getPicHandle()==NULL)
	{
		s_pAniPicBack->setPicHandle(T_AppModule::iconback.c_str());
	}
	s_pAniPicBack->setCtrRect(m_ActRect);
	s_pAniPicBack->bindHandleRect();
	s_pAniPicBack->Start();
	m_bStartAniBack = true;
	//AddCtrl(s_pAniPicBack);
	
	
}

void GxxAtButton::StopAniBtn()
{
	m_bStartAniBack = false;
	s_pAniPicBack->Stop();
	//removeCtrl(s_pAniPicBack);
}

HANDLE GxxAtButton::getAppActHandle()
{
	GxxPicture *pic_up = GetAniPic();
	return pic_up->getPicHandle();
}

GxxPicture * GxxAtButton::GetAniPic( )
{
	GxxPicture * pic_up = NULL;
	if (m_appModule->b_enable)
	{
		if (m_ActRect.right-m_ActRect.left<80)//小于80个像素是小图标
		{
			pic_up = m_pS_PicUpEnable;
		}
		else
		{
			pic_up = m_pPicUpEnable;
		}

	}
	else
	{
		if (m_ActRect.right-m_ActRect.left<80)
		{
			pic_up = m_pS_PicUpDisable;
		}
		else
		{
			pic_up = m_pPicUpDisable;
		}

	}	return pic_up;
}
