
#ifndef	_TCCMEDIAINFO_H_
#define	_TCCMEDIAINFO_H_

const char VERSION[] = "TCCMInfoLib V100120"; 

/////////// Audio Codec  ////////////////
#define TCC_WF_UNKNOWN 0x0000
#define TCC_WF_PCM 0x0001
#define TCC_WF_ADPCM_MS 0x0002
#define TCC_WF_IEEE_FLOAT 0x0003
#define TCC_WF_ALAW  0x0006
#define TCC_WF_MULAW 0x0007
#define TCC_WF_DTS_MS 0x0008
#define TCC_WF_WMAS 0x000A // WMA 9 Speech
#define TCC_WF_IMA_ADPCM 0x0011
#define TCC_WF_GSM610 0x0031
#define TCC_WF_MSNAUDIO 0x0032
#define TCC_WF_G726 0x0045
#define TCC_WF_MP2	0x0050 
#define TCC_WF_MP3 0x0055
#define TCC_WF_AAC 0x00FF
#define TCC_WF_WMA1 0x0160 // WMA version 1
#define TCC_WF_WMA2 0x0161 // WMA version 2
#define TCC_WF_WMAP 0x0162 // WMA 9 Professional
#define TCC_WF_WMAL 0x0163 // WMA 9 Lossless
#define TCC_WF_AC3	0x2000 // Dolby AC-3
#define TCC_WF_DTS 0x2001 
#define TCC_WF_FFMPEG_AAC 0x706D
#define TCC_WF_VORBIS 0x566F // Vorbis
#define TCC_WF_FLAC 0xF1AC
#define TCC_WF_APE 0x4150 // APE Monkey's music


/////////// Video Codec  ////////////////
#define TCC_VC_NONE 0x00000000
//// MPG1 ////
#define TCC_VC_MPG1 0x4D504731
//// MPG2 ////
#define TCC_VC_MPG2 0x4D504732
//// MPG4 ////
#define TCC_VC_DIV4 0x44495634
#define TCC_VC_DIV5 0x44495635
#define TCC_VC_DIV6 0x44495636
#define TCC_VC_DIVX 0x44495658
#define TCC_VC_DX50 0x44583530
#define TCC_VC_MP42 0x4D503432
#define TCC_VC_MP43 0x4D503433
#define TCC_VC_MP4S 0x4D503453
#define TCC_VC_MP4V 0x4D503456
#define TCC_VC_MPG4 0x4D504734
#define TCC_VC_XVID 0x58564944
#define TCC_VC_div4 0x64697634
#define TCC_VC_div5 0x64697635
#define TCC_VC_div6 0x64697636
#define TCC_VC_divx 0x64697678
#define TCC_VC_dx50 0x64783530
#define TCC_VC_mp42 0x6D703432
#define TCC_VC_mp43 0x6D703433
#define TCC_VC_mp4s 0x6D703473
#define TCC_VC_mp4v 0x6D703476
#define TCC_VC_mpg4 0x6D706734
#define TCC_VC_xvid 0x78766964
//// H264 ////
#define TCC_VC_H264 0x48323634
#define TCC_VC_AVC1 0x41564331
#define TCC_VC_X264 0x58323634
#define TCC_VC_h264 0x68323634
#define TCC_VC_avc1 0x61766331
#define TCC_VC_x264 0x78323634
//// WMV  ////
#define TCC_VC_WMV7 0x574D5631 // WMV7
#define TCC_VC_WMV8 0x574D5632 // WMV8 
#define TCC_VC_WMV9 0x574D5633 // WMV9
#define TCC_VC_wmv7 0x776D7631 // WMV7
#define TCC_VC_wmv8 0x776D7632 // WMV8 
#define TCC_VC_wmv9 0x776D7633 // WMV9
//// H263 ////
#define TCC_VC_H263 0x48323633 // H263
#define TCC_VC_h263 0x68323633 // H263
#define TCC_VC_S263 0x53323633 // Sorenson H263 (Spark)
#define TCC_VC_s263 0x73323633 // Sorenson H263 (Spark)
//// UNKNOWN ////
#define TCC_VC_UNKNOWN 0xFFFFFFFF


/////////// File Format ////////////////////
#define TCC_FF_UNKNOWN 0x0000
#define TCC_FF_AVI 0x0001
#define TCC_FF_MP4 0x0002
#define TCC_FF_ASF 0x0003 // WMV, WMA
#define TCC_FF_OGG 0x0004
#define TCC_FF_ADTS 0x0005 // MP2, MP3, AAC
#define TCC_FF_WAVE 0x0006
#define TCC_FF_MPG1 0x0007
#define TCC_FF_MPG2 0x0008
#define TCC_FF_FLAC 0x0009
#define TCC_FF_APE 0x000A // APE Monkey's music
#define TCC_FF_FLV 0x000B // Flash Video

#define TCC_FF_PHOTO 0x1000
#define TCC_FF_JPG 0x1001
#define TCC_FF_GIF 0x1002
#define TCC_FF_BMP 0x1003
#define TCC_FF_PNG 0x1004

#define MAX_TAG_SIZE 128

typedef	struct _TCCFormatInfo{
	unsigned int format;
	unsigned __int64 filesize;
	unsigned int duration; // sec
}TCCFormatInfo;

typedef	struct _TCCAudioInfo {
	unsigned int audioCodec;
	unsigned int bitrate;
	unsigned int samplerate;
	unsigned int channel;
	BOOL isVBR; // is valid when MP3,MP2
}TCCAudioInfo;

typedef	struct _TCCVideoInfo {
	unsigned int videoCodec;
	unsigned int width;
	unsigned int height;
	unsigned int frameDuration; // micro sec
	unsigned int bitrate;
	unsigned int SARWidth; // sample aspect ratio width
	unsigned int SARHeight; // sample aspect ratio height
}TCCVideoInfo;

typedef	struct _TCCTagInfo {
	BOOL hasSongTitle;
	BOOL hasArtist;
	BOOL hasAlbum;
	BOOL hasTrackNumber;
	BOOL hasGenre;
	WCHAR SongTitle[MAX_TAG_SIZE];
	WCHAR Artist[MAX_TAG_SIZE];
	WCHAR Album[MAX_TAG_SIZE];
	WCHAR TrackNumber[MAX_TAG_SIZE];
	WCHAR Genre[MAX_TAG_SIZE];  // only valid when GenreIndex = -1
	int GenreIndex;
	BOOL hasComposer;
	BOOL hasYear;
	WCHAR Composer[MAX_TAG_SIZE];
	WCHAR Year[MAX_TAG_SIZE];
}TCCTagInfo;

typedef	struct _TCCPhotoInfo {
	unsigned int width;
	unsigned int height;
	unsigned int colorBits; 
}TCCPhotoInfo;

typedef	struct _TCCMediaInfo {
	HRESULT hrErrorCode;
	TCCFormatInfo formatInfo;
	TCCAudioInfo audioCodecInfo;
	TCCVideoInfo videoCodecInfo;
	TCCTagInfo tagInfo;
	TCCPhotoInfo photoInfo;
}TCCMediaInfo;


class CE_HardwareDll_API CTCCMediaInfo
{
public:
	CTCCMediaInfo();
	virtual ~CTCCMediaInfo();
	virtual HRESULT CheckFile(WCHAR* pWCHAR);
	virtual void CheckMediaType(HANDLE hFile);
	TCCMediaInfo m_info;
protected:
	HANDLE m_hFile;
	BOOL CheckMPEGAudio(HANDLE hFile);
	BOOL CheckAVIFormat(HANDLE hFile);
	BOOL CheckMP4Format(HANDLE hFile);
	BOOL CheckASFFormat(HANDLE hFile);
	BOOL CheckOggFormat(HANDLE hFile);
	BOOL CheckMPGFormat(HANDLE hFile);
	BOOL CheckFLACFormat(HANDLE hFile);
	BOOL CheckAPEFormat(HANDLE hFile);
	BOOL CheckPhotoFormat(HANDLE hFile);
	BOOL CheckFLVFormat(HANDLE hFile);
};

#endif
