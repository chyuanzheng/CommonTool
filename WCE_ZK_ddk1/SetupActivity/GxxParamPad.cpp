#include "StdAfx.h"
#include "GxxParamPad.h"
#include "GxxProgressV.h"
#include "GxxSwText.h"
#include "XmlDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
#include "AVSet.h"
#include "VolumeControl.h"

const int GxxParamPad::C_FreqRate[FREQ_COUNT] = {20,25,31.5,40,50,63,80,100,125,160,200,250,315,400,500,630,800,1000,1200,1600,2000,2600,3200,4000,5800,6400,7200,8000,9000,10000,12000,16000,20000};

#define  MAX_LEVEL 7


#define  FREQ_STEP 4
static RegisterHelp help("GxxParamPad", GxxParamPad::CreateControl);
GxxView* GxxParamPad::CreateControl()
{
	return new GxxParamPad;
}

GxxParamPad::GxxParamPad():m_freqLevel(sysConfig.sysParam.curFreqLevel), m_qValue(sysConfig.sysParam.curQLevel), m_bandFreq(sysConfig.sysParam.curBandFreq)
{
	int nnn = sizeof(sysConfig.sysParam);
	checkValue();
	//SetAllPEQ();
	m_curBand = 0;
	m_pPicBack = new GxxPicture;

	m_pDotLine = new GxxPicture;
	m_pFullLine = new GxxPicture;
	m_pCurLine = new GxxPicture;
	m_pNorDot = new GxxPicture;
	m_pLineDot = new GxxPicture;
	m_pCurDot = new GxxPicture;

	Notify notify;
	notify.dwParam = this;
	notify.funNotify = SetDefault;
	GXNotify::RegisterNotifyHandler("eq_default_set", notify);

	//if ((bool)sysConfig.sysParam.curDefeat)// 如果是1则需要预设成默认
	SetDefault(sysConfig.sysParam.curDefeat,0);
}

GxxParamPad::~GxxParamPad()
{
	delete m_pPicBack;

	delete m_pDotLine;
	delete m_pFullLine;
	delete m_pCurLine;
	delete m_pNorDot;
	delete m_pLineDot;
	delete m_pCurDot;
}


void GxxParamPad::checkValue()
{
	int i = 0;
	for (i = 0; i <BAND_COUNT; i++)
	{
		if (m_freqLevel[i]>MAX_LEVEL || m_freqLevel[i] < -MAX_LEVEL)
		{
			break;
		}
		if (m_qValue[i]>MAX_Q || m_qValue[i] < MIN_Q)
		{
			break;
		}

		if (m_bandFreq[i]>FREQ_STEP*(i+2) || m_bandFreq[i] < FREQ_STEP*i)
		{
			break;
		}

		if (i>0)
		{
			if (m_bandFreq[i] <= m_bandFreq[i-1])
			{
				break;
			}
		}
	}

	if (i != BAND_COUNT)
	{
		SetFlat();
	}

	

}


void GxxParamPad::SetAllPEQ()
{

	for (int i = 0; i <BAND_COUNT; i++)
	{
		ASSERT (m_bandFreq[i]>=0 && m_bandFreq[i]< FREQ_COUNT );
		AVSET::SetPEQ(i,C_FreqRate[m_bandFreq[i]],m_qValue[i]*30,m_freqLevel[i]*2);	
	}

}


void GxxParamPad::SetFlat( bool bInvalid /*= false*/ )
{
	for (int i = 0; i <BAND_COUNT; i++)
	{
		m_freqLevel[i] = 0;
		m_qValue[i] = 1;
		m_bandFreq[i] = FREQ_STEP*(i+1);

		sysConfig.WriteConfig((BYTE *)&m_freqLevel[i]);
		sysConfig.WriteConfig(&m_qValue[i]);
		sysConfig.WriteConfig(&m_bandFreq[i]);
	}
	SetAllPEQ();
	if (bInvalid)
	{
		invalidateRect();
	}
}

// 如果param1是1则需要预设成默认
LRESULT GxxParamPad::SetDefault(DWORD param1, DWORD param2)
{
	if (bool(param1))
	{
		for (int i = 0; i <BAND_COUNT; i++)
		{
			AVSET::SetPEQ(i,C_FreqRate[FREQ_STEP*(i+1)], 30,0);	
		}
	}
	else
	{
		SetAllPEQ();
	}
	return 0;
}

void GxxParamPad::SavePre( int nth )
{
	ASSERT(nth>=1&&nth<=3);

	char		*  t_freqLevel=sysConfig.sysParam.presetFreqLevel+(nth-1)*BAND_COUNT;
	BYTE		*  t_qValue=sysConfig.sysParam.presetQLevel+(nth-1)*BAND_COUNT;
	BYTE		*  t_bandFreq=sysConfig.sysParam.presetBandFreq+(nth-1)*BAND_COUNT;

	memcpy(t_freqLevel, m_freqLevel, sizeof(sysConfig.sysParam.curFreqLevel) );
	memcpy(t_qValue, m_qValue, sizeof(sysConfig.sysParam.curQLevel) );
	memcpy(t_bandFreq, m_bandFreq,sizeof(sysConfig.sysParam.curBandFreq) );

	for (int i = 0; i <BAND_COUNT; i++)
	{
		sysConfig.WriteConfig((BYTE *)&t_freqLevel[i]);
		sysConfig.WriteConfig(&t_qValue[i]);
		sysConfig.WriteConfig(&t_bandFreq[i]);
	}
}


void GxxParamPad::SetPre( int nth )
{
	ASSERT(nth>=1&&nth<=3);


	m_freqLevel=sysConfig.sysParam.presetFreqLevel+(nth-1)*BAND_COUNT;
	m_qValue=sysConfig.sysParam.presetQLevel+(nth-1)*BAND_COUNT;
	m_bandFreq=sysConfig.sysParam.presetBandFreq+(nth-1)*BAND_COUNT;
	checkValue();//

	memcpy(sysConfig.sysParam.curFreqLevel, m_freqLevel, sizeof(sysConfig.sysParam.curFreqLevel) );
	memcpy(sysConfig.sysParam.curQLevel, m_qValue, sizeof(sysConfig.sysParam.curQLevel) );
	memcpy(sysConfig.sysParam.curBandFreq, m_bandFreq, sizeof(sysConfig.sysParam.curBandFreq) );

	m_freqLevel = sysConfig.sysParam.curFreqLevel;
	m_qValue = sysConfig.sysParam.curQLevel;
	m_bandFreq = sysConfig.sysParam.curBandFreq;

	SetAllPEQ();

	for (int i = 0; i <BAND_COUNT; i++)
	{
		sysConfig.WriteConfig((BYTE *)&m_freqLevel[i]);
		sysConfig.WriteConfig(&m_qValue[i]);
		sysConfig.WriteConfig(&m_bandFreq[i]);
	}
	invalidateRect();
	getParentView()->TranslateMessage(MES_INVALIDATE,0,0);

}


void GxxParamPad::SetCurFreq()
{
	sysConfig.WriteConfig((BYTE *)&m_freqLevel[m_curBand]);
	sysConfig.WriteConfig(&m_qValue[m_curBand]);
	sysConfig.WriteConfig(&m_bandFreq[m_curBand]);
	AVSET::SetPEQ(m_curBand,C_FreqRate[m_bandFreq[m_curBand]],m_qValue[m_curBand]*30,m_freqLevel[m_curBand]*2);	
}

int GxxParamPad::GetLevel()
{
	return m_freqLevel[m_curBand];
}

int GxxParamPad::MoveLevel( int nAdd )
{
	m_freqLevel[m_curBand] += nAdd;
	ASSERT( abs(m_freqLevel[m_curBand]) <=BAND_COUNT );
	SetCurFreq();
	invalidateRect();
	return GetLevel();
}

int GxxParamPad::GetFreq( bool &bmax,bool &bmin )
{
	bmax = bmin = false;
	if (m_curBand < BAND_COUNT-1  )
	{
		if ( m_bandFreq[m_curBand] == m_bandFreq[m_curBand+1]-1)
		{
			bmax = true;
		}
		else if ( m_bandFreq[m_curBand]==FREQ_STEP*(m_curBand+2))
		{
			bmax = true;
		}
	}
	else if (m_bandFreq[m_curBand] == FREQ_COUNT-1 )
	{
		bmax = true;
	}

	if (m_curBand >0)
	{
		if (m_bandFreq[m_curBand] == m_bandFreq[m_curBand-1]+1)
		{
			bmin = true;
		}
		else if ( m_bandFreq[m_curBand]==FREQ_STEP*(m_curBand))
		{
			bmin = true;
		}
	}
	else if (m_bandFreq[m_curBand] == 0)
	{
		bmin = true;
	}
	ASSERT (m_bandFreq[m_curBand]>=0 && m_bandFreq[m_curBand]< FREQ_COUNT );
	return C_FreqRate[m_bandFreq[m_curBand]];
}

int GxxParamPad::MoveFreq( int nAdd,bool &bmax,bool &bmin )
{
	m_bandFreq[m_curBand] += nAdd;
	ASSERT ( m_bandFreq[m_curBand]<=FREQ_STEP*(m_curBand+2) && m_bandFreq[m_curBand] >= FREQ_STEP*m_curBand);
	if (m_curBand>0)
	{
		ASSERT(m_bandFreq[m_curBand] > m_bandFreq[m_curBand-1]);
	}
	if (m_curBand<BAND_COUNT-1 )
	{
		ASSERT(m_bandFreq[m_curBand] < m_bandFreq[m_curBand+1]);
	}
	SetCurFreq();
	invalidateRect();
	return GetFreq(bmax,bmin);
}


int GxxParamPad::GetQValue()
{
	return m_qValue[m_curBand];
}


int GxxParamPad::MoveQValue( int nAdd )
{
	m_qValue[m_curBand] += nAdd;
	ASSERT(m_qValue[m_curBand]>=MIN_Q && m_qValue[m_curBand]<=MAX_Q );
	SetCurFreq();
	invalidateRect();
	return GetQValue();
}


void GxxParamPad::NextBand()
{
	m_curBand++;
	if (m_curBand==BAND_COUNT)
	{
		m_curBand = 0;
	}
	invalidateRect();
}


BOOL GxxParamPad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case WM_LBUTTONDOWN:
		if (InMyArea(m_drawRect, LOWORD( lParam ), HIWORD( lParam )) )
		{
			int n = (LOWORD( lParam ) - m_drawRect.left)/(m_nSetpWidth*FREQ_STEP);
			ASSERT(n>=0);
			if (n>=BAND_COUNT)
			{
				n = BAND_COUNT-1;
			}
			if (n!=m_curBand)
			{
				m_curBand = n;
				invalidateRect();
				getParentView()->TranslateMessage(MES_INVALIDATE,0,0);
			}
			return TRUE;
		}
	default:
		return FALSE;
	}
	return FALSE;
}


void GxxParamPad::Draw()
{
	m_pPicBack->DrawPicWithRect(m_ActRect);

	RECT rc_color = m_drawRect;
	rc_color.left += m_nSetpWidth*FREQ_STEP*m_curBand-m_nSetpWidth/2;
	rc_color.right = rc_color.left +  m_nSetpWidth*(FREQ_STEP*2+1);
	SkiaBitmapManager::GetInstance()->DrawColor(0xFFFF8C00,&rc_color,180);
	//m_pCurLine->DrawPicWithRect(m_drawRect);
	int j =0;

	RECT rcline;
	RECT rcdot;
	rcline.top = m_drawRect.top;
	rcline.bottom = m_drawRect.bottom;
	int y_mid = (rcline.top + rcline.bottom)/2;
	for (int i = 0; i <FREQ_COUNT; i++ )
	{
		rcline.left = m_drawRect.left + i*m_nSetpWidth;
		rcline.right = rcline.left+m_nLineWidth;

		int x_mid = (rcline.left +rcline.right)/2;
		rcdot.left = x_mid - m_nDotLen/2;
		rcdot.right = rcdot.left  + m_nDotLen;
		

		if (j<BAND_COUNT && i == m_bandFreq[j])
		{
			rcline.left -= 2;
			rcline.right += 2;//调整
			rcdot.top = y_mid -m_freqLevel[j]*m_nSetpHeight- m_nDotLen/2;
			rcdot.bottom = rcdot.top + m_nDotLen;

			if (m_curBand == j)//当前的
			{
				m_pCurLine->DrawPicWithRect(rcline);
				m_pCurDot->DrawPicWithRect(rcdot);
			}
			else
			{
				m_pFullLine->DrawPicWithRect(rcline);
				m_pLineDot->DrawPicWithRect(rcdot);
			}
			j++;
		}
		else
		{
			int next_freq = -1;
			int pre_freq = -1;
			if (j>0)
			{
				pre_freq = m_bandFreq[j-1];
			}
			if (j<BAND_COUNT)
			{
				next_freq = m_bandFreq[j];
			}


			int nor_level_1 = 0;
			int nor_level_2 = 0;
			int n_level = 0;
			if (pre_freq != -1 &&  i-pre_freq<=2)
			{
				if (m_freqLevel[j-1]>0)
				{
					nor_level_1 = m_freqLevel[j-1] - (i-pre_freq)*m_qValue[j-1];
					if (nor_level_1<0)
					{
						nor_level_1 = 0;
					}
				}
				else if(m_freqLevel[j-1] < 0)
				{
					nor_level_1 = m_freqLevel[j-1] + (i-pre_freq)*m_qValue[j-1];
					if (nor_level_1>0)
					{
						nor_level_1 = 0;
					}
				}
			}
			if (next_freq!=-1 && next_freq-i<=2)
			{
				if (m_freqLevel[j]>0)
				{
					nor_level_2 = m_freqLevel[j] - (next_freq-i)*m_qValue[j];
					if (nor_level_2<0)
					{
						nor_level_2 = 0;
					}
				}
				else if(m_freqLevel[j] < 0)
				{
					nor_level_2 = m_freqLevel[j] + (next_freq-i)*m_qValue[j];
					if (nor_level_2>0)
					{
						nor_level_2 = 0;
					}
				}
			}
			if( (nor_level_1>0 && nor_level_2>0) || ( nor_level_1<0 && nor_level_2<0 ) )
			{
				n_level = (nor_level_1 + nor_level_2)/2;
			}
			else 
			{
				n_level = nor_level_1 + nor_level_2;
			}

			rcdot.top = y_mid -n_level*m_nSetpHeight- m_nDotLen/2;
			rcdot.bottom = rcdot.top + m_nDotLen;

			m_pDotLine->DrawPicWithRect(rcline);
			m_pNorDot->DrawPicWithRect(rcdot);
		}
	}

}

#define  DOTTED_LINE            "dotted_line"
#define  FULL_LINE				"full_line"
#define  CUR_LINE				"cur_line"

#define  NOR_DOT				"nor_dot"
#define  LINE_DOT				"line_dot"
#define  CUR_DOT				"cur_dot"
void GxxParamPad::setCtrLayout( TiXmlElement * ele )
{
	setCtrName(ele);
	setCtrRectUseCenter(ele);
	::SetRect(&m_drawRect,m_ActRect.left+49,m_ActRect.top+37,m_ActRect.right-25,m_ActRect.bottom-30);

	m_drawRect.left += 15;
	m_drawRect.right += 15;
	m_drawRect.top -= 2;
	m_drawRect.bottom -= 2;
	m_nSetpWidth = (m_drawRect.right - m_drawRect.left)/FREQ_COUNT;
	m_nSetpHeight = (m_drawRect.bottom - m_drawRect.top)/(BAND_COUNT*2);

	const char* pa = ele->Attribute(BACK_BMP);
	if (m_pPicBack->setPicHandle(pa))
	{
		m_pPicBack->setCtrRect(m_ActRect);
		m_pPicBack->bindHandleRect();
	}

	pa = ele->Attribute(DOTTED_LINE);
	m_pDotLine->setPicHandle(pa);

	pa = ele->Attribute(FULL_LINE);
	m_pFullLine->setPicHandle(pa);

	pa = ele->Attribute(CUR_LINE);
	m_pCurLine->setPicHandle(pa);

	m_nLineWidth = m_pCurLine->getPicWidth();
	//m_nLineHeight = m_pCurLine->getPicHeight();

	pa = ele->Attribute(NOR_DOT);
	m_pNorDot->setPicHandle(pa);

	pa = ele->Attribute(LINE_DOT);
	m_pLineDot->setPicHandle(pa);

	pa = ele->Attribute(CUR_DOT);
	m_pCurDot->setPicHandle(pa);

	m_nDotLen = m_pCurDot->getPicWidth();


	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);

}












