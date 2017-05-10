global load_gdt
load_gdt:
	mov eax,[esp + 4]
	lgdt [eax]
	mov ax,0x10
	mov ds,ax
	mov ss,ax
	mov fs,ax
	mov es,ax
	mov gs,ax
	jmp 0x08:set_code_segment
set_code_segment:
	ret
