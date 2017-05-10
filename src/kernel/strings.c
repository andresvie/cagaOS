#include "strings.h"
int string_len(const char *text){
  int length = 0;
  while(*text!=NULL_CHARACTER){
    text++;
    length++;
  }
  return length;
}
int is_new_line(char ch){
  return NEW_LINE == ch;
}
int is_return_of_car(char ch){
  return RETURN_OF_CAR == ch;
}
int is_a_tab(char ch){
  return TAB == ch;
}
