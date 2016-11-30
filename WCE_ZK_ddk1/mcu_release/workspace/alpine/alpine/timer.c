#include "macro.h"
#include "timer.h"

int global_timer[16] = {0};

void handler_timer()
{
	int i=0;
	for(i=0;i<16;i++)
	{
		if(global_timer[i]>0)
		{
			global_timer[i]--;
		}
		else
		{
			global_timer[i] = 0;
		}
	}
}

void set_timer(int id, int delay)
{
	global_timer[id] = delay;
}

int wait_timer(int id)
{
	if(global_timer[id] == 0)
	{
		return 1;
	}
	return 0;
}

void kill_timer(int id)
{
	global_timer[id] = 0;
}