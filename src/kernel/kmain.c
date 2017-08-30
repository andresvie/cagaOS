#include "console.h"
#include "serial.h"
#include "string.h"
#include "descriptors_manager.h"
#include "interruption_handler.h"

char console_back_buffer[CONSOLE_BUFFER_SIZE];
char console_buffer[CONSOLE_BUFFER_SIZE];

void test_carlos_viera();

void kmain(uint32_t kernel_physical_memory_start, uint32_t kernel_physical_memory_end, uint32_t page_directory,
           uint32_t page_table,uint32_t stack_begin) {
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
    itoa(kernel_physical_memory_start, buffer);
    write_text_to_char_console("Kernel Memory Address Start:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(kernel_physical_memory_end, buffer);
    write_text_to_char_console("Kernel Memory Address End:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(page_directory, buffer);
    write_text_to_char_console("Page directory address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(page_table, buffer);
    write_text_to_char_console("Page table address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");
    itoa(stack_begin, buffer);
    write_text_to_char_console("Stack address:");
    write_text_to_char_console(buffer);
    write_text_to_char_console("\n");

    setup_interruption();

    while (1) {
        test_carlos_viera();
    }

}

void test_carlos_viera() {

}
