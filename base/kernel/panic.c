#include "diagcons.h"

__attribute__((noreturn))
void Kernel_Panic(char* reason) {
	DiagCons_Clear();
	//DiagCons_SetColor(8); add when implemented
	DiagCons_Puts("Kernel panic....");
	
	// spin forever
	while(1);
}