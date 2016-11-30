#pragma once
#include "GxxPicture.h"
#include "AnimationManage.h"
#include "GxxTimer.h"
#include "GXNotify.h"

#define  FREQ_COUNT  33
#define  BAND_COUNT 7
#define  MAX_Q 3
#define  MIN_Q 1
#define		MES_INVALIDATE              152011   //向父控件发送设置失败
class  GxxParamPad : public GxxView
{
public:
	GxxParamPad();
	virtual ~GxxParamPad();
	static GxxView* CreateControl();
	void SetFlat(bool bInvalid = false);
	int GetLevel();
	int MoveLevel(int nAdd);
	int GetFreq(bool &bmax,bool &bmin);
	int MoveFreq(int nAdd,bool &bmax,bool &bmin);
	int GetQValue();
	int MoveQValue(int nAdd);
	void NextBand();
	void SetPre( int nth );
	void SavePre( int nth );
protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );
	virtual void Draw( );
	void checkValue();

	void SetAllPEQ() ;

	void SetCurFreq();
private:
	DECLARE_NOTIFY_CALLBACK(SetDefault, GxxParamPad);	

private:
	static  const int C_FreqRate[FREQ_COUNT];
	int		m_nLineWidth;
	int     m_nDotLen;

	int		m_nSetpWidth;
	int		m_nSetpHeight;
	RECT     m_drawRect;

	char		*  m_freqLevel;
	BYTE		*  m_qValue;
	BYTE		*  m_bandFreq;

	BYTE        m_allLevel[FREQ_COUNT];//中间值，方便绘图
	BYTE        m_curBand;


	GxxPicture *m_pPicBack;

	GxxPicture *m_pDotLine;
	GxxPicture *m_pFullLine;
	GxxPicture *m_pCurLine;
	GxxPicture *m_pNorDot;
	GxxPicture *m_pLineDot;
	GxxPicture *m_pCurDot;
	
};
