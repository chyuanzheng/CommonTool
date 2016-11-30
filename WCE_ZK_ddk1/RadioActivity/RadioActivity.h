#pragma once
#include "RadioDllModule.h"
#include "Activity.h"
#include "ControlHelp.h"
#include "GxxAniLable.h"

#include "GxxControlGroup.h"
#include "Radiocon.h"
#include "GXNotify.h"

#define PER_PAGE_NUM 3	//每页的台数
#define TOTAL_FM_PAGE 6
#define TOTAL_AM_PAGE 4

#define DECLARE_MSGHANDLER(theFun, theClass) \
	static DWORD theFun(CHardware *pControl, DWORD dwParam, UINT msg, WPARAM wParam, LPARAM lParam)\
{\
	theClass *pThis = (theClass *)dwParam;\
	return pThis->theFun(pControl, msg, wParam, lParam);\
}\
	DWORD theFun(CHardware *pControl, UINT msg, WPARAM wParam, LPARAM lParam);

class GxxLableSet;
class CE_RADIOACTIVITY_API  RadioActivity : public Activity
{
public:
	RadioHardware	*pRadioHardware;

	RadioActivity();
	virtual ~RadioActivity ();
	virtual  void onCreate();
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	
	static Activity* CreateControl();
	virtual void  onResume();
	virtual void onPause();
	virtual void onStop();

	DECLARE_MSGHANDLER(RadioSearchHandler, RadioActivity)

	int curFMFreq;
	int curAMFreq;
	int curFMCH;
	int curAMCH;

	int curFMPage;
	int totalFMPage;
	int curAMPage;
	int totalAMPage;

	

	void SetFreqNow(int freq, bool bredraw);	// 设置频率显示
	void SetPage(int page);

	void AutoSearch();

	void PageUp();
	void PageDown();

	void Band();	//切换频率

	
	void ClickFreq(int iNum);	//单击频率
	void LongClickFreq(int iNum, GxxAniLable* pControl);		//长按频率按钮
	void SelectFreq(int iNum);	//按钮设定为选中状态

	//单步
	void DownStep();
	void UpStep();

	//搜台
	void SearchNext();
	void SearchPrev();

	void SwitchInfoOrMain();


	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, RadioActivity);

private:


	GxxAniLable* pLabel_CurrentFreq;	//显示频率
	GxxAniLable* pLabel_Auto_Memory;	//自动搜台
	GxxAniLable* pLabel_SwitchBand;	//当道频道
	GxxAniLable* pLabel_CurrentBand;	//当前频道
	GxxAniLable* pLabel_CurrentFreqNum;	//频率的ID

	GxxAniLable* pInc_Label_Return_Main;	//返回主界面

	GxxString strUnits;	//频率单位

	//显示搜到的频率
	GxxAniLable *pLabFreq[PER_PAGE_NUM];


	//上下翻页
	GxxAniLable* pLabel_PageUp;
	GxxAniLable* pLabel_PageDown;

	//单步调台
	GxxAniLable* pLabel_SearchPrev;
	GxxAniLable* pLabel_SearchNext;

	//跳到信息界面
	GxxAniLable* pLabel_SwitchInfoOrMain;

	GxxControlGroup* pControlGroup_info;
	GxxControlGroup* pControlGroup_main;

	//跳转到设置界面
	GxxAniLable* pLabelToSetupAudio;
	GxxLableSet *m_lable_set;
	GxxSwText *pLabel_CurrentFreq_invert;
	GxxSwText *pLabel_uint_invert;
	GxxSwText *pLabel_uint;

	//显示当前的频率ID号
	void ShowCurrentFreqNum(int iNum);

	DECLARE_NOTIFY_CALLBACK(RestoreDefault, RadioActivity);
};


