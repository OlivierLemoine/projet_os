//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// Provides the low-level initialization function that gets called on chip
/// startup.
///
/// !Usage
///
/// LowLevelInit() is called in board_cstartup.s.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------
/* PLL definitions */
#define PLLE_BIT        0
#define PLLC_BIT        1
#define PLOCK_BIT       10

__attribute__((interrupt("IRQ"))) void default_irq_isr()
{
	_VICVectAddr = 0;
}

#if 0
//------------------------------------------------------------------------------
/// Performs the low-level initialization of the chip. This includes master
/// clock, VIC & watchdog configuration, as well as memory remapping.
//------------------------------------------------------------------------------
void LowLevelInit( void )
{
    /* Initialize the VIC
     ********************/
    _VICIntEnClr    = 0xFFFFFFFF;
    _VICProtection  = 0;                    /* Setup interrupt controller                         */
    _VICDefVectAddr = (unsigned int)default_irq_isr;      /* Direct unvectored IRQs to reset, i.e., address 0x0 */

    _VICVectAddr0   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr1   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr2   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr3   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr4   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr5   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr6   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr7   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr8   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr9   = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr10  = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr11  = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr12  = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr13  = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr14  = (unsigned int)0;      /* Set the vector address */
    _VICVectAddr15  = (unsigned int)0;      /* Set the vector address */
    
    /* Initialize main oscillator
     ****************************/
    // --- enable and connect the PLL (Phase Locked Loop) ---
    // a. set multiplier and divider
#if (Fcco / Fcclk) == 2
    _PLL0CFG = (PLL_M - 1) | (0 << 5);
#elif (Fcco / Fcclk) == 4
    _PLL0CFG = (PLL_M - 1) | (1 << 5);
#elif (Fcco / Fcclk) == 8
    _PLL0CFG = (PLL_M - 1) | (2 << 5);
#elif (Fcco / Fcclk) == 16
    _PLL0CFG = (PLL_M - 1) | (3 << 5);
#else
	#error Bad PLL config !
#endif
    
    // b. enable PLL
    _PLL0CON = (1<<PLLE_BIT);
    // c. feed sequence
    _PLL0FEED = 0xAA;
    _PLL0FEED = 0x55;
    // d. wait for PLL lock (PLOCK bit is set if locked)
    while ( !( _PLL0STAT & (1<<PLOCK_BIT) ) );
    // e. connect (and enable) PLL
    _PLL0CON = (1<<PLLE_BIT) | (1<<PLLC_BIT);
    // f. feed sequence
    _PLL0FEED = 0xAA;
    _PLL0FEED = 0x55;
	
    /* setup and enable the MAM (Memory Accelerator Module)
     ******************************************************/
	/* MAMCR : 0=disabled, 1=partly enabled (enabled for code prefetch, but
	   not for data), 2=fully enabled */
    _MAMCR = 0;	
	/* number of CCLK to fetch from the FLASH */
#if Fcclk < 20000000
	_MAMTIM = 1;
#elif Fcclk < 40000000
	_MAMTIM = 2;
#else
	_MAMTIM = 3;
#endif
    _MAMCR = 2;

	/* APBDIV Frequency divider setup
	 ********************************/
#if (Fcclk / Fpclk) == 4
    _APBDIV = 0;
#elif (Fcclk / Fpclk) == 2
    _APBDIV = 2;
#elif (Fcclk / Fpclk) == 1
    _APBDIV = 1;
#else
	#error Bad APBDIV value !
#endif

    /* All pins as input GPIOs */
    _PINSEL0 = 0;
    _PINSEL1 = 0;

	/* Power up the USB Device to be able to use the extra 8K RAM */
	_PCONP|=0x80000000;
    /* Use Legacy GPIO access for P0 and P1 (FIO seems buggy) */
    _SCS = 0;
}
#else
void LowLevelInit( void )
{
	int i;
    /* Initialize the VIC
     ********************/
    _VIC->IntEnClr    = 0xFFFFFFFF;
    _VIC->Protection  = 0;                    /* Setup interrupt controller                         */
    _VIC->DefVectAddr = (unsigned int)0;      /* Direct unvectored IRQs to reset, i.e., address 0x0 */

    /* Set the vector addresses to NULL */
    for (i=0;i<16;i++) _VIC->VectAddrSlot[i]=(unsigned int)0;

    /* Initialize main oscillator
     ****************************/
    // --- enable and connect the PLL (Phase Locked Loop) ---
    // a. set multiplier and divider
#if (Fcco / Fcclk) == 2
    _SCB->PLL0CFG = (PLL_M - 1) | (0 << 5);
#elif (Fcco / Fcclk) == 4
    _SCB->PLL0CFG = (PLL_M - 1) | (1 << 5);
#elif (Fcco / Fcclk) == 8
    _SCB->PLL0CFG = (PLL_M - 1) | (2 << 5);
#elif (Fcco / Fcclk) == 16
    _SCB->PLL0CFG = (PLL_M - 1) | (3 << 5);
#else
	#error Bad PLL config !
#endif

    // b. enable PLL
    _SCB->PLL0CON = (1<<PLLE_BIT);
    // c. feed sequence
    _SCB->PLL0FEED = 0xAA;
    _SCB->PLL0FEED = 0x55;
    // d. wait for PLL lock (PLOCK bit is set if locked)
    while ( !( _SCB->PLL0STAT & (1<<PLOCK_BIT) ) );
    // e. connect (and enable) PLL
    _SCB->PLL0CON = (1<<PLLE_BIT) | (1<<PLLC_BIT);
    // f. feed sequence
    _SCB->PLL0FEED = 0xAA;
    _SCB->PLL0FEED = 0x55;

    /* setup and enable the MAM (Memory Accelerator Module)
     ******************************************************/
	/* MAMCR : 0=disabled, 1=partly enabled (enabled for code prefetch, but
	   not for data), 2=fully enabled */
    _SCB->MAMCR = 0;
	/* number of CCLK to fetch from the FLASH */
#if Fcclk < 20000000
    _SCB->MAMTIM = 1;
#elif Fcclk < 40000000
    _SCB->MAMTIM = 2;
#else
    _SCB->MAMTIM = 3;
#endif
    _SCB->MAMCR = 2;

	/* APBDIV Frequency divider setup
	 ********************************/
#if (Fcclk / Fpclk) == 4
    _SCB->APBDIV = 0;
#elif (Fcclk / Fpclk) == 2
    _SCB->APBDIV = 2;
#elif (Fcclk / Fpclk) == 1
    _SCB->APBDIV = 1;
#else
	#error Bad APBDIV value !
#endif

    /* All pins as input GPIOs */
    _PCB->PINSEL0 = 0;
    _PCB->PINSEL1 = 0;

	/* Power up the USB Device to be able to use the extra 8K RAM */
	_SCB->PCONP |= 0x80000000;
    /* Use Legacy GPIO access for P0 and P1 (FIO seems buggy) */
    _SCB->SCS = 0;
}
#endif

#ifdef __DEBUG__
VIC *    const _VIC 	= VIC_BASE;

PCB *    const _PCB		= PCB_BASE;
SCB *    const _SCB		= SCB_BASE;
EXT *    const _EXT		= EXT_BASE;

IO *     const _IO0 	= IO0_BASE;
IO *     const _IO1 	= IO1_BASE;
FIO *    const _FIO0	= FIO0_BASE;
FIO *    const _FIO1	= FIO1_BASE;

TIMER *  const _TIMER0	= TIMER0_BASE;
TIMER *  const _TIMER1	= TIMER1_BASE;

PWM *    const _PWM		= PWM_BASE;

UART *   const _UART0	= UART0_BASE;
UART *   const _UART1	= UART1_BASE;

I2C *    const _I2C0	= I2C0_BASE;
I2C *    const _I2C1	= I2C1_BASE;

SPI *    const _SPI0	= SPI0_BASE;

SSP *    const _SSP     = SSP_BASE;

RTC *    const _RTC		= RTC_BASE;

ADC *    const _ADC0    = AD0_BASE;
ADC *    const _ADC1    = AD1_BASE;

DAC *    const _DAC		= DAC_BASE;

WD *     const _WD		= WD_BASE;
#endif
