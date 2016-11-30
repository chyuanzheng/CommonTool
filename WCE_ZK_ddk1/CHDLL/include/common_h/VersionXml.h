#pragma once
#include "DllDefine.h"
//�����豸�б�ӿ�



class  CE_CONTROL_API VersionXml
{
public:
	static VersionXml* GetInstance();
	void WritXmlValue( LPCSTR valueName, int index );

	//0��ȫ������--- 1�Ƿ���--- 2�Ǽ���
   typedef enum {LAN_ALL =0, LAN_Traditional, LAN_Simplified} Option_Language;
	Option_Language GetLanguage(){ return m_opt_language; }
	void  SetLanguage(int index);


	//0��NaviKing //1�ǿ�����  //2�Ǹߵ�
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


	 //0���е�������//1��û�е�������
	typedef enum  {Navi_Mix_Added =0, Navi_Mix_Removed}Option_NaviMixSound;
	Option_NaviMixSound GetNaviMix(){ return m_opt_Navi_MixSound;}
	void  SetNaviMix(int index);


	//0��������//1��û������
	typedef enum {BT_Module_Added =0, BT_Module_Removed}Option_BT_Module;
	Option_BT_Module GetBtModule(){return m_bt_Module; }
	void  SetBtModule(int index);


	//0���г��ص���ѡ��//1��û�г��ص��� 
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