#include "StdAfx.h"
#include "GxxAniPictureA.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"

HANDLE GxxAniPictureA::S_hAniScale = NULL;
GxxAniPictureA::GxxAniPictureA()
{
	//需要申请内存的变量都需要在默认构造函数中赋空值
	setDraw(false);
	if (S_hAniScale == NULL)
	{
		S_hAniScale = AnimationManage::GetInstance()->InitAniSet(AfxAddWorkPathA ("\\layout\\AniBtn1.xml"));
	}
}

GxxAniPictureA::~GxxAniPictureA()
{
	/*AnimationManage::GetInstance()->DeInitAniSet(m_hAniScale);*/
}





void GxxAniPictureA::Start( )
{
	if (NULL==m_hPicture)
	{
		return;
	}
	setDraw(true);
	AnimationAction * act = AnimationManage::GetInstance()->GetAction(S_hAniScale,"ani1");
	ASSERT(NULL!=act);
	act->ClearHandles();
	act->AddHandle(m_hPicture);
	act->SetAniRect(m_ActRect);

	act = AnimationManage::GetInstance()->GetAction(S_hAniScale,"ani2");
	if(NULL!=act)
	{
		act->ClearHandles();
		act->AddHandle(m_hPicture);
		act->SetAniRect(m_ActRect);
	}
	AnimationManage::GetInstance()->StartAction(S_hAniScale);

}

void GxxAniPictureA::Stop()
{
	setDraw(false);
}




