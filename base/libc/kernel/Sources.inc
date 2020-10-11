# sources file for the kernel libc (libk)

TARGET_NAME=k
BUILD_TARGET=staticlib
BUILD_COMP=freestanding

# We add a define to tell libc sources they are actually compiling libk
ADDL_CCFLAGS = -O2 -std=gnu99 -Wall -Wextra -I../include -D_libk

# Given here are X86 sources.
X86_SOURCES = \
	crtn.asm

# Generic sources.
SOURCES = \
	../abort.c

	
