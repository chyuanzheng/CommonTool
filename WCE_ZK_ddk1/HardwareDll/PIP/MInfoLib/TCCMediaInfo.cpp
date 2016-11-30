#include "windows.h"
#include "TCCMediaInfo.h"

CTCCMediaInfo::CTCCMediaInfo()
{
	m_hFile=NULL;
	m_info.hrErrorCode=S_FALSE;
	m_info.formatInfo.format=TCC_FF_UNKNOWN;
	m_info.formatInfo.filesize=0;
	m_info.formatInfo.duration=0;
	m_info.audioCodecInfo.audioCodec=TCC_WF_UNKNOWN;
	m_info.audioCodecInfo.bitrate=0;
	m_info.audioCodecInfo.samplerate=0;
	m_info.audioCodecInfo.channel=0;
	m_info.audioCodecInfo.isVBR = FALSE;
	m_info.videoCodecInfo.videoCodec=TCC_VC_NONE;
	m_info.videoCodecInfo.width=0;
	m_info.videoCodecInfo.height=0;
	m_info.videoCodecInfo.frameDuration=0;
	m_info.videoCodecInfo.bitrate=0;
	m_info.videoCodecInfo.SARWidth=0;
	m_info.videoCodecInfo.SARHeight=0;
	m_info.tagInfo.hasSongTitle=FALSE;
	m_info.tagInfo.hasArtist=FALSE;
	m_info.tagInfo.hasAlbum=FALSE;
	m_info.tagInfo.hasTrackNumber=FALSE;
	m_info.tagInfo.hasGenre=FALSE;
	m_info.tagInfo.GenreIndex = -1; // default
	m_info.tagInfo.hasComposer=FALSE;
	m_info.tagInfo.hasYear=FALSE;
	memset(m_info.tagInfo.SongTitle,0,sizeof(m_info.tagInfo.SongTitle));
	memset(m_info.tagInfo.Artist,0,sizeof(m_info.tagInfo.Artist));
	memset(m_info.tagInfo.Album,0,sizeof(m_info.tagInfo.Album));
	memset(m_info.tagInfo.TrackNumber,0,sizeof(m_info.tagInfo.TrackNumber));
	memset(m_info.tagInfo.Genre,0,sizeof(m_info.tagInfo.Genre));
	memset(m_info.tagInfo.Composer,0,sizeof(m_info.tagInfo.Composer));
	memset(m_info.tagInfo.Year,0,sizeof(m_info.tagInfo.Year));
	m_info.photoInfo.width = 0;
	m_info.photoInfo.height = 0;
	m_info.photoInfo.colorBits = 0;
}

CTCCMediaInfo::~CTCCMediaInfo()
{
	if(m_hFile)
	{
		::CloseHandle(m_hFile);
		m_hFile=NULL;
	}
}

HRESULT CTCCMediaInfo::CheckFile(WCHAR* pWCHAR) 
{
	if(m_hFile)
	{
		::CloseHandle(m_hFile);
		m_hFile=NULL;
	}
	m_hFile=::CreateFile(pWCHAR,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,NULL);

	if(m_hFile==INVALID_HANDLE_VALUE)
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	CheckMediaType(m_hFile);
	if(m_hFile)
	{
		::CloseHandle(m_hFile);
		m_hFile=NULL;
	}
	return S_OK;
}

void CTCCMediaInfo::CheckMediaType(HANDLE hFile) 
{
	if(CheckPhotoFormat(hFile)) // JPG/GIF/BMP/PNG file check
		return;
	if(CheckAVIFormat(hFile)) // AVI/WAVE file check
		return;
	if(CheckMP4Format(hFile)) // MP4 file check
		return;
	if(CheckASFFormat(hFile)) // ASF file(WMA/WMV) check
		return;
	if(CheckOggFormat(hFile)) // Ogg file(Audio Only) check
		return;
	if(CheckMPGFormat(hFile)) // MPG file check
		return;
	if(CheckMPEGAudio(hFile)) // MP2/MP3 file check
		return;
	if(CheckFLACFormat(hFile)) // FLAC file check
		return;
	if(CheckAPEFormat(hFile)) // APE Monkey's music check
		return;
	if(CheckFLVFormat(hFile)) // Flash Video check
		return;
}


