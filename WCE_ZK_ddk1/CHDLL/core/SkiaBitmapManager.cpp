#include "StdAfx.h"
#include "SkiaBitmapManager.h"
#include "StrHelp.h"




#ifdef _DEBUG
#define SK_DEBUG
//"GR_DEBUG=1"
#else
#define SK_RELEASE
#endif

#define SK_IGNORE_STDINT_DOT_H
#define  SK_SCALAR_IS_FIXED
#define  SK_CAN_USE_FLOAT
#define  SKIA_DLL
#include "../skia_ce/include/core/SkCanvas.h"
#include "../skia_ce/include/core/SkRect.h"
#include "../skia_ce/include/core/SkStream.h"
#include "../skia_ce/include/images/SkImageDecoder.h"
#include "../skia_ce/include/core/SkFontHost.h"
#include "../skia_ce/include/utils/SkCamera.h"
#include "../skia_ce/include/effects/skgradientshader.h"
#include <vector>

const string BACKPNG =  ".png";
typedef list<SkiaInfo*>    TLIST_INFO;
typedef map<string *,TLIST_INFO *> T_MAP_SH;
class  SkiaInfo
{
	//DWORD pixelformat;      // the pixelformat of the image
	//HBITMAP hBitMap;        // the Handle of the PARGB image 
public:
	SkBitmap *pCtrlBtp;
	SkPaint  ctrPnt;
	SkRect   ctrRect;//需要绘制的rect 作为动画的参考矩形
	SkMatrix ctrMatrix;
	string  *p_strpath;

	SkiaInfo(const CHAR *file){
		p_strpath = new string;
		*p_strpath = file;

		pCtrlBtp = new SkBitmap;
		

		ctrPnt.setAlpha(255);
		ctrPnt.setAntiAlias(true);

		TLIST_INFO *lt_info = new TLIST_INFO;
		lt_info->push_back(this);

		s_map_sh.insert(std::make_pair(p_strpath,lt_info));
		ASSERT(s_map_sh.size()<600);//小于60张图
	}

	SkiaInfo(bool bBitmap){
		if (bBitmap)
		{
			pCtrlBtp = new SkBitmap;
		}
		else
		{
			pCtrlBtp = NULL;
		}
		p_strpath = NULL;
		ctrPnt.setAlpha(255);
		ctrPnt.setAntiAlias(true);
	}
	~SkiaInfo(){
		if ( NULL == p_strpath )
		{
			if (pCtrlBtp!=NULL)
			{
				delete pCtrlBtp;
			}
			return;
		}

		T_MAP_SH::iterator pos = s_map_sh.find( p_strpath);
		ASSERT(pos != s_map_sh.end());
		TLIST_INFO *lt_info = pos->second;
		lt_info->remove(this);

		if (lt_info->empty())
		{
			ASSERT(NULL!=pCtrlBtp);
			delete  p_strpath;
			delete  lt_info;
			delete pCtrlBtp;
			s_map_sh.erase(pos);
		}

	}

	static SkiaInfo *GetSkiaFromMap(const CHAR *file){
		T_MAP_SH::iterator pos ;
		for ( pos = s_map_sh.begin(); pos != s_map_sh.end(); ++pos )
		{
			if ( *(pos->first) == file)
			{
				break;
			}
		}
		if (pos != s_map_sh.end())
		{
			SkiaInfo *info = new SkiaInfo( *(pos->second->front()));//直接复制拷贝而不需要解码
			pos->second->push_back(info);
			return info;
		}
		return NULL;
	}


	
private:
	SkiaInfo(SkiaInfo & info){
		pCtrlBtp = info.pCtrlBtp;
		p_strpath = info.p_strpath;
	} 
	SkiaInfo &  operator =(const SkiaInfo&   info); 
	static T_MAP_SH s_map_sh;
	
	
};
T_MAP_SH SkiaInfo::s_map_sh = T_MAP_SH();



SkiaBitmapManager *SkiaBitmapManager::m_pInstance = NULL;
SkiaBitmapManager* SkiaBitmapManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SkiaBitmapManager;
	}
	return m_pInstance;
}

SkiaBitmapManager::SkiaBitmapManager()
{
	m_b_invalidate= FALSE;
	if (AfxGetDeviceBitcount()==16)
	{
		m_wndBtp = new SkBitmap();
		m_wndBtp->setConfig(SkBitmap::kRGB_565_Config, 800, 480);
		m_wndBtp->allocPixels();
		m_wndCanvas = new SkCanvas();
		m_wndCanvas->setBitmapDevice(*m_wndBtp);

		m_bitmapInfo  = (BITMAPINFO*)malloc( sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(2) );
		memset( m_bitmapInfo, 0, sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(2) );
		m_bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_bitmapInfo->bmiHeader.biWidth = 800;
		m_bitmapInfo->bmiHeader.biHeight = -480;
		m_bitmapInfo->bmiHeader.biPlanes = 1;
		m_bitmapInfo->bmiHeader.biBitCount = 16;
		m_bitmapInfo->bmiHeader.biCompression = BI_BITFIELDS;
		m_bitmapInfo->bmiHeader.biSizeImage = 0;

		m_bitmapInfo->bmiColors[0].rgbBlue = 0;  
		m_bitmapInfo->bmiColors[0].rgbGreen = 0xF8;  
		m_bitmapInfo->bmiColors[0].rgbRed = 0;  
		m_bitmapInfo->bmiColors[0].rgbReserved = 0;  
		m_bitmapInfo->bmiColors[1].rgbBlue = 0xE0;  
		m_bitmapInfo->bmiColors[1].rgbGreen = 0x07;  
		m_bitmapInfo->bmiColors[1].rgbRed = 0;  
		m_bitmapInfo->bmiColors[1].rgbReserved = 0;  
		m_bitmapInfo->bmiColors[2].rgbBlue = 0x1F;  
		m_bitmapInfo->bmiColors[2].rgbGreen = 0;  
		m_bitmapInfo->bmiColors[2].rgbRed = 0;  
		m_bitmapInfo->bmiColors[2].rgbReserved = 0;  

	}
	else if (AfxGetDeviceBitcount()==32)
	{
		m_wndBtp = new SkBitmap();
		m_wndBtp->setConfig(SkBitmap::kARGB_8888_Config, 800, 480);
		m_wndBtp->allocPixels();

		m_wndCanvas = new SkCanvas();
		m_wndCanvas->setBitmapDevice(*m_wndBtp);

		m_bitmapInfo  = (BITMAPINFO*)malloc( sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(255) );
		memset( m_bitmapInfo, 0, sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(255) );
		m_bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_bitmapInfo->bmiHeader.biWidth = 800;
		m_bitmapInfo->bmiHeader.biHeight = -480;
		m_bitmapInfo->bmiHeader.biPlanes = 1;
		m_bitmapInfo->bmiHeader.biBitCount = 32;
		m_bitmapInfo->bmiHeader.biCompression = BI_RGB;
		m_bitmapInfo->bmiHeader.biSizeImage = 0;
	}


	//AddFontResFS(SongTi,string("font\\SongTi.ttc"));
	//AddFontResFS(LucidaSans,string("font\\LucidaSans.ttf"));
	AddFontResFS(msyh,string("\\font\\msyh.ttf"));
	m_dfFont = InitFont(0xffffffff,40);
	m_df16Font = InitFont(0xffffffff,40,SK_UTF16);
}

SkiaBitmapManager::~SkiaBitmapManager()
{

	free(m_bitmapInfo);
	delete m_wndBtp;
	delete m_wndCanvas;
	DeInitFont(m_dfFont); 

}

H_SKFONT SkiaBitmapManager::InitFont( UINT color,int size, T_CODING code/*=SK_UTF8*/, T_TYPEFACE tf /*= msyh*/,UINT a /*=255*/ )
{
	SkPaint *fntPaint = new SkPaint;
	fntPaint->setColor(color);
	fntPaint->setTextSize(SkIntToScalar(size));
	switch (code)
	{
	case SK_UTF8:
		fntPaint->setTextEncoding(SkPaint::kUTF8_TextEncoding);
		break;
	case SK_UTF16:
		fntPaint->setTextEncoding(SkPaint::kUTF16_TextEncoding);
		break;
	case SK_GlyphID:
		fntPaint->setTextEncoding(SkPaint::kGlyphID_TextEncoding);
		break;
	default:
		ASSERT(0);
		break;
	}
	fntPaint->setTypeface(m_tSktype[tf]);
	
	fntPaint->setAntiAlias(true);
	fntPaint->setLCDRenderText(true);
	fntPaint->setAlpha(a);

	return  (H_SKFONT)fntPaint;
	
}



void SkiaBitmapManager::DeInitFont( H_SKFONT hfont )
{
	ASSERT(NULL!=hfont);
	delete (SkPaint *)hfont;
}



void SkiaBitmapManager::DeInitImage( HANDLE ResID )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;
	delete (info);

}


const char * SkiaBitmapManager::GetImagePath(HANDLE ResID)
{
	SkiaInfo* info = (SkiaInfo*)ResID;
	if (info->p_strpath)
	{
		return info->p_strpath->c_str();
	}
	return NULL;
}


HANDLE SkiaBitmapManager::InitImage( const CHAR* file,const RECT* rect /*= NULL*/,bool isPng /*= true*/ )
{
	//首先从Map中看是否有已经村子的imageinfo
	if (NULL == file)
	{
		return NULL;
	}

	string sfile = file;//StrHelp
	if (isPng)//默认是Png图片
	{
		sfile += BACKPNG ;
	}

	SkiaInfo* imageinfo = SkiaInfo::GetSkiaFromMap(sfile.c_str());

	if (NULL==imageinfo)
	{
		imageinfo = new SkiaInfo(sfile.c_str());


		
		SkFILEStream stream(sfile.c_str());

		SkImageDecoder* codec = SkImageDecoder::Factory(&stream);
		bool bret = false;
		if(NULL != codec){
			if (AfxGetDeviceBitcount()==16)
			{
				bret = codec->decode(&stream, imageinfo->pCtrlBtp, SkBitmap::kRGB_565_Config,
					SkImageDecoder::kDecodePixels_Mode);
			}
			if (AfxGetDeviceBitcount()==32)
			{
				bret = codec->decode(&stream, imageinfo->pCtrlBtp, SkBitmap::kARGB_8888_Config,
					SkImageDecoder::kDecodePixels_Mode);
			}
			delete codec;
		}
		if (false ==bret )
		{
			delete imageinfo;
			return NULL;
		}
		//ASSERT(NULL!=codec);

		//ASSERT(bret);
	}

	SetRect(imageinfo,rect);
	return (HANDLE)imageinfo;
}

HANDLE SkiaBitmapManager::InitImage(const RECT* rect)
{
	ASSERT(NULL != rect);
	SkiaInfo* imageinfo =  new SkiaInfo(true);
	if (AfxGetDeviceBitcount() == 16)
	{
		imageinfo->pCtrlBtp->setConfig(SkBitmap::kRGB_565_Config, rect->right - rect->left, rect->bottom - rect->top);
	}
	if (AfxGetDeviceBitcount() == 32)
	{
		imageinfo->pCtrlBtp->setConfig(SkBitmap::kARGB_8888_Config, rect->right - rect->left, rect->bottom - rect->top);
	}
	
	imageinfo->pCtrlBtp->allocPixels();
	SetRect(imageinfo,rect);
	return (HANDLE)imageinfo;
}

HANDLE SkiaBitmapManager::InitImage()//用于Ipod的图片
{
	SkiaInfo* imageinfo =  new SkiaInfo(true);
	return (HANDLE)imageinfo;
}


void SkiaBitmapManager::SetIconConfig(HANDLE ResID, void *p, int w, int h )
{
	SkiaInfo* info = (SkiaInfo*)ResID;
	if (info==NULL)
	{
		return;
	}
	info->pCtrlBtp->setConfig(SkBitmap::kRGB_565_Config,w,h);
	info->pCtrlBtp->setPixels(p);
}


HANDLE SkiaBitmapManager::InitImage( const WCHAR* file,const RECT* rect /*= NULL*/,bool isPng /*= true*/ )
{
	ASSERT(NULL!=file);
	string sfile = StrHelp::WStringToString(wstring(file));
	return InitImage(sfile.c_str(),rect,isPng);
}

HANDLE SkiaBitmapManager::InitImage( HDC hdc,const RECT* rect,HBITMAP *pHbmp  )
{
	BITMAPINFO* lpbmi;
	BITMAPINFO *bitmapInfo;
	if (AfxGetDeviceBitcount() == 16)
	{
		bitmapInfo  = (BITMAPINFO*)malloc( sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(2) );
		memset( bitmapInfo, 0, sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(2) );
		bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo->bmiHeader.biWidth = rect->right - rect->left;
		bitmapInfo->bmiHeader.biHeight = -(rect->bottom - rect->top);
		bitmapInfo->bmiHeader.biPlanes = 1;
		bitmapInfo->bmiHeader.biBitCount = 16;
		bitmapInfo->bmiHeader.biCompression = BI_BITFIELDS;
		bitmapInfo->bmiHeader.biSizeImage = 0;

		bitmapInfo->bmiColors[0].rgbBlue = 0;  
		bitmapInfo->bmiColors[0].rgbGreen = 0xF8;  
		bitmapInfo->bmiColors[0].rgbRed = 0;  
		bitmapInfo->bmiColors[0].rgbReserved = 0;  
		bitmapInfo->bmiColors[1].rgbBlue = 0xE0;  
		bitmapInfo->bmiColors[1].rgbGreen = 0x07;  
		bitmapInfo->bmiColors[1].rgbRed = 0;  
		bitmapInfo->bmiColors[1].rgbReserved = 0;  
		bitmapInfo->bmiColors[2].rgbBlue = 0x1F;  
		bitmapInfo->bmiColors[2].rgbGreen = 0;  
		bitmapInfo->bmiColors[2].rgbRed = 0;  
		bitmapInfo->bmiColors[2].rgbReserved = 0;  
	}
	else
	{
		ASSERT(FALSE);
	}
	lpbmi = bitmapInfo;

	SkiaInfo* imageinfo =  new SkiaInfo(true);



	imageinfo->pCtrlBtp->setConfig(SkBitmap::kRGB_565_Config, rect->right - rect->left, rect->bottom - rect->top );


	void *pixel = NULL;
	*pHbmp = CreateDIBSection(hdc, (BITMAPINFO *)lpbmi, 0, (void**)&pixel, NULL, 0);
	::SelectObject(hdc, *pHbmp);
	imageinfo->pCtrlBtp->setPixels(pixel);

	SetRect(imageinfo,rect);
	return (HANDLE)imageinfo;
}






void SkiaBitmapManager::DrawLine( int x0,int y0,int x1,int y1,UINT color /*=0xffff0000*/,int width /*= 3*/ )
{
	SkPaint paint;
	paint.setColor(color);
	paint.setStrokeWidth( SkIntToScalar(width));
	m_wndCanvas->drawLine( SkIntToScalar(x0), SkIntToScalar(y0),SkIntToScalar(x1),SkIntToScalar(y1),paint);
}

void SkiaBitmapManager::AddFontResFS(T_TYPEFACE tf,string path)
{
	string workpath;
	AfxGetWorkPathA(workpath);
	workpath = workpath + path;
	SkTypeface *psktf = SkFontHost::CreateTypefaceFromFile(workpath.c_str());
	ASSERT(NULL!=psktf);
	m_tSktype.insert(std::make_pair(tf,psktf) );
	//SkFontHost.
}
void SkiaBitmapManager::AddSysFontResFS(T_TYPEFACE tf,string path)
{	string workpath;
	AfxGetWorkPathA(workpath);
	workpath = workpath + path;
	SkTypeface *psktf = SkFontHost::CreateTypefaceFromFile((workpath).c_str());
	ASSERT(NULL!=psktf);
	m_tSktype.insert(std::make_pair(tf,psktf) );
}
void SkiaBitmapManager::DrawTextInRect( const wstring& strtext, const RECT& rect, UINT format/*=DT_CENTER*/, H_SKFONT hfont/*=NULL */  )
{
	if (NULL==hfont)
	{
		hfont = m_df16Font;
	}
	DoDrawText(hfont, rect, strtext.c_str(), strtext.size()*2,format);
}


void SkiaBitmapManager::DrawTextInRect( const string& strtext, const RECT& rect, UINT format/*=DT_CENTER*/, H_SKFONT hfont/*=NULL */  )
{
	if (NULL==hfont)
	{
		hfont = m_dfFont;
	}
	DoDrawText(hfont, rect, strtext.c_str(), strtext.size(),format);

}

void SkiaBitmapManager::DoDrawText( H_SKFONT hfont, const RECT &rect, const void *ptext,int size, UINT format )
{
	SkPaint *pfntPaint = (SkPaint *)hfont;


	SkScalar xText = SkIntToScalar(rect.left);
	SkRect      bounds;
	SkScalar wText = pfntPaint->measureText(ptext, size, &bounds);
	SkScalar hText = -bounds.fTop;
	SkScalar yText = SkIntToScalar(rect.top) + hText;
	if (format & DT_LEFT)
	{
		xText = SkIntToScalar(rect.left);
	}
	if (format & DT_CENTER)
	{
		xText = SkIntToScalar(rect.left) + (SkIntToScalar(rect.right-rect.left)-wText)/2;
	}
	if (format & DT_RIGHT)
	{
		xText = SkIntToScalar(rect.right) - wText;
	}
	if (format & DT_TOP)
	{
		yText = SkIntToScalar(rect.top) + hText;
	}
	if (format & DT_BOTTOM)
	{
		yText = SkIntToScalar(rect.bottom) - bounds.fBottom;
	}
	if (format & DT_VCENTER)
	{
		yText += (SkIntToScalar(rect.bottom-rect.top)-bounds.height())/2;
	}
	// 这个函数会越来越慢
	//m_wndCanvas->drawText(ptext, size, xText, yText, *pfntPaint);


	SkRect skrt;

	skrt.set(SkIntToScalar(230),SkIntToScalar(230),SkIntToScalar(rect.right),SkIntToScalar(rect.bottom));
	SkPaint paint;
	// paint.setStyle(SkPaint::kStroke_Style);
	paint.setStyle(SkPaint::kStroke_Style);
	paint.setColor(SK_ColorGREEN);;
	m_wndCanvas->drawRect(skrt, paint);

	m_wndCanvas->drawCircle(SkIntToScalar(180),SkIntToScalar(90),SkIntToScalar(25),paint);

	SkPath path;
	path.cubicTo(SkIntToScalar(768), SkIntToScalar(0), SkIntToScalar(-512),SkIntToScalar(256), SkIntToScalar(256), SkIntToScalar(256));
	paint.setColor(SK_ColorGREEN);
	m_wndCanvas->drawPath(path, paint);

	std::vector<std::vector<SkPath>>ps;
	SkPoint point[200]; 
	bool b = m_wndCanvas->getPaths(ptext, size, xText, yText, *pfntPaint, ps);
	if (b)
	{
		for (std::vector<std::vector<SkPath>>::iterator it = ps.begin(); it!= ps.end();it++)
		{
			for( std::vector<SkPath>::iterator iu = it->begin();iu!=it->end();iu++)
			{

				int n = iu->getPoints(point,200);
				int dnX = SkScalarToFloat(point->fX);
				int dnY = SkScalarToFloat(point->fY);
				int dnx = dnX + 0;
				m_wndCanvas->drawPath(*iu,paint);
			}
			
		}
	}

}
UINT SkiaBitmapManager::GetTextLen( const wstring &m_wstr,H_SKFONT hfont )
{
	SkPaint *pfntPaint = (SkPaint *)hfont;
	SkScalar wText = pfntPaint->measureText(m_wstr.c_str(), m_wstr.size()*2);
	return (UINT)SkScalarToFloat(wText);

}
//动画 必须用这个函数来绘图
BOOL SkiaBitmapManager::DrawImage( HANDLE ResID)
{

	ASSERT(NULL!=ResID);
	
	SkiaInfo* info = (SkiaInfo*)ResID;

	m_wndCanvas->drawBitmapMatrix(*(info->pCtrlBtp),info->ctrMatrix,&info->ctrPnt);//skrt.fLeft,skrt.fTop);
	//m_wndCanvas->drawRect()
	return TRUE;
}

BOOL SkiaBitmapManager::DrawColor( UINT color,const RECT* rect, UINT a /*= 255*/ )
{
	ASSERT(NULL!=rect);

	SkRect skrt;

	skrt.set(SkIntToScalar(rect->left),SkIntToScalar(rect->top),SkIntToScalar(rect->right),SkIntToScalar(rect->bottom));
	SkPaint paint;
	paint.setColor(color);
	paint.setAlpha(a);
	m_wndCanvas->drawRect(skrt, paint);
	return TRUE;
}

//动画 必须用这个函数来绘色彩
BOOL SkiaBitmapManager::DrawColor( UINT color,HANDLE ResID )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;
	//这里可以考虑建立一个变化后的rect，以后使用不需要重新计算
	SkScalar sx =  info->ctrMatrix.getTranslateX();
	SkScalar sy =  info->ctrMatrix.getTranslateY();
	SkScalar sw =  info->pCtrlBtp->width() * (info->ctrMatrix.getScaleX());
	SkScalar sh =  info->pCtrlBtp->height() * (info->ctrMatrix.getScaleY());
	SkRect   srect;
	srect.setXYWH(sx,sy,sw,sh);

	SkPaint paint;
	paint.setColor(color);
	m_wndCanvas->drawRect(srect, paint);
	return TRUE;
}

BOOL SkiaBitmapManager::DrawImage( HANDLE ResID,const RECT* rect, UINT a /*= 255*/ )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;

	SkRect skrt;
	skrt.set(SkIntToScalar(rect->left),SkIntToScalar(rect->top),SkIntToScalar(rect->right),SkIntToScalar(rect->bottom));
	SkPaint sp;
	sp.setAlpha(a);
	m_wndCanvas->drawBitmapRect( *(info->pCtrlBtp),NULL,skrt,&sp);
	return TRUE;
}

BOOL SkiaBitmapManager::DrawImage( HANDLE ResID,const RECT* SrcRc, const RECT* DstRc,UINT a /*= 255*/ )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;

	ASSERT(SrcRc && DstRc);
	SkRect Dst_skrt;
	Dst_skrt.set(SkIntToScalar(DstRc->left),SkIntToScalar(DstRc->top),SkIntToScalar(DstRc->right),SkIntToScalar(DstRc->bottom));

	SkIRect Src_skrt;
	Src_skrt.set((SrcRc->left),(SrcRc->top),(SrcRc->right),(SrcRc->bottom));
	


	SkPaint sp;
	sp.setAlpha(a);
	m_wndCanvas->drawBitmapRect( *(info->pCtrlBtp),&Src_skrt,Dst_skrt,&sp);
	return TRUE;
}

//只画0，90，180，270
BOOL SkiaBitmapManager::DrawImage( HANDLE ResID,const RECT& SrcRc, int angle )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;

	int picWidth = info->pCtrlBtp->width();
	int picHeight= info->pCtrlBtp->height();

	int rcWidth = SrcRc.right - SrcRc.left;
	int  rcHeight = SrcRc.bottom - SrcRc.top;


	int dstPicWidth ;
	int dstPicHeight ;
	
	angle = angle%360;
	if (angle == 0 || angle == 180)
	{
		dstPicWidth = picWidth;
		dstPicHeight = picHeight;

	}
	else if (angle == 90 || angle == 270)
	{
		dstPicWidth = picHeight;
		dstPicHeight = picWidth;
	}
	else
	{
		ASSERT(0);
	}

	float fw = dstPicWidth/float(rcWidth);
	float fh = dstPicHeight/float(rcHeight);

	float fscale = 1;
	if (fw > fh && fw > 1)
	{
		fscale = 1/fw;
	}
	else if (fh > fw && fh > 1)
	{
		fscale = 1/fh;
	}


	info->ctrPnt.setAlpha(255);
	int cX = (SrcRc.left + SrcRc.right)/2;
	int cY = (SrcRc.top + SrcRc.bottom)/2;
	info->ctrMatrix.setTranslate(SkIntToScalar(SrcRc.left),SkIntToScalar(SrcRc.top));
	//info->ctrMatrix.postRotate(SkIntToScalar(angle),SkIntToScalar(cX),SkIntToScalar(cY));
	info->ctrMatrix.preScale(SkFloatToScalar(fscale),SkFloatToScalar(fscale));
	m_wndCanvas->drawBitmapMatrix(*(info->pCtrlBtp),info->ctrMatrix,&info->ctrPnt);//skrt.fLeft,skrt.fTop);
	//m_wndCanvas->drawRect()
	return TRUE;
}

void SkiaBitmapManager::SetRect( HANDLE ResID, const RECT* rect )
{
	if (NULL==ResID||NULL==rect)
	{
		return ;
	}
	
	SkiaInfo* info = (SkiaInfo*)ResID;
	info->ctrRect.set(SkIntToScalar(rect->left),SkIntToScalar(rect->top),SkIntToScalar(rect->right),SkIntToScalar(rect->bottom));

	PreAction(info);


}

void SkiaBitmapManager::SetAlpha( HANDLE ResID, UINT a )
{
	if (NULL==ResID)
	{
		return ;
	}
	SkiaInfo* info = (SkiaInfo*)ResID;
	info->ctrPnt.setAlpha(a);
}

 
void * SkiaBitmapManager::getBitmapPixels()
{
	if (NULL==m_wndBtp)
	{
		return NULL;
	}
	return m_wndBtp->getPixels();
}


void SkiaBitmapManager::DrawToDevice( HDC hdc,const RECT &rect )
{
	
	SetDIBitsToDevice(hdc, -rect.left, -rect.top,AfxGetDevWidth(),AfxGetDevHeight(),0, 0, 0,rect.bottom-rect.top,
		getBitmapPixels(),m_bitmapInfo, DIB_RGB_COLORS);
	

}



void SkiaBitmapManager::SaveStatus()
{
	m_wndCanvas->save();
}

void SkiaBitmapManager::ReleasStatus()
{
	m_wndCanvas->restore();
}

void SkiaBitmapManager::SetClipRect(const RECT &rect)
{
	m_wndCanvas->clipRect( SkRect::MakeLTRB( SkIntToScalar(rect.left),SkIntToScalar(rect.top),SkIntToScalar(rect.right),SkIntToScalar(rect.bottom)),SkRegion::kIntersect_Op );
}
void SkiaBitmapManager::InvalidRect( const RECT * rt )
{
	RECT  rect = *rt;
	static int h = AfxGetDevHeight();
	static int w = AfxGetDevWidth();
	//invRect.top = (rt.top<invRect.top)?rt.top:
	if (!m_b_invalidate)
	{
		int i = m_wndCanvas->save();
		m_b_invalidate=TRUE;
		m_clipRect = rect;
	}
	else
	{

		m_clipRect.left = m_clipRect.left<rect.left?m_clipRect.left:rect.left;
		m_clipRect.top = m_clipRect.top<rect.top?m_clipRect.top:rect.top;
		m_clipRect.right = m_clipRect.right>rect.right?m_clipRect.right:rect.right;
		m_clipRect.bottom = m_clipRect.bottom>rect.bottom?m_clipRect.bottom:rect.bottom;
 

		
	}
	m_clipRect.left = m_clipRect.left<0?0:m_clipRect.left;
	m_clipRect.top = m_clipRect.top<0?0:m_clipRect.top;
	m_clipRect.right = m_clipRect.right>w?w:m_clipRect.right;
	m_clipRect.bottom = m_clipRect.bottom>h?h:m_clipRect.bottom;
	m_wndCanvas->clipRect( SkRect::MakeLTRB( SkIntToScalar(m_clipRect.left),SkIntToScalar(m_clipRect.top),SkIntToScalar(m_clipRect.right),SkIntToScalar(m_clipRect.bottom)),SkRegion::kReplace_Op );
}

void SkiaBitmapManager::Validate()
{
	if (m_b_invalidate)
	{
		m_b_invalidate=FALSE;
		m_wndCanvas->restore();
		::SetRect(&m_clipRect,0,0,0,0);
	}
	
	//::SetRect(&m_invRect,ERROR_RECT,ERROR_RECT,ERROR_RECT,ERROR_RECT);
}

BOOL SkiaBitmapManager::AlphaAction( HANDLE h, AlphaAnimation * alphaAni )
{
	ASSERT(NULL!=h&&NULL!=alphaAni);
	SkiaInfo* info = (SkiaInfo*)h;
	float a = alphaAni->getAlphaValue();
	info->ctrPnt.setAlpha(UINT(255*a));

	return TRUE;
}

BOOL SkiaBitmapManager::ScaleAction( HANDLE h,  ScaleAnimation * alphaAni )
{
	ASSERT(NULL!=h&&NULL!=alphaAni);
	SkiaInfo* info = (SkiaInfo*)h;
	Animation::PIVOT_TYPE ptX = alphaAni->getPivotXType();
	Animation::PIVOT_TYPE ptY = alphaAni->getPivotYType();
	ASSERT(ptX==ptY);
	float ax = alphaAni->getScaleXValue();
	float ay = alphaAni->getScaleYValue();



	if (ptX==Animation::RELATIVE_TO_ORIGIN)
	{
		info->ctrMatrix.postScale(SkFloatToScalar(ax),SkFloatToScalar(ay));//以原点开始缩放
	}
	else if (ptX==Animation::RELATIVE_TO_SELF)
	{

		float pivotx = alphaAni->getPivotXValue();
		float pivoty = alphaAni->getPivotYValue();

		SkScalar startx = pivotx* info->ctrRect.width() + info->ctrMatrix.getTranslateX();
		SkScalar starty = pivoty* info->ctrRect.height() + info->ctrMatrix.getTranslateY();

		info->ctrMatrix.postScale(SkFloatToScalar(ax),SkFloatToScalar(ay), startx ,starty);//以指定点开始缩放
	}
	else
	{
		ASSERT(0);
	}
	return TRUE;
}

BOOL SkiaBitmapManager::TranslateAction( HANDLE h, TranslateAnimation * alphaAni )
{
	ASSERT(NULL!=h&&NULL!=alphaAni);
	SkiaInfo* info = (SkiaInfo*)h;

	float ax = alphaAni->getTranXValue();
	float ay = alphaAni->getTranYValue();

	info->ctrMatrix.postTranslate(SkFloatToScalar(ax),SkFloatToScalar(ay));

	return TRUE;
}

BOOL SkiaBitmapManager::RotateYAction( HANDLE h, RotateYAnimation * alphaAni )
{
	ASSERT(NULL!=h&&NULL!=alphaAni);
	SkiaInfo* info = (SkiaInfo*)h;
	float a = alphaAni->getRotateY();
	SkScalar center_x = (info->ctrRect.left()+info->ctrRect.right())/2;

	Sk3DView	sk3DView;
	SkMatrix	matrix;
	sk3DView.rotateY(SkFloatToScalar(a));
	sk3DView.getMatrix(&matrix);
	matrix.preTranslate(-center_x, 0);
	matrix.postTranslate(center_x, 0);
	info->ctrMatrix.postConcat(matrix);

	return TRUE;
}

void SkiaBitmapManager::SetInvertX( int m_Invert_y )
{
	Sk3DView	sk3DView;
	SkMatrix	matrix;
	//sk3DView.rotateX(SkFloatToScalar(180.0));
	//sk3DView.getMatrix(&matrix);

	

	//SkScalar move_y = SkIntToScalar(m_Invert_y);
	matrix.setScale(SkIntToScalar(1),SkIntToScalar(-1),SkIntToScalar(400),SkIntToScalar(m_Invert_y));
	//matrix.preTranslate( 0, -move_y);
	//matrix.postTranslate( 0, move_y);
	m_wndCanvas->setMatrix(matrix);
}

void SkiaBitmapManager::SetTextGradient( H_SKFONT hfont, int nfrom_color, int nto_color, int ny0, int ny1 )
{
	SkPaint *pfntPaint = (SkPaint *)hfont;
	SkPoint p = SkPoint::Make(SkIntToScalar(0),SkIntToScalar(ny0));
	SkPoint q = SkPoint::Make(SkIntToScalar(0),SkIntToScalar(ny1));
	 SkPoint pts[] ={p,q};
	 SkColor colors[] ={
		 nfrom_color,nto_color
	 };
	 SkShader *shader ;
	 shader =SkGradientShader::CreateLinear(
		 pts,colors,NULL,SK_ARRAY_COUNT(colors),SkShader::kClamp_TileMode);
	 pfntPaint->setShader(shader);
	 shader->unref();
}


void SkiaBitmapManager::DoAction( HANDLE h, Animation *pAni )
{
	if (Animation::ALPHA==(pAni)->getType())
	{
		AlphaAction(h, (AlphaAnimation *)pAni);
	}
	else if (Animation::SCALE==(pAni)->getType())
	{
		ScaleAction(h,(ScaleAnimation *)pAni);
	}
	else if (Animation::TRANSLATE==(pAni)->getType())
	{
		TranslateAction(h, (TranslateAnimation *)pAni);
	}
	else if (Animation::ROTATE_Y==(pAni)->getType())
	{
		RotateYAction(h, (RotateYAnimation *)pAni);
	}
}

void SkiaBitmapManager::PreAction( HANDLE h )
{
	ASSERT(NULL!=h);
	SkiaInfo* info = (SkiaInfo*)h;

	SkScalar prex_s = info->ctrRect.width()/info->pCtrlBtp->width();
	SkScalar prey_s = info->ctrRect.height()/info->pCtrlBtp->height();

	//以下是初始情况
	info->ctrPnt.setAlpha(255);
	info->ctrMatrix.setTranslate(info->ctrRect.left(), info->ctrRect.top());
	info->ctrMatrix.preScale(prex_s,prey_s);
}


void SkiaBitmapManager::NotInAction( HANDLE h )
{
	ASSERT(NULL!=h);
	SkiaInfo* info = (SkiaInfo*)h;
	info->ctrPnt.setAlpha(0);
}


void SkiaBitmapManager::setActivityScreen( GxxView* view, HANDLE hscreen )
{
	//int i = m_wndCanvas->save();
	SkiaInfo* info = (SkiaInfo*)hscreen;
	info->ctrPnt.setAlpha(255);
	m_wndCanvas->setBitmapDevice( *(info->pCtrlBtp) );
	view->DoPaint();
	m_wndCanvas->setBitmapDevice(*m_wndBtp);
	//m_wndCanvas->restore();
	
}

int SkiaBitmapManager::GetWidth( HANDLE ResID )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;
	return info->pCtrlBtp->width();
}

int SkiaBitmapManager::GetHeight( HANDLE ResID )
{
	ASSERT(NULL!=ResID);
	SkiaInfo* info = (SkiaInfo*)ResID;
	return info->pCtrlBtp->height();
}









/*
BOOL SkiaBitmapManager::getRightRect( RECT &srcrect, RECT &destrect )
{
	//m_invRect
	RECT  trRect;//表示相交的部分
	//找到相交的 x轴坐标
	if (!getCoordinate(trRect.left, trRect.right, m_invRect.left, m_invRect.right, destrect.left, destrect.right))
	{
		return FALSE;
	}
	//找到相交的 y轴坐标
	if (!getCoordinate(trRect.top, trRect.bottom, m_invRect.top, m_invRect.bottom, destrect.top, destrect.bottom))
	{
		return FALSE;
	}
	LONG lenD = destrect.right - destrect.left;
	LONG lenS = srcrect.right - srcrect.left;
	srcrect.left = lenS*(trRect.left - destrect.left)/lenD;
	srcrect.right = lenS * (trRect.right - destrect.left)/lenD;

	lenD = destrect.bottom - destrect.top;
	lenS = srcrect.bottom - srcrect.top;
	srcrect.top = lenS*(trRect.top - destrect.top)/lenD;
	srcrect.bottom = lenS * (trRect.bottom - destrect.top)/lenD;
	destrect =  trRect;
	return TRUE;
}



BOOL SkiaBitmapManager::getCoordinate( LONG & xget, LONG & yget, LONG xA, LONG yA, LONG xB, LONG yB )
{
	xget = (xA<xB)? xB:xA; //选大
	yget = (yA>yB)? yB:yA; //选小的
	LONG  lw = yget-xget;
	//相交的部分要大于0，且小于等于两个边长
	if (lw>0&&lw<=yA-xA&&lw<=yB-xB)//
	{
		return TRUE;
	}
	return FALSE;
}
*/


