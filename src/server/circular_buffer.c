#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

void strncircular(t_circular *c, char *str, int n)
{
  int i;
  int cpos;

  i = 0;
  cpos = c->pos;
  while (i < n)
  {
    c->buffer[cpos] = str[i];
    INCR(cpos);
    ++i;
    ++c->len;
  }
}

static bool end(t_circular *c, int pos)
{
  return (c->buffer[pos] == '\r' &&
          c->buffer[INCR(pos)] == '\n');
}

bool find_command(t_circular *c)
{
  int pos;
  int i;

  i = 0;
  pos = c->pos;
  while (i < c->len)
  {
    if (end(c, pos))
      return (true);
    ++i;
    INCR(pos);
  }
  return (false);
}

void strfromcircular(t_circular *c, char out[MESSAGE_MAX_SIZE])
{
  int i;

  i = 0;
  memset(out, 0, MESSAGE_MAX_SIZE);
  while (!end(c, c->pos))
  {
    out[i] = c->buffer[c->pos];
    INCR(c->pos);
    ++i;
    --c->len;
  }
  c->buffer[c->pos] = 0;
  out[i] = 0;
  INCR(c->pos);
  c->len -= 1;
}