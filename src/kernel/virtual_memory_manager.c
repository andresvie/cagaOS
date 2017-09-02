#include <virtual_memory_manager.h>


static physical_memory_allocator_t physical_allocator;
static virtual_page_memory_allocator_t virtual_allocator;

static void init_physical_memory_allocator();

static void init_virtual_page_memory_allocator(uint32_t *directory, uint32_t *page_tables,
                                               physical_address page_tables_address);

static void clear_page_directory(uint32_t *directory);

static void clear_page_table(uint32_t *tables);

static void init_memory_for_kernel();

static void allocate_directory_page();

static int allocate_physical_memory(physical_address begin_address, physical_address end_address);

static void allocate_virtual_memory_page(physical_address memory_address);

void init_virtual_memory_page(physical_address page_directory_address, physical_address page_table_address) {
    uint32_t *directory = (uint32_t *) page_directory_address;
    uint32_t *page_tables = (uint32_t *) page_table_address;
    init_physical_memory_allocator();
    init_virtual_page_memory_allocator(directory, page_tables, page_table_address);
    init_memory_for_kernel();
    enable_page(page_directory_address);

}


static void init_memory_for_kernel() {
    physical_address begin_address = 0x0;
    physical_address end_address = 16 * 1024 * 1024;
    allocate_directory_page();
    allocate_physical_memory(begin_address, end_address);
}


static int allocate_physical_memory(physical_address begin_address, physical_address end_address) {
    physical_address memory_address = begin_address;
    while (memory_address < end_address) {
        allocate_virtual_memory_page(memory_address);
        memory_address += PAGE_SIZE;
    }
    return 0;
}

static void allocate_virtual_memory_page(physical_address memory_address) {
    uint16_t page_index = virtual_allocator.pages_table_index;
    uint32_t global_index = virtual_allocator.global_pages_index;
    address_union address;
    address.address = memory_address;
    address.pt_entry_t.present = 1;
    address.pt_entry_t.rw = 1;
    address.pt_entry_t.user = 0;
    virtual_allocator.tables[global_index] = address.address;
    page_index++;
    global_index++;
    if (page_index >= NUMBER_OF_PAGES_TABLES_ENTRIES) {
        allocate_directory_page();
        page_index = 0;
    }
    virtual_allocator.pages_table_index = page_index;
    virtual_allocator.global_pages_index = global_index;
}


static void allocate_directory_page() {
    uint16_t directory_index = virtual_allocator.pages_directory_index;
    physical_address page_base_address = virtual_allocator.page_tables_address + (directory_index * PAGE_SIZE);
    address_union address;
    address.address = page_base_address;
    address.pd_directory_t.user = 0;
    address.pd_directory_t.present = 1;
    address.pd_directory_t.rw = 1;
    virtual_allocator.directory[directory_index] = address.address;
    virtual_allocator.pages_directory_index = (uint16_t) (directory_index + 1);
}

static void init_physical_memory_allocator() {
    physical_allocator.bits_index = 0;
    physical_allocator.physical_page_index = 0;
    uint32_t i = 0;
    for (; i < KERNEL_NUMBER_OF_PAGES_FOR_256MB_PHYSICAL_ALLOCATOR; i++) {
        physical_allocator.physical_pages[0] = 0;
    }
}

static void init_virtual_page_memory_allocator(uint32_t *directory, uint32_t *page_tables,
                                               physical_address page_tables_address) {
    clear_page_directory(directory);
    clear_page_table(page_tables);
    virtual_allocator.pages_directory_index = 0;
    virtual_allocator.pages_table_index = 0;
    virtual_allocator.global_pages_index = 0;
    virtual_allocator.directory = directory;
    virtual_allocator.tables = page_tables;
    virtual_allocator.page_tables_address = page_tables_address;
}


static void clear_page_directory(uint32_t *directory) {
    uint32_t i = 0;
    for (; i < NUMBER_OF_PAGE_DIRECTORY_ENTRIES; i++) {
        directory[i] = 0;
        directory++;
    }
}

static void clear_page_table(uint32_t *tables) {
    uint32_t i = 0;
    for (; i < KERNEL_NUMBER_OF_PAGES_FOR_256MB; i++) {
        tables[0] = 0;
        ++tables;
    }
}