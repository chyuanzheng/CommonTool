#pragma once

#define     WM_EXIT_PROSS                      WM_USER + 554
#define     ZK_MSG_BASE                       WM_USER + 555

#define     SETUP_READ_DATA							     ZK_MSG_BASE - 2//��ȡ����
#define     SETUP_WRITE_DATA							 ZK_MSG_BASE - 3//д������

#define     MCU_POPMENU							 ZK_MSG_BASE +1
#define     MCU_POPMENU_LONG                       ZK_MSG_BASE +2
#define		CTR_MESSAGE                       ZK_MSG_BASE + 3  //����AbControl����Ϣ������ͨ�������Ϣ�ŷ��͡�
#define		CTR_ANIMATION_MES                 ZK_MSG_BASE + 4  //֪ͨ���ζ�������Ϣ
#define		CTR_TRANLATE_MES                  ZK_MSG_BASE + 5  // 
#define		CTR_CYCLE_STOP                   ZK_MSG_BASE +  6  //֪ͨ���ζ�������Ϣ
#define		CTR_VOLUME_MES                   ZK_MSG_BASE +  7  //����
#define		CTR_VOLUME_MAX                   ZK_MSG_BASE +  8  //�������

#define		CTR_LIST_BACK_ACTIVITY                   ZK_MSG_BASE +  9  //�ص���ҳ�� btn_back
#define		CTR_FUC_ACTIVITY                   ZK_MSG_BASE +  10  //�ص���һ������ҳ�� btn_x
#define		CTR_INTO_FULL_SCREEN                   ZK_MSG_BASE +  11  //����ȫ��
#define		CTR_EXIT_FULL_SCREEN                   ZK_MSG_BASE +  12  //����ȫ��
#define		CTR_INTO_DVD_INTERFACE                  ZK_MSG_BASE +  13  //����DVD����
#define		CTR_EXIT_DVD_INTERFACE                  ZK_MSG_BASE +  14  //����DVD����
#define		CTR_DVD_ENABLE_OR_NOT                  ZK_MSG_BASE +  15  //DVD�Ƿ�ɲ�����
#define		CTR_BT_CONNECTED                  ZK_MSG_BASE +  16  //����������
#define		CTR_BT_DISCONNECTED                  ZK_MSG_BASE +  17  //�����ѶϿ�
#define		CTR_USB_MEDIA_STOP                  ZK_MSG_BASE +  18  //USB����Ƶֹͣ
#define		CTR_USB_MEDIA_PLAY					ZK_MSG_BASE +  19  //USB����Ƶ����
#define		CTR_USB_MEDIA_PAUSE					ZK_MSG_BASE +  20  //USB����Ƶ��ͣ
#define		CTR_USB_MEDIA_RECODE_FAIL					ZK_MSG_BASE +  21  //USBý�����ʧ��

#define		CTR_INTO_MAIN_INTERFACE						ZK_MSG_BASE +  22  //����������
#define		CTR_USB_MEDIA_VIDEO_CHANG					ZK_MSG_BASE +  23  //USB���ŵ���Ŀ�ı�
#define		CTR_USB_MOVIE_INFO							ZK_MSG_BASE +  24  //USB��Ƶ��Ϣ�ı�

#define		CTR_IPOD_MEDIA_CHANGE						ZK_MSG_BASE +  25  //IPODý��ı�
#define		CTR_NAVI_SHOW						ZK_MSG_BASE +  26  //��������
#define		CTR_NAVI_HIDE						ZK_MSG_BASE +  27  //��������
#define		CTR_POST_PAINT						ZK_MSG_BASE +  28  //ˢ����Ļ



#define		CTR_LISTLINE_MES                  ZK_MSG_BASE + 31  //�б����Ϣ
#define		CTR_LISTBOX_MES                  ZK_MSG_BASE + 32  //�б����Ϣ


#define		CTR_LISTBOX_X                    ZK_MSG_BASE + 33  //�б����Ϣ

#define		CTR_TOOL_ANIMATION                       ZK_MSG_BASE + 34//���԰�����ģ�����½ǵİ���

#define		CTR_ENTER_EDIT_MODE                        ZK_MSG_BASE + 35
#define		CTR_EXIT_EDIT_MODE                        ZK_MSG_BASE + 36

#define		CTR_APP_LEFT_MODE                        ZK_MSG_BASE + 37
#define		CTR_APP_RIGHT_MODE                        ZK_MSG_BASE + 38
#define		CTR_BT_SWITCH                            ZK_MSG_BASE +  39  //�����Ƿ��




#define     ZK_MSG_BASE_2                       WM_USER + 1510
#define		CTR_SET_BTN_MATCH                    ZK_MSG_BASE_2 + 1  //
#define		CTR_DEVICE_DELETE					 ZK_MSG_BASE_2 + 2  //
#define		CTR_DEVICE_CONNECT					 ZK_MSG_BASE_2 + 3  //
#define		CTR_DEVICE_DISCONNECT				 ZK_MSG_BASE_2 + 4  //
#define		CTR_LISTLINE_ENABLE			 ZK_MSG_BASE_2 +  5  //
#define		CTR_DEFEAT_ENABLE			 ZK_MSG_BASE_2 +  6  //
#define		CTR_LINE_01_SWITCH			 ZK_MSG_BASE_2 +  7  //


#define		MES_LBUTTONDOWN               ZK_MSG_BASE_2 + 20  //
#define		MES_LBUTTONUP                 ZK_MSG_BASE_2 + 21  //
#define		MES_LBUTTONLONG                 ZK_MSG_BASE_2 + 22  //
#define		MES_MSG_OK                     ZK_MSG_BASE_2 + 23  //
#define		MES_MSG_CANCEL                     ZK_MSG_BASE_2 + 24  //

#define		MES_ADD_VEDIO_SET                    ZK_MSG_BASE_2 + 25  //

#define		MES_ANIMATION_END                  ZK_MSG_BASE_2 + 32  //

#define		CTR_DTV_SIGNAL   					ZK_MSG_BASE_2 +  33  //����������




#define		CTR_SETUP_START_ACTIVITY                  ZK_MSG_BASE_2 + 39  //�б����Ϣ
#define		CTR_SETUP_START_LISTBOX                  ZK_MSG_BASE_2 + 40  //�б����Ϣ
#define		CTR_SETUP_START_MASSAGE                  ZK_MSG_BASE_2 + 41  //�б����Ϣ

#define		CTR_SETUP_READ_LIST						ZK_MSG_BASE_2 + 42  //�б����Ϣ,��listȥ��ȡ����,��һ���������ַ���
#define		CTR_SETUP_READ_CURSOR					ZK_MSG_BASE_2 + 43  //�б����Ϣ,��listȥ��ȡ����
#define		CTR_SET_BSF_LINE						ZK_MSG_BASE_2 + 44  //
#define		CTR_SET_BEEP							ZK_MSG_BASE_2 + 45  //


#define		CTR_BTN_MATCH_BACK						ZK_MSG_BASE_2 + 46  //���صĺ���

#define		CTR_CLOSE_MUTE							ZK_MSG_BASE_2 + 47  //
#define		CTR_SWITCH_MUTE							ZK_MSG_BASE_2 + 48  //
#define		CTR_LISTBOX_FILEITEM					ZK_MSG_BASE_2 + 49  //
#define		CTR_LIST_PERCENT_BTN					ZK_MSG_BASE_2 + 50  //



#define		CTR_SOUND_SET 					ZK_MSG_BASE_2 + 51  //


#define		CTR_IPOD_BACK					ZK_MSG_BASE_2 + 52  //
#define		CTR_MAIN_LOAD					ZK_MSG_BASE_2 + 53  //

#define		CTR_DELETE_ALL					ZK_MSG_BASE_2 + 54  //

#define		CTR_INIT_MUTE							ZK_MSG_BASE_2 + 55  //

#define		CTR_START_ALL_MODULE					ZK_MSG_BASE_2 + 56  //

#define		CTR_BUTTON_SWITCH					ZK_MSG_BASE_2 + 57  //

#define		ANIMATION_START                   0  //������ʼ
#define		ANIMATION_END                     1 //��������






#define ANIMOTION_TIME    30 //msһ��animation


#define ANIMOTION_TIMER_NAME  "Aniation_Timer"



