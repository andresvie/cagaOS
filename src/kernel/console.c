#include <console.h>
#include "console.h"
#include "string.h"
#include "io.h"

volatile char *char_console_buffer = (volatile char *) FRAME_BUFFER_ADDRESS;
char_console *console = 0x0;
char *back_buffer = 0x0;
char *buffer = 0x0;

static void _clear_console();

static void _write_text_to_char_console(const char *text);

static void _write_character_to_console(char char_to_write);

static void _move_cursor_on_console();

static void _scroll_console();

static void _swap_buffer();

static uint32_t _get_first_rows_index();


void init_console(char_console *_console, char *_back_buffer, char *_buffer) {
    console = _console;
    back_buffer = _back_buffer;
    buffer = _buffer;
    console->column = 0x0;;
    console->buffer_index = 0x0;
    console->row = 0x0;
    console->background_color = BLACK;
    console->font_color = BLUE;
}

void set_char_console_color(char background_color, char font_color) {
    console->background_color = background_color;
    console->font_color = font_color;
    _clear_console();
}

void put_char_to_console(const char character) {
    const char buffer[2] = {character, 0x0};
    _write_text_to_char_console(buffer);
}

void write_text_to_char_console(const char *text) {
    _write_text_to_char_console(text);
}


static void _write_text_to_char_console(const char *text) {
    uint32_t length = string_len(text);
    uint32_t i = 0;
    if (length == 0) {
        return;
    }
    for (; i < length; i++) {
        buffer[console->buffer_index] = text[i];
        console->buffer_index++;
        if (console->column > TOTAL_COLUMNS - 2) {
            console->row += 1;
            console->column = 0;
        }
        _write_character_to_console(text[i]);
        if (console->row > (ROWS - 3)) {
            _scroll_console();
        }
    }
    _move_cursor_on_console();
}


static void _scroll_console() {
    uint32_t size = ((ROWS - 3) * COLUMNS);
    uint32_t column = 0;
    console->buffer_index = 0x0;
    console->row = 0;
    console->column = 0;
    _clear_console();
    _swap_buffer();
    while (column < size) {
        _write_character_to_console(buffer[console->buffer_index]);
        if (console->column > TOTAL_COLUMNS - 2) {
            console->row += 1;
            console->column = 0;
        }
        column = ((TOTAL_COLUMNS * (console->row)) + console->column) / 2;
        console->buffer_index++;
    }
    console->row = ROWS - 3;
    console->column = 0;
}

static void _clear_console() {
    console->row = 0;
    console->column = 0;
    uint32_t column = 0;
    uint32_t i = 0;
    uint32_t j = 0;
    for (; i < ROWS; i++) {
        j = 0;
        for (; j < TOTAL_COLUMNS; j += 2) {
            column = (i * TOTAL_COLUMNS) + j;
            char_console_buffer[column] = ' ';
            char_console_buffer[column + 1] = (4 << (console->font_color & 0x0F)) | (console->background_color & 0x0F);
        }
    }
    _move_cursor_on_console();
}


static void _move_cursor_on_console() {
    unsigned short position = (unsigned short) ((TOTAL_COLUMNS * (console->row)) + console->column) / 2;
    write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_LOW_BITS_COMMAND);
    write_port(FRAME_DATA_PORT, position & 0x00FF);
    write_port(FRAME_COMMAND_PORT, FRAME_BUFFER_SEND_HIGHT_BITS_COMMAND);
    write_port(FRAME_DATA_PORT, (position >> 8) & 0x00FF);
}


static void _write_character_to_console(char char_to_write) {

    if (is_new_line(char_to_write)) {
        console->row += 1;
        console->column = 0;
        return;
    }

    if (is_return_of_car(char_to_write)) {
        console->column = 0;
        return;
    }

    if (is_a_tab(char_to_write)) {
        console->column += (4 * 2);
        return;
    }

    uint32_t column = (TOTAL_COLUMNS * (console->row)) + console->column;
    char_console_buffer[column] = char_to_write;
    console->column += 2;

}


static void _swap_buffer() {
    char *temp;
    uint32_t size = ((ROWS - 3) * COLUMNS);
    uint32_t i = _get_first_rows_index();
    uint32_t index = 0;
    fill_empty(back_buffer, CONSOLE_BUFFER_SIZE);
    for (; i < size; i++) {
        back_buffer[index] = buffer[i];
        index++;
    }
    temp = back_buffer;
    back_buffer = buffer;
    buffer = temp;

}

static uint32_t _get_first_rows_index() {
    uint32_t i = 0;
    for (; i < COLUMNS; i++) {
        if (is_new_line(buffer[i])) {
            return i + 1;
        }
    }
    return COLUMNS;
}