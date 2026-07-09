// File: main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "dynamic_string.h"
#include "turing_machine.h"

bool is_running;
void exit_program(int sig) {is_running = false;}


int err(char * msg)
{
  fprintf(stderr, "Error: %s\n", msg);
  return 1;
}


bool is_label(char c)
{
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
  || (c >= '0' && c <= '9') || c == '_';
}


bool is_token(char c)
{
  return is_label(c) || c == '+' || c == '-' || c == '<' || c == '>'
  || c == '.' || c == '?' || c == ':';
}


int next_token(string * code, int i)
{
  do {i++;} while (i < code->len && !is_token(code->chars[i]));
  return i;
}


int skip_label(string * code, int i)
{
  do {i++;} while (i < code->len && is_label(code->chars[i]));
  return i;
}


int find_label_entry(string * code, string * label)
{
  if (label->len < 1) return code->len;
  for (int i = 0; i < code->len; i++)
  {
    if (!is_label(code->chars[i])) continue;
    int j;
    for (j = 0; j < label->len; j++)
    {
      if (i + j >= code->len || code->chars[i + j] != label->chars[j])
      {
        i += j;
        while (i < code->len && is_label(code->chars[i])) i++;
        goto continue2;
      }
    }
    i += j - 1;
    i = next_token(code, i);
    if (i < code->len && code->chars[i] == ':') return i;
    continue2:
    i--;
  }
  return code->len;
}


int main(int argc, char ** argv)
{
  if (argc < 2) return err("Usage: ./labels.out (filename) ...");

  is_running = true;
  signal(SIGINT, exit_program);
  signal(SIGTERM, exit_program);

  string * code = str_new();
  if (code == NULL) return err("malloc() failed");
  char buf;
  int fd, i;
  int retval = 0;

  for (i = 1; i < argc; i++)
  {
    fd = open(argv[i], O_RDONLY);
    if (fd < 0)
    {
      str_free(code);
      return err("open() failed");
    }

    while (read(fd, &buf, 1) > 0)
    {
      if (!str_push_back(code, buf))
      {
        close(fd);
        str_free(code);
        return err("str_push_back() failed");
      }
    }

    close(fd);
    if (!str_push_back(code, ' '))
    {
      str_free(code);
      return err("str_push_back() failed");
    }
  }

  turing_machine * tm = tm_new();
  if (tm == NULL)
  {
    str_free(code);
    return err("tm_new() failed");
  }

  for (i = 0; is_running && i < code->len; i++)
  {
    switch (code->chars[i])
    {
    case '+':
      tm_inc_value(tm);
      break;
    case '-':
      tm_dec_value(tm);
      break;
    case '<':
      if (!tm_move_left(tm))
      {
        retval = err("tm_move_left() failed");
        goto cleanup;
      }
      break;
    case '>':
      if (!tm_move_right(tm))
      {
        retval = err("tm_move_right() failed");
        goto cleanup;
      }
      break;
    case '.':
      printf("%c", tm_get_value(tm));
      break;
    case '?':
      if (tm_get_value(tm) == 0)
      {
        i = next_token(code, i);
        if (i < code->len && is_label(code->chars[i]))
        {
          i = skip_label(code, i);
          i--;
        }
      }
      break;
    default:
      if (!is_label(code->chars[i])) break;
      string * label = str_new();
      if (label == NULL)
      {
        retval = err("str_new() failed");
        goto cleanup;
      }
      do
      {
        if (!str_push_back(label, code->chars[i]))
        {
          retval = err("str_push_back() failed");
          goto cleanup;
        }
        i++;
      }
      while (i < code->len && is_label(code->chars[i]));
      i = next_token(code, i - 1);
      if (!(i < code->len && code->chars[i] == ':'))
      {
        i = find_label_entry(code, label);
      }
      str_free(label);
      break;
    }
  }

  cleanup:
  tm_free(tm);
  str_free(code);
  return retval;
}
