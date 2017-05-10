#include "serial.h"
static int is_serial_ready_to_write(unsigned short com);

static void write_serial_data_until_is_empty(unsigned short com, char data);
static void configure_serial_baud_rate(unsigned short com, unsigned short divisor);
static void configure_serial_line(unsigned short com);
static void configure_serial_buffer(unsigned short com);
static void configure_serial_modem(unsigned short com);


void write_serial_console(unsigned short com, const char *message, int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		write_serial_data_until_is_empty(com, message[i]);
	}
}

void configure_serial(unsigned short com, unsigned short divisor)
{
	configure_serial_baud_rate(com, divisor);
	configure_serial_line(com);
	configure_serial_buffer(com);
	configure_serial_modem(com);
}

static void configure_serial_baud_rate(unsigned short com, unsigned short divisor)
{
	write_port(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	write_port(SERIAL_DATA_PORT(com), divisor>>8 & 0x00FF);
	write_port(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

static  void configure_serial_line(unsigned short com)
{
	write_port(SERIAL_LINE_COMMAND_PORT(com), SERIAL_CONFIGURE_LINE_FLAGS);
}

static void configure_serial_buffer(unsigned short com)
{
	write_port(SERIAL_FIFO_COMMAND_PORT(com), SERIAL_CONFIGURE_BUFFER_FLAGS);
}

static void configure_serial_modem(unsigned short com)
{
	write_port(SERIAL_MODEM_COMMAND_PORT(com), SERIAL_CONFIGURE_MODEM);
}

static void write_serial_data_until_is_empty(unsigned short com, char data)
{
	while(!is_serial_ready_to_write(com))
	{
		continue;
	}
	write_port(SERIAL_DATA_PORT(com), data);
}

static int is_serial_ready_to_write(unsigned short com)
{
	return read_port(SERIAL_LINE_STATUS_PORT(com)) & EMPTY_TRANSMITTER_HOLDING_REGISTER;
}
