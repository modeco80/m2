#############################################
# Standardized build system for making
# a OS component
##############################################

# vpath fun
TOP = $(PWD)
VPATH = $(TOP) $(TOP)/$(TARGET_ARCH) ../ ../$(TARGET_ARCH)

# include the sources first
include ./Sources.inc

# Include the specific defs file
ifeq ($(OS_ARCH),)
include $(ToolsDir)/Defs.$(OS_ARCH)
else
# assume x86
include $(ToolsDir)/Defs.x86
endif

ifeq ($(BUILD_COMP), freestanding)
CCFLAGS = -ffreestanding $(TARGET_DEFINES) $(ADDL_CCFLAGS)
else
CCFLAGS = $(ADDL_CCFLAGS) $(TARGET_DEFINES)
endif


CORRECTED_SOURCES = $(shell echo $(SOURCES) | sed 's/\.\.\///g')


# Tell make that the virtual targets we have
# are in fact not dependent on files.
.PHONY: all build post

all: build post

$(O):
	@mkdir -p $@

# TODO: We need A crt executable
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
$(error Invalid build target $(BUILD_TARGET) - it can be any one of the following: executable, staticlib)
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

clean:
	-rm -rf $(O) obj
