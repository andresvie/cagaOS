#include "console.h"
#include "io.h"
#include "serial.h"
#include "string.h"
#include "descriptors_manager.h"
#include "interruption_handler.h"
void test_carlos_viera();
int kmain()
{
	gdt_entry_t gdt_entries[NUMBER_OF_DESCRIPTORS];
	setup_gdt_entries(gdt_entries);
	const char *test_serial_console_message = "carlos \nestos es una\t mierda\nno pasa nada";
	init_console();
	set_char_console_color(RED,BLACK);		
	unsigned short com1 = COM1;
	configure_serial(com1, 2);
	write_serial_console(com1, test_serial_console_message, string_len(test_serial_console_message));
	setup_interruption();
	while(1){
		test_carlos_viera();
	}
	return 15;
}
void test_carlos_viera(){

}
