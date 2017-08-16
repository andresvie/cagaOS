#ifndef STRING_H
#define STRING_H
#include "types.h"
#define TAB 0x9
#define NEW_LINE 0xa
#define RETURN_OF_CAR 0xd
#define NULL_CHARACTER  0x0
uint32_t string_len(const char *text);
int is_new_line(char ch);
int is_return_of_car(char ch);
int is_a_tab(char ch);
char *itoa(int number, char *text);
char *reverse(char *text);
extern void *memcpy(const void *src,void *dest, size_t n);
void fill_empty(char *buffer,size_t bytes);
#endif
