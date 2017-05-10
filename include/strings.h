#ifndef STRINGS_H
#define STRINGS_H
#define TAB 0x9
#define NEW_LINE 0xa
#define RETURN_OF_CAR 0xd
#define NULL_CHARACTER  0x0
int string_len(const char *text);
int is_new_line(char ch);
int is_return_of_car(char ch);
int is_a_tab(char ch);
#endif
