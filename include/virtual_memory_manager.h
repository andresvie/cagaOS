#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include "types.h"

#define IS_PAGE_PRESENT 0x01
#define PAGE_WRITABLE_MEMORY 0x02
#define USER_MODE_PAGE 0x04
#define PAGE_WAS_ACCESSED 0x20
#define IS_PAGE_DIRTY 0x40
#define PAGE_FRAME_MASK 0x7FFFF000
#define NUMBER_OF_PAGES_IN_BIT_MAP 0x2000
#define IS_PAGE_DIRECTORY_PRESENT 0x1
#define PAGE_DIRECTORY_WRITABLE_MEMORY 0x02
#define PAGE_DIRECTORY_USER_MODE_PAGE 0x04
#define PAGE_DIRECTORY_PWT 0x08
#define PAGE_DIRECTORY_WAS_ACCESSED 0x20
#define IS_PAGE_DIRECTORY_DIRTY 0x40
#define PAGE_DIRECTORY_4MB 0x80
#define PAGE_DIRECTORY_CPU_GLOBAL 0x100
#define PAGE_DIRECTORY_LV4_GLOBAL 0x200
#define PAGE_DIRECTORY_FRAME 0x7FFFF000

#define KERNEL_BEGIN_INITIAL_MEMORY 0x0
#define KERNEL_END_INITIAL_MEMORY 0xa00000

typedef uint32_t pt_entry_t;
typedef uint32_t pd_entry_t;
typedef uint32_t physical_address;


typedef struct {
    pt_entry_t pages[1024];
} page_table_t;

typedef struct {
    pd_entry_t directories[1024];
} page_directory_t;

void init_virtual_memory_page();

void add_page_directory_attributes(pd_entry_t *e, uint32_t attrs);

void delete_page_directory_attributes(pd_entry_t *e, uint32_t attrs);

bool is_page_directory_present(pd_entry_t e);

bool is_page_directory_writable(pd_entry_t e);

physical_address get_page_directory_frame_physical_address(pd_entry_t e);

void set_page_directory_frame_physical_address(pd_entry_t *e, physical_address address);


void add_page_attributes(pt_entry_t *e, uint32_t attrs);

void delete_page_attributes(pt_entry_t *e, uint32_t attrs);

bool is_page_writable(pt_entry_t e);

bool is_page_present(pt_entry_t e);

bool is_page_dirty(pt_entry_t e);

physical_address get_page_frame_physical_address(pt_entry_t e);

void set_page_table_frame_physical_address(pt_entry_t *e, physical_address p);

physical_address get_physical_page_avaible();

#endif
