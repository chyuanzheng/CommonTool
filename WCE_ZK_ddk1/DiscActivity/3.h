#pragma once



//enum EPF_CMD
//{
//	SET_END,
//	SET_TYPE,
//	SET_MODEL,
//	CALL_SET_TYPE_INFO,
//	CALL_SET_MODEL_INFO,
//	DISC_LOAD_EJECT,
//	FORCE_EJECT,
//	SET_MODEL_TYPE,
//	INITIALIZE,
//	SOURCE_CHANGE,
//	PLAY_KEY,
//	STOP_KEY,
//	PAUSE_KEY,
//	STEP_F_KEY,
//	STEP_B_KEY,
//	FAST_F_KEY,
//	FAST_B_KEY,
//	FAST_F_AUTO_KEY,
//	FAST_B_AUTO_KEY,
//	SLOW_F_KEY,
//	SLOW_B_KEY,
//	SLOW_F_AUTO_KEY,
//	SLOW_B_AUTO_KEY,
//	FAST_SLOW_CANCEL_KEY,
//	SKIP_F_KEY,
//	SKIP_B_KEY,
//	SKIP_FOLDER_F_KEY,
//	SKIP_FOLDER_B_KEY,
//	PLAY_PAUSE_KEY,
//	AUDIO_KEY,
//	SUBP_KEY,
//	SUBP_ON_OFF_KEY,
//	ANGLE_KEY,
//	TOP_MENU_KEY,
//	MENU_KEY,
//	MODE_CHANGE_KEY,
//	N_P_KEY,
//	REPEAT_KEY,
//	MIX_KEY,
//	SCAN_KEY,
//	REPEAT_AB_KEY,
//	DIRECTION_KEY,
//	TEN_KEY,
//	ENTER_KEY,
//	RETURN_KEY,
//	DISC_PROG_UPDATE,
//}	;


/* ------------------------------------- */
/* Name: SET2A_LANG
* Source: 2.8.5 [0905]
* Command Description: 
*      Set priority of Stream that based on the language correspond to Audio/SubPicute/Menu.
*	   This command is valid during non-playing state (NO DISC, STOP and etc.).
*     < Parameter Description > 

*		SelectMode ( Param0. bit0 to 1 ) : Set the target stream mode
*		01b : Set Audio Stream ( Audio )
*		10b : Set Sub Picture Stream ( SubP )
*		11b : Set Menu ( Menu )

*		SPDisp ( Param0. bit4 ) : Set display of SubPicuture
*		0b : Hidden SubPicture ( OFF ) have a priority to set. ( SelectMode = Audio/SubP/Menu )
*		1b : Display SubPicture ( ON ) have a priority to set. ( SelectMode = SubP ) ( Initial value in valid )

*		LangCode ( Param1 to 2. All ) : Set Criterial Language code for Stream selection
*		* If the corresponding language is not exist as Stream, select the minimum Stream number.
*			0000 to FFFEh : Name of priority language to select
*		* The setting code complies with ISO639.
*		* Set the ASCII capital character code in decimal notation by each 4 bit unit.
*		* e.c. ) 7465 -> JA -> Japanese
*			FFFFh : The language selection is set according to the specification by Disc (Navigation data).
*/
void SET2A_LANG(BYTE SelectMode, BYTE SPDisp, BYTE LangCode);

void set_end();

/* 3.2 System Control Command */
/* ------------------------------------- */
/* Name: set_type()
* Source: 3.2.1 [8001]
* Command Description: 
*      System¡¯s basic setting is made (Common settings that defined per 
* deployment destination and etc.). 
*      Setting is made by selecting the setting defined per model type, 
* destination and mechanism type. 
*      Only if it is in Initialization period (Refer to SET_END command),this 
* command is enabled. 
*/ 

/* ModelType */
/*
ModelType ( Param0.    All ) : Specify model type 
* Each setting¡¯s default value is determined per model type. 
* Each setting¡¯s default value per model is separately defined. 
00h:  No model type setting (Initial value) 
07h:  Setting is made for model type 7 (for GAC) 
*/

enum {
	NOMODEL = 0x00,
	MODEL_TYPE7 = 0x07,
};

/* dest: destination */
/*
Destination ( Param1.    All ) : Specify destination 
00h:  No destination specification (Initial value) 
10h:  Destination setting for US 
20h:  Destination setting for Japan 
21h:  Destination setting for Europe 
22h:  Destination setting for United Arab Emirates 
30h:  Destination setting for Hong Kong 
31h:  Destination setting for Korea 
32h:  Destination setting for Philippines 
40h:  Destination setting for Australia 
41h:  Destination setting for Mexico 
42h:  Destination setting for Paraguay 
50h:  Destination setting for Russia 
51h:  Destination setting for Ghana 
52h:  Destination setting for Mongolia 
60h:  Destination setting for China 
*/

enum {
	NODEST = 0x00,
	DEST_US = 0x10,     /* United States */
	DEST_JP = 0x20,      /* Japan */
	DEST_EU = 0x21,     /* Europe */
	DEST_AE = 0x22,     /* United Arab Emirates */
	DEST_HK = 0x30,     /* Hong Kong */
	DEST_KP = 0x31,     /* Korea */
	DEST_PH = 0x32,     /* Philippines */
	DEST_AU = 0x40,     /* Australia */
	DEST_MX = 0x41,     /* Mexico */
	DEST_PY = 0x42,     /* Paraguay */
	DEST_RU = 0x50,     /* Russia */
	DEST_GH = 0x51,     /* Ghana */
	DEST_MN = 0x52,     /* Mongolia */
	DEST_CN = 0x60,     /* China */
};

/* Mecha: mechanism */
/*
Mecha ( Param2.    All ) : Specify mechanism 
00h:  No mechanism type specification (Initial value) 
*/

enum {
	NOMECHA = 0x00,
};

void set_type(BYTE ModelType, BYTE Dest, BYTE Mecha);

/* ------------------------------------- */
/* Name: set_model()
* Source: 3.2.2 [8002]
* Command Description: 
*      Detailed system setting (Setting defined per adopted product¡¯s 
* individual specification) is made. 
*      Setting is made with detailed setting value that is specified based on 
* the adopted product specification. 
*      Only if it is in Initialization period (Refer to SET_END command),this 
* command is enabled. 
*/ 


/* HiTempControl: Boundary temperature value setting for high-temperature */
/*
HiTemp ( Param0.    All ) : Boundary temperature value setting for 
high-temperature 
00h:  No high-temperature is judged (Initial value) 
01 - FFh:  High-temperature boundary temperature AD value 01 - FF 
* If high-temperature is judged, high-temperature error is notified 
(Refer to SYSMODE_INFO status) 
*/ 

enum {
	NOHITEMP = 0x00,
};

/* LowTempControl: Boundary temperature value setting for low-temperature */
/*
LowTemp ( Param1.    All ) : Boundary temperature value setting for 
low-temperature 
00h:  No low-temperature is judged (Initial value) 
01 - FFh:  Low-temperature boundary temperature AD value 01 - FF 
* If low-temperature is judged, low-temperature error is notified 
(Refer to SYSMODE_INFO status)
*/

enum {
	NOLOWTEMP = 0x00,
};

/* OSD */
/*
OSD ( Param2.    bit0 ) : OSD display control specification 
0b:  No OSD is used 
*/

enum {
	NOOSD = 0x00,
};

/* SpdifOut: Digital (SPDIF) output setting */
/*
SpdifOut ( Param3.    bit0 ) : Digital (SPDIF) output setting 
0b:  No output /output prohibited by hardware 
1b:  Output (Initial value) 
*/

enum {
	NOSPDIFOUT = 0x00,
	SPDIFOUT = 0x01,
};

/* DacQb: DAC I/F quantization bit count setting */
/*
DacQb ( Param3.    bit1 - 2 ) : DAC I/F quantization bit count setting 
00b:  Fixed to 16bits 
* 20bits/24bits content also use 16bits. 
01b:  Fixed to 20bits 
* 16bits/24bits content also use 20bits. 
10b:  Fixed to 24bits (Initial value) 
* 16bits/20bits content also use 24bits. 
*/

enum {
	FIX_TO_16BITS = 0x00,
	FIX_TO_20BITS = 0x01,
	FIX_TO_24BITS = 0x02,
};

/* LrckFs: Maximum LRCK frequency setting for DAC I/F */
/*
LrckFs ( Param3.    bit3 - 5 ) : Maximum LRCK frequency setting for DAC I/F 
010b: 48 kHz 
100b: 96 kHz 
110b:  192 kHz (Initial value) 
*/ 

enum {
	FRQ_48KHZ = 0x02,
	FRQ_96KHZ = 0x04,
	FRQ_192KHZ = 0x06,
};

/* StForm: Dac I/F output format setting */
/*
StForm ( Param3.    bit6 - 7 ) : Dac I/F output format setting 
00b:  Left justify (Initial value) 
01b: Right justify 
01b: I2S 
*/

enum {
	LEFT_JUSTIFY = 0x00,
	RIGHT_JUSTIFY = 0x01,
	I2S = 0x02,
};

/* Composit: Output setting of composite signal */
/*
Composit ( Param4.    bit0 ) : Output setting of composite signal 
0b:  Off 
1b:  On (Initial value) 
*/

enum {
	COMPOSIT_OFF = 0x00,
	COMPOSIT_ON = 0x01,
};

/* YC: Output setting of Y/C signal */
/*
YC ( Param4.    bit1 ) : Output setting of Y/C signal 
0b:  Off 
1b:  On (Initial value) 
*/

enum {
	YC_OFF = 0x00,
	YC_ON = 0x01,
};

/* Component: Output setting of component signal */
/*
Component ( Param4.    bit2 ) : Output setting of component signal 
0b:  Off (Initial value) 
1b:  On
*/

enum {
	COMPONENT_OFF = 0x00,
	COMPONENT_ON = 0x01,
};

/* TextFirstChar: Text character code setting as selected with first priority */
/*
TextFirstChar ( Param5.    All ) : Text character code setting as selected with 
first priority 
* Only if there are no character codes that match with this setting, 
¡°TextSecondChar¡± setting is enabled. 
00h:  ISO 8859-1 (Initial value) 
01h:  ISO / IEC 646 
80h:  SHIFT JIS kanji & JIS katakana 
81h:  Korean character 
82h:  Mandarin character 
*/

enum {
	TEXTFIRSTCHAR_ISO8859_1 = 0x00,
	TEXTFIRSTCHAR_ISO_IEC_646 = 0x01,
	TEXTFIRSTCHAR_SHIFT_JIS = 0x80,
	TEXTFIRSTCHAR_KP = 0x81,
	TEXTFIRSTCHAR_CN = 0x82,
};

/* TextSecondChar: Text character code setting as selected with second priority */
/*
TextSecondChar ( Param6.    All ) : Text character code setting as selected with 
second priority 
* Only if there are no character codes that match with ¡°TextFirstChar¡± 
setting, this setting is enabled. 
* If there are no character codes that match with this setting, character 
code in disc heading record is selected. 
00h: ISO 8859-1 
01h:  ISO/IEC 646 (Initial value) 
80h:  SHIFT JIS kanji & JIS katakana 
81h:  Korean character 
82h:  Mandarin character 
*/

enum {
	TEXTSECONDCHAR_ISO8859_1 = 0x00,
	TEXTSECONDCHAR_ISO_IEC_646 = 0x01,
	TEXTSECONDCHAR_SHIFT_JIS = 0x80,
	TEXTSECONDCHAR_KP = 0x81,
	TEXTSECONDCHAR_CN = 0x82,
};

/* FullEject: Disc remaining amount setting in EJECT operation */
/*
FullEject ( Param7.    bit0 ) : Disc remaining amount setting in EJECT operation 
0b : The eject operation is ended in the state of Eject With Disc. (Initial 
value) 
1b : The eject operation is ended in the state of Eject Without Disc. 
*/ 

enum {
	EJECT_WITH_DISC = 0x00,
	EJECT_WITHOUT_DISC = 0x01,
};

/* Size8Disc: Correspondence setting to 8cm disc */
/*
Size8Disc ( Param7.    bit1 ) : Correspondence setting to 8cm disc 
1b : It doesn't accept to LOAD of 8cm disc. 
* EJECT is begun by detection of 8cm disc.
*/

enum {
	SIZE8DISC_UNACCEPT = 0x01,
};

void set_model(BYTE HiTempControl, BYTE LowTempControl, BYTE OSD, BYTE SpdifOut, BYTE DacQb, BYTE LrckFs,  BYTE StForm,  BYTE Composit,  BYTE YC, BYTE Component, BYTE TextFirstChar, BYTE TextSecondChar, BYTE Size8Disc, BYTE FullEject);

/* ------------------------------------- */
/* Name: call_set_type_info()
* Source: 3.2.3 [8003]
* Command Description: 
*      The current basic setting value information is acquired. 
*      The information is obtained with SET_TYPE_INFO (Refer to the status). 
*/
void call_set_type_info();

/*-------------------------------------*/
/* Name: call_set_model_info()
* Source: 3.2.4 [8004]
* Command Description: 
*      The current detailed setting value information is acquired. 
*      The information is obtained with SET_MODEL_INFO (Refer to the status). 
*/
void call_set_model_info();

/* ------------------------------------- */
/* Name: disc_load_eject()
* Source: 3.2.5 [8005]
* Command Description: 
*      For disc, Loading / EJECT and subsequent replay operation will be 
* started. 
*/

/* SelectDisc: Specify DISC to control */
/*
SelectDisc ( Param0.    bit0 - 3 ) : Specify DISC to control 
1h:  Specify current slot to control (Current) 
*/

enum {
	SPEC_DISC = 0x01,
};

/* MechaMode: Specify mechanism control operation */
/*
MechaMode ( Param1.    bit0 - 3 ) : Specify mechanism control operation 
0h:  Start LOAD operation if disc is not detected. 
* If disc is detected, mechanism operation is not taken. 
1h:  Start EJECT operation If disc is detected. 
* If disc is not detected, mechanism operation is not taken. 
*/

enum {
	LOAD_DISC = 0x00,
	EJECT_DISC = 0x01,
};

/* LoadPlay : Specify disc control operation (Identification/Replay) */
/*
LoadPlay ( Param1.    bit4 - 7 ) : Specify disc control operation 
(Identification/Replay) 
0h:  No disc control operation is taken 
1h:  If disc is detected after mechanism control operation, disc 
identification starts. 
* If disc is not detected, mechanism operation is not taken. 
2h:  If disc is detected after mechanism control operation, disc 
identification and replay will start. 
* If disc is not detected, mechanism operation is not taken.
*/

enum {
	NODISCOP = 0x00,
	START_DISC_IDENT = 0x01,
	REPLAY_DISC_IDENT = 0x02,
};
void disc_load_eject(BYTE SelectDisc, BYTE LoadPlay, BYTE MechaMode);

/* ------------------------------------- */
/* Name: force_eject()
* Source: 3.2.6 [8006]
* Command Description: 
*      EJECT operation is compelling executed. 
*/
void force_eject();

/* ------------------------------------- */
/* Name: set_model_type()
* Source: 3.2.7 [8012]
* Command Description: 
*      Basic system setting (Setting defined per adopted product¡¯s individual 
* specification) is made. 
*      The setting is common with Model Type setting of the SET_TYPE command 
* (refer the command), but the target is only for effective setteing items 
* after Initialization period has done. 
*      Only if it is non-replaying period (NO DISC, STOP and etc.), this 
* command is enabled. 
*/

/* ModelType : Specify model type */
/*
ModelType ( Param0.    All ) : Specify model type 
07h:  Setting is made for model type 7 (for GAC) 
FFh:  Initializing of mechanism 
*/

enum {
	SET_MODEL_TYPE7 = 0x07,
	MECHA_INI = 0xFF,
};

/* Setup : Selection of amendment object of setting specified by ModelType */
/*
Setup ( Param1.    bit0 ) : Selection of amendment object of setting specified 
by ModelType 
0b:  The all setting items. (The setting target is only effective item after 
Initialization period) . 
1b:  The setting item that can be selected on the general setup menu . 
*/

enum {
	ALL_SETTING_ITEM = 0x00,
	SELECTABLE_SETTING_ITEM = 0x01,
};
void set_model_type(BYTE ModelType, BYTE Setup);

/* ------------------------------------- */
/* Name:initialize()
* Source: 3.2.8 [0101]
* Command Description: 
* Initialization request for PPM information and setting information that 
* stored in memory. 
* Each initialization request is able to set individually. 
*/

/* PpmInfo:    Clear request of PPM (Play Position Memory) inforamtion */ 
/*
PpmInfo ( Param0.  bit1 )  :    Clear request of PPM (Play Position Memory) 
inforamtion 
0b :  PPM information is not cleared 
1b :  PPM information is cleared 
*/

enum {
	PPM_UNCLEAR = 0x00,
	PPM_CLEAR = 0x01,
};

/* SetupClear:    Clear request of setting information that stored in memory */
/*
SetupClear ( Param0.    bit3 )    :    Clear request of setting information that 
stored in memory 
0b :  Start/Initial/Operation setting information that stored in memory are 
not initialized. 
1b :  Start/Initial/Operation setting information that stored in memory are 
initialized (Set Default value of System). 
*/ 

enum {
	SETTING_UNINITIALIZE = 0x00,
	SETTING_INITIALIZE = 0x01,
};
void initialize(BYTE SetupClear, BYTE PpmInfo);

/* ------------------------------------- */
/* Name:source_change()
* Source: 3.2.9 [0107]
* Command Description: 
*      Transition control of this system to switch to other system. 
*      Controlled functions by switching the system are ¡°Replay control¡±, 
*          ¡°output clock¡± and ¡°Disc spin¡± 
*/

/* Mode : Specify the condition at switching */
/*
Mode ( Param0.    bit0 ) : Specify the condition at switching 
0b :  Specify the transition to startup status of this system (Ready) 
* Ready for replay (waiting for replay order), clock output and Ready 
for spin disc (waiting for spin order). 
1b :  Specify the transition to startup status of other system (Ready) 
* Stop replay (Keep PPM information), Stop clock and Stop spin disc. 
*/

enum {
	STARTUP_THIS_SYSTEM = 0x00,
	STARTUP_OTHER_SYSTEM = 0x01,
};
void source_change(BYTE Mode);

/* Replay Control Command */
/*-------------------------------------*/
/* Name: play_key()
* Source: 3.3.1 [8021]
* Command Description: 
*      Start normal replay. 
*          * With VCD PBC-ON, PBC operation is performed. 
*/
void play_key();

/* ------------------------------------- */
/* Name: stop_key()
* Source: 3.3.2 [8022]
* Command Description: 
*      Stop replay. 
*      ( Stop : State of STOP to not maintain PPM information ) 
*      ( Pre-Stop : State of STOP to maintain PPM information ) 
*      ( PPM : Play Position Memory  ¡ú  Information at replay position ) 
* 
*/
void stop_key();

/* ------------------------------------- */
/* Name: pause_key()
* Source: 3.3.3 [8023]
* Command Description: 
*      Pause the replay temporarily
*/
void pause_key();
void step_f_key();
void step_b_key();

/* ------------------------------------- */
/* Name: fast_f_key()
* Source: 3.3.6 [8026]
* Command Description: 
*      Fast forward replay (Fixed speed) 
*/

/* Speed : Speed specified */
/*
Speed ( Param0.    All ) : Speed specified 
00h:  Speed not specified 
02h:  ¡Á2 speed 
03h:  ¡Á3 speed 
04h:  ¡Á4 speed 
08h:  ¡Á8 speed 
0Ah:  ¡Á10 speed 
10h:  ¡Á16 speed 
15h:  ¡Á21 speed 
20h:  ¡Á32 speed 
*/

enum {
	SPEED_UNSPECIFY = 0x00,
	SPEED_X2 = 0x02,
	SPEED_X3 = 0x03,
	SPEED_X4 = 0x04,
	SPEED_X8 = 0x08,
	SPEED_X10 = 0x0A,
	SPEED_X16 = 0x10,
	SPEED_X21 = 0X15,
	SPEED_X32 = 0x20,
};
void fast_f_key(BYTE Speed);
void fast_b_key(BYTE Speed);
void fast_f_auto_key();
void fast_b_auto_key();

/* ------------------------------------- */
/* Name: slow_f_key()
* Source: 3.3.10 [802A]
* Command Description: 
*      Forward direction low speed replay with VCD/DVD-Video (Fixed speed)
*/

/* Speed: Speed specified */
/*
Speed ( Param0.    All ) : Speed specified 
00h:  Speed not specified 
02h:  ¡Á1/2 speed 
04h:  ¡Á1/4 speed 
08h:  ¡Á1/8 speed 
10h:  ¡Á1/16 speed 
*/ 

enum {
	/* SPEED_UNSPECIFY = 0x00; */
	SPEED_X1_2 = 0x02,
	SPEED_X1_4 = 0x04,
	SPEED_X1_8 = 0x08,
	SPEED_X1_16 = 0x10,
};
void slow_f_key(BYTE Speed);
void slow_b_key(BYTE Speed);
void slow_f_auto_key();
void slow_b_ato_key();
void fast_slow_cancel_key();


/* ------------------------------------- */
/* Name: skip_f_key()
* Source: 3.3.15 [802F]
* Command Description: 
*      Jump to beggining of next Second Position. 
*      * Second Position 
(DVD-Video)  : Chapter (Program) 
(CD-DA)   : Track 
(VCD)   : Track 
(COMPRESS) : File 
*      * With VCD PBC-ON, PBC operation is performed. 
*/

/* Time : Time Skip Executed/not Executed */
/*
Time ( Param0.    bit0 ) : Time Skip Executed/not Executed 
0b:    Time Skip not Executed 
1b:    Time Skip Executed 
*  When only one Second Position exists in the First Position section, 
it moves to the replay position of 30 seconds later from the present 
instead of the movement to the following Second Position. 
(Only in the case that 30 seconds later position is included in same Second 
Position section.) 
*/ 

enum {
	TIME_SKIP_UNEXECUTE = 0x00,
	TIME_SKIP_EXECUTE = 0x01,
};
void skip_f_key(BYTE Time);
void skip_b_key(BYTE Time);
void skip_folder_f_key();
void skip_folder_b_key();
void play_pause_key();

/* ------------------------------------- */
/* Name: audio_key()
* Source: 3.3.20 [8041]
* Command Description: 
*      Switch audio
*/

/* Stereo : Stereo switching requested/not requested */
/*
Stereo ( Param0.    bit0 ) : Stereo switching requested/not requested 
0b:  Stereo switching not specified 
1b:  Stereo switching specified 
*/

enum {
	STEREO_SWITCH_UNSPECIFY = 0x00,
	STEREO_SWITCH_SPECIFY = 0x01,
};

void audio_key(BYTE Stereo);

/* ------------------------------------- */
/* Name: subp_key()
* Source: 3.3.21 [8042]
* Command Description: 
*      Sub-picture switching in DVD-V. 
*/

/* Output : Sub-picture output requested/not requested */
/*
Output ( Param0.    bit0 ) : Sub-picture output requested/not requested 
0b:  Sub-picture output not specified 
1b:  Sub-picture output specified 
*/

enum {
	SUBP_UNSPECIFY = 0x00,
	SUBP_SPECIFY = 0x01,
};
void subp_key(BYTE Output);
void subp_on_off_key();
void angle_key();
void top_menu_key();
void menu_key();
void mode_change_key();
void n_p_key();
void repeat_key();
void mix_key();
void scan_key();
void repeat_ab_key();

/* ------------------------------------- */
/* Name: direction_key()
* Source: 3.3.32 [8062]
* Command Description: 
*      Operation for up/down and left/right movement (e.g. cursor movement). 
*/

/* Direction : Specify direction */
/*
Direction ( Param0.    bit0 - 3 ) : Specify direction 
0h:  Select ¡°Down¡± direction 
1h:  Select ¡°Up¡± direction 
2h:  Select ¡°Right¡± direction 
3h:  Select ¡°Left¡± direction 
*/

enum {
	DIRECTION_DOWN = 0x00,
	DIRECTION_UP = 0x01,
	DIRECTION_RIGHT = 0x02,
	DIRECTION_LEFT = 0x03,
};
void direction_key(BYTE Direction);

/*
Picture ( Param0. bit0 - 2 ) : Specify page
00h: Home page
01h: Previous page
02h: Next page
*/
enum {
	PAGE_HOME = 0x00,
	PAGE_PREVIOUS = 0x01,
	PAGE_NEXT = 0x02
};

void page_key(BYTE picture);

/* ------------------------------------- */
/* Name: ten_key()
* Source: 3.3.33 [8063]
* Command Description: 
*      Numeric entry operation. 
*      * PBC operation is performed for VCD PBC-ON.
*/

/* Value : Specify entry numerical value */
/*
Value ( Param0.    bit0 - 3 ) : Specify entry numerical value 
0h:  Select number ¡°0¡± 
1h:  Select number ¡°1¡± 
2h:  Select number ¡°2¡± 
3h:  Select number ¡°3¡± 
4h:  Select number ¡°4¡± 
5h:  Select number ¡°5¡± 
6h:  Select number ¡°6¡± 
7h:  Select number ¡°7¡± 
8h:  Select number ¡°8¡± 
9h:  Select number ¡°9¡± 
*/

enum {
	NUMBER0 = 0x00,
	NUMBER1 = 0x01,
	NUMBER2 = 0x02,
	NUMBER3 = 0x03,
	NUMBER4 = 0x04,
	NUMBER5 = 0x05,
	NUMBER6 = 0x06,
	NUMBER7 = 0x07,
	NUMBER8 = 0x08,
	NUMBER9 = 0x09,
};
void ten_key(BYTE Value);

/* ------------------------------------- */
/* Name: enter_key()
* Source: 3.3.34 [8065]
* Command Description: 
*      Apply selected item and entered number. 
*      * PBC operation is performed for VCD PBC-ON. 
*/


/* Time : Time until execution beginning */
/*
Time ( Param0.    All ) : Time until execution beginning 
00h:      Immediate execution 
01 - 0Fh:  Execution after 1 - 15 seconds 
*/

enum {
	TIME_EXECUTE_NOW = 0x00,
	/* TIME_EXECUTE_WAIT = 0x01 - 0x0F */
};

void enter_key(BYTE Time);
void return_key();
void disc_prog_update();
void disc_menu_key();

void dvd_info_reset();