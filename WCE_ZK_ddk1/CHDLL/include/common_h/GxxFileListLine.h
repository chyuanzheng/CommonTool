#pragma once

#include "GxxView.h"
#include "GxxLBLine.h"
#include "bluetooth.h"
class GxxPicture;
class GxxSwText;

class CE_CONTROL_API GxxFileListLine : public GxxLBLine
{
public:
	typedef enum {NoneLine,MusicLine,MovieLine,PictureLine,FolderLine}ICON_TYPE;
	GxxFileListLine();
	virtual ~GxxFileListLine();
	void setFileLine( int index,const wstring  &wstr,ICON_TYPE type,HANDLE h);//index 是第几行，nline可以计算line的Rect
	void setFileLine( int index,const string  &str_id,ICON_TYPE type,HANDLE h);//index 是第几行，nline可以计算line的Rect
	ICON_TYPE getLineType(){return m_icon_type;}
	HANDLE    getHandle(){return m_handle;}
	const wstring & getLineName(){return m_strText;}

protected:
	virtual void Draw();

private: 
	static GxxPicture *S_iconMusic;//左边 icon
	static GxxPicture *S_iconMovie;//左边 icon
	static GxxPicture *S_iconPicture;//左边 icon
	static GxxPicture *S_iconFolder;//左边 icon
	static GxxSwText *S_pTextName;

	ICON_TYPE  m_icon_type;
	wstring    m_strText;
	HANDLE     m_handle;
	const wstring    *m_strText_id;
};
