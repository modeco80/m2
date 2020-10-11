//
// Deals with I/O ports on x86.
//

#include "../kernel.h"


void Kernel_Sys_OutB(u16 port, u8 val) {
	asm volatile(
		"outb %0, %1" : : "a"(val), "Nd"(port)
	);
}

u8 Kernel_Sys_InB(u16 port) {
	u8 v;
	asm volatile(
		"inb %1, %0" : "=a"(v) : "Nd"(port)
	);
	return v;
}