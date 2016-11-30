
#ifndef _IPOD_AUDIO_H_
#define _IPOD_AUDIO_H_



extern BOOL iPod_GetAudioThreadStatus(VOID);
extern BOOL iPod_StartAudioThread(IPOD_PLAYER_CONTEXT *pPlayerContext);
extern VOID iPod_StopAudioThread(VOID);
extern VOID iPod_CloseAudioThread(VOID);

extern VOID iPod_AudioStart(VOID);
extern VOID iPod_AudioStop(VOID);

extern DWORD iPod_GetAudioDeviceDriverNumber( DWORD UniqueID );
extern DWORD iPod_RetrieveAudioDeviceDriverNumber( void );

extern VOID iPod_SetAudioSamplingFreq( DWORD nSamplingFreq );

#ifdef TEST_CLEAR_BUFFER
extern VOID iPod_SetAudioBufferClearFlag( BOOL bEnableClear );
#endif

#endif	// _IPOD_AUDIO_H_
