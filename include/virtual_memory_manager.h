#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include "types.h"


#define KERNEL_NUMBER_OF_PAGES_FOR_256MB_PHYSICAL_ALLOCATOR    0x2000
#define KERNEL_NUMBER_OF_PAGES_FOR_256MB    0x10000
#define NUMBER_OF_PAGE_DIRECTORY_ENTRIES    0x400
#define NUMBER_OF_PAGES_TABLES_ENTRIES  0x400
#define PAGE_SIZE   0x1000

typedef uint32_t physical_address;


typedef union {
    struct  {
        uint32_t present    : 1;
        uint32_t rw         : 1;
        uint32_t user       : 1;
        uint32_t pwt       : 1;
        uint32_t pcd       : 1;
        uint32_t accessed   : 1;
        uint32_t ignore   : 6;
        uint32_t frame      : 20;
    }pd_directory_t;

    struct  {
        uint32_t present    : 1;
        uint32_t rw         : 1;
        uint32_t user       : 1;
        uint32_t pwt       : 1;
        uint32_t pcd       : 1;
        uint32_t accessed   : 1;
        uint32_t dirty      : 1;
        uint32_t ignore     : 5;
        uint32_t frame      : 20;
    }pt_entry_t;

    physical_address address;
} address_union;


struct _physical_memory_allocator {
    uint8_t physical_pages[KERNEL_NUMBER_OF_PAGES_FOR_256MB];
    uint32_t physical_page_index;
    uint8_t bits_index;
}__attribute__((packed));

struct _virtual_page_memory_allocator {
    uint16_t pages_directory_index;
    uint16_t pages_table_index;
    uint32_t global_pages_index;
    physical_address page_tables_address;
    uint32_t *directory;
    uint32_t *tables;
};

typedef struct _virtual_page_memory_allocator virtual_page_memory_allocator_t;
typedef struct _physical_memory_allocator physical_memory_allocator_t;

void init_virtual_memory_page(physical_address page_directory, physical_address page_table);

extern void enable_page(physical_address directory);

#endif
