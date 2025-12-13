// File: dynamic_string.c
// Include this file *after* including <stdlib.h>
typedef struct
{
  char * chars;
  int len;
  int size;
}
string;

string * str_new()
{
  string * str = malloc(sizeof(string));
  str->len = 0;
  str->size = 16;
  str->chars = malloc(str->size);
  return str;
}

void str_free(string * str)
{
  if (str == NULL) return;
  free(str->chars);
  free(str);
}

void str_realloc_if_full(string * str)
{
  if (str->size < 1)
  {
    str->size = 1;
    str->chars = realloc(str->chars, str->size);
  }
  while (str->len >= str->size)
  {
    str->size *= 2;
    str->chars = realloc(str->chars, str->size);
  }
}

void str_null_terminate(string * str)
{
  str_realloc_if_full(str);
  str->chars[str->len] = '\0';
}

void str_pop_back(string * str)
{
  if (str->len < 1) return;
  str->len -= 1;
  str->chars[str->len] = '\0';
}

void str_push_back(string * str, char c)
{
  str_realloc_if_full(str);
  str->chars[str->len] = c;
  str->len += 1;
}

void str_append(string * str, char * arr)
{
  for (char * itr = arr; *itr != '\0'; itr++) str_push_back(str, *itr);
  str_null_terminate(str);
}
