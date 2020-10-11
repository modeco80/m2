// Diagnostic console module.
// This is very basic and should only be used during very early boot.

#ifndef _DIAGCONS_H
#define _DIAGCONS_H

#include "kernel.h"

void DiagCons_Clear();

void DiagCons_SetColor(u8 color);

void DiagCons_Putc(char c);

void DiagCons_Puts(char* str);

#endif // _DIAGCONS_H