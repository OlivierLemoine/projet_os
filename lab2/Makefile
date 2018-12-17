##############################################################################################
# Start of user section
#
#PROJ = tp1_ex1
#PROJ = tp1_ex2
#PROJ = tp1_ex3
#PROJ = tp1_ex4
#PROJ = tp1_ex5
#PROJ = tp1_ex3
#PROJ = tp1_ex6
#PROJ = tp1_ex7
# PROJ = tp2_ex1
# PROJ = tp2_ex2
# PROJ = tp2_ex3
# PROJ = tp2_ex4
# PROJ = tp2_ex5
# PROJ = tp3_ex1
PROJ = tp3_ex2

# Directory defines
OSLIB   = oslib
KERNEL  = kernel
DRIVERS = oslib/drivers

# List C source files here
# Define linker script file here
LDSCRIPT = $(DRIVERS)/config/sram.lds

# Define optimisation level here
# OPT = -O0
OPT = -O2

# Debug
DEBUG = #-g

# List all user C define here
# UDEFS = -D__WITH_GPIO_DEV

# Define ASM defines here
UADEFS = 

SRC  = user/$(PROJ).c \
       user/lexer.c \
       $(DRIVERS)/startup/board_lowlevel.c \
       $(DRIVERS)/startup/board_stubs.c \
       $(DRIVERS)/lib/diskio.c \
       $(DRIVERS)/target.c \
       $(OSLIB)/kernellib.c $(OSLIB)/libc.c $(OSLIB)/vfs.c $(OSLIB)/termio.c \
       $(OSLIB)/fat.c

# List ASM source files here
ASRC = $(DRIVERS)/startup/board_cstartup.s

# List all user directories here
UINCDIR =include $(KERNEL) $(OSLIB) $(DRIVERS) $(DRIVERS)/include

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = $(DRIVERS)/lib/liblpc2148.a $(KERNEL)/libkernel.a
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
CFLAGS = $(INCDIR) $(MCFLAGS) $(DEBUG) $(OPT) -fomit-frame-pointer -Wall -ffunction-sections $(DEFS)
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

