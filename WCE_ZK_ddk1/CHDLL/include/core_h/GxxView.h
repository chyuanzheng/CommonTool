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
	//�ؼ����� ele�еĲ��������Լ�������
	//virtual void TimerTick(UINT nIDEvent){}
	void setMoveRect(int x_len, int y_len);//�ƶ����пؼ�
	virtual void setCtrLayout( TiXmlElement * ele);//
	void   setCtrName(TiXmlElement * ele);
	void   setCtrName(const char * name);
	//const char *getCtrName(){return m_name.c_str();}
	const string& getCtrName(){return m_sCtrName;}

	bool setCtrRect(TiXmlElement * ele );//ele�ж�������,���ȣ��߶ȡ�
	bool setCtrRect(TiXmlElement * ele,int left,int top);//x_pos��y_pos�����Ͻǣ�ele�ж��������ȣ��߶ȡ�
	bool setCtrRect(int width,int height,TiXmlElement * ele);//ele�ж��������Ͻǣ����Ͻǡ�
	bool setCtrRect(int left,int top,int length,int height){::SetRect(&m_ActRect,left,top,left+length,top+height); return true;}//����,���ȣ��߶ȡ�
	bool setCtrRectUseCenter(TiXmlElement * ele,int width,int height );
	bool setCtrRectUseCenter(TiXmlElement * ele );
	bool setCtrRectUseCenter(int x_center,int y_center,int lenth,int height){::SetRect(&m_ActRect,x_center-lenth/2,y_center-height/2,x_center+lenth/2,y_center+height/2); return true;}//���ĵ㣬���ȣ��߶ȡ�
	void setCtrRectUseLeftTop(int left,int top,int right,int bottom){::SetRect(&m_ActRect,left,top,right,bottom);}//��������
	void setCtrRect(const RECT & rt ){m_ActRect = rt;}
	const RECT &getCtrRect() {return m_ActRect;}
	void getCtrRect( RECT & rt ) {rt=m_ActRect;}//���������������ʹ��,��ʹ�����Ϻ���
	

	static void setSelView(GxxView *view,bool onlypaint = false){s_selView = view; S_OnlyPaintSel = onlypaint;}
	static GxxView *getSelView(){ return s_selView;}
	static void clearSelView(){s_selView = NULL;}
	void invalidateRect();





	void	setEnable(bool e);
	bool	getEnable(){return m_enable;}
	void	setDraw(bool e){m_bDraw = e;}
	bool	getDraw(){return m_bDraw;}
	
	GxxView *findViewByName(const CHAR* name);//���������ҵ��ӿؼ�
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
	//���¼���ؼ����Ȼ���ա�
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

			//�ؼ��Ļ��ƺ������
	virtual void Paint();//**
	
	//�ؼ�����Ϣ�������
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
	
	//����onCreate����setContentView;
	virtual void onCreate();
	// ��ȫ�ͷ�ʱ���ǵ�ɾ�����е��ӿؼ�
	virtual void  onDestroy();
	

	void DoPaint();//**
	BOOL DealSelCtrlMsg( UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL Response(  UINT nMsg, WPARAM wParam, LPARAM lParam ){return FALSE;}


	void PaintSelView();

    //���ؼ�����Ϣ����
	

	
	//���ؼ��Ļ���
	virtual void Draw( ){};

	//�����ӿؼ����������
	void setCtrList( TiXmlElement * ele,ControlList *ctrList=NULL );
	BOOL loadXmlView( TiXmlElement * ele );
	void setEnableFromXml( TiXmlElement * ele );

	//void DrawRoWnd(HANDLE handle,const RECT *rectDst,UINT alpha=255 );
	
	



	
	virtual void    onMoveRect(int x_len, int y_len ){ ::SetRect(&m_ActRect,m_ActRect.left+x_len,m_ActRect.top+y_len,m_ActRect.right+x_len,m_ActRect.bottom+y_len);}//�ƶ�
	
	RECT        m_ActRect;//��ʾ��RECT
    //CImagesManager *pImageManager;
	
	ControlList  *m_pCtrlVet;//�����ӿؼ�

	
private:

	GxxView	 *m_ParentCtrl; //���ؼ�  
	string       m_sCtrName;
	bool          m_enable;
	bool          m_bDraw;

	bool          m_bOnlyDrawActRect;//�Ƿ�ֻ��������
	
	static TMapStr_CtrList  s_allList;//�����ⲿ��list
	static      GxxView* s_selView;//����ѡ�е�View
	static      bool S_OnlyPaintSel;
	
	
};

