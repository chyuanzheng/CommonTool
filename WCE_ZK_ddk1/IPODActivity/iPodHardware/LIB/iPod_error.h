/**************************************************************************			
***                                                                          
***   Telechips SYS1-1 Team                          
***                                                                          
***   Module : iPod_error.h                
***                                                              
**************************************************************************/

#ifndef _IPOD_ERROR_H_
#define _IPOD_ERROR_H_


typedef enum 
{
	IPOD_NO_ERROR = 0x00,

	IPOD_UNKNOWN_DATABASE_CATEGORY = 0x01,

	IPOD_COMMAND_FAILED = 0x02,

	IPOD_OUT_OF_RESOURCE = 0x03,

	IPOD_BAD_PARAMETER = 0x04,

	IPOD_UNKNOWN_COMMAND = 0x05,

	IPOD_RESERVERD = 0x06,

	IPOD_ACCESSORY_NOT_AUTHENTICATED = 0x07,

	IPOD_BAD_AUTHENTICATION_VERSION = 0x08,

	IPOD_ACCESSORY_POWER_MODE_REQUEST_FAILED = 0x09,

	IPOD_CERTIFICATE_INVALID = 0x0A,

	IPOD_CERTIFICATE_PERMISSION_INVALID = 0x0B,

	IPOD_FILE_IS_IN_USE	= 0x0C,

	IPOD_INVALID_FILE_HANDLE = 0x0D,

	IPOD_DIRECTORY_NOT_EMPTY = 0x0E,

	IPOD_OPERATION_TIMED_OUT = 0x0F,

	IPOD_CMD_UNAVILABLE_IN_THIS_IPOD_MODE = 0x10,

	IPOD_INVALID_ACCESSORY_REGISTOR_ID_VAL = 0x11,

    IPOD_SELECTION_NOT_GENIUS = 0x12,

    IPOD_MULTISECTION_DATA_SECTION_REVCEIVED_SUCCESSFULLY = 0x13,

    IPOD_LINGO_BUSY = 0x14,

    IPOD_MAXIMUM_NUMBER_OF_ACCESSORY_CONNECTIONS_ALREADY_REACHED = 0x15,

    IPOD_HID_DESCRIPTOR_INDEX_ALREADY_IN_USE = 0x16,

    IPOD_DROPPED_DATA = 0x17,

    IPOD_ATTEMPT_TO_ENTER_IPOD_OUT_MODE_WITH_INCOMPATIBLE_VIDEO_SETTING = 0x18,
    
	IPOD_INTERNAL_LIB_ERROR_START = 0xFF,
	/*
		iPod library gets the invalid parameter 
		Just NULL pointer check 
	*/
	IPOD_INVALID_PARAM = 0x100,

	/*
		There is no return data.
	*/
	IPOD_NO_DATA = 0x101,


	/*
		Previous command is not finished.
	*/
	IPOD_PREVIOUS_CMD_NOT_FINISHED = 0x102,

	/*
		Invalid return data from iPod
	*/	
	IPOD_DATA_PASING_ERROR = 0x103,

	/*
		Initialize error of IPOD_init_XXX function.
	*/	
	IPOD_ALREADY_INIT = 0x104,
	IPOD_INIT_SUCCESS = 0x105,
	IPOD_INIT_FAIL = 0x106,
	IPOD_ALREADY_DEINITED = 0x107,

	/*
		iPod identification error
		Please check the iPod_init function's MLingoType parameter or
		I2C channel 
	*/
	IPOD_IDENTYFY_ERROR = 0x108,


	/*
		There is no response of specific command 
	*/
	
	IPOD_TIMOUT_ERROR = 0x109,

	/*
		If the iPod is not initialized, It is not prepared the library context
	*/
	IPOD_CONTEXT_ERROR = 0x10A,

	/*	
		iPod Library Message Queue Error
	*/
	IPOD_OPEN_MSGQ_ERROR = 0x10B,
	
	/*	
		iPod Library Message Queue Error
	*/
	IPOD_READ_MSGQ_ERROR = 0x10C,

	/*	
		iPod Library Message Queue Error
	*/
	IPOD_WRITE_MSGQ_ERROR = 0x10D,

	/*
		iPod library thread error 
		wrong thread ID or thread is not running.
	*/
	IPOD_THREAD_ERROR = 0x10E,
	
	/*
		iPod is disconnected.
	*/
	IPOD_DISCONNECT_ERROR = 0x10F,

	/*
		iPod event not found
	*/
	IPOD_NOT_REG_EVENT = 0x110,

	/*
		Packet Transaction Error (under IDPS)
	*/
	IPOD_TRANSACTION_ERROR = 0x111,	


	IPOD_COMMAND_ACCEPTED = 0x112,

	IPOD_COMMAND_TIMEOUT = 0x113,

	/*
		parsing Error of FID token ACK.
	*/
	IPOD_TOKEN_PARSING_ERROR = 0x114,

	/*
		Error of FID token ACK.
	*/
	IPOD_TOKEN_ERROR = 0x115,

	/*
		
	*/
	IPOD_IDPS_ERROR = 0x116,

	/*

	*/
	IPOD_NOT_EXIST = 0x117,

	/*

	*/
	IPOD_MALLOC_ERROR = 0x118,

	IPOD_IDPS_NOT_SUPPORT_ERROR = 0x119,

	IPOD_CLASSID_NOT_MATCHED = 0x11A,

	IPOD_UNKNOWN_TRACKID = 0x11B,

	IPOD_COMMAND_PENDING = 0x11C,

	IPOD_NOT_AUTHENTICATED = 0x11D,

	IPOD_MISMATCHED_AUTH_PROTOCOL_VER = 0x11E,

	IPOD_NOT_SUPPORTED_CMD = 0x11F,

	IPOD_NO_SEARCHED_DATA = 0x120,

	IPOD_INVALID_HANDLE = 0x121,

	IPDO_INVALID_BASIC_FORMATID = 0x122,
	
	/*
		semaphore error
		IPOD_API_Init() should be called.
	*/
	IPOD_SEMA_ERROR = 0x123,

	IPOD_INVALID_TX_BUFFER = 0x124,

	IPOD_BUFFER_ERROR = 0x125,

	IPOD_COMMAND_MISMATCH = 0x126,

	IPOD_AUTH_INFO_ERROR = 0x127,

	IPOD_AUTH_SIG_ERROR = 0x128,

	IPOD_AUTH_CP_ERROR = 0x129,

	IPOD_INVALID_PARAM_FROM_IPOD = 0x12a,

	IPOD_OVERFLOW_TX_BUFFER = 0x12b,

	/*
		UART or USB IO interface Error 
		write error 
	*/
	IPOD_IO_CHANNEL_ERROR = 0x200,

	/*
		I2C interface Error of authentication IC.
		read or write error
	*/
	IPOD_IO_CP_ERROR = 0x202,

	IPOD_IO_CHECKSUM_ERROR = 0x203,


	IPOD_CMD_SYNC_ERROR = 0x300,

	/*

	*/
	IPOD_DATA_PASING_FINISHED = 0x800,
	IPOD_NO_DATA_TO_PASING = 0x801,

	/*
		Data Transfer Session
	*/
	IPOD_NOT_ESTABLISHED_SESSION_ERROR = 0x900,

	/*
		Retry Init !!
	*/
	IPOD_RETRY_IDPS = 0xA00,
	IPOD_IDPS_TIMEOUT =0xA01,
	IPOD_IDPS_ERROR_STATE = 0xA02,
    IPOD_RETRY_STARTIDPS = 0xA03,
    
	IPOD_TOKEN_NO_VALUE = 0xB00,

	IPOD_BUFFER_OVERFLOW		= 0xC00,

	IPOD_WORK_QUEUE_OVERFLOW = 0xD00,


	IPOD_UNKONWN_ERROR = 0x9000,
	IPOD_MAX_ERROR = 0x7FFFFFFF
}IPOD_ERROR;


#endif	// _IPOD_ERROR_H_
