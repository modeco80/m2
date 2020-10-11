#include "serial.h"
#include "ports.h"

// TODO: The COM driver should probably fuck

void Kernel_Sys_InitCOM() {
	Kernel_Sys_OutB(COM1_PORT + 1, 0x0);
	Kernel_Sys_OutB(COM1_PORT + 3, 0x80);
	Kernel_Sys_OutB(COM1_PORT + 0, 0x3);
	
	Kernel_Sys_OutB(COM1_PORT + 1, 0x0);
	Kernel_Sys_OutB(COM1_PORT + 3, 0x3);
	Kernel_Sys_OutB(COM1_PORT + 2, 0xC7);
	Kernel_Sys_OutB(COM1_PORT + 4, 0x0B); 
}

static int _TransmitEmpty() {
	return Kernel_Sys_InB(COM1_PORT+5) & 0x20;
}

void Kernel_Sys_WriteCOM(u8 byte) {
	// spin until we can write
	while(_TransmitEmpty() == 0);
	
	
	Kernel_Sys_OutB(COM1_PORT, byte);
}