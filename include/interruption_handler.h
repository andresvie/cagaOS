#ifndef INTERUPTION_HANDLER_H
#define INTERUPTION_HANDLER_H

#include "types.h"
#include "pic_manager.h"
#include "console.h"

#define NUMBER_OF_INTERRUPTIONS 0xFF
#define INTERRUPTION_HANDLER_ATTR 0x8E
#define CODE_DESCRIPTOR 0x08

extern void interruption_handler_default();

extern void interruption_handler_33();

extern void interruption_handler_32();

extern void interruption_handler_13();

extern void interruption_handler_14();

#define CLOCK_INTERRUPTION (uint32_t)interruption_handler_32
#define KEYBOARD_INTERRUPTION (uint32_t)interruption_handler_33
#define GENERAL_PROTECTION_EXCEPTION (uint32_t)interruption_handler_13
#define PAGE_FAULT (uint32_t)interruption_handler_14

#define CLOCK_INTERRUPTION_NUMBER 0x20

struct interruption_entry_struct {
    uint16_t offset_low;
    uint16_t code_descriptor;
    uint8_t zero;
    uint8_t attr;
    uint16_t offset_high;
}__attribute__((packed));

struct interruption_register_struct {
    uint16_t limit_in_bytes;
    uint32_t interruption_table_address;
}__attribute__((packed));

struct cpu_state_struct {
    uint32_t cr2;
    uint32_t cr3;
    uint32_t cr4;
    uint16_t ds;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
}__attribute__((packed));

struct interruption_state_struct {
    uint32_t interruption_number;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
}__attribute__((packed));

typedef struct cpu_state_struct cpu_state;

typedef struct interruption_state_struct interruption_state;

typedef struct interruption_entry_struct interruption_entry;

typedef struct interruption_register_struct interruption_register;

void interrupt_handler(cpu_state cpu, interruption_state irq_state);

void handler_keyboard_interruption();

void handler_timer_interruption();

void setup_interruption();

extern void load_idt(interruption_register *re);

#endif
