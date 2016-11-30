#ifndef PARAM_DONE
#define PARAM_DONE

/* This is the general definition for the size and width of the
   JPEG blocks. Do not change.
   */
#define BLOCKSIZE 64
#define BLOCKWIDTH 8
#define BLOCKHEIGHT 8

/* Definitions for JPEG and internal compatibility. */

#define MAXIMUM_HORIZONTAL_FREQUENCY 15
#define MAXIMUM_VERTICAL_FREQUENCY 15

#define MAXIMUM_JPEG_HORIZONTAL_FREQUENCY 4
#define MAXIMUM_JPEG_VERTICAL_FREQUENCY 4

#define MINIMUM_BUFFERSIZE 16

#define MAXIMUM_UNSIGNED16 65535
#define MAXIMUM_RESYNC_INTERVAL 65535
#define MAXIMUM_BUFFERSIZE 65535
#define MAXIMUM_IMAGE_HEIGHT 65535
#define MAXIMUM_IMAGE_WIDTH 65535

/* Devices: Number of active devices operating at one time.
   Quantization tables, huffman tables, etc. are all devices.
   */
#define MAXIMUM_DEVICES 4

/* Sources: Number of active sources in stream at one time.
   A source is one interleave possibility.
   */
#define MAXIMUM_SOURCES 4

/* Components: Number of components that can be active per frame.
   A component consists of one complete plane of the image.
*/
#define MAXIMUM_COMPONENTS 4

/* Q value as defined by archaic and now defunct F-Factor:
   Used to rescale quantization matrices.
 */

#define Q_PRECISION 50

/* Scan component threshold is the maximum number of components put
in per scan */

#define SCAN_COMPONENT_THRESHOLD 4  

/* Number of streams is the number of active read/write streams possible.
   For all jpeg operations, this value is 1.*/

#define NUMBER_OF_STREAMS 1

#endif

