#include "string.h"
void fill_empty(char *buffer,size_t bytes)
{
  size_t i;
  for(i=0;i<bytes;i++)
  {
    buffer[i]=' ';
  }
}
char *itoa(int number, char *text)
{
  int new_number = number;
  int index = 0;
  int remain = 0;
  if(new_number == 0)
  {
    text[0] = '0';
    text[1] = NULL_CHARACTER;
    return text;
  }
  if(new_number < 0)
  {
    text[0] = '-';
    index++;
    new_number = new_number * -1;
  }
  while(new_number !=0)
  {
    remain = new_number % 10;
    text[index] = '0' + remain;
    new_number = new_number / 10;
    index++;
  }
  text[index] = NULL_CHARACTER;
  return reverse(text);
}

char *reverse(char *text)
{
  int len = string_len(text);
  char aux;
  int start = 0;
  int end = len;
  while(start != end){
    aux = text[start];
    text[start] = text[end - 1];
    text[end - 1] = aux;
    ++start;
    --end;
  }
  return text;
}

int string_len(const char *text){
  int length = 0;
  while(*text != NULL_CHARACTER){
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
