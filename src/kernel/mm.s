global enable_page
enable_page:
	mov eax,dword [esp + 4]
	mov cr3,eax
	mov eax,cr0
	or eax,0x80000000
	mov cr0,eax
	ret