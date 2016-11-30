#pragma once
#include "GxxView.h"
#include "AnimationAction.h"
#include "GxxPicture.h"
class Activity;
typedef Activity* (*FunCrtActivity)();

//string activity������ 
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
	}T_TRASIT;//�����л���״̬



	Activity();
	virtual bool GetAnimation(){ return true;}
	static void SetActivityBackColor(UINT color){s_backColor = color;}
	static UINT GetActivityBackColor(){return s_backColor;}
	static bool GetSetupNotOperate(){return m_bInSetupNotOperate;}

	//setContentView�������ӿؼ������趨�ӿؼ��Ĳ���
	BOOL setContentView(const CHAR* layout);
	void setBackColor(UINT color);
	static void overridePendingTransition( GxxView *topView,GxxView *bottomView,HANDLE hAni_handle );
	BOOL DealActivityMsg( UINT nMsg, WPARAM wParam, LPARAM lParam );

	void RetToFucActivity();

	

	static Activity * startActivity(Activity *pfomer,const string& tostart,const string& param_id = "");
	static void failedStart(const string& tostart);

	

	//bforce = true ǿ���л�,pModuleAct��Ҫ������Activity��pActActivity�ǵ�ǰ��Activity
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

	//Paint()�������ٱ��̳�
	virtual void Paint();

	static bool s_bluetooth_exist;//���������豸
	static bool s_is_init_sound;//���������豸
protected:

	//��activity ���ٴ�����Ӧ��Ϣ��״̬ʱ ����� onPause()
	//��activity �ٴ�����Ӧ��Ϣ��״̬ʱ ����� onResume()
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

	static T_TRASIT s_bInTransition;//�Ƿ����ڽ��н����л�
	static HANDLE    s_handleBtpTrasitBottom;//�˳�����
	static HANDLE    s_handleBtpTrasitTop;//���붯��
	static AnimationAction *  s_bottomAction;
	static AnimationAction * s_topAction;
	static TMapStr_Str S_ActivityDllContainer;//�����Ӻ�������ģ��

	string m_param;
	bool   m_isMainPad;//�Ƿ�����ҳ
	static bool   S_isPowerInLanguage;//�Ƿ�ΪB+�ϵ磬��ʾ���Խ�����
	
private:
	static void startPopupActivity(const string& tostart);
	static bool transiteActivity( const string &tostart, Activity * pActActivity, const string& param_id );

	void CheckTransitionStatus();
	static void defaultPendingTransition();
	void renewParent();
	




	
	static TMapStr_Int s_int_content;
	static TMapStr_Str s_str_content;

	static Activity * s_active;//��ǰ���activity
	static Activity * s_popup_active;//��ǰ���activity
	static Activity * s_preAct;//֮ǰ���activiy
	static Activity * s_fuctionAct;//֮ǰ��Ĺ��ܵ�activiy
	static TMapStr_Activity s_allActivity;
	static bool m_bBrake;
	static bool m_bInSetupNotOperate;//�Ƿ���Setup���ܲ���
	

	Activity *m_pPreActivity ;
	Activity *m_pNextActiviy;
	//UINT   *m_pbackColor;//����ɫ��
	static UINT   s_backColor;//����ɫ��
	

	BOOL m_bShowTop;
	BOOL m_bShowBottom;
	static bool m_bPermitStart;//�Ƿ����� startActivity
	string  m_strActivityName;

	static Activity *S_testMain;//test
	

	

};

