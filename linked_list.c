// File: linked_list.c
#include <stdlib.h>
#include "linked_list.h"

linked_list * ll_new(char init_val)
{
  linked_list * itr = malloc(sizeof(linked_list));
  itr->prev = NULL;
  itr->next = NULL;
  itr->val = init_val;
  return itr;
}


void ll_free(linked_list * itr)
{
  if (itr == NULL) return;
  while (itr->next != NULL) itr = itr->next;
  while (itr->prev != NULL)
  {
    itr = itr->prev;
    free(itr->next);
  }
  free(itr);
}


void ll_push_prev(linked_list * itr, char init_val)
{
  if (itr == NULL) return;
  linked_list * temp = itr->prev;
  itr->prev = ll_new(init_val);
  itr->prev->next = itr;
  if (temp != NULL)
  {
    temp->next = itr->prev;
    itr->prev->prev = temp;
  }
}


void ll_push_next(linked_list * itr, char init_val)
{
  if (itr == NULL) return;
  linked_list * temp = itr->next;
  itr->next = ll_new(init_val);
  itr->next->prev = itr;
  if (temp != NULL)
  {
    temp->prev = itr->next;
    itr->next->next = temp;
  }
}


void ll_pop_prev(linked_list * itr)
{
  if (itr == NULL || itr->prev == NULL) return;
  linked_list * temp = itr->prev->prev;
  free(itr->prev);
  itr->prev = temp;
  if (temp != NULL) temp->next = itr;
}


void ll_pop_next(linked_list * itr)
{
  if (itr == NULL || itr->next == NULL) return;
  linked_list * temp = itr->next->next;
  free(itr->next);
  itr->next = temp;
  if (temp != NULL) temp->prev = itr;
}
