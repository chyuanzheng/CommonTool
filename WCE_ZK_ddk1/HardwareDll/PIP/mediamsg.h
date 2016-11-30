#pragma once

// for camera									// wParam												|	//lParam
#define WM_MEDIAMODE			WM_USER+1000	// 0 进入camera 模式, 1 进入 movie 模式					|
#define WM_INITPREVIEW			WM_USER+1001	// 0 NTSC, 1 PAL										|
#define WM_MEDIARECT				WM_USER+1002	// 设置显示位置										|
#define WM_CAMERAPLAY			WM_USER+1003	// 0 开始捕捉, 1 暂停, 2 停止							|
#define WM_CAMERACROPRECT		WM_USER+1004
// for movie
#define	WM_MOVIEPLAY			WM_USER+1005	// 0 开始播放视频, 1 暂停, 2 停止						|	播放时间
#define WM_MOVIESTATUS			WM_USER+1006	// 获取视频播放状态
#define WM_MOVIETIME			WM_USER+1007	// 获取视频播放时间 wParam=当前时间, lParam=总时间
#define WM_PLAYRADIO			WM_USER+1031
// for music
#define	WM_MUSICPLAY			WM_USER+1008	// 0 开始播放音频, 1 暂停, 2 停止						|	播放时间
#define WM_MUSICSTATUS			WM_USER+1009	// 获取音频播放状态
#define WM_MUSICTIME			WM_USER+1010	// 获取音频播放时间 wParam=当前时间, lParam=总时间
#define WM_MUSICINFO			WM_USER+1011	// 获取音乐ID3信息
#define WM_MUSICALBUM			WM_USER+1012	// 获取音乐封面信息
// for photo
#define WM_PHOTOPlAY			WM_USER+1301	// 显示图片
#define WM_PHOTOROTATE			WM_USER+1302	// 旋转图片
#define WM_PHOTOZOOM			WM_USER+1303	// 缩放图片
#define WM_PHOTOGETNEXT			WM_USER+1304	// 得到下一张图片
#define WM_REDRAW				WM_USER+1305

// for normal message
#define WM_SETHWND				WM_USER+1020
#define WM_MEDIALBUTTONDOWN		WM_USER+1022
#define WM_MEDIALBUTTONUP		WM_USER+1023
#define WM_MEDIAHEART			WM_USER+1024
#define WM_VMODE				WM_USER+1025
#define WM_VOLUME				WM_USER+1026