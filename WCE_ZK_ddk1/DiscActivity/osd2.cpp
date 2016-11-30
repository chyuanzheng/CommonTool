#include "stdafx.h"
#include "epf.h"


/* ------------------------------------- */
/* Name: call_setup_info()
 * Source: 2.1.1 [0C02]
 * Command Description: 
 *      The current various setting value information is obtained. 
 *      The information is obtained by various statuses ( SETxx_xx_INFO ) that 
 * specified by the parameter of this command. 
 */

/* Parameter */
/*
GroupID ( Param0.    All )    : Group ID of target status 
    07 to 0Bhã€?0h : Group ID 
 
GroupSubID ( Param1.    All )    : Group Sub ID of target status 
    01 to FFh : Group Sub ID 
*/

void call_setup_info(BYTE GroupID, BYTE GroupSubID)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0C;
    cmd[1] = 0x02;
    cmd[2] = GroupID;
    cmd[3] = GroupSubID;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_inquiry_info()
 * Source: 2.1.2 [0C03]
 * Command Description: 
 *      The particular information of system is obtained. 
 *      The information is obtained by INQUIRY_INFO status (refer description of 
 * this status). 
 */

/* Parameter */
/*
PageCode ( Param0.    All )    : Select target information 
    00h : Request of type information on mechanism.   
    01h : Request of pproduct revision level information. 
    02h : Request of Pproduct identification (1st page) information. 
    03h : Request of Pproduct identification (2nd page) information. 
    04h : Request of the original product identification (1st page) information. 
    05h : Request of the original product identification (2nd page) information. 
*/

void call_inquiry_info(BYTE PageCode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0C;
    cmd[1] = 0x03;
    cmd[2] = PageCode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_sysmode_info()
 * Source: 2.1.3 [0C07]
 * Command Description: 
 *      The general information of system is obtained. 
 *      The information is obtained by SYSMODE_INFO status (refer description of 
 * this status). 
 * (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*

*/

void call_sysmode_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0C;
    cmd[1] = 0x07;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_temp_info()
 * Source: 2.1.4 [0C0D]
 * Command Description: 
 *      The temperature information of Mechanism , which mechanism is installed 
 * this system, is obtained. 
 *      The information is obtained by TEMP_INFO status (refer description of 
 * this status). 
 */

/* Parameter */
/*

*/

void call_temp_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0C;
    cmd[1] = 0x0D;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_testtone_info()
 * Source: 2.1.5 [0C0F]
 * Command Description: 
 *      The information of Test-tone (refer to description of TESTTONE_OUTPUT 
 * command ) which is currently-running, is obtained. 
 *      The information is obtained by TESTTONE_INFO status (refer description 
 * of this status). 
 */

/* Parameter */
/*

*/

void call_testtone_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0C;
    cmd[1] = 0x0F;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_toc1_info()
 * Source: 2.2.1 [030B]
 * Command Description: 
 *      The TOC information of intended track is obtained. 
 *      The information is obtained as TOC1_INFO status. 
 */

/* Parameter */
/*
TrackNo ( Param0.    All )    : Specifies target track to request TOC information 
    00h  : Specifies first track 
    01h to 63h  : Specifies track number [ 1 to 99] 
    A2h  : Specifies Lead-Out 
*/

void call_toc1_info(BYTE TrackNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x03;
    cmd[1] = 0x0B;
    cmd[2] = TrackNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_toc2_info()
 * Source: 2.2.2 [030C]
 * Command Description: 
 *      The TOC information of 4 tracks from intended track is obtained. 
 *      The information is obtained as TOC2_INFO status. 
 */

/* Parameter */
/*
TrackNo ( Param0.  All )  : Specifies intended start track to request TOC information 
    00h  : Specifies first track 
    01h to 63h  : Specifies track number [ 1 to 99] 
    A2h  : Specifies Lead-Out 
*/

void call_toc2_info(BYTE TrackNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x03;
    cmd[1] = 0x0C;
    cmd[2] = TrackNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_folder_file_no()
 * Source: 2.2.3 [0322]
 * Command Description: 
 *      The file number for folder or the file number for Disc corresponding to 
 * the recorded file on Disc is obtained.   
 *      When the target file is specified by the serial file number for Disc, 
 * the file number for Folder is obtained as intended information. 
 *      When the target file is specified by the file number for Folder, the 
 * serial file number for Disc is obtained as intended information. 
 *      The information is obtained by FOLDER_FILE_NO_INFO status (refer to the 
 * description of this status). 
 *      This command is valid at COMPRESS. 
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All ) : Specifies the folder number that contains target information file.   
        (It is valid when specified by the serial file number in the disc)   
    0000h         :  None specified 
        * It is shown that this command is a demand of information on the file number for Folder. 
        * [FileNo] is a file number for Disc 
        * The information of file number for Folder that specified by the file number for Disc is obtained. 
    0001 to 0100h      :    Folder number [ 1 to 256 ] 
        * It is shown that this command is a demand of information on the file number for Disc. 
        * 0001h indicates as root. 
        * [FileNo] is a file number in [Folder] 
        * The information of file number for Disc that specified by the file number for Folder is obtained. 
 
FileNo. ( Param2 to 3.    All ) : Specifies the file number that is target information file.   
    0001 to 1000h    :    file number [ 1 to 4096 ] 
        * If [ FolderNo = 0000h ], this parameter shows file number for Disc. 
        * If [ FolderNo  â‰? 0000h ], this parameter shows file number for Folder of [FolderNo] 
*/

void call_folder_file_no(WORD FolderNo, WORD FileNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x03;
    cmd[1] = 0x22;
    cmd[2] = BYTE((FolderNo & 0xFF00) >> 8);
    cmd[3] = BYTE(FolderNo & 0x00FF);
    cmd[4] = BYTE((FileNo & 0xFF00) >> 8);
    cmd[5] = BYTE(FileNo & 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_text_code_info()
 * Source: 2.3.1 [0D01]
 * Command Description: 
 *      The Code information of corresponding text type and language on replay 
 * content is obtained. 
 *      The information is obtained by TEXT_CODE_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with CDDA. 
 *      Note: The presence of Text data can be judged from DISC_INFO status 
 * information. 
 */

/* Parameter */
/*
PageNo ( Param0.    All )    : Specifies the divided page number 
    01 to 02h :    Page number [ 1 to 2 ]
*/

void call_text_code_info(BYTE PageNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x01;
    cmd[2] = PageNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_text_info()
 * Source: 2.3.2 [0D02]
 * Command Description: 
 *      The text on replay content is obtained. 
 *      The information is obtained by TEXT_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with CDDA. 
 *      Note: The presence of Text data can be judged from DISC_INFO status 
 * information. 
 */

/* Parameter */
/*
TextType ( Param0.    All )    : Specifies target item of text information 
    80h :  Album title / Song title 
    81h :  Artist name 
    82h :  Lyricist 
    83h :  Composer 
    84h :  Arranger 
    87h :  Genre 
    8Fh :  Arrangement information 
 
TrackNo ( Param1.    All )    : Target track number to require information 
    00h  : Specifies Disc 
    01h to 63h  : Specifies Track number [ 1 to 99 ] 
 
PageNo ( Param2.    All )    : Specify divided page number 
    00 to FFh : Page number [ 0 to 255 ] 
        * Specifies page as [ 01 to 08h ] with [ TextType = 8Fh ], and specifies as [ 01 to FFh ]   
with [ TextType  â‰?8Fh ]. 
        * For divided transmission with    [ TextType = 8Fh ], 1 language information is allocate for each page. 
        * For divided transmission with [ TextType  â‰? 8Fh ], 8 byte text data is allocated for each page. 
 
SelectInfo ( Param3.    All )    : Specifies content of text information (valid in TextType = 8Fh ) 
        * "Album title / Song title" and "Artist name" information is sure to be included. 
    00h :  No specification  (TextTypeâ‰?Fh) 
    00h :  All information  (TextTypeï¼?Fh) 
        * The object of information is â€œLyricistâ€? â€œComposerâ€?â€?Arrangerâ€?and â€œGenreâ€? 
    82h :  Lyricist    (TextTypeï¼?Fh) 
    83h :  Composer    (TextTypeï¼?Fh) 
    84h :  Arranger    (TextTypeï¼?Fh) 
    87h :  Genre    (TextTypeï¼?Fh) 
*/

void call_text_info(BYTE TextType, BYTE TrackNo, BYTE PageNo, BYTE SelectInfo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x02;
    cmd[2] = TextType;
    cmd[3] = TrackNo;
    cmd[4] = PageNo;
    cmd[5] = SelectInfo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_file_name_info()
 * Source: 2.3.3 [0D03]
 * Command Description: 
 *      The name of each file that recorded on Identification Disc is obtained. 
 *      The information is obtained by FILE_NAME_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS. 
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All )    : Specifies the folder number that include target file. 
    0001 to 0100h  : Folder number [ 1 to 256 ] ( Select )   
        * 0001h is indicated as root   
    FFFFh  : Specifies by the serial file number ( All )   
 
FileNo ( Param2 to 3.    All )    : Specifies target file number in a folder 
    0001 to 1000h :   File number in a folder [ 1 to 4096 ]  ( FolderNo = Select )   
    0001 to 1000h :   File number in a Disc [ 1 to 4096 ]   ( FolderNo = All )   
 
PageNo ( Param4.    All )    : Specifies divided page number 
    00 to 07h :   Page number [ 0 to 7 ] 
        * Specifies page as [ 01 to 07h ] for divided transmission and specifies as [ 00h ] for batch transmission. 
        * For divided transmission, 10 byte file name data is allocated for each page. 
        * AdditionFileNs  â‰? 00h with Batch transmission, name size per a file is fixed as 64 byte. 
        * AdditionFileNs = 00h with EPFIII Batch transmission, name size per a file is fixed as 64 byte. 
        * When the file name size doesn't come up to the transmission length, it is corrected by using the Null(0x00) data. 
 
Extension ( Param5.    bit0 to 1 )    : Obtaining of file extension   
    00b : Exclude the extension as file name 
    01b : Include the extension as file name 
        *When the number of characters of file name exceeds permissible size, the extension is not included.   
    11b : The extension must be included as file name. 
        *The permissible size of file name is the number that subtracted number of characters of file extension from permissible size. 
 
AdditionFileNs ( Param6.    All )    : Number of obtaining file at once ( valid only with PageNo = 00h)   
    00h  : Obtain the file name that specified by FolderNo and FileNo. (PageNo = 00h,  â‰?0h) 
        01ï½?3h  : Number of additional obtaining file [1 to 19]    (PageNo = 00h) 
        * Obtain all file names that have file numbers as [from FileNo + 1 to FileNo + AdditionFileNs] at once. 
        * If [FolderNo  â‰? FFFFh] is specified, only the file in a pertinent folder is targeted to obtain information. 
        * When a specified file doesn't exist, the Null(0x00) data is allocated. 
*/

BOOL call_file_name_info(WORD FolderNo, WORD FileNo, BYTE PageNo, BYTE Extension, BYTE AdditionFileNs)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x03;
    cmd[2] = BYTE((FolderNo & 0xFF00) >> 8);
    cmd[3] = BYTE(FolderNo & 0x00FF);
	cmd[4] = BYTE((FileNo & 0xFF00) >> 8);
    cmd[5] = BYTE(FileNo & 0x00FF);
    cmd[6] = PageNo;
    cmd[7] = Extension;
    cmd[8] = AdditionFileNs;
	
	if (PageNo == 0)
	{
		int len = 0;
		len = 5+64*AdditionFileNs;
		ASSERT(AdditionFileNs);
		return epf_send(cmd, len);
	}

    return epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_folder_name_info()
 * Source: 2.3.4 [0D04]
 * Command Description: 
 *      The name of each folder that recorded on Identification Disc is obtained. 
 *      The information is obtained by FOLDER_NAME_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS. 
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All )    : Specifies target folder number 
    0001 to 0100h    : Folder number [ 1 to 256 ] 
        * 0001h is indicated as root. 
 
PageNo ( Param2.    All )    : Specifies divided page number 
    00 to 07h : page number [ 0 to 7 ] 
        * Specifies page as [ 01 to 07h ] for divided transmission and specifies as [ 00h ] for batch transmission. 
        * For divided transmission, 10 byte folder name data is allocated for each page. 
        * AdditionFolderNs  â‰? 00h with Batch transmission, name size per a folder is fixed as 64 byte. 
        * AdditionFolderNs = 00h with EPFIII Batch transmission, name size per a folder is fixed as 64 byte. 
        * When the folder name size doesn't come up to the transmission length, it is corrected by using the Null(0x00) data. 
 
AdditionFolderNs ( Param3.    All )    : Number of obtaining folder at once ( valid only with PageNo = 00h)   
    00h  : Obtain the folder name that specified by FolderNo.  (PageNo = 00h,  â‰?0h) 
    01ï½?4h  : Number of additional obtaining folder [1 to 20]    (PageNo = 00h) 
        * The folder name of the lower folder that belongs to the folder specified with FolderNo is acquired. 
        * When a specified file doesn't exist, the Null(0x00) data is allocated.   
 
StartFolder ( Param4.    All )    : Number in folder of the first lower folder to be acquired ( valid only with PageNo  â‰? 00h)   
    00h  : Obtain the folder name that specified by FolderNo.    (PageNo = 00h,  â‰?0h) 
    01ï½žFFh  : Number in folder of the first child folder to be acquired [1 to 255]  (PageNoâ‰?0h) 
        * It is a number counted from the head of the folder that belongs to the folder that FolderNo specifies. 
        * The lower folder name of AdditionFolderNs piece is acquired from the lower folder that StartFolder specifies.
*/

void call_folder_name_info(WORD FolderNo, BYTE PageNo, BYTE AdditionFolderNs, BYTE StartFolder)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x04;
    cmd[2] = BYTE((FolderNo & 0xFF00) >> 8);
    cmd[3] = BYTE(FolderNo & 0x00FF);
    cmd[4] = PageNo;
    cmd[5] = AdditionFolderNs;
    cmd[6] = StartFolder;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_tag_info()
 * Source: 2.3.5 [0D05]
 * Command Description: 
 *      The TAG information of currently replaying file is obtained. 
 *      The information is obtained by TAG_INFO status (refer to the description 
 * of this status). 
 *      This command is valid with COMPRESS. 
 */

/* Parameter */
/*
TagType ( Param0.    All )    : Specifies target type of TAG to require information 
        * 0A to 0Dh are valid for JPEG file. 
    00h : Title 
    01h : Artist name 
    02h : Album title 
    03h : Released year 
    04h : Comment 
    05h : Genre 
    0Ah : Original shooting date 
    0Bh : Last update 
    0Ch : Vertical size of image 
    0Dh : Horizontal size of image 
 
PageNo ( Param1.    All )    : Specifies divided page number 
    00 to 10h : page number[ 0 to 16 ] 
        * Specifies page as [ 01 to 10h ] for divided transmission and specifies as [ 00h ] for batch transmission. 
        * For divided transmission, 8 byte TAG data is allocated for each page. 
        * Name size per a file by EPFIII Batch transmission is fixed as 128 bytes. 
 
DataSelect ( Param2.  bit0 )  : Specifies optimization execution for obtained data 
    0b : Perform no optimization   
       * Treat all data in TAG area as target information. 
    1b : Perform optimization 
        * Treat only the data that complying with TAG standard in TAG area as target information. 
*/

void call_tag_info(BYTE TagType, BYTE PageNo, BYTE DataSelect)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x05;
    cmd[2] = TagType;
    cmd[3] = PageNo;
    cmd[4] = DataSelect;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_disc_name_info()
 * Source: 2.3.6 [0D0A]
 * Command Description: 
 *      The Disc name correspond to Identification Disc is obtained. 
 *      The information is obtained by DISC_NAME_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS, VCD, DVD-Video. 
 */

/* Parameter */
/*
PageNo ( Param0.    All )    : Specifies divided page number 
    01 to 07h : page number [ 1 to 7 ] 
        * For divided transmission, 10 byte Disc name data is allocated for each page. 
*/

void call_disc_name_info(BYTE PageNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0D;
    cmd[1] = 0x0A;
    cmd[2] = PageNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_disc_info()
 * Source: 2.4.1 [0E01]
 * Command Description: 
 *      The information about identified disc is obtained. 
 *      The information is obtained by DISC_INFO status (refer description of 
 * this status). 
 * (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*
InfoType ( Param0.    bit0 )    :    Specifies the obtaining range of target information 
    0b : Media information 
    1b : Media and Contents information 
*/

void call_disc_info(BYTE InfoType)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x01;
    cmd[2] = InfoType;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_firstposition_info()
 * Source: 2.4.2 [0E02]
 * Command Description: 
 *      The information about current replaying First Position section of replay 
 * content is obtained. 
 *      The definitions of First Position section for each content are as follows. 
            CDDA    : Not applicable (Not correspond to the command )   
            VCD    : Not applicable (Not correspond to the command)   
            COMPRESS : Folder  DVD-Video : Title The information is obtained by 
            FIRSTPOSITION_INFO status (refer description of this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*

*/

void call_firstposition_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x02;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_secondposition_info()
 * Source: 2.4.3 [0E03]
 * Command Description: 
 *      The information about current replaying Second Position section of 
 * replay content is obtained. 
 *      The definitions of Second Position section for each content are as 
 * follows. 
            CD-DA  : Track  
            VCD  : Track  
            COMPRESS : File   
            DVD-Video  : Chapter (PTT) 
 *      The information is obtained by SECONDPOSITION_INFO status (refer 
 * description of this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for 
 * customer) ") 
 */

/* Parameter */
/*

*/

void call_secondposition_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x03;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_domain_info()
 * Source: 2.4.4 [0E04]
 * Command Description: 
 *      The information about classification of current replaying position of 
 * replay content is obtained. 
 *      The information is obtained by DOMAIN_INFO status (refer description of 
 * this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for 
 * customer) ") 
 */

/* Parameter */
/*

*/

void call_domain_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x04;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_folder_info()
 * Source: 2.4.5 [0E05]
 * Command Description: 
 *      The information of recording folder in Identification Disc is obtained. 
 *      The information is obtained by FOlDER_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS. 
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All )    : Specifies target folder number 
    0001 to 0100h    : Folder number [ 1 to 256 ] 
        * 0001h is indicated as root. 
 
InfoType( Param2.    bit0 ) : Specifies target information type 
    0b : Information of file composition ( Composition ) 
    1b : Information of lower folder number ( Lower ) 
 
PageNo ( Param3.    All )    : Specifies divided page number 
    00h  : No division of page   ( InfoType = Composition) 
    01 to 33h  : Page number [ 1 to 51 ]  ( InfoType = Lower ) 
        * For divided transmission, 5 lower folder information are allocated by ascending order for each page.
*/

void call_folder_info(WORD FolderNo, BYTE InfoType, BYTE PageNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x05;
    cmd[2] = BYTE((FolderNo & 0xFF00) >> 8);
    cmd[3] = BYTE(FolderNo & 0x00FF);
    cmd[4] = InfoType;
    cmd[5] = PageNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_file_type_info()
 * Source: 2.4.6 [0E06]
 * Command Description: 
 *      The information of recording file type in Identification Disc is obtained. 
 *      The information is obtained by FILE_TYPE_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS
 */

/* Parameter */
/*
FolderNo ( Param0 to 1.    All )    : Specifies the folder number that include target file.
    0001 to 0100h  : Folder number [ 1 to 256 ] ( Select )   
        * 0001h is indicated as root   
    FFFFh  : Specifies by the serial file number / Specifies entire Disc ( All )   
 
FileNo ( Param2 to 3.    All )    : Specifies target file number in a folder 
    0001 to 1000h    : File number in a folder [ 1 to 4096 ]  ( FolderNo = Select )   
    0001 to 1000h    : File number in a Disc [ 1 to 4096 ]  ( FolderNo = All )   
    FFFFh    : All files in the specified folder    ( FolderNo = Select )   
    FFFFh    : All files in entire Disc      ( FolderNo = All )   
*/

void call_file_type_info(WORD FolderNo, WORD FileNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x06;
    cmd[2] = BYTE((FolderNo & 0xFF00) >> 8);
    cmd[3] = BYTE(FolderNo & 0x00FF);
    cmd[4] = BYTE((FileNo & 0xFF00) >> 8);
    cmd[5] = BYTE(FolderNo & 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_secondposition_ns_info()
 * Source: 2.4.7 [0E07]
 * Command Description:
 *      The total Second Position number in the specified First Position section 
 * on replay content is obtained. 
 *      The information is obtained by SECONDPOSITION_NS_INFO status (refer to the 
 * description of this status). 
 *      This command is valid with COMPRESS, DVD-Video. 
 */

/* Parameter */
/*
FirstPosition ( Param0 to 1.    All )    : Specifies the target First Position number to start obtaining information 
        * EPF III: 4 First Position sections from  specified position are intended.  
    0001 to 0100h    : Folder number [ 1 to 256 ]    ( COMPRESS )   
        * 0001h is indicated as root 
    0001 to 0063h    : Title number [ 1 to 99 ]     ( DVD-Video )  
*/

void call_secondposition_ns_info(WORD FirstPosition)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x07;
    cmd[2] = BYTE((FirstPosition & 0xFF00) >> 8);
    cmd[3] = BYTE(FirstPosition & 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_stream_attribute_info()
 * Source: 2.4.8 [0E08]
 * Command Description: 
 *      The information about attribute of specified stream type of replay 
 * content is obtained. 
 *      The information is obtained by STREAM_ATTRIBUTE_INFO status (refer to 
 * the description of this status). 
 *      This command is valid with COMPRESS, DVD-Video. 
 */

/* Parameter */
/*
StType ( Param0.    All )    : Selects stream of target information 
    00h   : Audio stream ( Audio )   
    01h   : Sub Picture stream ( SubP )   
 
StNo ( Param1.    All )    : Specifies number of target stream 
    01 to 20h    : Stream number [ 1 to 32 ] 
*/

void call_stream_attribute_info(BYTE StType, BYTE StNo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0E;
    cmd[1] = 0x08;
    cmd[2] = StType;
    cmd[3] = StNo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_play_info()
 * Source: 2.5.1 [0F01]
 * Command Description: 
 *      The information about running replay operation is obtained. 
 *      The information is obtained by PLAY_INFO status (refer description of 
 * this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for 
 * customer) ") 
 */

/* Parameter */
/*

*/

void call_play_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0F;
    cmd[1] = 0x01;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_media_play_info()
 * Source: 2.5.2 [0F02]
 * Command Description: 
 *      The information about running replay Media is obtained. 
 *      The information is obtained by MEDIA_PLAY_INFO status (refer description 
 * of this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for
 * customer) ") 
 */

/* Parameter */
/*

*/

void call_media_play_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0F;
    cmd[1] = 0x02;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_audio_set_info()
 * Source: 2.5.3 [0F03]
 * Command Description: 
 *      The information about attribute of running replay Audio stream is obtained. 
 *      The information is obtained by AUDIO_SET_INFO status (refer description of 
 * this status). 
 * (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*

*/

void call_audio_set_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0F;
    cmd[1] = 0x03;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_st_info()
 * Source: 2.5.4 [0F04]
 * Command Description: 
 *      The information about condition of running replay Audio stream is obtained. 
 *      The information is obtained by ST_INFO status (refer description of this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 *      This command is invalid with CDDA. 
 */

/* Parameter */
/*

*/

void call_st_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0F;
    cmd[1] = 0x04;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_copy_info()
 * Source: 2.6.1 [1002]
 * Command Description: 
 *      The CGMS/SCMS/APS information for current replaying position ( condition ) 
 * is obtained.
 *      The information is obtained by COPY_INFO status (refer description of 
 * this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*

*/

void call_copy_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x11;
    cmd[1] = 0x02;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: call_cci_info()
 * Source: 2.6.2 [1003]
 * Command Description: 
 *      The current replaying position ( condition ) information is obtained. 
 *      The information is obtained by CCI_INFO status (refer description of this status). 
 *      (For status, refer to " DVD-AV EPF Command/Status Specification (for customer) ") 
 */

/* Parameter */
/*

*/

void call_cci_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x10;
    cmd[1] = 0x03;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3v_back_video()
 * Source: 2.7.1 [0A01]
 * Command Description: 
 *      The setting about output image (background image) is set while video 
 * contents are not replaying.   
 *      This command is valid in all time. (This command doesn't correspond by 
 * limiting the device in the state of the replay.) 
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

void set3v_back_video(BYTE BackVideo, BYTE YSignal, BYTE CbSignal, BYTE CrSignal)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0A;
    cmd[1] = 0x01;
    cmd[2] = BackVideo;
    cmd[3] = YSignal;
    cmd[4] = CbSignal;
    cmd[5] = CrSignal;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3v_video_adjust()
 * Source: 2.7.2 [0A10]
 * Command Description: 
 *      Set the quality of the picture. 
 *      The adjustment object is "Brightness", "Contrast", "Color", and "Tint". 
 *      This command is always valid. 
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

void set3v_video_adjust(BYTE BSign, BYTE Brightness, BYTE CtSign, BYTE Contrast, BYTE ClSign, BYTE Color, BYTE TSign, BYTE Tint)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0A;
    cmd[1] = 0x10;
    cmd[2] = (BSign << 7) + Brightness;
    cmd[3] = (CtSign << 7) + Contrast;
    cmd[4] = (ClSign << 7) + Color;
    cmd[5] = (TSign << 7) + Tint;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_drc()
 * Source: 2.7.3 [0B01]
 * Command Description: 
 *      Set the Dynamic Range control. 
 *      This command is valid in all time. 
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

void set3a_drc(BYTE DRCMode, BYTE CutScale, BYTE BoostScale)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x01;
    cmd[2] = DRCMode;
    cmd[3] = CutScale;
    cmd[4] = BoostScale;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_a_spk()
 * Source: 2.7.4 [0B02]
 * Command Description: 
 *      Set connecting condition and size of Speaker on system environment. 
 *      This command is valid in all time. 
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

void set3a_a_spk(BYTE CenterSize, BYTE RearSize, BYTE FrontSize, BYTE Sw)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x02;
    cmd[2] = (CenterSize << 4) + (RearSize << 2) + FrontSize;
    cmd[3] = Sw;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_a_delay()
 * Source: 2.7.5 [0B03]
 * Command Description: 
 *      Set Delay setting for each Audio Channel 
 *      This command is valid in all time. 
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

void call_setup_info(BYTE FLDelay, BYTE FRDelay, BYTE CDelay, BYTE RLDelay,
                     BYTE RRDelay, BYTE SwDelay)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x03;
    cmd[2] = FLDelay;
    cmd[3] = FRDelay;
    cmd[4] = CDelay;
    cmd[5] = RLDelay;
    cmd[6] = RLDelay;
    cmd[7] = RRDelay;
    cmd[8] = SwDelay;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_spk_lvl()
 * Source: 2.7.6 [0B04]
 * Command Description: 
 *      Set the Level setting for each Audio Channel. 
 *      This command is valid in all time. 
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

void set3a_spk_lvl(BYTE FLSign, BYTE FLLevel, BYTE FRSign, BYTE FRLevel, BYTE CSign, BYTE CLevel, BYTE RLSign, BYTE RLLevel, BYTE RRSign, BYTE RRLevel, BYTE SwSign, BYTE SwLevel)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x04;
    cmd[2] = (FLSign << 4) + FLLevel;
    cmd[3] = (FRSign << 4) + FRLevel;
    cmd[4] = (CSign << 4) + CLevel;
    cmd[5] = (RLSign << 4) + RLLevel;
    cmd[6] = (RRSign << 4) + RRLevel;
    cmd[7] = (SwSign << 4) + SwLevel;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_a_mute()
 * Source: 2.7.7 [0B05]
 * Command Description: 
 *      Set the Mute setting for Audio output. 
 *      This command is valid in all time. 
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

void set3a_a_mute(BYTE DigitalMute, BYTE AnalogMute, BYTE SwMute, BYTE RLMute, BYTE RRMute, BYTE CMute, BYTE FLMute, BYTE FRMute)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x05;
    cmd[2] = (DigitalMute << 4) + AnalogMute;
    cmd[3] = (SwMute << 5) + (RLMute << 4) + (RRMute << 3) + (CMute << 2)
           + (FLMute << 1) + FRMute;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_dm_mode()
 * Source: 2.7.8 [0B06]
 * Command Description: 
 *      Set the Down-Mix mode setting for Down-Mix to 2ch. 
 *      This command is valid in all time. 
 */

/* Parameter */
/*
DmMode ( Param0.    All )    : Set Down-Mix mode 
    00h : Stereo Down-Mix    ( Lo / Ro )   
    01h : Surround compatible Down-Mix    ( Lt / Rt )    ( Initial value )
*/

void set3a_dm_mode(BYTE DmMode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x06;
    cmd[2] = DmMode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_dpl2_rf()
 * Source: 2.7.9 [0B07]
 * Command Description: 
 *      Set for Dolby Pro Logic II and Rear Fill. 
 *      This command is valid in all time. 
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

void set3a_dpl2_rf(BYTE SetMode, BYTE RDelay)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x07;
    cmd[2] = SetMode;
    cmd[3] = RDelay;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_phantom()
 * Source: 2.7.10 [0B10]
 * Command Description: 
 *      Set for BI-PHANTOM. 
 *      This command is valid in all time. 
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

void set3a_phantom(BYTE Mode, BYTE Sign, BYTE Level)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x08;
    cmd[2] = Mode;
    cmd[3] = Sign;
    cmd[4] = Level;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set3a_bassmng()
 * Source: 2.7.11 [0B0A]
 * Command Description: 
 *      Set the cutoff frequency setting of the low area. 
 *      This command is valid in all time. 
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

void set3a_bassmng(BYTE Mode, BYTE BmFs)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x0B;
    cmd[1] = 0x0A;
    cmd[2] = (Mode << 7) + BmFs;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2s_scan_time()
 * Source: 2.8.1 [0806]
 * Command Description: 
 *      Set execution timing of SEARCH for SCAN replay. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
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

void set2s_scan_time(BYTE Time, BYTE Skip)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x08;
    cmd[1] = 0x06;
    cmd[2] = Time;
    cmd[3] = Skip;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2s_tv_aspect()
 * Source: 2.8.2 [0807]
 * Command Description: 
 *      Set TV aspect ratio of System. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
 */

/* Parameter */
/*
SelectMode ( Param0.    bit0 to 1 )    : Set TV aspect ratio 
    00b : Wide ( Initial value )     
    01b : Pan & scan 
    10b : Letterbox 
*/

void set2s_tv_aspect(BYTE SelectMode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x08;
    cmd[1] = 0x07;
    cmd[2] = SelectMode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2s_dau_out()
 * Source: 2.8.3 [0809]
 * Command Description: 
 *      Set Digital Audio output setting. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.).  
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

void set2s_dau_out(BYTE MPEG, BYTE DTS, BYTE Dolby, BYTE DtsDecode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x08;
    cmd[1] = 0x09;
    cmd[2] = (MPEG << 2) + (DTS << 1) + Dolby;
    cmd[3] = DtsDecode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2a_play_priority()
 * Source: 2.8.4 [0902]
 * Command Description: 
 *      Set replay contents priority by DVD/CD disc at initial access. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
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

void set2a_play_priority(BYTE CD, BYTE VCD)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x09;
    cmd[1] = 0x02;
    cmd[2] = CD << 1;
    cmd[3] = 0x14 + VCD;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2a_lang()
 * Source: 2.8.5 [0905]
 * Command Description: 
 *      Set priority of Stream that based on the language correspond to Audio/SubPicute/Menu. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.).
 */

/* Parameter */
/*
SelectMode ( Param0.    bit0 to 1 )    : Set the target stream mode 
    01b : Set Audio Stream ( Audio )   
    10b : Set Sub Picture Stream ( SubP )   
    11b : Set Menu ( Menu )   
 
SPDisp ( Param0.    bit4 )    : Set display of SubPicuture 
    0b : Hidden SubPicture ( OFF ) have a priority to set. ( SelectMode = Audio/SubP/Menu )   
    1b : Display SubPicture ( ON ) have a priority to set. ( SelectMode = SubP )    ( Initial value in valid )   
 
LangCode ( Param1 to 2.    All )    : Set Criterial Language code for Stream selection 
   * If the corresponding language is not exist as Stream, select the minimum Stream number. 
    0000 to FFFEh : Name of priority language to select 
        * The setting code complies with ISO639. 
        * Set the ASCII capital character code in decimal notation by each 4 bit unit. 
        * e.c. ) 7465 -> JA -> Japanese 
 
    FFFFh       :  The language selection is set according to the specification by Disc (Navigation data).   
*/

void set2a_lang(BYTE SPDisp, BYTE SelectMode, WORD LangCode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x09;
    cmd[1] = 0x05;
    cmd[2] = (SPDisp << 4) + SelectMode;
    cmd[3] = BYTE((LangCode & 0xFF00) >> 8);
    cmd[4] = BYTE(LangCode & 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2a_country_code()
 * Source: 2.8.6 [0907]
 * Command Description: 
 *      Set Country code of DVD-Video. 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
 */

/* Parameter */
/*
CountryCode ( Param0 to 1.    All )    : Set Country code 
    0000 to FFFFh : Country code ( Initial value 7480 )   
        * The setting code complies with ISO3166. 
        * Set the ASCII capital character code in decimal notation by each 4 bit unit. 
        * e.c. ) 7480 -> JP -> Japan 
*/

void set2a_country_code(WORD CountryCode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x09;
    cmd[1] = 0x07;
    cmd[2] = BYTE((CountryCode & 0xFF00) >> 8);
    cmd[3] = BYTE(CountryCode & 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2a_ptl_lvl()
 * Source: 2.8.7 [0908]
 * Command Description: 
 *      Set parental control settings on DVD-Video 
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
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

void set2a_ptl_lvl(BYTE Level, BYTE PtlPwd4, BYTE PtlPwd3, BYTE PtlPwd2,
                   BYTE PtlPwd1)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x09;
    cmd[1] = 0x08;
    cmd[2] = Level;
    cmd[3] = (PtlPwd4 << 4) + PtlPwd3;
    cmd[4] = (PtlPwd2 << 4) + PtlPwd1;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: set2a_pause_mode()
 * Source: 2.8.8 [0909]
 * Command Description: 
 *      Set Pause settings. ( refer to the description of PAUSE_PLAY command ).   
 *      This command is valid during non-playing state (NO DISC, STOP and etc.). 
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

void set2a_pause_mode(BYTE PauseMode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x09;
    cmd[1] = 0x09;
    cmd[2] = PauseMode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: search_play()
 * Source: 2.9.1
 * Command Description: 
 *      SEARCH to specified position to start to play. 
 *      The position to search, can be specified by Time and Unit.    
 *      ( Unit Time Search/Time Search/Unit Search )  
 */

/* Parameter */

/* SelectMode : Unit Time */
/*
FirstPosition ( Param3 to 4.    All )    : Specifies FistPosition Unit number to Search   
        * At present, Not supported except current number specification. 
    0000h  : None specified  ( CD-DA, VCD )   
    0001 to 0063h  : Title number [ 1 to 99 ]  ( DVD-Video )   
 
Hours ( Param7.    All )    : Specifies â€œHourâ€?to Search time 
    00 to 63h  : [ 0 to 99 hours ]  ( DVD-Video )   
    0000h  : None specified  ( CD-DA, VCD )   
 
Minutes ( Param8.    All )    : Specifies â€œMinuteâ€?to Search time 
    00 to 3Bh  : [ 0 to 59 minutes ]  ( DVD-Video )   
    00 to 63h  : [ 0 to 99 minutes ]  ( CD-DA, VCD )   
 
Hours ( Param9.    All )    : Specifies â€œSecondâ€?to Search time 
    00 to 3Bh  : [ 0 to 59 seconds ] 
*/

struct STRUCT_SELECTMODE_UNITTIME {
    WORD    FirstPosition;
    BYTE    Hours;
    BYTE    Minutes;
    BYTE    Seconds;
    BYTE    STRUCT_SELECTMODE_UNITTIME_NULL0;
    BYTE    STRUCT_SELECTMODE_UNITTIME_NULL1;
    BYTE    STRUCT_SELECTMODE_UNITTIME_NULL2;
};

/* SelectMode : Unit */
/*
FirstPosition ( Param3 to 4.    All )    :    Specifies FistPosition Unit number to Search   
    0000h  : None specified  ( CD-DA, VCD )   
    0000h  : Specifies current replaying unit  ( COMPRESS , DVD-Video )   
    0001 to 0100h    : Folder number [ 1 to 256 ]  ( COMPRESS )   
        * 0001h is indicated as root. 
    FFFFh  : Serial File number by SecondPosition  ( COMPRESS )   
    0001 to 0063h  : Title number [ 1 to 99 ]  ( DVD-Video )   
 
SecondPosition ( Param5 to 6.    All )    : Specifies SecondPosition Unit number to Search 
    FFFFh  : Specifies the beginning (end) of specified FirstPosition section. 
    0001 to 0063h  : Track number [ 1 to 99 ]        ( CD-DA )   
    0001 to 0063h  : Track number [ 1 to 99 ]        ( VCD )   
    0001 to 1000h  : File number [ 1 to 4096 ]        ( COMPRESS )   
        * FirstPosition = FFFFh : Serial File number of Disc 
        * FirstPosition  â‰? FFFFh : File number of Folder 
    0001 to 03E7h  : Chapter ( PTT ) number [ 1 to 999 ]      ( DVD-Video )  
*/

struct STRUCT_SELECTMODE_UNIT {
    WORD    FirstPosition;
    WORD    SecondPosition;
};

/* SelectMode : Time */
/*
Hours ( Param3.    All )    : Specifies â€œHourâ€?to Search time 
    00 to 63h  : [ 0 to 99 hours ]    ( DVD-Video )   
    0000h  : None specified    ( CD-DAã€VCD )   
 
Minutes ( Param4.    All )    : Specifies â€œMinuteâ€?to Search time 
    00 to 3Bh  : [ 0 to 59 minutes ]    ( DVD-Video )   
    00 to 63h    : [ 0 to 99 minutes ]    ( CD-DAã€VCD )   
 
Hours ( Param5.    All )    : Specifies â€œSecondâ€?to Search time 
    00 to 3Bh    : [ 0 to 59 seconds ] 
*/

struct STRUCT_SELECTMODE_TIME {
    BYTE    Hours;
    BYTE    Minutes;
    BYTE    Seconds;
    BYTE    STRUCT_SELECTMODE_TIME_NULL0;
};

/*
SelectMode ( Param0.    bit0 to 1 )    : Selects method to specify the position to search 
    01b : Specified by Unit and Time ( Unit Time )   
    10b : Specified by Unit    ( Unit )   
    11b : SSpecified by Time    ( Time )   
 
PlayMode ( Param1.    All )    : Specifies Play operation after Search 
    01h : Stand by to play ( Standby )   
    04h : Play forward in normal speed ( Play )   
    05h : Pause ( Pause )   
    0Ah : Play Fast Forward ( Fast Forward )   
    0Bh : Play Fast Backward ( Fast Backward )   
        * Invalid in DVD-Video/VCD ( PBC ON ) 
    0Ch : Play Slow Forward ( Slow Forward )   
 
Speed ( Param2.    All )    : Specifies play speed after search ( valid in PlayMode = Fast/Slow )   
    00h : Not specified    ( PlayMode = Standby/Play/Pause )   
    02h : 2x speed    ( PlayMode = Fast Forward/Fast Backward )   
    03h : 3x speed    ( PlayMode = Fast Forward/Fast Backward )   
    04h : 4x speed    ( PlayMode = Fast Forward/Fast Backward )   
    08h : 8x speed    ( PlayMode = Fast Forward/Fast Backward )   
    0Ah : 10x speed    ( PlayMode = Fast Forward/Fast Backward )   
    10h : 16x speed    ( PlayMode = Fast Forward/Fast Backward )   
    15h : 21x speed    ( PlayMode = Fast Forward/Fast Backward )   
    20h : 32x speed    ( PlayMode = Fast Forward/Fast Backward )   
    02h : 1/2x speed    ( PlayMode = Slow Forward/Slow Backward )   
    04h : 1/4x speed    ( PlayMode = Slow Forward/Slow Backward )   
    08h : 1/8x speed    ( PlayMode = Slow Forward/Slow Backward )   
    10h : 1/16x speed    ( PlayMode = Slow Forward/Slow Backward )   
 
* As for the following parameters, the format is selected by the information content of â€œSelectModeâ€? 

*/

struct SELECTMODE {
    struct STRUCT_SELECTMODE_UNITTIME selectmode_unittime_block;
    struct STRUCT_SELECTMODE_UNIT selectmode_unit;
    struct STRUCT_SELECTMODE_TIME selectmode_time;
};

void search_play(BYTE SelectMode, BYTE PlayMode, BYTE Speed, struct SELECTMODE selectmode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x04;
    cmd[1] = 0x06;
    cmd[2] = SelectMode;
    cmd[3] = PlayMode;
    cmd[4] = Speed;

    /* SelectMode : Unit Time */
    if (SelectMode == 0x01) {
        cmd[9] = selectmode.selectmode_unittime_block.Hours;
        cmd[10] = selectmode.selectmode_unittime_block.Minutes;
        cmd[11] = selectmode.selectmode_unittime_block.Seconds;
    }

    /* SelectMode: Unit */
    if (SelectMode == 0x10) {
        cmd[5] = BYTE((selectmode.selectmode_unit.FirstPosition & 0xF0) >> 8);
        cmd[6] = BYTE(selectmode.selectmode_unit.FirstPosition & 0x0F);
        cmd[7] = BYTE((selectmode.selectmode_unit.SecondPosition & 0xF0) >> 8);
        cmd[8] = BYTE(selectmode.selectmode_unit.SecondPosition & 0x0F);
    }

    /* SelectMode: Time */
    if (SelectMode == 0x11) {
        cmd[5] = selectmode.selectmode_time.Hours;
        cmd[6] = selectmode.selectmode_time.Minutes;
        cmd[7] = selectmode.selectmode_time.Seconds;
    }

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


/* ------------------------------------- */
/* Name: chg_tempptl()
 * Source: 2.9.2 [0506]
 * Command Description: 
 *      Responds Permission/ No permission to the temporary change request of the parental level (temporary parental). 
 *      This command is valid for DVD-Video. 
 */

/* Parameter */
/*
Permit ( Param0.    bit0 )    : Selects Permission or No permission 
    0b : Not permit 
    1b : Permit 
*/

void chg_tempptl(BYTE Permit)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x05;
    cmd[1] = 0x06;
    cmd[2] = Permit;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: chg_media_mode()
 * Source: 2.9.3 [050E]
 * Command Description: 
 *      Switch between replay medias on mixed Disc 
 *      This command is effective in coexistence disc of "CDDA/COMPRESS". 
 */

/* Parameter */
/*
SelectMode ( Param0.    All )    : Specifies Media 
    00h : Switch over to CDDA    (Coexistence of CDDA/COMPRESS) 
    01h : Switch over to COMPRESS  (Coexistence of CDDA/COMPRESS) 
*/

void chg_media_mode(BYTE SelectMode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x05;
    cmd[1] = 0x0E;
    cmd[2] = SelectMode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: user_cont()
 * Source: 2.9.4 [0506]
 * Command Description: 
 *      Determine entry figure at MENU screen and others. 
 */

/* Parameter */
/*
SelectMode ( Param0.    All )    : Specifies operation 
    04h : Select and determine the number 
 
Selection ( Param1 to 2.    All )    : Specifies determined value 
    0001 to 0123h : Determined value [ 1 to 291 ] 
*/

void user_cont(BYTE SelectMode, WORD Selection)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x06;
    cmd[1] = 0x05;
    cmd[2] = SelectMode;
    cmd[3] = BYTE((Selection && 0xFF00) >> 8);
    cmd[4] = BYTE(Selection && 0x00FF);

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void user_cont(BYTE SelectMode, WORD CoordinateX, WORD CoordinateY)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x06;
	cmd[1] = 0x05;
	cmd[2] = SelectMode;
	cmd[3] = BYTE((CoordinateX & 0xFF00) >> 8);
	cmd[4] = BYTE(CoordinateX & 0x00FF);
	cmd[5] = BYTE((CoordinateY & 0xFF00) >> 8);
	cmd[6] = BYTE(CoordinateY & 0x00FF);

	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: testtone_output()
 * Source: 2.10.1 [0105]
 * Command Description: 
 *      Output TEST tone audio data from 4-wire Audio output. 
 */

/* Parameter */
/*
SelectMode ( Param0.    bit0 to 1 )    : Specifies output pattern of Test tone 
    00b : Stop Test tone output    ( TestTone Off )   
    10b : Continuous output of Test tone from specified channel ( Param1 ).  ( TestTone Channel )   
    11b : Test tone output and switch over channel automatically for every 2 seconds.    ( TestTone Auto )   
 
Noise ( Param0.    bit4 to 5 )    : Selects output noise 
    00b : Output Pink Noise.   
      *Only one channel is effective in the channel specification with Param1.    ( Invalid for multiple channel) 
    01b : Output White Noise ( Not supported )   
    10b : Output sine wave ( Not supported )   
 
Lf ( Param1.    bit0 )    : Setting of Front Left channel output  ( valid for â€˜SelectMode = Channelâ€?)   
Rf ( Param1.    bit1 )    : Setting of Front Right channel output  ( valid for â€˜SelectMode = Channelâ€?)   
C ( Param1.    bit2 )    : Setting of Center channel output  ( valid for â€˜SelectMode = Channelâ€?)   
Ls ( Param1.    bit3 )   : Setting of Surround Left channel output  ( valid for â€˜SelectMode = Channelâ€?)   
Rs ( Param1.    bit4 )   : Setting of Surround Left channel output  ( valid for â€˜SelectMode = Channelâ€?)   
Sw ( Param1.    bit5 )   : Setting of Subwoofer channel output  ( valid for â€˜SelectMode = Channelâ€?)   
    0b : None specified  ( SelectMode = Off/Auto )   
    0b : Set as no output channel  ( SelectMode = Channel )   
    1b : Set as Output channel  ( SelectMode = Channel )   
*/

void testtone_output(BYTE Noise, BYTE SelectMode, BYTE Sw, BYTE Rs, BYTE Ls,
                     BYTE C, BYTE Rf, BYTE Lf)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x01;
    cmd[1] = 0x05;
    cmd[2] = (Noise << 4) + SelectMode;
    cmd[3] = (Sw << 5) + (Rs << 4) + (Ls << 3) + (C << 2) + (Rf << 1) + Lf;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void search_play_unit_time(BYTE PlayMode, BYTE Speed, WORD FirstPosition, BYTE Hours, BYTE Minutes, BYTE Seconds)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x04;
	cmd[1] = 0x06;
	cmd[2] = 0x01;
	cmd[3] = PlayMode;
	cmd[4] = Speed;
	cmd[5] = FirstPosition>>8;
	cmd[6] = FirstPosition;
	cmd[7] = 0x0;
	cmd[8] = 0x0;
	cmd[9] = Hours;
	cmd[10] = Minutes;
	cmd[11] = Seconds;


	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void search_play_unit(BYTE PlayMode, BYTE Speed, WORD FirstPosition, WORD SecondPosition)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x04;
	cmd[1] = 0x06;
	cmd[2] = 0x02;
	cmd[3] = PlayMode;
	cmd[4] = Speed;
	cmd[5] = FirstPosition>>8;
	cmd[6] = FirstPosition;
	cmd[7] = SecondPosition>>8;
	cmd[8] = SecondPosition;



	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void search_play_time(BYTE PlayMode, BYTE Speed, BYTE Hours, BYTE Minutes, BYTE Seconds)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x04;
	cmd[1] = 0x06;
	cmd[2] = 0x03;
	cmd[3] = PlayMode;
	cmd[4] = Speed;
	cmd[5] = Hours;
	cmd[6] = Minutes;
	cmd[7] = Seconds;


	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

