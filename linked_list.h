// File: linked_list.h
typedef struct linked_list
{
  struct linked_list * prev;
  struct linked_list * next;
  char val;
}
linked_list;

linked_list * ll_new(char init_val);
void ll_free(linked_list * itr);
void ll_push_prev(linked_list * itr, char init_val);
void ll_push_next(linked_list * itr, char init_val);
void ll_pop_prev(linked_list * itr);
void ll_pop_next(linked_list * itr);
