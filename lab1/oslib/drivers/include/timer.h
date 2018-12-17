#ifndef _TIMER_H_
#define _TIMER_H_

#include "board.h"

typedef void (*OnTick)(void);

/* timer_wait_ms
 *   wait for ms millisecoonds function
 */
void timer_wait_ms(TIMER *tmr, uint32 ms);

/* timer_wait_us
 *   wait for us microsecoonds function
 */
void timer_wait_us(TIMER *tmr, uint32 us);

/* timer_tick_init
 *   setup timer to call cb function periodically, each tick_ms
 */
int timer_tick_init(TIMER *tmr, uint32 tick_ms, OnTick cb);

/* timer_oneshot_init
 *   timer configured to generate one shot wait time
 */
int timer_oneshot_init(TIMER *tmr, uint32 ms, OnTick cb);

/* timer_start
 *   start counting to generate ticks
 */
void timer_start(TIMER *tmr);

/* timer_stop
 *   stop and reset counting
 */
void timer_stop(TIMER *tmr);

#endif
