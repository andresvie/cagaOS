extern  interrupt_handler
global load_idt
global interruption_handler_default
load_idt:
  mov eax,[esp+4]
  lidt [eax]
  sti
  ret



interruption_handler_default:
  push dword 0x0
  push dword 0xFFFF
  jmp general_interruption_handler

%macro interruption_handler_with_no_error 1
  global interruption_handler_%1
  interruption_handler_%1:
    push dword 0x0
    push dword %1
    jmp general_interruption_handler
%endmacro

%macro interruption_handler_with_error 1
  global interruption_handler_number_%1
  interruption_handler_number_%1:
    push dword %1
    jmp general_interruption_handler
%endmacro

general_interruption_handler:
  push edi
  push esi
  push ebp
  push edx
  push ecx
  push ebx
  push eax
  push ds
  push ebx
  mov bx,0x10
  mov ds,bx
  pop ebx
  call interrupt_handler
  mov 	al, 0x20
  out 	0x20, al
  pop ds
  pop eax
  pop ebx
  pop ecx
  pop edx
  pop ebp
  pop esi
  pop edi
  add esp,0x08
  iret
interruption_handler_with_no_error 32
interruption_handler_with_no_error 33
