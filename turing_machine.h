// File: turing_machine.h
typedef struct
{
  char * left;
  char * right;
  int l_size;
  int r_size;
  int l_len;
  int r_len;
  int idx;
}
turing_machine;

void tm_free(turing_machine * tm);
turing_machine * tm_new();
bool tm_move_left(turing_machine * tm);
bool tm_move_right(turing_machine * tm);
char tm_get_value(turing_machine * tm);
void tm_inc_value(turing_machine * tm);
void tm_dec_value(turing_machine * tm);
