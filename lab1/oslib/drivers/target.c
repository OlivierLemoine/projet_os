#include <stdlib.h>
#include <board.h>
#include <io.h>
#include <irq.h>
#include <uart.h>
#include <eint.h>
#include <timer.h>
#include <i2c.h>
#include <alloc.h>
#include "target.h"

/*****************************************************************************
 * external symbols
 *****************************************************************************/
void sys_round_robin(); /* kernel/kernel.c */
void sys_wait();

/*****************************************************************************
 * EINT1 External Interrupt Button device driver
 *****************************************************************************/
/*
 *  ISR callback
 */
static void on_button_cb()
{
    sys_round_robin();
}

/*****************************************************************************
 * System timer interrupt callback
 *****************************************************************************/
static void on_timeout_cb()
{
    sys_wait();
    sys_round_robin();
}

/*****************************************************************************
 * RS232 device driver
 *****************************************************************************/
static void on_receive_cb()
{
}

/*****************************************************************************
 * Target Init
 *****************************************************************************/

void dev_init()
{
    // P0.8:15 -> output (leds)
    io_configure(IO_PORT0, 0x0000FF00, IO_PIN_OUTPUT);
    // P0.16:20 -> input (push button)
    io_configure(IO_PORT0, 0x001F0000, IO_PIN_INPUT);

    eint1_init(EXT_EDGE_SENSITIVE, EXT_RISING, on_button_cb);
    timer_tick_init(_TIMER0, SYS_TICK, on_timeout_cb);
    uart_init(_UART0, 115200, UART_8N1, on_receive_cb);
    minit();
}
