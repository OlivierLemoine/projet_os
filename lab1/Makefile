##############################################################################################
# Start of user section
#
# PROJ = tp1_ex1
# PROJ = tp1_ex2
# PROJ = tp1_ex3
# PROJ = tp1_ex4
# PROJ = tp1_ex5
# PROJ = tp1_ex6
PROJ = tp1_ex7

# Directory defines
OSLIB   = oslib
KERNEL  = kernel
DRIVERS = $(OSLIB)/drivers

# Define linker script file here
LDSCRIPT = $(DRIVERS)/config/sram.lds

# Define optimisation level here
OPT = -O0

# Debug
DEBUG = -g

# List all user C define here
UDEFS =

# Define ASM defines here
UADEFS = 

# List C source files here
SRC  = user/$(PROJ).c \
       $(DRIVERS)/startup/board_lowlevel.c \
       $(DRIVERS)/startup/board_stubs.c \
       $(DRIVERS)/target.c \
       $(KERNEL)/alloc.c $(KERNEL)/kernel.c $(KERNEL)/list.c \
       $(KERNEL)/syscall_dispatch.c $(OSLIB)/kernellib.c 

# List ASM source files here
ASRC = $(DRIVERS)/startup/board_cstartup.s

# List all user directories here
UINCDIR =include $(KERNEL) $(OSLIB) $(OSLIB)/drivers $(DRIVERS)/include

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = $(DRIVERS)/lib/liblpc2148.a

#
# End of user defines
#############################################################################


#############################################################################
# Start of default section
#

TARGET  = arm-none-eabi-
CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

MCU  = arm7tdmi

# List all default C defines here, like -D_DEBUG=1
DDEFS =

# List all default ASM defines here, like -D_DEBUG=1
DADEFS = -D__ASSEMBLY__

# List all default directories to look for include files here
DINCDIR = 

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 

#
# End of default section
##############################################################################################

INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))
DEFS    = $(DDEFS) $(UDEFS)
ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(SRC:.c=.o) $(ASRC:.s=.o)
LIBS    = $(DLIBS) $(ULIBS)

# In case THUMB code should be created, add "-mthumb" to the MCFLAGS too.
MCFLAGS = -mcpu=$(MCU)

ASFLAGS = $(INCDIR) -Wa,--gdwarf2 $(ADEFS)
#CFLAGS = $(INCDIR) $(MCFLAGS) $(DEBUG) $(OPT) -fomit-frame-pointer -Wall -mlong-calls -ffunction-sections $(DEFS)
CFLAGS = $(INCDIR) $(MCFLAGS) $(DEBUG) $(OPT) -fomit-frame-pointer -Wall -ffunction-sections $(DEFS)
#LDFLAGS = $(MCFLAGS) -nostartfiles -nostdlib -T$(LDSCRIPT) -Wl,-Map=$(PROJ).map,--gc-sections $(LIBDIR)
LDFLAGS = $(MCFLAGS) -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(PROJ).map,--gc-sections $(LIBDIR)

# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d
ASFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#
all: $(OBJS) main.elf
# $(PROJ).hex $(PROJ).bin

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@

%o: %s
	$(AS) $(ASFLAGS) $< -o $@

%.elf: $(OBJS) $(LDSCRIPT)
	$(CC) -o $@ $(filter-out %.lds, $^) $(LDFLAGS) $(LIBS)
	$(OBJDUMP) -h $@
	$(SIZE) $@
	
%hex: %elf
	$(OBJCOPY) -O ihex $< $@

%bin: %elf
	$(OBJCOPY) -O binary $< $@
	
clean:
	-rm -f $(OBJS)
	-rm -f *.elf
	-rm -f *.map
	-rm -f *.bin
	-rm -f *.hex
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

.PHONY: clean

