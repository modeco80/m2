#include <stdlib.h>

#ifdef _libk
#include "../../kernel/inc/kernel.h"
#endif

__attribute__((noreturn)) void abort() {
#ifdef _libk
	// TODO: abort() should cause a more descriptive panic

	Kernel_Panic("something in the kernel called libk abort()?");
#else
	
#endif
	while(1) {}
	__builtin_unreachable();
}
