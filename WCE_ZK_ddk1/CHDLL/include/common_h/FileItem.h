#pragma once




class FileItem
{
public:
	enum EnumFileType
	{
		FILE_TYPE_MUSIC= 0,
		FILE_TYPE_MOVIE,
		FILE_TYPE_PICTURE,
		FILE_TYPE_NULL
	};
	EnumFileType fileType;
	wstring  fileName;
	wstring  filePath;
};


class  CE_CONTROL_API FileListGroupInterface
{
public:
	typedef enum EnumSortClassification 	//存放归类方式
	{
		DEPOSIT_BY_FOLDER = 0,		//按文件夹归类
		DEPOSIT_BY_ALL,
		DEPOSIT_BY_NONE	//无归类
	}EnumSort;

	virtual void GotoPath(const wstring &path, const wstring & music_ext, const wstring & vidio_ext,const wstring & pic_ext) = 0;	//设定根目录路径，和文件拓展名
	virtual EnumSort GetDepositClassification(FileItem::EnumFileType etype) = 0;	//媒体文件的归类方式
	virtual bool GetMediaItemInFolder(int nItem,FileItem::EnumFileType etype,FileItem &item) = 0;		//返回文件夹中指定ID的ITEM
	virtual bool GetTotalMediaCountInFolder(FileItem::EnumFileType etype,int &count ) = 0;	//获取文件夹中媒体文件的数目
	virtual bool GetTotalMediaCountInAll(FileItem::EnumFileType etype,int &count ) = 0;						//获得媒体文件的总数目
	virtual bool GetMediaItemInAll(int nItem,FileItem::EnumFileType etype,FileItem &item) = 0;
	virtual void DeleteAllItem() = 0;	//
};


//class  FileListGroupInterface
//{
//public:
//
//
//	virtual void GotoPath(const wstring &path, const wstring & music_ext, const wstring & vidio_ext,const wstring & pic_ext) = 0;	//设定根目录路径，和文件拓展名
//
//	virtual EnumSort GetDepositClassification(FileItem::EnumFileType etype);	//媒体文件的归类方式
//
//	virtual FileItem* GetMediaItemInFolder(int nItem,FileItem::EnumFileType etype) = 0;		//返回文件夹中指定ID的ITEM
//
//	virtual int GetTotalMediaCountInFolder(FileItem::EnumFileType etype) = 0;	//获取文件夹中媒体文件的数目
//
//	virtual FileItem* GetMediaItemInAll(int nItem,FileItem::EnumFileType etype) = 0;
//
//	virtual int GetTotalMediaCountInAll(FileItem::EnumFileType etype ) = 0;						//获得媒体文件的总数目
//
//	virtual void DeleteAllItem() = 0;
//};