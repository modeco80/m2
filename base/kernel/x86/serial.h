#include "../kernel.h"

#define COM1_PORT 0x3f8

void Kernel_Sys_InitCOM();

void Kernel_Sys_WriteCOM(u8 byte);