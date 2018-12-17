#ifndef __UART_H__
#define __UART_H__

#include "board.h"

typedef void (*OnUartRx)();


// Definitions for typical UART 'mode' settings
#define UART_CHAR_5       (0x00)
#define UART_CHAR_6       (0x01)
#define UART_CHAR_7       (0x02)
#define UART_CHAR_8       (0x03)

#define UART_STOP_1       (0x00)
#define UART_STOP_2       (0x04)

#define UART_PAR_NO       (0x00)
#define UART_PAR_ODD      (0x08)
#define UART_PAR_EVEN     (0x18)
#define UART_PAR_1        (0x28)
#define UART_PAR_0        (0x38)

#define UART_8N1          (UART_CHAR_8 + UART_PAR_NO   + UART_STOP_1)
#define UART_7N1          (UART_CHAR_7 + UART_PAR_NO   + UART_STOP_1)
#define UART_8N2          (UART_CHAR_8 + UART_PAR_NO   + UART_STOP_2)
#define UART_7N2          (UART_CHAR_7 + UART_PAR_NO   + UART_STOP_2)
#define UART_8E1          (UART_CHAR_8 + UART_PAR_EVEN + UART_STOP_1)
#define UART_7E1          (UART_CHAR_7 + UART_PAR_EVEN + UART_STOP_1)
#define UART_8E2          (UART_CHAR_8 + UART_PAR_EVEN + UART_STOP_2)
#define UART_7E2          (UART_CHAR_7 + UART_PAR_EVEN + UART_STOP_2)
#define UART_8O1          (UART_CHAR_8 + UART_PAR_ODD  + UART_STOP_1)
#define UART_7O1          (UART_CHAR_7 + UART_PAR_ODD  + UART_STOP_1)
#define UART_8O2          (UART_CHAR_8 + UART_PAR_ODD  + UART_STOP_2)
#define UART_7O2          (UART_CHAR_7 + UART_PAR_ODD  + UART_STOP_2)

/*
 * uart_init : initialize with baud, line mode parameters,
 *             polling Tx and IRQ Rx
 */
int uart_init(UART *u, uint32 baud, uint8 mode, OnUartRx cb);

/*
 * uart_getc : get a char from the serial link (polling)
 */
char uart_getc(UART *u);

/*
 * uart_getchar : check if a char has been received from the serial link
 * (non-blocking)
 */
int uart_getchar(UART *u, char *pChar);

/*
 * uart_putc : send a char over the serial link (polling)
 */
void uart_putc(UART *u, char c);

/*
 * uart_puts : send a string over the serial link (polling)
 */
void uart_puts(UART *u, char *s);

/*
 * uart_printf : print formatted text to serial link
 */
void uart_printf(UART *u, const char* fmt, ...);

#endif
