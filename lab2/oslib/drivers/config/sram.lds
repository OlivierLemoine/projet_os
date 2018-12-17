/*---------------------------------------------------------------------------
 *      Linker script for running in SRAM on the LPC2148
 *-------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

/* The sizes of the stacks used by the application. NOTE: you need to adjust */
USR_STACK_SIZE = 128;
IRQ_STACK_SIZE = 1024;
FIQ_STACK_SIZE = 0;
SVC_STACK_SIZE = 1024;
ABT_STACK_SIZE = 0;
UND_STACK_SIZE = 0;

HEAP_END = 0x7FD02000;

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
    SRAM1 (rwx) : ORIGIN = 0x40000000, LENGTH = 32K
    SRAM2 (rwx) : ORIGIN = 0x7FD00000, LENGTH = 8K
}

SECTIONS
{  
	/* ----------------------------------------------------------------------
     * .vectors section : exception vectors (remapped in SRAM)
     * --------------------------------------------------------------------*/
	.vectors : {
		*(.vectors)
	} >SRAM1
	
	/* ----------------------------------------------------------------------
     * .text section : code 
     * --------------------------------------------------------------------*/
    .text : {
    	*(.init .init.*)
        *(.text .text.*)
    } >SRAM1
    
	/* ----------------------------------------------------------------------
     * .rodata section (read-only (const) initialized variables)
     * --------------------------------------------------------------------*/
    .rodata : {
		*(.rodata .rodata.*) 
    } > SRAM1
    
	/* ----------------------------------------------------------------------
     * .data section (read/write initialized variables)
     * 
     * initial values need to be copyed to their RAM location
     * --------------------------------------------------------------------*/
/*    .data : {
        __data_load = LOADADDR (.data);
        __data_start = .;
        *(.data)
		. = ALIGN (4);
        __data_end = .;
    } >SRAM2 AT>SRAM1*/
    .data : {
        __data_load = LOADADDR (.data);
        __data_start = .;
        *(.data)
		. = ALIGN (4);
        __data_end = .;
    } >SRAM1

    /* ----------------------------------------------------------------------
     * .bss section (uninitialized variables)
     * 
     * this section need to be zeroed
     * --------------------------------------------------------------------*/
    .bss : {
        __bss_start = . ;
        *(.bss .bss.*)
		. = ALIGN (4);
        __bss_end = .;
    } >SRAM1

    /* ----------------------------------------------------------------------
     * .stack section
     * --------------------------------------------------------------------*/
    .stack (NOLOAD) : {
		. = ALIGN (4);
        __stack_start = . ;
		
        . += USR_STACK_SIZE;
        . = ALIGN (4);
        __usr_stack_top = . ;

        . += IRQ_STACK_SIZE;
        . = ALIGN (4);
        __irq_stack_top = . ;

        . += FIQ_STACK_SIZE;
        . = ALIGN (4);
        __fiq_stack_top = . ;

        . += SVC_STACK_SIZE;
        . = ALIGN (4);
        __svc_stack_top = . ;

        . += ABT_STACK_SIZE;
        . = ALIGN (4);
        __abt_stack_top = . ;

        . += UND_STACK_SIZE;
        . = ALIGN (4);
        __und_stack_top = . ;

        __stack_end = .;
    } >SRAM1
    
    /* ----------------------------------------------------------------------
     * .stack section
     * --------------------------------------------------------------------*/
   .heap (NOLOAD) : {
		__heap_start = .;
		. = ABSOLUTE(HEAP_END) ;
		__heap_end = . ;
   } >SRAM2
}
