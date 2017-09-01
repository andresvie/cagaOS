#include <virtual_memory_manager.h>


static physical_memory_allocator_t physical_allocator;
static virtual_page_memory_allocator_t virtual_allocator;

static void init_physical_memory_allocator();

static void init_virtual_page_memory_allocator(page_directory *directory, page_table *page_tables,
                                               physical_address page_tables_address);

static void clear_page_directory(page_directory *directory);

static void clear_page_table(page_table *tables);

static void init_memory_for_kernel();

static void allocate_directory_page();

static int allocate_physical_memory(physical_address begin_address, physical_address end_address);

static void allocate_virtual_memory_page(physical_address memory_address);

void init_virtual_memory_page(physical_address page_directory_address, physical_address page_table_address) {
    page_directory *directory = (page_directory *) page_directory_address;
    page_table *page_tables = (page_table *) page_table_address;
    init_physical_memory_allocator();
    init_virtual_page_memory_allocator(directory, page_tables, page_table_address);
    init_memory_for_kernel();
    enable_page(page_directory_address);
}


static void init_memory_for_kernel() {
    physical_address begin_address = 0x0;
    physical_address end_address = 10 * 1024 * 1024;
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
    virtual_allocator.tables[page_index].frame = memory_address;
    virtual_allocator.tables[page_index].user = 1;
    virtual_allocator.tables[page_index].present = 1;
    virtual_allocator.tables[page_index].rw = 1;
    virtual_allocator.tables[page_index].user = 0;
    virtual_allocator.tables[page_index].present = 1;
    virtual_allocator.tables[page_index].present = 1;
    page_index++;
    if (page_index > NUMBER_OF_PAGES_TABLES_ENTRIES) {
        allocate_directory_page();
        page_index = 0;
    }
    virtual_allocator.pages_table_index = (uint16_t) (page_index);
}


static void allocate_directory_page() {
    uint16_t directory_index = virtual_allocator.pages_directory_index;
    physical_address page_base_address = virtual_allocator.page_tables_address + (directory_index * PAGE_SIZE);
    virtual_allocator.directory[directory_index].present = 1;
    virtual_allocator.directory[directory_index].rw = 1;
    virtual_allocator.directory[directory_index].user = 0;
    virtual_allocator.directory[directory_index].frame = page_base_address;
    virtual_allocator.pages_directory_index = (uint16_t) (directory_index + 1);
}

static void init_physical_memory_allocator() {
    physical_allocator.bits_index = 0;
    physical_allocator.physical_page_index = 0;
    uint32_t i = 0;
    for (; i < KERNEL_NUMBER_OF_PAGES_FOR_256MB; i++) {
        physical_allocator.physical_pages[0] = 0;
    }
}

static void init_virtual_page_memory_allocator(page_directory *directory, page_table *page_tables,
                                               physical_address page_tables_address) {
    clear_page_directory(directory);
    clear_page_table(page_tables);
    virtual_allocator.pages_directory_index = 0;
    virtual_allocator.pages_table_index = 0;
    virtual_allocator.directory = directory;
    virtual_allocator.tables = page_tables;
    virtual_allocator.page_tables_address = page_tables_address;
}


static void clear_page_directory(page_directory *directory) {
    uint32_t i = 0;
    for (; i < NUMBER_OF_PAGE_DIRECTORY_ENTRIES; i++) {
        directory->present = 0;
        directory->rw = 0;
        directory->user = 0;
        directory->pwt = 0;
        directory->pcd = 0;
        directory->accessed = 0;
        directory->ignore = 0;
        directory->frame = 0;
        directory++;
    }
}

static void clear_page_table(page_table *tables) {
    uint32_t i = 0;
    for (; i < KERNEL_NUMBER_OF_PAGES_FOR_256MB; i++) {
        tables->present = 0;
        tables->rw = 0;
        tables->user = 0;
        tables->pwt = 0;
        tables->pcd = 0;
        tables->accessed = 0;
        tables->dirty = 0;
        tables->ignore = 0;
        tables->frame = 0;
        ++tables;
    }
}