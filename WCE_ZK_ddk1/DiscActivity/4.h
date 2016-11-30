#pragma once

struct SYS_START {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    Program;
	BYTE    Initial;
};

struct SYSMODE_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    MediaCont;
	BYTE    TvSystem;
	BYTE    Flash;
	BYTE    Initial;
	BYTE    Setup;
	BYTE	Slot;
	BYTE    LoadMode;
	BYTE    Door;
	BYTE    MechaStatus;
	BYTE    Source;
	BYTE    DiscSpin;
	BYTE    ErrorCode1;
	BYTE    ErrorCode2;
	BYTE    MediaErrorCode1;
	BYTE    MediaErrorCode2;
};

struct SET_RESP {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    SetGroupID;
	BYTE    SetSubID;
};

struct CMD_ACT_STATUS_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    ActGroupID;
	BYTE    ActSubID;
	BYTE    ActStatus;
};

struct SET_TYPE_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    ModelType;
	BYTE    Dest;
	BYTE    Mecha;
};

struct SET_MODEL_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    HiTempControl;
	BYTE    LowTempControl;
	BYTE	OSD;
	BYTE    StForm;
	BYTE    LrckFs;
	BYTE    DacQb;
	BYTE    SpdifOut;
	BYTE    Component;
	BYTE    YC;
	BYTE    Composit;
	BYTE    TextFirstChar;
	BYTE    TextSecondChar;
	BYTE    Size8Disc;
	BYTE    FullEject;
};

struct STRUCT_CDDA {
	BYTE    AFormat;
	BYTE    Text;
	BYTE    StartTrackNo;
	BYTE    EndTrackNo;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    TimeFrame;
	BYTE    STRUCT_CDDA_NULL0;
};

struct STRUCT_VCD {
	BYTE    VFormat;
	BYTE    Psd;
	BYTE    Version1;
	BYTE    Version2;
	BYTE    TrackNs;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    TimeFrame;
};

struct STRUCT_DATA {
	BYTE    FileSystemType;
	BYTE    PlayList;
	BYTE    AudioFile;
	BYTE    STRUCT_DATA_NULL0;
	WORD    FolderNs;
	WORD    FileNs;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    TimeFrame;
	BYTE    STRUCT_DATA_NULL1;
};

struct STRUCT_DVDV {
	BYTE    SRM;
	BYTE    TTMenu;
	BYTE    Parental;
	BYTE    Text;
	BYTE    Jacket;
	BYTE    TVSystem;
	BYTE    TTNs;
	BYTE    STRUCT_DVDV_NULL0;
	DWORD   EndAddress;
};

struct STRUCT_UPDATE {
	BYTE    SecterType;
	BYTE    UpdateFileNs;
	BYTE    STRUCT_UPDATE_NULL0;
	BYTE    STRUCT_UPDATE_NULL1;
};

enum
{
	MEDIATYPE_INVALID = 0,
	MEDIATYPE_CDDA = 0x01,
	MEDIATYPE_VCD = 0x02,
	MEDIATYPE_COMPRESS = 0x03,
	MEDIATYPE_DVDV = 0x11,
	MEDIATYPE_UPDATE = 0x21
};

struct DISC_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    StsType;
	BYTE    PhyMedia;
	BYTE    Update;
	BYTE    DATA;
	BYTE    VCD;
	BYTE    CDDA;
	BYTE    DVDV;
	BYTE    SetMediaType;
	BYTE    DISC_INFO_NULL0;
	BYTE    DISC_INFO_NULL1;

	struct STRUCT_CDDA CDDA_block;
	struct STRUCT_VCD VCD_block;
	struct STRUCT_DATA DATA_block;
	struct STRUCT_DVDV DVDV_block;
	struct STRUCT_UPDATE UPDATE_block;
};

struct STRUCT_FIRSTPOSITION_INFO_DVDV {
	BYTE    RootMenu;
	BYTE    DisplayMode;
	BYTE    Karaoke;
	BYTE    Parental;
	BYTE    TitleType;
	BYTE    TimeHour;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    AstNs;
	BYTE    SPstNs;
	BYTE    AgNs;
	BYTE    STRUCT_FIRSTPOSITION_INFO_NULL0;
};

struct FIRSTPOSITION_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    FIRSTPOSITION_INFO_NULL0;
	BYTE    FIRSTPOSITION_INFO_NULL1;
	WORD    FirstPositionNo;
	WORD    SecondPositionNs;

	struct STRUCT_FIRSTPOSITION_INFO_DVDV DVDV_block;
};

struct STRUCT_SECONDPOSITION_INFO_CDDA {
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    STRUCT_SECONDPOSITION_INFO_CDDA_NULL0;
	BYTE    STRUCT_SECONDPOSITION_INFO_CDDA_NULL1;
};

struct STRUCT_SECONDPOSITION_INFO_VCD {
	BYTE    TrackType;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    STRUCT_SECONDPOSITION_INFO_VCD_NULL0;
};

struct STRUCT_SECONDPOSITION_INFO_DATA {
	DWORD   FileMediaType;
	BYTE    VideoType;
	BYTE    BitType;
	BYTE    Format;
	BYTE    TimeHour;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    STRUCT_SECONDPOSITION_INFO_DATA_NULL0;
	BYTE    STRUCT_SECONDPOSITION_INFO_DATA_NULL1;
	WORD    FPS;
	BYTE    STRUCT_SECONDPOSITION_INFO_DATA_NULL2;
	BYTE    STRUCT_SECONDPOSITION_INFO_DATA_NULL3;
};

struct STRUCT_SECONDPOSITION_INFO_DVDV {
	BYTE    TimeHour;
	BYTE    TimeMinute;
	BYTE    TimeSecond;
	BYTE    STRUCT_SECONDPOSITION_INFO_DVDV_NULL0;
};

struct SECONDPOSITION_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    SECONDPOSITION_INFO_NULL0;
	BYTE    SECONDPOSITION_INFO_NULL1;
	WORD    SecondPositionNo;
	BYTE    SECONDPOSITION_INFO_NULL2;
	BYTE    SECONDPOSITION_INFO_NULL3;

	struct STRUCT_SECONDPOSITION_INFO_CDDA CDDA_block;
	struct STRUCT_SECONDPOSITION_INFO_DATA DATA_block;
	struct STRUCT_SECONDPOSITION_INFO_DVDV DVDV_block;
	struct STRUCT_SECONDPOSITION_INFO_VCD VCD_block;
};

struct STRUCT_MEDIATYPE_DVDV {
	WORD    MLangType;
	BYTE    STRUCT_MEDIATYPE_DVDV_NULL0;
	BYTE    STRUCT_MEDIATYPE_DVDV_NULL1;
};

struct DOMAIN_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    MediaType;
	BYTE    DomainType;
	BYTE    ControlType;
	BYTE    DOMAIN_INFO_NULL0;
	BYTE    DOMAIN_INFO_NULL1;
	BYTE    DOMAIN_INFO_NULL2;

	struct STRUCT_MEDIATYPE_DVDV mediatype_dvdv_block;
};

struct PLAY_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    PlayMode;
	BYTE    Speed;
	BYTE    StandbyMode;
	BYTE    StopMode;
	BYTE    RepeatMode;
	BYTE    MuteMode;
};

struct STRUCT_MEDIA_PLAY_INFO_CDDA_VCD {
	BYTE    DiscTimeMinute;
	BYTE    DiscTimeSecond;
	BYTE    TrackTimeMinute;
	BYTE    TrackTimeSecond;
	BYTE    Index;
	BYTE    RetryStatus;
	BYTE    STRUCT_MEDIA_PLAY_INFO_CDDA_VCD_NULL0;
	BYTE    STRUCT_MEDIA_PLAY_INFO_CDDA_VCD_NULL1;
};

struct STRUCT_MEDIA_PLAY_INFO_DATA {
	BYTE    FileTimeHour;
	BYTE    FileTimeMinute;
	BYTE    FileTimeSecond;
	BYTE    DATA_BitrateHi;
	BYTE    DATA_BitrateLow;
	BYTE    DATA_RetryStatus;
	BYTE    STRUCT_MEDIA_PLAY_INFO_DATA_NULL0;
	BYTE    STRUCT_MEDIA_PLAY_INFO_DATA_NULL1;
};


struct STRUCT_MEDIA_PLAY_INFO_DVDV {
	BYTE    PGCTimeHour;
	BYTE    PGCTimeMinute;
	BYTE    PGCTimeSecond;
	BYTE    PTTTimeHour;
	BYTE    PTTTimeMinute;
	BYTE    PTTTimeSecond;
	BYTE    DVDV_BitrateHi;
	BYTE    DVDV_BitrateLow;
	BYTE    DiscRestrict;
	BYTE    DVDV_RetryStatus;
	BYTE    STRUCT_MEDIA_PLAY_INFO_DVDV_NULL0;
	BYTE    STRUCT_MEDIA_PLAY_INFO_DVDV_NULL1;
};

struct MEDIA_PLAY_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    MediaType;
	BYTE    MEDIA_PLAY_INFO_NULL1;

	struct STRUCT_MEDIA_PLAY_INFO_CDDA_VCD media_play_info_CDDA_VCD;
	struct STRUCT_MEDIA_PLAY_INFO_DATA media_play_info_DATA;
	struct STRUCT_MEDIA_PLAY_INFO_DVDV media_play_info_DVDV;
};

struct AUDIO_SET_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    AudioFormat;
	BYTE    AppliMode;
	BYTE    ChannelNs;
	BYTE    StMode;
	BYTE    ChAssX;
	BYTE    ChAssY;
	BYTE    ChAssZ;
	BYTE    FsGroup2;
	BYTE    FsGroup1;
	BYTE    QbGroup2;
	BYTE    QbGroup1;
	BYTE    OutFs;
	BYTE    OutQb;
	BYTE    ChAssGroup1;
	BYTE    ChAssGroup2;
	BYTE    AUDIO_SET_INFO_NULL0;
	BYTE    AUDIO_SET_INFO_NULL1;
	BYTE    AUDIO_SET_INFO_NULL2;
};

struct STRUCT_ST_INFO_VCD {
	BYTE    StereoMode;
	BYTE    PbcSelectNs;
	BYTE    PbcOffsetNo;
	BYTE    PbcPlay;
	BYTE    PbcReturn;
	BYTE    PbcPrev;
	BYTE    PbcNext;
	BYTE    STRUCT_ST_INFO_VCD_NULL0;
};

struct STRUCT_ST_INFO_DATA {
	BYTE    AstNo;
	BYTE    STRUCT_ST_INFO_DATA_NULL0;
	BYTE    STRUCT_ST_INFO_DATA_NULL1;
	BYTE    STRUCT_ST_INFO_DATA_NULL2;
	WORD    FPS;
	BYTE    STRUCT_ST_INFO_DATA_NULL3;
	BYTE    STRUCT_ST_INFO_DATA_NULL4;
};


struct STRUCT_ST_INFO_DVDV {
	BYTE    PTL;
	BYTE    Button;
	BYTE    TempPTL;
	BYTE    AgBlock;
	BYTE    AngleNo;
	BYTE    SPDisp;
	BYTE    SPstNo;
	BYTE    STRUCT_ST_INFO_DVDV_NULL0;
	WORD    SubPLangCode;
	BYTE    AstNo;
	BYTE    STRUCT_ST_INFO_DVDV_NULL1;
	WORD    AudioLangCode;
	BYTE    ButtonNo;
	BYTE    ButtonNs;
	BYTE    ButtonOffSet;
	BYTE    STRUCT_ST_INFO_DVDV_NULL2;
	BYTE    STRUCT_ST_INFO_DVDV_NULL3;
	BYTE    STRUCT_ST_INFO_DVDV_NULL4;
};

struct ST_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    ST_INFO_NULL0;
	BYTE    ST_INFO_NULL1;

	struct STRUCT_ST_INFO_VCD st_info_VCD_block;
	struct STRUCT_ST_INFO_DATA st_info_DATA_block;  
	struct STRUCT_ST_INFO_DVDV st_info_DVDV_block;
};

struct COPY_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    ApsTriggerBit;
	BYTE    Cgms;
};

struct CCI_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    ACopyPermit;
	BYTE    ACopyNo;
	BYTE    AQuality;
	BYTE    ATrans;
	BYTE    CCI_INFO_NULL0;
	BYTE    CCI_INFO_NULL1;
};

struct UPDATE_INFO{
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    InfoNo;
	BYTE    InfoType;
	BYTE    Condition;
	BYTE    UPDATE_INFO_NULL0;
	BYTE    UPDATE_INFO_NULL1;
	BYTE    UPDATE_INFO_NULL2;
};

struct CMD_RESP {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    CmdResp;
	BYTE    RespGroupID;
	BYTE    RespSubID;
	BYTE    CMD_RESP_NULL0;
	BYTE    CMD_RESP_NULL1;
	BYTE    CMD_RESP_NULL2;
};

struct CMD_FAIL {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    CmdFail;
	BYTE    FailGroupID;
	BYTE    FailSubID;
	BYTE    CMD_FAIL_NULL0;
	BYTE    CMD_FAIL_NULL1;
	BYTE    CMD_FAIL_NULL2;
};


void parse_system_start(struct SYS_START *p_sys_start, BYTE *states);
void parse_sysmode_info(struct SYSMODE_INFO *p_sysmode_info, BYTE *states);
void parse_set_resp(struct SET_RESP *p_set_resp, BYTE *states);
void parse_cmd_act_status_info(struct CMD_ACT_STATUS_INFO *p_cmd_act_status_info, BYTE *states);
void parse_set_type_info(struct SET_TYPE_INFO *p_set_type_info, BYTE *states);
void parse_set_model_info(struct SET_MODEL_INFO *p_set_model_info, BYTE *states);
void parse_disc_info(struct DISC_INFO *p_disc_info, BYTE *states);
void parse_firstposition_info(struct FIRSTPOSITION_INFO *p_firstposition_info, BYTE *states, BYTE);
void parse_secondposition_info(struct SECONDPOSITION_INFO *p_secondposition_info, BYTE *states, BYTE SetMediaType);
void parse_domain_info(struct DOMAIN_INFO *p_domain_info, BYTE *states);
void parse_play_info(struct PLAY_INFO *p_play_info, BYTE *states);
void parse_media_play_info_CDDA_VCD(struct MEDIA_PLAY_INFO *p_media_play_info, BYTE *states, BYTE SetMediaType);
void parse_audio_set_info(struct AUDIO_SET_INFO *p_audio_set_info, BYTE *states);
void parse_st_info(struct ST_INFO *p_st_info, BYTE *states, BYTE SetMediaType);
void parse_copy_info(struct COPY_INFO *p_copy_info, BYTE *states);
void parse_cci_info(struct CCI_INFO *p_cci_info, BYTE *states);
void parse_update_info(struct UPDATE_INFO *p_update_info, BYTE *states);
void parse_cmd_resp(struct CMD_RESP *p_cmd_resp, BYTE *states);
void parse_cmd_fail(struct CMD_FAIL *p_cmd_fail, BYTE *states);
