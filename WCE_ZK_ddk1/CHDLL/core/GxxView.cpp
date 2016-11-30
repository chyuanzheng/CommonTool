#include "StdAfx.h"
#include "XmlDef.h"
#include "GxxView.h"

#include "SkiaBitmapManager.h"
#include "GXCreateControls.h"
#include "StrHelp.h"
TMapStr_CtrList  GxxView::s_allList= TMapStr_CtrList();
GxxView* GxxView::s_selView= NULL;
bool  GxxView::S_OnlyPaintSel = false;
GxxView::GxxView()
{
	m_ParentCtrl=NULL;
	m_enable = true;
	m_bDraw  = true;
	m_bOnlyDrawActRect = false;
	//pImageManager= CImagesManager::GetInstance();
	m_pCtrlVet = new ControlList;
	SetRect(&m_ActRect,0,0,0,0);
}
GxxView::~GxxView()
{
	delete m_pCtrlVet;
}
BOOL   GxxView::AddCtrl(GxxView* control)
{
	ASSERT(control);
	if (std::find(m_pCtrlVet->begin(), m_pCtrlVet->end(), control) == m_pCtrlVet->end())
	{
		control->m_ParentCtrl = this;
		m_pCtrlVet->push_back(control);
		return true;
	}
	return false;
}

BOOL   GxxView::AddCtrl(GxxView* control, GxxView* bef)
{
	if (std::find(m_pCtrlVet->begin(), m_pCtrlVet->end(), control) == m_pCtrlVet->end())
	{
		ControlList::iterator bPos = std::find(m_pCtrlVet->begin(), m_pCtrlVet->end(), bef);
		control->m_ParentCtrl = this;
		m_pCtrlVet->insert(bPos,control);
		return true;
	}
	return false;
}

//这里并不会将 control 的父控件 设为 NULL
BOOL GxxView::removeCtrl( GxxView* control )
{
	m_pCtrlVet->remove(control);
	return true;
}

void    GxxView::deleteAllCtrls()
{
	ControlList::iterator pos;
	for (pos=m_pCtrlVet->begin();pos!=m_pCtrlVet->end();pos++)
	{
		delete (*pos);
	}
	ClearCtrls();
}

void    GxxView::deleteOneCtrl(GxxView *v)
{
	delete v;
	removeCtrl(v);
}

BOOL GxxView::AddCtrl( ControlList* ctrList )
{
	ControlList::iterator pos;
	for (pos=ctrList->begin();pos!=ctrList->end();pos++)
	{
		AddCtrl(*pos);
	}
	return TRUE;
}

void GxxView::setResume()
{
	onResume();
	for(ControlList::iterator pos  = m_pCtrlVet->begin(); pos != m_pCtrlVet->end();++pos )
	{
		(*pos)->setResume();
	}
}

void GxxView::setPause()
{
	onPause();
	for(ControlList::iterator pos  = m_pCtrlVet->begin(); pos != m_pCtrlVet->end();++pos )
	{
		(*pos)->setPause();
	}
}

/** 控件的消息处理入口函数 
    （WM_DESTROY WM_EXIT_PROSS WM_PAINT 不在此处理）
    
    先处理本控件中的子控件的消息
	然后再处理本控件的消息 （Response）
*/
BOOL GxxView::DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if ( !m_bDraw||!m_enable)
	{
		if (message < WM_USER || CTR_MESSAGE ==  message)//|| CTR_ANIMATION_MES ==  message
		{
			return FALSE;
		}
		//if (0x119==message || WM_LBUTTONDOWN==message || WM_LBUTTONUP ==message || WM_MOUSEMOVE ==  message || CTR_MESSAGE ==  message || WM_SETCURSOR ==  message || CTR_ANIMATION_MES ==  message)
		//{
		//	return FALSE;//
		//}
		
	}

	//if (!m_bDraw)
	//{
	//	return FALSE;
	//}
	ControlList::reverse_iterator pos;	
	pos = m_pCtrlVet->rbegin();
	while(pos != m_pCtrlVet->rend())
	{

		if ((*pos != s_selView) && (*pos)->DealCtrlMsg(message, wParam, lParam ))
		{
			return TRUE;
		}
		pos++;
	}
	if (Response(message, wParam, lParam ) == TRUE)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL GxxView::DealSelCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	if (!m_bDraw || !m_enable)
	{
		if (message < WM_USER|| CTR_MESSAGE ==  message )
		{
			return FALSE;
		}
		//if (0x119==message || WM_LBUTTONDOWN==message || WM_LBUTTONUP ==message || WM_MOUSEMOVE ==  message || CTR_MESSAGE ==  message || WM_SETCURSOR ==  message )
		//{
		//	return FALSE;//
		//}

	}

	//if (!m_bDraw)
	//{
	//	return FALSE;
	//}

	if (s_selView != NULL )//选中的要先处理消息
	{
		if (s_selView->DealCtrlMsg(message, wParam, lParam ))
		{
			return TRUE;
		}
	}
	return FALSE;
}
/** 控件的WM_PAINT消息处理入口函数 
注意 动画效果可以在这里处理，在这里处理的话，matrix会处理
所有子控件，所以会产生一起变化，如一起变大或者变小，
甚至可以在一起变化的同时子控件可以再做其他的变化。如:
在一起变大的过程中，子控件再旋转，翻个跟斗……暂时不做
*/
void GxxView::Paint(  )
{
	if (!m_bDraw)
	{
		return;
	}
	DoPaint();

}

void GxxView::DoPaint()
{
	if (m_bOnlyDrawActRect)
	{
		SkiaBitmapManager::GetInstance()->SaveStatus();
		SkiaBitmapManager::GetInstance()->SetClipRect(m_ActRect);
	}
	Draw();
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{
		if (*pos != s_selView)
		{
			(*pos)->Paint(  );
		}		
		pos++;
	}

	if (m_bOnlyDrawActRect)
	{
		SkiaBitmapManager::GetInstance()->ReleasStatus();
	}
}
void GxxView::PaintSelView()
{
	if ( s_selView != NULL )//选中的要最后画
	{
		s_selView->Paint( );
	}
}
void GxxView::setMoveRect( int x_len, int y_len )
{
	onMoveRect(x_len,y_len);
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{	
		//(*pos)->MoveLen(x_len,y_len);
		(*pos)->setMoveRect(x_len,y_len);
		pos++;
	}
}



bool GxxView::setCtrRect( TiXmlElement * ele )
{
	int data =0;

	const char * c = ele->Attribute(LAYOUT_X,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.left = data;

	c = ele->Attribute(LAYOUT_Y,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.top =  data;

	c = ele->Attribute(LAYOUT_WIDTH,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.right =  data + m_ActRect.left;

	c = ele->Attribute(LAYOUT_HEIGHT,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.bottom =  data + m_ActRect.top;

	return true;
}

bool GxxView::setCtrRectUseCenter( TiXmlElement * ele )
{
	int center_x = 0;
	int center_y = 0;
	int lenth = 0;
	int height = 0;
	const char * c = ele->Attribute(CENTER_X,&center_x);
	if (NULL == c)
	{
		return false;
	}
	c = ele->Attribute(CENTER_Y,&center_y);
	if (NULL == c)
	{
		return false;
	}
	c = ele->Attribute(LAYOUT_WIDTH,&lenth);
	if (NULL == c)
	{
		return false;
	}
	c = ele->Attribute(LAYOUT_HEIGHT,&height);
	if (NULL == c)
	{
		return false;
	}
	return setCtrRectUseCenter(center_x,center_y,lenth,height);
}

bool GxxView::setCtrRectUseCenter( TiXmlElement * ele,int width,int height )
{
	int center_x = 0;
	int center_y = 0;
	int nwidth = width;
	int nheight = height;
	const char * c = ele->Attribute(CENTER_X,&center_x);
	if (NULL == c)
	{
		return false;
	}

	c = ele->Attribute(CENTER_Y,&center_y);
	if (NULL == c)
	{
		return false;
	}

	if (NULL!=ele->Attribute(LAYOUT_WIDTH) )
	{
		ele->Attribute(LAYOUT_WIDTH,&nwidth);
	}
	if (NULL!=ele->Attribute(LAYOUT_HEIGHT) )
	{
		ele->Attribute(LAYOUT_HEIGHT,&nheight);
	}
	return setCtrRectUseCenter(center_x,center_y,nwidth,nheight);
}

bool GxxView::setCtrRect( TiXmlElement * ele,int left,int top )
{

	m_ActRect.left = left;
	m_ActRect.top =  top;

	int data =0;
	const char * c = ele->Attribute(LAYOUT_WIDTH,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.right =  data + m_ActRect.left;
	c = ele->Attribute(LAYOUT_HEIGHT,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.bottom =  data + m_ActRect.top;
	return true;
}

bool GxxView::setCtrRect( int width,int height,TiXmlElement * ele )
{
	int data;
	const char * c = ele->Attribute(LAYOUT_X,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.left = data;

	c = ele->Attribute(LAYOUT_Y,&data);
	if (NULL == c)
	{
		return false;
	}
	m_ActRect.top = data;
	m_ActRect.right = m_ActRect.left +width;
	m_ActRect.bottom = m_ActRect.top +height;
	return true;
}


void GxxView::setCtrName( TiXmlElement * ele )
{
	const CHAR *elename = ele->Attribute(CTR_NAME);
	if (NULL!=elename)
	{
		m_sCtrName=elename;
	}
}

void GxxView::setEnableFromXml( TiXmlElement * ele )
{
	const CHAR *elename = ele->Attribute(CTR_ENABLE);
	if (NULL!=elename)
	{
		string s=elename;
		if ( StrHelp::StringEqual(elename,"false") )
		{
			setEnable(false);
		}
		else if ( StrHelp::StringEqual(elename,"true") )
		{
			setEnable(true);
		}
		
	}
	else
	{
		setEnable(true);//默认
	}
}

void GxxView::setCtrName(const char * name )
{
	if (NULL!=name)
	{
		m_sCtrName=name;
	}
}


GxxView * GxxView::findViewByName( const CHAR* vname )
{
	ASSERT(vname!=NULL);
	ControlList::iterator pos;	
	string ctrname;
	pos = m_pCtrlVet->begin();
	GxxView * pctr=NULL;
	while(pos != m_pCtrlVet->end())
	{
		ctrname=(*pos)->getCtrName();
        if (ctrname==vname)
        {
			pctr = (*pos);
			break;
        }
		pctr =(*pos)->findViewByName(vname);
		if (NULL!=pctr)
		{
			break;
		}
		pos++;
	}
	return pctr;
}

void GxxView::onCreate()
{

	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{	
		(*pos)->onCreate();
		pos++;
	}
}

void GxxView::onDestroy()
{
	ControlList::iterator pos;	
	pos = m_pCtrlVet->begin();
	while(pos != m_pCtrlVet->end())
	{	
		(*pos)->onDestroy();
		pos++;
	}
	delete this;
}




void GxxView::setCtrList( TiXmlElement * ele,ControlList *ctrList/*=NULL */ )
{
	string ctrname;

	while(ele)
	{
		GxxView *ctr=NULL;
		ctrname = ele->Value();

		if (ctrname == INCLUDE)
		{
			ASSERT(ctrList==NULL);
			loadXmlView(ele);
			ele = ele->NextSiblingElement();
			continue;
		}
		else if (ctrname == INCLUDE_COPY)
		{
			ASSERT(ctrList==NULL);
			const char* pa = ele->Attribute(LOCAL);
			auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
			BOOL bload = xmlDoc->LoadFile(AfxAddWorkPathA(pa));
			ASSERT(bload);
			TiXmlElement *root = xmlDoc->RootElement();

			setCtrList(root);
			ele = ele->NextSiblingElement();
			continue;
		}
		else
		{
			ctr = GXCreateControl::CreateControlByType(ctrname.c_str());
		}
		ASSERT(NULL!=ctr);
		if (NULL!=ctr)
		{
			if (NULL!=ctrList)
			{
				ctrList->push_back(ctr);
			}

			AddCtrl(ctr);
			ctr->setCtrLayout(ele);
		}
		ele = ele->NextSiblingElement();

	}
}

BOOL GxxView::loadXmlView( TiXmlElement * ele )
{
	const char* pa = ele->Attribute(LOCAL);

	string str_pa = pa;
	TMapStr_CtrList::iterator pos;
	for (pos=s_allList.begin();pos!=s_allList.end();pos++)
	{
		if (pos->first==str_pa)
		{
			AddCtrl(pos->second);
			return TRUE;
		}
	}


	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	BOOL bload = xmlDoc->LoadFile(AfxAddWorkPathA(pa));
	ASSERT(bload);
	TiXmlElement *root = xmlDoc->RootElement();

	ControlList *ctrlist = new ControlList;
	setCtrList(root,ctrlist);
	s_allList[str_pa]=ctrlist;

	return TRUE;

}

void GxxView::setCtrLayout( TiXmlElement * ele )
{

}

//bool GxxView::SendMesToParent( GxxView* mesView, UINT nMsg, WPARAM wParam, LPARAM lParam )
//{
//	GxxView *p = getParentView();
//	while (NULL!= p)
//	{
//		if (p->DoMesToParent( mesView, nMsg, wParam, lParam ))
//		{
//			return true;
//			break;
//		}
//		p = p->getParentView();
//	}
//	return false;
//}



void GxxView::setEnable( bool e )
{
	m_enable = e; 
	onEnable(e); 
	AfxInvalidateRect(&m_ActRect);
}

void GxxView::invalidateRect()
{
	AfxInvalidateRect(&m_ActRect);
}

bool GxxView::checkToParent(TiXmlElement * ele )
{
	bool bto_parent = false;
	const char * pchar  = ele->Attribute(TO_PARENT);
	if (pchar!=0)
	{
		if ( StrHelp::StringEqual( string(pchar),string("true") ) )
		{
			bto_parent = true;
		}
	}
	if (bto_parent)
	{
		GxxView *pv = getParentView();
		ASSERT(pv!=NULL);
		RECT rc = pv->getCtrRect();
		ASSERT(rc.right>rc.left&&rc.right<=800);
		::SetRect(&m_ActRect,m_ActRect.left+rc.left, m_ActRect.top+rc.top, m_ActRect.right+rc.left, m_ActRect.bottom+rc.top);
	}	
	return bto_parent;
}


