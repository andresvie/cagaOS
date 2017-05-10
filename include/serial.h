#ifndef SERIAL_H
#define SERIAL_H
#include "io.h"
#define COM1	0x3F8
#define SERIAL_DATA_PORT(base)	(base)
#define SERIAL_FIFO_COMMAND_PORT(base)	(base+2)
#define SERIAL_LINE_COMMAND_PORT(base)	(base+3)
#define SERIAL_MODEM_COMMAND_PORT(base)	(base+4)
#define SERIAL_LINE_STATUS_PORT(base)	(base+5)
#define SERIAL_LINE_ENABLE_DLAB 0x80
#define SERIAL_CONFIGURE_LINE_FLAGS 0x03
#define SERIAL_CONFIGURE_BUFFER_FLAGS	0xC7
#define SERIAL_CONFIGURE_MODEM	0x03
#define EMPTY_TRANSMITTER_HOLDING_REGISTER    0x20
#define DATA_READY_STATUS	0x1
void configure_serial(unsigned short com, unsigned short divisor);
void write_serial_console(unsigned short com, const char *message, int length);
#endif
