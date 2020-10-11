# sources file for the kernel

TARGET_NAME=kernel
BUILD_TARGET=executable
BUILD_COMP=freestanding

ADDL_CCFLAGS = -O2 -std=gnu99 -Wall -Wextra -I../libc/include
LDFLAGS = -T $(TARGET_ARCH)/kernel.ld -L../libc/kernel/obj/$(TARGET_ARCH) -lk  -ffreestanding -nostdlib -lgcc 

# Given here are X86 sources.
X86_SOURCES = \
	multiboot.asm \
	diagcons.c \
	ports.c \
	serial.c

# Generic sources.
SOURCES = \
	init.c \
	panic.c

	
