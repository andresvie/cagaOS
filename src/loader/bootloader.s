global loader
STACK_SIZE	equ 4096
MAGIC_NUMBER	equ 0x1BADB002
FLAGS	equ	0x0
CHECKSUM	equ -MAGIC_NUMBER
extern kmain
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
	mov esp,stack_begin + STACK_SIZE
	call kmain
.loop:
	jmp .loop

