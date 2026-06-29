// File: dynamic_string.c
#include <stdlib.h>
#include <stdbool.h>
#include "dynamic_string.h"

#define DEFAULT_SIZE 64

string * str_new()
{
  string * str = malloc(sizeof(string));
  if (str == NULL) return NULL;
  str->len = 0;
  str->size = DEFAULT_SIZE;
  str->chars = malloc(str->size);
  if (str->chars == NULL)
  {
    free(str);
    return NULL;
  }
  return str;
}


void str_free(string * str)
{
  if (str != NULL)
  {
    if (str->chars != NULL) free(str->chars);
    free(str);
  }
}


bool str_realloc_if_full(string * str)
{
  if (str->len < str->size) return true;
  str->size *= 2;
  if (str->size < 0) return false;
  str->chars = realloc(str->chars, str->size);
  return (str->chars != NULL);
}


bool str_null_terminate(string * str)
{
  if (!str_realloc_if_full(str)) return false;
  str->chars[str->len] = '\0';
  return true;
}


void str_pop_back(string * str)
{
  if (str->len < 1) return;
  str->len -= 1;
  str->chars[str->len] = '\0';
}


bool str_push_back(string * str, char c)
{
  if (!str_realloc_if_full(str)) return false;
  str->chars[str->len] = c;
  str->len += 1;
  return true;
}


bool str_append(string * str, char * arr)
{
  for (char * itr = arr; *itr != '\0'; itr++)
    if (!str_push_back(str, *itr)) return false;
  return str_null_terminate(str);
}
