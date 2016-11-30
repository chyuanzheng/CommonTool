#pragma once;

#ifdef GRT_EXPORTS
#define GRT_API __declspec(dllexport)
#else
#define GRT_API __declspec(dllimport)
#endif

GRT_API BOOL IICOpen(void);
GRT_API void IICOpen(int);
GRT_API BOOL IICRead(BYTE pslaveAddr, BYTE psubAddr,int NumBytes,BYTE *ReadBuf);
GRT_API BOOL IICReadMcu(BYTE pslaveAddr, BYTE psubAddr,int NumBytes,BYTE *ReadBuf);
GRT_API BOOL IICRead(BYTE SlaveAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWrite(BYTE *WriteBytes,int iLen);
GRT_API BOOL IICWrite(BYTE SlaveAddr, BYTE SubAddr, BYTE *databuf, int iCount);
GRT_API BOOL IICWrite(BYTE SlaveAddr, BYTE SubAddr, BYTE data);
GRT_API void IICClose(void); 

GRT_API BOOL IICRead4(BYTE SlaveAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICRead4(BYTE pslaveAddr, BYTE psubAddr,int NumBytes,BYTE *ReadBuf);
GRT_API BOOL IICWrite4(BYTE *WriteBytes,int iLen);
GRT_API BOOL IICWrite4(BYTE SlaveAddr, BYTE SubAddr, BYTE iicdata);
GRT_API BOOL IICWrite4(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf); // MCU

GRT_API void BackLight(BOOL b);
GRT_API void KeypadLight(BOOL b);
GRT_API void CameraMirror(BOOL bMirror);
GRT_API void  VideoSelect(int i);
GRT_API BOOL MixOn(BOOL b);
GRT_API BOOL ReadMachine();
GRT_API BOOL ReadRdsReady();


BOOL FS8816_ComnunicationTest(void);
BOOL FS8816_Init(void);
GRT_API BYTE IICRead(void);
GRT_API BYTE IICWrite();

GRT_API BOOL IICWrite2(BYTE slvaddr, int len, BYTE *data);

GRT_API BOOL IICRead2(BYTE slvaddr, int len, BYTE *data);
GRT_API BOOL IICRead2(BYTE slvaddr, BYTE *data);


GRT_API BOOL IICRead3(BYTE SlaveAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICRead3(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWrite3(BYTE *WriteBytes, int iLen);
GRT_API BOOL IICWrite3(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWrite3(BYTE SlaveAddr, BYTE SubAddr, BYTE data);

GRT_API BOOL IICRead5(BYTE SlaveAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICRead5(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWrite5(BYTE *WriteBytes, int iLen);
GRT_API BOOL IICWrite5(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWrite5(BYTE SlaveAddr, BYTE SubAddr, BYTE data);

GRT_API BOOL IICWriteIpodCP(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICWriteIpodCP(BYTE SlaveAddr, BYTE SubAddr, BYTE data);
GRT_API BOOL IICReadIpodCP(BYTE SlaveAddr, BYTE SubAddr, int iCount, BYTE *databuf);
GRT_API BOOL IICReadIpodCP(BYTE SlaveAddr, int iCount, BYTE *databuf);

GRT_API char BrightnessSet(char b);
GRT_API char ContrastSet(char c);
GRT_API char HueSet(char h);
GRT_API void KeyLightRed(int r);
GRT_API void KeyLightGreen(int g);
GRT_API void KeyLightBlue(int b);
GRT_API void TouchSwitch(int b);

GRT_API int USBSwitch(BYTE b);
GRT_API BOOL CarLightRead();
GRT_API BOOL IsBackCamera();

GRT_API void GPIOSet(char port, int portnum, BOOL value);
GRT_API BOOL GPIOGet(char port, int portnum);

GRT_API BOOL ReadCDData(BYTE *data, DWORD *len);

GRT_API BOOL EpfRead(BYTE *buf, int *len);
GRT_API BOOL EpfWrite(BYTE *sbuf, BYTE *rbuf, int len);
GRT_API BOOL IOControl(DWORD dwCode, LPVOID lpInBuffer, DWORD nInBuffSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned);

GRT_API void GetBackCameraControl();
GRT_API int ReadBootVersion();