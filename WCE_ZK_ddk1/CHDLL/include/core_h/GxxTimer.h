#pragma once
	/************************************************************************/
	/*       ��ʱ������״̬alive_always��ʾTimer��һֱ������Ϣ��
	alive_when_active ֻ�е�View����active�ᷢ����Ϣ��
	alive_only_active ��View������activeʱ��ر�Timer*/
	/************************************************************************/
class CE_CONTROL_API GxxTimer 
{
protected:
	UINT RegisterTimer(UINT uElapse, const char* name = NULL);
	void UnRegisterTimer(UINT uID);

	UINT OpenTimer(const char * name);
	void StartTimer(UINT uID);
	void StopTimer(UINT uID);
	GxxTimer( ){};
	virtual ~GxxTimer( ){};
	//�ؼ����� ele�еĲ��������Լ�������
public:
	virtual void TimerTick(UINT nIDEvent){}

};

