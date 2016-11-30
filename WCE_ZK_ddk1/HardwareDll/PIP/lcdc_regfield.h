typedef union _LCTRL{
    unsigned int lctrl;
    struct{
        unsigned int len:1;
        unsigned int ovb:3;
        unsigned int evsel:1;
        unsigned int stn:1;
        unsigned int opt:1;
        unsigned int tv:1;
        unsigned int ni:1;
        unsigned int dp:1;
        unsigned int r2y:1;
        unsigned int clen:1;
        unsigned int ip:1;
        unsigned int ih:1;
        unsigned int iv:1;
        unsigned int id:1;
        unsigned int pxdw:4;
        unsigned int bpp:3;
        unsigned int ckg:1;
        unsigned int f656:1;
        unsigned int gen:1;
        unsigned int reserved:2;
        unsigned int r2ymd:2;
        unsigned int evs:1;
        unsigned int evp:1;
    }B;
}uLCTRL;

typedef union _LBC{
    unsigned int lbc;
    struct{
        unsigned int bg0:8;
        unsigned int bg1:8;
        unsigned int bg2:8;
        unsigned int reserved:7;
        unsigned int bgv:1;
    }B;
}uLBC;

typedef union _LCLKDIV{
    unsigned int lclkdiv;
    struct{
        unsigned int pxclkdiv:8;
        unsigned int reserved0:8;
        unsigned int acdiv:8;
        unsigned int reserved1:8;
    }B;
}uLCLKDIV;

typedef union _LHTIME1{
    unsigned int lhtime1;
    struct{
        unsigned int lpc:14;
        unsigned int reserved0:2;
        unsigned int lpw:9;
        unsigned int reserved1:7;
    }B;
}uLHTIME1;

typedef union _LHTIME2{
    unsigned int lhtime2;
    struct{
        unsigned int lewc:9;
        unsigned int reserved:7;
        unsigned int lswc:9;
        unsigned int reserved1:7;
    }B;
}uLHTIME2;

typedef union _LVTIME1{
    unsigned int lvtime1;
    struct{
        unsigned int flc:14;
        unsigned int reserved0:2;
        unsigned int fpw:6;
        unsigned int vdf:4;
        unsigned int reserved1:1;
        unsigned int vdb:5;
    }B;
}uLVTIME1;

typedef union _LVTIME2{
    unsigned int lvtime2;
    struct{
        unsigned int fewc:9;
        unsigned int reserved0:7;
        unsigned int fswc:9;
        unsigned int reserved1:7;
    }B;
}uLVTIME2;

typedef union _LVTIME3{
    unsigned int lvtime3;
    struct{
        unsigned int flc:14;
        unsigned int reserved0:2;
        unsigned int fpw:6;
        unsigned int reserved1:10;
    }B;
}uLVTIME3;

typedef union _LVTIME4{
    unsigned int lvtime4;
    struct{
        unsigned int fewc:9;
        unsigned int reserved0:7;
        unsigned int fswc:9;
        unsigned int reserved1:7;
    }B;
}uLVTIME4;

typedef union _LLUTR{
    unsigned int llutr;
    struct{
        unsigned int llutr:32;
    }B;
}uLLUTR;

typedef union _LLUTG{
    unsigned int llutg;
    struct{
        unsigned int llutg:32;
    }B;
}uLLUTG;

typedef union _LLUTB{
    unsigned int llutb;
    struct{
        unsigned int llutb:16;
        unsigned int reserved:16;
    }B;
}uLLUTB;

typedef union _LDP7L{
    unsigned int ldp7l;
    struct{
        unsigned int dp1_7:7;
        unsigned int reserved0:1;
        unsigned int dp3_7:7;
        unsigned int reserved1:1;
        unsigned int dp4_7:7;
        unsigned int reserved2:1;
        unsigned int dp5_7:7;
        unsigned int reserved3:1;
    }B;
}uLDP7L;

typedef union _LDP7H{
    unsigned int ldp7h;
    struct{
        unsigned int dp6_7:7;
        unsigned int reserved:25;
    }B;
}uLDP7H;

typedef union _LDP5{
    unsigned int ldp5;
    struct{
        unsigned int dp1_5:6;
        unsigned int reserved0:2;
        unsigned int dp2_5:6;
        unsigned int reserved1:2;
        unsigned int dp3_5:6;
        unsigned int reserved2:2;
        unsigned int dp4_7:6;
        unsigned int reserved3:2;
    }B;
}uLDP5;

typedef union _LDP4{
    unsigned int ldp4;
    struct{
        unsigned int dp1_4:4;
        unsigned int dp2_4:4;
        unsigned int dp3_4:4;
        unsigned int reserved:20;
    }B;
}uLDP4;

typedef union _LDP3
{
    unsigned int ldp3;
    struct{
        unsigned int dp1_3:3;
        unsigned int reserved0:1;
        unsigned int dp2_3:3;
        unsigned int reserved1:25;
    }B;
}uLDP3;

typedef union _LCP1{
    unsigned int lcp1;
    struct{
        unsigned int clp1:8;
        unsigned int reserved0:8;
        unsigned int clp2:8;
        unsigned int reserved1:8;
    }B;
}uLCP1;

typedef union _LCP2{
    unsigned int lcp2;
    struct{
        unsigned int clp2:8;
        unsigned int reserved0:8;
        unsigned int clp2l:8;
        unsigned int reserved1:8;
    }B;
}uLCP2;

typedef union _LDS{
    unsigned int lds;
    struct{
        unsigned int hsize:13;
        unsigned int reserved0:3;
        unsigned int vsize:13;
        unsigned int reserved1:3;
    }B;
}uLDS;

typedef union _LSTATUS{
    unsigned int lstatus;
    struct{
        unsigned int status:16;
        unsigned int resreved:9;
        unsigned int i2eof:1;
        unsigned int i1eof:1;
        unsigned int i0eof:1;
        unsigned int deof:1;
        unsigned int ef:1;
        unsigned int busy:1;
        unsigned int vs:1;
    }B;
}uLSTATUS;

typedef union _LIM{
    unsigned int lim;
    struct{
        unsigned int fu:1;
        unsigned int vsr:1;
        unsigned int vsf:1;
        unsigned int ru:1;
        unsigned int dd:1;
        unsigned int der:1;
        unsigned int def:1;
        unsigned int iE0R:1;
        unsigned int iE0F:1;
        unsigned int iE1R:1;
        unsigned int iE1F:1;
        unsigned int iE2R:1;
        unsigned int iE2F:1;
        unsigned int reserved:19;
    }B;
}uLIM;

typedef union _LGR0{
    unsigned int lgr0;
    struct{
        unsigned int gr0:4;
        unsigned int gr1:4;
        unsigned int gr2:4;
        unsigned int gr3:4;
        unsigned int gr4:4;
        unsigned int gr5:4;
        unsigned int gr6:4;
        unsigned int gr7:4;
    }B;
}uLGR0;

typedef union _LGR1{
    unsigned int lgr1;
    struct{
        unsigned int gr8:4;
        unsigned int gr9:4;
        unsigned int gr10:4;
        unsigned int gr11:4;
        unsigned int gr12:4;
        unsigned int gr13:4;
        unsigned int gr14:4;
        unsigned int gr15:4;
    }B;
}uLGR1;

typedef union _LGG0{
    unsigned int lgg0;
    struct{
        unsigned int gg0:4;
        unsigned int gg1:4;
        unsigned int gg2:4;
        unsigned int gg3:4;
        unsigned int gg4:4;
        unsigned int gg5:4;
        unsigned int gg6:4;
        unsigned int gg7:4;
    }B;
}uLGG0;

typedef union _LGG1{
    unsigned int lgg1;
    struct{
        unsigned int gg8:4;
        unsigned int gg9:4;
        unsigned int gg10:4;
        unsigned int gg11:4;
        unsigned int gg12:4;
        unsigned int gg13:4;
        unsigned int gg14:4;
        unsigned int gg15:4;
    }B;
}uLGG1;

typedef union _LGB0{
    unsigned int lgb0;
    struct{
        unsigned int gb0:4;
        unsigned int gb1:4;
        unsigned int gb2:4;
        unsigned int gb3:4;
        unsigned int gb4:4;
        unsigned int gb5:4;
        unsigned int gb6:4;
        unsigned int gb7:4;
    }B;
}uLGB0;

typedef union _LGB1{
    unsigned int lgb1;
    struct{
        unsigned int gb8:4;
        unsigned int gb9:4;
        unsigned int gb10:4;
        unsigned int gb11:4;
        unsigned int gb12:4;
        unsigned int gb13:4;
        unsigned int gb14:4;
        unsigned int gb15:4;
    }B;
}uLGB1;

typedef union _LENH{
    unsigned int lenh;
    struct{
        unsigned int contrast:8;
        unsigned int brightness:8;
        unsigned int hue:8;
        unsigned int reserved:8;
    }B;
}uLENH;

typedef union _LIC{
    unsigned int lic;
    struct{
        unsigned int fmt:5;
        unsigned int reserved0:2;
        unsigned int br:1;
        unsigned int y2r:1;
        unsigned int y2rmd:2;
        unsigned int reserved1:4;
        unsigned int pd:1;
        unsigned int reserved2:8;
        unsigned int asel:1;
        unsigned int aopt:2;
        unsigned int src:1;
        unsigned int ien:1;
        unsigned int cen:1;
        unsigned int aen:1;
        unsigned int intl:1;        
    }B;
}uLIC;

typedef union _LIP{
    unsigned int lip;
    struct{
        unsigned int posx:13;
        unsigned int reserved0:3;
        unsigned int posy:13;
        unsigned int reserved1:3;
    }B;
}uLIP;

typedef union _LIS{
    unsigned int lis;
    struct{
        unsigned int width:13;
        unsigned int reserved0:3;
        unsigned int height:13;
        unsigned int reserved1:3;
    }B;
}uLIS;

typedef union _LIBA{
    unsigned int liba;
    struct{
        unsigned int liba:32;
    }B;
}uLIBA;

typedef union _LICA{
    unsigned int curr;
    struct{
        unsigned int curr:32;
    }B;
}uLICA;

typedef union _LIBA1{
    unsigned int liba1;
    struct{
        unsigned int liba1:32;
    }B;
}uLIBA1;

typedef union _LIBA2{
    unsigned int liba2;
    struct{
        unsigned int liba2:32;
    }B;
}uLIBA2;

typedef union _LIO{
    unsigned int lio;
    struct{
        unsigned int offset0:16;
        unsigned int offset1:16;
    }B;
}uLIO;

typedef union _LISC{
    unsigned int lisc;
    struct{
        unsigned int xscale:4;
        unsigned int yscale:4;
        unsigned int reserved:24;
    }B;
}uLISC;


typedef union _LIA{
    unsigned int lia;
    struct{
        unsigned int a0:8;
        unsigned int reserved0:8;
        unsigned int a1:8;
        unsigned int reserved1:8;
    }B;
}uLIA;

typedef union _LIKR{
    unsigned int likr;
    struct{
        unsigned int key:8;
        unsigned int reserved0:8;
        unsigned int keymask:8;
        unsigned int reserved1:8;
    }B;
}uLIKR;

typedef union _LIKG{
    unsigned int likg;
    struct{
        unsigned int key:8;
        unsigned int reserved0:8;
        unsigned int keymask:8;
        unsigned int reserved1:8;
    }B;
}uLIKG;

typedef union _LIKB{
    unsigned int likb;
    struct{
        unsigned int key:8;
        unsigned int reserved0:8;
        unsigned int keymask:8;
        unsigned int reserved1:8;
    }B;
}uLIKB;

typedef union _LIEN{
    unsigned int lien;
    struct{
        unsigned int contrast:8;
        unsigned int brightness:8;
        unsigned int hue:8;
        unsigned int reserved:8;
    }B;
}uLIEN;

typedef union _LUTIDX{
    unsigned int lutidx;
    struct{
        unsigned int chsel:2;
        unsigned int reserved0:2;
        unsigned int en0:1;
        unsigned int en1:1;
        unsigned int en2:1;
        unsigned int reserved1:27;
    }B;
}uLUTIDX;

typedef struct _LCDCIMG{
    uLIC    LIC;
    uLIP    LIP;
    uLIS    LIS;
    uLIBA   LIBA;
    uLICA   LICA;
    uLIBA1  LIBA1;
    uLIBA2  LIBA2;
    uLIO    LIO;
    uLISC   LISC;
    uLIA    LIA;
    uLIKR   LIKR;
    uLIKG   LIKG;
    uLIKB   LIKB;
    uLIEN   LIEN;
}stLCDCIMG;


typedef struct __LCDC{
    volatile uLCTRL     LCTRL;
    volatile uLBC       LBC;
    volatile uLCLKDIV   LCLKDIV;
    volatile uLHTIME1   LHTIME1;
    volatile uLHTIME2   LHTIME2;
    volatile uLVTIME1   LVTIME1;
    volatile uLVTIME2   LVTIME2;
    volatile uLVTIME3   LVTIME3;
    volatile uLVTIME4   LVTIME4;
    volatile uLLUTR     LLUTR;
    volatile uLLUTG     LLUTG;
    volatile uLLUTB     LLUTB;
    volatile uLDP7L     LDP7L;
    volatile uLDP7H     LDP7H;
    volatile uLDP5      LDP5;
    volatile uLDP4      LDP4;
    volatile uLDP3      LDP3;
    volatile uLCP1      LCP1;
    volatile uLCP2      LCP2;
    volatile uLDS       LDS;
    volatile uLSTATUS   LSTATUS;
    volatile uLIM       LIM;
    volatile uLGR0      LGR0;
    volatile uLGR1      LGR1;
    volatile uLGG0      LGG0;
    volatile uLGG1      LGG1;
    volatile uLGB0      LGB0;
    volatile uLGB1      LGB1;
    volatile uLENH      LENH;
    volatile int        NotUsed;
    volatile stLCDCIMG  LCDCIMG[3];
    volatile int        LCDLUT;
}stLCDC, *pstLCDC;


typedef struct {
    unsigned int ID;
    pstLCDC      PCTRL;
}stLCDCOND,*PLCDCOND;

typedef struct {
    unsigned int     CtrlId;
    unsigned int     ImgCh;
    unsigned int     Size;
    void            *pParam;
}DRIVERPARAM,*PDRIVERPARAM;

typedef union {
    unsigned int chromaval;
    struct{
        unsigned int bv:8;
        unsigned int gu:8;
        unsigned int ry:8;
        unsigned int reserved:8;
    }B;
}uCROMAKEY;

typedef struct {
    unsigned int ImgSizeWidth;
    unsigned int ImgSizeHeight;
    unsigned int ImgFormat;
    unsigned int BaseAddress;
    unsigned int Function;
    unsigned int Interlaced;
    unsigned int AlphaValue;
    unsigned int Hue;
    unsigned int Bright;
    unsigned int Contrast;
    uCROMAKEY    ChromaKey;
}IMGCFGPARAM, *PIMGCFGPARAM;

typedef struct{
    unsigned int Function;    
    unsigned int DispWidth;
    unsigned int DispHeight;
    unsigned int LayerOrder;
    unsigned int PXDataWidth;
    unsigned int Interlaced;
}CTRCFGPARAM, *PCTRCFGPARAM;


typedef struct{
    PCTRCFGPARAM pCtrParam;
    PIMGCFGPARAM pImgParam;
}DISPMODEPARAM, *PDISPMODEPARAM;

// FOR Controller

// FOR Channel


static CTRCFGPARAM CtrCfgInfo[4] = 
{
//   Fn   Wth,  Hgt, Layer, PXDW, Intl
    { 0,  800,  480,     5,   12,   0 },
    { 1, 1024,  768,     5,   12,   0 },
    { 2, 1280,  720,     5,   12,   0 },
    { 3,  720,  480,     5,   12,   1 },
};


static IMGCFGPARAM   ImgCHCfgInfo[4] = 
{
    //ImgW, ImgH, Fmt,         BA, Fn, Chr, Alp, Hue, Bri, Cntr, Intl
    {  800,  480,   10, 0x49000000, 1,    0,  95,   0,   0, 0x20,   0 }, // RGB_LCD
    { 1024,  768,   10, 0x49177000, 1,    0,  95,   0,   0, 0x20,   0 }, // LVDS
    { 1280,  720,   10, 0x49000000, 1,    0,  95,   0,   0, 0x20,   0 }, // HDMI
    {  720,  480,   10, 0x49000000, 1,    0,  95,   0,   0, 0x20,   1 }, // TVOUT
};


typedef struct{
    struct{
        unsigned int Controller;
        unsigned int ImgChannel[4];
    }CTRL[2];
    unsigned int CurUICtrl;
    unsigned int CurUIChnl;
    unsigned int CurFunc;
}stDISPMODE, *PDISPMODE;