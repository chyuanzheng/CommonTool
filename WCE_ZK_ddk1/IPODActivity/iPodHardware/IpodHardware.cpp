#include "stdafx.h"
//#include "base.h"
#include "IpodHardware.h"


IpodHardware* IpodHardware::pInstance = NULL;

DWORD IpodHardware::ReadThread(LPVOID lpParam)
{
	int		hasError = 0;
	COMSTAT comstat;				// COMSTAT struct 
	BYTE    aCode = 0;
	DWORD	dwError;
	BYTE	CMD[256] = {0};
	int		iLen = -1;
	BYTE	checksum = 0;
	BOOL bRecving = 0;
	IpodHardware *p = (IpodHardware *)lpParam;
#ifdef USESERIAL
	if (p->IPODSerial.IsOpen())
	{
		RETAILMSG(1,(TEXT("COM3 is Opened\r\n")));
		p->IPODSerial.Purge();
	}
	else
	{
		RETAILMSG(1,(TEXT("COM3 is Closed\r\n")));
		return 0;
	}
	// 提高线程优先级
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	p->iNum = 0;
	int p_status = P_NONE;
	vector<BYTE> vecData;
	int data_len = 0;
	while (1)
	{
		//RETAILMSG(1, (TEXT("Serial Read +++++++++++++++++++++++++\r\n")));
		p->IPODSerial.WaitEvent();
		//RETAILMSG(1, (TEXT("Serial Read +++++++++++--------------+\r\n")));
		if (p->IPODSerial.GetEventType()&EV_ERR)
		{
			::ClearCommError(p->IPODSerial.GetCommHandle(), &dwError, &comstat);
			//DEBUGMSG(1,(_T("COM%d rx err:0x%X \r\n"),ceSeries->m_dwDevIndex, dwError));
		}

		//p->IPODSerial.Read(&aCode,1);
		BYTE data[1024] = {0};
		DWORD len = 0;
		p->IPODSerial.Read(data,1024, &len);

		for (int i=0; i<len; i++)
		{
			aCode = data[i];
			if (aCode == 0x55)
			{
				if (p->iNum > 2)
				{
					if (CMD[p->iNum-1] == 0xFF)
					{
						p->iNum = 2;
						CMD[0] = 0xFF;
						CMD[1] = 0x55;
						continue;
					}
				}
			}
			if (p->iNum == 2)
			{
				if (CMD[0] == 0xFF && CMD[1] == 0x55)
				{
					iLen = aCode;
					CMD[p->iNum++] = aCode;
				}
				else
				{
					CMD[p->iNum++] = aCode;
					hasError = 1;
				}
			}
			else if (p->iNum == iLen+4-1)	//最后一个字节
			{
				checksum = aCode;
				CMD[p->iNum++] = aCode;
				if (p->Checksum(&CMD[2], iLen) == checksum)
				{
					hasError = 0;
					p->ipodQueue.join(&CMD[2]);
					SetEvent(p->hHandlerEvent);
					p->IsCmdAck = 1;
					p->failTimes = 0;
					RETAILMSG(0, (TEXT("Get a msg from ipod\r\n")));
					//PostMessage(p->hWnd, WM_IPOD, 0, 0);
				}
				else
				{
					hasError = 1;
				}
				p->iNum = 0;
				memset(CMD, 0, 256);
				iLen = -1;
			}
			else
			{
				if (p->iNum>2)
				{
					if (CMD[p->iNum-2] == 0xFF && CMD[p->iNum-1] == 0x55)
					{
						if (hasError == 1)
						{
							p->iNum = 2;
							iLen = aCode;
							CMD[0] = 0xFF;
							CMD[1] = 0x55;
							CMD[p->iNum++] = aCode;
						}
						else
						{
							CMD[p->iNum++] = aCode;
						}
					}
					else
					{
						CMD[p->iNum++] = aCode;
					}
				}
				else
				{
					CMD[p->iNum++] = aCode;
				}

			}
			if (p->iNum == 255)
			{
				p->iNum = 0;
			}
		}
	}
#endif
#ifdef USBIPOD
	WaitForSingleObject(p->m_hEventAttach,INFINITE);
	p->m_hEventRead = OpenEvent( EVENT_ALL_ACCESS ,FALSE, IPOD_E);
	while (1)
	{
		if (WAIT_OBJECT_0!=WaitForSingleObject(p->m_hEventRead,INFINITE))
		{
			continue;
		}
		// Attempt a synchronous read operation.
		BYTE  CMD[IPOD_MAXBYTE];
		DWORD nBytesRead;
		BOOL bResult= ReadFile(p->m_hDrv, CMD, IPOD_MAXBYTE, &nBytesRead, NULL) ;
		p->ipodQueue.join(&CMD[1], 255);
		SetEvent(p->hHandlerEvent);
	}
#endif
}

DWORD IpodHardware::HandlerThread(LPVOID lpParam)
{
	IpodHardware *pIpodHardware = (IpodHardware *)lpParam;
	while (1)
	{
		WaitForSingleObject(pIpodHardware->hHandlerEvent, INFINITE);
		BYTE CMD[256] = {0};
		while (pIpodHardware->ipodQueue.fetch(CMD))
		{
			BYTE byteLingo = CMD[1];
			RETAILMSG(IPODDEBUG,(TEXT("lingo = 0x%x\r\n"), byteLingo));
			switch(byteLingo)
			{
			case 0:	// general lingo
				{
					WORD wType = CMD[2];
					RETAILMSG(IPODDEBUG,(TEXT("wType = 0x%x\r\n"), wType));
					switch(wType)
					{
					case 0x0:	// RequestIdentify ipod要求认证
						{
							// 当使用UART串口连接时,认证过程开始于附件设备传送同步字节后
							// 当传送同步字节后,附件需要等待20ms,然后传送 Command 0x01:Identify
							// 或者 Command 0x13:IdentifyDeviceLingoes 通知 ipod 自己支持的lingoes
							//	The accessory should next check the version of the General lingo protocol supported by the iPod, by
							//	sending “Command 0x0F: RequestLingoProtocolVersion” (page 83) using the ID of the General lingo.
							//	The iPod responds with a “Command 0x10: ReturnLingoProtocolVersion” (page 84) packet containing
							//	the protocol version of the General lingo.
							//
							//	Note: If the iPod does not respond, the accessory should retry the IdentifyDeviceLingoes and
							//		  RequestLingoProtocolVersion commands. If the retry also fails, the accessory should assume that
							//		  these commands are not supported. If an iPod fails to ACK the IdentifyDeviceLingoes command,
							//		  the accessory should reidentify using the Identify command.
							// 如果设备收到 RequestIdentify 包,必须重新认证
							// 一旦附件设备包传输开始,最大的字节传输时间为25ms,如果命令字节间的延时
							// 超过25ms,ipod 丢弃已经收到的字节,直到下一个有效的包到来
							// 当 ipod 的系统负载过重时,它发出的包也可以超过25ms的限制
							// 设备初始化流程
							//	1. Send a sync byte; this should wake up the iPod.
							//	2. Wait for 20 ms.
							//	3. Send the command packet with sync byte.

							// 授权
							// 授权是 ipod 验证附件是否一个拥有授权的方法,一些特定的功能必须授权后
							// 才可以使用,使用串口连接和usb连接要求的授权不同.授权开始后,将进入一个最长达
							// 75s的后台授权过程,这时附件设备可以使用未授权的功能,直到授权过程结束

							// 在无授权的时候,大部分的 lingo 0x4 命令可以使用,所以我们需要进入 lingo 0x4 模式
							// 本程序认证步骤
							// 1. 不断发送 RequestiPodName 以判断 ipod 是否已经连接到附件上
							// 2. ipod 连接后,发送 RequestpIpodHardware->iPodModelNum 判断 ipod 型号
							// 3. 如果系统中包含 apple cp, 进入认证过程, 使用 lingoes 1 & 3 来控制ipod,和显示状态
							// 4. 如果系统中不包含 cp, 如果 ipod 属于 cracked ipod, 同3
							// 5. 如果系统中不包含 cp, 并且非 cracked ipod, 进入 lingo 0x4, 使用 extend 命令控制ipod和显示状态

							break;
						}
					case 0x2:	// ACK
						{
							//0x00 = Success (OK)
							//0x01 = ERROR: Unknown database category
							//0x02 = ERROR: Command failed
							//0x03 = ERROR: Out of resources
							//0x04 = ERROR: Bad parameter
							//0x05 = ERROR: Unknown ID
							//0x06 = Command Pending. See Table 5-12 (page72) .
							//0x07 = ERROR: Not authenticated
							//0x08 = ERROR: Bad authentication version
							//0x09 Reserved
							//0x0A ERROR: Certificate invalid
							//0x0B ERROR: Certificate permissions invalid
							//0x0C – 0x10 Reserved
							//0x11 = ERROR: Invalid accessory resistor ID value
							//0x12 – 0xFF Reserved
							if (CMD[3] != 0)
							{
								RETAILMSG(1,(TEXT("ack info = 0x%x id = 0x%x\r\n"), CMD[3], CMD[4]));
								if (CMD[3] == 0x4 && CMD[4] == 0x38)
								{
									// 不支持 IDPS
									pIpodHardware->IdentifyDeviceLingoes(1, pIpodHardware->ipodCP.deviceID);
								}
							}
							if (CMD[3] == 0 && CMD[4] == 0x30)
							{
								// 支持 IDPS
								// 发送第一个FID
								DWORD deviceID = pIpodHardware->ipodCP.deviceID;
								DWORD deviceOption = 0xE;
								BYTE accessoryLingoes[] = {0x00, 0x00,  3, 0x00, 0x02, 0x04, deviceOption>>24, deviceOption>>16, deviceOption>>8, deviceOption,deviceID>>24, deviceID>>16, deviceID>>8, deviceID};
								pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accessoryLingoes), accessoryLingoes);

								//BYTE accessoryLingoes[] = {0x00, 0x03, 3, 0x00, 0x02, 0x04, ,deviceID>>24, deviceID>>16, deviceID>>8, deviceID};
								//pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accessoryLingoes), accessoryLingoes);
							}

							break;
						}
					case 0x8:	// ReturniPodName
						{
							// 返回IPOD 名字
							if (pIpodHardware->iPodModel == NOIPOD)
							{
								char szSongname[MAX_PATH] = {0};
								for (int i=0;i<CMD[0]-3;i++)
								{
									szSongname[i] = CMD[3+i];
								}

								GxxString str;
								str.UTF8ToUNICODE(szSongname);
								pIpodHardware->sIpodName = str;
								//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_NAME, (LPARAM)&str);
								pIpodHardware->SendMsg(WM_IPOD, IPOD_NAME, (LPARAM)&str);
								Sleep(1);
								pIpodHardware->RequestiPodModelNum();
								pIpodHardware->iPodModel = MUSICIPOD;
							}
							break;
						}
					case 0xE:	// ReturnpIpodHardware->iPodModelNum
						{
							DWORD ipodID = CMD[3]<<24 | CMD[4]<<16 | CMD[5]<<8 | CMD[6];
							RETAILMSG(IPODDEBUG,(TEXT("ipodID = 0x%x\r\n"), ipodID));
							switch(ipodID>>16)
							{
							case 0x0003:	// 3G iPod
								{
									break;
								}
							case 0x0004:	// iPod mini
								{
									break;
								}
							case 0x0005:	// 4G iPod
								{
									pIpodHardware->iPodModel = VIDEOIPOD;	
									break;
								}
							case 0x0006:	// iPod photo
								{
									break;
								}
							case 0x0007:	// 2G iPod mini
								{
									break;
								}
							case 0x000B:	// 5G iPod
								{
#ifndef IPOD_CRACK_TEST
									pIpodHardware->iPodModel = VIDEOIPOD;
#endif	
									break;
								}
							case 0x000C:	// iPod nano
								{
									break;
								}
							case 0x0010:	// 2G iPod nano
								{
									break;
								}
							case 0x0011:	// iPhone
								{
									pIpodHardware->iPodModel = VIDEOIPOD;	
									break;
								}
							case 0x0013:	// iPod classic
								{
									pIpodHardware->iPodModel = VIDEOIPOD;
									break;
								}
							case 0x0014:	// 3G iPod nano
								{
									break;
								}
							case 0x0015:	// iPod touch
								{
									pIpodHardware->iPodModel = VIDEOIPOD;	
									break;
								}
							case 0x0017:
								{
									pIpodHardware->iPodModel = VIDEOIPOD;	
									break;
								}
							default:
								{
									// 不支持破解的ipod
#ifndef IPOD_CRACK_TEST
									pIpodHardware->iPodModel = VIDEOIPOD;						;			 
#endif								
								}
							}
#ifdef USESERIAL
							if (pIpodHardware->iPodModel == MUSICIPOD)
							{
								pIpodHardware->ipodAuthMode = IPOD_NOAUTH;
								pIpodHardware->IdentifyDeviceLingoes(0); // 不要求授权
								pIpodHardware->SetiPodPreferences_AudioOut();
								// 进入lingoes 4
								pIpodHardware->EntryHighControlMode();
								// 设置自动时间发送
								pIpodHardware->SetPlayStatusChangeNotification();
								// 开始播放并且获取播放状态
								pIpodHardware->ResetDBSelection();
								pIpodHardware->SelectDBRecord(IpodHardware::CATE_TRACK, 0);
								pIpodHardware->PlayCurrentSelection(0);
								pIpodHardware->IpodPlay();
							}
							else
#endif
							
							{
								if (pIpodHardware->ipodCP.IsExisted())
								{
									pIpodHardware->ipodAuthMode = IPOD_CPAUTH;
									//pIpodHardware->StartIDPS(pIpodHardware->GetTransID());
									// 使用旧的方法验证
									pIpodHardware->IdentifyDeviceLingoes(1);
								}
								else
								{
									pIpodHardware->ipodAuthMode = IPOD_NOAUTH;
									pIpodHardware->IdentifyDeviceLingoes(0); // 不要求授权
									pIpodHardware->SetiPodPreferences_AudioOut();
									// 进入lingoes 4
									pIpodHardware->EntryHighControlMode();
									// 设置自动时间发送
									pIpodHardware->SetPlayStatusChangeNotification();
									// 开始播放并且获取播放状态
									pIpodHardware->ResetDBSelection();
									pIpodHardware->SelectDBRecord(IpodHardware::CATE_TRACK, 0);
									pIpodHardware->PlayCurrentSelection(0);
									pIpodHardware->IpodPlay();
								}
							}

							break;
						}
					case 0x27:	// GetAccessoryInfo
						{
							// ipod请求附件信息
							RETAILMSG(1, (TEXT("Get AC info 0x%x\r\n"), CMD[3])); 
							switch(CMD[3])	// Accessory Info Type
							{

								// Accessory info capabilities 0x00
								// Accessory name 0x01
								// Accessory minimum supported iPod firmware version 0x02
								// Accessory minimum supported lingo version 0x03
								// Accessory firmware version 0x04
								// Accessory hardware version 0x05
								// Accessory manufacturer 0x06
								// Accessory model number 0x07
								// Accessory serial number 0x08
								// Accessory incoming maximum payload size 0x09
								// Reserved 0x0A-0xFF
							case 0:
								{
									pIpodHardware->RetAcInfoCap();
									break;
								}
							case 1:
								{
									pIpodHardware->RetAcName(0x1, L"VW made for iPod");
									break;
								}
							case 2:
								{
									break;
								}
							case 3:
								{
									break;
								}
							case 4:
								{
									pIpodHardware->RetAcFirmwareVersion();
									break;
								}
							case 5:
								{
									pIpodHardware->RetAcHardVersion();
									break;
								}
							case 6:
								{
									pIpodHardware->RetAcName(0x6, L"Grt");
									break;
								}
							case 7:
								{
									pIpodHardware->RetAcName(0x7, L"82");
									break;
								}
							case 8:
								{
									break;
								}
							}
							break;
						}
					case 0x14:	// GetDevAuthenticationInfo
						{
							if (pIpodHardware->ipodAuthMode == IPOD_CPAUTH)
							{
								// 含有cp的时候,认证过程
								// ReadAccessoryCertificate Length and Data from CP
								// 发送 Certificate data 到 ipod
								pIpodHardware->RetDevAuthenticationInfo(pIpodHardware->ipodCP.certData, pIpodHardware->ipodCP.certLen);
							}
							break;
						}
					case 0x16:	// AckDevAuthenticationInfo
						{
							RETAILMSG(1, (TEXT("AckDevAuthenticationInfo = 0x%x\r\n"), CMD[3]));	

							break;
						}
					case 0x17:	// GetDevAuthenticationSignature
						{
							if (pIpodHardware->ipodAuthMode == IPOD_CPAUTH)
							{
								// 获取 Challenge 数据
								BYTE *challenData = &CMD[3]; 
								// 写入到cp
								pIpodHardware->ipodCP.WriteChallengeData(challenData, 20);
								// 生成 signature
								pIpodHardware->ipodCP.WriteAuthControl(IpodCP::GENERATE_SIGNATURE);
								// 等待 cp 完成计算
								Sleep(200);
								while (pIpodHardware->ipodCP.ReadAuthStatus() == 0)
								{
									Sleep(10);
								}
								// 从cp读取Signature
								BYTE signData[128];
								int signLen = pIpodHardware->ipodCP.ReadSignatureData(signData);

								// 发送 Signature 到ipod
								pIpodHardware->RetDevAuthSignature(signData, signLen);
							}
							break;
						}
					case 0x19:	// AckDevAuthenticationStatus
						{
							// 授权结果 0x00 = passed
							RETAILMSG(1, (TEXT("AckDevAuthenticationStatus = 0x%x\r\n"), CMD[3]));
							if (CMD[3] != 0x00)
							{
								// 授权失败,重新授权???
								pIpodHardware->SendMsg(WM_IPOD, IPOD_AUTHSUCCESS, 1);
							}
							else
							{
								pIpodHardware->SetiPodPreferences();
								pIpodHardware->SetiPodPreferences_AudioOut();


								// 进入lingoes 4
								pIpodHardware->EntryHighControlMode();
								// 设置自动时间发送
								pIpodHardware->SetPlayStatusChangeNotification();

								// ipod 授权 ac 成功, 进入 ac 验证 ipod 流程
								pIpodHardware->SendMsg(WM_IPOD, IPOD_AUTHSUCCESS, 0);
								pIpodHardware->eHierarchy = HIERARCHY_NONE;
							}
							break;
						}
					case 0x23:
						{
							RETAILMSG(1, (TEXT("NotifyiPodstateChange = 0x%x\r\n"), CMD[3]));
							break;
						}
					case 0x3A:	// RetFIDTokenValueACKs
						{
							WORD transID = CMD[3]<<8 | CMD[4];
							if (CMD[6] == 0x00 && CMD[7] == 0x00)
							{
								// ret IdentifyToken
								RETAILMSG(1, (TEXT("IdentifyToken ACK = 0x%x\r\n"), CMD[8]));
								if (CMD[8] == 0x00)
								{
									// 发送第二个 FID, ACC caps
									BYTE accLingoes[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}
							}
							if (CMD[6] == 0x00 && CMD[7] == 0x01)
							{
								// 发送第三个 FID, ACC info 
								// acc name
								BYTE accLingoes[] = {0x00, 0x02, 0x1, 'V', 'W', ' ', 'M', 'a', 'd', 'e', ' ', 'f', 'o', 'r', ' ', 'i', 'P', 'o', 'd', 0x00};
								pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);

							}
							if (CMD[6] == 0x00 && CMD[7] == 0x02)
							{
								RETAILMSG(1, (TEXT("acc info ACK = 0x%x\r\n"), CMD[8]));
								if (transID == 0x03)
								{
									// acc firm version
									BYTE accLingoes[] = {0x00, 0x02, 0x04, 0x00, 0x01, 0x00};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}
								if (transID == 0x04)
								{
									// acc hard version
									BYTE accLingoes[] = {0x00, 0x02, 0x05, 0x00, 0x01, 0x00};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);

								}
								if (transID == 0x05)
								{
									// acc manufactuer
									BYTE accLingoes[] = {0x00, 0x02, 0x1, 'G', 'r', 't', 0x00};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);

								}

								if (transID == 0x06)
								{
									// acc model num
									BYTE accLingoes[] = {0x00, 0x02, 0x1, 'G', 'r', 't', 0x00};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}

								if (transID == 0x07)
								{
									// iPodPreferrenceToken
									// 打开视频
									BYTE accLingoes[] = {0x00, 0x03, 0x00, 0x01, 0x01};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);


								}
							}
							if (CMD[6] == 0x00 && CMD[7] == 0x03)
							{
								if (transID == 0x08)
								{
									// 打开音频
									BYTE accLingoes[] = {0x00, 0x03, 0x03, 0x01, 0x01};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}
								if (transID == 0x09)
								{
									// CBVS
									BYTE accLingoes[] = {0x00, 0x03, 0x08, 0x01, 0x01};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}
								if (transID == 0x0A)
								{
									// 结束设置
									pIpodHardware->EndIDPS(pIpodHardware->GetTransID());
								}
							}
							break;
						}
					case 0x3C:	// IDPSStatus
						{
							RETAILMSG(1, (TEXT("IDPSStatus = 0x%x\r\n"), CMD[5]));
							break;
						}
					}
					break;
				}
			case 1:	// microphone lingo
				{
					break;
				}
			case 2: // simple remote lingo
				{
					break;
				}
			case 3: // display remote lingo
				{
					WORD wType = CMD[2];
					RETAILMSG(IPODDEBUG,(TEXT("wType = 0x%x\r\n"), wType));
					switch(wType)
					{
					case 0x00:
						{
							// 0x00 ok
							// 0x01 reserved
							// 0x02 command failed
							// 0x03 out of resources
							// 0x04 bad parameter
							// 0x05 Unknown ID
							// 0x06 reserved
							// 0x07 accessory not authenticated
							RETAILMSG(IPODDEBUG,(TEXT("lingo 3 ack info = 0x%x\r\n"), CMD[3]));
							break;
						}
					case 0x09:	// RemoteEventNotification
						{
							RETAILMSG(IPODDEBUG,(TEXT("moede = 0x%x\r\n"), CMD[3]));
							switch(CMD[3])
							{
							case 0x0:	// track position
								{
									pIpodHardware->iCurTime =  CMD[4]<<24 | CMD[5]<<16 | CMD[6]<<8 | CMD[7];
									if (pIpodHardware->iCurTime == 0)
									{
										pIpodHardware->GetPlayStatus3();
									}
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TIME, 0);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_TIME, 0);
									break;
								}
							case 0x1:	// track index
								{
									break;
								}
							case 0x2:	// chapter information
								{
									break;
								}
							case 0x3:	// playstatus
								{
									pIpodHardware->ipodPlayStatus = CMD[4];

									if (pIpodHardware->ipodPlayStatus == IPOD_PLAYING)
									{
										pIpodHardware->GetPlayStatus3();
									}
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
									break;
								}
							case 0xF:
								{
									pIpodHardware->iCurTime =  CMD[4]<<8 | CMD[5];
									if (pIpodHardware->iCurTime == 0)
									{
										pIpodHardware->GetPlayStatus3();
									}
									pIpodHardware->SendMsg(WM_IPOD, IPOD_TIME, 0);
									break;
								}
							}
							break;
						}
					case 0x10:	// RetPlayStatus
						{
							pIpodHardware->SetiPodPreferences();
							pIpodHardware->ipodPlayStatus = CMD[3];
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
							pIpodHardware->iTotalTime = CMD[8]<<24 | CMD[9]<<16 | CMD[10]<<8 | CMD[11];
							pIpodHardware->iTotalTime /= 1000;
							pIpodHardware->iCurTime =  CMD[12]<<24 | CMD[13]<<16 | CMD[14]<<8 | CMD[15];
							pIpodHardware->iCurTime /= 1000;
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TIME, 0);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_TIME, 0);
							int iTrackNum = CMD[4]<<24 | CMD[5]<<16 | CMD[6]<<8 | CMD[7];
							pIpodHardware->GetIndexedPlayingTrackInfo3(0x2, iTrackNum);
							pIpodHardware->GetIndexedPlayingTrackInfo3(0x3, iTrackNum);
							pIpodHardware->GetIndexedPlayingTrackInfo3(0x4, iTrackNum);
							pIpodHardware->GetIndexedPlayingTrackInfo3(0x5, iTrackNum);
							break;
						}
					case 0x13:	// RetIndexedPlayingTrackInfo
						{
							WORD wType = CMD[3];
							RETAILMSG(IPODDEBUG,(TEXT("wType = 0x%x\r\n"), wType));
							switch(wType)
							{
							case 0x2:
								{
									// 返回当前艺术家名称
									char szSongname[MAX_PATH] = {0};
									for (int i=0;i<CMD[0]-3;i++)
									{
										szSongname[i] = CMD[4+i];
									}
									GxxString str;
									str.UTF8ToUNICODE(szSongname);
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_ARTIST, (LPARAM)&str);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_ARTIST, (LPARAM)&str);
									break;
								}
							case 0x3:
								{
									// 返回当前专辑名称
									char szSongname[MAX_PATH] = {0};
									for (int i=0;i<CMD[0]-3;i++)
									{
										szSongname[i] = CMD[4+i];
									}
									GxxString str;
									str.UTF8ToUNICODE(szSongname);
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_ALBUM, (LPARAM)&str);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_ALBUM, (LPARAM)&str);
									break;
								}
							case 0x4:
								{
									// 返回当前流派名称
									char szSongname[MAX_PATH] = {0};
									for (int i=0;i<CMD[0]-3;i++)
									{
										szSongname[i] = CMD[4+i];
									}
									GxxString str;
									str.UTF8ToUNICODE(szSongname);
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_GENRE, (LPARAM)&str);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_GENRE, (LPARAM)&str);
									break;
								}
							case 0x5:
								{
									// 返回当前歌曲名称
									char szSongname[MAX_PATH] = {0};
									for (int i=0;i<CMD[0]-3;i++)
									{
										szSongname[i] = CMD[4+i];
									}
									GxxString str;
									str.UTF8ToUNICODE(szSongname);
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TITLE, (LPARAM)&str);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_TITLE, (LPARAM)&str);
									break;
								}
							}
							break;
						}
					}
					break;
				}
			case 4: // extended interface lingo
				{
					WORD wType = (CMD[2]<<8) | CMD[3];
					//STLOG_WRITE("wType = 0x%x", wType);
					RETAILMSG(IPODDEBUG,(TEXT("wType = 0x%x\r\n"), wType));
					switch(wType)
					{
					case 0x0001:
						{
							//0x00 = Success (OK)
							//0x01 = ERROR: Unknown database category
							//0x02 = ERROR: Command failed
							//0x03 = ERROR: Out of resources
							//0x04 = ERROR: Bad parameter
							//0x05 = ERROR: Unknown ID
							//0x06 = Command Pending. See Table 5-12 (page72) .
							//0x07 = ERROR: Not authenticated
							// 返回命令是否成功
							RETAILMSG(1, (TEXT("ACK4 = 0x%x\r\n"), CMD[4]));
							break;
						}
					case 0x0003:
						{
							// 返回连接是否成功
							break;
						}
					case 0x0013:
						{
							// 返回IPOD型号
							break;
						}
					case 0x0015:
						{
							// 返回IPOD名字
							break;
						}
					case 0x0019: // ReturnNumberCategorizedDBRecords 
						{
							// 返回IPOD各类型的总数
							//ipodList.ReturnNumberCategorizedDBRecords(CMD);
							//pIpodHardware->SendMsg(WM_IPOD, IPOD_NUMRECORD, (LPARAM)CMD);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_NUMRECORD, (LPARAM)CMD);
							break;
						}
					case 0x001B:
						{
							// 返回多项对应的项目名称
							//ipodList.ReturnCategorizedDBRecords(CMD);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_CATRECORD, (LPARAM)CMD);
							break;
						}
					case 0x001D:	// ReturnPlayStatus
						{
							// 返回当前歌曲播放的总时间和当前播放时间
							int totalTime, curTime;
							totalTime = (CMD[4]<<24) | (CMD[5]<<16) | (CMD[6]<<8) | CMD[7];
							curTime = (CMD[8]<<24) | (CMD[9]<<16) | (CMD[10]<<8) | CMD[11];
							pIpodHardware->iTotalTime = totalTime /= 1000;
							pIpodHardware->iCurTime = curTime /= 1000;
							int hour = totalTime/3600;
							int min = (totalTime - hour*3600)/60;
							int sec = totalTime % 60;

							hour = curTime/3600;
							min = (curTime - hour*3600)/60;
							sec = curTime % 60;

							if (pIpodHardware->iTotalTime)
							{
							}
							if (CMD[12] < 3)
							{
								pIpodHardware->ipodPlayStatus = CMD[12];
								//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
								pIpodHardware->SendMsg(WM_IPOD, IPOD_PLAYSTATUS, pIpodHardware->ipodPlayStatus);
							}
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TIME, 0);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_TIME, 0);
							break;
						}
					case 0x001F:	// ReturnCurrentPlayingTrackIndex
						{
							pIpodHardware->GetMusicID3(CMD);
							break;
						}
					case 0x0021:
						{
							// 返回当前歌曲名称
							char szSongname[MAX_PATH] = {0};
							for (int i=0;i<CMD[0]-3;i++)
							{
								szSongname[i] = CMD[4+i];
							}
							GxxString str;
							str.UTF8ToUNICODE(szSongname);
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TITLE, (LPARAM)&str);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_TITLE, (LPARAM)&str);
							break;
						}
					case 0x0023:
						{
							// 返回当前歌曲演唱者
							char szSongname[MAX_PATH] = {0};
							for (int i=0;i<CMD[0]-3;i++)
							{
								szSongname[i] = CMD[4+i];
							}
							GxxString str;
							str.UTF8ToUNICODE(szSongname);
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_ARTIST, (LPARAM)&str);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_ARTIST, (LPARAM)&str);
							break;
						}
					case 0x0025:
						{
							// 返回当前歌曲专辑
							char szSongname[MAX_PATH] = {0};
							for (int i=0;i<CMD[0]-3;i++)
							{
								szSongname[i] = CMD[4+i];
							}
							GxxString str;
							str.UTF8ToUNICODE(szSongname);
							//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_ALBUM, (LPARAM)&str);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_ALBUM, (LPARAM)&str);
							break;
						}
					case 0x0027:	// PlayStatusChangeNotification
						{
							// 返回当前歌曲播放时间
							BYTE playStatus = CMD[4];
							switch(playStatus)
							{
							case 0x0:	// Playback stopped
								{
									break;
								}
							case 0x01:	// Playback track changed
								{
									// 获取新的 track 索引
									int trackIndex = (CMD[5]<<24) | (CMD[6]<<16) | (CMD[7]<<8) | CMD[8];
									pIpodHardware->ipodNowIndex = trackIndex;
									pIpodHardware->GetMusicID3(trackIndex);
									pIpodHardware->GetPlayStatus();
									break;
								}
							case 0x02:	// Playback forward seek stop
								{
									break;
								}
							case 0x03:	// Playback backward seek stop
								{
									break;
								}
							case 0x04:	// Playback track position
								{
									// 获取新的播放位置
									int curTime = (CMD[5]<<24) | (CMD[6]<<16) | (CMD[7]<<8) | CMD[8];
									pIpodHardware->iCurTime = curTime /= 1000;
									int hour = curTime/3600;
									int min = (curTime - hour*3600)/60;
									int sec = curTime % 60;
									//::PostMessage(pIpodHardware->hWnd, WM_IPOD, IPOD_TIME, 0);
									pIpodHardware->SendMsg(WM_IPOD, IPOD_TIME, 0);
									break;
								}
							case 0x05:	// Playback chapter changed
								{
									break;
								}
							}		
							break;
						}
					case 0x002D:	// ReturnShuffle
						{
							pIpodHardware->ipodShuffleStatus = CMD[4];
							pIpodHardware->SendMsg(WM_IPOD, IPOD_SHUFFLE, CMD[4]);
							break;
						}
					case 0x0030:	// ReturnRepeat
						{
							pIpodHardware->ipodRepeatStatus = CMD[4];
							pIpodHardware->SendMsg(WM_IPOD, IPOD_REPEAT, CMD[4]);
							break;
						}
					}
					break;
				}
			case 5: // RF transmitter lingo
				{
					break;
				} 
			case 6: // usb host control lingo
				{
					break;
				}
			case 7: // RF tuner lingo
				{
					break;
				}
			case 8:	// accessory equalizer lingo
				{
					break;
				}
			case 0xA:// digite audio lingo
				{
					break;
				}
			}
		}

	}
}

DWORD IpodHardware::SendThread(LPVOID lpParam)
{
	IpodHardware *p = (IpodHardware *)lpParam;		
	while (1)
	{
		WaitForSingleObject(p->hSendEvent, INFINITE);
#ifdef USESERIAL
		// 发送命令
		BYTE CMD[256] = {0};
		while (p->ipodCMD.fetch(CMD))
		{
			p->IsCmdAck = 0;
			if (CMD[0] == 0xFF)
			{
				p->IPODSerial.Write(CMD, CMD[2]+4);
			}

			// 等待回应
			int i = 0;
			while (p->IsCmdAck == 0)
			{
				Sleep(10);
				if (i++ > 5)
				{
					RETAILMSG(0,(TEXT("CMD mode=0x%x, type=0x%x, Miss ACK\r\n"),CMD[3],CMD[4]));
					Sleep(10);
					// 连续5次命令没有回应,就判断为没有 ipod
					p->failTimes++;
					if (p->failTimes > 6)
					{
						p->failTimes = 0;
						if (p->iPodModel != NOIPOD)
						{
							p->iPodModel = NOIPOD;
							p->sIpodName.Empty();
							p->ResetTransID();
							p->SendMsg(WM_IPOD, IPOD_NAME, 0);
						}
					}

					//PostMessage(p->hWnd, WM_IPOD, 1, CMD[3]<<16 | CMD[4]);
					break;						
				}
			}
			if (i<5)
			{
				p->failTimes = 0;
				Sleep(10*(5-i));	// 保证每个命令之间有50ms间隔
			}
		}
#endif
#ifdef USBIPOD
		// 发送命令
		BYTE CMD[256] = {0};
		while (p->ipodCMD.fetch(CMD))
		{
			p->SendCommand(CMD, CMD[2]+4);

		}
#endif
	}

}