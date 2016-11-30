#include "StdAfx.h"
#include "GxxFileListGroup.h"
#include "StrHelp.h"
#include "XmlDef.h"
#include "MesDef.h"
#include "SkiaBitmapManager.h"
#include "ControlHelp.h"
#include "GXCreateControls.h"
#include "GxxView.h"
#include "GxxAniButton.h"
#include "GxxProgressV.h"
#include "GxxFileLBList.h"
#include "GxxListPercent.h"
#include "GxxSwText.h"

//
//#include "aygshell.h"
#define  PercentLineMin 60
static RegisterHelp help("GxxFileListGroup", GxxFileListGroup::CreateControl);
GxxView* GxxFileListGroup::CreateControl()
{
	return new GxxFileListGroup;
}
GxxFileListGroup::GxxFileListGroup()
{
	m_curListBox =  new GxxFileLBList;
	AddCtrl(m_curListBox);
	m_cur_set = NULL;
	m_media_type = FileItem::FILE_TYPE_NULL;
	m_sort = DEPOSIT_BY_NONE;

}

GxxFileListGroup::~GxxFileListGroup()
{

}

BOOL GxxFileListGroup::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{

	switch( nMsg )
	{
	case CTR_MESSAGE:
		if (MES_LBUTTONUP==lParam)
		{
			if ((GxxView *)wParam == m_btx)
			{
				AfxPostMessage(CTR_LISTBOX_X, (WPARAM)this, 0 );
				return TRUE;
			}
			if ((GxxView *)wParam == m_btnBack)
			{
				if (m_media_type ==  FileItem::FILE_TYPE_NULL)
				{
					ASSERT(m_sort == DEPOSIT_BY_NONE);
					AfxPostMessage(CTR_LISTBOX_X, (WPARAM)this, 0 );
				}
				else
				{
					if (m_sort == DEPOSIT_BY_NONE)
					{
						m_media_type = FileItem::FILE_TYPE_NULL;
						ShowPathList();
					}
					else if (m_sort == DEPOSIT_BY_ALL)
					{
						m_sort = DEPOSIT_BY_NONE;
						ShowPathList();
					}
					else 
					{
						ASSERT(m_sort == DEPOSIT_BY_FOLDER);
						if (m_cur_set->m_parent_set == NULL)
						{
							m_sort = DEPOSIT_BY_NONE;
							ShowPathList();
						}
						else
						{
							m_cur_set = m_cur_set->m_parent_set;
							ShowPathList();
						}
					}
				}
				return TRUE;
			}
		}
		break;
	case CTR_LISTLINE_MES:
		LineBtnDown(wParam, lParam);
		return TRUE;
	default:
		break;
	}
	return GxxListGroupBase::Response(nMsg,wParam,lParam);
}

void GxxFileListGroup::setCtrLayout( TiXmlElement * ele )
{

	setCtrName(ele);
	setCtrRect(ele);
	if (setPicHandle(ele,BACKGROUD))
	{
		bindHandleRect();
	}
	
	

	TiXmlElement * chid = ele->FirstChildElement();
	setCtrList(chid);
	FindChildCtrls();
	m_percentBtn = (GxxListPercent *)safeFindViewByName("list_percent");

	ASSERT(m_btnBack!=NULL && m_btx!=NULL);

}


int FilePathSet::s_movie_count = 0;
int FilePathSet::s_music_count = 0;
int FilePathSet::s_picture_count = 0;

void GxxFileListGroup::GotoPath( const wstring &path, const wstring &music_ext, const wstring &vidio_ext,const wstring & pic_ext)
{
	releaseAllSet();

	TL_WSTR tListExtMusic;
	TL_WSTR tListExtVidio;
	TL_WSTR tListExtPic;

	StrHelp::WStringToSubWStr(music_ext,tListExtMusic,L'_');
	StrHelp::WStringToSubWStr(vidio_ext,tListExtVidio,L'_');
	StrHelp::WStringToSubWStr(pic_ext,tListExtPic,L'_');

	m_goto_path = path;
	m_media_type = FileItem::FILE_TYPE_NULL;
	m_sort = DEPOSIT_BY_NONE;

	FilePathSet::s_movie_count = 0;
	FilePathSet::s_music_count = 0;
	FilePathSet::s_picture_count = 0;
	m_cur_set = new FilePathSet;
	m_nfiles = 0;
	SetFileToList(m_cur_set,path,tListExtMusic,tListExtVidio,tListExtPic);//这里要防止异常；
	ShowPathList();

	return;

}

void GxxFileListGroup::GetMusicCount( FilePathSet * _set, int & count )
{
	count += _set->m_g_music.size();
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		GetMusicCount(*pos,count);
	}
}
void GxxFileListGroup::GetMovieCount( FilePathSet * _set, int & count )
{
	count += _set->m_g_movie.size();
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		GetMovieCount(*pos,count);
	}
}
void GxxFileListGroup::GetPictureCount( FilePathSet * _set, int & count )
{
	count += _set->m_g_picture.size();
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		GetPictureCount(*pos,count);
	}
}




bool GxxFileListGroup::GetTotalMediaCountInAll( FileItem::EnumFileType etype,int &count )
{
	if ( m_cur_set == NULL || etype == FileItem::FILE_TYPE_NULL)
	{
		return false;
	}

	FilePathSet *_set = m_cur_set;
	while(_set->m_parent_set!=NULL)//找到最上层的目录
	{
		_set = _set->m_parent_set;
	}
	count = 0;
	if (etype == FileItem::FILE_TYPE_MUSIC)
	{
		GetMusicCount(_set,count);
	
	}
	else if (etype == FileItem::FILE_TYPE_MOVIE )
	{
		GetMovieCount(_set,count);
	}
	else if (etype == FileItem::FILE_TYPE_PICTURE )
	{
		GetPictureCount(_set,count);
	}
	return true;

}

bool GxxFileListGroup::GetMusicItem( FilePathSet * _set,int& nItem, FileItem & item )
{
	if (nItem >= _set->m_g_music.size())
	{
		nItem -= _set->m_g_music.size();
	}
	else
	{
		TL_STRING::iterator pos = _set->m_g_music.begin();
		std::advance(pos,nItem);
		item.fileName = *pos;
		GetPathFormSet(_set,item.filePath);
		item.filePath += L"\\" + item.fileName;
		return true;
	}
	
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		if (GetMusicItem(*pos,nItem,item))
		{
			return true;
		}
	}
	return false;
}

bool GxxFileListGroup::GetMovieItem( FilePathSet * _set,int& nItem, FileItem & item )
{
	if (nItem >= _set->m_g_movie.size())
	{
		nItem -= _set->m_g_movie.size();
	}
	else
	{
		TL_STRING::iterator pos = _set->m_g_movie.begin();
		std::advance(pos,nItem);
		item.fileName = *pos;
		GetPathFormSet(_set,item.filePath);
		item.filePath += L"\\" + item.fileName;
		return true;
	}

	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		if (GetMovieItem(*pos,nItem,item))
		{
			return true;
		}
	}
	return false;
}

bool GxxFileListGroup::GetPictureItem( FilePathSet * _set,int& nItem, FileItem & item )
{
	if (nItem >= _set->m_g_picture.size())
	{
		nItem -= _set->m_g_picture.size();
	}
	else
	{
		TL_STRING::iterator pos = _set->m_g_picture.begin();
		std::advance(pos,nItem);
		item.fileName = *pos;
		GetPathFormSet(_set,item.filePath);
		item.filePath += L"\\" + item.fileName;
		return true;
	}

	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos)
	{
		if (GetPictureItem(*pos,nItem,item))
		{
			return true;
		}
	}
	return false;
}


bool GxxFileListGroup::GetMediaItemInAll( int nItem,FileItem::EnumFileType etype,FileItem &item )
{
	if ( m_cur_set == NULL || etype == FileItem::FILE_TYPE_NULL)
	{
		return false;
	}

	FilePathSet *_set = m_cur_set;
	while(_set->m_parent_set!=NULL)//找到最上层的目录
	{
		_set = _set->m_parent_set;
	}

	bool bRet = false;
	item.fileType = etype;
	if (etype == FileItem::FILE_TYPE_MUSIC)
	{
		bool bRet = GetMusicItem(_set,nItem,item);
	}
	else if (etype == FileItem::FILE_TYPE_MOVIE )
	{
		bool bRet = GetMovieItem(_set,nItem,item);
	}
	else if (etype == FileItem::FILE_TYPE_PICTURE )
	{
		bool bRet = GetPictureItem(_set,nItem,item);
	}


	return bRet;
}



bool GxxFileListGroup::GetTotalMediaCountInFolder( FileItem::EnumFileType etype,int &count )
{
	if (m_sort != DEPOSIT_BY_FOLDER || m_cur_set == NULL || etype == FileItem::FILE_TYPE_NULL)
	{
		return false;
	}
	if (m_media_type !=  etype)
	{
		return false;
	}
	count = ((GxxFileLBList *)m_curListBox)->getCtrlsSize();
	return true;
	//if (etype == FileItem::FILE_TYPE_MUSIC)
	//{
	//	count = m_cur_set->m_g_music.size();
	//}
	//else if (etype == FileItem::FILE_TYPE_MOVIE )
	//{
	//	count = m_cur_set->m_g_movie.size();
	//}
	//else if (etype == FileItem::FILE_TYPE_PICTURE )
	//{
	//	count = m_cur_set->m_g_picture.size();
	//}
	//return true;
}


bool GxxFileListGroup::GetMediaItemInFolder( int nItem,FileItem::EnumFileType etype,FileItem &item )
{
	if (m_sort != DEPOSIT_BY_FOLDER || m_cur_set == NULL || etype == FileItem::FILE_TYPE_NULL)
	{
		return false;
	}
	if (m_media_type !=  etype)
	{
		return false;
	}
	item.fileType = etype;

	bool bRet = ((GxxFileLBList *)m_curListBox)->getLineName(nItem,item.fileName);


	if (bRet)
	{
		GetPathFormSet(m_cur_set,item.filePath);
		item.filePath += L"\\" + item.fileName;
	}

	return bRet;
}


bool GxxFileListGroup::GetFileNameFromList( int nItem,  wstring &name,  TL_STRING &wsList )
{
	if (nItem >= wsList.size())
	{
		return false;
	}
	TL_STRING::iterator pos = wsList.begin();
	std::advance(pos,nItem);
	name = *pos;
	return true;
}

void GxxFileListGroup::releaseAllSet()
{
	if (NULL == m_cur_set)
	{
		return;
	}
	while(m_cur_set->m_parent_set!=NULL)//找到最上层的目录
	{
		m_cur_set = m_cur_set->m_parent_set;
	}
	doReleaseAllSet(m_cur_set);
	m_cur_set = NULL;
}

void GxxFileListGroup::doReleaseAllSet(FilePathSet *path_set)
{
	for (TL_FPSET::iterator pos = path_set->m_AllChildSets.begin();pos != path_set->m_AllChildSets.end(); ++pos)
	{
		doReleaseAllSet(*pos);
	}
	delete path_set;
}

#define  MAX_PATH_INDEX   4
#define  MAX_FILES   7000
void GxxFileListGroup::SetFileToList( FilePathSet *path_set,const wstring &path,const TL_WSTR &tlMusicExt,const TL_WSTR &tlVidioExt,const TL_WSTR &tlPicExt,int nPathIndex /*=0 */  )
{
	nPathIndex++;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = ::FindFirstFile((path + L"\\*.*").c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return;
	} 


	path_set->m_movie_index   = FilePathSet::s_movie_count;
	path_set->m_picture_index = FilePathSet::s_picture_count;
	path_set->m_music_index   = FilePathSet::s_music_count;

	if (MAX_FILES == m_nfiles)
	{
		return;
	}
	do 
	{
		if (MAX_FILES == m_nfiles)
		{
			break;
		}
		m_nfiles++;
		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0]==L'.')
			{
				continue;
			}
			FilePathSet * child_set = new FilePathSet;
			child_set->m_parent_set = path_set;
			child_set->m_path_name = FindFileData.cFileName;
			path_set->m_AllChildSets.push_back(child_set);
			
		}
		else
		{
			if (FileInExtType(FindFileData.cFileName, tlMusicExt) )
			{
				path_set->m_g_music.push_back(wstring(FindFileData.cFileName));
			}
			else if ( FileInExtType(FindFileData.cFileName, tlVidioExt)  )
			{
				path_set->m_g_movie.push_back(wstring(FindFileData.cFileName));
			}
			else if ( FileInExtType(FindFileData.cFileName, tlPicExt)  )
			{
				path_set->m_g_picture.push_back(wstring(FindFileData.cFileName));
			}
			
		}

	} while(FindNextFile(hFind, &FindFileData));
		
	FilePathSet::s_movie_count	 += path_set->m_g_movie.size();
	FilePathSet::s_music_count   += path_set->m_g_music.size();
	FilePathSet::s_picture_count += path_set->m_g_picture.size();

	TL_FPSET  &all_child_sets = path_set->m_AllChildSets;
	if (nPathIndex <= MAX_PATH_INDEX)
	{
		for (TL_FPSET::iterator pos = all_child_sets.begin(); pos!=all_child_sets.end(); ++pos)
		{
			SetFileToList ( *pos,path + L"\\" + (*pos)->m_path_name,tlMusicExt,tlVidioExt,tlPicExt,nPathIndex);
		}
	}
	FindClose(hFind);
}

void GxxFileListGroup::releasFileItem( TL_FILE_ITEM & tlist )
{
	TL_FILE_ITEM::iterator pos;
	for (pos = tlist.begin();pos != tlist.end();++pos)
	{
		delete (*pos);
	}
	tlist.clear();
}

bool GxxFileListGroup::FileInExtType( const wchar_t *filename,const TL_WSTR &tl_ext)
{
	ASSERT(NULL != filename);
	wstring wName = filename;
	wstring wExtStr;

	int nlocal =wName.find_last_of(L'.');
	if (nlocal > 0)
	{
		wExtStr = wName.substr(nlocal + 1);
	}
	else
	{
		return false;
	}

	TL_WSTR::const_iterator pos;
	for (pos = tl_ext.begin(); pos != tl_ext.end(); ++pos)
	{
		if (StrHelp::WStringEqual(wExtStr,*pos))
		{
			return true;
		}
	}	
	return false;
}



void GxxFileListGroup::LineBtnDown( WPARAM wParam, LPARAM lParam )
{
	int nline = lParam;
	if (m_media_type == FileItem::FILE_TYPE_NULL)
	{
		ASSERT(nline < 3);
		ASSERT(m_sort == DEPOSIT_BY_NONE);
		m_media_type = (FileItem::EnumFileType )nline;
		ShowPathList();
	}
	else
	{
		if (m_sort == DEPOSIT_BY_NONE)
		{
			ASSERT(nline < 2);
			m_sort = EnumSort(nline);
			ShowPathList();
		}
		else
		{
			GxxFileListLine * fileline  = (GxxFileListLine * )wParam;
			if (fileline->getLineType() == GxxFileListLine::FolderLine)//
			{
				//DEPOSIT_BY_FOLDER ,
				FilePathSet * fileset = (FilePathSet *)fileline->getHandle();
				ASSERT(m_cur_set == fileset);
				for (TL_FPSET::iterator pos = m_cur_set->m_AllChildSets.begin(); pos != m_cur_set->m_AllChildSets.end(); ++pos)
				{
					if ((*pos)->m_path_name == fileline->getLineName())
					{
						m_cur_set = *pos;
						ShowPathList();
						break;
					}
				}
			}
			else 
			{
				//DEPOSIT_BY_FOLDER ,DEPOSIT_BY_ALL
				FilePathSet * fileset = (FilePathSet *)fileline->getHandle();
				ASSERT(NULL!=fileset);
				FileItem item;
				item.fileName = fileline->getLineName();
				bool b = GetPathFormSet(fileset,item.filePath);
				ASSERT(b);
				item.filePath += L"\\" + fileline->getLineName();

				int indexInAll = 0;
				switch(fileline->getLineType())
				{
				case GxxFileListLine::MusicLine:
					item.fileType = FileItem::FILE_TYPE_MUSIC;
					indexInAll = fileset->m_music_index;
					break;
				case GxxFileListLine::MovieLine:
					item.fileType = FileItem::FILE_TYPE_MOVIE;
					indexInAll = fileset->m_movie_index;
					break;
				case GxxFileListLine::PictureLine:
					item.fileType = FileItem::FILE_TYPE_PICTURE;
					indexInAll = fileset->m_picture_index;
					break;
				default:
					ASSERT(0);
					break;
				}
				if (DEPOSIT_BY_ALL == m_sort){
					indexInAll = lParam;
				}
				else{
					indexInAll = indexInAll + (int)lParam - fileset->m_AllChildSets.size(); 
				}
				
				AfxSendMessage( CTR_LISTBOX_FILEITEM, (WPARAM)(&item), (LPARAM)indexInAll );//CTR_LISTBOX_FILEITEM
			}
			
		}
	}
}

void GxxFileListGroup::ShowPathList()
{
	m_curListBox->deleteAllCtrls();
	if (m_media_type == FileItem::FILE_TYPE_NULL)
	{
		 m_titleText->setTextFromId("ID_SEARCH");
		 m_titleText->invalidateRect();
		((GxxFileLBList *)m_curListBox)->AddLine("MUSIC_31");
		((GxxFileLBList *)m_curListBox)->AddLine("MOVIE_31");
		((GxxFileLBList *)m_curListBox)->AddLine("PICTURE_31");
	}
	else 
	{
		if (m_sort == DEPOSIT_BY_NONE)
		{
			switch(m_media_type)
			{
			case FileItem::FILE_TYPE_MUSIC:
				m_titleText->setTextFromId("MUSIC_31");
				break;
			case  FileItem::FILE_TYPE_MOVIE:
				m_titleText->setTextFromId("MOVIE_31");
				break;
			case  FileItem::FILE_TYPE_PICTURE:
				m_titleText->setTextFromId("PICTURE_31");
				break;
			default:
				ASSERT(0);
				break;
			}
			m_titleText->invalidateRect();
			((GxxFileLBList *)m_curListBox)->AddLine("FOLDER_31");
			((GxxFileLBList *)m_curListBox)->AddLine("ALL_31");
		}
		else
		{
			ASSERT(NULL!=m_cur_set);
			if (m_sort == DEPOSIT_BY_FOLDER)
			{
				for (TL_FPSET::iterator pos = m_cur_set->m_AllChildSets.begin(); pos != m_cur_set->m_AllChildSets.end(); ++pos)
				{
					((GxxFileLBList *)m_curListBox)->AddLine((*pos)->m_path_name, GxxFileListLine::FolderLine,(HANDLE)m_cur_set);
				}
				switch(m_media_type)
				{
				case FileItem::FILE_TYPE_MUSIC:
					for (TL_STRING::iterator pos = m_cur_set->m_g_music.begin(); pos != m_cur_set->m_g_music.end(); ++pos)
					{
						((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::MusicLine,(HANDLE)m_cur_set);
					}
					break;
				case  FileItem::FILE_TYPE_MOVIE:
					for (TL_STRING::iterator pos = m_cur_set->m_g_movie.begin(); pos != m_cur_set->m_g_movie.end(); ++pos)
					{
						((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::MovieLine,(HANDLE)m_cur_set);
					}
					break;
				case  FileItem::FILE_TYPE_PICTURE:
					for (TL_STRING::iterator pos = m_cur_set->m_g_picture.begin(); pos != m_cur_set->m_g_picture.end(); ++pos)
					{
						((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::PictureLine,(HANDLE)m_cur_set);
					}
					break;
				default:
					ASSERT(0);
					break;
				}
			}
			else if (m_sort == DEPOSIT_BY_ALL)
			{
				ASSERT(m_cur_set->m_parent_set == NULL);
				switch(m_media_type)
				{
				case FileItem::FILE_TYPE_MUSIC:
					AddAllMusicFile(m_cur_set);
					break;
				case  FileItem::FILE_TYPE_MOVIE:
					AddAllMovieFile(m_cur_set);
					break;
				case  FileItem::FILE_TYPE_PICTURE:
					AddAllPictureFile(m_cur_set);
					break;
				default:
					ASSERT(0);
					break;
				}
			}
		}
	}
	m_curListBox->FreshListBox();
	m_curListBox->ResetPosition();
	m_percentBtn->setDraw(m_curListBox->getCtrlsSize()>PercentLineMin);
	m_percentBtn->invalidateRect();
	m_curListBox->invalidateRect();
}

void GxxFileListGroup::DeleteAllItem()
{
	m_curListBox->deleteAllCtrls();
	m_percentBtn->setDraw(false);
	m_percentBtn->invalidateRect();
	m_curListBox->FreshListBox();	
	
}

void GxxFileListGroup::AddAllMusicFile( FilePathSet * _set )
{
	for (TL_STRING::iterator pos = _set->m_g_music.begin(); pos != _set->m_g_music.end(); ++pos)
	{
		((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::MusicLine,(HANDLE)_set);
	}
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos )
	{
		AddAllMusicFile(*pos);
	}
}

void GxxFileListGroup::AddAllMovieFile( FilePathSet * _set )
{
	for (TL_STRING::iterator pos = _set->m_g_movie.begin(); pos != _set->m_g_movie.end(); ++pos)
	{
		((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::MovieLine,(HANDLE)_set);
	}
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos )
	{
		AddAllMovieFile(*pos);
	}
}

void GxxFileListGroup::AddAllPictureFile( FilePathSet * _set )
{
	for (TL_STRING::iterator pos = _set->m_g_picture.begin(); pos != _set->m_g_picture.end(); ++pos)
	{
		((GxxFileLBList *)m_curListBox)->AddLine((*pos), GxxFileListLine::PictureLine,(HANDLE)_set);
	}
	for (TL_FPSET::iterator pos = _set->m_AllChildSets.begin(); pos != _set->m_AllChildSets.end(); ++pos )
	{
		AddAllPictureFile(*pos);
	}
}

bool GxxFileListGroup::GetPathFormSet( FilePathSet * fileset, wstring & path )
{
	if(NULL == fileset){
		return false;
	}
	path = fileset->m_path_name;
	fileset = fileset->m_parent_set;
	while (fileset != NULL && fileset->m_path_name.size() >0)
	{
		path = fileset->m_path_name + L"\\" +  path;
		fileset = fileset->m_parent_set;
	}
	if (path.size()> 0)
	{
		path = m_goto_path + L"\\" + path ;
	}
	else
	{
		path = m_goto_path;
	}
	
	return true;
}


