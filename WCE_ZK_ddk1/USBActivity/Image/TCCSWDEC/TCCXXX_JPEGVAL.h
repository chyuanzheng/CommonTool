#ifndef GLOBAL_DONE
#define GLOBAL_DONE


#include "TCCXXX_JPEGPARAM.h"

#define hinyb(val) ((val>>4)&0x0f)
#define lonyb(val) (val & 0x0f)

/* A flag obtaining macro */
#define GetFlag(value,flag) (((value) & (flag)) ? 1:0)

/* MAX and MIN macros */
#define MAX(x,y) ((x > y) ? x:y)
#define MIN(x,y) ((x > y) ? y:x)

/* Error flags */

#define ERROR_NONE 0
#define ERROR_BOUNDS -1            /*Input Values out of bounds */
#define ERROR_HUFFMAN_READ -2      /*Huffman Decoder finds bad code */
#define ERROR_MARKER -4            /*Error Found in Marker */
#define ERROR_READ -10             /*Cannot write input */
#define ERROR_NOT_SUPPORT_INPUT -14 /*Not Supportable Input Format*/

#ifndef __TCC89XX_WINCE__
#define ERROR_HUFFMAN_ENCODE -3    /*Undefined value in encoder */
#define ERROR_INIT_FILE -5         /*Cannot initialize files */
#define ERROR_UNRECOVERABLE -6     /*No recovery mode specified */
#define ERROR_PREMATURE_EOF -7     /*End of file unexpected */
#define ERROR_MARKER_STRUCTURE -8  /*Bad Marker Structure */
#define ERROR_WRITE -9             /*Cannot write output */
#define ERROR_PARAMETER -11        /*System Parameter Error */
#define ERROR_MEMORY -12           /*Memory exceeded */
#define ERROR_LOSSLESS_MODE   -13/*Not Supportablly Encoded*/
#endif

#endif
