#ifndef DESCRIPTORS_MANAGER
#define DESCRITORS_MANAGER

#include "types.h"

#define NUMBER_OF_DESCRIPTORS 0x5
#define LOW_MASK    0x0000FFFF
#define DATA_RING_0_TYPE_DESCRIPTOR    0x92
#define CODE_RING_0_TYPE_DESCRIPTOR    0x9A
#define CODE_RING_3_TYPE_DESCRIPTOR    0xFA
#define DATA_RING_3_TYPE_DESCRIPTOR    0xF2
#define GRANURALITY_AND_SEGMENT_AND_SIZE_HIGH_SEGMENT_LIMIT    0XCF
#define LOW_SEGMENT_LIMIT    0xFFFF

struct gdt_entry_struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t type_and_access;
    uint8_t segment_high_and_granularity;
    uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void setup_gdt_entries(gdt_entry_t *gdt_entries);

#endif
