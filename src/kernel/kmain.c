#include <virtual_memory_manager.h>
#include "console.h"
#include "serial.h"
#include "string.h"
#include "descriptors_manager.h"
#include "interruption_handler.h"

char console_back_buffer[CONSOLE_BUFFER_SIZE];
char console_buffer[CONSOLE_BUFFER_SIZE];
struct kernel_params_struct {
    physical_address kernel_physical_memory_start;
    physical_address kernel_physical_memory_end;
    physical_address page_directory;
    physical_address page_table;
    physical_address stack_begin;
}__attribute__((packed));
typedef struct kernel_params_struct kernel_params;

void test_carlos_viera();

void kmain(kernel_params params) {
    gdt_entry_t gdt_entries[NUMBER_OF_DESCRIPTORS];
    setup_gdt_entries(gdt_entries);
    char_console console;
    char buffer[200];
    const char *test_serial_console_message = "carlos \nestos es una\t mierda\nno pasa nada";
    fill_empty(console_back_buffer, ROWS * COLUMNS);
    fill_empty(console_buffer, (ROWS * COLUMNS));
    init_console(&console, console_back_buffer, console_buffer);
    set_char_console_color(RED, BLACK);
    unsigned short com1 = COM1;
    configure_serial(com1, 2);
    write_serial_console(com1, test_serial_console_message, string_len(test_serial_console_message));
    itoa(params.kernel_physical_memory_start, buffer);
    write_text_to_char_console("Kernel Memory Address Start:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(params.kernel_physical_memory_end, buffer);
    write_text_to_char_console("Kernel Memory Address End:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(params.page_directory, buffer);
    write_text_to_char_console("Page directory address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(params.page_table, buffer);
    write_text_to_char_console("Page table address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(params.stack_begin, buffer);
    write_text_to_char_console("Stack address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");

    setup_interruption();
    init_virtual_memory_page(params.page_directory, params.page_table);
    while (1) {
        test_carlos_viera();
    }

}

void test_carlos_viera() {

}
