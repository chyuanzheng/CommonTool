#pragma once
#include "iic.h"

/*
0--2
0--no correction
1--2 bits
2--5 bits
*/
#define RDS_ERR_LEVEL  1


#define RDS_DECODER_ADDR     0x20

typedef struct
{
	BYTE W0;    //initialization and mode control setting
	BYTE W1;    //pause level and flywheel setting
	BYTE W2;    //pause time/oscillator frequency and quality detector sensitivity setting
}s_rdsctrl_word;

/*
for saa6588 rds decoder
*/
#define SQCM   0
#define TSQD   0
#define NWSY  1
#if (RDS_ERR_LEVEL == 0)
#define SYM    0x00
#elif(RDS_ERR_LEVEL == 1)
#define SYM    0x01
#elif(RDS_ERR_LEVEL == 2)
#define SYM    0x11
#endif
#define RBDS  0
/*PL--pause level 0--3*/
#define PL      0 
/*
DAC--DAVN signal 
0x00: H--sync search  L--a new block found
0x02: H--sync search L--a correct A-block detected //fast PI search
0x03: H--sync search L--2 new block available
*/
#define DAC   0x01
#define FEB   0x20//100000
/*PTF 00=4.332MHz;01=8.664MHz;10=12.996MHz;11=17.328MHz*/
#define PTF   0x00 //4.332MHz
#define SOSC 1
/*
SQS signal qualities
0x00---9.0dB
0x0f---0dB
0x1f---+9.6dB
*/
#define SQS   0x0f

#define AW0  ((SQCM<<7)|(TSQD<<6)|(NWSY<<5)|(SYM<<3)|(RBDS<<2)|(DAC))
#define AW1  ((PL<<6)|(FEB))
#define AW2  ((PTF<<6)|(SOSC<<5)|(SQS))

class SAA6588
{

public:
	BYTE rds_data[7];

	char radioTextBufA[2][65];
	char radioTextBufB[2][33];
	char programServiceBuf[9];
	char programTypeNameBuf[9]; 
	TCHAR programTypeBuf[17];
	TCHAR clocktimeBuf[26];
	UINT16 txtAreadyFlag,txtBreadyFlag,ptynReadyFlag,ctReadyFlag;
	BYTE psReadyFlag,ptyReadyFlag; 

	UINT16 radio_text_type;

	BYTE rds_func_flag;
	BYTE rdsinfo_dispindex ;

	UINT16 ta;
	BYTE   pty;

	UINT16	af_count;
	UINT16  cur_count;
	BYTE	AFFreq[25];

	BOOL  ta_flag, af_flag;
	BOOL  bHasRDS;

	UINT16 nowPI;
	UINT16 afPI;

public:
	SAA6588()
	{
		memset(rds_data,0,sizeof(rds_data));
		rds_clear_var();
		af_count = 0;
		cur_count = 0;
		memset(AFFreq, 0, sizeof(AFFreq));
		ta_flag = 0;
		af_flag = 0;
		bHasRDS = 0;
	}

	void Clear()
	{
		memset(rds_data,0,sizeof(rds_data));
		rds_clear_var();
		af_count = 0;
		cur_count = 0;
		memset(AFFreq, 0, sizeof(AFFreq));
		ta_flag = 0;
		af_flag = 0;
		bHasRDS = 0;
		nowPI = 0;
	}

	void Init();


	void CollectData();



	void rds_clear_var(void);



	// Basic Tuning and Switching (AF, PS)
	void rds_process_group0(UINT16 a, UINT16 b, UINT16 c, UINT16 d);




	/*====================================================

	====================================================*/
	void rds_process_group1(UINT16 a, UINT16 b, UINT16 c, UINT16 d);


	// Radiotext

	void rds_process_group2(UINT16 a, UINT16 b, UINT16 c, UINT16 d);



	// Clock-time and date
	void rds_process_group4(UINT16 a, UINT16 b,  UINT16 c, UINT16 d);


	// Program type Name (8 char)
	void rds_process_group10(UINT16 a, UINT16 b, UINT16 c, UINT16 d);



	void rds_process_group(UINT16 a, UINT16 b, UINT16 c, UINT16 d);


	void rds_process_block(UINT8 id, UINT16 v);


	TCHAR *get_ptyBuf(int i);


	char * rds_get_ps(void)
	{
		return programServiceBuf;
	}

	TCHAR * rds_get_pty(void)
	{
		return programTypeBuf;
	}

	char * rds_get_rt(BYTE type)
	{
		if(type == 0)
			return radioTextBufA[0];
		else if(type == 1)
			return radioTextBufA[1];
		else
			return NULL;
	}

	TCHAR * rds_get_ct(void)
	{
		return clocktimeBuf;
	}

	char * rds_get_ptyn(void)
	{

		return programTypeNameBuf;
	}

	UINT16 SAA6588::rds_data_read(void);
};