// x86 specific structures
// placed here so that the task switching system can (hopefully)
// be made generic relatively easily
#ifndef _X86CPU_H
#define _X86CPU_H

#include <kernel.h>


// all registers that we need to push/pop
// when a interrupt occurs
typedef struct {
	
	
	
} saveregs_t;

#endif