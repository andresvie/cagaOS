global memcpy
memcpy:
  push ebp
  mov ebp,esp
  push ecx
  push edi
  push esi
  mov dword ecx,0
  mov ecx,[ebp + 0x10]
  mov edi,[ebp + 0x0c]
  mov esi,[ebp + 0x08]
  rep movsb
  mov eax,esi
  pop esi
  pop edi
  pop ecx
  pop ebp
  ret
