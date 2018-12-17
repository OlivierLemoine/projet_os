#ifndef _IRQ_H_
#define _IRQ_H_

#include "typedefs.h"

typedef void (*Handler_t)(void);


#define IRQ_CHANNEL_WDT				0
/* channel 1 reserved */
#define VIC_CHANNEL_ARMCore_DbgRx	2
#define VIC_CHANNEL_ARMCore_DbgTx	3
#define IRQ_CHANNEL_TIMER0			4
#define IRQ_CHANNEL_TIMER1			5
#define IRQ_CHANNEL_UART0			6
#define IRQ_CHANNEL_UART1			7
#define IRQ_CHANNEL_PWM				8
#define IRQ_CHANNEL_I2C0			9
#define IRQ_CHANNEL_SPI0			10
#define IRQ_CHANNEL_SPI1			11
#define IRQ_CHANNEL_PLL				12
#define IRQ_CHANNEL_RTC				13
#define IRQ_CHANNEL_EINT0			14
#define IRQ_CHANNEL_EINT1			15
#define IRQ_CHANNEL_EINT2			16
#define IRQ_CHANNEL_EINT3			17
#define IRQ_CHANNEL_ADC0			18
#define IRQ_CHANNEL_I2C1	  		19
#define IRQ_CHANNEL_BOD		  		20
#define IRQ_CHANNEL_ADC1	  		21
#define IRQ_CHANNEL_USB		  		22
/* channels 23 to 31 reserved */

/* disable all irq channels */
void  irq_init();

/* irq/fiq enable/disable in cpsr */
void  irq_enable();
void  irq_disable();


/* irq_register_slot : register an isr, enable channel interrupt
 *
 *   channel : irq vic channel
 *   slot    : slot to be allocated to channel
 *   isr     : callback isr
 */
int   irq_register_slot(uint32 channel, uint32 slot, Handler_t isr);

/* irq_unregister_slot : unregister slot, disable irq handling
 *
 *   channel : irq vic channel
 *   slot    : slot to be deallocated
 */
int   irq_unregister_slot(uint32 channel, uint32 slot);

/* acknowledge vic interrupt priority logic */
void  irq_ack();

#endif
