#include "console.h"
#include "string.h"
#include "io.h"

static volatile char *char_console_buffer = (volatile char *)FRAME_BUFFER_ADDRESS;
static char_console consoles[8];
static char_console *current_console = 0x0;
static char back_buffer[COLUMNS * ROWS];
void init_console()
{
  int i=0;
  for(;i<NUMBER_OF_CONSOLES;i++){
    consoles[i].offset = 0x0;
    consoles[i].background_color = BLACK;
    consoles[i].font_color = RED;
    consoles[i].buffer_index = 0;
    fill_empty(consoles[i].buffer,COLUMNS * ROWS);
    consoles[i].row = 0;
    consoles[i].column = 0;
  }
  fill_empty(back_buffer, COLUMNS * ROWS);
  current_console=consoles;
}

void set_char_console_color(char background_color, char font_color)
{
  current_console->background_color = background_color;
  current_console->font_color = font_color;
  clear_console(current_console);
}

void put_char_to_console(const char character)
{
  const char buffer[2] = {character, 0x0};
  write_text_to_char_console(buffer);
}

void write_text_to_char_console(const char *text){
  char_console * console = current_console;
  int column = 0;
  int length = string_len(text);
  int i=0;
  for(;i<length;i++){
    char char_to_write = text[i];
    console->buffer[console->buffer_index] = char_to_write;
    console->buffer_index++;
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
    if(console->column > TOTAL_COLUMNS){
      console->row +=1;
      if(console->row > (ROWS - 2)){
        scroll(console);
      }
      console->column = 0;
    }
    column = (TOTAL_COLUMNS * (console->row)) + console->column;
    char_console_buffer[column] = text[i];
    console->column += 2;
  }
  if(console->row > (ROWS - 2)){
    scroll(console);
  }
  move_cursor_on_console(console);
}

void scroll(char_console *console)
{
  uint32_t total_bytes_to_copy = (ROWS - 2) * COLUMNS;
  uint32_t i=0;
  for(i=COLUMNS;i<total_bytes_to_copy;i++)
  {
    back_buffer[i-COLUMNS] = console->buffer[i];
  }
  back_buffer[total_bytes_to_copy]=0x0;
  console->row = 0;
  console->buffer_index = 0;
  console->column = 0;
  write_text_to_char_console(back_buffer);
}

void clear_console(char_console *console)
{
  int column = 0;
  int i=0;
  for(;i<TOTAL_ROWS;i++){
    int j=0;
    for(;j<TOTAL_COLUMNS;j+=2){
      column = (i*COLUMNS) + j;
      char_console_buffer[column] = 0x20;
      char_console_buffer[column + 1] = (4<<(console->font_color & 0x0F)) | (console->background_color & 0x0F);
    }
  }
  move_cursor_on_console(console);
}

void move_cursor_on_console(char_console *console){
  unsigned short position = ((TOTAL_COLUMNS * (console->row)) + console->column) / 2;
  write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_LOW_BITS_COMMAND);
	write_port(FRAME_DATA_PORT, position & 0x00FF);
	write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_HIGHT_BITS_COMMAND);
	write_port(FRAME_DATA_PORT, (position >> 8)  & 0x00FF);
}
