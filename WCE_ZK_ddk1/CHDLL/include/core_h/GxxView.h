#pragma once

#include "DllDefine.h"

//#include "SkiaBitmapManager.h"

#pragma warning(disable:4800) //

class GxxView;
typedef  list<GxxView*> ControlList;
typedef map<string, ControlList *>  TMapStr_CtrList;

typedef GxxView* (*FunCrtControl)();
typedef list<HANDLE> TL_HANDLE;


class CE_CONTROL_API GxxView 
{
	friend class CWnd;
	friend class CCommonWnd;
	friend class CPopupWnd;
	friend class Activity;
	friend class SkiaBitmapManager;
public:
	GxxView( );
	~GxxView( );
	//控件根据 ele中的参数设置自己的属性
	//virtual void TimerTick(UINT nIDEvent){}
	void setMoveRect(int x_len, int y_len);//移动所有控件
	virtual void setCtrLayout( TiXmlElement * ele);//
	void   setCtrName(TiXmlElement * ele);
	void   setCtrName(const char * name);
	//const char *getCtrName(){return m_name.c_str();}
	const string& getCtrName(){return m_sCtrName;}

	bool setCtrRect(TiXmlElement * ele );//ele中读出左上,长度，高度。
	bool setCtrRect(TiXmlElement * ele,int left,int top);//x_pos，y_pos是左上角，ele中读出，长度，高度。
	bool setCtrRect(int width,int height,TiXmlElement * ele);//ele中读出，左上角，右上角。
	bool setCtrRect(int left,int top,int length,int height){::SetRect(&m_ActRect,left,top,left+length,top+height); return true;}//左上,长度，高度。
	bool setCtrRectUseCenter(TiXmlElement * ele,int width,int height );
	bool setCtrRectUseCenter(TiXmlElement * ele );
	bool setCtrRectUseCenter(int x_center,int y_center,int lenth,int height){::SetRect(&m_ActRect,x_center-lenth/2,y_center-height/2,x_center+lenth/2,y_center+height/2); return true;}//中心点，长度，高度。
	void setCtrRectUseLeftTop(int left,int top,int right,int bottom){::SetRect(&m_ActRect,left,top,right,bottom);}//左上右下
	void setCtrRect(const RECT & rt ){m_ActRect = rt;}
	const RECT &getCtrRect() {return m_ActRect;}
	void getCtrRect( RECT & rt ) {rt=m_ActRect;}//这个函数不建议再使用,请使用以上函数
	

	static void setSelView(GxxView *view,bool onlypaint = false){s_selView = view; S_OnlyPaintSel = onlypaint;}
	static GxxView *getSelView(){ return s_selView;}
	static void clearSelView(){s_selView = NULL;}
	void invalidateRect();





	void	setEnable(bool e);
	bool	getEnable(){return m_enable;}
	void	setDraw(bool e){m_bDraw = e;}
	bool	getDraw(){return m_bDraw;}
	
	GxxView *findViewByName(const CHAR* name);//根据名字找到子控件
	GxxView *safeFindViewByName(const CHAR* name)
	{
		GxxView * ctr = findViewByName(name); ASSERT(NULL!=ctr); return ctr;
	}

	BOOL	removeCtrl(GxxView* control);
	void    deleteAllCtrls();
	void    deleteOneCtrl(GxxView *v);

	BOOL	AddCtrl(GxxView* control);
	BOOL	AddCtrl(ControlList* ctrList);
	BOOL    AddCtrl(GxxView* control, GxxView* bef);
	//重新加入控件，先会清空。
	void	ClearCtrls(){m_pCtrlVet->clear();}
	int     getCtrlsSize(){return m_pCtrlVet->size();}
	ControlList *getCtrlsList(){return m_pCtrlVet;}
	bool    findView(GxxView *v){ return std::find(m_pCtrlVet->begin(),m_pCtrlVet->end(),v) !=  m_pCtrlVet->end();}
	GxxView * getParentView(){return m_ParentCtrl;}
	GxxView * saftGetParentView(){ ASSERT(NULL!=m_ParentCtrl); return m_ParentCtrl;}
	void    setParentView(GxxView *p){m_ParentCtrl = p;}

	void    setOnlyDrawActRect(bool b_only){m_bOnlyDrawActRect = b_only;} 
	bool    getOnlyDrawActRect(){ return m_bOnlyDrawActRect;} 
	
	bool TranslateMessage( UINT nMsg, WPARAM wParam, LPARAM lParam ){return Response(nMsg,wParam,lParam);}

			//控件的绘制函数入口
	virtual void Paint();//**
	
	//控件的消息函数入口
	virtual BOOL DealCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);

protected:
	void setResume();
	void setPause();
	bool checkToParent(TiXmlElement * ele );
	virtual void onResume(){}
	virtual void onPause(){}
	bool InMyArea( int x, int y )
	{
		POINT pt = {x,y};
		return ::PtInRect(&m_ActRect, pt);
	}
	bool InMyArea( LPARAM lParam ){ return InMyArea( LOWORD( lParam ), HIWORD( lParam ) );}
	bool InMyArea(const RECT &rc,int x, int y)
	{ 
		POINT pt = {x,y};
		return ::PtInRect(&rc, pt);
	}

	virtual void  onEnable(bool e){}
	
	//请在onCreate调用setContentView;
	virtual void onCreate();
	// 完全释放时，记得删除所有的子控件
	virtual void  onDestroy();
	

	void DoPaint();//**
	BOOL DealSelCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}


	void PaintSelView();

    //本控件的消息处理
	

	
	//本控件的绘制
	virtual void Draw( ){};

	//加载子控件用这个函数
	void setCtrList( TiXmlElement * ele,ControlList *ctrList=NULL );
	BOOL loadXmlView( TiXmlElement * ele );
	void setEnableFromXml( TiXmlElement * ele );

	//void DrawRoWnd(HANDLE handle,const RECT *rectDst,UINT alpha=255 );
	
	



	
	virtual void    onMoveRect(int x_len, int y_len ){ ::SetRect(&m_ActRect,m_ActRect.left+x_len,m_ActRect.top+y_len,m_ActRect.right+x_len,m_ActRect.bottom+y_len);}//移动
	
	RECT        m_ActRect;//显示的RECT
    //CImagesManager *pImageManager;
	
	ControlList  *m_pCtrlVet;//所有子控件

	
private:

	GxxView	 *m_ParentCtrl; //父控件  
	string       m_sCtrName;
	bool          m_enable;
	bool          m_bDraw;

	bool          m_bOnlyDrawActRect;//是否只画本区域。
	
	static TMapStr_CtrList  s_allList;//所有外部的list
	static      GxxView* s_selView;//处于选中的View
	static      bool S_OnlyPaintSel;
	
	
};

