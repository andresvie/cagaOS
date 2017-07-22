#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "console.h"
#include "strings.h"
#include "io.h"
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_CONTROL_PORT 0x64
#define IS_KEY_RELEASED(scan_code)  (((scan_code & 0x80) != 0x0))
void handler_keyboard_interruption(char_console *console);
#endif
