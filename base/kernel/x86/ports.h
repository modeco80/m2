//
// Deals with I/O ports on x86.
//

#ifndef _PORTS_H
#define _PORTS_H

#include "../kernel.h"

void Kernel_Sys_OutB(u16 port, u8 val);

u8 Kernel_Sys_InB(u16 port);

#endif