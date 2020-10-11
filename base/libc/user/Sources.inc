# sources file for the user libc

TARGET_NAME=c
BUILD_TARGET=staticlib
BUILD_COMP=freestanding

# We add a define to tell libc sources they are actually compiling libc
ADDL_CCFLAGS = -O2 -std=gnu99 -Wall -Wextra -I../include -D_libc

# Given here are X86 sources.
X86_SOURCES = 

# Generic sources.
SOURCES = \
	../abort.c

	
