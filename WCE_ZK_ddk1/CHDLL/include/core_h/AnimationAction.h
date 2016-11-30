#pragma once


#include "DllDefine.h"
#include "Animation.h"
#include "ScaleAnimation.h"
#include "AlphaAnimation.h"
#include "TranslateAnimation.h"

typedef list<Animation *> TL_ANIMATION;




class CE_CONTROL_API AnimationAction
{
public:
	friend class AnimationManage;
	AnimationAction();
	~AnimationAction();
	//���� false ��ʾ�������
	void AddHandle(HANDLE h);
	void RemoveHandle( HANDLE h );
	void ClearHandles();
	void AddAnimation(Animation * ani);
	void SetAniRect( const RECT & rt);//������Ҫ���µ�����
	void SetName(const char* name){m_name = name;}
	const char*GetName(){return m_name.c_str();}


	void setDuration(UINT t);
	int getDuration(){return m_lenth;}
	void setDelay(int t);//���ö�����ʱ
	int getDelay(){return m_delay;}
	Animation * getAnimation(const char *name = NULL);

private:
	void Action(int tick,BOOL fromRvt);
	void PreAction(int tick,BOOL fromRvt);
	void setAfterDraw( bool b ){m_bAfter_draw = b;}
	void setBeforeDraw( bool b ){m_bBefore_draw = b;}

	TL_ANIMATION m_listAnimation;
	TL_HANDLE    m_listHandle;
	RECT         m_Rect;
	string       m_name;

	UINT m_lenth;//����
	int m_delay;//�ڼ���

	bool   m_bAfter_draw;
	bool   m_bBefore_draw;
};

