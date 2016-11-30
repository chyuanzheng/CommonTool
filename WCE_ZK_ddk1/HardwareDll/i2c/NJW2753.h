#pragma once

#include "stdAfx.h"
#include "iic.h"
#include "mcu.h"

class NJW2753
{
public:
	enum INPUT
	{
		INPUT_1,
		INPUT_2,
		INPUT_3
	};
private:
	INPUT curInput;
	INPUT saveInput;
public:
	void SaveStatus()
	{
		saveInput = curInput;
	}
	void RestoreStatus()
	{
		OutputSelect(saveInput);
	}
	void OutputSelect(INPUT input)
	{
		curInput = input;
		MCU::NJW2573Output(input);
	}
	INPUT GetCurInput()
	{
		return curInput;
	}
};