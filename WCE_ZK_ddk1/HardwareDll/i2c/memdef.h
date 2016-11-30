#define NO_KEY		0
#define KEY_HOME	1
#define KEY_VOLD	2
#define KEY_VOLU	3
#define KEY_OPEN	4
#define KEY_RETRUN	5
#define KEY_MODE0	6
#define KEY_BT		7
#define KEY_PP		8
#define KEY_PREV	9
#define KEY_NEXT	10
#define KEY_MEDIA	11
#define KEY_MUTE	12
#define KEY_SOUND	13
#define KEY_PIC		14
#define KEY_MODE	15
#define KEY_FM		16
#define KEY_TV		17
#define KEY_NAVI	18
#define KEY_DVD		19
#define KEY_STOP	20

#define MEM_ACC_STATUS			    23
#define MEM_BACK_STATUS			    24
#define MEM_LIGHT_STATUS		    25
#define MEM_BRAKE_STATUS		    26
#define MEM_LCD_POWER_OFF         	27
#define MEM_SYSTEM_POWER_OFF   		28

#define MEM_TPMS_IN					35		// 1: TPMS IN;  0 : NO TPMS
#define MEM_CORE_START_STATUS		36		// 核心板启动状态
#define MEM_ACC_OFF_WAIT		    37			// 0=ON `1=OFF 2=POWERKEY
#define MEM_CAN_BUS_STATUS			38		// CAN BUS是否有接入 1:有接入CAN BUS 0：没有接入CAN BUS
#define MEM_CAR_SPEED_BUFFER		39		// 车速buffer

#define MEM_GPS_ANT_STATUS			40		// GPS天线0：正常；1；短路；2：断路
#define MEM_RADIO_ANT_STATUS		41		// RADIO天线0：正常；1；短路；2：断路

#define MEM_AC_B50_ILOOP		42  	// 空调内循环 0:off;1:左内循环；2:右内循环
#define MEM_AC_B55_DUAL			43	// 空调双区控制
#define MEM_AC_B58_RLOCK		44  	// 后窗除雾
#define MEM_AC_B5B_LTEMP		45	// 空调左区温度
#define MEM_AC_B61_RTEMP		46	// 空调右区问题
#define MEM_AC_B62_FAN			47	// 空调风扇速度
#define MEM_AC_B63_AUTO			48	// 空调AUTO信息 0:off,1:low 2:high
#define MEM_AC_B64_1_GL			49	// 空调前玻璃除雾
#define MEM_AC_B64_2_FANF		50	// 前出风
#define MEM_AC_B64_3_FANR		51	// 后出风
#define MEM_AC_B71_PWR			52	// 空调电源开关
#define MEM_AC_B6E_GLMAX		53	// 空调前玻璃除雾MAX
#define MEM_AC_COOLMAX			54	// 空调快速制冷MAX
#define MEM_AC_B4D_COOLPWR		55	// 空调制冷开关
#define MEM_AC_B5F_MASTER_SEAT    	56	// 主驾驶座
#define MEM_AC_B65_SLAVE_SEAT    	57	// 副驾驶座


#define MEM_PA5_VL_Abstand          70    //雷达垂直左方  
#define MEM_PA5_VR_Abstand          71    //雷达垂直右方   
#define MEM_PA5_HL_Abstand          72    //雷达水平左方  
#define MEM_PA5_HR_Abstand          73    //雷达水平右方   

#define MEM_PA5_VML_Abstand         74    //雷达垂直后左方  
#define MEM_PA5_VMR_Abstand         75    //雷达垂直后右方   
#define MEM_PA5_HML_Abstand         76    //雷达水平后左方  
#define MEM_PA5_HMR_Abstand         77    //雷达水平后右方  


#define MEM_STEERING_WHEEL          85     //方向盘转角
#define MEM_BACK_RADAR_STATUS       86    //0:OFF;1:ON
#define MEM_DISC_IN_START           87   //入碟开机


#define MEM_RESET_ARM					98
#define MEM_WHEEL_KEY					99
#define MEM_POWER_KEY					100

#define MEM_IR_ARM						101
#define MEM_DTV_IR_CUSTOM				102
#define MEM_DTV_IR_CODE					103

#define MEM_NJW_OUTPUT					110
#define MEM_FAN_POWER                  	111
#define MEM_TFT_POWER                  	112
#define MEM_EXTAMP_POWER             	113
#define MEM_DVD_POWER			        114
#define MEM_VDD12_POWER			        115
#define MEM_DTV_POWER			        116

#define MEM_IRRECV_CUSCODE			246
#define MEM_CAN_YEAR_MONTH		247
#define MEM_CAN_DAY_TIME		248
#define MEM_TOUCH_SCREEN_COM	249    //触摸屏命令

#define MEM_MCU_VER_YEAR		251
#define MEM_MCU_VER_MONTH		252
#define MEM_MCU_VER_DAY			253
#define MEM_CAR_STATE_CHANGE	254









