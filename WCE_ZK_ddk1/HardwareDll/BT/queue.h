#pragma once

//#include "stdafx.h"

#define MAXCMDLEN 256
class Queue
{
	BYTE command[20][MAXCMDLEN];
	int  head,tail;
public:
	Queue()
	{
		memset(command,0,20*MAXCMDLEN);
		head = 0;
		tail = 0;
	}
	void join(BYTE *com, int len = MAXCMDLEN)
	{
		if (len > MAXCMDLEN)
		{
			ASSERT(FALSE);
		}
		head++;
		if (head>19)
		{
			head = 0;
		}
		memset(command[head],0,MAXCMDLEN);
		for (int i=0;i<len;i++)
		{
			command[head][i] = com[i];
		}
	}
	BOOL fetch(BYTE *com, int len = MAXCMDLEN)
	{
		RETAILMSG(0,(TEXT("head = %d\r\n"),head));
		RETAILMSG(0,(TEXT("tail = %d\r\n"),tail));
		if (tail == head)
		{
			return FALSE;
		}
		tail++;
		if (tail>19)
		{
			tail = 0;
		}
		for (int i=0;i<len;i++)
		{
			com[i] = command[tail][i];
		}
		return TRUE;
	}
};