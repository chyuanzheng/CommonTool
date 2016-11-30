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
	typedef enum EnumSortClassification 	//��Ź��෽ʽ
	{
		DEPOSIT_BY_FOLDER = 0,		//���ļ��й���
		DEPOSIT_BY_ALL,
		DEPOSIT_BY_NONE	//�޹���
	}EnumSort;

	virtual void GotoPath(const wstring &path, const wstring & music_ext, const wstring & vidio_ext,const wstring & pic_ext) = 0;	//�趨��Ŀ¼·�������ļ���չ��
	virtual EnumSort GetDepositClassification(FileItem::EnumFileType etype) = 0;	//ý���ļ��Ĺ��෽ʽ
	virtual bool GetMediaItemInFolder(int nItem,FileItem::EnumFileType etype,FileItem &item) = 0;		//�����ļ�����ָ��ID��ITEM
	virtual bool GetTotalMediaCountInFolder(FileItem::EnumFileType etype,int &count ) = 0;	//��ȡ�ļ�����ý���ļ�����Ŀ
	virtual bool GetTotalMediaCountInAll(FileItem::EnumFileType etype,int &count ) = 0;						//���ý���ļ�������Ŀ
	virtual bool GetMediaItemInAll(int nItem,FileItem::EnumFileType etype,FileItem &item) = 0;
	virtual void DeleteAllItem() = 0;	//
};


//class  FileListGroupInterface
//{
//public:
//
//
//	virtual void GotoPath(const wstring &path, const wstring & music_ext, const wstring & vidio_ext,const wstring & pic_ext) = 0;	//�趨��Ŀ¼·�������ļ���չ��
//
//	virtual EnumSort GetDepositClassification(FileItem::EnumFileType etype);	//ý���ļ��Ĺ��෽ʽ
//
//	virtual FileItem* GetMediaItemInFolder(int nItem,FileItem::EnumFileType etype) = 0;		//�����ļ�����ָ��ID��ITEM
//
//	virtual int GetTotalMediaCountInFolder(FileItem::EnumFileType etype) = 0;	//��ȡ�ļ�����ý���ļ�����Ŀ
//
//	virtual FileItem* GetMediaItemInAll(int nItem,FileItem::EnumFileType etype) = 0;
//
//	virtual int GetTotalMediaCountInAll(FileItem::EnumFileType etype ) = 0;						//���ý���ļ�������Ŀ
//
//	virtual void DeleteAllItem() = 0;
//};