// File: labels.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "dynamic_string.c"
#include "linked_list.c"

bool is_running;

void exit_program() {is_running = false;}

int err(char * msg)
{
  fprintf(stderr, "%s", msg);
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
  if (argc < 2) return err("Usage: ./labels.out (filename)\n");

  is_running = true;
  signal(SIGINT, exit_program);
  signal(SIGTERM, exit_program);

  string * code = str_new();
  char buf;
  int fd;

  for (int i = 1; i < argc; i++)
  {
    fd = open(argv[i], O_RDONLY);
    if (fd < 0)
    {
      str_free(code);
      return err("Failed to open file\n");
    }

    while (read(fd, &buf, 1) > 0) str_push_back(code, buf);

    close(fd);
    str_push_back(code, ' ');
  }

  linked_list * tm = ll_new(0);

  for (int i = 0; is_running && i < code->len; i++)
  {
    switch (code->chars[i])
    {
      case '+':
        tm->val += 1;
        break;
      case '-':
        tm->val -= 1;
        break;
      case '<':
        if (tm->prev == NULL) ll_push_prev(tm, 0);
        tm = tm->prev;
        break;
      case '>':
        if (tm->next == NULL) ll_push_next(tm, 0);
        tm = tm->next;
        break;
      case '.':
        printf("%c", tm->val);
        break;
      case '?':
        if (tm->val == 0)
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
        do
        {
          str_push_back(label, code->chars[i]);
          i++;
        }
        while (i < code->len && is_label(code->chars[i]));
        i = next_token(code, i);
        if (!(i < code->len && code->chars[i] == ':'))
        {
          i = find_label_entry(code, label);
        }
        str_free(label);
        break;
    }
  }

  str_free(code);
  ll_free(tm);
  return 0;
}
