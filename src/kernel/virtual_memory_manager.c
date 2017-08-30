#include "virtual_memory_manager.h"

uint8_t physical_pages[NUMBER_OF_PAGES_IN_BIT_MAP];

static void clear_physical_memory_pages();

void init_virtual_memory_page() {
    clear_physical_memory_pages();
}

static void clear_physical_memory_pages() {
    uint32_t i = 0;
    for (; i < NUMBER_OF_PAGES_IN_BIT_MAP; i++) {
        physical_pages[0] = 0;
    }
}


void add_page_directory_attributes(pd_entry_t *e, uint32_t attrs) {
    *e = *e | attrs;
}

void delete_page_directory_attributes(pd_entry_t *e, uint32_t attrs) {
    *e = *e & (~attrs);
}

bool is_page_directory_present(pd_entry_t e) {
    bool is_present = (bool) ((IS_PAGE_DIRECTORY_PRESENT & e) != 0x0);
    return is_present;
}

bool is_page_directory_writable(pd_entry_t e) {
    bool can_write = (bool) ((PAGE_DIRECTORY_WRITABLE_MEMORY & e) != 0x0);
    return can_write;
}

physical_address get_page_directory_frame_physical_address(pd_entry_t e) {
    return (physical_address) (e & PAGE_DIRECTORY_FRAME);
}

void set_page_directory_frame_physical_address(pd_entry_t *e, physical_address address) {
    *e = (*e | (PAGE_DIRECTORY_FRAME & address));
}


void add_page_attributes(pt_entry_t *e, uint32_t attrs) {
    *e = *e | attrs;
}

void delete_page_attributes(pt_entry_t *e, uint32_t attrs) {
    *e = *e & (~attrs);
}

bool is_page_writable(pt_entry_t e) {
    bool can_write = (bool) ((e & PAGE_WRITABLE_MEMORY) != 0);
    return can_write;
}

bool is_page_present(pt_entry_t e) {
    bool is_present = (bool) ((IS_PAGE_PRESENT & e) != 0x0);
    return is_present;
}

bool is_page_dirty(pt_entry_t e) {
    bool is_dirty = (bool) ((IS_PAGE_DIRTY & e) != 0x0);
    return is_dirty;
}

physical_address get_page_frame_physical_address(pt_entry_t e) {
    return (physical_address) (e & PAGE_FRAME_MASK);
}

void set_page_table_frame_physical_address(pt_entry_t *e, physical_address p) {
    *e = (*e | (p & PAGE_FRAME_MASK));
}