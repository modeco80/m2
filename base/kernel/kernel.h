#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef int8_t s8;

typedef uint16_t u16;
typedef int16_t s16;

typedef uint32_t u32;
typedef int32_t s32;

typedef uint64_t u64;
typedef int64_t s64;


// This small bit of the multiboot structure
// is what we bother to use. 
typedef struct {
	u32 flags;
	u32 mem_lower;
	u32 mem_upper;
	
	u32 boot_dev;
	
	// this is actually a char*
	u32 cmdline;
} multiboot_info_t;

// System-independent kernel routines go here..

__attribute__((noreturn))
void Kernel_Panic(char* reason);

#endif