#include "console.h"
#include "strings.h"
#include "io.h"
static volatile char *char_console_buffer = (volatile char *)FRAME_BUFFER_ADDRESS;
void set_char_console_color(char_console *console,char background_color, char font_color)
{
  console->background_color = background_color;
  console->font_color = font_color;
  clear_console(console);
}

void write_text_to_char_console(char_console *console, const char *text){
  int column = 0;
  int length = string_len(text);
  for(int i=0;i<length;i++){
    char char_to_write = text[i];
    if(is_new_line(char_to_write)){
      console->row += 1;
      console->column = 0;
      continue;
    }
    if(is_return_of_car(char_to_write)){
      console->column = 0;
      continue;
    }
    if(is_a_tab(char_to_write)){
      console->column += (4*2);
      continue;
    }
    if(console->column >= TOAL_COLUMNS){
      console->row +=1;
      console->column = 0;
    }
    if(console->row >= TOTAL_ROWS){
      console->column = 0;
      console->row = 0;
      clear_console(console);
    }
    column = (TOAL_COLUMNS * (console->row)) + console->column;
    char_console_buffer[column] = text[i];
    console->column += 2;
  }
  move_cursor_on_console(console);
}

void clear_console(char_console *console)
{
  int column = 0;
  for(int i=0;i<TOTAL_ROWS;i++){
    for(int j=0;j<TOAL_COLUMNS;j+=2){
      column = (i*COLUMNS) + j;
      char_console_buffer[column] = 0x20;
      char_console_buffer[column + 1] = (4<<(console->font_color & 0x0F)) | (console->background_color & 0x0F);
    }
  }
  move_cursor_on_console(console);
}

void move_cursor_on_console(char_console *console){
  unsigned short position = ((TOAL_COLUMNS * (console->row)) + console->column) / 2;
  write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_LOW_BITS_COMMAND);
	write_port(FRAME_DATA_PORT, position & 0x00FF);
	write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_HIGHT_BITS_COMMAND);
	write_port(FRAME_DATA_PORT, (position >> 8)  & 0x00FF);
}
