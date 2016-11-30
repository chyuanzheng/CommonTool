#pragma once

// for camera									// wParam												|	//lParam
#define WM_MEDIAMODE			WM_USER+1000	// 0 ����camera ģʽ, 1 ���� movie ģʽ					|
#define WM_INITPREVIEW			WM_USER+1001	// 0 NTSC, 1 PAL										|
#define WM_MEDIARECT				WM_USER+1002	// ������ʾλ��										|
#define WM_CAMERAPLAY			WM_USER+1003	// 0 ��ʼ��׽, 1 ��ͣ, 2 ֹͣ							|
#define WM_CAMERACROPRECT		WM_USER+1004
// for movie
#define	WM_MOVIEPLAY			WM_USER+1005	// 0 ��ʼ������Ƶ, 1 ��ͣ, 2 ֹͣ						|	����ʱ��
#define WM_MOVIESTATUS			WM_USER+1006	// ��ȡ��Ƶ����״̬
#define WM_MOVIETIME			WM_USER+1007	// ��ȡ��Ƶ����ʱ�� wParam=��ǰʱ��, lParam=��ʱ��
#define WM_PLAYRADIO			WM_USER+1031
// for music
#define	WM_MUSICPLAY			WM_USER+1008	// 0 ��ʼ������Ƶ, 1 ��ͣ, 2 ֹͣ						|	����ʱ��
#define WM_MUSICSTATUS			WM_USER+1009	// ��ȡ��Ƶ����״̬
#define WM_MUSICTIME			WM_USER+1010	// ��ȡ��Ƶ����ʱ�� wParam=��ǰʱ��, lParam=��ʱ��
#define WM_MUSICINFO			WM_USER+1011	// ��ȡ����ID3��Ϣ
#define WM_MUSICALBUM			WM_USER+1012	// ��ȡ���ַ�����Ϣ
// for photo
#define WM_PHOTOPlAY			WM_USER+1301	// ��ʾͼƬ
#define WM_PHOTOROTATE			WM_USER+1302	// ��תͼƬ
#define WM_PHOTOZOOM			WM_USER+1303	// ����ͼƬ
#define WM_PHOTOGETNEXT			WM_USER+1304	// �õ���һ��ͼƬ
#define WM_REDRAW				WM_USER+1305

// for normal message
#define WM_SETHWND				WM_USER+1020
#define WM_MEDIALBUTTONDOWN		WM_USER+1022
#define WM_MEDIALBUTTONUP		WM_USER+1023
#define WM_MEDIAHEART			WM_USER+1024
#define WM_VMODE				WM_USER+1025
#define WM_VOLUME				WM_USER+1026