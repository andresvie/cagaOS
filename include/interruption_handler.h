#ifndef INTERUPTION_HANDLER_H
#define INTERUPTION_HANDLER_H
#include "types.h"
#define INTERRUPTION_CODE_RING_0 0x0
#define IS_INTERRUPTION_PRESENT_IN_MEMORY 0x1
#define IS_INTERRUPTION_GATE_32_BIT_SIZE 0x1
#define INTERUPTION_DESCRIPTOR_PRIVILEGE_RING (INTERRUPTION_CODE_RING_0 << 5)
#define INTERUPTION_PRESENT_IN_MEMORY (IS_INTERRUPTION_PRESENT_IN_MEMORY << 7)
#define INTERRUPTION_GATE_SIGNATURE 0x6
#define INTERRUPTION_GATE_SIZE_32 (IS_INTERRUPTION_GATE_32_BIT_SIZE << 3)
#define INTERUPTION_HANDLER_ATTRIBUTES (INTERRUPTION_GATE_SIZE_32 | INTERUPTION_DESCRIPTOR_PRIVILEGE_RING | INTERUPTION_PRESENT_IN_MEMORY | INTERRUPTION_GATE_SIGNATURE)
#define CODE_DESCRIPTOR 0x08
struct interruption_entry_struct{
  uint16_t offset_low;
  uint16_t code_descriptor;
  uint8_t zero;
  uint8_t attr;
  uint16_t offset_high;
}__attribute__((packed));

struct cpu_state_struct{
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebp;
  uint32_t esp;
  uint32_t esi;
  uint32_t edi;
}__attribute__((packed));

struct interruption_state_struct{
  uint_32_t eip;
  uint32_t cs;
  uint_32_t eflags;
  uint_32_t error_code;
  uint_32_t inturruption_number;
}__attribute__((packed));

typedef struct cpu_state_struct cpu_state;
typedef struct interruption_state_struct interruption_state;
void interrupt_handler(interruption_state interruption_state, cpu_state cpu);

struct interruption_register_struct{
  uint16_t limit_in_bytes;
  uint32_t interruption_table_address;
}__attribute__((packed));

typedef struct interruption_entry_struct interruption_entry;
typedef struct interruption_register_struct interruption_register;
#endif INTERUPTION_HANDLER_H
