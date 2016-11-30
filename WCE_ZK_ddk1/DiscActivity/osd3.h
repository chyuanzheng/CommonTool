#pragma once


/* ------------------------------------- */
/* Name: parse_inquiry_info()
 * Source: 3.1.1 [0C03]
 * Status Description: 
 *      Notification of system-specific information. 
 *      This is a response status to CALL_INQUIRY_INFO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */

/* PageCode : MechaType */
/*
PeripheralDeviceType ( Param1.  bit0 to 3 )  :  Type of Drive mechanism 
    2h : DVD single mechanism 
 
InSw ( Param2.    bit0 )    : Active setting of Disc IN switch 
    0b : Low is active 
 
StockPosition ( Param2.    bit4 to 6 )    : Disc storing type of Drive mechanism 
    001b  : Slot type 
 
MaxRate1 ( Param3.    All )    : Max value of transfer clock (integer number digits)   
*Indicate Max value of transfer clock in combination with MaxRate2 
    09 to 77h : Max value of transfer clock  integer number digits [ 9 to 119 Kbps ] 
      * Clock value    =    MaxRate1 x 1Kbps + MaxTare2 x 0.1Kbps 
 
MaxRate2 ( Param4.    bit0 to 3 )    : Max value of transfer clock (decimal number digits) 
*Indicate Max value of transfer clock in combination with MaxRate1 
    0 to 9h : Max value of transfer clock    decimal number digits [ 0 to 0.9 Kbps ] 
      * Clock value    =    MaxRate1 x 1Kbps + MaxTare2 x 0.1Kbps 
 
CDDA ( Param5.    bit0 )    : Ability for CDDA playing 
    0b : Unable to play CDDA 
    1b : Able to pay CDDA 
 
MP3 ( Param5.    bit1 )    : Ability for MP3 playing 
    0b : Unable to play MP3 
    1b : Able to play MP3 
 
WMA ( Param5.    bit2 )    : Ability for WMA playing 
    0b : Unable to play WMA 
    1b : Able to play WMA 
 
M4AAC ( Param5.    bit3 )    : Ability for MPEG4-AAC playing 
    0b : Unable to play MPEG4-AAC 
    1b : Able to play MPEG4-AAC 

WAV ( Param5.    bit4 )    : Ability for WAV playing 
    0b : Unable to play WAV     
    1b : Able to play WAV     
 
MP3Pro ( Param5.    bit5 )    : Ability for MP3Pro playing 
    0b : Unable to play MP3Pro     
    1b : Able to play MP3Pro     
 
M2AAC ( Param5.    bit6 )    : Ability for MPEG2-AAC playing 
    0b : Unable to play MPEG2-AAC     
    1b : Able to play MPEG2-AAC     
 
VCD ( Param7.    bit0 )    : Ability for VCD playing 
    0b : Unable to play VCD     
    1b : Able to play VCD     
 
DivX ( Param7.    bit1 )    : Ability for DivX playing 
    0b : Unable to play DivX     
    1b : Able to play DivX     
 
ASF ( Param7.    bit2 )    : Ability for ASF playing 
    0b : Unable to play ASF     
    1b : Able to play ASF     
 
JPEG ( Param7.    bit7 )    : Ability for JPEG playing 
    0b : Unable to play JPEG     
    1b : Able to play JPEG     
 
DVDV ( Param9.    bit0 )    : Ability for DVD-Video playing 
    0b : Unable to play DVD-Video     
    1b : Able to play DVD-Video     
 
DVDA ( Param9.    bit1 )  : Ability for DVD-Audio playing 
    0b : Unable to play DVD-Audio     
    1b : Able to play DVD-Audio     
 
DVDVR ( Param9.    bit2 )    : Ability for DVD-VR playing 
    0b : Unable to play DVD-VR     
    1b : Able to play DVD-VR     
 
RegionCode ( Param10.    All )    : Region code setting value 
    01 to 06h : Region code [ 1 to 6 ] 
*/
struct STRUCT_PAGECODE_MECHATYPE {
    BYTE    PeripheralDeviceType;
    BYTE    StockPosition;
    BYTE    InSw;
    BYTE    MaxRate1;
    BYTE    MaxRate2;
    BYTE    M2AAC;
    BYTE    MP3Pro;
    BYTE    WAV;
    BYTE    M4AAC;
    BYTE    WMA;
    BYTE    MP3;
    BYTE    CDDA;
    BYTE    JPEG;
    BYTE    ASF;
    BYTE    DivX;
    BYTE    VCD;
    BYTE    DVDVR;
    BYTE    DVDA;
    BYTE    DVDV;
    BYTE    RegionCode;
};

/* PageCode : SoftVersion */
/*
ControlSoftVersion1 ( Param1.    All )    : Version number of Control software ( Integer number digits ) 
ControlSoftVersion2 ( Param2.    All )    : Version number of Control software ( 1st decimal digit ) 
ControlSoftVersion3 ( Param3.    All )    : Version number of Control software ( 2nd decimal digit ) 
ControlSoftVersion4 ( Param4.    All )    : Version number of Control software ( 3rd decimal digit ) 
ControlSoftVersion5 ( Param5.    All )    : Version number of Control software ( 4th decimal digit ) 
    00 to FFh : Each version number ( ASCII code )   
        * Indicate version number in combination with ControlSoftVersion1 to 5. 
 
MechaSoftVersion1 ( Param6.    All )  : Version number of Control software for Mech-microprocessor   
        ( Integer number digits ) 
MechaSoftVersion2 ( Param7.    All )  : Version number of Control software for Mech-microprocessor ( 1st decimal digit ) 
MechaSoftVersion3 ( Param8.    All )  : Version number of Control software for Mech-microprocessor ( 2nd decimal digit ) 
MechaSoftVersion4 ( Param9.    All )  : Version number of Control software for Mech-microprocessor ( 3rd decimal digit ) 
MechaSoftVersion5 ( Param10.    All )  : Version number of Control software for Mech-microprocessor ( 4th decimal digit ) 
    00 to FFh : Each version number ( ASCII code )   
        * Indicate version number in combination with MechaSoftVersion1 to 5. 
        * If the Mech-microprocessor is not installed, use software version of control software. 
*/

struct STRUCT_PAGECODE_SOFTVERSION {
    BYTE    ControlSoftVersion1;
    BYTE    ControlSoftVersion2;
    BYTE    ControlSoftVersion3;
    BYTE    ControlSoftVersion4;
    BYTE    ControlSoftVersion5;
    BYTE    MechaSoftVersion1;
    BYTE    MechaSoftVersion2;
    BYTE    MechaSoftVersion3;
    BYTE    MechaSoftVersion4;
    BYTE    MechaSoftVersion5;
    BYTE    STRUCT_PAGECODE_SOFTVERSION_NULL0;
    BYTE    STRUCT_PAGECODE_SOFTVERSION_NULL1;
};

/* PageCode : ProductFirst */
/*
ProductName ( Param1 to N.    All )    : Product name 
Any : Product name ( ASCII code )   
              * Param1 is set as the fist character and recorded the character of product name. 
       * The max character count is 12. 
       * After the 13th character is obtained by [PageCode = ProductSecond] status. 
              * The identification code of end recording name is [FFh] and, "FFh" is recorded for all unnecessary (blank) counts. 
*/

struct STRUCT_PAGECODE_PRODUCTFIRST {
    char    ProductName[12];
};

/* PageCode : ProductSecond */
/*
ProductName ( Param1 to N.    All )    : Product name ( after 13th character )   
Any : Product name ( ASCII code )   
  * Param1 is set as the fist character and recorded from the 13th character of product name. 
  * The max character count of name is 24 in combination with [PageCode = ProductFirst]. 
  * The identification code of end recording name is [FFh] and, "FFh" is recorded for all unnecessary (blank) counts. 
*/

struct STRUCT_PAGECODE_PRODUCTSECOND {
    char    ProductName[12];
};

/* PageCode : VenderFirst */
/* 
VenderName ( Param1 to N.    All )    : Vender name 
Any : Product name ( ASCII code )   
              * Param1 is set as the fist character and recorded the character of vender name. 
       * The max character count is 12. 
       * After the 13th character is obtained by [PageCode = VenderSecond] status. 
              * The identification code of end recording name is [FFh] and, "FFh" is recorded for all unnecessary (blank) counts. 
*/ 

struct STRUCT_PAGECODE_VENDERFIRST {
    char    VenderName[12];
};

/* PageCode : VenderSecond */
/* 
VenderName ( Param1 to N.    All )    : Vender name ( after 13th character )   
Any : Product name ( ASCII code )   
  * Param1 is set as the fist character and recorded from the 13th character of product name. 
  * The max character count of name is 24 in combination with [PageCode = VenderFirst]. 
  * The identification code of end recording name is [FFh] and, "FFh" is recorded for all unnecessary (blank) counts.
*/

struct STRUCT_PAGECODE_VENDERSECOND {
    char    VenderName[12];
};

/*
PageCode ( Param0.    All )    : Information type 
    00h : Type of Mechanism ( MechaType )   
    01h : Information of revision version on product ( SoftVersion )   
    02h : Product identification information ( First page )    ( ProductFirst )   
    03h : Product identification information ( Second page )    ( ProductSecond )   
    04h : Product vender identification information ( First page ) ( VenderFirst )   
    05h : Product vender identification information ( Second page ) ( VenderSecond )   
*/ 

struct INQUIRY_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    PageCode;
    BYTE    INQUIRY_INFO_NULL0;

    struct STRUCT_PAGECODE_MECHATYPE pagecode_mechatype_block;
    struct STRUCT_PAGECODE_SOFTVERSION pagecode_softversion_block;
    struct STRUCT_PAGECODE_PRODUCTFIRST pagecode_productfirst_block;
    struct STRUCT_PAGECODE_PRODUCTSECOND pagecode_productsecond_block;
    struct STRUCT_PAGECODE_VENDERFIRST pagecode_venderfirst;
    struct STRUCT_PAGECODE_VENDERSECOND pagecode_vendersecond;
};
void parse_inquiry_info(struct INQUIRY_INFO *p_inquiry_info, BYTE *states);
void parse_temp_info(struct TEMP_INFO *p_temp_info, BYTE *states);
void parse_testtone_info(struct TESTTONE_INFO *p_testtone_info, BYTE *states);
void parse_toc1_info(struct TOC1_INFO *p_toc1_info, BYTE *states);
void parse_toc2_info(struct TOC2_INFO *p_toc2_info, BYTE *states);
void parse_folder_file_no_info(struct FOLDER_FILE_NO_INFO *p_folder_file_no_info, BYTE *states);
void parse_text_code_info(struct TEXT_CODE_INFO *p_text_code_info, BYTE *states);

/* ------------------------------------- */
/* Name: parse_text_info()
* Source: 3.3.2 [0D02]
* Status Description: 
*      Notification of text data for replay contents. 
*      This is a response status to CALL_TEXT_INFO command ( refer to the 
* description of this command ). 
*/

/* Parameter */

/* CDDA : TextType = 8Fh */
/* 
PageNo ( Param0.    All )    : Divided page number of target information 
01 to 08h : Page number [ 1 to 8 ] 
* 1 language information is allocated per a page. ( Max 8 languages ) 

LastPageNo ( Param1.    All )    : Last page number 
01 to 08h : Page number [ 1 to 8 ] 

BlockNo ( Param6( X-1 )ï¼?.  All )  : Identification number of target information 
00 to 07h : Block number of CD TEXT [ 0 to 7 ] 
* 1 Block is composed of the information of 1 language.    ( It is equivalent to 1 page ) 
* 1 block is composed of [BlockNo][CharCode][AlbumSize][PerformerSize][SelectSize][LangCode]. 
* Block number is counted start from 0 in the recorded order.   
* The combination of the kind of language and the information set number is different according to the source. 
CharCode ( Param6( X-1 )ï¼?.    All )    : Text character code of target information 
00h : ISO 8859-1 
01h : ISO/IEC 646 
80h : SHIFT JIS Kanji and JIS Katakana 
81h : Korean character 
82h : Mandarin character 
Any : Other code than the above 
* There is a possibility that the codes other than the above-mentioned exist because it just replies the code recorded on the Disc. 


AlbumSize ( Param6( X-1 )ï¼?.    All )    : Text size of Album title / Song title of target information 
00 to FFh : [ 0 to 254 packs ] 
* 1 pack = 12 byte 

PerformerSize ( Param6( X-1 )ï¼?.    All )    : Text size of Artist name / Player name of target information 
00 to FFh : [ 0 to 254 packs ] 
* 1 pack = 12 byte 

SelectSize ( Param6( X-1 )ï¼?.    All )    : Text size of specified information of target information 
* The information is specified by â€œSelectInfoâ€?of CALL_TEXT_INFO command. 
00 to FFh : [ 0 to 254 packs ] 
* 1 pack = 12 byte 

LangCode ( Param0.  All )  :  Text language code of target information 
08h : German 
09h : English 
0Ah : Spanish 
0Fh : French 
69h : Japanese 
Any : Other code than the above 
* There is a possibility that the code other than the above-mentioned exist because it just replies the code recorded on the Disc. 
*/ 

struct STRUCT_TEXT_INFO_0X8FH {
	BYTE    PageNo;
	BYTE    LastPageNo;
	BYTE    BlockNo1;
	BYTE    CharCode1;
	BYTE    AlbumSize1;
	BYTE    performerSize1;
	BYTE    SelectSize1;
	BYTE    LangCode1;
};


/* CDDA : TextTypeâ‰?Fh */
/*
LangCode ( Param0.    All )    : Text language code 
08h : German 
09h : English 
0Ah : Spanish 
0Fh : French 
69h : Japanese 
Any : Other code than the above 
* There is a possibility that the codes other than the above-mentioned exist because it just replies the code recorded on the Disc. 

CharCode ( Param1.    All )    : Text character code 
00h : ISO 8859-1 
01h : ISO/IEC 646 
80h : SHIFT JIS Kanji and JIS Katakana 
81h : Korean character 
82h : Mandarin character 
Any : Other code than the above 
* There is a possibility that the code other than the above-mentioned exist because it just replies the code recorded on the Disc. 

PageNo ( Param2.    All )    : Divided page number of target information 
01to FFh : Page number [ 1to 255 ] 
* 8 bytes text data is allocated per a page.   

LastPageNo ( Param3.    All )    : Last Page number 
01to FFh : Page number [ 1to 255 ] 

TextData ( Param4 to N.    All )    : Text data 
Any : Text data 
* The Max size of total text data information that can be transmitted is 2040 bytes. 
*/

struct STRUCT_TEXT_INFO_NOT_0X8FH {
	BYTE    LangCode;
	BYTE    CharCode;
	BYTE    PageNo;
	BYTE    LastPageNo;
	char    TextData[8];
};

/*

*/ 
/* ------------------------------------- */
/* Name: parse_folder_info()
 * Source: 3.4.1 [0E05]
 * Status Description:  
 *      Notification of information about recorded Folder on identification Disc. 
 *      This is a response status to CALL_FOLDER_INFO command ( refer to the 
 * description of this command ) and, the target information folder is specified 
 * by the command. 
 */

/* Parameter */

/* Notification of information about folder composition when the CALL_FOLDER_INFO specified [InfoType = 0b ] (Composition) .  */
/*
FileNs( Param0ï½?.    All ) : Number of files in the Folder 
    0000 to 1000h    : Number of files [ 0 to 4096 ] 
 
UpperFolderNo( Param2ï½?.    All ) : Upper Folder number 
    0001 to 00FFh    : Folder number [ 1 to 255 ] 
        * 0001h is indicated as root. 
        * FFFFh means the corresponding folder in not exist 
 
LowerFolderNs( Param4ï½?.    All ) : Number of Lower Folder   
    0000 to 0100h    : Number of Folders [ 0 to 256 ] 
*/

struct STRUCT_FOLDER_INFO_FOLDER {
    WORD    FileNs;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL0;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL1;
    WORD    UpperFolderNo;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL2;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL3;
    WORD    LowerFolderNs;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL4;
    BYTE    STRUCT_FOLDER_INFO_FOLDER_NULL5;
};

/* Notification of information about Lower Folder when the CALL_FOLDER_INFO specified [InfoType = 1b ] (Lower) . */
/*
* N = 1 to 5 
 
PageNo( Param0.    All ) : Divided page number of target information 
    01to 33h : Page number [ 1to 51 ] 
        * 5 lower folder information are allocated by ascending order for each page. 
 
LastPageNo( Param1.    All ) : Last page number   
    01to 33h : Page number [ 1to 51 ] 
 
FolderNoX( Param2 to N x 2 + 1.    All ) : Lower folder number 
    0000h    : There is no lower folder 
    0002ï½?100h  : Folder number [ 2 to 256 ] 
        * Lower folder number is notified in ascending order.
*/ 

struct STRUCT_FOLDER_INFO_LOWER_FOLDER {
    BYTE    PageNo;
    BYTE    LastPageNo;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL0;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL1;
    WORD    FolderNo1;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL2;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL3;
    WORD    FolderNo2;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL4;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL5;
    WORD    FolderNo3;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL6;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL7;
    WORD    FolderNo4;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL8;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL9;
    WORD    FolderNo5;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL10;
    BYTE    STRUCT_FOLDER_INFO_LOWER_FOLDER_NULL11;
};

struct FOLDER_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    FOLDER_INFO_NULL0;
    BYTE    FOLDER_INFO_NULL1;

    struct STRUCT_FOLDER_INFO_FOLDER folder_info_folder_block;
    struct STRUCT_FOLDER_INFO_LOWER_FOLDER folder_info_lower_folder_block;
};

struct TEXT_INFO {
	BYTE    GroupID;
	BYTE    SubID;
	BYTE    TEXT_INFO_NULL0;
	BYTE    TEXT_INFO_NULL1;

	struct STRUCT_TEXT_INFO_0X8FH text_info_0x8fh;
	struct STRUCT_TEXT_INFO_NOT_0X8FH text_info_not_0x8fh;
};

typedef struct _FILENAME_INFO{

	BYTE	GroupID;
	BYTE	SubID;
	BYTE	PageNo;
	BYTE	LastPageNo;
	BYTE	FileType;
	BYTE	FILENAME[10];
}FILENAME_INFO;
void parse_text_info(struct TEXT_INFO *p_text_info, BYTE *states, BYTE TextType);
void parse_file_name_info(FILENAME_INFO *p_filename_info, BYTE *states);
void parse_disc_name_info(struct DISC_NAME_INFO *p_disc_name_info, BYTE *states);
void parse_folder_info(struct FOLDER_INFO *p_folder_info, BYTE *states, BYTE InfoType);
void parse_file_type_info(struct FILE_TYPE_INFO *p_file_type_info, BYTE *states);
void parse_secondposition_ns_info(struct SECONDPOSITION_NS_INFO *p_secondposition_ns_info, BYTE *states);
void parse_stream_attribute_info(struct STREAM_ATTRIBUTE_INFO *p_stream_attribute_info, BYTE *states, BYTE StType);
void parse_set3v_back_video_info(struct SET3V_VACK_VIDEO_INFO *p_set3v_back_video_info, BYTE *states);
void parse_set3v_video_adjust_info(struct SET3V_VIDEO_ADJUST_INFO *p_set3v_video_adjust_info, BYTE *states);
void parse_set3a_drc_info(struct SET3A_DRC_INFO *p_set3a_drc_info, BYTE *states);
void parse_set3a_a_spk_info(struct SET3A_A_SPK_INFO *p_set3a_a_spk_info, BYTE *states);
void parse_set3a_a_delay_info(struct SET3A_A_DELAY_INFO *p_set3a_a_delay_info, BYTE *states);
void parse_set3a_spk_lvl_info(struct SET3A_SPK_LVL_INFO *p_set3a_spk_lvl_info, BYTE *states);
void parse_set3a_a_mute_info(struct SET3A_A_MUTE_INFO *p_set3a_a_mute_info, BYTE *states);
void parse_set3a_dm_mode_info(struct SET3A_DM_MODE_INFO *p_set3a_dm_mode_info, BYTE *states);
void parse_set3a_dpl2_rf_info(struct SET3A_DPL2_RF_INFO *p_set3a_dpl2_rf_info, BYTE *states);
void parse_set3a_phantom_info(struct SET3A_PHANTOM_INFO *p_set3a_phantom_info, BYTE *states);
void parse_set3a_bassmng_info(struct SET3A_BASSMNG_INFO *p_set3a_bassmng_info, BYTE *states);
void parse_set2s_scan_time_info(struct SET2S_SCAN_TIME_INFO *p_set2s_scan_time_info, BYTE *states);
void parse_set2s_tv_aspect_info(struct SET2S_TV_ASPECT_INFO *p_set2s_tv_aspect_info, BYTE *states);
void parse_set2s_dau_out_info(struct SET2S_DAU_OUT_INFO *p_set2s_dau_out_info, BYTE *states);
void parse_set2a_play_priority(struct SET2A_PLAY_PRIORITY_INFO *p_set2a_play_priority_info, BYTE *states);
void parse_set2a_lang_info(struct SET2A_LANG_INFO *p_set2a_lang_info, BYTE *states);
void parse_set2a_country_code_info(struct SET2A_COUNTRY_CODE_INFO *p_set2a_country_code_info, BYTE *states);
void parse_set2a_ptl_lvl_info(struct SET2A_PTL_LVL_INFO *p_set2a_ptl_lvl_info, BYTE *states);
void parse_set2a_pause_mode_info(struct SET2A_PAUSE_MODE_INFO *p_set2a_pause_mode_info, BYTE *states);
