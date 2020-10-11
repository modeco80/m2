# generic makefile for building OS components

# We deeply assume x86 in pretty much all cases
# however this makefile is designed to (maybe) allow multiple architechures?
TARGET_ARCH = x86

ifeq ($(TARGET_ARCH), x86)
TC = i686-elf
ASM = nasm -f elf32
endif

CC = $(TC)-gcc
LD = $(TC)-gcc
AR = $(TC)-ar
O = obj/$(TARGET_ARCH)

include ./Sources.inc
ifeq ($(BUILD_COMP), freestanding)
CCFLAGS = -ffreestanding -D_X86 $(ADDL_CCFLAGS)
else
CCFLAGS = $(ADDL_CCFLAGS)
endif


CORRECTED_SOURCES = $(shell echo $(SOURCES) | sed 's/\.\.\///g')

ifeq ($(TARGET_ARCH), x86)

CORRECTED_X86_SOURCES = $(X86_SOURCES:../=)

X86_ASM_SOURCES = $(CORRECTED_X86_SOURCES:%.c=)
X86_C_SOURCES = $(CORRECTED_X86_SOURCES:%.asm=)

OBJS=$(CORRECTED_SOURCES:%.c=$(O)/%.o) $(X86_ASM_SOURCES:%.asm=$(O)/%.o) $(X86_C_SOURCES:%.c=$(O)/%.o)
else
OBJS=$(CORRECTED_SOURCES:%.c=$(O)/%.o)
endif

# Tell make that the virtual targets we have
# are in fact not dependent on files.
.PHONY: all build post

all: build post

$(O):
	@mkdir -p $@

ifeq ($(BUILD_TARGET), executable)

build: $(O)/$(TARGET_NAME)

$(O)/$(TARGET_NAME): $(O) $(OBJS)
	$(info Linking executable $@ for $(TARGET_ARCH))
	@$(LD) $(CCFLAGS) $(OBJS) $(LDFLAGS) -o $@
ifneq ($(BUILD_PLACE), no)
	$(info Placing $@ into system root)
	@place $@
endif
else

ifeq ($(BUILD_TARGET), staticlib)
build: $(O)/lib$(TARGET_NAME).a

# Reformed to allow this to work
$(O)/lib$(TARGET_NAME).a: $(O) $(OBJS)
	$(info Creating library $@ for $(TARGET_ARCH))
	@$(AR) r $@ $(OBJS)
else
$(error Invalid BUILD_TARGET $(BUILD_TARGET))
endif

endif

$(O)/%.o: $(TARGET_ARCH)/%.asm
	$(info Assembling $< for $(TARGET_ARCH))
	@$(ASM) $< -o $@

# Arch-specific C code
$(O)/%.o: $(TARGET_ARCH)/%.c
	$(info Compiling C source $< for $(TARGET_ARCH))
	@$(CC) -c $< $(CCFLAGS) -o $@
	
$(O)/%.o: %.c
	$(info Compiling C source $< for $(TARGET_ARCH))
	@$(CC) -c $< $(CCFLAGS) -o $@

# a very very bad	
# hack for libk & other "multiple-target" things

$(O)/%.o: ../$(TARGET_ARCH)/%.asm
	$(info Assembling $< for $(TARGET_ARCH))
	@$(ASM) $< -o $@

$(O)/%.o: ../$(TARGET_ARCH)/%.c
	$(info Compiling C source $< for $(TARGET_ARCH))
	@$(CC) -c $< $(CCFLAGS) -o $@

$(O)/%.o: ../%.c
	$(info Compiling C source $< for $(TARGET_ARCH))
	@$(CC) -c $< $(CCFLAGS) -o $@

clean:
	-rm -rf $(O) obj