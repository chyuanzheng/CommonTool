#pragma once
//#include "base.h"
#include "CHardware.h"
#include "i2c/chip.h"
#include "3.h"
#include "4.h"
#include "osd2.h"
#include "osd3.h"
#include "GxxString.h"
#include "Hardware.h"
#define DVDDEBUG	0

class DVDHardware : public CHardware
{
	HWND hWnd;
public:
	SYS_START	sys_start;
	INQUIRY_INFO	inquiry_info;
	SYSMODE_INFO system_info;
	SET_RESP	 set_resp;
	CMD_RESP	 cmd_resp_status_info;
	CMD_FAIL	 cmd_resp_fail_info;
	CMD_ACT_STATUS_INFO	cmd_act_status_info;
	DISC_INFO	disc_info;
	PLAY_INFO	play_info;
	MEDIA_PLAY_INFO	media_play_info;
	DOMAIN_INFO	domain_info;
	FIRSTPOSITION_INFO	firstpostion_info;
	SECONDPOSITION_INFO	secondposition_info;
	FOLDER_INFO folder_info;	//文件夹信息
	FILENAME_INFO	filename_info;
	BYTE	text_type;
	TEXT_INFO	text_info;
	GxxString	cdda_text;
	BYTE epf_batch_data[1296];

	void PowerOn()
	{
		//Hardware::DVDPower(0);
		//Sleep(100);
		//dvd_info_reset();
		//Hardware::DVDPower(1);	// 将dvd断电再开,确保dvd初始化流程正确
		//Sleep(100);

		call_sysmode_info();
	}

	/*********************************
	
	*获取文件夹信息
	*
	
	***********************************/
	void Call_Folder_Information()
	{
		call_folder_info(0x0001, 0x00, 0x00);
	}

	BOOL Skipf()
	{
		skip_f_key(TIME_SKIP_UNEXECUTE);
		return 1;
	}
	/// <summary>
	/// 向前跳曲
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL Skipb()
	{
		skip_b_key(TIME_SKIP_UNEXECUTE);
		return 1;
	}
	/// <summary>
	/// 快进
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL FastF()
	{
		//fast_f_auto_key();
		fast_f_key(0);
		return 1;
	}
	/// <summary>
	/// 快退
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL FastR()
	{
		fast_b_key(0);
		return 1;
	}
	/// <summary>
	/// 返回碟片菜单
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDTopMenu()
	{
		top_menu_key();
		return 1;
	}

	/// <summary>
	/// 返回碟片菜单
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDMenu()
	{
		menu_key();
		return 1;
	}

	/// <summary>
	/// 切换语言
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDAudio_key()
	{
		audio_key(1);
		return 1;
	}

	/// <summary>
	/// 切换字幕
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDSubp_key()
	{
		subp_key(1);
		return 1;
	}

	/// <summary>
	/// 进出仓
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDEject()
	{
		if (system_info.Slot == 0)
		{
			call_sysmode_info();
			Sleep(20);
		}
		if (system_info.MechaStatus == 0x00)	// 碟在入碟口
		{
			disc_load_eject(SPEC_DISC, REPLAY_DISC_IDENT, LOAD_DISC);	// 入碟并且播放
		}
		else if (system_info.Slot = 0x3)
		{
			disc_load_eject(SPEC_DISC, NODISCOP, EJECT_DISC);
		}
		else
		{
			if (IsDiscIn())
			{
				disc_load_eject(SPEC_DISC, NODISCOP, EJECT_DISC);
				return 1;
			}
		}
		return 1;
	}
	/// <summary>
	/// 开机/待机
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDPower()
	{
		return 1;
	}

	/// <summary>
	/// 方向键上
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL KeyUp()
	{
		direction_key(DIRECTION_UP);
		return 1;
	}
	/// <summary>
	/// 方向键下
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL KeyDown()
	{
		direction_key(DIRECTION_DOWN);
		return 1;
	}
	/// <summary>
	/// 方向键左
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL KeyLeft()
	{
		direction_key(DIRECTION_LEFT);
		return 1;
	}
	/// <summary>
	/// 方向键右
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL KeyRight()
	{
		direction_key(DIRECTION_RIGHT);
		return 1;
	}
	/// <summary>
	/// 确认
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL KeyEnter()
	{
		enter_key(TIME_EXECUTE_NOW);
		return 1;
	}
	/// <summary>
	/// DVD停止
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL DVDStop()
	{
		stop_key();
		return 1;
	}
	/// <summary>
	/// DVD播放
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL Play()
	{
		play_key();
		return 1;
	}
	BOOL Pause()
	{
		pause_key();
		return 1;
	}
	BOOL DVDPlayPause()
	{
		play_pause_key();
		return 1;
	}
	/// <summary>
	/// A/B重复播放
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL MarkAB()
	{
		repeat_ab_key();
		return 1;
	}

	/// <summary>
	/// Switch Repeat setting (Not for VCD PBC-ON)
	/// </summary>
	/// <returns>是否成功执行</returns>
	bool DiscRepeat_Key()
	{
		repeat_key();
		return 1;
	}

	/// <summary>
	/// Still picture page switching in DVD-A/ DVD-VR.
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL HomePage()
	{
		page_key(PAGE_HOME);
		return 1;
	}
	BOOL NextPage()
	{
		page_key(PAGE_NEXT);
		return 1;
	}
	BOOL PreviousPage()
	{
		page_key(PAGE_PREVIOUS);
		return 1;
	}
	/// <summary>
	/// 随机播放
	/// </summary>
	/// <returns>是否成功执行</returns>
	BOOL Random()
	{
		return 0;
	}
	BOOL DvdUser_cont(WORD x, WORD y)
	{
		int DVDposX = x*720/800;
		int DVDposY = y*576/480;
	
		if(DVDposX <1 && DVDposX>720)
		{
			assert(false);
			return 0;
		}
		if(DVDposY <1 && DVDposY>576)
		{
			assert(false);
			return 0;
		}
		//user_cont(0x05h, DVDposY);
		user_cont(0x05, DVDposX, DVDposY);
//		RETAILMSG(COUT_MSG, (TEXT("calculate x=%d,y=%d\r\n"), DVDposX, DVDposY));
		//user_cont(0x01, 0x0002);
		return 1;
	}
	
	/// <summary>
	/// Angle switching in DVD-V/DVD-A.
	/// </summary>
	/// <returns>是否成功执行</returns>
	bool DVDANGLE_KEY()
	{
		//angle_key();
		set1_dvd(3);
		Sleep(100);
		//call_inquiry_info(0);
		/*call_set_type_info();
		Sleep(50);
		call_set_model_info();*/
		return 1;
	}

	void DVDReset()
	{
		initialize(SETTING_INITIALIZE, PPM_UNCLEAR);
	}

	/// <summary>
	/// Display disc menu OSD screen.
	/// </summary>
	/// <returns>是否成功执行</returns>
	bool DisplayDiscMenu()
	{
		disc_menu_key();
		return 1;
	}

	void EnterDvd()
	{
		source_change(0);
		call_sysmode_info();
	}

	void LeaveDvd()
	{
		source_change(1);
	}

	void PlayCD(int TrackNo)
	{
		search_play_unit(0x4, 0x0, firstpostion_info.FirstPositionNo, TrackNo);
	}

	void PlayCDDA(int TrackNo)
	{
		search_play_unit(0x4, 0x0,	0, TrackNo);
	}

	void GetCDDATextInfo(BYTE TextType, BYTE TrackNo, BYTE PageNo, BYTE SelectInfo)
	{
		call_text_info(TextType, TrackNo, PageNo, SelectInfo);
		text_type = TextType;
	}
	BOOL IsDiscIn()
	{
		if (system_info.Slot == 0)
		{
			call_sysmode_info();
			Sleep(20);
		}
		return system_info.Slot > 1;
	}
	void Init(HWND hwnd)
	{
		hWnd = hwnd;
		DWORD dwTheadID = 0;
		CreateThread(NULL, 0, EPFReadThread, (LPVOID)this, 0, &dwTheadID);
	}
	static DWORD EPFReadThread(LPVOID lpParam)
	{
		DVDHardware *p = (DVDHardware*)lpParam;
		HANDLE hEvent1 = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, L"EPF_READ" );
		HANDLE hEvent2 = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, L"EPF_BATCH_READ");
		if (!hEvent1 || !hEvent2)
		{
			return 0;
		}
		HANDLE hEvent[2] = {hEvent1, hEvent2};
		while (1)
		{
			//DWORD dwRet = WaitForMultipleObjects(2, hEvent, 0, INFINITE);
			DWORD dwRet = WaitForSingleObject(hEvent1, INFINITE);
			if (dwRet == WAIT_OBJECT_0)
			{
				BYTE epf_msg[17] = {0};
				int len;
				while(EpfRead(epf_msg, &len))
				{
					for(int i=0;i<17;i++)
					{
						RETAILMSG(0, (TEXT("[%02X] "), epf_msg[i]));
					}
					RETAILMSG(0, (TEXT("\r\n")));
					p->ParseStatus(epf_msg);
				}
			}
			if (dwRet == WAIT_OBJECT_0+1)
			{
				int len = 0;
				EpfRead(p->epf_batch_data, &len);
				RETAILMSG(1, (TEXT("EPF batch read len = %d\r\n"), len));
			}
		}
		return 0 ;
	}
	void ParseStatus(BYTE *epf_msg)
	{
		switch(epf_msg[0])
		{
		case 0x03:	// data info status
			{
				RETAILMSG(DVDDEBUG, (TEXT("data info status\r\n")));
				break;
			}
		case 0x0C:	// program control status / system info status
			{
				RETAILMSG(DVDDEBUG, (TEXT("program control status / system info status\r\n")));
				switch(epf_msg[1])
				{
				case 0x01:	// system_start
					{
						RETAILMSG(DVDDEBUG, (TEXT("system start\r\n")));
						parse_system_start(&sys_start, epf_msg);
						if (sys_start.Initial == 0)
						{
							RETAILMSG(DVDDEBUG, (TEXT("system is factory\r\n")));
							// 删除保存的记忆
							//initialize(SETTING_INITIALIZE, PPM_UNCLEAR);
						}
						else
						{
							RETAILMSG(DVDDEBUG, (TEXT("system is settuped\r\n")));
							//initialize(SETTING_INITIALIZE, PPM_UNCLEAR);
							//set_end();
						}
						break;
					}
				case 0x03:	// inquiry info
					{
						parse_inquiry_info(&inquiry_info, epf_msg);
						break;
					}
				case 0x07:	// sysmode info
					{
						RETAILMSG(DVDDEBUG, (TEXT("sysmode info\r\n")));
						parse_sysmode_info(&system_info, epf_msg);
						if (system_info.Initial == 0)
						{
							// 初始化过程中
							if (sys_start.Initial == 0)
							{
								// 第一次初始化
								set_type(MODEL_TYPE7, NODEST, NOMECHA);
							}
							else
							{
								// 机芯已经记忆状态
								//set_model(NOHITEMP, NOLOWTEMP, NOOSD, NOSPDIFOUT, FIX_TO_24BITS, FRQ_192KHZ, I2S, COMPOSIT_ON, YC_ON, COMPONENT_ON, TEXTFIRSTCHAR_ISO8859_1, TEXTSECONDCHAR_CN, EJECT_WITH_DISC, SIZE8DISC_UNACCEPT);
								//set_type(MODEL_TYPE7, NODEST, NOMECHA);
								//set_type(NOMODEL, NODEST, NOMECHA);
								set_end();								
							}
						}
						else
						{	
							if(system_info.Slot)
							{
								// load 完成
								GXNotify::SendNotifySync(hWnd, "load_disc", system_info.MechaStatus, 0);
								call_disc_info(1);
							}
							GXNotify::SendNotifySync(hWnd, "sysmode_info", (DWORD)&system_info, 0);
							//call_disc_info(1);
						}
						
						break;
					}
				case 0x09:	//USERMENU_INFO
					{
						RETAILMSG(DVDDEBUG, (TEXT("USERMENU_INFO\r\n")));
						break;
					}
				case 0x0A:	// set resp
					{
						RETAILMSG(DVDDEBUG, (TEXT("SET_RESP\r\n")));
						parse_set_resp(&set_resp, epf_msg);
						break;
					}
				case 0x0E:	// cmd act status info
					{
						parse_cmd_act_status_info(&cmd_act_status_info, epf_msg);
						if (cmd_act_status_info.ActStatus == 0x00)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_ACT_STATUS_INFO(End) [%02X][%02X]\r\n"), cmd_act_status_info.ActGroupID, cmd_act_status_info.ActSubID));

							if (cmd_act_status_info.ActGroupID == 0x80)
							{
								if (cmd_act_status_info.ActSubID == 0x01)
								{
									// set_type end
									
									// cs4344 i2s
									// cs4345 left justify
									// cs4346 right justify 24
									// cs4348 right justify 16
									
									//set_model(0xA6, NOLOWTEMP, NOOSD, NOSPDIFOUT, FIX_TO_24BITS, FRQ_192KHZ, I2S, COMPOSIT_ON, YC_ON, COMPONENT_OFF, TEXTFIRSTCHAR_ISO8859_1, TEXTSECONDCHAR_CN, SIZE8DISC_UNACCEPT, EJECT_WITH_DISC);
									if (cmd_resp_status_info.CmdResp == 0x00 && cmd_resp_status_info.RespGroupID == 0x80 && cmd_resp_status_info.RespSubID == 0x01)
									{
										set_model(0xA6, NOLOWTEMP, NOOSD, SPDIFOUT, FIX_TO_24BITS, FRQ_192KHZ, I2S, COMPOSIT_ON, YC_ON, COMPONENT_OFF, TEXTFIRSTCHAR_ISO8859_1, TEXTSECONDCHAR_CN, SIZE8DISC_UNACCEPT, EJECT_WITH_DISC);
									}
									RETAILMSG(DVDDEBUG, (TEXT("Execution End of set_type \r\n")));
									
								}
								if (cmd_act_status_info.ActSubID == 0x02)
								{
									// set_model end
									set1_dvd(3);
									//Sleep(100);
									//set_end();
									//RETAILMSG(DVDDEBUG, (TEXT("Execution End of set_model \r\n")));
								}
							}
							if (cmd_act_status_info.ActGroupID == 0x07)
							{
								set_end();
							}
						}
						else if (cmd_act_status_info.ActStatus == 0x01)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_ACT_STATUS_INFO(Start) [%02X][%02X]\r\n"), cmd_act_status_info.ActGroupID, cmd_act_status_info.ActSubID));
						}
						break;
					}
				case 0x50:	//CHANGE_STATUS_INFO
					{
						RETAILMSG(DVDDEBUG, (TEXT("CHANGE_STATUS_INFO\r\n")));
						
						break;
					}
				}
				break;
			}
		case 0x0D:	// text info status
			{
				RETAILMSG(DVDDEBUG, (TEXT("text info status\r\n")));
				switch(epf_msg[1])
				{
				case 0x0A:	//DISC_NAME_INFO
					{
						RETAILMSG(DVDDEBUG, (TEXT("DISC_NAME_INFO\r\n")));
						break;
					}
				case 03:	//FILE_NAME_INFO
					{
						RETAILMSG(DVDDEBUG, (TEXT("FILE_NAME_INFO\r\n")));
						parse_file_name_info(&filename_info, epf_msg);
						GXNotify::SendNotifySync(hWnd, "filename_info", (DWORD)&filename_info, 0);
						break;
					}
				case 0x02:	// text info
					{
						RETAILMSG(DVDDEBUG, (TEXT("text start\r\n")));
						parse_text_info(&text_info, epf_msg, text_type);
						if (text_type == 0x8F)
						{
						}
						else
						{
							switch(text_info.text_info_not_0x8fh.CharCode)
							{
							case 0x00:	// ISO 8859-1
								{
									GxxString str;
									str.UTF8ToUNICODE(text_info.text_info_not_0x8fh.TextData);
									cdda_text += str;
									if (text_info.text_info_not_0x8fh.PageNo == text_info.text_info_not_0x8fh.LastPageNo)
									{
										GXNotify::SendNotifySync(hWnd, "text_info", (DWORD)&cdda_text, 0);
									}
									break;
								}
							case 0x01:	// ISO/IEC 646
								{
									break;
								}
							case 0x80:	// SHIFT JIS Kanji and JIS Katakana
								{
									break;
								}
							case 0x81:	// Korean character
								{
									break;
								}
							case 0x82:	// Mandarin character
								{
									GxxString str;
									str.FromCustomCode(936, text_info.text_info_not_0x8fh.TextData, 8);
									cdda_text += str;
									if (text_info.text_info_not_0x8fh.PageNo == text_info.text_info_not_0x8fh.LastPageNo)
									{
										GXNotify::SendNotifySync(hWnd, "text_info", (DWORD)&cdda_text, 0);
										RETAILMSG(1, (TEXT("cdda = %s\r\n"), cdda_text.GetData()));
									}
									break;
								}
							default:
								{

								}
							}
					
						}
					}
				}
				break;

			}
		case 0x0E:	// media info status
			{
				RETAILMSG(DVDDEBUG, (TEXT("media info status\r\n")));
				switch(epf_msg[1])
				{
				case 0x01: // disc info
					{
						RETAILMSG(DVDDEBUG, (TEXT("disc info\r\n")));
						parse_disc_info(&disc_info, epf_msg);
						
					//	RETAILMSG(1, (TEXT("(%02X) "), disc_info.DATA_block.FolderNs));
					//	RETAILMSG(1, (TEXT("(%02X) "), disc_info.DATA_block.FileNs));

						
						GXNotify::SendNotifySync(hWnd, "disc_info", (DWORD)&disc_info, 0);
						break;
					}
				case 0x02:
					{
						RETAILMSG(DVDDEBUG, (TEXT("firstpostion info\r\n")));
						parse_firstposition_info(&firstpostion_info, epf_msg, disc_info.SetMediaType);
						GXNotify::SendNotifySync(hWnd, "firstposition_info", (DWORD)&firstpostion_info, disc_info.SetMediaType);
						break;
					}
				case 0x03:
					{
						RETAILMSG(DVDDEBUG, (TEXT("secondpostion info\r\n")));
						parse_secondposition_info(&secondposition_info, epf_msg, disc_info.SetMediaType);
						GXNotify::SendNotifySync(hWnd, "secondposition_info", (DWORD)&secondposition_info, disc_info.SetMediaType);
						break;
					}
				case 0x04:	// domain info
					{
						RETAILMSG(DVDDEBUG, (TEXT("domain info\r\n")));
						parse_domain_info(&domain_info, epf_msg);
						GXNotify::SendNotifySync(hWnd, "domain_info", (DWORD)&domain_info, 0);
						break;
					}
				case 0x05:
					{
						parse_folder_info(&folder_info, epf_msg, 0x00);
						GXNotify::SendNotifySync(hWnd, "folder_info", (DWORD)&folder_info, 0);
						RETAILMSG(DVDDEBUG, (TEXT("FOLDER_INFO\r\n")));
						break;
					}
				}
				break;
			}
		case 0x0F:	// replay info status
			{
				switch(epf_msg[1])
				{
				case 0x01:
					{
						// play info
						RETAILMSG(DVDDEBUG, (TEXT("play info\r\n")));
						parse_play_info(&play_info, epf_msg);
						GXNotify::SendNotifySync(hWnd, "dvd_play_info", (DWORD)&play_info, 0);
						break;
					}
				case 0x02:
					{
						RETAILMSG(DVDDEBUG, (TEXT("media info\r\n")));
						// media play info
						parse_media_play_info_CDDA_VCD(&media_play_info, epf_msg, disc_info.SetMediaType);
						GXNotify::SendNotifySync(hWnd, "media_play_info", (DWORD)&media_play_info, (DWORD)&disc_info);
						break;
					}
				}
				break;
			}
		case 0x10:	// copy info status
			{
				RETAILMSG(DVDDEBUG, (TEXT("copy info status\r\n")));
				break;
			}

		case 0x11:	// cmd response status
			{	
				switch(epf_msg[1])
				{
				case 0x01:
					{
						parse_cmd_resp(&cmd_resp_status_info,epf_msg);
						if(cmd_resp_status_info.CmdResp == 0x00)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_RESP(Accept) [%02X][%02X]\r\n"), cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID));
							GXNotify::SendNotifySync(hWnd, "NotifyCommandAccept", cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID);

						}
						else if(cmd_resp_status_info.CmdResp == 0x02)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_RESP(SysReject) [%02X][%02X]\r\n"), cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID));
							GXNotify::SendNotifySync(hWnd, "NotifyCommandFail", cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID);
						}
						else if(cmd_resp_status_info.CmdResp == 0xff)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_RESP(Fail) [%02X][%02X]\r\n"), cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID));
						}
						else if(cmd_resp_status_info.CmdResp == 0x03)
						{
							RETAILMSG(DVDDEBUG, (TEXT("CMD_RESP(Error) [%02X][%02X]\r\n"), cmd_resp_status_info.RespGroupID, cmd_resp_status_info.RespSubID));
						}
						break;
					}
				case 0x02:
					{
						parse_cmd_fail(&cmd_resp_fail_info,epf_msg);
						RETAILMSG(COUT_MSG, (TEXT("CMD Fail = 0x%x GroupID = 0x%x subID = 0x%x\r\n"), cmd_resp_fail_info.CmdFail, cmd_resp_fail_info.FailGroupID, cmd_resp_fail_info.FailSubID));
						GXNotify::SendNotifySync(hWnd, "NotifyCommandFail", cmd_resp_fail_info.FailGroupID, cmd_resp_fail_info.FailSubID);
						break;
					}
				}
				
				
				
				break;
			}
		case 0x8:	// setting control info status (non-playing status)
			{
				RETAILMSG(DVDDEBUG, (TEXT("setting control info status\r\n")));
				break;
			}
		case 0x9:	// setting control info status (non-playing status)
			{
				RETAILMSG(DVDDEBUG, (TEXT("setting control info status\r\n")));
				break;
			}
		case 0x0A:	// setting control info status (all time)
			{
				RETAILMSG(DVDDEBUG, (TEXT("setting control info status\r\n")));
				break;
			}
		case 0x0B:	// setting control info status (all time)
			{
				RETAILMSG(DVDDEBUG, (TEXT("setting control info status\r\n")));
				break;
			}
		case 0x80:
			{
				switch(epf_msg[1])
				{
				case 0x02:
					{
						// [80] [04] [00] [00] [00] [74] [07] [00] [82] [01]  [00] [00] [00] [00] [00] [74] [00] 
						// [80] [04] [00] [00] [00] [74] [07] [00] [82] [01]  [00] [00] [00] [00] [00] [74] [00] 
						// [80] [04] [A6] [00] [00] [35] [03] [00] [01] [00]  [00] [00] [00] [00] [00] [15] [00] 
						// [80] [04] [A6] [00] [00] [35] [03] [00] [01] [00]  [00] [00] [00] [00] [00] [15] [00] 
						RETAILMSG(1, (TEXT("0x80---------\r\n")));
						break;
					}
				case 0x03:
					{
						//[80] [03] [07] [60] [01] [00] [00] [00] [00] [00] [00] [00] [00] [00] [00] [E5] [00] 
						//[80] [04] [A6] [00] [00] [35] [03] [00] [82] [02] [00] [00] [00] [00] [00] [94] [00] 
						for(int i=0;i<17;i++)
						{
							RETAILMSG(1, (TEXT("[%02X] "), epf_msg[i]));
						}
						RETAILMSG(1, (TEXT("\r\n")));
						break;
					}
				case 0x04:
					{
						for(int i=0;i<17;i++)
						{
							RETAILMSG(1, (TEXT("[%02X] "), epf_msg[i]));
						}
						RETAILMSG(1, (TEXT("\r\n")));
						break;
					}
				}
				break;
			}
		}
	}
};