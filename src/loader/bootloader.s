global loader
STACK_SIZE	equ 4096
MAGIC_NUMBER	equ 0x1BADB002
FLAGS	equ	0x0
CHECKSUM	equ -MAGIC_NUMBER
extern kmain
extern kernel_physical_memory_start
extern kernel_physical_memory_end
section .bss
align 4
stack_begin:
	resb STACK_SIZE
section .text
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM
loader:
    mov eax,stack_begin
    add eax,STACK_SIZE
	mov esp,eax
	push dword kernel_physical_memory_end
	push dword kernel_physical_memory_start
	call kmain
.loop:
	jmp .loop

