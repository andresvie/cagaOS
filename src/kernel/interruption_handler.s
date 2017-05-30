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
  push esp
  push ebp
  push edx
  push ecx
  push ebx
  push eax
  call interrupt_handler
  pop eax
  pop ebx
  pop ecx
  pop edx
  pop ebp
  pop esp
  pop esi
  pop edi
  add esp,8
  iret
