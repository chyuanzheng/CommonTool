#pragma once
#include "GxxView.h"
#include "AnimationAction.h"
#include "GxxPicture.h"
class Activity;
typedef Activity* (*FunCrtActivity)();

//string activity的名字 
typedef map<string, Activity *>  TMapStr_Activity;
typedef map<string, int>  TMapStr_Int;
typedef map<string, string>  TMapStr_Str;

#define  TEST_ACTIVITY   12345

class CE_CONTROL_API Activity : public GxxPicture
{
public:
	typedef	enum
	{
		T_DRAW_TRASITION,		
		T_NEED_ENABLE,
		T_OK_USE
	}T_TRASIT;//界面切换的状态



	Activity();
	virtual bool GetAnimation(){ return true;}
	static void SetActivityBackColor(UINT color){s_backColor = color;}
	static UINT GetActivityBackColor(){return s_backColor;}
	static bool GetSetupNotOperate(){return m_bInSetupNotOperate;}

	//setContentView将生成子控件，并设定子控件的参数
	BOOL setContentView(const CHAR* layout);
	void setBackColor(UINT color);
	static void overridePendingTransition( GxxView *topView,GxxView *bottomView,HANDLE hAni_handle );
	BOOL DealActivityMsg( UINT nMsg, WPARAM wParam, LPARAM lParam );

	void RetToFucActivity();

	

	static Activity * startActivity(Activity *pfomer,const string& tostart,const string& param_id = "");
	static void failedStart(const string& tostart);

	

	//bforce = true 强制切换,pModuleAct需要启动的Activity，pActActivity是当前的Activity
	static bool DoTransiteActivity( Activity * pModuleAct, Activity * pActActivity, const string& param_id,bool bforce = false );



	
	static Activity * findActivity(const string& tostart);
	static Activity * GetActiveActiviy(){return s_active;}
	static Activity * GetPopupActiveActiviy(){return s_popup_active;}
	static Activity * GetPreActiviy(){return s_preAct;}
	static void EnableActivity( const string &actName,bool b_enable );

	static void AddActivityDll(const string & act,const string & dll);
	static	void loadDllModule( const char * strName, const char * strActivity );
	static	void StartAllModule();

	bool    finish();




	virtual ~Activity ();
	virtual void Draw( );

	//Paint()不可以再被继承
	virtual void Paint();

	static bool s_bluetooth_exist;//有无蓝牙设备
	static bool s_is_init_sound;//有无蓝牙设备
protected:

	//当activity 不再处于响应消息的状态时 会调用 onPause()
	//当activity 再处于响应消息的状态时 会调用 onResume()
	static void CheckAccOff();
	virtual void onStart(){}
	virtual void onStop();

	static void SetContentInt(const string &name,int n);
	static void SetContentStr(const string &name,const string &s);

	static bool GetContentInt(const string &name,int &n);
	static bool GetContentStr(const string &name,string &s);
	static void SetPermitStart(bool b){m_bPermitStart = b;}
	static void SetBrake( bool b );
	static Activity *GetFuctionAct(){ return s_fuctionAct;}
	static void  SetMainActivity(Activity *act){S_testMain = act;}//test
	

	static bool   s_isAccOff;
	static HANDLE s_hAniScaleUp;
	static HANDLE s_hAniScaleDown;
	static HANDLE s_hAniApha;
	static HANDLE s_hAniRotateY;

	static T_TRASIT s_bInTransition;//是否正在进行界面切换
	static HANDLE    s_handleBtpTrasitBottom;//退出动画
	static HANDLE    s_handleBtpTrasitTop;//进入动画
	static AnimationAction *  s_bottomAction;
	static AnimationAction * s_topAction;
	static TMapStr_Str S_ActivityDllContainer;//所以延后启动的模块

	string m_param;
	bool   m_isMainPad;//是否是主页
	static bool   S_isPowerInLanguage;//是否为B+断电，显示语言界面中
	
private:
	static void startPopupActivity(const string& tostart);
	static bool transiteActivity( const string &tostart, Activity * pActActivity, const string& param_id );

	void CheckTransitionStatus();
	static void defaultPendingTransition();
	void renewParent();
	




	
	static TMapStr_Int s_int_content;
	static TMapStr_Str s_str_content;

	static Activity * s_active;//当前活动的activity
	static Activity * s_popup_active;//当前活动的activity
	static Activity * s_preAct;//之前活动的activiy
	static Activity * s_fuctionAct;//之前活动的功能的activiy
	static TMapStr_Activity s_allActivity;
	static bool m_bBrake;
	static bool m_bInSetupNotOperate;//是否是Setup不能操作
	

	Activity *m_pPreActivity ;
	Activity *m_pNextActiviy;
	//UINT   *m_pbackColor;//背景色彩
	static UINT   s_backColor;//背景色彩
	

	BOOL m_bShowTop;
	BOOL m_bShowBottom;
	static bool m_bPermitStart;//是否允许 startActivity
	string  m_strActivityName;

	static Activity *S_testMain;//test
	

	

};

