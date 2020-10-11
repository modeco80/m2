#include <stdlib.h>

#ifdef _libk
#include "../kernel/kernel.h"
#endif

__attribute__((noreturn)) void abort() {
#ifdef _libk
	// TODO: abort() should cause a fuck
	Kernel_Panic("something in the kernel called libk abort()?");
#else
	
#endif
	while(1) {}
	__builtin_unreachable();
}