#include "stdAfx.h"
#include "ControlHelp.h"

#include "MainPad.h"




Activity* MainPad::CreateControl()
{
	return new MainPad;
}

void MainPad::onCreate()
{
	Activity::SetActivityBackColor(0xFF0000FF);
	setContentView("layout\\MainPad.xml");
	Activity::onCreate();//必须在setContentView后面
}


BOOL MainPad::Response( UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	//HBITMAP hOldMap;

	switch( nMsg )
	{
	case CTR_MAIN_LOAD:
		LoadXml();
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}


//为了提供隐藏蓝牙的功能将 LoadXml延后
void MainPad::LoadXml()
{


	startActivity(NULL,"MainPad");

}


static RegisterHelp help("MainPad", MainPad::CreateControl);