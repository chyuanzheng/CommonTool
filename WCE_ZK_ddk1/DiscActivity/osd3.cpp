#include "stdafx.h"
#include "osd3.h"
#define BYTE unsigned char
#define WORD unsigned short int
#define DWORD unsigned int



void parse_inquiry_info(struct INQUIRY_INFO *p_inquiry_info, BYTE *states)
{
    p_inquiry_info->GroupID = states[0];
    p_inquiry_info->SubID = states[1];
    p_inquiry_info->PageCode = states[2];
    
    /* PageCode : MechaType */
    if (p_inquiry_info->PageCode == 0x00) {
        p_inquiry_info->pagecode_mechatype_block.PeripheralDeviceType = states[3];
        p_inquiry_info->pagecode_mechatype_block.StockPosition = (states[4] & 0x70) >> 4;
        p_inquiry_info->pagecode_mechatype_block.InSw = states[4] & 0x01;
        p_inquiry_info->pagecode_mechatype_block.MaxRate1 = states[5];
        p_inquiry_info->pagecode_mechatype_block.MaxRate2 = states[6];
        p_inquiry_info->pagecode_mechatype_block.M2AAC = (states[7] & 0x40) >> 6;
        p_inquiry_info->pagecode_mechatype_block.MP3Pro = (states[7] & 0x20) >> 5;
        p_inquiry_info->pagecode_mechatype_block.WAV = (states[7] & 0x10) >> 4;
        p_inquiry_info->pagecode_mechatype_block.M4AAC = (states[7] & 0x08) >> 3;
        p_inquiry_info->pagecode_mechatype_block.WMA = (states[7] & 0x04) >> 2;
        p_inquiry_info->pagecode_mechatype_block.MP3 = (states[7] & 0x02) >> 1;
        p_inquiry_info->pagecode_mechatype_block.CDDA = states[7] & 0x01;
        p_inquiry_info->pagecode_mechatype_block.JPEG = (states[9] & 0x80) >> 7;
        p_inquiry_info->pagecode_mechatype_block.ASF = (states[9] & 0x04) >> 2;
        p_inquiry_info->pagecode_mechatype_block.DivX = (states[9] & 0x02) >> 1;
        p_inquiry_info->pagecode_mechatype_block.VCD = states[9] & 0x01;
        p_inquiry_info->pagecode_mechatype_block.DVDVR = (states[11] & 0x04) >> 2;
        p_inquiry_info->pagecode_mechatype_block.DVDA = (states[11] & 0x02) >> 1;
        p_inquiry_info->pagecode_mechatype_block.DVDVR = states[11] & 0x01;
        p_inquiry_info->pagecode_mechatype_block.RegionCode = states[12];
    }

    /* PageCode : SoftVersion */
    if (p_inquiry_info->PageCode == 0x01) {
        p_inquiry_info->pagecode_softversion_block.ControlSoftVersion1 = states[3];
        p_inquiry_info->pagecode_softversion_block.ControlSoftVersion2 = states[4];
        p_inquiry_info->pagecode_softversion_block.ControlSoftVersion3 = states[5];
        p_inquiry_info->pagecode_softversion_block.ControlSoftVersion4 = states[6];
        p_inquiry_info->pagecode_softversion_block.ControlSoftVersion5 = states[7];
        p_inquiry_info->pagecode_softversion_block.MechaSoftVersion1 = states[8];
        p_inquiry_info->pagecode_softversion_block.MechaSoftVersion2 = states[9];
        p_inquiry_info->pagecode_softversion_block.MechaSoftVersion3 = states[10];
        p_inquiry_info->pagecode_softversion_block.MechaSoftVersion4 = states[11];
        p_inquiry_info->pagecode_softversion_block.MechaSoftVersion5 = states[12];
    }

    /* PageCode : ProductFirst */
    if (p_inquiry_info->PageCode == 0x02) {
        for (int i=0; i<=11; ++i)
            p_inquiry_info->pagecode_productfirst_block.ProductName[i+3] = states[i+3];
    }

    /* PageCode : ProductSecond */
    if (p_inquiry_info->PageCode == 0x03) {
        for (int i=0; i<=11; ++i)
            p_inquiry_info->pagecode_productsecond_block.ProductName[i+3] = states[i+3];
    }

    /* PageCode : VenderFirst */
    if (p_inquiry_info->PageCode = 0x04) {
         for (int i=0; i<=11; ++i)
            p_inquiry_info->pagecode_venderfirst.VenderName[i+3] = states[i+3];
    }

    /* PageCode : VenderSecond */
    if (p_inquiry_info->PageCode = 0x05) {
         for (int i=0; i<=11; ++i)
            p_inquiry_info->pagecode_vendersecond.VenderName[i+3] = states[i+3];
    }
}

/* ------------------------------------- */
/* Name: parse_temp_info()
 * Source: 3.1.2 [0C0D]
 * Status Description: 
 *      Notification of temperature information of the mechanism that this 
 * system installed. 
 *      This is a response status to CALL_TEMP_INFO command ( refer to the 
 * description of this command ) and, this is voluntarily notified at the state 
 * transition. 
 */

/* Parameter */
/*
Temperature ( Param0.    bit0 to 6 )    : Temperature information 
    00 to 7Fh : AD value 
        * For AD value, refer to the specification of hardware 
 
HiLow ( Param0.    bit7 )    : Temperature range information 
    0b : LowTemp information 
    1b : HiTemp information
*/ 

struct TEMP_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    HiLow;
    BYTE    Temperature;
};

void parse_temp_info(struct TEMP_INFO *p_temp_info, BYTE *states)
{
    p_temp_info->GroupID = states[0];
    p_temp_info->SubID = states[1];
    p_temp_info->HiLow = (states[2] & 0x80) >> 7;
    p_temp_info->Temperature = states[2] & 0x7F;
}

/* ------------------------------------- */
/* Name: parse_testtone_info()
 * Source: 3.1.3 [0C0F]
 * Status Description:  
 *      Notification of information about Test tone ( refer to the description 
 * of TESTTONE_OUTPUT command ) that currently running. 
 *      This is a response status to CALL_TESTTPME_INFO command ( refer to the 
 * description of this command ) and, this is voluntarily notified at the state 
 * transition. 
 */

/* Parameter */
/*
TestMode ( Param0.    bit0 to 1 )    : Current running status of Test Tone 
    00b : Test tone OFF ( Off )   
    10b : Test tone is being output continuously from specified ON channel as Param1 . ( Channel )   
          * Unless otherwise instructed to control, the ON channel is remained after a fixed time 
    11b : Test tone is being output from specified ON channel in order of precedence as Param1. ( Auto )   
          * The ON channel automatically switch over to another after a fixed time without any control instruction. 
 
NoiseMode ( Param0.    bit4 to 5 )    : Type of tone    ( valid in â€˜TestMode = Channel/Autoâ€?)   
    00b : Not specified      ( TestMode = Off )   
    00b : Pink Noise is outputting   ( TestMode = Channel/Auto )   
    10b : Sine wave is outputting    ( TestMode = Channel/Auto )   
 
LfMode ( Param1.    bit0 )  : Front Left channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?) 
RfMode ( Param1.    bit0 )  : Front Right channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?) 
CMode ( Param1.    bit0 )  : Center channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?) 
LsMode ( Param1.    bit0 )  : Left Surround channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?)   
RsMode ( Param1.    bit0 )  : Right Surround channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?) 
SwMode ( Param1.    bit0 )  : Subwoofer channel output status      ( valid in â€˜TestMode = Channel/Autoâ€?) 
    0b : Not specified        ( TestMode = Off )   
    0b : Test tone is not being output    ( TestMode = Channel/Auto )   
    1b : Test tone is being output      ( TestMode = Channel/Auto )   
*/ 

struct TESTTONE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    NoiseMode;
    BYTE    TestMode;
    BYTE    SwMode;
    BYTE    RsMode;
    BYTE    LsMode;
    BYTE    CMode;
    BYTE    RfMode;
    BYTE    LfMode;
    BYTE    TESTTONE_INFO_NULL0;
    BYTE    TESTTONE_INFO_NULL1;
};

void parse_testtone_info(struct TESTTONE_INFO *p_testtone_info, BYTE *states)
{
    p_testtone_info->GroupID = states[0];
    p_testtone_info->SubID = states[1];
    p_testtone_info->NoiseMode = (states[2] & 0x30) >> 4;
    p_testtone_info->TestMode = states[2] & 0x03;
    p_testtone_info->SwMode = (states[3] & 0x20) >> 5;
    p_testtone_info->RsMode = (states[3] & 0x10) >> 4;
    p_testtone_info->LsMode = (states[3] & 0x08) >> 3;
    p_testtone_info->CMode = (states[3] & 0x04) >> 2;
    p_testtone_info->RfMode = (states[3] & 0x02) >> 1;
    p_testtone_info->LfMode = states[3] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_toc1_info()
 * Source: 3.2.1 [030B]
 * Status Description: 
 *      Notification of TOC information of specified track. 
 *      This is a response status to CALL_TOC1_INFO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */
/*
FirstTrack ( Param0.    All )    : First track number of target disc 
    01 to 63h : Track number [ 1 to 99 ] 
 
LastTrack ( Param1.  All )  : Last track number of target disc 
    01 to 63h : Track number [ 1 to 99 ] 
 
RequestTrack ( Param2.    All )    : Requested track number of target track 
    01 to 63h : Track number [ 1 to 99 ] 
 
Cont0 ( Param3.    bit0 )    : Number of channels of target track 
    0b : 2ch Audio 
    1b : 4ch Audio 
 
Cont1 ( Param3.    bit1 )    : Type of data of target track 
    0b : Audio track 
    1b : Data track 
 
Cont2 ( Param3.    bit2 )    : Digital copy permission of target track 
    0b : Digital Copy inhibit 
    1b : Digital Copy is permitted 
 
Cont3 ( Param3.    bit3 )    : Presence of Pre-emphasis of target track 
    0b : None 
    1b : Exist 
 
StartMinute ( Param4.    All )    : Start position of target track ( minute )   
    00 to 63h : [ 0 to 99 minute ] 

StartSecond ( Param5.    All )    : Start position of target track ( second )   
    00 to 3Bh : [ 0 to 59 seconds ] 
 
StartFrame ( Param6.    All )    : Start position of target track ( frame )   
    00 to 63h : [ 0 to 99 frames ] 
 
SessionNs ( Param7.    All )    : Total session numbers of target track   
    01 to 63h : [ 1 to 99 sessions ] 
*/ 

struct TOC1_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    FirstTrack;
    BYTE    LastTrack;
    BYTE    RequestTrack;
    BYTE    Cont3;
    BYTE    Cont2;
    BYTE    Cont1;
    BYTE    Cont0;
    BYTE    StartMinute;
    BYTE    StartSecond;
    BYTE    StartFrame;
    BYTE    SessionNs;
    BYTE    TOC1_INFO_NULL0;
    BYTE    TOC1_INFO_NULL1;
    BYTE    TOC1_INFO_NULL2;
};

void parse_toc1_info(struct TOC1_INFO *p_toc1_info, BYTE *states)
{
    p_toc1_info->GroupID = states[0];
    p_toc1_info->SubID = states[1];
    p_toc1_info->FirstTrack = states[2];
    p_toc1_info->LastTrack = states[3];
    p_toc1_info->RequestTrack = states[4];
    p_toc1_info->Cont3 = (states[5] & 0x08) >> 3;
    p_toc1_info->Cont2 = (states[5] & 0x04) >> 2;
    p_toc1_info->Cont1 = (states[5] & 0x02) >> 1;
    p_toc1_info->Cont0 = states[5] & 0x01;
    p_toc1_info->StartMinute = states[6];
    p_toc1_info->StartSecond = states[7];
    p_toc1_info->StartFrame = states[8];
    p_toc1_info->SessionNs = states[9];
}

/* ------------------------------------- */
/* Name: parse_toc2_info()
 * Source: 3.2.2 [030C]
 * Status Description: 
 *      Notification of the TOC information with 4 tracks from specified track. 
 *      This is a response status to CALL_TOC2_INFO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */
/*
StartTrackNo ( Param0.    All )    : Track number of specified track ( or Lead-out area) 
    * The track number which is specified to obtain information by CALL_TOC2_INFO   
command. 
    01 to 63h  : Track number [ 1 to 99 ] 
    A2h : Lead-Out 
 
StartMinute1 ( Param1.    All )    : Start position of specified track ( minute ) 
StartMinute2 ( Param4.  All )  : Start position of specified track + 1 ( minute ) 
StartMinute3 ( Param7.  All )  : Start position of specified track + 2 ( minute ) 
StartMinute4 ( Param10.    All )    : Start position of specified track + 3 ( minute ) 
    00 to 63h : 0 to 99 minutes 
 
StartMinute1 ( Param2.  All )  : Start position of specified track ( second ) 
StartMinute2 ( Param5.  All )  : Start position of specified track + 1 ( second )   
StartMinute3 ( Param8.  All )  : Start position of specified track + 2 ( second )   
StartMinute4 ( Param11.    All )    : Start position of specified track + 3 ( second )   
    00 to 3Bh : 0 to 59 seconds 
 
StartFrame1 ( Param3.    All )    : Start position of specified track ( frame ) 
StartFrame2 ( Param6.    All )    : Start position of specified track + 1 ( frame ) 
StartFrame3 ( Param9.    All )    : Start position of specified track + 2 ( frame ) 
StartFrame4 ( Param12.    All )    : Start position of specified track + 3 ( frame )   
    00 to 63h :    0 to 99 frames 
*/ 

struct TOC2_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    StartTrackNo;
    BYTE    StartMinute1;
    BYTE    StartSecond1;
    BYTE    StartFrame1;
    BYTE    StartMinute2;
    BYTE    StartSecond2;
    BYTE    StartFrame2;
    BYTE    StartMinute3;
    BYTE    StartSecond3;
    BYTE    StartFrame3;
    BYTE    StartMinute4;
    BYTE    StartSecond4;
    BYTE    StartFrame4;
    BYTE    TOC2_INFO_NULL0;
};

void parse_toc2_info(struct TOC2_INFO *p_toc2_info, BYTE *states)
{
    p_toc2_info->GroupID = states[0];
    p_toc2_info->SubID = states[1];
    p_toc2_info->StartTrackNo = states[2];
    p_toc2_info->StartMinute1 = states[3];
    p_toc2_info->StartSecond1 = states[4];
    p_toc2_info->StartFrame1 = states[5];
    p_toc2_info->StartMinute2 = states[6];
    p_toc2_info->StartSecond2 = states[7];
    p_toc2_info->StartFrame2 = states[8];
    p_toc2_info->StartMinute3 = states[9];
    p_toc2_info->StartSecond3 = states[10];
    p_toc2_info->StartFrame3 = states[11];
    p_toc2_info->StartMinute4 = states[12];
    p_toc2_info->StartSecond4 = states[13];
    p_toc2_info->StartFrame4 = states[14];
}

/* ------------------------------------- */
/* Name: parse_folder_file_no_info()
 * Source: 3.2.3 [0322]
 * Status Description: 
 *      Notification of the file number of folder or the file number of disc 
 * corresponding to the recorded file on disc. 
 *      This is a response status to CALL_FOLDER_FILE_NO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All )    : Folder number that contains target information file (It is valid with file number for disc) 
    0000h         : No information 
        * This means that this information is a file number for disk shown by [FileNo].   
    0001 to 0100h    : Folder number [ 1 to 256 ] 
        * 0001h indicates as root. 
        * This means that this information is a file number for folder shown by [FileNo] and [Folder].   
 
FileNo ( Param2 to 3.    All )    : File number of target information file 
    0001 to 1000h    : File number [ 1 to 4096 ] 
        * If [FolderNo = 0000h], this parameter shows file number for Disc. 
        * If [FolderNo  â‰? 0000h], this parameter shows file number for Folder of [FolderNo] 
*/ 

struct FOLDER_FILE_NO_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    FOLDER_FILE_NO_INFO_NULL0;
    BYTE    FOLDER_FILE_NO_INFO_NULL1;
    WORD    FolderNo;
    WORD    FileNo;
};

void parse_folder_file_no_info(struct FOLDER_FILE_NO_INFO *p_folder_file_no_info, BYTE *states)
{
    p_folder_file_no_info->GroupID = states[0];
    p_folder_file_no_info->SubID = states[1];
    p_folder_file_no_info->FolderNo = (WORD(states[2]) << 7) + states[3];
    p_folder_file_no_info->FileNo = (WORD(states[4]) << 7) + states[5];
}

/* ------------------------------------- */
/* Name: parse_text_code_info()
 * Source: 3.3.1 [0D01]
 * Status Description: 
 *      Notification of the Code information of corresponding text type and 
 * language on current replaying CDDA.. 
 *      This is a response status to CALL_TEXT_CODE_INFO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */
/*
PageNo ( Param0.    All )    : Divided page number of target information 
    01 to 02h : Page number [ 1 to 2 ] 
 
LastPageNo ( Param1.    All )    : Last page number 
    01 to 02h : Page number [ 1 to 2 ] 
 
LangCodeX ( Param2X.    All )    : The corresponding language code that recorded Xth 
    00h : No Text 
    08h : German 
    09h : English 
    0Ah : Spanish 
    0Fh : French 
    69h : Japanese 
    Any : Other code than the above 
        * There is a possibility that the codes other than the above-mentioned exist because it just replies the code recorded on the Disc. 
 
CharCodeX ( Param2X+1.    All )    : The corresponding character code that recorded Xth 
    00h : No Text 
    00h : ISO 8859-1 
    01h : ISO/IEC 646 
    80h : SHIFT JIS Kanji and JIS Katakana 
    81h : Korean character 
    82h : Mandarin character 
    Any : Other code than the above 
        * There is a possibility that the code other than the above-mentioned exist because it just replies the code recorded on the Disc. 
*/ 

struct TEXT_CODE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    PageNo;
    BYTE    LastPageNo;
    BYTE    LangCode1;
    BYTE    CharCode1;
    BYTE    LangCode2;
    BYTE    CharCode2;
    BYTE    LangCode3;
    BYTE    CharCode3;
    BYTE    LangCode4;
    BYTE    CharCode4;
    BYTE    LangCode5;
    BYTE    CharCode5;
    BYTE    TEXT_CODE_INFO_NULL0;
    BYTE    TEXT_CODE_INFO_NULL1;
};

void parse_text_code_info(struct TEXT_CODE_INFO *p_text_code_info, BYTE *states)
{
    p_text_code_info->GroupID = states[0];
    p_text_code_info->SubID = states[1];
    p_text_code_info->PageNo = states[2];

    if (p_text_code_info->PageNo == 0x01) {
        p_text_code_info->LangCode1 = states[4];
        p_text_code_info->CharCode1 = states[5];
        p_text_code_info->LangCode2 = states[6];
        p_text_code_info->CharCode2 = states[7];
        p_text_code_info->LangCode3 = states[8];
        p_text_code_info->CharCode3 = states[9];
        p_text_code_info->LangCode4 = states[10];
        p_text_code_info->CharCode4 = states[11];
        p_text_code_info->LangCode5 = states[12];
        p_text_code_info->CharCode5 = states[13];
    }

    if (p_text_code_info->PageNo == 0x02) {
        p_text_code_info->LangCode1 = states[4];
        p_text_code_info->CharCode1 = states[5];
        p_text_code_info->LangCode2 = states[6];
        p_text_code_info->CharCode2 = states[7];
        p_text_code_info->LangCode3 = states[8];
        p_text_code_info->CharCode3 = states[9];
    }
}



void parse_text_info(struct TEXT_INFO *p_text_info, BYTE *states, BYTE TextType)
{
    p_text_info->GroupID = states[0];
    p_text_info->SubID = states[1];
    
    /* CDDA : TextType = 8Fh */
    if (TextType == 0x8F) {
        p_text_info->text_info_0x8fh.PageNo = states[2];
        p_text_info->text_info_0x8fh.LastPageNo = states[3];
        p_text_info->text_info_0x8fh.BlockNo1 = states[4];
        p_text_info->text_info_0x8fh.CharCode1 = states[5];
        p_text_info->text_info_0x8fh.AlbumSize1 = states[6];
        p_text_info->text_info_0x8fh.performerSize1 = states[7];
        p_text_info->text_info_0x8fh.SelectSize1 = states[8];
        p_text_info->text_info_0x8fh.LangCode1 = states[9];
    }

    /* CDDA : TextTypeâ‰?Fh */
    if (TextType != 0x8F) {
        p_text_info->text_info_not_0x8fh.LangCode = states[2];
        p_text_info->text_info_not_0x8fh.CharCode = states[3];
        p_text_info->text_info_not_0x8fh.PageNo = states[4];
        p_text_info->text_info_not_0x8fh.LastPageNo = states[5];
        
        for (int i=0; i<8; ++i)
            p_text_info->text_info_not_0x8fh.TextData[i] = states[i+6];
    }
}

void parse_file_name_info(FILENAME_INFO *p_filename_info, BYTE *states)
{
	p_filename_info->GroupID = states[0];
	p_filename_info->SubID = states[1];
	p_filename_info->PageNo = states[2];
	p_filename_info->LastPageNo = states[3];
	p_filename_info->FileType = states[4];
	for (int i=0;i<sizeof(p_filename_info->FILENAME)/sizeof(p_filename_info->FILENAME[0]);i++)
	{
		p_filename_info->FILENAME[i] = states[5+i];
	}
}

/* ------------------------------------- */
/* Name: parse_disc_name_info()
 * Source: 3.3.6 [0D0A]
 * Status Description: 
 *      Notification of Disc name correspond to identification Disc. 
 *      This is a response status to CALL_DISC_NAME_INFO command ( refer to the 
 * description of this command ). 
 */

/* Parameter */
/*
PageNo ( Param0.    All )    : Divided page number of target information 
    01to 07h : Page number [ 1to 7 ] 
        * 10 bytes text data is allocated per a page.   
 
 
LastPageNo ( Param1.    All )    : Last page number 
    01to 07h : Page number [ 1to 7 ] 
 
CharCode ( Param2.    All )    : Character code of Disc name 
    00h : ISO 8859-1 
    01h : Unicode 
 
DiscName ( Param3 to N.    All )    : Disc name 
    Any : Disc name 
        *    The sendable number of character is 64 for ASCII and 32 for UNICODE. 
*/ 


void parse_folder_info(struct FOLDER_INFO *p_folder_info, BYTE *states, BYTE InfoType)
{
    p_folder_info->GroupID = states[0];
    p_folder_info->SubID = states[1];

    /* InfoType = 0b */
    if (InfoType == 0x00) {
        p_folder_info->folder_info_folder_block.FileNs = (WORD(states[2]) << 8)
                                                       + states[3];
        p_folder_info->folder_info_folder_block.UpperFolderNo = (WORD(states[4]) << 8)
                                                              + states[5];
        p_folder_info->folder_info_folder_block.LowerFolderNs = (WORD(states[6]) << 8)
                                                              + states[7];
    }

    /* InfoType = 1b */
    if (InfoType == 0x01) {
        p_folder_info->folder_info_lower_folder_block.PageNo = states[2];
        p_folder_info->folder_info_lower_folder_block.LastPageNo = states[3];
        p_folder_info->folder_info_lower_folder_block.FolderNo1 = (WORD(states[4]) << 8)
                                                                + states[5];
        p_folder_info->folder_info_lower_folder_block.FolderNo2 = (WORD(states[6]) << 8)
                                                                + states[7];
        p_folder_info->folder_info_lower_folder_block.FolderNo3 = (WORD(states[8]) << 8)
                                                                + states[9];
        p_folder_info->folder_info_lower_folder_block.FolderNo4 = (WORD(states[10]) << 8)
                                                                + states[11];
        p_folder_info->folder_info_lower_folder_block.FolderNo5 = (WORD(states[12]) << 7)
                                                                + states[13];
    }

}

/* ------------------------------------- */
/* Name: parse_file_type_info()
 * Source: 3.4.2 [0E06]
 * Status Description: 
 *      Notification of information about type of recorded file on 
 * identification Disc. 
 *      This is a response status to CALL_FILE_TYPE_INFO command ( refer to the 
 * description  of this command ) and, the target information file is specified 
 * by the command.
 */

/* Parameter */
/*
MP3 ( Param0.    bit1 )  : Presence of MP3 file ( Specified by folder ) / Identification of MP3 file ( Specified by file )     
WMA ( Param0.    bit2 )  : Presence of WMA file ( Specified by folder ) /     
    Identification of WMA file    ( Specified by file )     
WAV ( Param0.    bit4 )  : Presence of WAV file ( Specified by folder ) / Identification of WAV file    ( Specified by file ) 
UnSupport ( Param3.    bit7 )  : Presence of unsupported file ( Specified by folder ) /     
    Identification of unsupported file      ( Specified by file )     
    0b : Not exist    / Not identified as specified file type 
    1b : Exist    / Identified as specified file type 
*/ 

struct FILE_TYPE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    WAV;
    BYTE    WMA;
    BYTE    MP3;
    BYTE    UnSupport;
    BYTE    FILE_TYPE_INFO_NULL0;
    BYTE    FILE_TYPE_INFO_NULL1;
};

void parse_file_type_info(struct FILE_TYPE_INFO *p_file_type_info, BYTE *states)
{
    p_file_type_info->GroupID = states[0];
    p_file_type_info->SubID = states[1];
    p_file_type_info->WAV = (states[2] & 0x10) >> 4;
    p_file_type_info->WMA = (states[2] & 0x04) >> 2;
    p_file_type_info->MP3 = (states[2] & 0x02) >> 1;
    p_file_type_info->UnSupport = (states[5] & 0x80) >> 7;

}

/* ------------------------------------- */
/* Name: parse_secondposition_ns_info()
 * Source: 3.4.3 [0E07]
 * Status Description: 
 *      Notification of total number of Second Position in specified First 
 * Position section on replay content. 
 *      This is a response status to CALL_SECONDPOSITION_NS_INFO command ( refer 
 * to the description of this command ) and, the target information file is 
 * specified by the command. 
 */

/* Parameter */
/*
FirstPositionNo ( Param0 to 1.    All )    :    Specified First Position number 
    0001 to 0100h    : Folder number [ 1 to 256 ]  ( COMPRESS )   
        * 0001h is indicated as root 
    0001 to 0063h    : Title number [ 1 to 99 ]  ( DVD-Video )   
 
SecondPositionNs0 ( Param2 to 3.    All )    : Total number of second positions in the specified First Position 
SecondPositionNs1 ( Param4 to 5.    All )  : Total number of second positions in the specified First Position +1 
SecondPositionNs2 ( Param6 to 7.    All )  : Total number of second positions in the specified First Position +2 
SecondPositionNs3 ( Param8 to 9.    All )  : Total number of second positions in the specified First Position +3 
SecondPositionNs1 ( Param10 to 11.    All )    : Total number of second positions in the specified First Position +4 
    0001 to 1000h   : Total number of files [ 1 to 4096 ]  ( COMPRESS )   
    0001 to 03E7h  : Total number of chapters ( PTT ) [ 1 to 999 ]  ( DVD-Video )   
*/ 

struct SECONDPOSITION_NS_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    SECONDPOSITION_NS_INFO_NULL0;
    BYTE    SECONDPOSITION_NS_INFO_NULL1;
    WORD    FirstPositionNo;
    WORD    SecondPositionNs0;
    WORD    SecondPositionNs1;
    WORD    SecondPositionNs2;
    WORD    SecondPositionNs3;
    WORD    SecondPositionNs4;
};

void parse_secondposition_ns_info(struct SECONDPOSITION_NS_INFO *p_secondposition_ns_info, BYTE *states)
{
    p_secondposition_ns_info->GroupID = states[0];
    p_secondposition_ns_info->SubID = states[1];
    p_secondposition_ns_info->FirstPositionNo = (WORD(states[2]) << 7)
                                              + states[3];
    p_secondposition_ns_info->SecondPositionNs0 = (WORD(states[4]) << 7)
                                                + states[5];
    p_secondposition_ns_info->SecondPositionNs1 = (WORD(states[6]) << 7)
                                                + states[7];
    p_secondposition_ns_info->SecondPositionNs2 = (WORD(states[8]) << 7)
                                                + states[9];
    p_secondposition_ns_info->SecondPositionNs3 = (WORD(states[10]) << 7)
                                                + states[11];
    p_secondposition_ns_info->SecondPositionNs4 = (WORD(states[12]) << 7)
                                                + states[13];
}

/* ------------------------------------- */
/* Name: parse_stream_attribute_info()
 * Source: 3.4.4 [0E08]
 * Status Description: 
 *      Notification of specified stream attribute type information on replay content. 
 *      This is a response status to CALL_STREAM_ATTRIBUTE_INFO command ( refer 
 * to the description of this command ) and, the target stream type is specified 
 * by the command. 
 *      Moreover, the information format is decided by the stream type. 
 *      Note :  This information is based on the administrative information 
 * recorded on the Disc, and has a possibility of difference from actual stream.   
 */

/* Parameter */
/* CALL_STREAM_ATTRIBUTE_INFO . StType : Audio */
/*
AudioFormat ( Param0.  All )  : Audio Format   
    00h : Unknown Format 
    01h : Linear PCM ( DVD-Video/CDDA/VCD )   
    11h : Dolby Digital ( Unknown extension )   
    22h : DTS 
    23h : DTS-ES 
           * Notify as â€œDTSâ€?because this is not able to identified by present standard. 
    31h : SDDS 
    42h : MPEG1 without extended Bit Stream ( MPEG-Audio Layerâ…?)  
    43h : MPEG1 with extended Bit Stream    ( MPEG-Audio Layerâ…?)  
              * Notify as â€œMPEG1 without extended Bit Stream â€?because this is not able to identified by present standard. 
    45h : MPEG2 without extended Bit Stream ( MPEG-Audio Layerâ…?)   
              * Notify as â€œMPEG1 without extended Bit Stream â€?because this is not able to identified by present standard. 
    46h : MPEG2 with extended Bit Stream ( MPEG-Audio Layerâ…?)  
    48h : MP3 ( MPEG1 Layerâ…?)  
    49h : MP3 ( MPEG2 Layerâ…?)  
    4Ah : MP3 ( MPEG2.5 Layerâ…?)  
 
ChannelNs ( Param1.    bit0 to 3 )    : Number of channels   
    0h : Unknown 
    1 to 8h  : Number of channels [ 1 to 8 ch ] 
    9h  : DualMono at 2 channel 
 
LangCode ( Param3 to 4.    All )    : Audio language code 
    0000 to FFFFh : Language code 
        * The code complies with ISO639. 
*/ 

struct STRUCT_STREAM_ATTRIBUTE_INFO_AUDIO {
    BYTE    AudioFormat;
    BYTE    ChannelNs;
    WORD    LangCode;
};

/* CALL_STREAM_ATTRIBUTE_INFO . StType : SubP */
/*
LangCode ( Param3 to 4.    All )    : Language code of Sub-picture 
    0000 to FFFFh : Language code 
        * The code complies with ISO639. 
*/

struct STRUCT_STREAM_ATTRIBUTE_INFO_SUBP {
    WORD    LangCode;
    BYTE    STRUCT_STREAM_ATTRIBUTE_INFO_SUBP_NULL0;
    BYTE    STRUCT_STREAM_ATTRIBUTE_INFO_SUBP_NULL1;
};

struct STREAM_ATTRIBUTE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    STREAM_ATTRIBUTE_INFO_NULL0;
    BYTE    STREAM_ATTRIBUTE_INFO_NULL1;

    struct STRUCT_STREAM_ATTRIBUTE_INFO_AUDIO stream_attribute_info_audio;
    struct STRUCT_STREAM_ATTRIBUTE_INFO_SUBP stream_attribute_info_subp;
};

void parse_stream_attribute_info(struct STREAM_ATTRIBUTE_INFO *p_stream_attribute_info, BYTE *states, BYTE StType)
{
    p_stream_attribute_info->GroupID = states[0];
    p_stream_attribute_info->SubID = states[1];
    
    /* CALL_STREAM_ATTRIBUTE_INFO . StType : Audio */
    if (StType == 0x00) {
        p_stream_attribute_info->stream_attribute_info_audio.AudioFormat = states[2];
        p_stream_attribute_info->stream_attribute_info_audio.ChannelNs = states[3];
        p_stream_attribute_info->stream_attribute_info_audio.LangCode = (WORD(states[5]) << 7) + states[6];
    }

    /* CALL_STREAM_ATTRIBUTE_INFO . StType : SubP */
    if (StType == 0x01) {
        p_stream_attribute_info->stream_attribute_info_subp.LangCode = (WORD(states[2]) << 7) + states[3];
    }
}

/* ------------------------------------- */
/* Name: parse_set3v_back_video_info()
 * Source: 3.5.1 [0A01]
 * Status Description: 
 *      Notification of setting condition about output image (background image) 
 * while video contents are not replaying.   
 *      The setting condition that is indicated by this status is possible to 
 * change by SET3V_BACK_VIDEO command (refer to the description of this command). 
 */

/* Parameter */
/*
BackVideo ( Param0.    All ) : Setting of type of Background image 
    00h : Set as specified background color ( initial value ) 
        * It is specified in combination with [Ysignal], [CbSignal] and [CrSignal] settings 
    01h : Set as [Demo screen] in memory record 
      * Use image data that stored in Screensaver area 0 of memory 
 
Ysignal ( Param1.    All ) : Setting of Brightness (Y) as for background color 
    00ï½žFFh : Brightness Y value ( initial value : 00 ) 
 
CbSignal ( Param2.    All ) : Setting of Color difference (Cb) as for background color 
    00ï½žFFh : Color difference Cb value ( initial value : A0 ) 
 
CrSignal ( Param3.    All ) : Setting of Color difference (Cr) as for background color 
    00ï½žFFh : Color difference Cr value    ( initial value : 70 ) 
*/ 

struct SET3V_BACK_VIDEO_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    BackVideo;
    BYTE    YSignal;
    BYTE    CbSignal;
    BYTE    CrSignal;
    BYTE    SET3V_BACK_VIDEO_INFO_NULL0;
    BYTE    SET3V_BACK_VIDEO_INFO_NULL1;
};

void parse_set3v_back_video_info(struct SET3V_BACK_VIDEO_INFO *p_set3v_back_video_info, BYTE *states)
{
    p_set3v_back_video_info->GroupID = states[0];
    p_set3v_back_video_info->SubID = states[1];
    p_set3v_back_video_info->BackVideo = states[2];
    p_set3v_back_video_info->YSignal= states[3];
    p_set3v_back_video_info->CbSignal = states[4];
    p_set3v_back_video_info->CrSignal = states[5];
}

/* ------------------------------------- */
/* Name: parse_set3v_video_adjust_info()
 * Source: 3.5.2 [0A10]
 * Status Description: 
 *      Notification of setting condition about quality of the picture. 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET3V_VIDEO_ADJUST command (refer to the description of this command). 
 */

/* Parameter */
/*
BSign ( Param0.    bit7 )    : Set the sign of Brightness level 
* It indicates set level in combination with absolute value of [Brightness]. 
    0b : Minus (ï¼? (Initial value) 
    1b : Plus (ï¼? 
 
Brightness ( Param0.    bit0 to 6 )    : Set the absolute value of Brightness level value 
        * It indicates set level in combination with [BSign]. 
    00 to 0Fh : [ 0 to 15 ]    (Initial value = 0) 
        * The setting that lightens most is "BSin=1" "Brightness=15". 
        * The setting that darkens most is "BSin=0" "Brightness=15". 
 
CtSign ( Param1.    bit7 )    : Set the sign of Contrast level 
        * It indicates set level in combination with absolute value of [Contrast]. 
    0b : Minus (ï¼? (Initial value) 
    1b : Plus (ï¼? 
 
Contrast ( Param1.    bit0 to 6 )    : Set the absolute value of Contrast level value 
        * It indicates set level in combination with [CtSign]. 
    00 to 0Fh : [ 0 to 15 ]    (Initial value = 0) 
        * The setting with the highest contrast ratio is "CtSin=1" "Contrast=15". 
        * The setting with the lowest contrast ratio is "CtSin=0" "Contrast=15". 
 
ClSign ( Param2.    bit7 )    : Set the sign of Color level 
        * It indicates set level in combination with absolute value of [Color]. 
    0b : Minus (ï¼? (Initial value) 
    1b : Plus (ï¼? 
 
Color ( Param2.    bit0 to 6 )    : Set the absolute value of Color level value 
        * It indicates set level in combination with [ClSign]. 
    00 to 0Fh : [ 0 to 15 ]    (Initial value = 0) 
        * The setting that deepens most is "ClSin=1" "Color=15". 
        * The setting that dilutes most is "ClSin=0" "Color=15". 

TSign ( Param3.    bit7 )    : Set the sign of Tint level 
        * It indicates set level in combination with absolute value of [Tint]. 
    0b : Minus (ï¼? (Initial value) 
    1b : Plus (ï¼? 
 
Tint ( Param3.    bit0 to 6 )    : Set the absolute value of Tint level value 
        * It indicates set level in combination with [TSign]. 
    00 to 0Fh : [ 0 to 15 ]    (Initial value = 0) 
        * The setting that becomes red is "TSin=1" "Tint=15". 
        * The setting that becomes green is "TSin=0" "Tint=15". 
*/ 

struct SET3V_VIDEO_ADJUST_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    BSign;
    BYTE    Brightness;
    BYTE    CtSign;
    BYTE    Contrast;
    BYTE    ClSign;
    BYTE    Color;
    BYTE    TSign;
    BYTE    Tint;
    BYTE    SET3V_VIDEO_ADJUST_INFO_NULL0;
    BYTE    SET3V_VIDEO_ADJUST_INFO_NULL1;
};

void parse_set3v_video_adjust_info(struct SET3V_VIDEO_ADJUST_INFO *p_set3v_video_adjust_info, BYTE *states)
{
    p_set3v_video_adjust_info->GroupID = states[0];
    p_set3v_video_adjust_info->SubID = states[1];
    p_set3v_video_adjust_info->BSign = (states[2] & 0x80) >> 7;
    p_set3v_video_adjust_info->Brightness = states[2] & 0x7F;
    p_set3v_video_adjust_info->CtSign = (states[3] & 0x80) >> 7;
    p_set3v_video_adjust_info->Contrast = states[3] & 0x7F;
    p_set3v_video_adjust_info->ClSign = (states[4] & 0x80) >> 7;
    p_set3v_video_adjust_info->Color = states[4] & 0x7F;
    p_set3v_video_adjust_info->TSign = (states[5] & 0x80) >> 7;
    p_set3v_video_adjust_info->Tint = states[5] & 0x7F;
}

/* ------------------------------------- */
/* Name: parse_set3a_drc_info()
 * Source: 3.5.3 [0B01]
 * Status Description: 
 *      Notification of setting condition about Dynamic Range control. 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET3A_DRC command (refer to the description of this command). 
 */

/* Parameter */
/*
DRCMode ( Param0.  bit0 to 3 )  :  Select the mode of Dynamic Range Control 
    0h : Set standard ( Std )    ( Initial value )   
    1h : Set Radiofrequency ( Rf )   
    2h : Set Max value ( Max )   
    3h : Set the value based on the coefficient ( Custom )   
    4h : Set Radiofrequency of TV type for Home ( RfTV )   
      * For Dolby authorization on this setting requires careful attention. 
 
CutScale ( Param1.    bit0 to 3 )    :    Set Compression cut scale on standards of ATSC 
    0h  : None specified ( DRCMode = Std/Rf/Max/RfTV )    ( Initial value )     
    0 to 8h  : [ 0.000 to 1.000 ] ( DRCMode = Custom )    ( in 0.125 increments    )   
 
BoostScale ( Param2.    bit0 to 3 )    : Set Compression boost scale on standards of ATSC 
    0h  : None specified ( DRCMode = Std/Rf/Max/RfTV )    ( Initial value )     
    0 to 8h  : [ 0.000 to 1.000 ] ( DRCMode = Custom )    ( in 0.125 increments )   
*/ 

struct SET3A_DRC_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    DRCMode;
    BYTE    CutScale;
    BYTE    BoostScale;
    BYTE    SET3A_DRC_INFO_NULL0;
    BYTE    SET3A_DRC_INFO_NULL1;
    BYTE    SET3A_DRC_INFO_NULL2;
};

void parse_set3a_drc_info(struct SET3A_DRC_INFO *p_set3a_drc_info, BYTE *states)
{
    p_set3a_drc_info->GroupID = states[0];
    p_set3a_drc_info->SubID = states[1];
    p_set3a_drc_info->DRCMode = states[2];
    p_set3a_drc_info->CutScale = states[3];
    p_set3a_drc_info->BoostScale = states[4];
}

/* ------------------------------------- */
/* Name: parse_set3a_a_spk_info()
 * Source: 3.5.4 [0B02]
 * Status Description: 
 *      Notification of setting condition and size of Speaker on system environment. 
 *      The setting condition that is indicated by this status is  possible to 
 * change by SET3A_A_SPK command (refer to the description of this command). 
 */

/* Parameter */
/*
FrontSize ( Param0.    bit0 to 1 )    : Set Front speaker size 
    01b : Small 
    10b : Large ( Initial value )     
 
RearSize ( Param0.    bit2 to 3 )    : Set Rear speaker size 
    00b : None ( Initial value )     
    01b : Small 
    10b : Large 
 
CenterSize ( Param0.    bit4 to 5 )    : Set Center speaker size 
    00b : None ( Initial value )     
    01b : Small 
    10b : Large 
 
Sw ( Param1.    bit0 to 1 )    : Set Subwoofer speaker connection 
    00b : Not connected ( Initial value )     
    10b : Be connected
*/ 

struct SET3A_A_SPK_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    CenterSize;
    BYTE    RearSize;
    BYTE    FrontSize;
    BYTE    Sw;
    BYTE    SET3A_A_SPK_INFO_NULL0;
    BYTE    SET3A_A_SPK_INFO_NULL1;
};

void parse_set3a_a_spk_info(struct SET3A_A_SPK_INFO *p_set3a_a_spk_info, BYTE *states)
{
    p_set3a_a_spk_info->GroupID = states[0];
    p_set3a_a_spk_info->SubID = states[1];
    p_set3a_a_spk_info->CenterSize = (states[2] & 0x30) >> 4;
    p_set3a_a_spk_info->RearSize = (states[2] & 0x0C) >> 2;
    p_set3a_a_spk_info->FrontSize = states[2] & 0x03;
    p_set3a_a_spk_info->Sw = states[3] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_set3a_a_delay_info()
 * Source: 3.5.5 [0B03]
 * Status Description: 
 *      Notification of setting condition of Delay for each Audio Channel 
 *      The setting condition that is indicated by this status is  possible to 
 * change by SET3A_A_DELAY command (refer to the description of this command). 
 */

/* Parameter */
/*
FLDelay ( Param0.    All )    : Set the Delay value for Front Left output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
 
FRDelay ( Param1.  All )  : Set the Delay value for Front Right output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
 
CDelay ( Param2.    All )    : Set the Delay value for Center output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
 
RLDelay ( Param3.  All )  : Set the Delay value for Rear Left output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
 
RRDelay ( Param4.  All )  : Set the Delay value for Rear Right output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
 
SwDelay ( Param5.    All )    : Set the Delay value for Subwoofer output. 
    00 to C8h : [ 0 to 20 ms ] ( in 0.1ms increments ) ( Initial value 0 )   
*/ 

struct SET3A_A_DELAY_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    FLDelay;
    BYTE    FRDelay;
    BYTE    CDelay;
    BYTE    RLDelay;
    BYTE    RRDelay;
    BYTE    SwDelay;
};

void parse_set3a_a_delay_info(struct SET3A_A_DELAY_INFO *p_set3a_a_delay_info, BYTE *states)
{
    p_set3a_a_delay_info->GroupID = states[0];
    p_set3a_a_delay_info->SubID = states[1];
    p_set3a_a_delay_info->FLDelay = states[2];
    p_set3a_a_delay_info->FRDelay = states[3];
    p_set3a_a_delay_info->CDelay = states[4];
    p_set3a_a_delay_info->RLDelay = states[5];
    p_set3a_a_delay_info->RRDelay = states[6];
    p_set3a_a_delay_info->SwDelay = states[7];
}

/* ------------------------------------- */
/* Name: parse_set3a_spk_lvl_info()
 * Source: 3.5.6 [0B04]
 * Status Description: 
 *      Notification of setting condition of Level for each Audio Channel. 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET3A_SPK_LVL command (refer to the description of this command). 
 */

/* Parameter */
/*
FLLevel ( Param0.    bit0 to 3 )    :    Set absolute value for Front Left output level 
        *The level value is shown by the combination with [FLSign].   
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
FLSign ( Param0.  bit4 )  :   Set sign for Front Left output level. 
        *The level value is shown by the combination with absolute value of [FLSign].   
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
FRLevel ( Param1.    bit0 to 3 )    :    Set absolute value for Front Right output level 
        * The level value is shown by the combination with [FRSign] 
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
FRSign ( Param1.    bit4 )    :    Set sign for Front Right output level 
        * The level value is shown by the combination with absolute value of [FRLevel] 
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
CLevel ( Param2.    bit0 to 3 )    :    Set absolute value for Center output level 
        *The level value is shown by the combination with [CSign] 
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
CSign ( Param2.  bit4 )  :   Set sign for Center output level 
        * The level value is shown by the combination with absolute value of [CLevel] 
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + ) 

RLLevel ( Param3.    bit0 to 3 )    :    Set absolute value for Rear Left output level 
        *The level value is shown by the combination with [RLSign].   
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
RLSign ( Param3.    bit4 )    :    Set sign for Rear Left output level. 
        *The level value is shown by the combination with absolute value of [RLSign].   
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
RRLevel ( Param4.    bit0 to 3 )    :    Set absolute value for Rear Right output level 
        * The level value is shown by the combination with [RRSign] 
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
RRSign ( Param4.  bit4 )  :   Set sign for Rear Right output level 
        * The level value is shown by the combination with absolute value of [RRLevel] 
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
SwLevel ( Param5.    bit0 to 3 )    :    Set absolute value for Subwoofer output level 
        *The level value is shown by the combination with [SwSign] 
    0 to Ch : [ 0 to 12 db ] ( in 1db increments )    ( Initial value 0 )   
 
SwSign ( Param5.  bit4 )  :   Set sign for Subwoofer output level 
        * The level value is shown by the combination with absolute value of [SwLevel] 
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
*/ 

struct SET3A_SPK_LVL_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    FLSign;
    BYTE    FLLevel;
    BYTE    FRSign;
    BYTE    FRLevel;
    BYTE    CSign;
    BYTE    CLevel;
    BYTE    RLSign;
    BYTE    RLLevel;
    BYTE    RRSign;
    BYTE    RRLevel;
    BYTE    SwSign;
    BYTE    SwLevel;
    BYTE    SET3A_SPK_LVL_INFO_NULL0;
    BYTE    SET3A_SPK_LVL_INFO_NULL1;
};

void parse_set3a_spk_lvl_info(struct SET3A_SPK_LVL_INFO *p_set3a_spk_lvl_info, BYTE *states)
{
    p_set3a_spk_lvl_info->GroupID = states[0];
    p_set3a_spk_lvl_info->SubID = states[1];
    p_set3a_spk_lvl_info->FLSign = (states[3] & 0x10) >> 4;
    p_set3a_spk_lvl_info->FLLevel = states[3] & 0x0F;
    p_set3a_spk_lvl_info->FRSign = (states[4] & 0x10) >> 4;
    p_set3a_spk_lvl_info->FRLevel = states[4] & 0x0F;
    p_set3a_spk_lvl_info->CSign = (states[5] & 0x10) >> 4;
    p_set3a_spk_lvl_info->CLevel = states[5] & 0x0F;
    p_set3a_spk_lvl_info->RLSign = (states[6] & 0x10) >> 4;
    p_set3a_spk_lvl_info->RLLevel = states[6] & 0x0F;
    p_set3a_spk_lvl_info->RRSign = (states[7] & 0x10) >> 4;
    p_set3a_spk_lvl_info->RRLevel = states[7] & 0x0F;
    p_set3a_spk_lvl_info->SwSign = (states[8] & 0x10) >> 4;
    p_set3a_spk_lvl_info->SwLevel = states[8] & 0x0F;
}

/* ------------------------------------- */
/* Name: parse_set3a_a_mute_info()
 * Source: 3.5.7 [0B05]
 * Status Description: 
 *      Notification of setting condition of Mute for Audio output. 
 *      The setting condition that is indicated by this status is  possible to 
 * change by SET3A_A_MUTE command (refer to the description of this command). 
 */

/* Parameter */
/*
AnalogMute ( Param0.    bit0 to 1 )    : Set mute for Analogue output 
        * If Analogue output is set as mute, Digital output is also muted. 
    00b : Mute is not set. ( Off )    ( Initial value )     
    01b : Mute is set. ( On )   
    11b : Mute is set on selected channel. ( Select )   
 
DigitalMute ( Param0.    bit4 to 5 )    : Set mute for Digital output 
    00b : Mute is not set. ( Initial value )     
    01b : Out put the audio data except additional information as [0]. 
 
FRMute ( Param1.    bit0 )    : Set mute for Front Right output 
    00b : Mute is not set.    ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
 
FLMute ( Param1.    bit1 )    : Set mute for Front Left output 
    00b : Mute is not set.    ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
 
CMute ( Param1.    bit2 )    : Set mute for Center output 
    00b : Mute is not set. ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
 
RRMute ( Param1.    bit3 )    : Set mute for Rear Right output 
    00b : Mute is not set.    ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
 
RLMute ( Param1.    bit4 )    : Set mute for Rear Left output 
    00b : Mute is not set.    ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
 
SwMute ( Param1.    bit5 )    : Set mute for Subwoofer output 
    00b : Mute is not set.    ( AnalogMute = Off/On/Select )    ( Initial value )     
    01b : Mute is set. ( AnalogMute = Select )   
*/ 

struct SET3A_A_MUTE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    DigitalMute;
    BYTE    AnalogeMute;
    BYTE    SwMute;
    BYTE    RLMute;
    BYTE    RRMute;
    BYTE    CMute;
    BYTE    FLMute;
    BYTE    FRMute;
    BYTE    SET3A_A_MUTE_INFO_NULL0;
    BYTE    SET3A_A_MUTE_INFO_NULL1;
};

void parse_set3a_a_mute_info(struct SET3A_A_MUTE_INFO *p_set3a_a_mute_info, BYTE *states)
{
    p_set3a_a_mute_info->GroupID = states[0];
    p_set3a_a_mute_info->SubID = states[1];
    p_set3a_a_mute_info->DigitalMute = (states[2] & 0x30) >> 4;
    p_set3a_a_mute_info->AnalogeMute = states[2] & 0x03;
    p_set3a_a_mute_info->SwMute = (states[3] & 0x20) >> 5;
    p_set3a_a_mute_info->RLMute = (states[3] & 0x10) >> 4;
    p_set3a_a_mute_info->RRMute = (states[3] & 0x08) >> 3;
    p_set3a_a_mute_info->CMute = (states[3] & 0x04) >> 2;
    p_set3a_a_mute_info->FLMute = (states[3] & 0x02) >> 1;
    p_set3a_a_mute_info->FRMute = states[3] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_set3a_dm_mode_info()
 * Source: 3.5.8 [0B06]
 * Status Description: 
 *      Notification of setting condition of Down-Mix mode at Down-Mix to 2ch . 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET3A_DM_MODE command (refer to the description of this command).
 */

/* Parameter */
/*
DmMode ( Param0.    All )    : Set Down-Mix mode 
    00h : Stereo Down-Mix    ( Lo / Ro )   
    01h : Surround compatible Down-Mix    ( Lt / Rt )    ( Initial value )
*/ 

struct SET3A_DM_MODE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    DmMode;
    BYTE    SET3A_DM_MODE_INFO_NULL0;
};

void parse_set3a_dm_mode_info(struct SET3A_DM_MODE_INFO *p_set3a_dm_mode_info, BYTE *states)
{
    p_set3a_dm_mode_info->GroupID = states[0];
    p_set3a_dm_mode_info->SubID = states[1];
    p_set3a_dm_mode_info->DmMode = states[2];
}

/* ------------------------------------- */
/* Name: parse_set3a_dpl2_rf_info()
 * Source: 3.5.9 [0B07]
 * Status Description: 
 *      Notification of setting condition of Dolby Pro Logic II and Rear Fill. . 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET3A_DPL2_RF command (refer to the description of this command). 
 */

/* Parameter */
/*
SetMode ( Param0.    bit0 to 3 )    : Set for ProLogic II and RearFill 
        * Simultaneous effective setting of ProLogic and RearFill is improper according to the limitation. 
    0h : ProLogic II and RearFill are not set.    ( Off )    ( Initial value )     
    1h : ProLogic II is set as Music mode. ( Music )   
    2h : ProLogic II is set as Movie mode. ( Movie )   
    3h : ProLogic II is set as Panorama mode. ( Panorama )   
    4h : RearFill is set. ( RearFill )   
 
RDelay ( Param1.    All )    : Set value of addition rear delay for ProLogi II
    00h  : Not specified    ( SetMode = Off/RearFill )    ( Initial value )     
    00 to 19h  : [ 0 to 25 ms ] ( SetMode = Music/Movie/Panorama )    ( in 1ms increments )   
        * At [SetMode = Music/Panorama], Set as 0 to 15 ms 
        * At [SetMode = Movie] , Set as Min 10 ms 
*/ 

struct SET3A_DPL2_RF_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    SetMode;
    BYTE    RDelay;
};

void parse_set3a_dpl2_rf_info(struct SET3A_DPL2_RF_INFO *p_set3a_dpl2_rf_info, BYTE *states)
{
    p_set3a_dpl2_rf_info->GroupID = states[0];
    p_set3a_dpl2_rf_info->SubID = states[1];
    p_set3a_dpl2_rf_info->SetMode = states[2];
    p_set3a_dpl2_rf_info->RDelay = states[3];
}

/* ------------------------------------- */
/* Name: parse_set3a_phantom_info()
 * Source: 3.5.10 [0B08]
 * Status Description: 
 *      Notification of setting condition of BI-PHANTOM. . 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET3A_PHANTOM command (refer to the description of this command). 
 */

/* Parameter */
/*
Level ( Param0.    bit0 to 5 )    :    Set absolute value for BI-PHANTOM output level 
        *The level value is shown by the combination with [Sign] 
    0 to 6h : [ 0 to 6db ] ( in 1db increments )    ( Initial value 0 )   
        *At [Sign =0], set as 0 to 5. 
 
Sign ( Param0.  bit6 )  :   Set sign for BI-PHANTOM output level 
        * The level value is shown by the combination with absolute value of [Level] 
    0b : minus ( - )    ( Initial value )     
    1b : plus ( + )   
 
Mode ( Param0.  bit7 )  :   Set BI-PHANTOM mode 
    0b : Disable ( Initial value )     
    1b : Enable 
*/ 

struct SET3A_PHANTOM_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    Mode;
    BYTE    Sign;
    BYTE    Level;
    BYTE    SET3A_PHANTOM_INFO_NULL0;
    BYTE    SET3A_PHANTOM_INFO_NULL1;
    BYTE    SET3A_PHANTOM_INFO_NULL2;
};

void parse_set3a_phantom_info(struct SET3A_PHANTOM_INFO *p_set3a_phantom_info, BYTE *states)
{
    p_set3a_phantom_info->GroupID = states[0];
    p_set3a_phantom_info->SubID = states[1];
    p_set3a_phantom_info->Mode = (states[2] & 0x80) >> 7;
    p_set3a_phantom_info->Sign = (states[2] & 0x40) >> 6;
    p_set3a_phantom_info->Level = states[2] & 0x3F;
}

/* ------------------------------------- */
/* Name: parse_set3a_bassmng_info()
 * Source: 3.5.11 [0B0A]
 * Status Description: 
 *      Notification of setting condition of cutoff frequency of the low area. 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET3A_BASSMNG command (refer to the description of this command). 
 */

/* Parameter */
/*
 BmFs ( Param0.    bit0 to 6 )    : Set value of the cutoff frequency. 
    01h  :  80 Hz    ( Initial value )     
    02h : 100 Hz 
    03h : 120 Hz 
    04h : 160 Hz 
    05h : 200 Hz 
    06h : 225 Hz 
    07h : 280 Hz 
    08h : 315 Hz 
    09h : 350 Hz 
    0Ah : 400 Hz 
    0Bh : 450 Hz 
    0Ch : 500 Hz 
 
Mode ( Param0.    bit7 )    : Set the cutoff frequency mode 
    0b : Disable ( Initial value )     
    1b : Enable

*/ 

struct SET3A_BASSMNG_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    Mode;
    BYTE    BmFs;
};

void parse_set3a_bassmng_info(struct SET3A_BASSMNG_INFO *p_set3a_bassmng_info, BYTE *states)
{
    p_set3a_bassmng_info->GroupID = states[0];
    p_set3a_bassmng_info->SubID = states[1];
    p_set3a_bassmng_info->Mode = (states[2] & 0x80) >> 7;
    p_set3a_bassmng_info->BmFs = states[2] & 0x7F;
}

/* ------------------------------------- */
/* Name: parse_set2s_scan_time_info()
 * Source: 3.6.1 [0806]
 * Status Description: 
 *      Notification of setting condition of execution timing of SEARCH for SCAN replay.. 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET2S_SCAN_TIME command (refer to the description of this command). 
 */

/* Parameter */
/*
 Time ( Param0.    All )    : Set each replay time for SCAN   
    01 to 18h : [ 5 to 120 sec ] ( Initial value 02h )   
            *It is calculated from 5sec x Time. 
 
Skip ( Param1.    bit0 )    : SCAN æŒ‡å®šæ™‚é–“ã®å†ç”Ÿçµ‚äº†åˆ¤æ–­ã®è¨­å®š 
    0b : SCAN to the next at 74th flame of the preceding Time that specified by [Time]. 
    1b : SCAN to the next at 74th flame of the Time that specified by [Time]. ( Initial value )     
*/ 

struct SET2S_SCAN_TIME_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    Time;
    BYTE    Skip;
};

void parse_set2s_scan_time_info(struct SET2S_SCAN_TIME_INFO *p_set2s_scan_time_info, BYTE *states)
{
    p_set2s_scan_time_info->GroupID = states[0];
    p_set2s_scan_time_info->SubID = states[1];
    p_set2s_scan_time_info->Time = states[2];
    p_set2s_scan_time_info->Skip = states[3];
}

/* ------------------------------------- */
/* Name: parse_set2s_tv_aspect_info()
 * Source: 3.6.2 [0807]
 * Status Description: 
 *      Notification of setting condition of TV aspect ratio of System... 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET2S_TV_ASPECT command (refer to the description of this command). 
 */

/* Parameter */
/*
 SelectMode ( Param0.    bit0 to 1 )    : Set TV aspect ratio 
    00b : Wide ( Initial value )     
    01b : Pan & scan 
    10b : Letterbox 
*/ 

struct SET2S_TV_ASPECT_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    SelectMode;
    BYTE    SET2S_TV_ASPECT_INFO_NULL0;
};

void parse_set2s_tv_aspect_info(struct SET2S_TV_ASPECT_INFO *p_set2s_tv_aspect_info, BYTE *states)
{
    p_set2s_tv_aspect_info->GroupID = states[0];
    p_set2s_tv_aspect_info->SubID = states[1];
    p_set2s_tv_aspect_info->SelectMode = states[2];
}

/* ------------------------------------- */
/* Name: parse_set2s_dau_out_info()
 * Source: 3.6.3 [0809]
 * Status Description: 
 *      Notification of setting condition of Digital Audio output setting. 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET2S_DAU_OUT command (refer to the description of this command). 
 */

/* Parameter */
/*
 Dolby ( Param0.    bit0 )    : Set DOLBY SPDIF output 
    0b : Set as ES ( Initial value )   
    1b : Set as LPCM 
 
DTS ( Param0.    bit1 )    : Set DTS SPDIF output 
    0b : Set as ES ( Initial value )   
    1b : Set as LPCM 
 
MPEG ( Param0.    bit2 )    : Set MPEG SPDIF output 
    0b : Set as ES 
    1b : Set as LPCM ( Initial value ) 
 
DtsDecode ( Param1.    bit0 )    : Set Decoding process for DTS 
    0b : Not execute decode processing 
    1b : Execute decode processing ( Initial value ) 
*/ 

struct SET2S_DAU_OUT_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    MPEG;
    BYTE    DTS;
    BYTE    Dolby;
    BYTE    DtsDecode;
    BYTE    SET2S_DAU_OUT_INFO_NULL0;
    BYTE    SET2S_DAU_OUT_INFO_NULL1;
};

void parse_set2s_dau_out_info(struct SET2S_DAU_OUT_INFO *p_set2s_dau_out_info, BYTE *states)
{
    p_set2s_dau_out_info->GroupID = states[0];
    p_set2s_dau_out_info->SubID = states[1];
    p_set2s_dau_out_info->MPEG = (states[2] & 0x04) >> 2;
    p_set2s_dau_out_info->DTS = (states[2] & 0x02) >> 1;
    p_set2s_dau_out_info->Dolby = states[2] & 0x01;
    p_set2s_dau_out_info->DtsDecode = states[3] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_set2a_play_priority_info()
 * Source: 3.6.4 [0902]
 * Status Description: 
 *      Notification of setting condition of replay contents priority by DVD/CD 
 * disc at initial access. 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET2A_PLAY_PRIORITY command (refer to the description of this command). 
 */

/* Parameter */
/*
 CD ( Param0.    bit1 to 3 )    : Set priorities of playing order by CD 
    000b : Play in the order of descending priorities as VCD > COMPRESS > CDDA ( Initial value )     
    001b : Play in the order of descending priorities as VCD > CDDA > COMPRESS 
 
VCD ( Param1.    bit0 )    : Set priority of PBC by VCD 
    0b : PBC OFF have a priority to set 
    1b : PBC ON have a priority to set ( Initial value )     
*/ 

struct SET2A_PLAY_PRIORITY_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    CD;
    BYTE    VCD;
};

void parse_set2a_play_priority(struct SET2A_PLAY_PRIORITY_INFO *p_set2a_play_priority_info, BYTE *states)
{
    p_set2a_play_priority_info->GroupID = states[0];
    p_set2a_play_priority_info->SubID = states[1];
    p_set2a_play_priority_info->CD = (states[2] & 0x0E) >> 1;
    p_set2a_play_priority_info->VCD = states[3] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_set2a_lang_info()
 * Source: 3.6.5 [0905]
 * Status Description:  
 *      Notification of setting condition of priority of Stream that based on 
 * the language correspond to Audio/SubPicute/Menu.. 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET2A_LANG command (refer to the description of this command). 
 */

/* Parameter */
/*
SPDisp ( Param0.    bit4 )    : Sub Picture display setting   
    * For the content of parameter, refer to the content of SPDisp (Param0. bit4) parameter setting when SelectMode is specified for SubP (10b) by the SET2A_LANG command. 
 
AudioLangCode ( Param1 to 2.    All )    : Language setting that is a criterion for Audio stream selection   
    * For the content of parameter, refer to the content of LangCode (Param1 to 2. All) parameter setting when SelectMode is specified for Audio (01b) by the SET2A_LANG command. 
 
SubPLangCode ( Param3 to 4.    All )    : Language setting that is a criterion for Sub Picture stream selection 
    * For the content of parameter, refer to the content of LangCode (Param1 to 2. All) parameter setting when SelectMode is specified for SubP (10b) by the SET2A_LANG command. 
 
 
MenuLangCode ( Param5 to 6.    All )    : Language setting that is a criterion for Sub Menu stream selection   
    * For the content of parameter, refer to the content of LangCode (Param1 to 2. All) parameter setting when SelectMode is specified for Menu (11b) by the SET2A_LANG command. 
*/ 

struct SET2A_LANG_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    SPDisp;
    BYTE    SET2A_LANG_INFO_NULL0;
    WORD    AudioLangCode;
    WORD    SubPLangCode;
    WORD    MenuLangCode;
};

void parse_set2a_lang_info(struct SET2A_LANG_INFO *p_set2a_lang_info, BYTE *states)
{
    p_set2a_lang_info->GroupID = states[0];
    p_set2a_lang_info->SubID = states[1];
    p_set2a_lang_info->SPDisp = (states[2] & 0x10) >> 4;
    p_set2a_lang_info->AudioLangCode = (WORD(states[3]) << 7) + states[4];
    p_set2a_lang_info->SubPLangCode = (WORD(states[5]) << 7) + states[6];
    p_set2a_lang_info->MenuLangCode = (WORD(states[7]) << 7) + states[8];
}

/* ------------------------------------- */
/* Name: parse_set2a_country_code_info()
 * Source: 3.6.6 [0907]
 * Status Description: 
 *      Notification of setting condition of Country code of DVD-Video. 
 *      The setting condition that is indicated by this status is possible to 
 * change by SET2A_COUNTRY_CODE command (refer to the description of this command). 
 */

/* Parameter */
/*
 CountryCode ( Param0 to 1.    All )    : Set Country code 
    0000 to FFFFh : Country code ( Initial value 7480 )   
        * The setting code complies with ISO3166. 
        * Set the ASCII capital character code in decimal notation by each 4 bit unit. 
        * e.c. ) 7480 -> JP -> Japan 
*/ 

struct SET2A_COUNTRY_CODE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    WORD    CountryCode;
};

void parse_set2a_country_code_info(struct SET2A_COUNTRY_CODE_INFO *p_set2a_country_code_info, BYTE *states)
{
    p_set2a_country_code_info->GroupID = states[0];
    p_set2a_country_code_info->SubID = states[1];
    p_set2a_country_code_info->CountryCode = (WORD(states[2]) << 7) + states[3];
}

/* ------------------------------------- */
/* Name: parse_set2a_ptl_lvl_info()
 * Source: 3.6.7 [0908]
 * Status Description: 
 *      Notification of setting condition of parental control settings on DVD-Video. 
 *      The setting condition that is indicated  by this status is possible to 
 * change by SET2A_PTL_LVL command (refer to the description of this command). 
 */

/* Parameter */
/*
Level ( Param0.    bit0 to 3 )    : Set parental level 
    0h        : Does not perform parental control ( Initial value )     
    1 to 8h : Specifies the parental level [ 1 to 8 ] 
 
PtlPwd4 ( Param1.    bit4 to 7 )   :  Set Parental Password  (4th digit)   
PtlPwd3 ( Param1.    bit0 to 3 )   :  Set Parental Password  (3rd digit)   
PtlPwd2 ( Param2.    bit4 to 7 )   :  Set Parental Password  (2nd digit)   
PtlPwd1 ( Param2.    bit0 to 3 )   :  Set Parental Password  (1st digit)   
    * Password needed when "Level" setting is changed on initialization screen (refer to 
description of SETUP_KEY command). 
    0 to 9h : Password value [ 0 to 9 ]    ( initial value : 1)   
        * Indicate Parental Password by combination of PtlPwd4 to PtlPwd1. 
        * The Bonus Code consists of 4 digits characters as [0000 to 9999] ( initial value : 0000 ) 
*/ 

struct SET2A_PTL_LVL_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    Level;
    BYTE    PtlPwd4;
    BYTE    PtlPwd3;
    BYTE    PtlPwd2;
    BYTE    PtlPwd1;
    BYTE    SET2A_PTL_LVL_INFO_NULL0;
};

void parse_set2a_ptl_lvl_info(struct SET2A_PTL_LVL_INFO *p_set2a_ptl_lvl_info, BYTE *states)
{
    p_set2a_ptl_lvl_info->GroupID = states[0];
    p_set2a_ptl_lvl_info->SubID = states[1];
    p_set2a_ptl_lvl_info->Level = states[2];
    p_set2a_ptl_lvl_info->PtlPwd4 = (states[3] & 0xF0) >> 4;
    p_set2a_ptl_lvl_info->PtlPwd3 = states[3] & 0x0F;
    p_set2a_ptl_lvl_info->PtlPwd2 = (states[4] & 0xF0) >> 4;
    p_set2a_ptl_lvl_info->PtlPwd1 = states[4] & 0x0F;

}

/* ------------------------------------- */
/* Name: parse_set2a_pause_mode_info()
 * Source: 3.6.8 [0909]
 * Status Description: 
 *      Notification of setting condition of Pause. ( refer to the description 
 * of PAUSE_PLAY command ).   
 *      The setting condition that is indicated by this status is possible to 
 * change by SET2A_PAUSE_MODE command (refer to the description of this command). 
 */

/* Parameter */
/*
PauseMode ( Param0.    bit0 to 1 )    : Specifies Pause processing for replaying video contents 
    01b : Field Pause 
      * The image is not blurred at fast-moving section, but the resolution is half the Flame Pause. 
    10b : Flame Pause 
      * The image is blurred at fast-moving section, but the resolution is twice the Field Pause. 
    11b : Field Pause and Frame Pause are selected according to the image automatically. ( Initial value )     
      * Field Pause or Frame Pause is selected based on the average bit rate and the present bit rate. 
      * The [Average bit rate] of each cell is calculated based on the cell size and the cell replay time.   
      *The [Present bit rate] is calculated based on the VOBU size and VOBU replay time. 
*/ 

struct SET2A_PAUSE_MODE_INFO {
    BYTE    GroupID;
    BYTE    SubID;
    BYTE    PauseMode;
    BYTE    SET2A_PAUSE_MODE_INFO_NULL0;
};

void parse_set2a_pause_mode_info(struct SET2A_PAUSE_MODE_INFO *p_set2a_pause_mode_info, BYTE *states)
{
    p_set2a_pause_mode_info->GroupID = states[0];
    p_set2a_pause_mode_info->SubID = states[1];
    p_set2a_pause_mode_info->PauseMode = states[2];
}



