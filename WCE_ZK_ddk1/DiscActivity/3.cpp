#include "stdafx.h" 
#include "epf.h"
#include "3.h"

//EPF_CMD epf_last_cmd;





/* 3.1 System Start Command */
/* ------------------------------------- */
/* Name: set_end()
 * Source: 3.1.1 [0103]
 * Command Description: 
 *      The end of the period that system start process is available (Refer to 
 * the SYSTEM_START status) is demanded. 
 *      This start-up period is defined as "Initialization period", and it is 
 * defined after that as "Normal operation period". 
 */

void set_end()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x01;
    cmd[1] = 0x03;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = SET_END;
}



void set_type(BYTE ModelType, BYTE Dest, BYTE Mecha)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x01;
    cmd[2] = ModelType;
    cmd[3] = Dest;
    cmd[4] = Mecha;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = SET_TYPE;
}



void set_model(BYTE HiTempControl, BYTE LowTempControl, BYTE OSD, BYTE SpdifOut, BYTE DacQb, BYTE LrckFs,  BYTE StForm,  BYTE Composit,  BYTE YC, BYTE Component, BYTE TextFirstChar, BYTE TextSecondChar, BYTE Size8Disc, BYTE FullEject)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x02;
    cmd[2] = HiTempControl;		// 0xA6
    cmd[3] = LowTempControl;	// 0x00
    cmd[4] = OSD;
	// StForm	0b
	// LrckFs	110b
	// DacQb	10b
	// SpdifOut	1b
    cmd[5] = (StForm << 6) + (LrckFs << 3) + (DacQb << 1) + SpdifOut;
	// Component	0
	// YC			1
	// Composit		1
    cmd[6] = (Component << 2) + (YC << 1) + Composit;
    cmd[7] = TextFirstChar;
    cmd[8] = TextSecondChar;
    cmd[9] = (Size8Disc << 1) + FullEject;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = SET_MODEL;
}


 
void call_set_type_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x03;
    cmd[2] = 0x00;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = CALL_SET_TYPE_INFO;
}


 
void call_set_model_info()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x04;
    cmd[2] = 0x00;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = CALL_SET_MODEL_INFO;
}



void disc_load_eject(BYTE SelectDisc, BYTE LoadPlay, BYTE MechaMode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x05;
    cmd[2] = SelectDisc;
    cmd[3] = (LoadPlay << 4) + MechaMode;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = DISC_LOAD_EJECT;
}




void force_eject()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x06;
    
    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = FORCE_EJECT;

}



void set_model_type(BYTE ModelType, BYTE Setup)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x12;
    cmd[2] = ModelType;
    cmd[3] = Setup;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = SET_MODEL_TYPE;
}



void initialize(BYTE SetupClear, BYTE PpmInfo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x01;
    cmd[1] = 0x01;
    cmd[2] = 0x3F;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = INITIALIZE;
}



void source_change(BYTE Mode)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x01;
    cmd[1] = 0x07;
    cmd[2] = Mode;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));

	//epf_last_cmd = SOURCE_CHANGE;
}



void play_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x21;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void stop_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x22;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void pause_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x23;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: step_f_key()
 * Source: 3.3.4 [8024]
 * Command Description: 
 *      Single frame Step forward in VCD / DVD-Video.
 */

void step_f_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x24;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: step_b_key()
 * Source: 3.3.5 [8025]
 * Command Description: 
 *      Single frame Step backward in VCD / DVD-Video.
 */

void step_b_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x25;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


 
void fast_f_key(BYTE Speed)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x26;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: fast_b_key()
 * Source: 3.3.7 [8027]
 * Command Description: 
 *      Fast rewind replay (Fixed speed) 
 */

/* Speed : Speed specified
 * Same as fast_f_key() enum
 */

void fast_b_key(BYTE Speed)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x27;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: fast_f_auto_key()
 * Source: 3.3.8 [8028]
 * Command Description: 
 *      Fast forward replay (Variable speed) 
 */

void fast_f_auto_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x28;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: fast_b_auto_key()
 * Source: 3.3.9 [8029]
 * Command Description: 
 *      Fast rewind replay (Variable speed) 
 */

void fast_b_auto_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x29;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void slow_f_key(BYTE Speed)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2A;
    cmd[2] = Speed;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: slow_b_key()
 * Source: 3.3.11 [802B]
 * Command Description: 
 *      Reverse direction low speed replay with VCD/DVD-Video (Fixed speed)
 */

/* Speed: Speed specified 
 * Same as slow_f_key() enum
 */

void slow_b_key(BYTE Speed)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2B;
    cmd[2] = Speed;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: slow_f_auto_key()
 * Source: 3.3.12 [802C]
 * Command Description: 
 *      Forward direction low speed replay with VCD/DVD-Video (Variable speed)
 */

void slow_f_auto_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2C;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: slow_b_auto_key()
 * Source: 3.3.13 [802D]
 * Command Description: 
 *      Reverse direction low speed replay with VCD/DVD-Video (Variable speed)
 */

void slow_b_auto_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2D;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: fast_slow_cancel_key()
 * Source: 3.3.14 [802E]
 * Command Description: 
 *      Release special replay mode (for avoiding release failure such as timing 
 * deviation) 
 */

void fast_slow_cancel_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2E;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void skip_f_key(BYTE Time)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x2F;
    cmd[2] = Time;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


/* ------------------------------------- */
/* Name: skip_b_key()
 * Source: 3.3.16 [8030]
 * Command Description: 
 *      Jump to cureent Second Position of beginning of previous Second Position. 
 *      * Second Position 
            (DVD-Video)  : Chapter (Program) 
            (CD-DA)   : Track 
            (VCD)   : Track 
            (COMPRESS) : File 
 *      * With VCD PBC-ON, PBC operation is performed. 
 */

/* Time : Time Skip Executed/not Executed 
 * Same as skip_f_key() enum
 */

void skip_b_key(BYTE Time)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x30;
    cmd[2] = Time;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: skip_folder_f_key()
 * Source: 3.3.17 [8031]
 * Command Description: 
 *      Jump to beggining of next First Position. 
 *      * First Position 
            (DVD-Video) : Title 
            (CD-DA)    : (Not supported) 
            (VCD)    : (Not supported) 
            (COMPRESS) : Folder
 */

void skip_folder_f_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x31;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: skip_folder_b_key()
 * Source: 3.3.18 [8032]
 * Command Description: 
 *      Jump to beggining of previous First Position. 
 *      * First Position 
            (DVD-Video)  : Title
            (CD-DA)   : (Not supported)
            (VCD)   : (Not supported)
            (COMPRESS) : Folder 
 */

void skip_folder_b_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x32;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: play_pause_key()
 * Source: 3.3.19 [8033]
 * Command Description: 
 *      Start normal replay, or pause the replay temporarily 
 *      * With VCD PBC-ON, PBC operation is performed. 
 */

void play_pause_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x33;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


void audio_key(BYTE Stereo)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x41;
    cmd[2] = Stereo;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void subp_key(BYTE Output)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x42;
    cmd[2] = Output;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: subp_on_off_key()
 * Source: 3.3.22 [8043]
 * Command Description: 
 *      Sub-picture output in DVD-V 
 */

void subp_on_off_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x43;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: angle_key()
 * Source: 3.3.23 [8044]
 * Command Description: 
 *      Angle switching in DVD-V. 
 */

void angle_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x44;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: PAGE_KEY()
 * Source: 3.3.24 [8045]
 * Command Description: 
 *      Still picture page switching in DVD-A/ DVD-VR.
 * Picture ( Param0. bit0 - 2 ) : Specify page
 */
void page_key(BYTE picture)
{
	BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x45;
	cmd[2] = picture;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: top_menu_key()
 * Source: 3.3.25 [8046]
 * Command Description: 
 *      Display (Replay) the menu related contents replay control for DVD-V. 
 */

void top_menu_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x46;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: menu_key()
 * Source: 3.3.25 [8047]
 * Command Description: 
 *      Display (Replay) the menu related contents replay control for DVD-V. 
 */

void menu_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x47;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: mode_change_key()
 * Source: 3.3.26 [8049]
 * Command Description: 
 *      Switch replay control mode in VCD. 
 */

void mode_change_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x49;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: n_p_key()
 * Source: 3.3.27 [804A]
 * Command Description: 
 *      Switch TV system “NTSC/PAL”. 
 */

void n_p_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x4A;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: repeat_key()
 * Source: 3.3.28 [8051]
 * Command Description: 
 *      Switch Repeat setting (Not for VCD PBC-ON) 
 */

void repeat_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x51;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: mix_key()
 * Source: 3.3.29 [8052]
 * Command Description: 
 *      Set M.I.X. replay.
 */

void mix_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x52;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: scan_key()
 * Source: 3.3.30 [8053]
 * Command Description: 
 *      Set scan replay.
 */

void scan_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x53;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: repeat_ab_key()
 * Source: 3.3.31 [8054]
 * Command Description: 
 *      Set repeat A-B replay.
 */

void repeat_ab_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x54;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void direction_key(BYTE Direction)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x62;
    cmd[2] = Direction;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}



void ten_key(BYTE Value)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x63;
	cmd[2] = Value;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


void enter_key(BYTE Time)
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x65;
    cmd[2] = Time;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

/* ------------------------------------- */
/* Name: return_key()
 * Source: 3.3.35 [8066]
 * Command Description: 
 *      Return to upper layer operation. 
 *      * PBC operation is performed in VCD PBC-ON. 
 */

void return_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x66;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}
/*----------------------------------------*/
/*
	*Name:DISC_MENU_KEY

	*Source: 3.3.41.  [ 80 68 ]
	* Command Description 
	Display disc menu OSD screen.
	This command is only enabled in changer mechanism.
*/

void disc_menu_key()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x68;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}


/* ------------------------------------- */
/* Name: disc_prog_update()
 * Source: 3.4.1 [8010]
 * Command Description: 
 *      Updating data that is recorded in Update disc, will be prepared to 
 * transfer as update program for microprocessor of dirve mechanism. 
 *      Update disc is defined that consist of one management information file 
 * and one updating data recorded in the root directory. This command is 
 * executed based on this management information. 
 *      Data transferring/writing by this command will be carried out after 
 * transfer data stored in system managed RAM. 
 */

void disc_prog_update()
{
    BYTE cmd[16] = {0};
    cmd[0] = 0x80;
    cmd[1] = 0x10;

    epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void user_cont(int x, int y)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x06;
	cmd[1] = 0x05;
	cmd[2] = 0x05;
	//CoordinateX
	cmd[3] = ((BYTE)(((x) >> 8) & 0xFF));
	cmd[4] = ((BYTE)(((x)>> 16) & 0xFFFF));

	//CoordinateY
	cmd[5] = ((BYTE)(((y) >> 8) & 0xFF));
	cmd[6] = ((BYTE)(((y)>> 16) & 0xFFFF));;
	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void set1_dvd(int regcode)
{
	BYTE cmd[16] = {0};
	cmd[0] = 0x07;
	cmd[1] = 0x05;
	cmd[2] = regcode;
	cmd[3] = 1;
	cmd[4] = 0x19;
	cmd[5] = 0;
	cmd[6] = 0;
	epf_send(cmd, sizeof(cmd)/sizeof(cmd[0]));
}

void dvd_info_reset()
{
	BYTE data[17] = {0};
	epf_send(data, 0);	// clear epf fifo
}
