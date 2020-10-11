#
# Template makefile for using the master
# Dazzle makefile.
#
include $(ToolsDir)/Makefile.os

# This target tests the kernel image using QEMU.
test: $(O)/$(TARGET_NAME)
	qemu-system-i386 -serial stdio -kernel $< -append TestCmdLineBuffer