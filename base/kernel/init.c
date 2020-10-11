#include "kernel.h"
#include "diagcons.h"

#ifdef _X86
	#include "x86/serial.h"
#endif

#include <stdlib.h>

// Kernel main entry point.
void Kernel_Entry(multiboot_info_t* MultibootImageInformation) {
	DiagCons_Clear();
	
#ifdef _X86
	// TODO for x86: We need to replace the GDT
	// that will be "fun"

	// Initalize serial hardware for a earlycon.
	Kernel_Sys_InitCOM();
#endif
	
	DiagCons_Puts("Kernel command line:");
	DiagCons_Puts((char*)MultibootImageInformation->cmdline);
	DiagCons_Puts("Do tabs work?\t Yes.");
	
	// this will test a libk call.
	abort();
}