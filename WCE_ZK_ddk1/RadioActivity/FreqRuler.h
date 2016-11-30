#include "GXControls/GXCreateControls.h"
#include "GXControls/CXWinFun.h"
#include "GXControls/GXNotify.h"

class FreqRuler : public CXWinFun
{
	GXLabel	*pLabRuler;
	GXLabel	*pLabFMArrow;
	GXLabel *pLabAMArrow;
	POINT ptNow;
	POINT ptEnd;
	int	speed;
	int acc;
	POINT ptClick;
	BOOL	bClick;
	int		freqLow;
	int		freqHigh;
	int		freqLowest;
	int		freqHighest;
	int		freqStep;
public:
	FreqRuler()
	{
		bClick = 0;
	}
	void SetControlFun(GXBaseControl *pControl, const char *funtype, const char *funval)
	{
		if(0 == cmpAstr(funtype, "label"))
		{
			if (0 == cmpAstr(funval, "ruler"))
			{
				pLabRuler = (GXLabel *)pControl;
			}
			if (0 == cmpAstr(funval, "fmarrow"))
			{
				pLabFMArrow = (GXLabel *)pControl;
			}
			if (0 == cmpAstr(funval, "amarrow"))
			{
				pLabAMArrow = (GXLabel *)pControl;
			}
		}
	}
	LRESULT DoLButtonDown(GXBaseControl *pControl, POINT pt)
	{
		bClick = 1;
		ptClick = pt;
		return 1;
	}
	LRESULT DoLButtonUp(GXBaseControl *pControl, POINT pt)
	{
		if (bClick)
		{
			int freq = GetFreq();
			if (freq > freqHigh)
			{
				RulerMoveTo(freqHigh);
			}
			else
			if (freq < freqLow)
			{
				RulerMoveTo(freqLow);
			}
			else
			if (freq % freqStep)
			{
				freq = freq - freq%freqStep;
				RulerMoveTo(freq);
			}
			GXNotify::SendNotify("rulerleave", freq, 0);
			bClick = 0;
		}
		return 0;
	}
	LRESULT DoMouseMove(GXBaseControl *pControl, POINT pt)
	{
		if (!bClick)
		{
			return 0;
		}
		int dis = pt.x - ptClick.x;
		ptClick = pt;
		pLabRuler->MoveTo(pLabRuler->rcWnd.left+dis, pLabRuler->rcWnd.top, 1);
		int freq = GetFreq();
		if (freq > freqHigh)
		{
			freq = freqHigh;
		}
		else if (freq < freqLow)
		{
			freq = freqLow;
		}
		else if (freq % freqStep)
		{
			freq = freq - freq%freqStep;
		}
		GXNotify::SendNotify("rulermove", freq, 0);
		return 0;
	}
	LRESULT DoTimer(GXBaseControl *pControl, UINT nID)
	{
		if (nID == 0)
		{
			int speedX=0;
			int speedY=0;
			POINT ptStart ={pLabRuler->rcWnd.left, pLabRuler->rcWnd.top};
			if (ptStart.x == ptEnd.x)
			{
				speedX = 0;
				speedY = speed;
			}
			else if (ptStart.y == ptEnd.y)
			{
				speedY = 0;
				speedX = speed;
			}
			else
			{
				float degree;
				degree = atan((ptEnd.y-ptStart.y)/((float)ptEnd.x-ptStart.x));
				speedX = speed * (cos(degree));
				speedY = speed * (sin(degree));

			}
			if (ptStart.x >= ptEnd.x)
			{
				speedX = -abs(speedX);
			}
			else
			{
				speedX = abs(speedX);
			}
			if (ptStart.y >= ptEnd.y)
			{
				speedY = -abs(speedY);
			}
			else
			{
				speedY = abs(speedY);
			}
			ptNow.x += speedX;
			ptNow.y += speedY;
			if (speedX > 0)
			{
				if (ptNow.x >= ptEnd.x)
				{
					ptNow = ptEnd;
					pWindow->KillTimer(0);
				}
			}
			else if (speedX < 0)
			{
				if (ptNow.x <= ptEnd.x)
				{
					ptNow = ptEnd;
					pWindow->KillTimer(0);
				}
			}
			if (speedY > 0)
			{
				if (ptNow.y >= ptEnd.y)
				{
					ptNow = ptEnd;
					pWindow->KillTimer(0);
				}
			}
			else if (speedY < 0)
			{
				if (ptNow.y <= ptEnd.y)
				{
					ptNow = ptEnd;
					pWindow->KillTimer(0);
				}
			}
			pLabRuler->MoveTo(ptNow.x, ptNow.y, 1);
		}
		return 0;
	}
	void RulerMoveTo(int freq)
	{
		ptEnd.y = pLabRuler->rcWnd.top;
		ptEnd.x = -pLabRuler->rcWnd.Width() * (freq - freqLowest)/(freqHighest-freqLowest)+pWindow->rcWnd.Width()/2;
		ptNow.x = pLabRuler->rcWnd.left;
		ptNow.y = pLabRuler->rcWnd.top;
		pWindow->SetTimer(0, 30, NULL);
		speed = 50;
		acc = 5;
	}
	int GetFreq()
	{
		int dis = pWindow->rcWnd.Width()/2 - pLabRuler->rcWnd.left;
		return (freqHighest-freqLowest)*dis/pLabRuler->rcWnd.Width() + freqLowest;
	}
	void SetBand(int freqlow, int freqhigh, int freqstep, int fmam)
	{
		freqLow = freqlow;
		freqHigh = freqhigh;
		freqStep = freqstep;
		if (!fmam)
		{
			freqLowest = 65000;
			freqHighest = 108000;
			pLabFMArrow->ShowWindow(1, 1);
			pLabAMArrow->ShowWindow(0, 1);
		}
		else
		{
			freqLowest = 522;
			freqHighest = 1710;
			pLabAMArrow->ShowWindow(1, 1);
			pLabFMArrow->ShowWindow(0, 1);
		}
	}
};