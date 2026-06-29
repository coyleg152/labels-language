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
bool str_realloc_if_full(string * str);
bool str_null_terminate(string * str);
void str_pop_back(string * str);
bool str_push_back(string * str, char c);
bool str_append(string * str, char * arr);
