#pragma once
#include "StrHelp.h"
#include "FileItem.h"
#include "GxxListGroupBase.h"

class GxxListPercent;
struct FilePathSet;
typedef list<wstring> TL_STRING;
typedef list<FilePathSet *> TL_FPSET;
struct FilePathSet
{
	FilePathSet()
	{
		m_parent_set = NULL;
	}
	wstring      m_path_name;//��ǰĿ¼������
	FilePathSet *m_parent_set;//��Ŀ¼
	TL_STRING	m_g_movie;//���е�movie �ļ�
	TL_STRING	m_g_picture;//
	TL_STRING	m_g_music;//
	int         m_movie_index;
	int         m_picture_index;
	int         m_music_index; 
	static	int         s_movie_count;
	static  int         s_picture_count;
	static  int         s_music_count; 
	TL_FPSET	m_AllChildSets;//��ǰĿ¼��Ӧ����Ŀ¼
};


class CE_CONTROL_API GxxFileListGroup : public GxxListGroupBase ,public FileListGroupInterface
{
public:
	void GotoPath(const wstring &path, const wstring & music_ext, const wstring & vidio_ext,const wstring & pic_ext);	//�趨��Ŀ¼·�������ļ���չ��
	virtual EnumSort GetDepositClassification(FileItem::EnumFileType etype) {return m_sort;}
	virtual bool GetMediaItemInFolder(int nItem,FileItem::EnumFileType etype,FileItem &item);		//�����ļ�����ָ��ID��ITEM
	virtual bool GetTotalMediaCountInFolder(FileItem::EnumFileType etype,int &count );	//��ȡ�ļ�����ý���ļ�����Ŀ
	virtual bool GetMediaItemInAll(int nItem,FileItem::EnumFileType etype,FileItem &item);
	virtual bool GetTotalMediaCountInAll(FileItem::EnumFileType etype,int &count );						//���ý���ļ�������Ŀ
	virtual void DeleteAllItem();


public:
	GxxFileListGroup();
	virtual ~GxxFileListGroup();
	
	static GxxView* CreateControl();



protected:
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual BOOL Response( 	UINT nMsg, WPARAM wParam, LPARAM lParam );

private:
	typedef enum {FolderLayer=0,AllFilesLayer,NoneLayer}MEDIA_LAYER;
	FileItem::EnumFileType   m_media_type;
	EnumSort	   m_sort;
	FilePathSet *m_cur_set;  
	wstring      m_goto_path;//��Ŀ¼��
	int         m_nfiles;

	GxxListPercent *m_percentBtn;
	void ShowPathList();
	void releaseAllSet();
	void doReleaseAllSet(FilePathSet *path_set);
	typedef  vector<FileItem *> TL_FILE_ITEM;
	bool FileInExtType( const wchar_t *filename,const TL_WSTR &tl_ext );
	void SetFileToList( FilePathSet *path_set,const wstring &path,const TL_WSTR &tlMusicExt,const TL_WSTR &tlVidioExt,const TL_WSTR &tlPicExt,int nPathIndex =0 );
	void releasFileItem(TL_FILE_ITEM & tlist);
	void LineBtnDown( WPARAM wParam, LPARAM lParam );
	void AddAllMusicFile( FilePathSet * _set );
	void AddAllMovieFile( FilePathSet * _set );
	void AddAllPictureFile( FilePathSet * _set );
	bool GetPathFormSet( FilePathSet * fileset, wstring & path );
	bool GetFileNameFromList( int nItem,  wstring &name,  TL_STRING &wsList );
	void GetMusicCount( FilePathSet * _set, int & count );
	void GetMovieCount( FilePathSet * _set, int & count );
	void GetPictureCount( FilePathSet * _set, int & count );
	bool GetMusicItem( FilePathSet * _set,int& nItem, FileItem & item );
	bool GetMovieItem( FilePathSet * _set,int& nItem, FileItem & item );
	bool GetPictureItem( FilePathSet * _set,int& nItem, FileItem & item );
};
