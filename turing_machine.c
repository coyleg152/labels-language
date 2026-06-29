// File: turing_machine.c
#include <stdlib.h>
#include <stdbool.h>
#include "turing_machine.h"

#define DEFAULT_SIZE 16

void tm_free(turing_machine * tm)
{
  if (tm != NULL)
  {
    if (tm->left != NULL) free(tm->left);
    if (tm->right != NULL) free(tm->right);
    free(tm);
  }
}


turing_machine * tm_new()
{
  turing_machine * tm = malloc(sizeof(turing_machine));
  if (tm == NULL) return NULL;
  tm->l_len = 0;
  tm->r_len = 1;
  tm->l_size = DEFAULT_SIZE;
  tm->r_size = DEFAULT_SIZE;
  tm->left = malloc(tm->l_size);
  tm->right = malloc(tm->r_size);
  if (tm->left == NULL || tm->right == NULL)
  {
    tm_free(tm);
    return NULL;
  }
  tm->idx = 0;
  tm->right[0] = 0;
  return tm;
}


bool tm_move_left(turing_machine * tm)
{
  tm->idx -= 1;
  if (-(tm->idx + 1) >= tm->l_len)
  {
    tm->l_len += 1;
    if (tm->l_len > tm->l_size)
    {
      tm->l_size *= 2;
      if (tm->l_size < 0) return false;
      tm->left = realloc(tm->left, tm->l_size);
      if (tm->left == NULL) return false;
    }
    tm->left[-(tm->idx + 1)] = 0;
  }
  return true;
}


bool tm_move_right(turing_machine * tm)
{
  tm->idx += 1;
  if (tm->idx >= tm->r_len)
  {
    tm->r_len += 1;
    if (tm->r_len > tm->r_size)
    {
      tm->r_size *= 2;
      if (tm->r_size < 0) return false;
      tm->right = realloc(tm->right, tm->r_size);
      if (tm->right == NULL) return false;
    }
    tm->right[tm->idx] = 0;
  }
  return true;
}


char tm_get_value(turing_machine * tm)
{
  if (tm->idx < 0) return tm->left[-(tm->idx + 1)];
  else return tm->right[tm->idx];
}


void tm_inc_value(turing_machine * tm)
{
  if (tm->idx < 0) tm->left[-(tm->idx + 1)] += 1;
  else tm->right[tm->idx] += 1;
}


void tm_dec_value(turing_machine * tm)
{
  if (tm->idx < 0) tm->left[-(tm->idx + 1)] -= 1;
  else tm->right[tm->idx] -= 1;
}
