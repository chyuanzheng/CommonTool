#include "stdafx.h"
#include "SAA6588.h"

TCHAR *ptyName[]= {L"NONE", L"NEWS", L"CURRENT AFFAIR", L"INFORMATION",
L"SPORT", L"EDUCATION", L"DRAMA", L"CULTURE",
L"SCIENCE", L"VARIED SPEECH", L"POP MUSIC", L"RICK MUSIC",
L"EASY LISTENING", L"LIGHT CLASSIC MUSIC", L"SERIOUS CLASSICS", L"OTHER MUSIC",
L"WEATHER", L"FINANCE", L"CHILDRENS PROGS", L"SOCAIL AFFAIRS",
L"RELIGION", L"PHONE IN", L"TRAVEL", L"LEISURE AND HOBBY",
L"JAZZ", L"COUNTRY", L"NATIONAL MUSIC", L"OLDIES",
L"FOLK", L"DOCUMENTARY", L"ALARM TEST", L"ALARM"};

void SAA6588::Init()
{
	BYTE data[4] = {0};
	data[0] = RDS_DECODER_ADDR;
	data[1] = AW0;
	data[2] = AW1;
	data[3] = AW2;
	IICWrite(data,4);
}

void SAA6588::CollectData()
{
#ifdef UIONLY
	return;
#else
	IICRead4(RDS_DECODER_ADDR,7,rds_data);
#endif
	//STLOG_WRITE("0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x", rds_data[0],rds_data[1],rds_data[2],rds_data[3],rds_data[4],rds_data[5],rds_data[6]);
}

void SAA6588::rds_clear_var(void)
{
	memset(radioTextBufA[0],0,sizeof(radioTextBufA[0])); 
	memset(radioTextBufA[1],0,sizeof(radioTextBufA[1])); 

	memset(radioTextBufB[0],0,sizeof(radioTextBufB[0])); 
	memset(radioTextBufB[1],0,sizeof(radioTextBufB[1])); 

	memset(programServiceBuf,0,sizeof(programServiceBuf)); 
	memset(programTypeNameBuf,0,sizeof(programTypeNameBuf)); 
	memset(programTypeBuf,0,sizeof(programTypeBuf)); 
	memset(clocktimeBuf,0,sizeof(clocktimeBuf)); 
	txtAreadyFlag = 0;
	txtBreadyFlag = 0;
	ptynReadyFlag = 0;
	ctReadyFlag = 0;
	psReadyFlag = 0;
	ptyReadyFlag = 0;
	rds_func_flag = 0;
	radio_text_type = 0;
	rds_func_flag = 0;
	rdsinfo_dispindex = 0;
}

void SAA6588::rds_process_group0(UINT16 a, UINT16 b, UINT16 c, UINT16 d)
{  
	static UINT16 i,ms,di,ps_seg,pi;
	char ch1,ch2;
	static UINT16 lastpi;
	c=c;  //avoid warning
	pi=a;
	ta =(b>>4) & 0x01;
	ms =(b>>3) & 0x01;
	di =(b>>2) & 0x01;
	ps_seg=b&0x03;

	ta_flag = 1;

	if(lastpi!=pi) 
	{
		psReadyFlag = 0;
		for(int i=0;i<8;i++)
			programServiceBuf[i]=' ';
	}

	BYTE af1 = c>>8;
	BYTE af2 = c;
	if (af_count == 0)
	{
		if (af1>224 && af1<250)
		{
			af_count = af1-224;
			AFFreq[cur_count++] = af2;
			afPI = a;
		}
	}
	else
	{
		if (cur_count<af_count)
		{
			BOOL bMatch = 0;
			for (int i=0;i<cur_count;i++)
			{
				if (AFFreq[i] == af1)
				{
					bMatch = 1;
					break;
				}
			}
			if (!bMatch && af1<205)
			{
				AFFreq[cur_count++] = af1;
			}
			bMatch = 0;
			for (int i=0;i<cur_count;i++)
			{
				if (AFFreq[i] == af2)
				{
					bMatch = 1;
					break;
				}
			}
			if (!bMatch && af2<205)
			{
				AFFreq[cur_count++] = af2;
			}
		}
		else
		{
			af_flag = 1;
		}
	}
	//af_count = c;


	ch1=d>>8;
	ch2=d&0xff;

	psReadyFlag |= 0x01<<ps_seg; 
#ifdef RDS_DBG
	//printf("seg %d\n",ps_seg);
#endif
	programServiceBuf[ps_seg*2]=ch1;
	programServiceBuf[ps_seg*2+1]=ch2;
	lastpi=pi;
	return;
}

/*====================================================

====================================================*/
void SAA6588::rds_process_group1(UINT16 a, UINT16 b, UINT16 c, UINT16 d)
{
	UINT8 gp_ab = 0,day = 0,hour =0,min = 0;

	nowPI = a = a;
	c = c;
	gp_ab = (b>>11) & 0x01;
	if(gp_ab == 0) //_1A type
	{
		day = (d>>11)&0x1f;
		hour = (d>>6)&0x1f;
		min = d&0x3f;
	}
#ifdef RDS_DBG
	//printf("time %d %d %d\n",day,hour,min);
#endif
}

// Radiotext

void SAA6588::rds_process_group2(UINT16 a, UINT16 b, UINT16 c, UINT16 d)
{
	UINT16 pi,text_ab,txt_seg,gp_ab;
	static UINT16 lastab=-1;
	static UINT16 lastpi=-1; 
	nowPI = pi=a; 
	text_ab=(b>>4) & 0x01;
	txt_seg=b &0x0f;
	gp_ab = (b>>11) & 0x01;

#ifdef RDS_DBG
	//printf("ab %d %d\n",text_ab,gp_ab);
#endif

	radio_text_type = text_ab;

	if(text_ab == 0)    
		txtAreadyFlag |= 0x01<<txt_seg;
	else if(text_ab ==1)
		txtBreadyFlag |= 0x01<<txt_seg;

	if(((c&0xff) == 0x0d) || (((c&0xff00)>>8)==0x0d) || ((d&0xff) == 0x0d) || (((d&0xff00)>>8)==0x0d))
	{
		if((text_ab == 0) && (txtAreadyFlag == (0xffff>>(15-txt_seg))))
			txtAreadyFlag = 0xffff;
		else if((text_ab == 1) && (txtBreadyFlag == (0xffff>>(15-txt_seg))))
			txtBreadyFlag = 0xffff;
	}
	if(gp_ab == 0)
	{
		radioTextBufA[text_ab][txt_seg*4]= c>>8;
		radioTextBufA[text_ab][txt_seg*4+1]= c&0xff;
		radioTextBufA[text_ab][txt_seg*4+2]= d>>8;
		radioTextBufA[text_ab][txt_seg*4+3]= d&0xff;
	}   
#ifdef RDS_DBG
	//if((txtBreadyFlag == 0xffff)||(txtAreadyFlag == 0xffff))
	//	printf("RT0:%d %s\n",text_ab,radioTextBufA[text_ab]);
#endif



	else if(gp_ab == 1)
	{ 
		radioTextBufB[text_ab][txt_seg*2] = d>>8;
		radioTextBufB[text_ab][txt_seg*2+1] = d&0xff;    
#ifdef RDS_DBG
		//printf("Radiotext: %s\n",radioTextBufB[text_ab]);
		//printf("Group2 Radiotext: a/b=%d  text_segment=%2d  TEXT=%c%c\n",
		//text_ab,txt_seg,radioTextBufB[text_ab][txt_seg*2], radioTextBufB[text_ab][txt_seg*2+1]);
#endif
	}

	//printf("*****txtAreadyFlag : %x     txtBreadyFlag :%x   ****\n",txtAreadyFlag,txtBreadyFlag);
	lastpi=pi;
	lastab=text_ab;
	return;
}

// Clock-time and date
void SAA6588::rds_process_group4(UINT16 a, UINT16 b,  UINT16 c, UINT16 d)
{
	/*static*/ UINT16 sign,mjd,hour,min,utc_offset;
	/*static*/ UINT16 y,m,dd,k=0;
	UINT8 version_ab = 0;
#ifdef RDS_DBG
	//printf("abcd %x %x %x %x\n",a,b,c,d);
#endif
	nowPI = a =a ;
	version_ab=(b>>11) & 0x01;
	if(version_ab == 0) //for 4A group
	{
		mjd= ((b&0x03)<<15) + (c>>1);
		hour     = ((c&0x01)<<4) + (d>>12);
		min      = (d>>6) & 0x3f;
		sign     = (d>>5)&0x01;
		utc_offset=d&0x1f; // in 30 min units
		y=((mjd * 100 - 1507820))/36525;
		m=(mjd*10000 - 149561000 - y * 36525 * 100)/306001;
		dd= mjd - 14956 - (y * 36525)/100 - (m * 306001)/10000;
		if(m==14 || m==15) 
			k=1;
		else k=0;
		y=y+k+1900; 
		m=m-1-k*12;

		if(sign)
			hour -= (utc_offset*5)/10;
		else
			hour += (utc_offset*5)/10; 

		ctReadyFlag = 0xff;

		if((d & 0xff00)==0xff00)
		{
#ifdef RDS_DBG
			printf("invalid time\n");
#endif
			wsprintf(clocktimeBuf,L"DATE %d-%d-%d",y,m,dd); 
		}
		else
		{
			wsprintf(clocktimeBuf,L"DATE %d-%d-%d TIME %02d:%02d",y,m,dd,hour,min); 
		}

#ifdef RDS_DBG
		//printf("date %d %d %d %d\n",y,m,dd,(utc_offset*5)/10);
		//printf("clk %d %d\n",hour,min);
#endif
	}
	else
	{
#ifdef RDS_DBG
		//printf("4B group\n");
#endif
	}
	return;
}

// Program type Name (8 char)
void SAA6588::rds_process_group10(UINT16 a, UINT16 b, UINT16 c, UINT16 d)
{
	UINT16 i,pi,last_ab=0,last_pi=0,ptn_seg,flag_ab;

	nowPI = pi=a;
	flag_ab=(b>>4) & 0x01;  

	ptn_seg=b&0x01;

	if((last_ab != flag_ab)||(last_pi!=pi))
	{
		ptynReadyFlag = 0;
		for(i=0;i<9;i++)
			programTypeNameBuf[i]=' '; 
	}

	ptynReadyFlag |= 0x01<<ptn_seg;

	programTypeNameBuf[ptn_seg*4]= c>>8;
	programTypeNameBuf[ptn_seg*4+1]= c&0xff;
	programTypeNameBuf[ptn_seg*4+2]= d>>8;
	programTypeNameBuf[ptn_seg*4+3]= d&0xff;

	last_ab=flag_ab;
	last_pi=pi;
	return;
}

void SAA6588::rds_process_group(UINT16 a, UINT16 b, UINT16 c, UINT16 d)
{
	UINT16 pi, group_type,version_ab,  tp;

	static UINT16 prevlastpi=-1,lastpi=-1;

	nowPI = pi=a;
	group_type= b>>12;
	version_ab=(b>>11) & 0x01;
	tp        =(b>>10) & 0x01;
	pty       =(b>> 5) & 0x1f;

	if(prevlastpi==lastpi && lastpi!=pi) 
	{
		lastpi=pi;
		prevlastpi=lastpi;
		return;
	}

	if(pty)
	{
		_tcscpy(programTypeBuf,ptyName[pty]);
		//printf("pty %s\n",programTypeBuf);
		ptyReadyFlag = 0xff;
	}
#ifdef RDS_DBG
	//printf("type %d\n",group_type);
#endif
	switch(group_type) 
	{
	case 0:
	case 15:
		rds_process_group0(a,b,c,d);
		break;
	case 1: 
		rds_process_group1(a,b,c,d);
		break;
	case 2: 
		rds_process_group2(a,b,c,d);
		break;
	case 4: 
		rds_process_group4(a,b,c,d);
		break;
	case 10: 
		rds_process_group10(a,b,c,d);
		break;
	default:
		//printf("default\n");
		break;
	}

	lastpi=pi;
	prevlastpi=lastpi;
}

void SAA6588::rds_process_block(UINT8 id, UINT16 v)
{
	static UINT16 blocs[4];
	static UINT8 prev = -1;
#ifdef MORE_COMPATIBLE    
	static BYTE block_rdy_flag = 0;
#endif
#ifdef RDS_DBG
	//printf("id %d ",id);
#endif

	if ((id==0) || id==prev+1) 
	{
		blocs[id]=v;
		if(id==3)
			rds_process_group(blocs[0],blocs[1],blocs[2],blocs[3]);
		prev=id;
	}
	else
		prev=-1;

}

UINT16 SAA6588::rds_data_read(void)
{
	UINT8 blockid,blockid_prev;
	static UINT8 lastblockid = 0;
	CollectData();
	if((rds_data[0] & 0x03) > RDS_ERR_LEVEL) // uncorrectable block
	{
#ifdef RDS_DBG
		//printf(".");//uncrrectable\n");
#endif
		rds_process_block(-1,0);
	}
	if(rds_data[0] & 0x08) // data overflow
	{
#ifdef RDS_DBG
		//printf("o\n");
#endif
		//rds_process_block(-1,0);
	}
	blockid=rds_data[0]>>5;
	blockid_prev=rds_data[6]>>5;
	if (blockid == lastblockid)
	{
		return 0;
	}
	if (blockid != lastblockid)
	{
		lastblockid = blockid;
	}
	if(blockid==4) blockid=2; // C` block
	if(blockid_prev==4) blockid=2; // C` block

	if (blockid == 1)
	{
		UINT group_type= rds_data[1]>>3;
		WORD b = rds_data[1]<<8 | rds_data[2];
		if (group_type == 0)
		{
			ta = rds_data[2]>>4 & 0x01;
			ta_flag = 1;
		}
		bHasRDS = 1;
	}

	if( (blockid == blockid_prev+1) || ((blockid==0) && ( blockid_prev==3))) 
	{
#ifdef RDS_DBG
		//printf("-");
#endif
		bHasRDS = 1;
		rds_process_block(blockid,(rds_data[1]<<8) | rds_data[2]);
	}
	return 0;	
}

TCHAR *SAA6588::get_ptyBuf(int i)
{
	return ptyName[i];
}