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
	// ����߳����ȼ�
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
			else if (p->iNum == iLen+4-1)	//���һ���ֽ�
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
					case 0x0:	// RequestIdentify ipodҪ����֤
						{
							// ��ʹ��UART��������ʱ,��֤���̿�ʼ�ڸ����豸����ͬ���ֽں�
							// ������ͬ���ֽں�,������Ҫ�ȴ�20ms,Ȼ���� Command 0x01:Identify
							// ���� Command 0x13:IdentifyDeviceLingoes ֪ͨ ipod �Լ�֧�ֵ�lingoes
							//	The accessory should next check the version of the General lingo protocol supported by the iPod, by
							//	sending ��Command 0x0F: RequestLingoProtocolVersion�� (page 83) using the ID of the General lingo.
							//	The iPod responds with a ��Command 0x10: ReturnLingoProtocolVersion�� (page 84) packet containing
							//	the protocol version of the General lingo.
							//
							//	Note: If the iPod does not respond, the accessory should retry the IdentifyDeviceLingoes and
							//		  RequestLingoProtocolVersion commands. If the retry also fails, the accessory should assume that
							//		  these commands are not supported. If an iPod fails to ACK the IdentifyDeviceLingoes command,
							//		  the accessory should reidentify using the Identify command.
							// ����豸�յ� RequestIdentify ��,����������֤
							// һ�������豸�����俪ʼ,�����ֽڴ���ʱ��Ϊ25ms,��������ֽڼ����ʱ
							// ����25ms,ipod �����Ѿ��յ����ֽ�,ֱ����һ����Ч�İ�����
							// �� ipod ��ϵͳ���ع���ʱ,�������İ�Ҳ���Գ���25ms������
							// �豸��ʼ������
							//	1. Send a sync byte; this should wake up the iPod.
							//	2. Wait for 20 ms.
							//	3. Send the command packet with sync byte.

							// ��Ȩ
							// ��Ȩ�� ipod ��֤�����Ƿ�һ��ӵ����Ȩ�ķ���,һЩ�ض��Ĺ��ܱ�����Ȩ��
							// �ſ���ʹ��,ʹ�ô������Ӻ�usb����Ҫ�����Ȩ��ͬ.��Ȩ��ʼ��,������һ�����
							// 75s�ĺ�̨��Ȩ����,��ʱ�����豸����ʹ��δ��Ȩ�Ĺ���,ֱ����Ȩ���̽���

							// ������Ȩ��ʱ��,�󲿷ֵ� lingo 0x4 �������ʹ��,����������Ҫ���� lingo 0x4 ģʽ
							// ��������֤����
							// 1. ���Ϸ��� RequestiPodName ���ж� ipod �Ƿ��Ѿ����ӵ�������
							// 2. ipod ���Ӻ�,���� RequestpIpodHardware->iPodModelNum �ж� ipod �ͺ�
							// 3. ���ϵͳ�а��� apple cp, ������֤����, ʹ�� lingoes 1 & 3 ������ipod,����ʾ״̬
							// 4. ���ϵͳ�в����� cp, ��� ipod ���� cracked ipod, ͬ3
							// 5. ���ϵͳ�в����� cp, ���ҷ� cracked ipod, ���� lingo 0x4, ʹ�� extend �������ipod����ʾ״̬

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
							//0x0C �C 0x10 Reserved
							//0x11 = ERROR: Invalid accessory resistor ID value
							//0x12 �C 0xFF Reserved
							if (CMD[3] != 0)
							{
								RETAILMSG(1,(TEXT("ack info = 0x%x id = 0x%x\r\n"), CMD[3], CMD[4]));
								if (CMD[3] == 0x4 && CMD[4] == 0x38)
								{
									// ��֧�� IDPS
									pIpodHardware->IdentifyDeviceLingoes(1, pIpodHardware->ipodCP.deviceID);
								}
							}
							if (CMD[3] == 0 && CMD[4] == 0x30)
							{
								// ֧�� IDPS
								// ���͵�һ��FID
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
							// ����IPOD ����
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
									// ��֧���ƽ��ipod
#ifndef IPOD_CRACK_TEST
									pIpodHardware->iPodModel = VIDEOIPOD;						;			 
#endif								
								}
							}
#ifdef USESERIAL
							if (pIpodHardware->iPodModel == MUSICIPOD)
							{
								pIpodHardware->ipodAuthMode = IPOD_NOAUTH;
								pIpodHardware->IdentifyDeviceLingoes(0); // ��Ҫ����Ȩ
								pIpodHardware->SetiPodPreferences_AudioOut();
								// ����lingoes 4
								pIpodHardware->EntryHighControlMode();
								// �����Զ�ʱ�䷢��
								pIpodHardware->SetPlayStatusChangeNotification();
								// ��ʼ���Ų��һ�ȡ����״̬
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
									// ʹ�þɵķ�����֤
									pIpodHardware->IdentifyDeviceLingoes(1);
								}
								else
								{
									pIpodHardware->ipodAuthMode = IPOD_NOAUTH;
									pIpodHardware->IdentifyDeviceLingoes(0); // ��Ҫ����Ȩ
									pIpodHardware->SetiPodPreferences_AudioOut();
									// ����lingoes 4
									pIpodHardware->EntryHighControlMode();
									// �����Զ�ʱ�䷢��
									pIpodHardware->SetPlayStatusChangeNotification();
									// ��ʼ���Ų��һ�ȡ����״̬
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
							// ipod���󸽼���Ϣ
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
								// ����cp��ʱ��,��֤����
								// ReadAccessoryCertificate Length and Data from CP
								// ���� Certificate data �� ipod
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
								// ��ȡ Challenge ����
								BYTE *challenData = &CMD[3]; 
								// д�뵽cp
								pIpodHardware->ipodCP.WriteChallengeData(challenData, 20);
								// ���� signature
								pIpodHardware->ipodCP.WriteAuthControl(IpodCP::GENERATE_SIGNATURE);
								// �ȴ� cp ��ɼ���
								Sleep(200);
								while (pIpodHardware->ipodCP.ReadAuthStatus() == 0)
								{
									Sleep(10);
								}
								// ��cp��ȡSignature
								BYTE signData[128];
								int signLen = pIpodHardware->ipodCP.ReadSignatureData(signData);

								// ���� Signature ��ipod
								pIpodHardware->RetDevAuthSignature(signData, signLen);
							}
							break;
						}
					case 0x19:	// AckDevAuthenticationStatus
						{
							// ��Ȩ��� 0x00 = passed
							RETAILMSG(1, (TEXT("AckDevAuthenticationStatus = 0x%x\r\n"), CMD[3]));
							if (CMD[3] != 0x00)
							{
								// ��Ȩʧ��,������Ȩ???
								pIpodHardware->SendMsg(WM_IPOD, IPOD_AUTHSUCCESS, 1);
							}
							else
							{
								pIpodHardware->SetiPodPreferences();
								pIpodHardware->SetiPodPreferences_AudioOut();


								// ����lingoes 4
								pIpodHardware->EntryHighControlMode();
								// �����Զ�ʱ�䷢��
								pIpodHardware->SetPlayStatusChangeNotification();

								// ipod ��Ȩ ac �ɹ�, ���� ac ��֤ ipod ����
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
									// ���͵ڶ��� FID, ACC caps
									BYTE accLingoes[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);
								}
							}
							if (CMD[6] == 0x00 && CMD[7] == 0x01)
							{
								// ���͵����� FID, ACC info 
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
									// ����Ƶ
									BYTE accLingoes[] = {0x00, 0x03, 0x00, 0x01, 0x01};
									pIpodHardware->SetFIDTokenValues(pIpodHardware->GetTransID(), sizeof(accLingoes), accLingoes);


								}
							}
							if (CMD[6] == 0x00 && CMD[7] == 0x03)
							{
								if (transID == 0x08)
								{
									// ����Ƶ
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
									// ��������
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
									// ���ص�ǰ����������
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
									// ���ص�ǰר������
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
									// ���ص�ǰ��������
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
									// ���ص�ǰ��������
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
							// ���������Ƿ�ɹ�
							RETAILMSG(1, (TEXT("ACK4 = 0x%x\r\n"), CMD[4]));
							break;
						}
					case 0x0003:
						{
							// ���������Ƿ�ɹ�
							break;
						}
					case 0x0013:
						{
							// ����IPOD�ͺ�
							break;
						}
					case 0x0015:
						{
							// ����IPOD����
							break;
						}
					case 0x0019: // ReturnNumberCategorizedDBRecords 
						{
							// ����IPOD�����͵�����
							//ipodList.ReturnNumberCategorizedDBRecords(CMD);
							//pIpodHardware->SendMsg(WM_IPOD, IPOD_NUMRECORD, (LPARAM)CMD);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_NUMRECORD, (LPARAM)CMD);
							break;
						}
					case 0x001B:
						{
							// ���ض����Ӧ����Ŀ����
							//ipodList.ReturnCategorizedDBRecords(CMD);
							pIpodHardware->SendMsg(WM_IPOD, IPOD_CATRECORD, (LPARAM)CMD);
							break;
						}
					case 0x001D:	// ReturnPlayStatus
						{
							// ���ص�ǰ�������ŵ���ʱ��͵�ǰ����ʱ��
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
							// ���ص�ǰ��������
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
							// ���ص�ǰ�����ݳ���
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
							// ���ص�ǰ����ר��
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
							// ���ص�ǰ��������ʱ��
							BYTE playStatus = CMD[4];
							switch(playStatus)
							{
							case 0x0:	// Playback stopped
								{
									break;
								}
							case 0x01:	// Playback track changed
								{
									// ��ȡ�µ� track ����
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
									// ��ȡ�µĲ���λ��
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
		// ��������
		BYTE CMD[256] = {0};
		while (p->ipodCMD.fetch(CMD))
		{
			p->IsCmdAck = 0;
			if (CMD[0] == 0xFF)
			{
				p->IPODSerial.Write(CMD, CMD[2]+4);
			}

			// �ȴ���Ӧ
			int i = 0;
			while (p->IsCmdAck == 0)
			{
				Sleep(10);
				if (i++ > 5)
				{
					RETAILMSG(0,(TEXT("CMD mode=0x%x, type=0x%x, Miss ACK\r\n"),CMD[3],CMD[4]));
					Sleep(10);
					// ����5������û�л�Ӧ,���ж�Ϊû�� ipod
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
				Sleep(10*(5-i));	// ��֤ÿ������֮����50ms���
			}
		}
#endif
#ifdef USBIPOD
		// ��������
		BYTE CMD[256] = {0};
		while (p->ipodCMD.fetch(CMD))
		{
			p->SendCommand(CMD, CMD[2]+4);

		}
#endif
	}

}