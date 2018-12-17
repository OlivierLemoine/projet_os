#ifndef _TARGET_H_
#define _TARGET_H_

#include "timer.h"

#define SYS_TICK  10     // system tick in ms

void dev_init();

/* start timer
 */
#define sys_timer_start() timer_start(_TIMER0)

/* stop and reset timer
 */
#define sys_timer_stop()  timer_stop(_TIMER0)

#endif
