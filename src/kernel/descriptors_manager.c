#include "descriptors_manager.h"

static gdt_ptr_t _gdt_ptr;

static void
setup_gdt_entry(gdt_entry_t *gdt_entries, uint32_t entry_number, uint32_t base, uint16_t limit, uint8_t access,
                uint8_t segment_high_and_granularity);

extern void load_gdt(gdt_ptr_t *gdt_ptr);

void setup_gdt_entries(gdt_entry_t *gdt_entries) {
    uint32_t gdt_ptr_value = (uint32_t) gdt_entries;
    setup_gdt_entry(gdt_entries, 0, 0, 0, 0, 0);
    setup_gdt_entry(gdt_entries, 1, 0, LOW_SEGMENT_LIMIT, CODE_RING_0_TYPE_DESCRIPTOR,
                    GRANURALITY_AND_SEGMENT_AND_SIZE_HIGH_SEGMENT_LIMIT);
    setup_gdt_entry(gdt_entries, 2, 0, LOW_SEGMENT_LIMIT, DATA_RING_0_TYPE_DESCRIPTOR,
                    GRANURALITY_AND_SEGMENT_AND_SIZE_HIGH_SEGMENT_LIMIT);
    setup_gdt_entry(gdt_entries, 3, 0, LOW_SEGMENT_LIMIT, CODE_RING_3_TYPE_DESCRIPTOR,
                    GRANURALITY_AND_SEGMENT_AND_SIZE_HIGH_SEGMENT_LIMIT);
    setup_gdt_entry(gdt_entries, 4, 0, LOW_SEGMENT_LIMIT, DATA_RING_3_TYPE_DESCRIPTOR,
                    GRANURALITY_AND_SEGMENT_AND_SIZE_HIGH_SEGMENT_LIMIT);
    _gdt_ptr.limit = NUMBER_OF_DESCRIPTORS * sizeof(struct gdt_entry_struct);
    _gdt_ptr.base = gdt_ptr_value;
    load_gdt(&_gdt_ptr);
}

static void
setup_gdt_entry(gdt_entry_t *gdt_entries, uint32_t entry_number, uint32_t base, uint16_t limit, uint8_t access,
                uint8_t segment_high_and_granularity) {
    gdt_entries[entry_number].limit_low = limit;
    gdt_entries[entry_number].base_low = base & LOW_MASK;
    gdt_entries[entry_number].base_middle = (base >> 16) & 0xFF;
    gdt_entries[entry_number].base_high = (base >> 24) & 0xFF;
    gdt_entries[entry_number].type_and_access = access;
    gdt_entries[entry_number].segment_high_and_granularity = segment_high_and_granularity;
}
