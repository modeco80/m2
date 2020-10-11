// x86 implmentation of the diagcons

#include "../diagcons.h"
#include "vga.h"
#include "serial.h"

u8 _SerialEnabled = 0;

void Kernel_Sys_OutB(u16 port, u8 val);
u8 Kernel_Sys_InB(u16 port);


//u16* VGABuffer = ((u16*)0xB8000);

#define DIAGCONS_WIDTH 80
#define DIAGCONS_HEIGHT 25

u8 DiagCons_Color = 15;
int DiagCons_Column = 0;
int DiagCons_Row = 0;

u16 _DiagCons_MakeAttributedChar(char c) {
	return c | DiagCons_Color << 8;
}

void _DiagCons_PutCharAt(char c, u8 x, u8 y) {
	VGABuffer[y*80+x] = _DiagCons_MakeAttributedChar(c);
}


void DiagCons_Clear() {
	// Disable the cursor, it's annoying
	Kernel_Sys_OutB(0x3D4, 0x0A);
	Kernel_Sys_OutB(0x3D5, 0x20);
	
	for(int x = 0; x < DIAGCONS_WIDTH; ++x)
		for(int y = 0; y < DIAGCONS_HEIGHT; ++y)
				_DiagCons_PutCharAt(' ', x, y);
			
	DiagCons_Column = 0;
	DiagCons_Row = 0;
}

void DiagCons_SetDiagCons_Color(u8 color) {
	DiagCons_Color = color;
}

void DiagCons_Putc(char c) {
	// test
	Kernel_Sys_WriteCOM(c);
	
	if(c == '\r') {
		DiagCons_Column = 0;
		return;
	} else if(c == '\n') {
		DiagCons_Column = 0;
		DiagCons_Row++;
		return; 
	} else if(c == '\t') {
		DiagCons_Column += 4;
		return;
	} else {
		_DiagCons_PutCharAt(c, DiagCons_Column, DiagCons_Row);
	}
	
	if(++DiagCons_Column == 80) {
		DiagCons_Column = 0;
		if(++DiagCons_Row == 25)
			DiagCons_Row = 0;
	}
}

void DiagCons_Puts(char* str) {
	char* StrIt = str;
	
	// while the Libk could have a strlen() this works ok
	while(1) {
		if(*StrIt == '\0')
			break;
		
		DiagCons_Putc(*StrIt);
		++StrIt;
	}
	
	// Mimicking the real thing, put a newline in
	DiagCons_Putc('\n');
}