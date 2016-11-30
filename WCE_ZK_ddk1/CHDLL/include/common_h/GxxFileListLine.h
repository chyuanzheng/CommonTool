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
	void setFileLine( int index,const wstring  &wstr,ICON_TYPE type,HANDLE h);//index �ǵڼ��У�nline���Լ���line��Rect
	void setFileLine( int index,const string  &str_id,ICON_TYPE type,HANDLE h);//index �ǵڼ��У�nline���Լ���line��Rect
	ICON_TYPE getLineType(){return m_icon_type;}
	HANDLE    getHandle(){return m_handle;}
	const wstring & getLineName(){return m_strText;}

protected:
	virtual void Draw();

private: 
	static GxxPicture *S_iconMusic;//��� icon
	static GxxPicture *S_iconMovie;//��� icon
	static GxxPicture *S_iconPicture;//��� icon
	static GxxPicture *S_iconFolder;//��� icon
	static GxxSwText *S_pTextName;

	ICON_TYPE  m_icon_type;
	wstring    m_strText;
	HANDLE     m_handle;
	const wstring    *m_strText_id;
};
