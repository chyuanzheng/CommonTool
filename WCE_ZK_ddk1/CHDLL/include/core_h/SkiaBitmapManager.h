#pragma once


#include "DllDefine.h"




#include "ScaleAnimation.h"
#include "AlphaAnimation.h"
#include "TranslateAnimation.h"
#include "RotateYAnimation.h"
class SkiaInfo;
class SkBitmap;
class SkCanvas;
class SkTypeface;
//class ScaleAnimation;



typedef void *H_SKFONT ; 
class Activity;
class CE_CONTROL_API SkiaBitmapManager
{
public:
	typedef enum{SK_UTF8,SK_UTF16,SK_GlyphID} T_CODING;
	typedef enum{SongTi,LucidaSans,msyh} T_TYPEFACE;
	typedef map <T_TYPEFACE , SkTypeface *> T_SK_TYPE;
	 

	static SkiaBitmapManager* GetInstance();
	virtual ~SkiaBitmapManager(); 
	HANDLE InitImage(const CHAR* file,const RECT* rect = NULL,bool isPng = true);
	HANDLE InitImage(const WCHAR* file,const RECT* rect = NULL,bool isPng = true);
	HANDLE InitImage(const RECT* rect);
	HANDLE InitImage();
	HANDLE InitImage(HDC hdc,const RECT* rect,HBITMAP *pHbmp);

	const char *GetImagePath(HANDLE ResID);
	//HANDLE InitImageForText(const RECT* rect);
	void   DeInitImage(HANDLE ResID);
	H_SKFONT  InitFont(UINT color,int  size, T_CODING code=SK_UTF8, T_TYPEFACE tf = msyh,UINT a =255);
	void SetIconConfig(HANDLE ResID, void *p, int w, int h );//ipod 的图片
	void   DeInitFont(H_SKFONT hfont);
	

	void SetRect(HANDLE ResID, const RECT* rect);
	void SetAlpha(HANDLE ResID, UINT a);
	int GetWidth(HANDLE ResID);
	int GetHeight(HANDLE ResID);
	

	BOOL DrawImage(HANDLE ResID);
	//定义了rect，a,，不会有动画的处理。
	BOOL DrawImage(HANDLE ResID,const RECT* rect, UINT a = 255);
	BOOL DrawImage(HANDLE ResID,const RECT* SrcRc, const RECT* DstRc,UINT a = 255);
	BOOL DrawImage(HANDLE ResID,const RECT& SrcRc, int angle);

	BOOL DrawColor(UINT color,const RECT* rect, UINT a = 255);
	BOOL DrawColor(UINT color,HANDLE ResID);

	void DrawLine(int x0,int y0,int x1,int y1,UINT color =0xffff0000,int width = 3);

	UINT GetTextLen( const wstring &m_wstr,H_SKFONT hfont );
	void DrawTextInRect( const string& strtext, const RECT& rect,UINT format=DT_CENTER, H_SKFONT hfont=NULL );
	void DrawTextInRect( const wstring& strtext, const RECT& rect, UINT format=DT_CENTER, H_SKFONT hfont=NULL  );
	void DoDrawText( H_SKFONT hfont, const RECT &rect, const void *ptext,int size, UINT format );
	void DrawToDevice(HDC hdc,const RECT &rect);

	void InvalidRect( const RECT * rt );
	void Validate();
	
	void SaveStatus();
	void ReleasStatus();
	void SetClipRect(const RECT &rect);

	void DoAction( HANDLE  h, Animation *pAni );
	void PreAction( HANDLE  h );
	void NotInAction( HANDLE  h );

	void setActivityScreen( GxxView* view, HANDLE hscreen );

	void SetInvertX( int m_Invert_y );
	void SetTextGradient( H_SKFONT hfont, int nfrom_color, int nto_color, int ny0, int ny1 );

private:
	SkiaBitmapManager();
	static SkiaBitmapManager *m_pInstance;
	BOOL GetImageFromFile( const CHAR* file,SkiaInfo* imageinfo );
	void *getBitmapPixels();
	void AddFontResFS(T_TYPEFACE tf,string path);
	void AddSysFontResFS(T_TYPEFACE tf,string path);

	BOOL AlphaAction( HANDLE h, AlphaAnimation * alphaAni );
	BOOL ScaleAction( HANDLE h, ScaleAnimation * alphaAni );
	BOOL TranslateAction( HANDLE h, TranslateAnimation * alphaAni );
	BOOL RotateYAction( HANDLE h, RotateYAnimation * alphaAni );
	







	//根据destrect 和 m_invRect相交，找到srcrect中的等比例矩形
	//BOOL getRightRect( RECT &srcrect, RECT &destrect );
	//inline BOOL getCoordinate( LONG & xget, LONG & yget, LONG xA, LONG yA, LONG xB, LONG yB );
	SkBitmap    * m_wndBtp;
	SkCanvas	*m_wndCanvas;
	BITMAPINFO *m_bitmapInfo;
	RECT m_invRect;//这个是需要刷新的区域
	BOOL m_b_invalidate;
	T_SK_TYPE m_tSktype;
	H_SKFONT  m_dfFont;
	H_SKFONT  m_df16Font;
	RECT    m_clipRect;

};

