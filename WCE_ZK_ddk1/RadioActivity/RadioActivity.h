#pragma once
#include "RadioDllModule.h"
#include "Activity.h"
#include "ControlHelp.h"
#include "GxxAniLable.h"

#include "GxxControlGroup.h"
#include "Radiocon.h"
#include "GXNotify.h"

#define PER_PAGE_NUM 3	//ÿҳ��̨��
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

	

	void SetFreqNow(int freq, bool bredraw);	// ����Ƶ����ʾ
	void SetPage(int page);

	void AutoSearch();

	void PageUp();
	void PageDown();

	void Band();	//�л�Ƶ��

	
	void ClickFreq(int iNum);	//����Ƶ��
	void LongClickFreq(int iNum, GxxAniLable* pControl);		//����Ƶ�ʰ�ť
	void SelectFreq(int iNum);	//��ť�趨Ϊѡ��״̬

	//����
	void DownStep();
	void UpStep();

	//��̨
	void SearchNext();
	void SearchPrev();

	void SwitchInfoOrMain();


	DECLARE_NOTIFY_CALLBACK(NotifyWheel_Msg, RadioActivity);

private:


	GxxAniLable* pLabel_CurrentFreq;	//��ʾƵ��
	GxxAniLable* pLabel_Auto_Memory;	//�Զ���̨
	GxxAniLable* pLabel_SwitchBand;	//����Ƶ��
	GxxAniLable* pLabel_CurrentBand;	//��ǰƵ��
	GxxAniLable* pLabel_CurrentFreqNum;	//Ƶ�ʵ�ID

	GxxAniLable* pInc_Label_Return_Main;	//����������

	GxxString strUnits;	//Ƶ�ʵ�λ

	//��ʾ�ѵ���Ƶ��
	GxxAniLable *pLabFreq[PER_PAGE_NUM];


	//���·�ҳ
	GxxAniLable* pLabel_PageUp;
	GxxAniLable* pLabel_PageDown;

	//������̨
	GxxAniLable* pLabel_SearchPrev;
	GxxAniLable* pLabel_SearchNext;

	//������Ϣ����
	GxxAniLable* pLabel_SwitchInfoOrMain;

	GxxControlGroup* pControlGroup_info;
	GxxControlGroup* pControlGroup_main;

	//��ת�����ý���
	GxxAniLable* pLabelToSetupAudio;
	GxxLableSet *m_lable_set;
	GxxSwText *pLabel_CurrentFreq_invert;
	GxxSwText *pLabel_uint_invert;
	GxxSwText *pLabel_uint;

	//��ʾ��ǰ��Ƶ��ID��
	void ShowCurrentFreqNum(int iNum);

	DECLARE_NOTIFY_CALLBACK(RestoreDefault, RadioActivity);
};


