/* dmd.h
 *
 * Led dot matrix display
 *
 * uses _TIMER0 and _SPI0 resources
 */
#ifndef _DMD_H_
#define _DMD_H_

#include "board.h"

#define FRAME_MODE_NONE			0
#define FRAME_MODE_REPLACE		1
#define FRAME_MODE_SCROLL		2

/* dmd_init
 *
 */
void dmd_init();

/* dmd_frame_period
 *   change the period used for updating scrolling
 */
void dmd_frame_period(uint32 period_ms);

/* dmd_put_image
 *
 */
void dmd_put_image(uint8* data);

/* dmd_put_images
 *   outputs the data byte stream to the dot matrix display
 *   data : array of bytes
 *   n    : length of the array in bytes
 *   mode : FRAME_MODE_NONE    : fixed 8 byte width picture,
 *          FRAME_MODE_REPLACE : a stream of n/8 pictures replacing each other,
 *          FRAME_MODE_SCROLL  : a stream to be scrolled byte by byte on the display.
 */
void dmd_put_images(uint8* data, uint32 n, uint32 mode);

#endif
