global write_port,read_port
write_port:
	mov al,[esp + 8]
	mov dx,[esp + 4]
	out dx,al	
	ret
read_port:
	mov dx,[esp + 4]
	in al,dx
	ret
