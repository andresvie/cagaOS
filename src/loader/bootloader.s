global loader
STACK_SIZE	equ 4096
PAGE_DIRECTORY_SIZE equ 0x1000
PAGE_TABLE_SIZE equ 0x400000
MAGIC_NUMBER	equ 0x1BADB002
FLAGS	equ	0x0
CHECKSUM	equ -MAGIC_NUMBER
extern kmain
extern kernel_physical_memory_start
extern kernel_physical_memory_end
section .bss
align 4096
start_page_directory:
    resb PAGE_DIRECTORY_SIZE
align 4096
start_page_table:
    resb PAGE_TABLE_SIZE
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
	push dword stack_begin
	push dword start_page_table
	push dword start_page_directory
	push dword kernel_physical_memory_end
	push dword kernel_physical_memory_start

	call kmain
.loop:
	jmp .loop

