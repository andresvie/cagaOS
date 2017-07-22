#ifndef CONSOLE_H
#define CONSOLE_H
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTE 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xa
#define LIGHT_CYAN 0xb
#define LIGHT_RED 0xc
#define LIGHT_MAGENTA 0xd
#define LIGHT_BROWN 0xe
#define WHITE 0xf
#define FRAME_BUFFER_ADDRESS 0x000b8000
#define TAB_LEN 4
#define ROWS  25
#define COLUMNS 80
#define TOTAL_ROWS  50
#define TOAL_COLUMNS  160
typedef struct{
  short column;
  short row;
  char background_color;
  char font_color;
}char_console;
void set_char_console_color(char_console *console,char background_color, char font_color);
void write_text_to_char_console(char_console *console,const char *text);
void put_char_to_console(char_console *console, const char character);
void clear_console(char_console *console);
void move_cursor_on_console(char_console *console);
#endif
