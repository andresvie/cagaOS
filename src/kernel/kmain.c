#include "console.h"
#include "io.h"
#include "serial.h"
#include "string.h"
#include "descriptors_manager.h"
#include "interruption_handler.h"
char console_back_buffer[CONSOLE_BUFFER_SIZE];
char console_buffer[CONSOLE_BUFFER_SIZE];
void test_carlos_viera();
int kmain()
{
	gdt_entry_t gdt_entries[NUMBER_OF_DESCRIPTORS];
	setup_gdt_entries(gdt_entries);
	char_console console;
	const char *test_serial_console_message = "carlos \nestos es una\t mierda\nno pasa nada";
	const char *test_console="Viera\nMosquera\nQue\nMierda\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAja\n";
	fill_empty(console_back_buffer,  ROWS * COLUMNS);
	fill_empty(console_buffer,  (ROWS * COLUMNS));
	init_console(&console, console_back_buffer, console_buffer);
	set_char_console_color(RED,BLACK);
	unsigned short com1 = COM1;
	configure_serial(com1, 2);
	write_serial_console(com1, test_serial_console_message, string_len(test_serial_console_message));
	setup_interruption();
	write_text_to_char_console(test_console);
	while(1){
		test_carlos_viera();
	}
	return 15;
}
void test_carlos_viera(){

}
