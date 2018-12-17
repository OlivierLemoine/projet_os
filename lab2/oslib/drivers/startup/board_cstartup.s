
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

#define	ARM_MODE_USR	 0x10      /* Normal User Mode */
#define ARM_MODE_FIQ     0x11      /* FIQ Fast Interrupts Mode */
#define ARM_MODE_IRQ     0x12      /* IRQ Standard Interrupts Mode */
#define ARM_MODE_SVC     0x13      /* Supervisor Interrupts Mode */
#define ARM_MODE_ABT     0x17      /* Abort Processing memory Faults Mode */
#define	ARM_MODE_UND	 0x1B      /* Undefined Instructions Mode */
#define	ARM_MODE_SYS	 0x1F      /* System Running in Priviledged Operating Mode */
#define	ARM_MODE_MASK	 0x1F

#define I_BIT            0x80      /* disable IRQ when I bit is set */
#define F_BIT            0x40      /* disable FIQ when F bit is set */

//------------------------------------------------------------------------------
//         Startup routine
//------------------------------------------------------------------------------

        .align      4
        .arm

/* Exception vectors
 *******************/
        .section    .vectors, "ax" , %progbits
        .global     _start, _exit
_start:
        ldr     pc, resetVector			/* Reset */
        ldr     pc, undefVector			/* Undefined instruction */
        ldr     pc, swiVector			/* Software interrupt */
        ldr     pc, prefetchAbortVector	/* Prefetch abort */
        ldr     pc, dataAbortVector		/* Data abort */
        .word   0xb9205f80				/* Magic number */
        ldr     pc, irqVector			/* Interrupt */
        ldr     pc, fiqVector			/* Fast interrupt */
resetVector:
		.word	resetHandler
undefVector:
		.word	undefHandler
swiVector:
		.word	swiHandler
prefetchAbortVector:
		.word	prefetchAbortHandler
dataAbortVector:
		.word	dataAbortHandler
reservedVector:
		.word	0
irqVector:
		.word	irqHandler	
fiqVector:
		.word	fiqHandler
		
        .section .init, "ax"
		.extern  syscall_handler, saved_ctx, LowLevelInit
//		.text
//------------------------------------------------------------------------------
/// Handles a undefined instructions
//------------------------------------------------------------------------------
undefHandler:
        b       undefHandler

//------------------------------------------------------------------------------
/// Handles instruction access abort
//------------------------------------------------------------------------------
prefetchAbortHandler:
        b       prefetchAbortHandler

//------------------------------------------------------------------------------
/// Handles data access abort
//------------------------------------------------------------------------------
dataAbortHandler:
        b       dataAbortHandler

//------------------------------------------------------------------------------
/// Handles a fast interrupt request by branching to the address defined in the
/// AIC.
//------------------------------------------------------------------------------
fiqHandler:
        b       fiqHandler

//------------------------------------------------------------------------------
/// Handles incoming interrupt requests by branching to the corresponding
/// handler, as defined in the VIC.
//------------------------------------------------------------------------------
irqHandler:
        sub     lr, lr, #4
        sub     sp, sp, #(4*17)         // get room for user context on irq stack
        stmia   sp, {r0-r14}^           // push r0-r14 (user) on svc stack
        str     lr, [sp, #(4*15)]       // push lr_irq (return user pc)
        mrs     r2, spsr
        str     r2, [sp, #(4*16)]       // push spsr_irq (user cpsr)
        
        ldr     r0, =saved_ctx          // set saved_ctx point to current saved
        str     sp, [r0]                // context on svc stack
        
        ldr     r4, =_VICVectAddr       // get the irq service routine from VIC
        mov     lr, pc
        ldr     pc, [r4]                // branch to VIC irq subroutine
        mov     r0, #0
        str     r0, [r4]                // acknowledge VIC
        
        ldr     r2, [sp,#(4*16)]        // restore spsr_irq
        msr     spsr_cxsf, r2
        ldr     lr, [sp, #(4*15)]       // restore lr_irq
        ldmia   sp, {r0-r14}^           // restore user mode registers
        add     sp, sp, #(4*17)         // restore sp_irq
        movs    pc, lr                  // jump back to user mode with eventually
                                        // a new context

//------------------------------------------------------------------------------
/// Handles software interrupt for syscall.
//------------------------------------------------------------------------------
swiHandler:
        sub     sp, sp, #(4*17)         // get room for user context on svc stack
        stmia   sp, {r0-r14}^           // push r0-r14 (user) on svc stack
        str     lr, [sp, #(4*15)]       // push lr_svc (return user pc)
        mrs     r2, spsr
        str     r2, [sp, #(4*16)]       // push spsr_svc (user cpsr)
        
        ldr     r2, =saved_ctx          // set saved_ctx point to current saved 
        str     sp, [r2]                // context on svc stack
        
        ldr     r0, [lr, #-4]
        bic     r0, r0, #0xff000000     // r0 = syscall number
        
        mov     r1, sp                  // r1 = user context pointer
       
        bl      syscall_dispatch        // C handler call
        str     r0, [sp]                // push result of the syscall
        ldr     r2, [sp,#(4*16)]        // restore spsr_svc
        msr     spsr_cxsf, r2
        ldr     lr, [sp, #(4*15)]       // restore lr_svc
        ldmia   sp, {r0-r14}^           // restore user mode registers
        add     sp, sp, #(4*17)         // restore sp_svc
        movs    pc, lr                  // jump back to user mode with eventually
                                        // a new context
        
//------------------------------------------------------------------------------
/// Initializes the chip and branches to the main() function.
//------------------------------------------------------------------------------

//entry:
resetHandler:
/* Perform low-level initialization of the chip using LowLevelInit() */
        ldr     sp, =__usr_stack_top
	    ldr     r0, =LowLevelInit
        mov     lr, pc
        bx      r0

/* Relocate the .data section (copy from ROM to RAM) */
/*        ldr     r0, =__data_load
        ldr     r1, =__data_start
        ldr     r2, =__data_end
1:
        cmp     r1, r2
        ldrcc   r3, [r0], #4
        strcc   r3, [r1], #4
        bcc     1b
*/
/* Clear the .bss section (zero init) */
	    ldr     r0, =__bss_start
        ldr     r1, =__bss_end
        mov     r2, #0
1:
        cmp     r0, r1
        strcc   r2, [r0], #4
        bcc     1b

/* Initialize stack pointers for all ARM modes */
        msr     CPSR_c,#(ARM_MODE_IRQ | I_BIT | F_BIT)
        ldr     sp,=__irq_stack_top           /* set the IRQ stack pointer */

        msr     CPSR_c,#(ARM_MODE_FIQ | I_BIT | F_BIT)
        ldr     sp,=__fiq_stack_top           /* set the FIQ stack pointer */

        msr     CPSR_c,#(ARM_MODE_SVC | I_BIT | F_BIT)
        ldr     sp,=__svc_stack_top           /* set the SVC stack pointer */

        msr     CPSR_c,#(ARM_MODE_ABT | I_BIT | F_BIT)
        ldr     sp,=__abt_stack_top           /* set the ABT stack pointer */

        msr     CPSR_c,#(ARM_MODE_UND | I_BIT | F_BIT)
        ldr     sp,=__und_stack_top           /* set the UND stack pointer */

        msr     CPSR_c,#(ARM_MODE_USR | I_BIT | F_BIT)
        ldr     sp,=__usr_stack_top           /* set the USR stack pointer */

/* Initialize devices */
		ldr		r0, =dev_init
		mov		lr, pc
		bx		r0
		
/* Branch to main() */
        ldr     r0, =main
        mov     lr, pc
        bx      r0

/* Loop indefinitely when program is finished */
_exit:
        b       _exit

