#pragma once
#include "DllDefine.h"
//蓝牙设备列表接口



class  CE_CONTROL_API VersionXml
{
public:
	static VersionXml* GetInstance();
	void WritXmlValue( LPCSTR valueName, int index );

	//0是全部语言--- 1是繁体--- 2是简体
   typedef enum {LAN_ALL =0, LAN_Traditional, LAN_Simplified} Option_Language;
	Option_Language GetLanguage(){ return m_opt_language; }
	void  SetLanguage(int index);


	//0是NaviKing //1是凯立德  //2是高德
	typedef enum {Navi_NaviKing =0, Navi_KaiLiDe, Navi_GaoDe} Option_NaviSoftWare ;
	Option_NaviSoftWare GetNaviSoftCode(){ return m_opt_Navi_SoftWare;}
	const string& GetNaviSoftWare()
	{
		if (Navi_NaviKing == m_opt_Navi_SoftWare){
			return m_strNaviKing;
		}
		else if (Navi_KaiLiDe == m_opt_Navi_SoftWare){
			return m_strKaiLiDe;
		}
		else if (Navi_GaoDe == m_opt_Navi_SoftWare){
			return m_strGaoDe;
		}
		else{
			ASSERT(0);
			return m_strGaoDe;
		}
	}
	void  SetSoftWare(int index);


	 //0是有导航混音//1是没有导航混音
	typedef enum  {Navi_Mix_Added =0, Navi_Mix_Removed}Option_NaviMixSound;
	Option_NaviMixSound GetNaviMix(){ return m_opt_Navi_MixSound;}
	void  SetNaviMix(int index);


	//0是有蓝牙//1是没有蓝牙
	typedef enum {BT_Module_Added =0, BT_Module_Removed}Option_BT_Module;
	Option_BT_Module GetBtModule(){return m_bt_Module; }
	void  SetBtModule(int index);


	//0是有超重低音选择//1是没有超重低音 
	typedef enum {Navi_BSF_Added =0, Navi_BSF_Removed}Option_BSF_Module;
	Option_BSF_Module GetBSFModule(){ return m_bsf_Module;}
	void  SetBSFModule(int index);




private:
	VersionXml();
	bool Init();
	
	static VersionXml *m_pInstance;


	string m_strNaviKing;
	string m_strKaiLiDe;
	string m_strGaoDe;

	Option_Language		m_opt_language;
	Option_NaviSoftWare m_opt_Navi_SoftWare;
	Option_NaviMixSound m_opt_Navi_MixSound;
	Option_BT_Module    m_bt_Module;
	Option_BSF_Module   m_bsf_Module;


	string  m_strXmlPath;


};