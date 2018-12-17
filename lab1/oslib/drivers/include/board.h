/*------------------------------------------------------------------------------
 * !Purpose
 *
 * Board level definitions
 *----------------------------------------------------------------------------*/ 

#ifndef _BOARD_H_
#define _BOARD_H_

#define __IRQ_HANDLER__
#ifndef __ASSEMBLY__
	#define __DEBUG__
	
	#include "typedefs.h"
#endif

#include "lpc214x.h"

/* 12 MHz main oscillator frequency */
#define	Fosc			12000000

/* System frequency, should be (1-32) multiples of Fosc, and should be equal or 
 * less than 60MHz. */
#define PLL_M			5
#define Fcclk			(Fosc * PLL_M)

/* CCO frequency,should be 1/2/4/8 multiples of Fcclk, ranged from 156MHz to 
 * 320MHz. */
#define PLL_P			2
#define Fcco			(2 * Fcclk * PLL_P)


/* APBDIV Frequency division factor = fcclk/fpclk */
#define	PDIV			1
#define Fpclk			(Fcclk / PDIV)


/* VIC priority level for used slots */
#define IRQ_SPI0_SLOT	1
#define IRQ_I2C0_SLOT	2
#define IRQ_EINT1_SLOT	3
#define IRQ_TIMER0_SLOT	4
#define IRQ_TIMER1_SLOT	5
#define IRQ_PWM_SLOT	6
#define IRQ_ADC0_SLOT	7
#define IRQ_ADC1_SLOT	8
#define IRQ_UART0_SLOT	9
#define IRQ_UART1_SLOT	10

/* Periphal definitions */
#ifndef __ASSEMBLY__
	#ifndef __DEBUG__
	#define _VIC	VIC_BASE
	
	#define _PCB	PCB_BASE
	#define _SCB	SCB_BASE
	#define _EXT	EXT_BASE
	
	#define _IO0 	IO0_BASE
	#define _IO1 	IO1_BASE
	#define _FIO0	FIO0_BASE
	#define _FIO1	FIO1_BASE
	
	#define _TIMER0	TIMER0_BASE
	#define _TIMER1	TIMER1_BASE
	
	#define _PWM	PWM_BASE
	
	#define _UART0	UART0_BASE
	#define _UART1	UART1_BASE
	
	#define _I2C0	I2C0_BASE
	#define _I2C1	I2C1_BASE
	
	#define _SPI0	SPI0_BASE

	#define _SSP    SSP_BASE

	#define _RTC	RTC_BASE

	#define _ADC0   AD0_BASE
	#define _ADC1	AD1_BASE
	
	#define _DAC	DAC_BASE

	#define _WD		WD_BASE

	#else
	/* Register Definitions for Debug Access */
	extern VIC *    const _VIC;
	
	extern PCB * 	const _PCB;
	extern SCB *    const _SCB;
	extern EXT *    const _EXT;

	extern IO *     const _IO0;
	extern IO *     const _IO1;
	extern FIO *    const _FIO0;
	extern FIO *    const _FIO1;
	
	extern TIMER *  const _TIMER0;
	extern TIMER *  const _TIMER1;
	
	extern PWM *    const _PWM;
		
	extern UART *   const _UART0;
	extern UART *   const _UART1;
	
	extern I2C *    const _I2C0;
	extern I2C *    const _I2C1;

	extern SPI *    const _SPI0;

	extern SSP *    const _SSP;

	extern RTC *    const _RTC;

	extern ADC *    const _ADC0;
	extern ADC *    const _ADC1;

	extern DAC *    const _DAC;

	extern WD *     const _WD;
	#endif
#endif


#endif /*_BOARD_H_ */

