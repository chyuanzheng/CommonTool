#include "StdAfx.h"
#include "SetupFuction.h"

SetupFuction *SetupFuction::m_pInstance = NULL;
SetupFuction* SetupFuction::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new SetupFuction;
	}
	return m_pInstance;
}

bool SetupFuction::ReadMinMax( const string &sline_name,int & min_cursor,int & max_cursor )
{
	if (NULL == m_curfun)
	{
		ASSERT(0);
		return false;
	}
	return m_curfun(sline_name,min_cursor,max_cursor);
}

bool SetupFuction::ReadSetup( const string &sline_name,int &n_cursor, string &sline_data )
{
	if (NULL == m_read)
	{
		ASSERT(0);
		return false;
	}
	return m_read(sline_name,n_cursor,sline_data);
}

bool SetupFuction::WriteSetup( const string &sline_name, int &n_cursor, string &sline_data )
{
	if (NULL == m_write)
	{
		ASSERT(0);
		return false;
	}
	return m_write(sline_name,n_cursor,sline_data);
}
