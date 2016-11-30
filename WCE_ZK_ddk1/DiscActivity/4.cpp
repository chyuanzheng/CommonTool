/* Standard status definition */
#include "stdafx.h"
#include "4.h"
#define BYTE unsigned char
#define WORD unsigned short int
#define DWORD unsigned int
/* ------------------------------------- */
/* Name: parse_system_start()
 * Source: 4.1.1 [0C01]
 * Status Description: 
 *      Notification of beginning of system start.   
 *      This status is voluntarily notified when this system begins starting, 
 * and the acceptance of the command is begun since this status. The period from 
 * this status notification to  the SET_END (Refer to the command) reception is 
 * defined as "Initialization period". 
 */

/* Parameter */
/*
Initial ( Param0.    bit0 ) : Reception history of SET_END command 
    0b:  The SET_END command has not been accepted in the past. 
        * This system is a state at the factory default. 
    1b:  The SET_END command has been received in the past. 
        * Product system or user's setting is preserved. 
 
Program ( Param0.    bit4 ) : Starting state of control program 
    0b: Program was normal and usually began correctly. 
    1b: Program was abnormal and began starting with the backup control software. 
        * After starting in abnormal state, only the update control of program 
            is acceptable. 
*/ 



void parse_system_start(struct SYS_START *p_sys_start, BYTE *states)
{
    p_sys_start->GroupID = states[0];
    p_sys_start->SubID = states[1];
    p_sys_start->Program = (states[2] & 0x10) >> 4;
    p_sys_start->Initial = states[2] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_sysmode_info()
 * Source: 4.1.2 [0C07]
 * Status Description: 
 *      Notification of state information on system. 
 *      This status is voluntarily notified at the state transition of the 
 * system. 
 */

/* Parameter */
/*
Setup ( Param0.    bit0 ) : Setup history of this system 
    0b:  The system has not been started in the past. 
    1b:  The system has been started in the past. 
 
Initial ( Param0.    bit1 ) : State of system start 
    0b:  During the system start setting period    ( "Initialization period" ) 
    1b:  End at system start setting period    ( "Normal operation period" ) 
 
Flash ( Param0.    bit2 ) : Comparison of state of system setting and Flash 
memory maintenance information 
    0b:  The state of the setting and maintenance information are the same. 
    1b:  The state of the setting and maintenance information are different. 
 
TvSystem ( Param0.    bit4 - 5 ) : TV system information 
    00b:  TV system is uncertain. 
    01b: NTSC 
    10b: PAL 
    11b:  State of switching of NTSC and PAL 
 
MediaCont ( Param0.    bit6 ) : State of switching of Media/Contents Mode 
* Each state change information on VCD-PBC 
    0b:  State of switching completion 
    1b:  State when being switching 
 
Slot ( Param1.    bit0 - 1 ) : Disc existence information on slot No.1 
    00b: Uncheck 
    01b:  There is no disc 
    11b:  There is a disc. 

Door ( Param5.    bit0 ) : State of door of mechanism 
    0b: No Informatiojn. 
    1b:  There is no door. 
 
LoadMode ( Param5.  bit3 )  : Information of external factor for Loading (LOADING)   
    0b :  Loading operation is not performed / Loading operation is performed by 
        external factor (Command / PushBack) 
    1b :  Loading operation is performed voluntarily (SelfLoading) 
 
MechanismStatus ( Param7.    All ) : State of mechanism operation 
    00h:  The Eject operation is completed with disc holding at exit. / The tray 
        is not drawn out though there is a Magazine. (EjectWithDisc) 
    01h:  The Eject operation is completed without disc holding at exit. 
        (EjectWithOutDisc / No Disc) 
    02h:  The Eject operation is being executed. (EjectExecute) 
    03h:  Disc is pushed back to mechanism from the state of “EjectEithDisc / 
        EjectWithOutDisc”. (PushBack) 
    04h:  The Load operation is being executed. (LoadExecute) 
    05h:  The Load operation is completed. (Load) 
    0Ah:  Disc check operation is being executed. (DiscCheck) 
    0Eh: The initialization operation is being executed.. (InitExecute) 
    0Fh:  The mechanism operation is given up by the error. (GiveUp) 
    10h:  Disc reading operation is being executed. (DiscRead) 
    11h:  Disc reading operation is ended. (DiscReadEnd) 
 
DiscSpin ( Param8.    bit0 ) : State of spin of disc 
    0b:  State of stop 
    1b:  State of spin 
 
Source ( Param8.    bit2 ) : State of system startup control   
    0b :      State of startup available for this system 
    1b :      State of startup available for other system 
 
ErrorCode1 ( Param10.    bit4 - 7 ) : Classification information on error 
    0h:  There is no error. (NoError) 
    1h:  State of Mechanism error. (MechaError) 
    2h:  State of System error. (SystemError) 

ErrorCode2 ( Param10.    bit0 - 3 ) : Detail information on error 
( ErrorCode1 = NoError ) 
    0h:  There is no error. 
( ErrorCode1 = MechaError ) 
    1h:  The error occurred while Eject was being operated or the transport 
        position was shifting. 
    4h:  The error occurred while operating Load. 
    5h:  The disc cannot be detected. 
  ( ErrorCode1 = SystemError ) 
    1h:  The error occurred in the internal processing. (servo error and timer 
        error, etc.) 
        * Error that needs reset processing on HOST side 
    2h:  The TV system error occurred. 
    3h:  The regional management error occurred. 
    Fh:  The illegal operation error of software occurred. (Restoration is being 
        processed by self-reset.) 
        * The state after mechanism recovers this error is the same as the state 
        of SET_END is executed. 
 
MediaErrorCode1 ( Param11.    bit4 - 7 ) : Classification information on error 
    0h:  There is no error. (NoError) 
    3h:  State of Medhia error. (MediaError) 
 
MediaErrorCode2 ( Param11.    bit0 - 3 ) : Detail information on error 
( ErrorCode1 = NoError ) 
    0h:  There is no error. 
( ErrorCode1 = MediaError ) 
    1h:  Unsupported disc was detected. 
    2h:  An illegal disc on the copyright protection was detected. 
    5h:  The data error occurred. (Read error/Input data error) 
    9h: Overcurrent error
*/



void parse_sysmode_info(struct SYSMODE_INFO *p_sysmode_info, BYTE *states)
{
    p_sysmode_info->GroupID = states[0];
    p_sysmode_info->SubID = states[1];
    p_sysmode_info->MediaCont = (states[2] & 0x40) >> 6;
    p_sysmode_info->TvSystem = (states[2] & 0x30) >> 4;
    p_sysmode_info->Flash = (states[2] & 0x04) >> 2;
    p_sysmode_info->Initial = (states[2] & 0x02) >> 1;
    p_sysmode_info->Setup = states[2] & 0x01;
    p_sysmode_info->Slot = states[3] & 0x3;
    p_sysmode_info->LoadMode = (states[7] & 0x08) >> 3;
    p_sysmode_info->Door = states[7] & 0x01; 
    p_sysmode_info->MechaStatus = states[9];
    p_sysmode_info->Source = (states[10] & 0x04) >> 2;
    p_sysmode_info->DiscSpin = states[10] & 0x01;
    p_sysmode_info->ErrorCode1 = (states[12] & 0xF0) >> 4;
    p_sysmode_info->ErrorCode2 = states[12] & 0x0F;
    p_sysmode_info->MediaErrorCode1 = (states[13] & 0xF0) >> 4;
    p_sysmode_info->MediaErrorCode2 = states[13] & 0x0F;
}

/* ------------------------------------- */
/* Name: parse_set_resp()
 * Source: 4.1.3 [0C0A]
 * Status Description: 
 *      Notification of completion of demand for processing to setting change 
 * demand by SET_TYPE (Refer to the command), SET_MODEL (Refer to the command), 
 * and SET_MODEL_TYPE (Refer to the command). 
 *      This status is voluntarily notified when the setting change processing 
 * ends normally. 
 */

/* Parameter */
/*
SetGroupID ( Param0.    All ) : Group ID of command that setting process is 
completed 
    01 - FFh:  Command Group ID 
 
SetSubID ( Param1.    All ) : Group Sub ID of command that setting process is 
completed 
    01- 02,12h:     Command Group Sub ID 
        *01h:  SET_TYPE Command 
        *02h:  SET_MODEL Command 
        *12h:  SET_MODEL_TYPE Command 
*/ 



void parse_set_resp(struct SET_RESP *p_set_resp, BYTE *states)
{
    p_set_resp->GroupID = states[0];
    p_set_resp->SubID = states[1];
    p_set_resp->SetGroupID = states[2];
    p_set_resp->SetSubID = states[3];
}

/* ------------------------------------- */
/* Name: parse_cmd_act_status_info()
 * Source: 4.1.4 [0C0E]
 * Status Description: 
 *      Notification of execution situation correspond to received command. 
 *      This status is voluntarily notified at the state transition of the 
 * execution processing. 
 */

/* Parameter */
/*
ActGroupID ( Param0.    All ) : Group ID of command under processing 
    01 - FFh:    Command Group ID 
 
ActSubID ( Param1.    All ) : Group Sub ID of command under processing 
    01 - FFh:    Command Group Sub ID 
 
ActStatus ( Param2.    All ) : Execution situation of processing 
    00h:  Execution End of correspondence processing 
    01h:  Execution Start of correspondence processing 
*/ 



void parse_cmd_act_status_info(struct CMD_ACT_STATUS_INFO *p_cmd_act_status_info, BYTE *states)
{
    p_cmd_act_status_info->GroupID = states[0];
    p_cmd_act_status_info->SubID = states[1];
    p_cmd_act_status_info->ActGroupID = states[2];
    p_cmd_act_status_info->ActSubID = states[3];
    p_cmd_act_status_info->ActStatus = states[4];
}

/* ------------------------------------- */
/* Name: parse_set_type_info()
 * Source: 4.2.1 [8003]
 * Status Description: 
 *      Notification of information concerning present basic setting value.
 */

/* Parameter */
/* Each parameter value is same with definition of SET_TYPE */



void parse_set_type_info(struct SET_TYPE_INFO *p_set_type_info, BYTE *states)
{
    p_set_type_info->GroupID = states[0];
    p_set_type_info->SubID = states[1];
    p_set_type_info->ModelType = states[2];
    p_set_type_info->Dest = states[3];
    p_set_type_info->Mecha = states[4];
}

/* ------------------------------------- */
/* Name: parse_set_model_info()
 * Source: 4.2.2 [8004]
 * Status Description: 
 *      Notification of information concerning present basic setting value. 
 */

/* Parameter */
/* Each parameter value is same with definition of SET_ MODEL
*/



void parse_set_model_info(struct SET_MODEL_INFO *p_set_model_info, BYTE *states)
{
    p_set_model_info->GroupID = states[0];
    p_set_model_info->SubID = states[1];
    p_set_model_info->HiTempControl = states[2];
    p_set_model_info->LowTempControl = states[3];
    p_set_model_info->OSD = states[4];
    p_set_model_info->StForm = (states[5] & 0xC0) >> 6;
    p_set_model_info->LrckFs = (states[5] & 0x38) >> 3;
    p_set_model_info->DacQb = (states[5] & 0x06) >> 1;
    p_set_model_info->SpdifOut = states[5] & 0x01;
    p_set_model_info->Component = (states[6] & 0x04) >> 2;
    p_set_model_info->YC = (states[6] & 0x02) >> 1;
    p_set_model_info->Composit = states[6] & 0x01;
    p_set_model_info->TextFirstChar = states[7];
    p_set_model_info->TextSecondChar = states[8];
    p_set_model_info->Size8Disc = (states[9] & 0x02) >> 1;
    p_set_model_info->FullEject = states[9] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_disc_info()
 * Source: 4.3.1 [0E01]
 * Status Description: 
 *      Notification of information concerning disc that has been identified. 
 *      This status is voluntarily notified when the disc is identified. 
 *      Moreover, the information format is decided by the contents that
 * recorded on the disc. 
 */


/* SetMediaType : CDDA */
/* 
Text ( Param5.    bit0 ) : Presence of Text Data. 
    0b:  Text Data is not recorded. 
    1b:  Text Data is recorded. 
 
AFormat ( Param5.    bit4 ) : Audio format 
    0b: CD-DA 
    1b: DTS-CD 
 
StartTrackNo ( Param6.    All ) : Start Track Number 
    01 - 63h:    Track No. ”1 - 99” 
 
EndTrackNo ( Param7.    All ) : End Track Number 
    01 - 63h:    Track No. “1 – 99” 
 
TimeMinute ( Param8.    All ) : Total Replay Time of Disc (minute) 
    * The Total Replay Time is indicated by combining ”TimeMinute”,”TimeSecond” 
        and “TimeFrame”. 
    00 - 63h:    Total replay time “0 - 99 minute” 
 
TimeSecond ( Param9.    All ) : Total Replay Time of Disc (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
 
TimeFrame ( Param10.    All ) : Total Replay Time of Disc (frame) 
    00 - 4Ah:    Total replay time “0 - 74 frame”
*/ 



/* SetMediaType : VCD */
/* 
Psd ( Param5.    bit0 ) : Presence of PSD (Play Sequence Descriptor) Information 
        * Necessary information for PBC (PlayBack Control) control 
    0b:  PSD is not recorded. 
    1b:  PSD is recorded. 
 
VFormat ( Param5.    bit4 ) : VCD format 
    0b: VCD 
    1b: SVCD 
 
Version1 ( Param6.    bit4 - 7 ) : VCD version number (Integer part) 
Version2 ( Param6.    bit0 - 3 ) : VCD version number (Decimal part) 
    0 - 9h:  Version number value “0 – 9” 
        * The Version number is indicated by combining “Version1” and “Version2”. 
        * The version number is shown as " 00 - 99h  ⇒ Ver.0.0 - 9.9 ". 
 
EndTrackNo ( Param7.    All ) : End Track Number 
    01 - 63h:    Track No. ”1 - 99” 
 
TimeMinute ( Param8.    All ) : Total Replay Time of Disc (minute) 
        * The Total Replay Time is indicated by combining ”TimeMinute”,
            ”TimeSecond” and “TimeFrame”. 
    00 - 63h:    Total replay time “0 - 99 minute” 
 
TimeSecond ( Param9.    All ) : Total Replay Time of Disc (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
 
TimeFrame ( Param10.    All ) : Total Replay Time of disc (frame) 
    00 - 4Ah:    Total replay time “0 - 74 frame” 
*/ 


/* SetMediaType : COMPRESS */
/* 
AudioFile ( Param5.    bit1 ) : Presence of Audio File to replay. 
        * The MP3 / WMA / WAV File are included. 
    0b:  The pertinent file is not recorded. 
    1b:  The pertinent file is recorded. 
 
PlayList ( Param5.    bit2 ) : Presence of PlayList File. 
    0b:  The pertinent file is not recorded. 
    1b:  The pertinent file is recorded. 
 
FileSystemType ( Param5.    bit4 - 7 ) : Volume composition type of File System 
    0h: Unknown. 
    1h:  Primary Volume Descriptor (PVD) 
    2h:  Supplementary Volume Descriptor (SVD Ver. uncertainty) 
    3h:  Supplementary Volume Descriptor (SVD Ver.1.0) 
    4h:  Supplementary Volume Descriptor（There is no “SVD Escape Sequences” Information） 
    5h:  Universal Disc Format (UDF Ve r. uncertainty) 
    6h:  Universal Disc Format (UDF Ver.1.02) 
    7h:  Universal Disc Format (UDF Ver.1.50) 
    8h:  Universal Disc Format (UDF Ver.2.00) 
    9h:  Universal Disc Format (UDF Ver.2.01) 
    Ah:  Universal Disc Format (UDF Ver.2.50) 
 
FolderNs ( Param6 - 7.    All ) : Total of FOLDER on Disc 
    0000 - 0100h:  Total of Folder “0 - 256” 
        * The number of folders that this system can identify is 256. 
 
FileNs ( Param8 - 9.    All ) : Total of FILE on Disc 
    0001 - 1000h:  Total of File “1 - 4096” 
        * The number of files that this system can identify is 4096. 
*/ 



/* SetMediaType : DVD-V */
/* 
TVSystem ( Param5.    bit0 - 1 ) : TV System 
    01b: NTSC. 
    10b: PAL. 
 
Jacket ( Param5.    bit2 ) : Presence of Jacket Picture File. 
    0b:  The pertinent file is not recorded. 
    1b:  The pertinent file is recorded. 
 
Text ( Param5.    bit3 ) : Presence of Text Data 
    0b:  Text Data is not recorded. 
    1b:  Text Data is recorded. 
 
Parental ( Param5.    bit4 ) : Presence of Parental Control Information. 
    0b:  Control Information is not recorded. 
    1b:  Control Information is recorded. 
 
TTMenu ( Param5.    bit5 ) : Presence of Title Menu 
    0b:  Title Menu is not recorded. 
    1b:  Title Menu is recorded. 
*/ 
 


/* SetMediaType : UPDATE */
/* SecterType ( Param5.    All ) : Type of the information recorded area on disc 
    00h:  The sector type is unknown. 
    02h:  It is recorded in the User data of YellowBook in 2048 bytes. 
    03h:  It is recorded in the User data of YellowBook in 2336 bytes. 
    04h:  It is recorded in the User data of GreenBook in 2048 bytes. 
    05h:  It is recorded in the User data of GreenBook in 2336 bytes. 
 
   UpdateFileNs ( Param7.    All ) : Total of Program File on Disc that can be Updated 
    00 - FFh:    Total of Update Program File “0 - 255” 
*/ 



/* Parameter */
/*
PhysicalMedia ( Param1.    bit0 - 6 ) : Media type 
    00h:  There is no disc. 
        * Information after Param2 are all invalid. (All 0) 
    01h: CD-DA disc 
    02h: CD-ROM disc 
    03h: Enhanced-CD disc 
    04h: Mixed-CD disc 
    21h: DVD-ROM disc 
    22h:  DVD-R (General) disc 
    23h:  DVD-R (General / Authoring) disc 
    24h: DVD-RW disc 
    25h: DVD-RAM disc 
    26h: DVD+R disc 
    27h: DVD+RW disc 
    7Fh: Unknown disc 
        * Information after Param2 are all invalid. (All 0) 
     

StsType ( Param1.    bit7 ) : Range of this information targets 
    0b:  Information about media. 
        * Information after Param4 are all invalid. (All 0) 
    1b:  Information about media and contents. 
 
CDDA ( Param2.    bit0 ) : Presence of CD-DA contents as disc data. 
VCD ( Param2.    bit1 ) : Presence of VCD contents as disc data 
DATA ( Param2.    bit2 ) : Presence of DATA(Compress) contents as disc data 
Update ( Param2.    bit7 ) : Presence of Program Update contents as disc data 
DVDV ( Param3.    bit0 ) : Presence of DVD-Video contents as disc data 
    0b:  The data is not recorded. 
    1b:  The data is is recorded. 
 
SetMediaType ( Param4.    All ) : Contents on disc that this information targets 
        * Contents that information targets after Param5. 
        * One of the contents that Param 2-3 marked as "The data is recorded" is targeted. 
    00h:  There is no contents information. (Invalid) 
        * Information after Param5 are all invalid. (All 0) 
    01h:  Information on CD-DA. (CDDA) 
    02h:  Information on VCD. (VCD) 
    03h:  Information on DATA. (COMPRESS) 
    11h:  Information on DVD-Video. (DVD-V) 
    21h: Information on Program Update Data. (UPDATE) 
*/ 



void parse_disc_info(struct DISC_INFO *p_disc_info, BYTE *states)
{
    p_disc_info->GroupID = states[0];
    p_disc_info->SubID = states[1];

    /* Information about media. */
    p_disc_info->StsType = (states[3] & 0x80) >> 7;
    if (p_disc_info->StsType == 0)
        return;

    /* No disc or Unknown disc. */
    p_disc_info->PhyMedia = states[3] & 0x7F;
    if (p_disc_info->PhyMedia == 0 || p_disc_info->PhyMedia == 0x7F)
        return;

    p_disc_info->Update = (states[5] & 0x80) >> 7;
    p_disc_info->DATA = (states[5] & 0x04) >> 2;
    p_disc_info->VCD = (states[5] & 0x02) >> 1;
    p_disc_info->CDDA = states[5] & 0x01;

    p_disc_info->SetMediaType = states[6];
        
    /* There is no contents information. (Invalid) */
    if (p_disc_info->SetMediaType == 0x00)
        return;

    /* Information on CD-DA contents. */
    if (p_disc_info->SetMediaType == 0x01) {
        p_disc_info->CDDA_block.AFormat = (states[7] & 0x10) >> 4;
        p_disc_info->CDDA_block.Text = states[7] & 0x01;
        p_disc_info->CDDA_block.StartTrackNo = states[8];
        p_disc_info->CDDA_block.EndTrackNo = states[9];
        p_disc_info->CDDA_block.TimeMinute = states[10];
        p_disc_info->CDDA_block.TimeSecond = states[11];
        p_disc_info->CDDA_block.TimeFrame = states[12];
    }

    /* Information on VCD contents. */
    if (p_disc_info->SetMediaType == 0x02) {
        p_disc_info->VCD_block.VFormat = (states[7] & 0x10) >> 4;
        p_disc_info->VCD_block.Psd = states[7] & 0x01;
        p_disc_info->VCD_block.Version1 = (states[8] & 0xF0) >> 4;
        p_disc_info->VCD_block.Version2 = states[8] & 0x0F;
        p_disc_info->VCD_block.TrackNs = states[9];
        p_disc_info->VCD_block.TimeMinute = states[10];
        p_disc_info->VCD_block.TimeSecond = states[11];
        p_disc_info->VCD_block.TimeFrame = states[12];
    }

    /* Information on DATA (Compress File) contents. */
    if (p_disc_info->SetMediaType == 0x03) {
        p_disc_info->DATA_block.FileSystemType = (states[7] & 0xF0) >> 4;
        p_disc_info->DATA_block.PlayList = (states[7] & 0x04) >> 2;
        p_disc_info->DATA_block.AudioFile = (states[7] & 0x02) >> 1;
        p_disc_info->DATA_block.FolderNs = (WORD(states[8]) << 7) 
                                         + states[9];
        p_disc_info->DATA_block.FileNs = (WORD(states[10]) << 7)
                                       + states[11];
        p_disc_info->DATA_block.TimeMinute = states[10];
        p_disc_info->DATA_block.TimeSecond = states[11];
        p_disc_info->DATA_block.TimeFrame = states[12];
    }

    /* Information on DVD-Video contents. */
    if (p_disc_info->SetMediaType == 0x11) {
        p_disc_info->DVDV_block.SRM = (states[7] & 0x40) >> 6;
        p_disc_info->DVDV_block.TTMenu = (states[7] & 0x20) >> 5;
        p_disc_info->DVDV_block.Parental = (states[7] & 0x10) >> 4;
        p_disc_info->DVDV_block.Text = (states[7] & 0x08) >> 3;
        p_disc_info->DVDV_block.Jacket = (states[7] & 0x04) >> 2;
        p_disc_info->DVDV_block.TVSystem = states[7] & 0x03;
        p_disc_info->DVDV_block.TTNs = states[8];
        p_disc_info->DVDV_block.EndAddress = (DWORD(states[9]) << 14)
                                           + (DWORD(states[10]) << 7)
                                           + states[11];
    }

    /* Information on Program Update Disc contents. */
    if (p_disc_info->SetMediaType == 0x21) {
        p_disc_info->UPDATE_block.SecterType = states[7];
        p_disc_info->UPDATE_block.UpdateFileNs = states[9];
    }
 
}

/* ------------------------------------- */
/* Name: parse_firstPosition_info()
 * Source: 4.3.2 [0E02]
 * Status Description: 
 *      Notification of information concerning the First Position section in 
 * present replay contents. 
 *      The definition of first position section for each contents is as follows. 
            CD-DA    : There is no object. (This status does not supports) 
            VCD    : There is no object. (This status does not supports) 
            COMPRESS : Folder  
            DVD-Video : Title 
 *      This status is voluntarily notified by the change in the first position 
 * that replay. 
 *      Moreover, the information format is decided by contents recorded on the 
 * media. 
 */

/* parameter */
/* 
TitleType ( Param4.    bit0 ) : Type of Title (PGC) 
    0b:  It is One Sequential PGC. 
    1b:  It is not One Sequential PGC / Unknown / unused. 
 
Parental ( Param4.    bit1 ) : Presence of Parental control 
    0b:  It is not Parental Block / Unknown / unused. 
    1b:  It is Parental Block. 
 
Karaoke ( Param4.    bit2 ) : Presence of KARAOKE control 
    0b:  It is not KARAOKE Title / Unknown / unused. 
    1b:  It is KARAOKE Title. 
 
DisplayMode ( Param4.    bit3 - 4 ) : Aspect ratio of Display 
    00b:  4:3 / Unknown / unused. 
    01b:  16:9 (Pan-scan and Letterbox) 
    10b:  16:9 (Pan-scan) 
    11b:  16:9 (Letterbox) 
 
RootMenu ( Param4.    bit5 ) : Presence of Root Menu 
    0b:  Root Menu is not recorded. 
    1b:  Root Menu is recorded. 
 
TimeHour ( Param5.    All ) : Total Replay Time of this Title (hour) 
        * The Total Replay Time is indicated by combining “TimeHour”,
            ”TimeMinute” and ”TimeSecond”. 
    00 - 63h:    Total replay time “0 - 99 hour” 
 
TimeMinute ( Param6.    All ) : Total Replay Time of this Title (minute) 
    00 - 3Bh:    Total replay time “0 - 59 minute” 
 
TimeSecond ( Param7.    All ) : Total Replay Time of this Title (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
 
AstNs ( Param8.    All ) : Number of effective Audio Streams 
    00 - 08h:    Audio Stream “0 - 8 streams” 
 
SPstNs ( Param9.    All ) : Number of effective Sub-picture Streams 
    00 - 20h:    Sub-picture Stream “0 - 32 streams” 
 
AgNs ( Param10.    All ) : Number of effective Angles 
    00 - 09h:    Angle “0 - 9 angle” 
*/ 


/* Parameter */
/* 
FirstPositionNo ( Param0 - 1.    All ) : The First Position Number of present 
    replay position 
    0001 - 0100h:  Folder No. “1 - 256”    (COMPRESS) 
        * Route layer is corresponded to 0001h. 
    0001 - 0063h:  Title No. “1 - 99”    (DVD-Video) 
 
SecondPositionNs ( Param2 - 3.    All ) : Total of Second Position included in 
    present First Position 
    0001 - 1000h:  Total of File “1 - 4096”       (COMPRESS) 
    0001 - 03E7h:  Total of Chapter (PTT) ”1 - 999”      (DVD-Video) 

As for the following parameters, the format is selected by "SetMediaType" 
information content of “DISC_INFO” status. 
*/ 


void parse_firstposition_info(struct FIRSTPOSITION_INFO *p_firstposition_info, BYTE *states, BYTE SetMediaType)
{
    p_firstposition_info->GroupID = states[0];
    p_firstposition_info->SubID = states[1];
    p_firstposition_info->FirstPositionNo = (WORD(states[2]) << 7) 
                                          + states[3];
    p_firstposition_info->SecondPositionNs = (WORD(states[4]) << 4)
                                           + states[5];
    

    /* Information on present replay Folder section in COMPRESS. */
    if (SetMediaType == 0x03)
        return;

    /* Information on present replay Title section in DVD-Video. */
    if (SetMediaType == 0x11) {
        p_firstposition_info->DVDV_block.RootMenu = (states[6] & 0x20) >> 5;
        p_firstposition_info->DVDV_block.DisplayMode = (states[6] & 0x18) >> 3;
        p_firstposition_info->DVDV_block.Karaoke = (states[6] & 0x04) >> 2;
        p_firstposition_info->DVDV_block.Parental = (states[6] & 0x02) >> 1;
        p_firstposition_info->DVDV_block.TitleType = states[6] & 0x01;
        p_firstposition_info->DVDV_block.TimeHour = states[7];
        p_firstposition_info->DVDV_block.TimeMinute = states[8];
        p_firstposition_info->DVDV_block.TimeSecond = states[9];
        p_firstposition_info->DVDV_block.AstNs = states[10];
        p_firstposition_info->DVDV_block.SPstNs = states[11];
        p_firstposition_info->DVDV_block.AgNs = states[12];
    }
 
}

/* ------------------------------------- */
/* Name: parse_secondposition_info()
 * Source: 4.3.3 [0E03]
 * Status Description: 
 *      Notification of information concerning the Second Position section in 
 * present replay contents. 
 *      The definition of the second position section for each contents is as 
 * follows. 
        CD-DA  : Track  
        VCD  : Track  
        COMPRESS : File   
        DVD-Video  : Chapter (PTT) 
 *      This status is voluntarily notified by the change in the second position 
 * that replay. 
 *      Moreover, the information format is decided by contents recorded on the 
 * media. 
 */

/* DISC_INFO . SetMediaType : CDDA */
/*
TimeMinute ( Param2.    All ) : Total Replay Time of this Track (minute) 
    * The Total Replay Time is indicated by  combining ”TimeMinute” and ”TimeSecond”. 
    00 - 63h:    Total replay time “0 - 99 minute” 
 
    TimeSecond ( Param3.    All ) : Total Replay Time of this Track (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
*/



/* DISC_INFO . SetMediaType : VCD */
/*
TrackType ( Param2.    All ) : Type of Track 
    00h:  Track type is unknown. 
    01h:  Mpeg Data Track. 
    02h: CD-DA Track. 
 
TimeMinute ( Param3.    All ) : Total Replay Time of this Track (minute) 
    * The Total Replay Time is indicated by  combining ”TimeMinute” and ”TimeSecond”. 
    00 - 63h:    Total replay time “0 - 99 minute” 
 
TimeSecond ( Param4.    All ) : Total Replay Time of this Track (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
*/ 



/* DISC_INFO . SetMediaType : COMPRESS */
/*
FileMediaType ( Param2 - 5.    All ) : Media type of this Track 
    00000000h:    File type is unknown. 
    00000002h:   MP3 File. 
    00000004h:   WMA File. 
    00000010h:   WAV File. 
 
Format ( Param6.    bit0 ) : Correspondence of file format 
    0b:  Format that can be reproduced. 
    1b:  Format that cannot be reproduced. 
 
BitType ( Param6.    bit1 ) : Type of Bit Rate 
    0b:  Constant Bit Rate. 
    1b:  Variable Bit Rate. 
 
VideoType ( Param6.    bit2 - 3 ) : Picture size of Video File. 
    00b:  There is no Picture (Audio File). 
    11b:  Information is uncertain.. 
        * When the number of partitions of the file is outside correspondence. 
 
TimeHour ( Param8.    All ) : Total Replay Time of this File (hour) 
        * The Total Replay Time is indicated by combining “TimeHour”,”TimeMinute” 
            and ”TimeSecond”. 
    00 - 63h:    Total replay time “0 - 99 hour” 
 
TimeMinute ( Param9.    All ) : Total Replay Time of this File (minute) 
    00 - 3Bh:    Total replay time “0 - 59 minute” 
 
TimeSecond ( Param10.    All ) : Total Replay Time of this File (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
 
FPS ( Param11 - 12.    All ) : Number of Frames per one second 
    0000 - FFFEh:    FPS value “0 - 65.534” 
        *Number of Frame per one second = devide FPS value by 1000 
    FFFFh:         FPS value “more than 65.535” 
*/



/* DISC_INFO . SetMediaType : DVD-V */
/*
TimeHour ( Param2.    All ) : Total Replay Time of this Chapter (hour) 
        * The Total Replay Time is indicated by combining “TimeHour”,”TimeMinute” 
            and ”TimeSecond”. 
    00 - 63h:    Total replay time “0 - 99 hour” 
 
TimeMinute ( Param3.    All ) : Total Replay Time of this Chapter (minute) 
    00 - 3Bh:    Total replay time “0 - 59 minute” 
 
TimeSecond ( Param4.    All ) : Total Replay Time of this Chapter (second) 
    00 - 3Bh:    Total replay time “0 - 59 second” 
*/ 



/* Parameter */
/*
SecondPositionNo ( Param0 - 1.    All ) : The Second Position Number of present 
replay position 
    0001 - 0063h:  Track No. “1 - 99”      (CD-DA) 
    0001 - 0063h:  Track No. “1 - 99”      (VCD) 
    0001 - 1000h:  File No. “1 - 4096”      (COMPRESS) 
        * File number in folder. 
    0001 - 03E7h:  Chapter (PTT) No. “1 - 999”    (DVD-Video) 
 
    As for the following parameters, the format is selected by "SetMediaType" 
information content of “DISC_INFO” status. 
*/ 



void parse_secondposition_info(struct SECONDPOSITION_INFO *p_secondposition_info, BYTE *states, BYTE SetMediaType)
{
    p_secondposition_info->GroupID = states[0];
    p_secondposition_info->SubID = states[1];
	p_secondposition_info->SecondPositionNo = (states[2]<<8) | states[3];
    /* Information on present replay Track section in CD-DA. */
    if (SetMediaType == 0x01) {
        p_secondposition_info->CDDA_block.TimeMinute = states[4];
        p_secondposition_info->CDDA_block.TimeSecond = states[5];
    }

    /* Information on present replay Track section in VCD. */    
    if (SetMediaType == 0x02) {
        p_secondposition_info->VCD_block.TrackType = states[4];
        p_secondposition_info->VCD_block.TimeMinute = states[5];
        p_secondposition_info->VCD_block.TimeSecond = states[6];
    }

    /* Information on present replay File section in COMPRESS. */
    if (SetMediaType = 0x03) {
        p_secondposition_info->DATA_block.FileMediaType = (DWORD(states[4]) >> 21)
                                                        + (DWORD(states[5]) >> 14)
                                                        + (DWORD(states[6]) >> 7)
                                                        + states[7];
        p_secondposition_info->DATA_block.VideoType = (states[8] & 0x0C) >> 2;
        p_secondposition_info->DATA_block.BitType = (states[8] & 0x02) >> 1;
        p_secondposition_info->DATA_block.Format = states[8] & 0x01;
        p_secondposition_info->DATA_block.TimeHour = states[10];
        p_secondposition_info->DATA_block.TimeMinute = states[11];
        p_secondposition_info->DATA_block.TimeSecond = states[12];
        p_secondposition_info->DATA_block.FPS = (states[13] << 7)
                                              + states[14];
    }

    /* Information on present replay Chapter (PTT) section in DVD-Video. */
    if (SetMediaType = 0x11) {
        p_secondposition_info->DVDV_block.TimeHour = states[4];
        p_secondposition_info->DVDV_block.TimeMinute = states[5];
        p_secondposition_info->DVDV_block.TimeSecond = states[6];
    }


}

/* ------------------------------------- */
/* Name: parse_domain_info()
 * Source: 4.3.4 [0E04]
 * Status Description: 
 *      Notification of information concerning classification of replay position 
 * in present replay contents. 
 *      This status is voluntarily notified by the change in the classification 
 * of the replay position. 
 *      Moreover, the information format is decided by contents recorded on the 
 * media. 
 */

/* MediaType : Invalid */
/* 
DomainType ( Param1.    All ) : Division of state (undefined) 
ControlType ( Param2.    All ) : State of control (undefined) 
    00h:  undefined. 
*/

/* MediaType : CDDA */
/*
DomainType ( Param1.    All ) : Division of state 
    00h:  unknown / State of read standby (state of replay standby)   
    01h:  State of stop 
    02h: State of Track replay 
 
ControlType ( Param2.    All ) : State of control (undefined) 
    00h:  undefined.
*/

/* MediaType : VCD */
/*
DomainType ( Param1.    All ) : Division of state 
    00h:  unknown / State of read standby (state of replay standby)   
    01h:  State of stop 
    02h: State of Track replay 
    03h:  State of SelectionList replay (PBC ON) 
    04h:  State of PlayList replay (PBC ON) 
 
ControlType ( Param2.    All ) : State of control (PBC) 
    00h:  PBC (Play Back Control) OFF 
    01h:  PBC (Play Back Control) ON 
*/

/*  MediaType : Compress */
/*
DomainType ( Param1.    All ) : Division of state 
    00h:  unknown / State of read standby (state of replay standby)   
    01h:  State of stop 
    02h:  State of MP3/WMA/WAV File replay (File without Video) 
 
ControlType ( Param2.    All ) : State of control (File identification in Disc) 
    01h:  Only the Compress-Audio File that available to replay is identified. 
    02h:  All File is identified. 
*/

struct STRUCT_MEDIATYPE {
};


/* MediaType : DVD-V */
/*
DomainType ( Param1.    All ) : Division of state 
    00h:  unknown / State of read standby (state of replay standby)   
    01h:  State of stop 
    02h:  State of First Play PGC replay 
    03h:  State of VMGM Domain replay 
    04h:  State of VTSM Domain replay 
    05h:  State of Title Domain replay 
 
ControlType ( Param2.    All ) : State of control (Menu replay) 
    00h:  Excluding state of the Menu replay 
    01h:  State of Title Menu replay 
    02h:  State of Root Menu replay 
    03h:  State of Sub-picture Menu replay 
    04h:  State of Audio Menu replay 
    05h:  State of Angle Menu replay 
    06h:  State of PTT Menu replay 
 
MLangCode ( Param3 - 4.    All ) : Menu Language Code 
    0000h:       Excluding state of the Menu replay 
    0000 - FFFFh:    Menu Language Code Value 
       * The Code value follows ISO639. 
*/

    

/* Parameter */
/*
MediaType ( Param0.    All ) : Type of present replay contents 
    00h: The contents type is unknown. (Invalid) 
    01h: CD-DA. (CDDA) 
    02h: VCD. (VCD) 
    03h: COMPRESS. (COMPRESS) 
    11h: DVD-Video. (DVD-V) 
 
As for the following parameters, the format is selected by the information content of “MediaType”. 
*/ 



void parse_domain_info(struct DOMAIN_INFO *p_domain_info, BYTE *states)
{
    p_domain_info->GroupID = states[0];
    p_domain_info->SubID = states[1];
    p_domain_info->MediaType = states[2];

    /* Information on replay classification of present unknown/CD-DA/VCD/DATA contents. */
    if ((p_domain_info->MediaType == 0x00)
        || (p_domain_info->MediaType = 0x01)
        || (p_domain_info->MediaType = 0x02)
        || (p_domain_info->MediaType = 0x03)) {
        p_domain_info->DomainType = states[4];
        p_domain_info->ControlType = states[5];
    }

    /* Information on replay classification of present DVD-Video replaying. */
    if (p_domain_info->MediaType == 0x11) {
        p_domain_info->mediatype_dvdv_block.MLangType = (WORD(states[5]) << 7)
                                                      + states[6];
    }
}

/* ------------------------------------- */
/* Name: parse_play_info()
 * Source: 4.4.1 [0F01]
 * Status Description: 
 *      Notification of information concerning present replay operation. 
 *      This status is voluntarily notified by the change in the replay operation. 
 */

/* Parameter */
/*
PlayMode ( Param0.    All ) : Present state of replay 
    00h:  It is not a state of replay. (NotPlay) 
    01h:  State of standby for replay. (Standby) 
    02h:  State of stop. (PPM Information is cleared) (Stop) 
    03h:  State of stop. (PPM Information is remained) (PreStop) 
    04h:  State of replay. (Play) 
    05h:  State of pause. (Pause) 
    06h:  State of still picture replay. (Still) 
    08h:  State of one step replay to forward direction. (StepForward) 
    09h:  State of one step replay to Backward direction. (StepBackward) 
    0Ah:  State of fast replay to forward direction. (FastForward) 
    0Bh:  State of fast replay to Backward direction. (FastBackward) 
    0Ch:  State of slow replay to forward direction. (SlowForward) 
    0Dh:  State of slow replay to Backward direction. (SlowBackward) 
    10h:  State of search execution. (Search) 
 
Speed ( Param1.    All ) : Replay operation speed (PlayMode = Fast/Slow) 
    00h:  It is not an variable speed replay (PlayMode≠Fast Forward / Fast Backward / Slow Forward / Slow Backward) 
    02h:  ×2 speed (PlayMode = Fast Forward / Fast Backward) 
    03h:  ×3 speed (PlayMode = Fast Forward / Fast Backward) 
    04h:  ×4 speed (PlayMode = Fast Forward / Fast Backward) 
    08h:  ×8 speed (PlayMode = Fast Forward / Fast Backward) 
    0Ah:  ×10 speed (PlayMode = Fast Forward / Fast Backward) 
    10h:  ×16 speed (PlayMode = Fast Forward / Fast Backward) 
    15h:  ×21 speed (PlayMode = Fast Forward / Fast Backward) 
    20h:  ×32 speed (PlayMode = Fast Forward / Fast Backward) 
    02h:  ×1/2 speed (PlayMode = Slow Forward / Slow Backward) 
    04h:  ×1/4 speed (PlayMode = Slow Forward / Slow Backward) 
    08h:  ×1/8 speed (PlayMode = Slow Forward / Slow Backward) 
    10h:  ×1/16 speed (PlayMode = Slow Forward / Slow Backward) 
 
StandbyMode ( Param2.    All ) : Factor of Standby (PlayMode = Standby) 
    00h:  It is not a state of Standby (PlayMode≠Standby). 
    01h:  Factor is “Reading end of the disc”. 
    02h: Factor is “PlayList read end”. 
    10h:  Factor is “Reach the head of the Disc”. 
    11h:  Factor is “Reach the end of the Disc”. 
    20h:  Factor is “Reach the head of the First Position”. 
    21h:  Factor is “Reach the end of the First Position”. 
    30h:  Factor is “Reach the head of the Second Position”. 
    31h:  Factor is “Reach the end of the Second Position”. 
    80h:  Factor is “End of the search operation”. 
    90h:  Factor is “Reach the replay non-correspondence File”. 
    91h:  Factor is “Reaches the partitions number non-correspondence File”. 
 
StopMode ( Param3.    All ) : Factor of Stop (PlayMode = Stop) 
    00h:  It is not a state of Standby (PlayMode≠Stop). 
    01h:  Factor is “Instruction by the command”. 
    02h: Factor is “Instruction by the contents”. 
    03h:  Factor is “Accrual of the Read Error”. 
    04h:  Factor is “There is no pertinent Parental in DVD-Video”. 
    FFh:  Factor is “Other causes”. 


RepeatMode ( Param4.    All ) : Present state of Repeat System Setting 
    00h:  The setting of the Repeat System is OFF. 
    11h: Second Position RPT 
    12h:  First Position RPT 
    13h: Disc RPT 
    21h: Second Position M.I.X. 
    22h:  First Position M.I.X. 
    23h: All M.I.X. 
    31h: Second Position SCAN 
    32h:  First Position SCAN 
    33h: All SCAN 
    41h:  One section replay of Second Position (One Play) 
    42h:  One section replay of First Position (One Play) 
    51h:  A-B RPT (Setting of A point only) 
    52h:  A-B RPT (Setting of A point and B point) 
 
MuteMode ( Param5.    All ) : State of Audio Mute 
    00h:  It is not a state of Audio Mute / It is not a state of Audio Output. 
 * The state of Fast Forward/Fast Backward is contained. 
    01h:  State of Audio Mute by Audio Stream change. 
*/ 



void parse_play_info(struct PLAY_INFO *p_play_info, BYTE *states)
{
    p_play_info->GroupID = states[0];
    p_play_info->SubID = states[1];
    p_play_info->PlayMode = states[2];
    p_play_info->Speed= states[3];
    p_play_info->StandbyMode= states[4];
    p_play_info->StopMode= states[5];
    p_play_info->RepeatMode= states[6];
    p_play_info->MuteMode= states[7];
}

/* ------------------------------------- */
/* Name: parse_media_play_info()
 * Source: 4.4.2 [0F02]
 * Status Description: 
 *      Notification of information concerning replay progress of present replay 
 * contents. 
 *      This status is voluntarily notified by the change in the progress of the 
 * replay.   
 *      Moreover, the information format is decided by contents recorded on the 
 * media. 
 */

/* Parameter */
/*
DiscTimeMinute ( Param0.    All ) : Present Replay Time in range of Disc (minute) 
        * The Present Replay Time is indicated by combining ”DiscTimeMinute” and 
            ”DiscTimeSecond”. 
    00 - 63h:    Present replay time “0 - 99 minute” 
 
DiscTimeSecond ( Param1.    All ) : Present Replay Time in range of Disc (second) 
    00 - 3Bh:    Presetnt replay time “0 - 59 second” 
 
TrackTimeMinute ( Param2.    All ) : Present Replay Time in range of Track (minute) 
        * The Present Replay Time is indicated by combining ”TrackTimeMinute” 
            and ”TrackTimeSecond”. 
    00 - 63h:    Present replay time “0 - 99 minute” 
 
TrackTimeSecond ( Param3.    All ) : Present Replay Time in range of Track (second) 
    00 - 3Bh:    Presetnt replay time “0 - 59 second” 
 
Index ( Param4.    bit0 ) : Present replay Indices Number 
    0b:  Index Number ”0” 
    1b:  Index Number ”1”    (CD-DA) 
    1b:  Index Number ” Excluding 0”  (VCD) 
 
RetryStatus ( Param5.    bit0 ) : Retrying of execution operation 
    0b:  Retrying is not executed. 
    1b:  Retrying is being executed. 
*/ 




/* DISC_INFO . SetMediaType : COMPRESS */
/*
FileTimeHour ( Param0.    All ) : Present Replay Time in range of File (hour) 
        * The Present Replay Time is indicated by combining ”FileTimeHour”,
            ”FileTimeMinute” and ”FileTimeSecond”. 
    00 - 63h:    Present replay time “0 - 99 hour” 
 
FileTimeMinute ( Param1.    All ) : Present Replay Time in range of File (minute) 
    00 - 3Bh:    Present replay time “0 - 59 minute” 
 
FileTimeSecond ( Param2.    All ) : Present Replay Time in range of File (second) 
    00 - 3Bh:    Presetnt replay time “0 - 59 second” 
 
BitrateHi ( Param3.    All ) : Bit Rate 
BitrateLow ( Param4.    All ) : Bit Rate 
    0005 - 0140h:    Bit Rate “5 - 1411 kbps” 
        * Bit Rate is indicated by combining ”BitrateHi” and ”BitrateLow”. 
          * unit : 1 kbps 
          * WAV replay : 1411 kbps 
 
RetryStatus ( Param7.    bit0 ) : Retrying of execution operation 
    0b:  Retrying is not executed. 
    1b:  Retrying is being executed. 
*/


/* DISC_INFO . SetMediaType : DVDV */
/*
PGCTimeHour ( Param0.    All ) : Present Replay Time in range of Title(PGC) (hour) 
        * The Present Replay Time is indicated by combining ”PGCTimeHour”,
            ”PGCTimeMinute” and ”PGCTimeSecond”. 
    00 - 63h:    Present replay time “0 - 99 hour” 
 
PGCTimeMinute ( Param1.    All ) : Present Replay Time in range of Title(PGC) (minute) 
    00 - 3Bh:    Present replay time “0 - 59 minute” 
 
PGCTimeSecond ( Param2.    All ) : Present Replay Time in range of Title(PGC) (second) 
    00 - 3Bh:    Presetnt replay time “0 - 59 second” 
 
PTTTimeHour ( Param3.    All ) : Present Replay Time in range of Chapter(PTT) (hour) 
        * The Present Replay Time is indicated by combining ”PTTTimeHour”,
            ”PTTTimeMinute” and ”PTTTimeSecond”. 
    00 - 63h:    Present replay time “0 - 99 hour” 
 
PTTTimeMinute ( Param4.    All ) : Present Replay Time in range of Chapter(PTT) (minute) 
    00 - 3Bh:    Present replay time “0 - 59 minute” 
 
PTTTimeSecond ( Param5.    All ) : Present Replay Time in range of Chapter(PTT) (second) 
    00 - 3Bh:    Presetnt replay time “0 - 59 second” 
 
BitrateHi ( Param6.    All ) : Bit Rate (integer part) 
BitrateLow ( Param7.    All ) : Bit Rate (fraction part) 
    0000 - 0A63h:    Bit Rate “0 - 10.99 Mbps” 
        * Bit Rate is indicated by combining ”BitrateHi” and ”BitrateLow”. 
            * BitrateHi : 2 digits of integer part : 00 - 0Ah : 0 - 10 Mbps (unit : 1 Mbps) 
            * BitrateLow : 2 digits of fraction part : 00 - 63h : 0 - 990 kbps (unit : 10 kbps) 
 
DiscRestrict ( Param8.    All ) : Limitation of RPT Setting by Disc Specification 
    00h:  There is no limitation. 
    01h:  Interdiction section of RPT operation. 
 
RetryStatus ( Param9.    bit0 ) : Retrying of execution operation 
    0b:  Retrying is not executed. 
    1b:  Retrying is being executed. 
*/


void parse_media_play_info_CDDA_VCD(struct MEDIA_PLAY_INFO *p_media_play_info, BYTE *states, BYTE SetMediaType)
{
    p_media_play_info->GroupID = states[0];
    p_media_play_info->SubID = states[1];

	p_media_play_info->MediaType = SetMediaType;
    /* DISC_INFO . SetMediaType : CDDA / VCD */
    if (SetMediaType == 0x01 || SetMediaType == 0x02) {
        p_media_play_info->media_play_info_CDDA_VCD.DiscTimeMinute = states[2];
        p_media_play_info->media_play_info_CDDA_VCD.DiscTimeSecond = states[3];
        p_media_play_info->media_play_info_CDDA_VCD.TrackTimeMinute = states[4];
        p_media_play_info->media_play_info_CDDA_VCD.TrackTimeSecond = states[5];
        p_media_play_info->media_play_info_CDDA_VCD.Index = states[6];
        p_media_play_info->media_play_info_CDDA_VCD.RetryStatus = states[7];
    }

    /* DISC_INFO . SetMediaType : COMPRESS */
    if (SetMediaType == 0x03) {
        p_media_play_info->media_play_info_DATA.FileTimeHour = states[2];
        p_media_play_info->media_play_info_DATA.FileTimeMinute = states[3];
        p_media_play_info->media_play_info_DATA.FileTimeSecond = states[4];
        p_media_play_info->media_play_info_DATA.DATA_BitrateHi = states[5];
        p_media_play_info->media_play_info_DATA.DATA_BitrateLow = states[6];
        p_media_play_info->media_play_info_DATA.DATA_RetryStatus = states[7];
    }

    /* DISC_INFO . SetMediaType : DVDV */ 
    if (SetMediaType == 0x11) {
        p_media_play_info->media_play_info_DVDV.PGCTimeHour = states[2];
        p_media_play_info->media_play_info_DVDV.PGCTimeMinute = states[3];
        p_media_play_info->media_play_info_DVDV.PGCTimeSecond = states[4];
        p_media_play_info->media_play_info_DVDV.PTTTimeHour = states[5];
        p_media_play_info->media_play_info_DVDV.PTTTimeMinute = states[6];
        p_media_play_info->media_play_info_DVDV.PTTTimeSecond = states[7];
        p_media_play_info->media_play_info_DVDV.DVDV_BitrateHi = states[8];
        p_media_play_info->media_play_info_DVDV.DVDV_BitrateLow = states[9];
        p_media_play_info->media_play_info_DVDV.DiscRestrict = states[10];
        p_media_play_info->media_play_info_DVDV.DVDV_RetryStatus = states[11];
    }

}

/* ------------------------------------- */
/* Name: parse_audio_set_info()
 * Source: 4.4.3 [0F03]
 * Status Description: 
 *      Notification of information concerning attribute of audio stream present 
 * replaying. 
 *      This status is voluntarily notified by the change in the audio attribute. 
 */

/* Parameter */
/*
AudioFormat ( Param0.    All ) : Audio Format 
    00h:  The format is unknown. (Invalid) 
    01h:  Linear PCM ”DVD-Video / CD-DA / VCD” (LPCM) 
    12h: Dolby Digital 
    13h: Dolby Digital-EX 
    22h: DTS 
    23h: DTS-ES 
    31h: SDDS 
    42h:  MPEG1 without extended bit stream “MPEG-Audio LayerII” 
    43h:  MPEG1 with extended bit stream “MPEG-Audio LayerII” 
    45h:  MPEG2 without extended bit stream “MPEG-Audio LayeIIr” 
    46h:  MPEG2 with extended bit stream    “MPEG-Audio LayerII” 
    48h:  MP3 “MPEG1 LayerIII” 
    49h:  MP3 ”MPEG2 LayerIII” 
    4Ah:  MP3 “MPEG2.5 LayerIII” 
    51h: WMA 
    61h: G-726 
 
ChannelNs ( Param1.    bit0 - 3 ) : Number of Channels 
    0h:  The number of channels is unknown. 
    1 - 8h:  The number of channels is “1 - 8 ch” 
        * Dolby-EX / DTS-ES : 6 ch 
    9h:  DualMono of 2ch.

AppliMode ( Param1.    bit4 - 7 ) : Composition type of stream 
    0h:  There is no specification / Unknown ( Format other than Dolby(-EX) / DTS(-ES) ) 
    0h: Karaoke Stream 
    0h: DualMono Stream 
 
ChAssZ ( Param2.    bit0 ) : Channel allocation of LFE element (AudioFormat = Dolby / DTS) 
    0b:  Format other than Dolby(-EX) / DTS(-ES) 
    0b:  There is no LFE element in the channel allocation. / Unknown 
    1b: There is LFE element in the channel allocation. 
 
ChAssY ( Param2.    bit1 - 3 ) : Channel allocation of Rear element (AudioFormat = Dolby / DTS) 
    000b:  Format other than Dolby(-EX) / DTS(-ES) 
    000b:  There is no Rear element in the channel allocation. / Unknown 
    001b:  There is 1ch Rear element in the channel allocation. 
    010b:  There are 2ch Rear element in the channel allocation. 
 
ChAssX ( Param2. bit4 - 6 ) : Channel allocation of Front element (AudioFormat = Dolby / DTS) 
    000b:  Format other than Dolby(-EX) / DTS(-ES) 
    000b:  There is no Front element in the channel allocation. / Unknown 
    001b:  There is 1ch Front element in the channel allocation (Center channel). 
    010b:  There are 2ch Front element in the channel allocation (Front Left / Front Right channels). 
    010b:  There are 3ch Front element in the channel allocation (Front Left / Front Right / Center channels). 
 
StMode ( Param2.    bit7 ) : Control of Audio (AudioFormat = Dolby / DTS) 
[AudioFormat = Dolby / DTS] 
    0b:  Surround mode is invalid / Unknown 
    1b:  Surround mode is valid 
[AudioFormat = Format other than Dolby / DTS] 
    0b:  Format other than Dolby(-EX) / DTS(-ES)
FsGroup1 ( Param3.    bit0 - 3 ) : Sampling Frequency of each channel 
         * When 1 and 2 of Channel Groups exist, specify for Channel Group 1. 
    0h:  There is no pertinent Frequency. 
    1h: 32 kHz 
    2h: 44.1 kHz 
    3h: 88.2 kHz 
    4h: 176.4 kHz 
    5h: 48 kHz 
    6h: 96 kHz 
    7h: 192 kHz 
    8h: 8 kHz 
    9h: 11.02 kHz 
    Ah: 12 kHz 
    Bh: 16 kHz 
    Ch: 22.05 kHz 
    Dh: 24 kHz 

FsGroup2 ( Param3.    bit4 - 7 ) : Sampling Frequency of each channel (For Channel Group 2) 
        * It is effective when 1 and 2 of Channel Groups exist. 
    0h:  There is no pertinent Frequency / The channel group doesn't exist. 
    2h: 44.1 kHz 
    3h: 88.2 kHz 
    4h: 176.4 kHz 
    5h: 48 kHz 
    6h: 96 kHz 
    7h: 192 kHz 
 
QbGroup1 ( Param4.  bit0 - 3 ) : Quantization Bit Rate of each channel 
        * When 1 and 2 of Channel Groups exist, specify for Channel Group 1. 
    0h:  There is no pertinent bit number. 
    1h: 16 bit 
    2h: 20 bit 
    3h: 24 bit 
 
QbGroup2 ( Param4.  bit4 - 7 ) : Quantization Bit Rate of each channel (For Channel Group 2) 
         * It is effective when 1 and 2 of Channel Groups exist. 
    0h:  There is no pertinent bit number / The channel group doesn't exist. 
    1h: 16 bit 
    2h: 20 bit 
    3h: 24 bit 
 
OutFs ( Param5.    bit0 - 3 ) : Output Sampling Frequency 
    0h:  Output frequency is unknown. 
    1h: 32 kHz 
    2h: 44.1 kHz 
    3h: 88.2 kHz 
    4h: 176.4 kHz 
    5h: 48 kHz 
    6h: 96 kHz 
    7h: 192 kHz 
    8h: 8 kHz 
    9h: 11.02 kHz 
    Ah: 12 kHz 
    Bh: 16 kHz 
    Ch: 22.05 kHz 
    Dh: 24 kHz 

OutQb ( Param6.    bit0 - 3 ) : Output Quantization Bit Rate 
    0h:  Output bit number is unknown. 
    1h: 16 bit 
    2h: 20 bit 
    3h: 24 bit 

ChAssGroup1 ( Param7.    All ) : Channel allocation element 
        * When 1 and 2 of Channel Groups exist, specify for Channel Group 1. 
                * C: Center / L(Lf) : Front Left / R(Rf) : Front Right 
                * S : Surround / Ls : Left Surround / Rs : Right Surround 
        * LFE : Sub Woofer(SW) 
    00h: The allocation element is unknown. 
    10h: The allocation element is "C". 
    11h:  The allocation element is "C / S". 
    12h:  The allocation element is "C / Ls / Rs". 
    13h: The allocation element is "C / LFE". 
    14h: The allocation element is "C / LFE / S". 
    15h: The allocation element is "C / LFE / Ls / Rs". 
    20h: The allocation element is "L / R(Ls / Rs)". 
    21h: The allocation element is "Lf / Rf / S". 
    22h: The allocation element is "Lf / Rf / Ls / Rs". 
    23h: The allocation element is "Lf / Rf / LFE". 
    24h: The allocation element is "Lf / Rf / LFE / S". 
    25h: The allocation element is "Lf / Rf / LFE / Ls / Rs". 
    30h: The allocation element is "Lf / Rf / C". 
    31h: The allocation element is "Lf / Rf / C / S". 
    32h: The allocation element is "Lf / Rf / C / Ls / Rs". 
    33h: The allocation element is "Lf / Rf / C / LFE". 
    34h: The allocation element is "Lf / Rf / C / LFE / S". 
    35h: The allocation element is "Lf / Rf / C / LFE / Ls / Rs". 
 
ChAssGroup2 ( Param8.    All ) : Channel allocation element (For Channel Group 2) 
           * It is effective when 1 and 2 of Channel Groups exist. 
           * C: Center / S : Surround / Ls : Left Surround / Rs : Right Surround 
           * LFE : Sub Woofer(SW) 
    00h: The allocation element is unknown / The Channel Group doesn't exist.. 
    01h: The allocation element is "S". 
    02h: The allocation element is "Ls / Rs". 
    03h: The allocation element is "LFE". 
    04h: The allocation element is "LFE / S". 
    05h: The allocation element is "Ls / Rs / LFE". 
    10h: The allocation element is "C". 
    11h: The allocation element is "C / S". 
    12h: The allocation element is "C / Ls / Rs". 
    13h: The allocation element is "C / LFE". 
    14h: The allocation element is "C / LFE / S". 
    15h: The allocation element is "C / Ls / Rs / LFE". 
*/ 



void parse_audio_set_info(struct AUDIO_SET_INFO *p_audio_set_info, BYTE *states)
{
    p_audio_set_info->GroupID = states[0];
    p_audio_set_info->SubID = states[1];
    p_audio_set_info->AudioFormat = states[2];
    p_audio_set_info->AppliMode = (states[3] & 0xF0) >> 4;
    p_audio_set_info->ChannelNs = states[3] & 0x0F;
    p_audio_set_info->StMode = (states[4] & 0x80) >> 7;
    p_audio_set_info->ChAssX = (states[4] & 0x70) >> 4;
    p_audio_set_info->ChAssY = (states[4] & 0x0E) >> 1;
    p_audio_set_info->ChAssZ = states[4] & 0x01;
    p_audio_set_info->FsGroup2 = (states[5] & 0xF0) >> 4;
    p_audio_set_info->FsGroup1 = states[5] & 0x0F;
    p_audio_set_info->QbGroup2 = (states[6] & 0xF0) >> 4;
    p_audio_set_info->QbGroup1 = states[6] & 0x0F;
    p_audio_set_info->OutFs = states[7] & 0x0F;
    p_audio_set_info->OutQb = states[8] & 0x0F;
    p_audio_set_info->ChAssGroup1 = states[9];
    p_audio_set_info->ChAssGroup2 = states[10];
}

/* ------------------------------------- */
/* Name: parse_st_info()
 * Source: 4.4.4 [0F04]
 * Status Description: 
 *      Notification of information concerning present replay stream. 
 *      This status is voluntarily notified by the change in the replay stream. 
 *      Moreover, the information format is decided by contents recorded on the media. 
 */

/* DISC_INFO . SetMediaType : VCD */
/*
StereoMode ( Param0.    bit0 - 1 ) : Setting of Stereo Mode 
    00b: LR 
    01b: LL 
    10b: RR 
 
PbcSelectNs ( Param1.    All ) : Total of "Numeric selection" at present replay position (PBC ON) 
    00b:  PBC OFF / There is no PBC. 
    00 - 63h:    Total “0 - 99” 
 
PbcOffsetNo ( Param2.    All ) : Offset Value of "Numeric selection" at present replay position (PBC ON) 
    00b:  PBC OFF / There is no PBC. 
    00 - 63h:    Offset Value “0 - 99” 
 
PbcNext ( Param3.    bit0 ) : “NEXT” PBC operation at present replay position (PBC ON) 
PbcPrev ( Param3.    bit1 ) : “PREVIOUS” PBC operation at present replay position (PBC ON) 
PbcReturn ( Param3.    bit2 ) : “RETURN” PBC operation at present replay position (PBC ON) 
PbcPlay ( Param3.    bit3 ) : “PLAY(SELECT)” PBC operation at present replay position (PBC ON) 
    0b:  PBC OFF / There is no PBC. 
    0b: Operation valid 
    1b: Operation invalid 
*/ 


/* DISC_INFO . SetMediaType : COMPRESS */
/*
AstNo ( Param0.    All ) : Audio Stream Number of present replay 
    00h:  Audio Stream doesn't exist. 
    01h:    Audio Stream No. “1” 
 
FPS ( Param2 - 3.    All ) : Number of Frames per one second 
    0000 - FFFEh:    FPS value “0 - 65.534” 
        *Number of Frame per one second = devide FPS value by 1000 
    FFFFh:         FPS value “more than 65.535” 
 
*/ 



/* DISC_INFO . SetMediaType : DVDV */
/*
AgBlock ( Param0.    bit0 ) : State of Angle Block 
    0b:  It is not Angle Block. 
    1b:  It is Angle Block. 
 
TempPTL ( Param0.    bit1 ) : State of Temporary Parental 
    0b:  It is not Temporary Parental. 
    1b:  It is Temporary Parental. 
 
Button ( Param0.    bit2 ) : Presence of operating Button 
    0b:  The button doesn't exist. 
    1b: The button exist. 
 
PTL ( Param0.    bit3 ) : State of Parental 
    0b:  There is no replay limitation by the Parental management. 
    1b:  There is replay limitation by the Parental management. 
 
AgNo ( Param1.    All ) : Angle Number of present replay 
    01 - 09h:    Angle No. “1 - 9” 
 
SPstNo ( Param2.    bit0 - 5 ) : Sub-picture Stream Number of present replay 
    00h:  Sub-picture Stream doesn't exist. 
    01 - 20h:  Sub-picture Stream No. “1 - 32” 
    3Eh: Sub-picture Stream is not selected. 
 
SPDisp ( Param2.    bit7 ) : Output state of present replay Sab-picture Stream 
    0b:  Sub-picture Stream is not output / Sub-picture Stream doesn't exist. 
    1b:      Sub-picture Stream is output 
 
SubPLangCode ( Param3 - 4.    All ) : Language Code of present replay Sub-picture Stream 
    0000 - FFFFh:    Language Code Value 
        * The Code value follows ISO639. 
 
AstNo ( Param5.    All ) : Audio Stream Number of present replay 
    00h:  Audio Stream doesn't exist. 
    01 - 08h:  Audio Stream No. “1 - 8” 
 
AudioLangCode ( Param6 - 7.    All ) : Language Code of present replay Audio Stream 
    0000 - FFFFh:    Language Code Value 
        * The Code value follows ISO639. 
 
ButtonNo ( Param8.    All ) : Button Number under selection 
    00h:  Button doesn't exist. 
    01 - 24h:  Button No. “1 - 36” 
        * Button manipulation value of user selection = Button Number (ButtonNo) + Button Offset Value (ButtonOffSet) 
 
ButtonNs ( Param9.    All ) : Total of Button that can be selected 
    00h:  Button doesn't exist. 
    01 - 24h:  Number of Button “1 - 36” 
        * The max button manipulation value of user selection = Total of Button (ButtonNs) + Button Offset Value (ButtonOffSet) 
 
ButtonOffSet ( Param10.    All ) : Offset value of “Button number” in user manipulation control 
    00h:  Button doesn't exist. 
    01 - 24h:  Offset Value “1 - 36”
*/


void parse_st_info(struct ST_INFO *p_st_info, BYTE *states, BYTE SetMediaType)
{
    p_st_info->GroupID = states[0];
    p_st_info->SubID = states[1];
    
    /* DISC_INFO . SetMediaType : VCD */
    if (SetMediaType == 0x02) {
        p_st_info->st_info_VCD_block.StereoMode = states[2];
        p_st_info->st_info_VCD_block.PbcSelectNs = states[3];
        p_st_info->st_info_VCD_block.PbcOffsetNo = states[4];
        p_st_info->st_info_VCD_block.PbcPlay = (states[5] & 0x08) >> 3;
        p_st_info->st_info_VCD_block.PbcReturn = (states[5] & 0x04) >> 2;
        p_st_info->st_info_VCD_block.PbcPrev = (states[5] & 0x02) >> 1;
        p_st_info->st_info_VCD_block.PbcNext = states[5] & 0x01;
    }

    /* DISC_INFO . SetMediaType : COMPRESS */
    if (SetMediaType == 0x03) {
        p_st_info->st_info_DATA_block.AstNo = states[2];
        p_st_info->st_info_DATA_block.FPS = (WORD(states[4]) << 7)
                                            + states[5];
    }

    /* DISC_INFO . SetMediaType : DVDV */
    if (SetMediaType == 0x11) {
        p_st_info->st_info_DVDV_block.PTL = (states[2] & 0x08) >> 3;
        p_st_info->st_info_DVDV_block.Button = (states[2] & 0x04) >> 2;
        p_st_info->st_info_DVDV_block.TempPTL = (states[2] & 0x02) >> 1;
        p_st_info->st_info_DVDV_block.AgBlock = states[2] & 0x01;
        p_st_info->st_info_DVDV_block.AngleNo = states[3];
        p_st_info->st_info_DVDV_block.SPDisp = (states[4] & 0x80) >> 7;
        p_st_info->st_info_DVDV_block.SPstNo = states[4] & 0x3F;
        p_st_info->st_info_DVDV_block.SubPLangCode = (WORD(states[5]) << 7)
                                                   + states[6];
        p_st_info->st_info_DVDV_block.AstNo = states[7];
        p_st_info->st_info_DVDV_block.AudioLangCode = (WORD(states[8]) << 7)
                                                    + states[9];
        p_st_info->st_info_DVDV_block.ButtonNo = states[10];
        p_st_info->st_info_DVDV_block.ButtonNs = states[11];
        p_st_info->st_info_DVDV_block.ButtonOffSet = states[12];
    }

}

/* ------------------------------------- */
/* Name: parse_copy_info()
 * Source: 4.5.1 [1002]
 * Status Description: 
 *      Notification of information concerning CGMS/SCMS/APS (Copy Protection 
 * information) information on present replay position (status).   
 *      This status is voluntarily notified by the change in information. 
 */

/* Parameter */
/*
Cpms ( Param0.    bit0 - 1 ) : CGMS / SCMS information 
    00b:  Copying is permitted without restriction. 
    01b:  Copieable for one generation. 
    11b: Prohibit the copying 
 
ApsTriggerBit ( Param0.    bit4 - 5 ) : APS information 
    00b:  APS is off 
    01b:  Type1 of APS is On 
    10b:  Type2 of APS is On 
    11b:  Type3 of APS is On 
*/ 


void parse_copy_info(struct COPY_INFO *p_copy_info, BYTE *states)
{
    p_copy_info->GroupID = states[0];
    p_copy_info->SubID = states[1];
    p_copy_info->ApsTriggerBit = (states[2] & 0x30) >> 4;
    p_copy_info->Cgms = states[2] & 0x03;
}

/* ------------------------------------- */
/* Name: parse_cci_info()
 * Source: 4.5.2 [1003]
 * Status Description: 
 *      Notification of CCI related information of present replay position (status). 
 *      This status is voluntarily notified by the change in information. 
 */

/* Parameter */
/*
ATrans ( Param0.    bit0 ) : Audio processing information 
    0b:  There is no information (unused) 
 
AQuality ( Param0.    bit1 - 2 ) : Audio quality at copy permission 
    00b:  Number of channels is two or less, Fs is no greater than 48 kHz, Q is no greater than 16 bit. 
        * In "ACopyPermit≠Number" case, "00b" is fixed. 
    01b:  Number of channels is two or less, Fs is not restricted, Q is not restricted. 
    10b:  Number of channels is not restricted, Fs is not restricted, Q is not restricted. 
    11b:  Number of channels is not restricted, Fs is no greater than 48 kHz, Q is no greater than 16 bit. 
 
ACopyNo ( Param0.    bit3 - 5 )  ：  Number of permitted copies of Audio 
    000b:  Number of permitted copies is “1” 
        * In "ACopyPermit≠Number" case, "00b" is fixed. 
    001b:  Number of permitted copies is “2” 
    010b:  Number of permitted copies is “4” 
    011b:  Number of permitted copies is “6” 
    100b:  Number of permitted copies is “8” 
    101b:  Number of permitted copies is “10” 
    111b:  Number of permitted copies is not restricted (Copy One Generation) 
 
ACopyPermit ( Param0.    bit6 - 7 ) : Describes the copy permission status of Audio 
    00b:  Copying is permitted without restriction. (Free) 
    01b:  Copying is permitted per “ACopyNo”. (Number) 
    11b:  No more copies are permitted./ Prohibit the copying    (NoMore) 
*/ 



void parse_cci_info(struct CCI_INFO *p_cci_info, BYTE *states)
{
    p_cci_info->GroupID = states[0];
    p_cci_info->SubID = states[1];
    p_cci_info->ACopyPermit = (states[2] & 0xC0) >> 6;
    p_cci_info->ACopyNo = (states[2] & 0x38) >> 3;
    p_cci_info->AQuality = (states[2] & 0x06) >> 1;
    p_cci_info->ATrans = states[2] & 0x01;
}

/* ------------------------------------- */
/* Name: parse_update_info()
 * Source: 4.6.1 [0C06]
 * Status Description: 
 *      Status of progress of update processing 
 *      This status is voluntarily notified by the update processing (Refer to 
 * DISC_PROG_UPDATE command). 
 */

/* Parameter */
/*
InfoType ( Param0.    bit0 - 3 ) : Type of information 
    3h:  Status of progress of update processing (Status) 
 
InfoNo ( Param0.    bit4 - 7 ) : File Number of object bin file 
    0 - 9h:    File No. “1 - 10” 
        * The file number is specified by the CALL_UPDATE_INFO command. 
        * The file number is count number that allocated ascending order of the file log on the disc. 
        * The file number = InfoNo + 1 
        * In" InfoType=Status " case, "0h" is fixed. 
 
Condition ( Param1.    All )  ：  State of progress of update processing 
    00h:  It is remained to be processed. 
    01h:  Data acquisition start from disc. 
    02h:  Data is acquiring from disc. 
    03h:  Data acquisition from disc is completed. 
    06h:  Update data writing start. 
    10h:  Specified data has been updated. 
    11h: Data Format Error. 
    12h: Checksum Error. 
    13h:  Transmission Error from disc. 
    14h:  Mode Error of Program update processing. 
    15h:  Received data Error. 
    FFh: Other Errors 
*/ 



void parse_update_info(struct UPDATE_INFO *p_update_info, BYTE *states)
{
    p_update_info->GroupID = states[0];
    p_update_info->SubID = states[1];
    p_update_info->InfoType = 0x03;
    p_update_info->InfoNo = (states[2] & 0xF0) >> 4;
    p_update_info->Condition = states[3];
}

/* ------------------------------------- */
/* Name: parse_cmd_resp()
 * Source: 4.7.1 [1101]
 * Status Description: 
 *      Notification of reception consequence of issued command on system side. 
 *      This status is voluntarily notified for the reception of the command. 
 */

/* Parameter */
/*
CmdResp ( Param0.    All ) : Receive consequence of command 
    00h:  The command is accepted. (Accept) 
    02h:  The command is rejected. (SysReject) 
        * The command that cannot be executed with present media 
    03h:  The command cannot be accepted. (Busy) 
        * The number of command acceptance limitation is exceeded. 
    05h: The invalid command for specification. (Error) 
    FFh:  The command cannot be accepted by other factors. (Fail) 
 
RespGroupID ( Param1.    All ) : Group ID of acceptance command 
    01 - FFh: Group ID 
 
RespSubID ( Param2.    All ) : Group Sub ID of acceptance command 
    01 - FFh:  Group Sub ID 
*/ 



void parse_cmd_resp(struct CMD_RESP *p_cmd_resp, BYTE *states)
{
    p_cmd_resp->GroupID = states[0];
    p_cmd_resp->SubID = states[1];
    p_cmd_resp->CmdResp = states[2];
    p_cmd_resp->RespGroupID = states[3];
    p_cmd_resp->RespSubID = states[4];
}

/* ------------------------------------- */
/* Name: parse_cmd_fail()
 * Source: 4.7.2 [1102]
 * Status Description: 
 *      Notification of execution error to accepted command. 
 *      This status is voluntary notification status of the error that occurs 
 * when the command executes processing. 
 */

/* Parameter */
/*
CmdFail ( Param0.    All ) : Content of command execution error 
    00h:  The present operation and the content of the demand are the same. (Same) 
        * It has already executed. 
    01h:  The command is rejected. (DiscReject) 
        * Limitation by application standard such as UOP 
    02h:  The command is rejected. (SysReject) 
        * Limitation based on system specification 
    03h:  The command that cannot be executed in present state. (MissMatch) 
        * It is correct as the specification of the command. 
    04h:  The command is interrupted/canceld by receiving the priority command. (Cancel) 
    FFh:  The command cannot be accepted by other factors. (Fail) 
 
FailGroupID ( Param1.    All ) :  Group ID of execution command 
    01 - FFh: Group ID 
 
FailSubID ( Param2.    All ) : Group Sub ID of execution command 
    01 - FFh:  Group Sub ID 
*/ 



void parse_cmd_fail(struct CMD_FAIL *p_cmd_fail, BYTE *states)
{
    p_cmd_fail->GroupID = states[0];
    p_cmd_fail->SubID = states[1];
    p_cmd_fail->CmdFail = states[2];
    p_cmd_fail->FailGroupID = states[3];
    p_cmd_fail->FailSubID = states[4];
}


