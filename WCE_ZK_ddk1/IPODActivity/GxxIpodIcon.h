#pragma once
#include "IPODDllModule.h"
#include "GxxPicture.h"
#include "AnimationManage.h"
#include "GXNotify.h"

class CE_IPODACTIVITY_API GxxIpodIcon : public GxxPicture
{
public:
	GxxIpodIcon();
	virtual ~GxxIpodIcon();
	static GxxView* CreateControl();
	void SetReceiveIcon(bool brec);
	void ResetIcon(); //ÃÌº”∫Ø ˝£¨÷ÿ÷√IpodÕº∆¨°£

protected:
	DECLARE_NOTIFY_CALLBACK(ReceiveIcon, GxxIpodIcon);
	virtual void setCtrLayout( TiXmlElement * ele);
	virtual void Draw();
	HANDLE     m_hIpod;
	bool       m_isIconOk;

private:
	bool    m_isReceiveIcon;
	
};
