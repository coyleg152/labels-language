// File: dynamic_string.h
typedef struct
{
  char * chars;
  int len;
  int size;
}
string;

string * str_new();
void str_free(string * str);
void str_realloc_if_full(string * str);
void str_null_terminate(string * str);
void str_pop_back(string * str);
void str_push_back(string * str, char c);
void str_append(string * str, char * arr);
