/***********************************************************************/
/*                                                                     */
/*  LPC214X.H:  Header file for Philips LPC2141/42/44/46/48            */
/*                                                                     */
/***********************************************************************/

#ifndef __LPC214x_H
#define __LPC214x_H


#ifndef __ASSEMBLY__
#define __REG_CAST_8(a) 		(*((volatile unsigned char *)(a)))
#define __REG_CAST_16(a) 		(*((volatile unsigned short *)(a)))
#define __REG_CAST_32(a) 		(*((volatile unsigned long *)(a)))
#define __STRUCT_CAST(type, a) 	((type *)(a))
#else
#define __REG_CAST_8(a) 		(a)
#define __REG_CAST_16(a) 		(a)
#define __REG_CAST_32(a) 		(a)
#define __STRUCT_CAST(type, a) 	(a)
#endif

/***************************************************************************
 * Vectored Interrupt Controller (VIC)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	IRQStatus;				/* IRQ Status Register */
	unsigned long	FIQStatus;				/* FIQ Status Register */
	unsigned long	RawIntr;				/* Raw Interrupt Status Register */
	unsigned long	IntSelect;				/* Interrupt Select Register */
	unsigned long	IntEnable;				/* Interrupt Enable Register */
	unsigned long	IntEnClr;				/* Interrupt Enable Clear Register */
	unsigned long	SoftInt;				/* Software Interrupt Register */
	unsigned long	SoftIntClr;				/* Software Interrupt Clear Register */
	unsigned long	Protection;				/* Protection Enable Register */
	unsigned long	Reserved1[3];
	unsigned long	VectAddr;				/* Vector Address Register */
	unsigned long	DefVectAddr;			/* Default Vector Address Register */
	unsigned long	Reserved2[50];
	unsigned long	VectAddrSlot[16];		/* Vector Address Slot[i] i=0 (priority++) - 15 (priority --) */
	unsigned long	Reserved3[48];
	unsigned long	VectCntlSlot[16];		/* Vector Control Slot[i] i=0-15 */
} VIC;
#endif

#define VIC_BASE_ADDR	0xFFFFF000
#define VIC_BASE		(__STRUCT_CAST(VIC,VIC_BASE_ADDR))

#define _VICIRQStatus    (__REG_CAST_32( 0xFFFFF000 ))
#define _VICFIQStatus    (__REG_CAST_32( 0xFFFFF004 ))
#define _VICRawIntr      (__REG_CAST_32( 0xFFFFF008 ))
#define _VICIntSelect    (__REG_CAST_32( 0xFFFFF00C ))
#define _VICIntEnable    (__REG_CAST_32( 0xFFFFF010 ))
#define _VICIntEnClr     (__REG_CAST_32( 0xFFFFF014 ))
#define _VICSoftInt      (__REG_CAST_32( 0xFFFFF018 ))
#define _VICSoftIntClr   (__REG_CAST_32( 0xFFFFF01C ))
#define _VICProtection   (__REG_CAST_32( 0xFFFFF020 ))
#define _VICVectAddr     (__REG_CAST_32( 0xFFFFF030 ))
#define _VICDefVectAddr  (__REG_CAST_32( 0xFFFFF034 ))
#define _VICVectAddr0    (__REG_CAST_32( 0xFFFFF100 ))
#define _VICVectAddr1    (__REG_CAST_32( 0xFFFFF104 ))
#define _VICVectAddr2    (__REG_CAST_32( 0xFFFFF108 ))
#define _VICVectAddr3    (__REG_CAST_32( 0xFFFFF10C ))
#define _VICVectAddr4    (__REG_CAST_32( 0xFFFFF110 ))
#define _VICVectAddr5    (__REG_CAST_32( 0xFFFFF114 ))
#define _VICVectAddr6    (__REG_CAST_32( 0xFFFFF118 ))
#define _VICVectAddr7    (__REG_CAST_32( 0xFFFFF11C ))
#define _VICVectAddr8    (__REG_CAST_32( 0xFFFFF120 ))
#define _VICVectAddr9    (__REG_CAST_32( 0xFFFFF124 ))
#define _VICVectAddr10   (__REG_CAST_32( 0xFFFFF128 ))
#define _VICVectAddr11   (__REG_CAST_32( 0xFFFFF12C ))
#define _VICVectAddr12   (__REG_CAST_32( 0xFFFFF130 ))
#define _VICVectAddr13   (__REG_CAST_32( 0xFFFFF134 ))
#define _VICVectAddr14   (__REG_CAST_32( 0xFFFFF138 ))
#define _VICVectAddr15   (__REG_CAST_32( 0xFFFFF13C ))
#define _VICVectCntl0    (__REG_CAST_32( 0xFFFFF200 ))
#define _VICVectCntl1    (__REG_CAST_32( 0xFFFFF204 ))
#define _VICVectCntl2    (__REG_CAST_32( 0xFFFFF208 ))
#define _VICVectCntl3    (__REG_CAST_32( 0xFFFFF20C ))
#define _VICVectCntl4    (__REG_CAST_32( 0xFFFFF210 ))
#define _VICVectCntl5    (__REG_CAST_32( 0xFFFFF214 ))
#define _VICVectCntl6    (__REG_CAST_32( 0xFFFFF218 ))
#define _VICVectCntl7    (__REG_CAST_32( 0xFFFFF21C ))
#define _VICVectCntl8    (__REG_CAST_32( 0xFFFFF220 ))
#define _VICVectCntl9    (__REG_CAST_32( 0xFFFFF224 ))
#define _VICVectCntl10   (__REG_CAST_32( 0xFFFFF228 ))
#define _VICVectCntl11   (__REG_CAST_32( 0xFFFFF22C ))
#define _VICVectCntl12   (__REG_CAST_32( 0xFFFFF230 ))
#define _VICVectCntl13   (__REG_CAST_32( 0xFFFFF234 ))
#define _VICVectCntl14   (__REG_CAST_32( 0xFFFFF238 ))
#define _VICVectCntl15   (__REG_CAST_32( 0xFFFFF23C ))


/***************************************************************************
 * Pin Connect Block
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	PINSEL0;
	unsigned long	PINSEL1;
	unsigned long	Reserved[3];
	unsigned long	PINSEL2;
} PCB;
#endif

#define PCB_BASE_ADDR	0xE002C000
#define PCB_BASE		(__STRUCT_CAST(PCB,PCB_BASE_ADDR))

#define _PINSEL0         (__REG_CAST_32( 0xE002C000 ))
#define _PINSEL1         (__REG_CAST_32( 0xE002C004 ))
#define _PINSEL2         (__REG_CAST_32( 0xE002C014 ))

/***************************************************************************
 * General Purpose Input/Output (GPIO)
 ***************************************************************************/
/* Legacy I/O */
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	PIN;
	unsigned long	SET;
	unsigned long	DIR;
	unsigned long	CLR;
} IO;
#endif

#define IO_PIN			0
#define IO_SET			4
#define IO_DIR			8
#define IO_CLR			12

/* Port 0 */
#define IO0_BASE_ADDR	0xE0028000
#define IO0_BASE		(__STRUCT_CAST(IO,IO0_BASE_ADDR))

#define _IOPIN0          (__REG_CAST_32( 0xE0028000 ))
#define _IOSET0          (__REG_CAST_32( 0xE0028004 ))
#define _IODIR0          (__REG_CAST_32( 0xE0028008 ))
#define _IOCLR0          (__REG_CAST_32( 0xE002800C ))

#define _IO0PIN          (__REG_CAST_32( 0xE0028000 ))
#define _IO0SET          (__REG_CAST_32( 0xE0028004 ))
#define _IO0DIR          (__REG_CAST_32( 0xE0028008 ))
#define _IO0CLR          (__REG_CAST_32( 0xE002800C ))

/* Port 1 */
#define IO1_BASE_ADDR	0xE0028010
#define IO1_BASE		(__STRUCT_CAST(IO,IO1_BASE_ADDR))

#define _IOPIN1          (__REG_CAST_32( 0xE0028010 ))
#define _IOSET1          (__REG_CAST_32( 0xE0028014 ))
#define _IODIR1          (__REG_CAST_32( 0xE0028018 ))
#define _IOCLR1          (__REG_CAST_32( 0xE002801C ))

#define _IO1PIN          (__REG_CAST_32( 0xE0028010 ))
#define _IO1SET          (__REG_CAST_32( 0xE0028014 ))
#define _IO1DIR          (__REG_CAST_32( 0xE0028018 ))
#define _IO1CLR          (__REG_CAST_32( 0xE002801C ))

/* Fast I/O */
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	DIR;
	unsigned long	Reserved[3];
	unsigned long	MASK;
	unsigned long	PIN;
	unsigned long	SET;
	unsigned long	CLR;
} FIO;
#endif

/* Port 0 */
#define FIO0_BASE_ADDR	0x3FFFC000
#define FIO0_BASE		(__STRUCT_CAST(FIO,FIO0_BASE_ADDR))

#define _FIO0DIR        (__REG_CAST_32( 0x3FFFC000 ))
#define _FIO0MASK       (__REG_CAST_32( 0x3FFFC010 ))
#define _FIO0PIN        (__REG_CAST_32( 0x3FFFC014 ))
#define _FIO0SET        (__REG_CAST_32( 0x3FFFC018 ))
#define _FIO0CLR        (__REG_CAST_32( 0x3FFFC01C ))

/* Port 1 */
#define FIO1_BASE_ADDR	0x3FFFC020
#define FIO1_BASE		(__STRUCT_CAST(FIO,FIO1_BASE_ADDR))

#define _FIO1DIR        (__REG_CAST_32( 0x3FFFC020 ))
#define _FIO1MASK       (__REG_CAST_32( 0x3FFFC030 ))
#define _FIO1PIN        (__REG_CAST_32( 0x3FFFC034 ))
#define _FIO1SET        (__REG_CAST_32( 0x3FFFC038 ))
#define _FIO1CLR        (__REG_CAST_32( 0x3FFFC03C ))

/***************************************************************************
 * System Control Block (SCB)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned char	MAMCR;					/* Memory Accelerator Module (MAM) */
	unsigned char	Reserved1[3];
	unsigned char	MAMTIM;
	unsigned char	Reserved2[59];
	unsigned char	MEMMAP;					/* Memory Mapping */
	unsigned char	Reserved3[63];
	unsigned char	PLL0CON;				/* Phase Locked Loop 0 (PLL0) */
	unsigned char	Reserved4[3];
	unsigned char	PLL0CFG;
	unsigned char	Reserved5[3];
	unsigned short	PLL0STAT;
	unsigned short	Reserved6;
	unsigned char	PLL0FEED;
	unsigned char	Reserved7[19];
	unsigned char	PLL1CON;				/* Phase Locked Loop 1 (PLL1) */
	unsigned char	Reserved8[3];
	unsigned char	PLL1CFG;
	unsigned char	Reserved9[3];
	unsigned short	PLL1STAT;
	unsigned short	Reserved10;
	unsigned char	PLL1FEED;
	unsigned char	Reserved11[19];
	unsigned char	PCON;					/* Power Control */
	unsigned char	Reserved12[3];
	unsigned long	PCONP;
	unsigned long   Reserved13[14];
	unsigned char	APBDIV;					/* APB Divider */
	unsigned char	Reserved14[63];
	unsigned char	EXTINT;					/* External Interrupts */
	unsigned char	Reserved15[3];
	unsigned short	INTWAKE;
	unsigned short	Reserved16;
	unsigned char	EXTMODE;
	unsigned char	Reserved17[3];
	unsigned char	EXTPOLAR;
	unsigned char	Reserved18[51];
	unsigned char	RSIR;					/* Reset */
	unsigned char	Reserved19[3];
	unsigned char	CSPR;					/* Code Security / Debugging */
	unsigned char	Reserved20[27];
	unsigned long	SCS;					/* System Control Miscellaneous */
} SCB;

typedef volatile struct {
	unsigned char	INT;					/* External Interrupts */
	unsigned char	Reserved1[3];
	unsigned short	INTWAKE;
	unsigned short	Reserved2;
	unsigned char	MODE;
	unsigned char	Reserved3[3];
	unsigned char	POLAR;
	unsigned char	Reserved4[3];
} EXT;
#endif

#define SCB_BASE_ADDR	0xE01FC000
#define EXT_BASE_ADDR	0xE01FC140
#define SCB_BASE		(__STRUCT_CAST(SCB,SCB_BASE_ADDR))
#define EXT_BASE		(__STRUCT_CAST(EXT,EXT_BASE_ADDR))

/* Memory Accelerator Module (MAM) */
#define _MAMCR          (__REG_CAST_8(  0xE01FC000 ))
#define _MAMTIM         (__REG_CAST_8(  0xE01FC004 ))

/* Memory Mapping */
#define _MEMMAP         (__REG_CAST_8(  0xE01FC040 ))

/* Phase Locked Loop 0 (PLL0) */
#define _PLL0CON        (__REG_CAST_8(  0xE01FC080))
#define _PLL0CFG        (__REG_CAST_8(  0xE01FC084 ))
#define _PLL0STAT       (__REG_CAST_16( 0xE01FC088 ))
#define _PLL0FEED       (__REG_CAST_8(  0xE01FC08C ))

/* Phase Locked Loop 1 (PLL1) */
#define _PLL1CON        (__REG_CAST_8(  0xE01FC0A0 ))
#define _PLL1CFG        (__REG_CAST_8(  0xE01FC0A4 ))
#define _PLL1STAT       (__REG_CAST_16( 0xE01FC0A8 ))
#define _PLL1FEED       (__REG_CAST_8(  0xE01FC0AC ))

/* Power Control */
#define _PCON           (__REG_CAST_8(  0xE01FC0C0 ))
#define _PCONP          (__REG_CAST_32( 0xE01FC0C4 ))

/* APB Divider */
#define _APBDIV         (__REG_CAST_8(  0xE01FC100 ))

/* External Interrupts */
#define _EXTINT         (__REG_CAST_8(  0xE01FC140 ))
#define _INTWAKE        (__REG_CAST_16( 0xE01FC144 ))
#define _EXTMODE        (__REG_CAST_8(  0xE01FC148 ))
#define _EXTPOLAR       (__REG_CAST_8(  0xE01FC14C ))

/* Reset */
#define _RSIR           (__REG_CAST_8(  0xE01FC180 ))

/* Code Security / Debugging */
#define _CSPR           (__REG_CAST_8(  0xE01FC184 ))

/* System Control Miscellaneous */
#define _SCS            (__REG_CAST_32( 0xE01FC1A0 ))

/***************************************************************************
 * Timer
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct{
    unsigned long IR;				/* Interrupt Register */
    unsigned long TCR;				/* Timer Control Register */
    unsigned long TC;				/* Timer Counter */
    unsigned long PR;				/* Prescale Register */
    unsigned long PC;				/* Prescale Counter */
    unsigned long MCR;				/* Match Control Register */
    unsigned long MR[4];			/* Match Register 0-3 */
    unsigned long CCR;				/* Capture Control Register */
    unsigned long CR[4];			/* Capture Register 0-3 */
    unsigned long EMR;				/* External Match Register */
    unsigned long Reserved[12];
    unsigned long CTCR;				/* Count Control Register */
} TIMER;
#endif

/* Timer 0 */
#define TIMER0_BASE_ADDR	0xE0004000
#define TIMER0_BASE		(__STRUCT_CAST(TIMER,TIMER0_BASE_ADDR))

#define _T0IR           (__REG_CAST_32( 0xE0004000 ))
#define _T0TCR          (__REG_CAST_32( 0xE0004004 ))
#define _T0TC           (__REG_CAST_32( 0xE0004008 ))
#define _T0PR           (__REG_CAST_32( 0xE000400C ))
#define _T0PC           (__REG_CAST_32( 0xE0004010 ))
#define _T0MCR          (__REG_CAST_32( 0xE0004014 ))
#define _T0MR0          (__REG_CAST_32( 0xE0004018 ))
#define _T0MR1          (__REG_CAST_32( 0xE000401C ))
#define _T0MR2          (__REG_CAST_32( 0xE0004020 ))
#define _T0MR3          (__REG_CAST_32( 0xE0004024 ))
#define _T0CCR          (__REG_CAST_32( 0xE0004028 ))
#define _T0CR0          (__REG_CAST_32( 0xE000402C ))
#define _T0CR1          (__REG_CAST_32( 0xE0004030 ))
#define _T0CR2          (__REG_CAST_32( 0xE0004034 ))
#define _T0CR3          (__REG_CAST_32( 0xE0004038 ))
#define _T0EMR          (__REG_CAST_32( 0xE000403C ))
#define _T0CTCR         (__REG_CAST_32( 0xE0004070 ))

/* Timer 1 */
#define TIMER1_BASE_ADDR	0xE0008000
#define TIMER1_BASE		(__STRUCT_CAST(TIMER,TIMER1_BASE_ADDR))

#define _T1IR           (__REG_CAST_32( 0xE0008000 ))
#define _T1TCR          (__REG_CAST_32( 0xE0008004 ))
#define _T1TC           (__REG_CAST_32( 0xE0008008 ))
#define _T1PR           (__REG_CAST_32( 0xE000800C ))
#define _T1PC           (__REG_CAST_32( 0xE0008010 ))
#define _T1MCR          (__REG_CAST_32( 0xE0008014 ))
#define _T1MR0          (__REG_CAST_32( 0xE0008018 ))
#define _T1MR1          (__REG_CAST_32( 0xE000801C ))
#define _T1MR2          (__REG_CAST_32( 0xE0008020 ))
#define _T1MR3          (__REG_CAST_32( 0xE0008024 ))
#define _T1CCR          (__REG_CAST_32( 0xE0008028 ))
#define _T1CR0          (__REG_CAST_32( 0xE000802C ))
#define _T1CR1          (__REG_CAST_32( 0xE0008030 ))
#define _T1CR2          (__REG_CAST_32( 0xE0008034 ))
#define _T1CR3          (__REG_CAST_32( 0xE0008038 ))
#define _T1EMR          (__REG_CAST_32( 0xE000803C ))
#define _T1CTCR         (__REG_CAST_32( 0xE0008070 ))

/***************************************************************************
 * Pulse Width Modulator (PWM)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	IR;				/* Interrupt Register */
	unsigned long	TCR;			/* Timer Control Register */
	unsigned long	TC;				/* Timer Counter */
	unsigned long	PR;				/* Prescale Register */
	unsigned long	PC;				/* Prescale Counter */
	unsigned long	MCR;			/* Match Control Register */
	unsigned long	MR0;			/* Match Register 0-3 */
	unsigned long	MR1;
	unsigned long	MR2;
	unsigned long	MR3;
	unsigned long	Reserved[6];
	unsigned long	MR4;			/* Match Register 4-6 */
	unsigned long	MR5;
	unsigned long	MR6;
	unsigned long	PCR;			/* PWM Control Register */
	unsigned long	LER;			/* Latch Enable Register */
} PWM;
#endif

#define PWM_BASE_ADDR	0xE0014000
#define PWM_BASE		(__STRUCT_CAST(PWM,PWM_BASE_ADDR))

#define _PWMIR           (__REG_CAST_32( 0xE0014000 ))
#define _PWMTCR          (__REG_CAST_32( 0xE0014004 ))
#define _PWMTC           (__REG_CAST_32( 0xE0014008 ))
#define _PWMPR           (__REG_CAST_32( 0xE001400C ))
#define _PWMPC           (__REG_CAST_32( 0xE0014010 ))
#define _PWMMCR          (__REG_CAST_32( 0xE0014014 ))
#define _PWMMR0          (__REG_CAST_32( 0xE0014018 ))
#define _PWMMR1          (__REG_CAST_32( 0xE001401C ))
#define _PWMMR2          (__REG_CAST_32( 0xE0014020 ))
#define _PWMMR3          (__REG_CAST_32( 0xE0014024 ))
#define _PWMMR4          (__REG_CAST_32( 0xE0014040 ))
#define _PWMMR5          (__REG_CAST_32( 0xE0014044 ))
#define _PWMMR6          (__REG_CAST_32( 0xE0014048 ))
#define _PWMPCR          (__REG_CAST_32( 0xE001404C ))
#define _PWMLER          (__REG_CAST_32( 0xE0014050 ))

/***************************************************************************
 * Universal Asynchronous Receiver Transmitter (UART)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	RBR_THR_DLL;	/* Receive Buffer Reg, Transmit Holding Reg, Divisor Latch LSB */
	unsigned long	IER_DLM;      	/* Interrupt Enable Register, Divisor Latch MSB register*/
	unsigned long	IIR_FCR;      	/* Interrupt ID Register, FIFO Control Register */
	unsigned long	LCR;			/* Line Control Register */
	unsigned long	MCR;			/* Modem Config Register (UART1 only) */
	unsigned long	LSR;			/* Line Status Register */
	unsigned long	MSR;			/* Modem Status Register (UART1 only) */
	unsigned long	SCR;			/* Scratch pad Register */
	unsigned long	ACR;			/* Autobaud Control Register */
	unsigned long	Reserved;
	unsigned long	FDR;			/* Fractionnal Divider Register */
	unsigned long	TER;			/* Tx Enable Register */
} UART;
#endif

#define UART0_BASE_ADDR	0xE000C000
#define UART1_BASE_ADDR	0xE0010000

#define UART0_BASE		(__STRUCT_CAST(UART,UART0_BASE_ADDR))
#define UART1_BASE		(__STRUCT_CAST(UART,UART1_BASE_ADDR))

/* Universal Asynchronous Receiver Transmitter 0 (UART0) */
#define _U0RBR           (__REG_CAST_8(  0xE000C000 ))
#define _U0THR           (__REG_CAST_8(  0xE000C000 ))
#define _U0IER           (__REG_CAST_32( 0xE000C004 ))
#define _U0IIR           (__REG_CAST_32( 0xE000C008 ))
#define _U0FCR           (__REG_CAST_8(  0xE000C008 ))
#define _U0LCR           (__REG_CAST_8(  0xE000C00C ))
#define _U0MCR           (__REG_CAST_8(  0xE000C010 ))
#define _U0LSR           (__REG_CAST_8(  0xE000C014 ))
#define _U0MSR           (__REG_CAST_8(  0xE000C018 ))
#define _U0SCR           (__REG_CAST_8(  0xE000C01C ))
#define _U0DLL           (__REG_CAST_8(  0xE000C000 ))
#define _U0DLM           (__REG_CAST_8(  0xE000C004 ))
#define _U0ACR           (__REG_CAST_32( 0xE000C020 ))
#define _U0FDR           (__REG_CAST_32( 0xE000C028 ))
#define _U0TER           (__REG_CAST_8(  0xE000C030 ))

/* Universal Asynchronous Receiver Transmitter 1 (UART1) */
#define _U1RBR           (__REG_CAST_8(  0xE0010000 ))
#define _U1THR           (__REG_CAST_8(  0xE0010000 ))
#define _U1IER           (__REG_CAST_32( 0xE0010004 ))
#define _U1IIR           (__REG_CAST_32( 0xE0010008 ))
#define _U1FCR           (__REG_CAST_8(  0xE0010008 ))
#define _U1LCR           (__REG_CAST_8(  0xE001000C ))
#define _U1MCR           (__REG_CAST_8(  0xE0010010 ))
#define _U1LSR           (__REG_CAST_8(  0xE0010014 ))
#define _U1MSR           (__REG_CAST_8(  0xE0010018 ))
#define _U1SCR           (__REG_CAST_8(  0xE001001C ))
#define _U1DLL           (__REG_CAST_8(  0xE0010000 ))
#define _U1DLM           (__REG_CAST_8(  0xE0010004 ))
#define _U1ACR           (__REG_CAST_32( 0xE0010020 ))
#define _U1FDR           (__REG_CAST_32( 0xE0010028 ))
#define _U1TER           (__REG_CAST_8(  0xE0010030 ))

/***************************************************************************
 * I2C Interface
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned char	CONSET;			/* I2C Control Set Register */
	unsigned char	Reserved1[3];
	unsigned char	STAT;			/* I2C Status Register */
	unsigned char	Reserved2[3];
	unsigned char	DAT;			/* I2C Data Register */
	unsigned char	Reserved3[3];
	unsigned char	ADR;			/* I2C Slave Address Register */
	unsigned char	Reserved4[3];
	unsigned short	SCLH;			/* I2C SCL High Duty Cycle Register */
	unsigned short	Reserved5;
	unsigned short	SCLL;			/* I2C SCL Low Duty Cycle Register */
	unsigned short	Reserved6;
	unsigned char	CONCLR;			/* I2C Control Clear Register */
	unsigned char	Reserved7[3];
} I2C;
#endif

#define I2C0_BASE_ADDR	0xE001C000
#define I2C1_BASE_ADDR	0xE005C000

#define I2C0_BASE		(__STRUCT_CAST(I2C,I2C0_BASE_ADDR))
#define I2C1_BASE		(__STRUCT_CAST(I2C,I2C1_BASE_ADDR))

/* I2C Interface 0 */
#define _I2C0CONSET      (__REG_CAST_8(  0xE001C000 ))
#define _I2C0STAT        (__REG_CAST_8(  0xE001C004 ))
#define _I2C0DAT         (__REG_CAST_8(  0xE001C008 ))
#define _I2C0ADR         (__REG_CAST_8(  0xE001C00C ))
#define _I2C0SCLH        (__REG_CAST_16( 0xE001C010 ))
#define _I2C0SCLL        (__REG_CAST_16( 0xE001C014 ))
#define _I2C0CONCLR      (__REG_CAST_8(  0xE001C018 ))

/* I2C Interface 1 */
#define _I2C1CONSET      (__REG_CAST_8(  0xE005C000 ))
#define _I2C1STAT        (__REG_CAST_8(  0xE005C004 ))
#define _I2C1DAT         (__REG_CAST_8(  0xE005C008 ))
#define _I2C1ADR         (__REG_CAST_8(  0xE005C00C ))
#define _I2C1SCLH        (__REG_CAST_16( 0xE005C010 ))
#define _I2C1SCLL        (__REG_CAST_16( 0xE005C014 ))
#define _I2C1CONCLR      (__REG_CAST_8(  0xE005C018 ))

/***************************************************************************
 * SPI0 (Serial Peripheral Interface 0)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned short	CR;				/* SPI Constrol Register */
	unsigned short  Reserved1;
	unsigned char	SR;				/* SPI Status Register */
	unsigned char	Reserved2[3];
	unsigned short	DR;				/* SPI Data Register */
	unsigned short  Reserved3;
	unsigned char	CCR;			/* SPI Clock Counter Register */
	unsigned char	Reserved4[15];
	unsigned char	INT;			/* SPI Interrupt Flag */
	unsigned char	Reserved5[3];
} SPI;
#endif

#define SPI0_BASE_ADDR	0xE0020000
#define SPI0_BASE		(__STRUCT_CAST(SPI,SPI0_BASE_ADDR))

#define _S0SPCR          (__REG_CAST_16( 0xE0020000 ))
#define _S0SPSR          (__REG_CAST_8(  0xE0020004 ))
#define _S0SPDR          (__REG_CAST_16( 0xE0020008 ))
#define _S0SPCCR         (__REG_CAST_8(  0xE002000C ))
#define _S0SPINT         (__REG_CAST_8(  0xE002001C ))

/***************************************************************************
 * SSP Controller (SPI1)
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned short	CR0;			/* Control Register 0 */
	unsigned short  Reserved1;
	unsigned char	CR1;			/* Control Register 1 */
	unsigned char	Reserved2[3];
	unsigned short	DR;				/* Data Register */
	unsigned short  Reserved3;
	unsigned char	SR;				/* Status Register */
	unsigned char	Reserved4[3];
	unsigned char	CPSR;			/* Clock Precsale Register */
	unsigned char	Reserved5[3];
	unsigned char	IMSC;			/* Interrupt Mask Set and Clear Register */
	unsigned char	Reserved6[3];
	unsigned char	RIS;			/* Interrupt Mask Set and Clear Register */
	unsigned char	Reserved7[3];
	unsigned char	MIS;			/* Interrupt Status Register */
	unsigned char	Reserved8[3];
	unsigned char	ICR;			/* Interrupt Clear Register */
	unsigned char	Reserved9[3];
} SSP;
#endif

#define SSP_BASE_ADDR	0xE0068000
#define SSP_BASE		(__STRUCT_CAST(SSP,SSP_BASE_ADDR))

#define _SSPCR0          (__REG_CAST_16( 0xE0068000 ))
#define _SSPCR1          (__REG_CAST_8(  0xE0068004 ))
#define _SSPDR           (__REG_CAST_16( 0xE0068008 ))
#define _SSPSR           (__REG_CAST_8(  0xE006800C ))
#define _SSPCPSR         (__REG_CAST_8(  0xE0068010 ))
#define _SSPIMSC         (__REG_CAST_8(  0xE0068014 ))
#define _SSPRIS          (__REG_CAST_8(  0xE0068018 ))
#define _SSPMIS          (__REG_CAST_8(  0xE006801C ))
#define _SSPICR          (__REG_CAST_8(  0xE0068020 ))

/***************************************************************************
 * Real Time Clock
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned char	ILR;			/* Interrupt Location Register */
	unsigned char	Reserved1[3];
	unsigned short	CTC;			/* Clock Tick Count */
	unsigned short	Reserved2;
	unsigned char	CCR;			/* Clock Control Register */
	unsigned char	Reserved3[3];
	unsigned char	CIIR;			/* Clock Increment Interrupt Register */
	unsigned char	Reserved4[3];
	unsigned char	AMR;			/* Alarm Mask Register */
	unsigned char	Reserved5[3];
	unsigned long	CTIME0;			/* Consolidated Time Register 0 */
	unsigned long	CTIME1;			/* Consolidated Time Register 1 */
	unsigned long	CTIME2;			/* Consolidated Time Register 2 */
	unsigned char	SEC;			/* Second 0-59 */
	unsigned char	Reserved6[3];
	unsigned char	MIN;			/* Minute 0-59 */
	unsigned char	Reserved7[3];
	unsigned char	HOUR;			/* Hour 0-23 */
	unsigned char	Reserved8[3];
	unsigned char	DOM;			/* Day Of Month 1-31 */
	unsigned char	Reserved9[3];
	unsigned char	DOW;			/* Day Of Week 0-6 */
	unsigned char	Reserved10[3];
	unsigned short	DOY;			/* Day Of Year 1-366 */
	unsigned short	Reserved11;
	unsigned char	MONTH;			/* Month 1-12 */
	unsigned char	Reserved12[3];
	unsigned short	YEAR;			/* Year 0-4095 */
	unsigned short	Reserved13[17];
	unsigned char	ALSEC;			/* Alarm Value for Second 0-59 */
	unsigned char	Reserved14[3];
	unsigned char	ALMIN;			/* Alarm Value for Minute 0-59 */
	unsigned char	Reserved15[3];
	unsigned char	ALHOUR;			/* Alarm Value for Hour 0-23 */
	unsigned char	Reserved16[3];
	unsigned char	ALDOM;			/* Alarm Value for Day Of Month 1-31 */
	unsigned char	Reserved17[3];
	unsigned char	ALDOW;			/* Alarm Value for Day Of Week 0-6 */
	unsigned char	Reserved18[3];
	unsigned short	ALDOY;			/* Alarm Value for Day Of Year 1-366 */
	unsigned short	Reserved19;
	unsigned char	ALMON;			/* Alarm Value for Month 1-12 */
	unsigned char	Reserved20[3];
	unsigned short	ALYEAR;			/* Alarm Value for Year 0-4095 */
	unsigned short	Reserved21;
	unsigned short	PREINT;			/* Prescale Value, Integer portion */
	unsigned short	Reserved22;
	unsigned short	PREFRAC;		/* Prescale Value, Fractionnal portion */
	unsigned short	Reserved23;
} RTC;
#endif

#define RTC_BASE_ADDR	0xE0024000
#define RTC_BASE		(__STRUCT_CAST(RTC,RTC_BASE_ADDR))

#define _ILR             (__REG_CAST_8(  0xE0024000 ))
#define _CTC             (__REG_CAST_16( 0xE0024004 ))
#define _CCR             (__REG_CAST_8(  0xE0024008 ))
#define _CIIR            (__REG_CAST_8(  0xE002400C ))
#define _AMR             (__REG_CAST_8(  0xE0024010 ))
#define _CTIME0          (__REG_CAST_32( 0xE0024014 ))
#define _CTIME1          (__REG_CAST_32( 0xE0024018 ))
#define _CTIME2          (__REG_CAST_32( 0xE002401C ))
#define _SEC             (__REG_CAST_8(  0xE0024020 ))
#define _MIN             (__REG_CAST_8(  0xE0024024 ))
#define _HOUR            (__REG_CAST_8(  0xE0024028 ))
#define _DOM             (__REG_CAST_8(  0xE002402C ))
#define _DOW             (__REG_CAST_8(  0xE0024030 ))
#define _DOY             (__REG_CAST_16( 0xE0024034 ))
#define _MONTH           (__REG_CAST_8(  0xE0024038 ))
#define _YEAR            (__REG_CAST_16( 0xE002403C ))
#define _ALSEC           (__REG_CAST_8(  0xE0024060 ))
#define _ALMIN           (__REG_CAST_8(  0xE0024064 ))
#define _ALHOUR          (__REG_CAST_8(  0xE0024068 ))
#define _ALDOM           (__REG_CAST_8(  0xE002406C ))
#define _ALDOW           (__REG_CAST_8(  0xE0024070 ))
#define _ALDOY           (__REG_CAST_16( 0xE0024074 ))
#define _ALMON           (__REG_CAST_8(  0xE0024078 ))
#define _ALYEAR          (__REG_CAST_16( 0xE002407C ))
#define _PREINT          (__REG_CAST_16( 0xE0024080 ))
#define _PREFRAC         (__REG_CAST_16( 0xE0024084 ))

/***************************************************************************
 * A/D Converter
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	CR;				/* A/D Control Register */
	unsigned long	GDR;			/* A/D Global Data Register */
	unsigned long	GSR;			/* A/D Global Start Register (AD0 only) */
	unsigned long	INTEN;			/* A/D Interrupt Enable Register */
	unsigned long	DR[8];			/* A/D Data Register channel[i], i=0-7 */
	unsigned long	STAT;			/* A/D Status Register */
} ADC;
#endif

#define AD0_BASE_ADDR	0xE0034000
#define AD1_BASE_ADDR	0xE0060000

#define AD0_BASE		(__STRUCT_CAST(ADC,AD0_BASE_ADDR))
#define AD1_BASE		(__STRUCT_CAST(ADC,AD1_BASE_ADDR))

/* A/D Converter 0 (AD0) */
#define _AD0CR           (__REG_CAST_32( 0xE0034000 ))
#define _AD0GDR          (__REG_CAST_32( 0xE0034004 ))
#define _AD0STAT         (__REG_CAST_32( 0xE0034030 ))
#define _AD0INTEN        (__REG_CAST_32( 0xE003400C ))
#define _AD0DR0          (__REG_CAST_32( 0xE0034010 ))
#define _AD0DR1          (__REG_CAST_32( 0xE0034014 ))
#define _AD0DR2          (__REG_CAST_32( 0xE0034018 ))
#define _AD0DR3          (__REG_CAST_32( 0xE003401C ))
#define _AD0DR4          (__REG_CAST_32( 0xE0034020 ))
#define _AD0DR5          (__REG_CAST_32( 0xE0034024 ))
#define _AD0DR6          (__REG_CAST_32( 0xE0034028 ))
#define _AD0DR7          (__REG_CAST_32( 0xE003402C ))

/* A/D Converter 1 (AD1) */
#define _AD1CR           (__REG_CAST_32( 0xE0060000 ))
#define _AD1GDR          (__REG_CAST_32( 0xE0060004 ))
#define _AD1STAT         (__REG_CAST_32( 0xE0060030 ))
#define _AD1INTEN        (__REG_CAST_32( 0xE006000C ))
#define _AD1DR0          (__REG_CAST_32( 0xE0060010 ))
#define _AD1DR1          (__REG_CAST_32( 0xE0060014 ))
#define _AD1DR2          (__REG_CAST_32( 0xE0060018 ))
#define _AD1DR3          (__REG_CAST_32( 0xE006001C ))
#define _AD1DR4          (__REG_CAST_32( 0xE0060020 ))
#define _AD1DR5          (__REG_CAST_32( 0xE0060024 ))
#define _AD1DR6          (__REG_CAST_32( 0xE0060028 ))
#define _AD1DR7          (__REG_CAST_32( 0xE006002C ))

/* A/D Converter Global */
#define _ADGSR           (__REG_CAST_32( 0xE0034008 ))

/***************************************************************************
 * D/A Converter
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned long	DACR;
} DAC;
#endif

#define DAC_BASE_ADDR	0xE006C000
#define DAC_BASE		(__STRUCT_CAST(DAC,0xE006C000))

#define _DACR           (__REG_CAST_32( 0xE006C000 ))


/***************************************************************************
 * Watchdog
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {
	unsigned char	MOD;			/* Watchdog Mode Register */
	unsigned char	Reserved1[3];
	unsigned long 	TC;				/* Watchdog Timer Constant register */
	unsigned char 	FEED;			/* Watchdog Feed Sequence Register */
	unsigned char	Reserved2[3];
	unsigned long 	TV;				/* Watchdog Timer Value */
} WD;
#endif

#define WD_BASE_ADDR	0xE0000000
#define WD_BASE			(__STRUCT_CAST(WD,WD_BASE_ADDR))

#define _WDMOD          (__REG_CAST_8(  0xE0000000 ))
#define _WDTC           (__REG_CAST_32( 0xE0000004 ))
#define _WDFEED         (__REG_CAST_8(  0xE0000008 ))
#define _WDTV           (__REG_CAST_32( 0xE000000C ))

/***************************************************************************
 * USB Controller
 ***************************************************************************/
#ifndef __ASSEMBLY__
typedef volatile struct {

} USB;
#endif

#define USB_BASE_ADDR	0xE0090000
#define USB_BASE		(__STRUCT_CAST(USB,USB_BASE_ADDR))

#define _USBIntSt       (__REG_CAST_32( 0xE01FC1C0 ))
#define _USBDevIntSt    (__REG_CAST_32( 0xE0090000 ))
#define _USBDevIntEn    (__REG_CAST_32( 0xE0090004 ))
#define _USBDevIntClr   (__REG_CAST_32( 0xE0090008 ))
#define _USBDevIntSet   (__REG_CAST_32( 0xE009000C ))
#define _USBDevIntPri   (__REG_CAST_8(  0xE009002C ))
#define _USBEpIntSt     (__REG_CAST_32( 0xE0090030 ))
#define _USBEpIntEn     (__REG_CAST_32( 0xE0090034 ))
#define _USBEpIntClr    (__REG_CAST_32( 0xE0090038 ))
#define _USBEpIntSet    (__REG_CAST_32( 0xE009003C ))
#define _USBEpIntPri    (__REG_CAST_32( 0xE0090040 ))
#define _USBReEp        (__REG_CAST_32( 0xE0090044 ))
#define _USBEpInd       (__REG_CAST_32( 0xE0090048 ))
#define _USBMaxPSize    (__REG_CAST_32( 0xE009004C ))
#define _USBRxData      (__REG_CAST_32( 0xE0090018 ))
#define _USBRxPLen      (__REG_CAST_32( 0xE0090020 ))
#define _USBTxData      (__REG_CAST_32( 0xE009001C ))
#define _USBTxPLen      (__REG_CAST_32( 0xE0090024 ))
#define _USBCtrl        (__REG_CAST_32( 0xE0090028 ))
#define _USBCmdCode     (__REG_CAST_32( 0xE0090010 ))
#define _USBCmdData     (__REG_CAST_32( 0xE0090014 ))
#define _USBDMARSt      (__REG_CAST_32( 0xE0090050 ))
#define _USBDMARClr     (__REG_CAST_32( 0xE0090054 ))
#define _USBDMARSet     (__REG_CAST_32( 0xE0090058 ))
#define _USBUDCAH       (__REG_CAST_32( 0xE0090080 ))
#define _USBEpDMASt     (__REG_CAST_32( 0xE0090084 ))
#define _USBEpDMAEn     (__REG_CAST_32( 0xE0090088 ))
#define _USBEpDMADis    (__REG_CAST_32( 0xE009008C ))
#define _USBDMAIntSt    (__REG_CAST_32( 0xE0090090 ))
#define _USBDMAIntEn    (__REG_CAST_32( 0xE0090094 ))
#define _USBEoTIntSt    (__REG_CAST_32( 0xE00900A0 ))
#define _USBEoTIntClr   (__REG_CAST_32( 0xE00900A4 ))
#define _USBEoTIntSet   (__REG_CAST_32( 0xE00900A8 ))
#define _USBNDDRIntSt   (__REG_CAST_32( 0xE00900AC ))
#define _USBNDDRIntClr  (__REG_CAST_32( 0xE00900B0 ))
#define _USBNDDRIntSet  (__REG_CAST_32( 0xE00900B4 ))
#define _USBSysErrIntSt (__REG_CAST_32( 0xE00900B8 ))
#define _USBSysErrIntClr (__REG_CAST_32( 0xE00900BC ))
#define _USBSysErrIntSet (__REG_CAST_32( 0xE00900C0 ))

#endif  // __LPC214x_H
