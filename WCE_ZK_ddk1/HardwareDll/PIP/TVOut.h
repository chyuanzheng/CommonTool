#pragma once
#include "windev.h"
#include "ioctl_code.h"

class TccTVOut
{
	HANDLE hTVDevice;
	BOOL	IsTvOutOpen;
public:
	static TccTVOut* Instance();
	void TVOutOpen();
	void TVOutClose();
	void TVOutAdjust();
protected:
	TccTVOut();
private:
	static TccTVOut* pinstance;
};