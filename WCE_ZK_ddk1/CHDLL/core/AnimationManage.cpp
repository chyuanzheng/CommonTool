#include "StdAfx.h"
#include "AnimationManage.h"
#include "RotateYAnimation.h"

struct T_ANI_SET
{
	T_ANI_SET()
	{
		m_start = m_end = m_count = 0;
		m_fromRvt = FALSE;

	}
	~T_ANI_SET()
	{
		TL_ACTION::iterator pos;
		for(pos=m_tlaction.begin(); pos!=m_tlaction.end(); pos++){
			delete (*pos);
		}
	}
	TL_ACTION m_tlaction;
	int m_start;
	int m_end;
	int m_count;
	BOOL m_fromRvt;//是否反方向动画
};
AnimationManage *AnimationManage::m_pInstance = NULL;
AnimationManage::AnimationManage()
{
	m_bIsStart = FALSE;
	m_uTimerID = RegisterTimer(ANIMOTION_TIME, ANIMOTION_TIMER_NAME);
}

AnimationManage::~AnimationManage()
{
	UnRegisterTimer(m_uTimerID);
}


AnimationManage* AnimationManage::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new AnimationManage;
	}
	return m_pInstance;
}

void AnimationManage::AddAction( HANDLE h,AnimationAction * action )
{
	T_ANI_SET* tas = (T_ANI_SET*)h;

	//只有不在进行动画的时候才可以加入动画
	ASSERT (!IsInAction(h));

	tas->m_tlaction.push_back(action);
}
//void AnimationManage::RemoveAction( HANDLE h,AnimationAction * action )
//{
//	T_ANI_SET* tas = (T_ANI_SET*)h;
//
//	//只有不在进行动画的时候才可以加入动画
//	ASSERT(tas->m_isInAction==FALSE);
//}

void AnimationManage::TimerTick(UINT nIDEvent)
{
	//static int lastTime = GetTickCount();
	//RETAILMSG(1, (TEXT("Animotion Time = %d\r\n"), GetTickCount()-lastTime));
	//lastTime = GetTickCount();
	TLIST_ANI_SET::iterator pos;
	BOOL ret = FALSE;
	for (pos=m_allSet.begin();pos!=m_allSet.end();)
	{
		BOOL ret2 = ProssAcion(*pos);
		if (!ret2)
		{
			pos = m_allSet.erase(pos);
		}
		else
		{
			pos++;
		}
		ret |= ret2;
	}
	if (!ret)
	{
		StopTimer(m_uTimerID);
		//AfxPostMessage(CTR_ALL_ANIMATION_END,NULL,NULL);
		m_bIsStart = FALSE;
	}
	//Sleep(0);
}

BOOL AnimationManage::ProssAcion( T_ANI_SET* tas )
{
	BOOL ret = TRUE;

	ASSERT(tas->m_count>=tas->m_start&&tas->m_start<=tas->m_end);
	TL_ACTION::iterator pos;
	for(pos=tas->m_tlaction.begin(); pos!=tas->m_tlaction.end(); pos++){
		(*pos)->PreAction(tas->m_count,tas->m_fromRvt);//处理动画
	}

	for(pos=tas->m_tlaction.begin(); pos!=tas->m_tlaction.end(); pos++){
		(*pos)->Action(tas->m_count,tas->m_fromRvt);//处理动画
	}

	//OutputDebugString(L"ani \r\n");
	if (tas->m_fromRvt)
	{
		tas->m_count--;
		if (tas->m_count < tas->m_start)
		{
			ret=FALSE;
		}
	}
	else
	{
		tas->m_count++;
		if (tas->m_count > tas->m_end)
		{
			ret=FALSE;
		}
	}
	return ret;//返回是否还有动画
}


void AnimationManage::StopAction( HANDLE h )
{
	T_ANI_SET* tas = (T_ANI_SET*)h;

	TLIST_ANI_SET::iterator pos = std::find(m_allSet.begin(),m_allSet.end(),tas);
	if(pos!=m_allSet.end())
	{
		m_allSet.erase(pos);
	}

	if(m_allSet.size() == 0)
	{
		StopTimer(m_uTimerID);
		m_bIsStart=FALSE;
	}
}


void AnimationManage::StartAction( HANDLE h,bool breset /*= true*/ )
{
	 T_ANI_SET* tas = (T_ANI_SET*)h;

	 if (breset)
	 {
		 if (tas->m_fromRvt)
		 {
			 tas->m_count  = tas->m_end;
		 }
		 else
		 {
			 tas->m_count = tas->m_start;
		 }
	 }

	 if (!m_bIsStart)
	 {
		 StartTimer(m_uTimerID);
		 m_bIsStart = TRUE;
	 }
	ASSERT(tas->m_tlaction.size()>0);

	TLIST_ANI_SET::iterator pos = std::find(m_allSet.begin(),m_allSet.end(),tas);
	if(pos==m_allSet.end())
	{
		m_allSet.push_back(tas);
	}

	TimerTick(m_uTimerID);
}

//void AnimationManage::StopAction()
//{
//	//TL_ACTION::iterator pos;
//	//for(pos=m_tlaction.begin(); pos!=m_tlaction.end(); pos++){
//	//	delete *pos;//析构动画
//	//}
//	m_tlaction.clear();
//	::KillTimer(AfxGetHWND(),ID_TIME_ANIMATION);
//	ASSERT (0==m_tlaction.size());
//	m_isInAction = FALSE;
//}

BOOL AnimationManage::IsInAction(HANDLE h)
{
	 T_ANI_SET* tas = (T_ANI_SET*)h;

	 TLIST_ANI_SET::iterator pos = std::find(m_allSet.begin(),m_allSet.end(),tas);
	 return (pos != m_allSet.end());
}


void AnimationManage::setTimeSection(HANDLE h, int start, int end )
{
	T_ANI_SET* tas = (T_ANI_SET*)h;
	ASSERT(end >  start);
	tas->m_start = start/ANIMOTION_TIME;
	tas->m_end = end/ANIMOTION_TIME;
	//setDirect(h,FALSE);//默认正方向
}



void AnimationManage::setDirect( HANDLE h,BOOL fromRvt )
{
	T_ANI_SET* tas = (T_ANI_SET*)h;
	tas->m_fromRvt = fromRvt;

}

BOOL AnimationManage::getDirect( HANDLE h )
{
	T_ANI_SET* tas = (T_ANI_SET*)h;
	return tas->m_fromRvt;
}
HANDLE AnimationManage::InitAniSet()
{
	T_ANI_SET  *tas =  new T_ANI_SET;
	//m_allSet.push_back(tas);
	return HANDLE(tas);
}

HANDLE AnimationManage::InitAniSet( const char* path )
{

	auto_ptr<TiXmlDocument> xmlDoc(new TiXmlDocument);
	BOOL bload = xmlDoc->LoadFile(path);
	ASSERT(bload);

	TiXmlElement *root = xmlDoc->RootElement();
	string ctrname = root->Value();
	if (ctrname != "AniSet")
	{
		ASSERT(0);
	}
	T_ANI_SET  *tas =  new T_ANI_SET;

	int nstart,nend;
	root->Attribute("start",&nstart);
	root->Attribute("end",&nend);
	setTimeSection(tas,nstart,nend);

	int ndrt;
	root->Attribute("direct",&ndrt);
	setDirect(tas,ndrt);

	TiXmlElement * ele_act = root->FirstChildElement();

	setAction(ele_act, tas);

	return HANDLE(tas);
}

void AnimationManage::DeInitAniSet( HANDLE h )
{
	T_ANI_SET  *tas =  (T_ANI_SET  *) h;
	TLIST_ANI_SET::iterator pos = std::find(m_allSet.begin(),m_allSet.end(),tas);
	if(pos!=m_allSet.end())
	{
		m_allSet.erase(pos);
	}
	delete tas;
}

void AnimationManage::setAction( TiXmlElement * ele_act, T_ANI_SET * tas )
{
	while(ele_act)
	{
		int data =0;
		string ctrname = ele_act->Value();
		if (ctrname != "Action")
		{
			ASSERT(0);
		}
		AnimationAction *ani_action =new AnimationAction();
		const CHAR *elename = ele_act->Attribute("name");
		if (NULL!=elename)
		{
			ani_action->SetName(elename);
		}
		ele_act->Attribute("delay",&data);
		ani_action->setDelay(data);
		ASSERT(tas->m_start <= ani_action->getDelay());
		ASSERT(tas->m_end > ani_action->getDelay());

		ele_act->Attribute("duration",&data);
		ani_action->setDuration(data);
		ASSERT(tas->m_start < ani_action->getDuration() + ani_action->getDelay() );
		ASSERT(tas->m_end >= ani_action->getDuration() + ani_action->getDelay() );

		if (ele_act->Attribute("after_draw",&data)!= NULL )
		{
			ani_action->setAfterDraw( bool(data) );
		}
		if( ele_act->Attribute("before_draw",&data) != NULL )
		{
			ani_action->setBeforeDraw( bool(data) );
		}

		tas->m_tlaction.push_back(ani_action);//加入action中 用户不需要再次加入

		TiXmlElement * ele_Ani = ele_act->FirstChildElement();
		setAnimation(ele_Ani, ani_action);

		ele_act = ele_act->NextSiblingElement();
	}
	ASSERT(tas->m_tlaction.size()>0);

}

void AnimationManage::setAnimation( TiXmlElement * ele_Ani, AnimationAction * ani_action )
{
	while(ele_Ani)
	{
		Animation * anim = NULL;
		string ctrname = ele_Ani->Value();

		if (ctrname == "Scale")
		{
			double fromX,toX,fromY,toY;
			ele_Ani->Attribute("fromX",&fromX);
			ele_Ani->Attribute("toX",&toX);
			ele_Ani->Attribute("fromY",&fromY);
			ele_Ani->Attribute("toY",&toY);
			anim = new ScaleAnimation(fromX,toX,fromY,toY,Animation::RELATIVE_TO_SELF,0.5f,Animation::RELATIVE_TO_SELF,0.5f);
			ani_action->AddAnimation(anim);
		}
		else if (ctrname == "alpha")
		{
			double from,to;
			ele_Ani->Attribute("from",&from);
			ele_Ani->Attribute("to",&to);
			anim = new AlphaAnimation(from,to);
			ani_action->AddAnimation(anim);
		}
		else if (ctrname == "Translate")
		{
			int fromX,toX,fromY,toY;
			ele_Ani->Attribute("fromX",&fromX);
			ele_Ani->Attribute("toX",&toX);
			ele_Ani->Attribute("fromY",&fromY);
			ele_Ani->Attribute("toY",&toY);
			anim = new TranslateAnimation(fromX,toX,fromY,toY);
			ani_action->AddAnimation(anim);
		}
		else if (ctrname == "rotate_y")
		{
			double from,to;
			ele_Ani->Attribute("from",&from);
			ele_Ani->Attribute("to",&to);
			anim = new RotateYAnimation(from,to);
			ani_action->AddAnimation(anim);
		}
		ASSERT(anim!=NULL);
		ele_Ani = ele_Ani->NextSiblingElement();
	}
	

}

AnimationAction * AnimationManage::GetAction( HANDLE h,const char* name/*=NULL*/ )
{
	T_ANI_SET  *tas =  (T_ANI_SET  *) h;
	
	TL_ACTION::iterator pos;
	ASSERT(tas->m_tlaction.size()>0);
	if (NULL == name)
	{
		pos=tas->m_tlaction.begin();
		return (*pos);
	}
	string strname = name;
	for(pos=tas->m_tlaction.begin(); pos!=tas->m_tlaction.end(); pos++){
		if ((*pos)->GetName() == strname )
		{
			return (*pos);
		}
	}
	//ASSERT(0);

	return NULL;
}


