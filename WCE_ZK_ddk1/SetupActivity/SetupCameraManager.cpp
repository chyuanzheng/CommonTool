#include "StdAfx.h"
#include "SetupCameraManager.h"
#include "Activity.h"
#include "i2c/chip.h"
#include "PIP/PIP.h"
const string cs_camera = "direct_camera_set";



SetupCameraManager *SetupCameraManager::m_pInstance = NULL;
SetupCameraManager::SetupCameraManager()
{
	//这里应该读取flash 得到m_color的值
	m_camera = sysConfig.sysParam.curCamera;
	if (m_camera>PAL)
	{
		m_camera = OFF;
	}
}

SetupCameraManager::~SetupCameraManager()
{

}


SetupCameraManager* SetupCameraManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupCameraManager;
	}
	return m_pInstance;
}


bool SetupCameraManager::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	
	if (sline_name == cs_camera)
	{
		
		min_cursor = (int)OFF;
		max_cursor = (int)PAL;
		return true;
	}
	return false;//没有最大 最小游标
}

bool SetupCameraManager::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (sline_name == cs_camera)
	{
		n_cursor = (int)m_camera;
		switch(m_camera)
		{
		case OFF:
			sline_data = "OFF";
			break;
		case  NTSC:
			sline_data = "NTSC";
			break;
		case  PAL:
			sline_data = "PAL";
			break;
		default:
			ASSERT(0);
			return false;
		}

	}
	AfxInvalidateRect(NULL);
	return true;
}



bool SetupCameraManager::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	bool ret = true;

	if (sline_name == cs_camera)
	{
		m_camera = n_cursor;
		sysConfig.sysParam.curCamera = m_camera;
		sysConfig.WriteConfig(&sysConfig.sysParam.curCamera);
		ReadSetup(sline_name,n_cursor,sline_data);
		return true;
	}
	ASSERT(0);
	return false;
}
