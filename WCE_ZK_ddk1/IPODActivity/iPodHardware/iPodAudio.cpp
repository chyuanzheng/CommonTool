
#include "stdafx.h"
#include "iPodConfig.h"
#include "iPodCommandControl.h"

#include <winioctl.h>
//#include "iPodPlayer.h"
//#include "iPodPlayerDlg.h"

#define PCMDATASIZE				8192//(32768)//32768	//=(8192*4)		//8192
#define NUMBER_OF_PCMBUFFER		10


/*******************************************
		 USBHost AUDIO CLASS
********************************************/
#define TCC_IOCTLCode(f,m)	CTL_CODE ( FILE_DEVICE_UNKNOWN , 0xA00 + (f), (m), FILE_ANY_ACCESS )

#define IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH			TCC_IOCTLCode(1101, METHOD_BUFFERED)
#define IOCTL_USBH_AUDIO_SET_ZERO_BANDWIDTH			TCC_IOCTLCode(1102, METHOD_BUFFERED)
#define IOCTL_USBH_AUDIO_SET_SAMPLERATE				TCC_IOCTLCode(1103, METHOD_BUFFERED)


HANDLE hAudioDevice;
HANDLE hiPodAudioThread;
HANDLE hiPodAudioReadThread;

BOOL iPodAudioThreadStatus;
BOOL iPodAudioThreadStopFlag;
BOOL iPodAudioReadThreadStatus;
BOOL iPodAudioReadThreadStopFlag;

#ifdef TEST_CLEAR_BUFFER
BOOL iPodAudioBufferClearFlag;
#endif

BOOL iPodAudioNewSamplingFreqFlag;
DWORD iPodAudioSamplingFreq;
DWORD iPodAudioDriverNumber;

typedef enum {
	IPOD_AUDIO_STATE_NONE,
	
	IPOD_AUDIO_STATE_STOP,
	IPOD_AUDIO_STATE_STOPPED,
	IPOD_AUDIO_STATE_STARTPLAY,
	IPOD_AUDIO_STATE_PLAY,

	IPOD_AUDIO_STATE_MAX	
} IPOD_AUDIO_STATE;

IPOD_AUDIO_STATE iPodAudioThreadState=IPOD_AUDIO_STATE_NONE;
IPOD_AUDIO_STATE iPodAudioReadThreadState=IPOD_AUDIO_STATE_NONE;

DWORD dwPlayedSec;

HWAVEOUT OpenWaveOut(HWND hWnd, WAVEFORMATEX *pwaveformat,DWORD NumberOfBuffer,WAVEHDR *waveheader,LPVOID *Buffer,DWORD BufLen) {
	MMRESULT mmresult;
	DWORD i;
	HWAVEOUT h_output;
	
	mmresult=waveOutOpen(&h_output,WAVE_MAPPER, pwaveformat,(DWORD) hWnd, 0, CALLBACK_WINDOW);
	if ( MMSYSERR_NOERROR != mmresult){
		TLOG(CH_AUDCTL, LV_ERROR, (TEXT("  > OpenWaveOut() Failed (%d)\r\n"), h_output) );
	}

	for (i=0;i<NumberOfBuffer;i++) {
		memset(&waveheader[i],0,sizeof(WAVEHDR));
		waveheader[i].lpData=(LPSTR)(Buffer[i]);
		waveheader[i].dwBufferLength=BufLen;
		mmresult=waveOutPrepareHeader(h_output,&waveheader[i],sizeof(WAVEHDR));
	}
	return h_output;
}

VOID CloseWaveOut(HWAVEOUT h_output,DWORD NumberOfBuffer,WAVEHDR *waveheader) {
	DWORD i;
	
	for (i=0;i<NumberOfBuffer;i++) {
		if (waveheader[i].dwFlags & WHDR_PREPARED) {
			waveOutUnprepareHeader(h_output,&waveheader[i],sizeof(WAVEHDR));
		}
	}
	waveOutClose(h_output);
}

VOID iPod_AudioStart(VOID) {
	switch (iPodAudioThreadState) {
		case IPOD_AUDIO_STATE_NONE:
		case IPOD_AUDIO_STATE_STOPPED:
			iPodAudioReadThreadState=IPOD_AUDIO_STATE_STARTPLAY;
			//iPodAudioThreadState=IPOD_AUDIO_STATE_STARTPLAY;
			TLOG(CH_AUDCTL, LV_LOG, (TEXT("iPod_AudioStart()\r\n")) );
			break;

	}
}

VOID iPod_AudioStop(VOID) {
	if (iPodAudioThreadState==IPOD_AUDIO_STATE_PLAY) {
		iPodAudioThreadState=IPOD_AUDIO_STATE_STOP;
		TLOG(CH_AUDCTL, LV_LOG, (TEXT("iPod_AudioStop()\r\n")) );
	}
}


CHAR *pcmdata[NUMBER_OF_PCMBUFFER];
WAVEHDR waveheader[NUMBER_OF_PCMBUFFER];
enum {
	WDF_EMPTY,
	WDF_PREPARED,
	WDF_PLAYING,
	
	WDF_MAX
} wavedoneflag[NUMBER_OF_PCMBUFFER];
DWORD BufferIndex=0;
DWORD BufferReadIndex=0;


HWAVEOUT h_output=0;

DWORD iPodAudioThread(LPVOID pData) {
	HWND hWnd=(HWND)pData;
	int i;
	DWORD dwSleepTime;
	DWORD dwFileOffset=0;
	DWORD writeflag=0;	// for test
	DWORD preparedbuffercount=0;
	DWORD BufferEmptyCheck=0;
	MMRESULT mmresult;

	hAudioDevice=0;
	iPodAudioThreadStatus=TRUE;

	//DWORD NextBufferIndex=(BufferIndex+1)%NUMBER_OF_PCMBUFFER;
	
	CeSetThreadPriority(GetCurrentThread(), 245);
	DWORD dwPlayedSamples=0;
	
	//HANDLE fd;
	DWORD readlen=0;
	
	//DWORD ReadSize;
	
	WAVEFORMATEX  waveformat;
 
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nChannels = 2;                      // 재생에 사용할 채널수 :  1 - 모노,  2 - 스테레오
	waveformat.nSamplesPerSec = 44100;	// 11025    // 샘플링 주기 : 11.025 KHz
	waveformat.wBitsPerSample = 16;	// 8;             // 샘플링 단위 : 8 Bits
	waveformat.nBlockAlign = waveformat.nChannels*waveformat.wBitsPerSample/8;
	waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec*waveformat.nBlockAlign;
	waveformat.cbSize = 0;                            // WAVEFORMATEX 구조체 정보외에 추가적인 정보가 없다.

	iPodAudioSamplingFreq = 44100;
	for (i=0;i<NUMBER_OF_PCMBUFFER;i++) {
		pcmdata[i]=new CHAR [PCMDATASIZE];
#ifdef TEST_CLEAR_BUFFER
		memset( pcmdata[i], 0x00, PCMDATASIZE );
#endif
	}
	
	h_output=OpenWaveOut(hWnd,&waveformat,NUMBER_OF_PCMBUFFER,waveheader,(LPVOID*)pcmdata,PCMDATASIZE);
	
	dwSleepTime=waveformat.nBlockAlign*waveformat.nSamplesPerSec/PCMDATASIZE/5;
	dwFileOffset=readlen;
	BufferIndex=0;
 	while (iPodAudioThreadStopFlag==FALSE) {

		// ==> Adjust sampling frequency
		if ( waveformat.nSamplesPerSec != iPodAudioSamplingFreq){

			TLOG(CH_AUDCTL, LV_LOG, (TEXT("  > SamplingFrequence Changing... \r\n")) );

			CloseWaveOut(h_output,NUMBER_OF_PCMBUFFER,waveheader);

			waveformat.wFormatTag = WAVE_FORMAT_PCM;
			waveformat.nChannels = 2;                      // 재생에 사용할 채널수 :  1 - 모노,  2 - 스테레오
			waveformat.nSamplesPerSec = iPodAudioSamplingFreq;	// 11025    // 샘플링 주기 : 11.025 KHz
			waveformat.wBitsPerSample = 16;	// 8;             // 샘플링 단위 : 8 Bits
			waveformat.nBlockAlign = waveformat.nChannels*waveformat.wBitsPerSample/8;
			waveformat.nAvgBytesPerSec = waveformat.nSamplesPerSec*waveformat.nBlockAlign;
			waveformat.cbSize = 0;                            // WAVEFORMATEX 구조체 정보외에 추가적인 정보가 없다.

			h_output=OpenWaveOut(hWnd,&waveformat,NUMBER_OF_PCMBUFFER,waveheader,(LPVOID*)pcmdata,PCMDATASIZE);
		}
		// <==
		

		switch (iPodAudioThreadState) {
			case IPOD_AUDIO_STATE_PLAY:
				switch (wavedoneflag[BufferIndex]) {
					case WDF_PREPARED:
						mmresult=waveOutWrite(h_output,&waveheader[BufferIndex],sizeof(WAVEHDR));
						if (mmresult!=MMSYSERR_NOERROR) {
							switch( mmresult ){
								case WAVERR_BADFORMAT:
									MessageBox(hWnd,_T("Error"),_T("Unsupported wave format !!"),MB_OK);
									iPodAudioSamplingFreq = 44100;
									break;

								case WAVERR_STILLPLAYING:
									TLOG(CH_AUDCTL, LV_WARN, (TEXT("still something playing..\r\n")) );
									break;

								default:
									MessageBox(hWnd,_T("Error"),_T("Wave Out Fail!"),MB_OK);
									break;
							}
							
							break;
						}
						if (writeflag) {
							HANDLE fdtest;
							DWORD writtenlen;
							DWORD offset=dwFileOffset-readlen;
							
							fdtest=CreateFile(_T("\\NAND\\T1.DAT"),GENERIC_WRITE,0,0,CREATE_ALWAYS,0,NULL);
							if (fdtest!=INVALID_HANDLE_VALUE) {
								WriteFile(fdtest,&offset,sizeof(DWORD),&writtenlen,NULL);
								WriteFile(fdtest,&waveheader[BufferIndex],sizeof(WAVEHDR),&writtenlen,NULL);
								WriteFile(fdtest,pcmdata[BufferIndex],readlen,&writtenlen,NULL);
								CloseHandle(fdtest);
							}
							writeflag=0;
						}
						dwPlayedSamples+=(waveheader[BufferIndex].dwBufferLength/waveformat.nBlockAlign);
						wavedoneflag[BufferIndex]=WDF_PLAYING;
						BufferIndex++;
						if (BufferIndex>=NUMBER_OF_PCMBUFFER) {
							BufferIndex=0;
						}
						break;
					default:
						Sleep(1);
						//Sleep(dwSleepTime);
						break;
				}
				break;
			case IPOD_AUDIO_STATE_STARTPLAY:
				iPodAudioThreadState=IPOD_AUDIO_STATE_PLAY;
				break;
			case IPOD_AUDIO_STATE_STOP:
				iPodAudioThreadState=IPOD_AUDIO_STATE_STOPPED;
				TLOG(CH_AUDCTL, LV_LOG, (TEXT(" iPodAudioThread() > IPOD_AUDIO_STATE_STOPPED\r\n")) );
				break;
			default:
				Sleep(100);
		}
		
	}
	
	for (i=0;i<NUMBER_OF_PCMBUFFER;i++) {
		if (pcmdata[i]) {
			delete pcmdata[i];
		}
	}
	CloseWaveOut(h_output,NUMBER_OF_PCMBUFFER,waveheader);

	//if (fd) {
	//	CloseHandle(fd);
	//}
	if (hAudioDevice) {
		CloseHandle(hAudioDevice);
		hAudioDevice=0;
	}

	iPodAudioThreadStatus=FALSE;
	return 0;
}

DWORD iPodAudioReadThread(LPVOID pData) {
	HWND hWnd=(HWND)pData;
	int i;
	//DWORD dwSleepTime;
	DWORD dwFileOffset=0;
	DWORD writeflag=0;	// for test
	DWORD preparedbuffercount=0;
	DWORD BufferEmptyCheck=0;
	//MMRESULT mmresult;

	MSG RequestMsg;
	hAudioDevice=0;
	iPodAudioReadThreadStatus=TRUE;

	//DWORD NextBufferIndex=(BufferIndex+1)%NUMBER_OF_PCMBUFFER;
	
	DWORD dwPlayedSamples=0;
	
	HANDLE fd;
	DWORD readlen=0;
	
	DWORD ReadSize;

	BOOL bSuccess = FALSE;

DWORD SamplingFreq = 44100;

	WCHAR strDeviceDriverName[16] = {0,};

	wsprintf(strDeviceDriverName, (L"AUD%d:"), iPodAudioDriverNumber);

	//fd=CreateFile(_T("AUD1:"),GENERIC_READ,0,0,OPEN_EXISTING,0,NULL);
	__try{
		fd=CreateFile(strDeviceDriverName,GENERIC_READ,0,0,OPEN_EXISTING,0,NULL);
	}
	__except(EXCEPTION_EXECUTE_HANDLER){
		fd=INVALID_HANDLE_VALUE;
		TLOG(CH_CMDCTL, LV_ERROR, (TEXT("[++++++++ERROR++++++++] > EXCEPTION on Create AUD handle \r\n")));
	}
	if (fd!=INVALID_HANDLE_VALUE) {
		/*
			On iPhone 4S, iPad 2 and New iPad, do not set full bandwidth at this time.
			move to below rootine.
		*/
		//DWORD ReadSize;
		//bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH,NULL,NULL,&ReadSize,sizeof(DWORD),NULL,NULL);            
		//TLOG(CH_AUDCTL, LV_LOG, (TEXT("iPodAudioReadThread() > Full band width (%s)\r\n"), ((bSuccess)?L"Success":L"Fail")) );
	}
	dwFileOffset=readlen;
	BufferReadIndex=0;
	CeSetThreadPriority(GetCurrentThread(), 245);
 	while (iPodAudioReadThreadStopFlag==FALSE) {

		if ( TRUE == PeekMessage(&RequestMsg, NULL, 0, 0, PM_REMOVE) ){
			switch( RequestMsg.message ){
				case WM_AUDIOCTRL_SET_FULLBAND_WIDTH :
					DWORD ReadSize;
					bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH,NULL,NULL,&ReadSize,sizeof(DWORD),NULL,NULL);            
					TLOG(CH_AUDCTL, LV_LOG, (TEXT("iPodAudioReadThread() > Full band width (%s)\r\n"), ((bSuccess)?L"Success":L"Fail")) );
					break;
				default :
					break;
			}
		}
		// ==> Adjust sampling frequency
		if ( ((iPodAudioNewSamplingFreqFlag) || (SamplingFreq != iPodAudioSamplingFreq) ) && iPodAudioSamplingFreq && SamplingFreq ){

			TLOG(CH_AUDCTL, LV_LOG, (TEXT("=== CHANGE SAMPINGFREQ AND SET FULL BANDWIDTH ===\r\n")));
			
			bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_SAMPLERATE,&iPodAudioSamplingFreq,sizeof(iPodAudioSamplingFreq),&ReadSize,sizeof(DWORD),NULL,NULL);
			
			if ( bSuccess ){
				TLOG(CH_AUDCTL, LV_LOG, (TEXT("CHANGE SAMPINGFREQ > (%d) => (%d)\r\n"), SamplingFreq, iPodAudioSamplingFreq));
			}
			else{
				TLOG(CH_AUDCTL, LV_WARN, (TEXT("CHANGE SAMPINGFREQ > Failed)\r\n")) );
			}

			DWORD ReadSize;
			bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH,NULL,NULL,&ReadSize,sizeof(DWORD),NULL,NULL);            
			TLOG(CH_AUDCTL, LV_LOG, (TEXT("iPodAudioReadThread() > Full band width (%s)\r\n"), ((bSuccess)?L"Success":L"Fail")) );
			SamplingFreq = iPodAudioSamplingFreq;
			iPodAudioNewSamplingFreqFlag = FALSE;
		}
		// <==
		

		switch (iPodAudioReadThreadState) {
			case IPOD_AUDIO_STATE_PLAY:

				#ifdef TEST_CLEAR_BUFFER
				// Clear buffer
				if ( iPodAudioBufferClearFlag ){
					DWORD iPodAudioThreadStateBackup = iPodAudioThreadState;
					DWORD nIndex = 0;
					iPodAudioThreadState = IPOD_AUDIO_STATE_STOP;

					Sleep(10);

					//Clear
					for (nIndex=0;nIndex<NUMBER_OF_PCMBUFFER;nIndex++) {
						if ( pcmdata[nIndex] ){
							memset( pcmdata[nIndex], 0x00, PCMDATASIZE);
						}
					}

					iPodAudioThreadState = (IPOD_AUDIO_STATE)iPodAudioThreadStateBackup;
					iPodAudioBufferClearFlag = FALSE;
				}
				#endif
				
				switch (wavedoneflag[BufferReadIndex]) {
					case WDF_PLAYING:
						if ((waveheader[BufferReadIndex].dwFlags==WHDR_PREPARED) || (waveheader[BufferReadIndex].dwFlags & WHDR_DONE)) {
							wavedoneflag[BufferReadIndex]=WDF_EMPTY;
						} else {
							Sleep(1);

							break;
						}
					case WDF_EMPTY:
						DWORD offset;
						offset=0;
						do {
							if (iPodAudioThreadStopFlag) {
								readlen=0;
								break;
							}
							readlen = 0;
							ReadFile(fd,pcmdata[BufferReadIndex],PCMDATASIZE,&readlen,0);
							if ( 0 == readlen ){
								//Sleep(10);
								break;
							}
							else{
								Sleep(1);
							}
							
							//RETAILMSG(1,(TEXT("readlen=%d(%d)\r\n"),readlen,PCMDATASIZE));
							dwFileOffset+=readlen;
							offset+=readlen;
						} while (offset<PCMDATASIZE);

						if ( offset < PCMDATASIZE ){
							Sleep(10);
						}
						else
						{
							waveheader[BufferReadIndex].dwFlags=WHDR_PREPARED;
							waveheader[BufferReadIndex].dwBufferLength=offset;
							wavedoneflag[BufferReadIndex]=WDF_PREPARED;
					
							BufferReadIndex++;
							if (BufferReadIndex>=NUMBER_OF_PCMBUFFER) {
								BufferReadIndex=0;
							}
						}
						break;
					default:
						//Sleep(dwSleepTime);
						Sleep(10);
						break;
				}
				break;
			case IPOD_AUDIO_STATE_STARTPLAY:
				if (iPodAudioThreadStatus==TRUE) {
					iPodAudioReadThreadState=IPOD_AUDIO_STATE_PLAY;
					/* move to sample rate changed rootine */
					//	bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_FULL_BANDWIDTH,NULL,NULL,&ReadSize,sizeof(DWORD),NULL,NULL);
					iPodAudioThreadState=IPOD_AUDIO_STATE_STARTPLAY;

					//	TLOG(CH_AUDCTL, LV_LOG, (TEXT("IPOD_AUDIO_STATE_STARTPLAY > Full band width (%s)\r\n"), ((bSuccess)?L"Success":L"Fail")) );
				}
				break;

			case IPOD_AUDIO_STATE_STOP:
				iPodAudioReadThreadState=IPOD_AUDIO_STATE_STOPPED;
				iPodAudioThreadState=IPOD_AUDIO_STATE_STOP;
				/* move to sample rate changed rootine */
				// Sleep(10);
				//	bSuccess = DeviceIoControl(fd,IOCTL_USBH_AUDIO_SET_ZERO_BANDWIDTH,NULL,NULL,&ReadSize,sizeof(DWORD),NULL,NULL);            

				//TLOG(CH_AUDCTL, LV_LOG, (TEXT("IPOD_AUDIO_STATE_STOP > Zero band width (%s)\r\n"), ((bSuccess)?L"Success":L"Fail")) );

				break;
			default:
				Sleep(100);
		}
		//Sleep(1000);

	}

	for (i=0;i<10000;i++) {
		if (iPodAudioThreadStatus==FALSE) {
			break;
		}
		Sleep(1);
	}

	if (fd) {
		CloseHandle(fd);
	}

	iPodAudioReadThreadStatus=FALSE;
	return 0;
}

BOOL iPod_GetAudioThreadStatus(VOID) {
	return iPodAudioThreadStatus;
}

BOOL iPod_StartAudioThread(IPOD_PLAYER_CONTEXT *pPlayerContext) {
	BOOL bSuccess = FALSE;
	DWORD AudioReadThreadID = 0;

	iPodAudioThreadStopFlag=FALSE;
	iPodAudioThreadStatus=FALSE;
	iPodAudioReadThreadStopFlag=FALSE;
	iPodAudioReadThreadStatus=FALSE;

	#ifdef TEST_CLEAR_BUFFER
	for(int nFlagIndex=0;nFlagIndex<NUMBER_OF_PCMBUFFER;nFlagIndex++){
		wavedoneflag[nFlagIndex] = WDF_EMPTY;
	}
	#endif

	if ( pPlayerContext ){
		iPodAudioDriverNumber = pPlayerContext->m_AudioDrvierNumber;
		hiPodAudioThread=CreateThread(NULL,0,iPodAudioThread,(PVOID)pPlayerContext->hWnd,0,NULL);
		hiPodAudioReadThread=CreateThread(NULL,0,iPodAudioReadThread,(PVOID)pPlayerContext->hWnd,0,&AudioReadThreadID);
		if ( (NULL!=hiPodAudioThread) && (NULL!=hiPodAudioThread) ){
			pPlayerContext->m_hAudioThread = hiPodAudioReadThread;
			pPlayerContext->m_AudioReadThreadID = AudioReadThreadID;

			bSuccess = TRUE;
		}
	}
	
	return bSuccess;
}

VOID iPod_StopAudioThread(VOID) {
	if (iPodAudioThreadStatus) {
		iPodAudioThreadStopFlag=TRUE;
		iPodAudioReadThreadStopFlag=TRUE;
	}
}

VOID iPod_CloseAudioThread(VOID) {
	if (iPodAudioThreadStatus) {
		TerminateThread(hiPodAudioThread,0);
		iPodAudioThreadStatus=FALSE;
		Sleep(100);
	}
	if (iPodAudioReadThreadStatus) {
		TerminateThread(hiPodAudioReadThread,0);
		iPodAudioReadThreadStatus=FALSE;
	}
	if (hiPodAudioThread) {
		CloseHandle(hiPodAudioThread);
		hiPodAudioThread=NULL;
	}
}

DWORD iPod_GetAudioDeviceDriverNumber( DWORD UniqueID ){

	/* Device attached message */
	HKEY hClientRegKey = NULL;
	DWORD dwType = 0;
	//DWORD dwLength = sizeof(DWORD);
	DWORD dwLength = 32;
	WCHAR DataBuffer[32] = {0,};
	DWORD DeviceNumber = 0;

	wchar_t RegPath[80] = {0, };

	//iPod
	wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\05AC\\%08x\\Audio_Class"),  UniqueID );

	//TC
	//wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\140E"));

	TLOG(CH_AUDCTL, LV_DEBUG,
				(TEXT("+ iPod_GetAudioDeviceDriverNumber() > RegPath(%s)\r\n"), RegPath));

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, RegPath, 0, 0, &hClientRegKey) == ERROR_SUCCESS ) { // We found Registry 
		DWORD err = RegQueryValueEx( hClientRegKey,DRIVERSTRING_SZ, NULL,&dwType, (LPBYTE)&DataBuffer[0], &dwLength);
		if ( err == ERROR_SUCCESS ){
			if ( REG_SZ == dwType){
				TLOG(CH_AUDCTL, LV_DEBUG,
							(TEXT("iPod_GetAudioDeviceDriverNumber() > Data Buffer(%s)\r\n"), &DataBuffer[0]));
				if ( ('A' == DataBuffer[0]) && ('U' == DataBuffer[1]) && ('D' == DataBuffer[2]) ){
					DeviceNumber = DataBuffer[3] - '0';

					if ( 0 < DeviceNumber ) {
						DWORD nOpenCount;
						LONG ret = RegQueryValueEx(hClientRegKey, DRIVEROPENCOUNT_SZ, NULL, &dwType, (LPBYTE)&nOpenCount, &dwLength);
						if ( (ERROR_SUCCESS == ret) && dwLength && (dwType == REG_DWORD) ){
							if (  0 !=nOpenCount ){
								DeviceNumber = 0;
							}
						}
					} 
				}
			}
			else{
				TLOG(CH_AUDCTL, LV_WARN, 
							(TEXT("iPod_GetAudioDeviceDriverNumber() > Invalid data type(%d)\r\n"), dwType));
			}			
		}
		else{
			TLOG(CH_AUDCTL, LV_WARN,
						(TEXT("iPod_GetAudioDeviceDriverNumber() > Failed to open registry key(%s), ErrorCode=%d\r\n"), DRIVERSTRING_SZ, err ));
		}

		RegCloseKey( hClientRegKey );
	}
	else{
		TLOG(CH_AUDCTL, LV_WARN,
					(TEXT("iPod_GetAudioDeviceDriverNumber() > Failed to open registry path(%s)\r\n"), RegPath));
	}

	TLOG(CH_AUDCTL, LV_DEBUG,
				(TEXT("- iPod_GetAudioDeviceDriverNumber() > DeviceNumber=%d\r\n"), DeviceNumber));
			
	return DeviceNumber;
}

DWORD iPod_RetrieveAudioDeviceDriverNumber( void ){

	/* Device attached message */
	HKEY hClientRegKey = NULL;
	DWORD dwType = 0;
	//DWORD dwLength = sizeof(DWORD);
	DWORD dwLength = 32;
	unsigned char DataBuffer[32] = {0,};
	DWORD DeviceNumber = 0;

	wchar_t RegPath[80] = {0, };

	WCHAR szUniqueId[256];
	DWORD nUniqueIDLen = sizeof(szUniqueId);

	DWORD nQueryMax = 256;
	DWORD nQueryCnt = 0;
	
	//iPod
	wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\05AC"));

	//TC
	//wsprintf(RegPath, (L"Drivers\\USB\\TelechipsDrivers\\140E"));

	TLOG(CH_AUDCTL, LV_DEBUG,
				(TEXT("+ iPod_RetrieveAudioDeviceDriverNumber() > RegPath(%s)\r\n"), RegPath));

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, RegPath, 0, 0, &hClientRegKey) == ERROR_SUCCESS ) { // We found Registry 

		for(nQueryCnt=0; nQueryCnt<nQueryMax; nQueryCnt++){
			if(RegEnumKeyEx(hClientRegKey, nQueryCnt, szUniqueId, &nUniqueIDLen, NULL,
			        NULL, NULL, NULL) == ERROR_SUCCESS){
			        
				HKEY hUniqueID;
				if(RegOpenKeyEx(hClientRegKey, szUniqueId, 0, 0, &hUniqueID) == ERROR_SUCCESS){ //"RegPath\\Unique"
					HKEY hDriver;
					if(RegOpenKeyEx(hUniqueID, L"Audio_Class", 0, 0, &hDriver) == ERROR_SUCCESS){ //"RegPath\\Unique\\TCCHIDClient"

						WCHAR DataBuffer[256];
						DWORD dwLength = sizeof(DataBuffer);
						DWORD dwType;

						TLOG(CH_AUDCTL, LV_DEBUG,
								(TEXT(" > Audio_Class path foud\r\n")));

						RegQueryValueEx(hDriver, DRIVERSTRING_SZ, NULL, &dwType,
											(LPBYTE)DataBuffer, &dwLength);

						if(dwLength && dwType == REG_SZ){
							if ( ('A' == DataBuffer[0]) && ('U' == DataBuffer[1]) && ('D' == DataBuffer[2]) ){
								DeviceNumber = DataBuffer[3] - '0';

								if ( 0 < DeviceNumber ) {
									DWORD nOpenCount;
									LONG ret = RegQueryValueEx(hDriver, DRIVEROPENCOUNT_SZ, NULL, &dwType, (LPBYTE)&nOpenCount, &dwLength);
									if ( (ERROR_SUCCESS == ret) && dwLength && (dwType == REG_DWORD) ){
										if (  0 != nOpenCount ){
											DeviceNumber = 0;
											RegCloseKey(hDriver);
											RegCloseKey(hUniqueID);
											continue; 
										}
									}
								}
								RegCloseKey(hDriver);
								RegCloseKey(hUniqueID);
								break;
							}
						}

						RegCloseKey(hDriver);
					}

					RegCloseKey(hUniqueID);
				}
			}

		}

		RegCloseKey(hClientRegKey);
	}
	else{
		TLOG(CH_CMDCTL, LV_DEBUG,
					(TEXT("> RegOpenKeyEx(%s) failed \r\n"),RegPath));
	}

	TLOG(CH_CMDCTL, LV_DEBUG,
				(TEXT("- iPod_RetrieveControlDeviceDriverNumber() > DeviceNumber=(%d)\r\n"), DeviceNumber));

	return DeviceNumber;
}

VOID iPod_SetAudioSamplingFreq( DWORD nSamplingFreq ){
	iPodAudioSamplingFreq = nSamplingFreq;
	iPodAudioNewSamplingFreqFlag = TRUE;
}

#ifdef TEST_CLEAR_BUFFER
VOID iPod_SetAudioBufferClearFlag( BOOL bEnableClear ){
	iPodAudioBufferClearFlag = bEnableClear;
}
#endif


