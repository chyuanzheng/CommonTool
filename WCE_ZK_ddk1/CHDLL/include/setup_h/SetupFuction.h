#pragma once

typedef bool (*SET_READ_WRITE)(const string &sline_name,int  &n_cursor, string &sline_data);
typedef bool (*SET_READ_MM)(const string &sline_name, int & min_cursor, int & max_cursor);

typedef int (*GET_STATUS)(const string &sline_name);

#define  SETUP_FUN_OK          0x01  
#define  SETUP_FUN_WAITING     0x02  

class CE_CONTROL_API SetupFuction
{
public:
	static SetupFuction* GetInstance();

	void SetFunction(SET_READ_WRITE rfun,SET_READ_WRITE wfun, SET_READ_MM mmfun, GET_STATUS getfun = S_GetStatus)
	{
		m_read = rfun;
		m_write = wfun;
		m_curfun = mmfun;
		m_getfun = getfun;
	}

	/************************************************************************/
	/*          	 读取游标
	                 [out]max_cursor    是最小的游标
					 [out]max_cursor    是最大的游标
					 返回false表示失败                                      */
	/************************************************************************/
	bool  ReadMinMax(const string &sline_name,int & min_cursor,int & max_cursor);

	/************************************************************************/
	/*          	 读取设置
	                 [out]n_cursor    是当前的游标
					 [out]sline_data  是需要显示的数值
					 返回false表示失败                                      */
	/************************************************************************/
	bool   ReadSetup(const string &sline_name,int &n_cursor, string &sline_data);


	/************************************************************************/
	/*          	 写入设置 
	                 [in]n_cursor    是当前的游标
					 [out]sline_data  是需要显示的数值
					 返回false表示失败                                      */
	/************************************************************************/
	bool   WriteSetup(const string &sline_name, int &n_cursor, string &sline_data);


	int    GetStatus(const string &sline_name)
	{
		return m_getfun(sline_name);
	}

private:
	SetupFuction()
	{
		m_read = NULL;
		m_write = NULL;
		m_curfun = NULL;
	}
	~SetupFuction();
	static int S_GetStatus(const string &sline_name)
	{
		return SETUP_FUN_OK;
	}
	static SetupFuction *m_pInstance;

	SET_READ_WRITE m_read;
	SET_READ_WRITE m_write;
	SET_READ_MM m_curfun;
	GET_STATUS  m_getfun;
};

