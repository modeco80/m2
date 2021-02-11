; ------------------------------------------------
;	Multiboot boot code for M2
; ------------------------------------------------

; Subset of Multiboot1 stuff we use

MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map


MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

; This is moved in by a Multiboot1 compliant bootloader to the EAX register when 
; the kernel is initally jumped to
BOOT_MAGIC equ 0x2BADB002

; Define the Multiboot1 header here.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Provide a elementary stack for the kernel to use.
STACK_SIZE equ 16 * 1024

section .bss
align 16 
stack_bot:
	resb STACK_SIZE
stack_top:

section .text

; Externs from the c/c++ code we call
extern Kernel_Entry
extern DiagCons_Puts

global _kstart:function (_kstart.end - _kstart)

; Kernel (real) entry point
_kstart:
	mov esp, stack_top
	
	; Test first if we were *actually* booted via Multiboot.
	cmp eax, BOOT_MAGIC
	je .compatibility_test_successful
	
	; Multiboot test failed. Hang the machine,
	; but before so, display a string detailing why we decided to do so.
	push Error_Not_MultiBoot
	call DiagCons_Puts
	jmp ._stack_clean
	
.compatibility_test_successful:
	
	; EBX contains a pointer to the Multiboot information structure that the boot loader
	; is supposed to initalize. Push it as the one and sole argument to the kernel entry point
	push ebx

	call Kernel_Entry
	
	; I guess this isn't quite *required*, 
	; but we clean up the stack after the function returns, as
	; System V/x86 ABI requires the callee to clean up the stack.

._stack_clean:
	add esp, 4
	
.hang:
	cli
	hlt
	jmp .hang

.end:

; Kernel pre-boot strings are here
Error_Not_MultiBoot: 
	db "Boot Error: ", 0x0a, "This kernel needs a Multiboot compliant boot-loader to boot properly.", 0