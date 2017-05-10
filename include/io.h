#ifndef PORT_H
#define PORT_H
extern void write_port(unsigned short port, unsigned char data);
extern unsigned char read_port(unsigned short port);
#define FRAME_COMMAND_PORT 0x3D4
#define FRAME_DATA_PORT 0x3D5
#define FRAME_BUFFER_SEND_HIGHT_BITS_COMMAND	0xE
#define FRAME_BUFFER_SEND_LOW_BITS_COMMAND	0xF
#endif
