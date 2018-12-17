/* io.h
 *
 * IO Configure and GPIO read/write ops
 *
 * UM10139.pdf p. 50-63
 */
 
#ifndef _IO_H_
#define _IO_H_

#include "board.h"


#define IO_PORT0			0
#define IO_PORT1			1

#define IO_PIN_INPUT		0
#define IO_PIN_OUTPUT		4
#define IO_PIN_FUNC1		1
#define IO_PIN_FUNC2		2
#define IO_PIN_FUNC3		3

#define IO_PIN_0			(1)
#define IO_PIN_1			(1<<1)
#define IO_PIN_2			(1<<2)
#define IO_PIN_3			(1<<3)
#define IO_PIN_4			(1<<4)
#define IO_PIN_5			(1<<5)
#define IO_PIN_6			(1<<6)
#define IO_PIN_7			(1<<7)
#define IO_PIN_8			(1<<8)
#define IO_PIN_9			(1<<9)
#define IO_PIN_10			(1<<10)
#define IO_PIN_11			(1<<11)
#define IO_PIN_12			(1<<12)
#define IO_PIN_13			(1<<13)
#define IO_PIN_14			(1<<14)
#define IO_PIN_15			(1<<15)
#define IO_PIN_16			(1<<16)
#define IO_PIN_17			(1<<17)
#define IO_PIN_18			(1<<18)
#define IO_PIN_19			(1<<19)
#define IO_PIN_20			(1<<20)
#define IO_PIN_21			(1<<21)
#define IO_PIN_22			(1<<22)
#define IO_PIN_23			(1<<23)
#define IO_PIN_24			(1<<24)
#define IO_PIN_25			(1<<25)
#define IO_PIN_26			(1<<26)
#define IO_PIN_27			(1<<27)
#define IO_PIN_28			(1<<28)
#define IO_PIN_29			(1<<29)
#define IO_PIN_30			(1<<30)
#define IO_PIN_31			(1<<31)

/* io_configure
 * configure pins referenced in pinmask of specified port according to 'func'
 *
 * returns 1 if success and 0 else
 */
int io_configure(uint32 port, uint32 pin_mask, uint32 func);

/* io_read
 *
 * read 32 bit data from port 'p', filter the result with mask
 */
uint32 io_read(IO *p, uint32 mask);

/* io_write
 *
 * write 32 bit data filtered by mask to port 'p'
 * '1' in val are written as HIGH level on port pins
 */
void io_write(IO *p, uint32 val, uint32 mask);

/* io_write_n
 *
 * write 32 bit data filtered by mask to port 'p'
 * '1' in val are written as LOW level on port pins
 */
void io_write_n(IO *p, uint32 val, uint32 mask);


void leds_and_btns_init();
void leds(uint8 val);
uint32 buttons();

int button0();
int button1();
int button2();
int button3();
int button4();

#endif
